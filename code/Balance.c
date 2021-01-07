/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"


/*************************************************************************************************
* 函数名: BalManage
* 参  数: 无
* 返回值: 无
* 描  述: 
	1. 平衡开启条件是电压、压差及电流 同时满足
	2. 平衡过程中，不再进行平衡检测
	3. 断线检测借用平衡
*************************************************************************************************/
void BalManage(void)
{
	U8 i;

	if(!bBalancingFlg && !bCellOpenDecFlag)		   //在一个平衡周期中或开启断线检测时不判定是否进行平衡
	{
	    if(bBAL_EN)
	    {
			uiBalanceChannel = 0;
	    	if(((uiCellVmax>E2uiOVvol)&&(!bHV))		//发生温度保护时不进行平衡,判定进入过压、过压恢复、进入充电截止时暂停平衡 
				||((uiCellVmax < E2uiOVRvol)&&(bHV))
				|| bOTC || bUTC || bOTD || bUTD) 
	    	{
	    		bBalanceFlg = 0;
	    		ucBalanceTimeCnt = 0;
	    	}
	    	else
		    {
		    	if(((uiCellVmax>E2uiBalanceVol) && (uiCellVmax-uiCellVmin)>=E2uiBalanceVolDiff) && (Info.slCurr>=E2siBalCurrent))
	    		{
	    			if(!bBalanceFlg)
	    			{
	    				ucBalanceTimeCnt++;															 
	    			}
	    			if(ucBalanceTimeCnt >= BAL_DELAY_CNT)											 
	    			{
	    				for(i=ucCellNumOffset; i<ucCellNumOffset+ucCellNum; i++)
	    				{
	    					if(((Info.uiVCell[i]-uiCellVmin)>=E2uiBalanceVolDiff)&&(Info.uiVCell[i]>=E2uiBalanceVol))	//电芯电压大于平衡电压，且压差大于阈值，开启该电芯平衡
	    					{
	    						uiBalanceChannel |= (1<<i);
	    					}
	    				}
	    				bBalanceFlg = 1;
	    			}
	    		}
	    		else
	    		{
	    			bBalanceFlg = 0;
	    			ucBalanceTimeCnt = 0;
	    		}
	        }
		}
	}	
}


/*************************************************************************************************
* 函数名: OpenBal， CloseBal
* 参  数: 无
* 返回值: 无
* 描  述: 开启和关闭平衡
*************************************************************************************************/
void OpenBal(U16 BalChTemp)
{
	REG.AFESCONF4 = BalChTemp>>5;       
	TwiWriteAFE(AFE_SCONF4, &REG.AFESCONF4);
	REG.AFESCONF5 = BalChTemp;
	TwiWriteAFE(AFE_SCONF5, &REG.AFESCONF5);
	bBalanceStateFlg = 1;
}

void CloseBal(void)
{
    if(bBalanceStateFlg)
    {
		bBalanceStateFlg = 0;
		REG.AFESCONF4 = 0;
		TwiWriteAFE(AFE_SCONF4, &REG.AFESCONF4);		   //	CleaerBalance=0x00
		REG.AFESCONF5 = 0;
		TwiWriteAFE(AFE_SCONF5, &REG.AFESCONF5);		   //when dec the VADC must close the balance 
	}
}


