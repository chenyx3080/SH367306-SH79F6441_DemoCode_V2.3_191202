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
* ������: BalManage
* ��  ��: ��
* ����ֵ: ��
* ��  ��: 
	1. ƽ�⿪�������ǵ�ѹ��ѹ����� ͬʱ����
	2. ƽ������У����ٽ���ƽ����
	3. ���߼�����ƽ��
*************************************************************************************************/
void BalManage(void)
{
	U8 i;

	if(!bBalancingFlg && !bCellOpenDecFlag)		   //��һ��ƽ�������л������߼��ʱ���ж��Ƿ����ƽ��
	{
	    if(bBAL_EN)
	    {
			uiBalanceChannel = 0;
	    	if(((uiCellVmax>E2uiOVvol)&&(!bHV))		//�����¶ȱ���ʱ������ƽ��,�ж������ѹ����ѹ�ָ����������ֹʱ��ͣƽ�� 
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
	    					if(((Info.uiVCell[i]-uiCellVmin)>=E2uiBalanceVolDiff)&&(Info.uiVCell[i]>=E2uiBalanceVol))	//��о��ѹ����ƽ���ѹ����ѹ�������ֵ�������õ�оƽ��
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
* ������: OpenBal�� CloseBal
* ��  ��: ��
* ����ֵ: ��
* ��  ��: �����͹ر�ƽ��
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

	if(bCTO_EN)		//�ж��Ƿ�֧�ֶ��߼��
	{
		if(!bCTO)	//����Ѿ���⵽���ߣ����ټ��
		{
			if(bCTOValidFlg)	//�жϵ�ѹѹ���Ƿ񳬹�1.2V
			{
				if(uiVadcVmin < VOL_CELL_CUT_180MV)	//180mV
				{
					bResult = 1;
					if(++ucCtoCnt >= TIME_50MS_500MS)		//���� 500mS
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
		else		//���߻ָ����ܣ�ÿ250mSһ�������ж���С��ѹ
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
* ������: BalProcess
* ��  ��: ��
* ����ֵ: ��
* ��  ��: 
	1. ƽ�����ڷ�Ϊ5��STEP���ϼ�250mS
	2. ƽ��Ч��<100/(250mS*2)(������żƽ��)
	3. �����⵽���ߣ����������ƽ����ж��߼��
	4. ƽ�⿪���������ĵ�ѹ�����ж���ʱ���ܻ����ʱ250mS(һ��ƽ������)
*************************************************************************************************/
void BalProcess(void)
{
    U16 BalChTemp;

//�жϵ�о��ѹѹ���Ƿ񳬹�1.2V����������������ж϶��ߣ���Ҫ�����о��ѹ<2V�����ƽ��ᴥ�������ж�����
//�жϵ�о����ѹ�Ƿ�С��1.38V�����С���������ж϶��ߣ���Ҫ���δ��Ч����о��ѹ�������ѹ���������ж�����
	if((uiCellVmax-uiCellVmin>=VOL_CELL_CUT_1200MV) || (uiCellVmax<=VOL_CELL_CUT_1380MV))
	{
		bCTOValidFlg = 1;
	}
    
    switch(ucBalanceStep)
    {
        case BALANCE_ENABLE:          //VADC�ɼ�����������������ѹ�ж�
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
				OpenBal(BalChTemp);	//����ƽ��	                 
	            ucBalanceStep = BALANCE_START;
	            bBalancingFlg = 1;
	        }
            break;

        case BALANCE_START:         //VADC�ɼ��ĵ�ѹ���ݶ���
            ucBalanceStep = BALANCING;
            break;

        case BALANCING:             //VADC�ɼ��ĵ�ѹ�����ж϶���
            if(!CheckCtoVol())      //��������ж���������������
	        {
				CloseBal();
                ucBalanceStep = BALANCE_DISABLE;
                bBalanceOddFlg = ~bBalanceOddFlg;
	        }
            break;

        case BALANCE_DISABLE:       //VADC�ɼ��ĵ�ѹ���ݶ���
            if(!CheckCtoVol())      //��������ж���������������
	        {
                ucBalanceStep = BALANCE_NULL;
		    }
		    else 
		    {
                ucBalanceStep = BALANCE_ENABLE;
                bBalanceOddFlg = ~bBalanceOddFlg;
		    }
            break;

        case BALANCE_NULL:          //VADC�ɼ�����������������ѹ�ж�
            ucBalanceStep = BALANCE_ENABLE;
            bCellOpenDecFlag = 0;
            bBalanceFlg = 0;
			bBalancingFlg = 0;		
            break;
	}
}


/*************************************************************************************************
* ������: CellOpenProcess
* ��  ��: ��
* ����ֵ: ��
* ��  ��: ÿ2S����һ�ζ��߼��
*************************************************************************************************/
void CellOpenProcess(void)
{
#ifdef SP_CTO_RECOVER
	if(bCTO_EN)					//֧�ֶ��߻ָ�
#else
    if(bCTO_EN && !bCTO)			//����ѷ��������򲻼��
#endif
	{
        if(++ucCellOpenDecCnt >= TIME_50MS_2250MS)	//2S
		{
			ucCellOpenDecCnt = TIME_50MS_2250MS;	//����ü��������ƽ���ż������ϵ
			if(!bBalancingFlg)						//�������ƽ�⣬���һ��ƽ�����ڽ������ٿ������߼��
			{
            	ucCellOpenDecCnt = 0;
            	bCellOpenDecFlag = 1;
            	uiBalanceChannel = 0x03ff;
			}
		}
	}	
}