/*******************************************************************************
Function: CheckCtoVol(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
bit CheckCtoVol(void)
{
    BOOL bResult=0;

	if(bCTO_EN)		//判断是否支持断线检测
	{
		if(!bCTO)	//如果已经检测到断线，则不再检测
		{
			if(bCTOValidFlg)	//判断电压压差是否超过1.2V
			{
				if(uiVadcVmin < VOL_CELL_CUT_180MV)	//180mV
				{
					bResult = 1;
					if(++ucCtoCnt >= TIME_50MS_500MS)		//断线 500mS
					{
						bCTO = 1;
					}
				}
				else
				{
					bCTOValidFlg = 0;
					ucCtoCnt = 0;
				}
			}
		}	
#ifdef SP_CTO_RECOVER
		else		//断线恢复功能，每250mS一个周期判断最小电压
		{
			if(uiVadcVmin >= VOL_CELL_CUT_180MV)	//180mV
			{
				if(++ucCtoRCnt >= TIME_250MS_1S)
				{
					bCTO = 0;
				}
			}
			else
			{
				ucCtoRCnt = 0;
			}
		}
#endif
	}

    return bResult;
}


/*************************************************************************************************
* 函数名: BalProcess
* 参  数: 无
* 返回值: 无
* 描  述: 
	1. 平衡周期分为5个STEP，合计250mS
	2. 平衡效率<100/(250mS*2)(采用奇偶平衡)
	3. 如果检测到断线，则持续开启平衡进行断线检测
	4. 平衡开启后，正常的电压保护判断延时可能会多延时250mS(一个平衡周期)
*************************************************************************************************/
void BalProcess(void)
{
    U16 BalChTemp;

//判断电芯电压压差是否超过1.2V，如果超过则允许判断断线，主要解决电芯电压<2V情况下平衡会触发断线判断条件
//判断电芯最大电压是否小于1.38V，如果小于则允许判断断线，主要解决未有效检测电芯电压的情况下压差不满足断线判断条件
	if((uiCellVmax-uiCellVmin>=VOL_CELL_CUT_1200MV) || (uiCellVmax<=VOL_CELL_CUT_1380MV))
	{
		bCTOValidFlg = 1;
	}
    
    switch(ucBalanceStep)
    {
        case BALANCE_ENABLE:          //VADC采集的数据用于正常电压判断
            if(bCellOpenDecFlag || bBalanceFlg)
	        {
	            if(bBalanceOddFlg)							  //odd balance
	            {
	                BalChTemp = uiBalanceChannel&0x5555;		  					
	            }
	            else											 //even balance
	            {
	                BalChTemp = uiBalanceChannel&0xAAAA;							
	            }	        
				OpenBal(BalChTemp);	//开启平衡	                 
	            ucBalanceStep = BALANCE_START;
	            bBalancingFlg = 1;
	        }
            break;

        case BALANCE_START:         //VADC采集的电压数据丢掉
            ucBalanceStep = BALANCING;
            break;

        case BALANCING:             //VADC采集的电压数据判断断线
            if(!CheckCtoVol())      //如果发现有断线则连续检测断线
	        {
				CloseBal();
                ucBalanceStep = BALANCE_DISABLE;
                bBalanceOddFlg = ~bBalanceOddFlg;
	        }
            break;

        case BALANCE_DISABLE:       //VADC采集的电压数据丢掉
            if(!CheckCtoVol())      //如果发现有断线则连续检测断线
	        {
                ucBalanceStep = BALANCE_NULL;
		    }
		    else 
		    {
                ucBalanceStep = BALANCE_ENABLE;
                bBalanceOddFlg = ~bBalanceOddFlg;
		    }
            break;

        case BALANCE_NULL:          //VADC采集的数据用于正常电压判断
            ucBalanceStep = BALANCE_ENABLE;
            bCellOpenDecFlag = 0;
            bBalanceFlg = 0;
			bBalancingFlg = 0;		
            break;
	}
}


/*************************************************************************************************
* 函数名: CellOpenProcess
* 参  数: 无
* 返回值: 无
* 描  述: 每2S开启一次断线检测
*************************************************************************************************/
void CellOpenProcess(void)
{
#ifdef SP_CTO_RECOVER
	if(bCTO_EN)					//支持断线恢复
#else
    if(bCTO_EN && !bCTO)			//如果已发生断线则不检测
#endif
	{
        if(++ucCellOpenDecCnt >= TIME_50MS_2250MS)	//2S
		{
			ucCellOpenDecCnt = TIME_50MS_2250MS;	//避免该检测周期是平衡的偶数倍关系
			if(!bBalancingFlg)						//如果正在平衡，则等一个平衡周期结束后再开启断线检测
			{
            	ucCellOpenDecCnt = 0;
            	bCellOpenDecFlag = 1;
            	uiBalanceChannel = 0x03ff;
			}
		}
	}	
}



