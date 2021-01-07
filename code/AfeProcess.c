/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"
#include "Calibrate.h"

/*******************************************************************************
Function: VolProtect(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void VolProtect(void)
{
	if(!bHV)
	{
		if(uiCellVmax > E2uiOVvol)
		{		
			if(++ucOVcnt >= OV_DELAY_CNT)
			{
				bHV = 1;
				ucOVcnt = 0;
				ucOVRcnt = 0;
			}
		}
		else if(uiCellVmax < E2uiOVRvol)
		{
			if(ucOVcnt > 0)
			{
				ucOVcnt--;
			}
		}
	}
	else
	{
		if(uiCellVmax < E2uiOVRvol)
		{			
			if(++ucOVRcnt >= OVR_DELAY_CNT)
			{
				bHV = 0;
				ucOVcnt = 0;
				ucOVRcnt = 0;
			}
		}
		else if(uiCellVmax > E2uiOVvol)
		{
			if(ucOVRcnt > 0)
			{
				ucOVRcnt--;
			}
		}
	}

	if(!bUV)
	{
		if(uiCellVmin < E2uiUVvol)
		{		
			if(++ucUVcnt >= UV_DELAY_CNT)
			{
				bUV = 1;
				ucUVcnt = 0;
				ucUVRcnt = 0;

	            bChkChgerFlg = 1;
	            bChgerConectFlg = 0;
				ucChgerCnt = 0;
	    		REG.AFESCONF1 |= 0x01;
	        	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	//使能充电器检测
			}
		}
		else if(uiCellVmin > E2uiUVRvol)
		{
			if(ucUVcnt > 0)
			{
				ucUVcnt--;
			}
		}
	}
	else
	{
		if(uiCellVmin > E2uiUVRvol)
		{			
			if(++ucUVRcnt >= UVR_DELAY_CNT)
			{
				bUV = 0;
				ucUVcnt = 0;
				ucUVRcnt = 0;
			}
		}
		else if(uiCellVmin < E2uiUVvol)
		{
			if(ucUVRcnt > 0)
			{
				ucUVRcnt--;
			}
		}
	}
}


/*******************************************************************************
Function: TempeProtect(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void TempeProtect(void)								//TempNum=0, Support one temperature 
{
	if(!bOTC)
	{
		if(uiTempeMax > E2uiTempOTC)
		{
			if(++ucOTCcnt >= TEMPE_DELAY_CNT)
			{
				bOTC = 1;
				ucOTCcnt = 0;
				ucOTCRcnt = 0;
			}
		}
		else if(uiTempeMax < E2uiTempOTCR)
		{
			if(ucOTCcnt > 0)
			{
				ucOTCcnt--;
			}
		}
	}
	else
	{
		if(uiTempeMax < E2uiTempOTCR)
		{
			if(++ucOTCRcnt >= TEMPER_DELAY_CNT)
			{
				bOTC = 0;
				ucOTCcnt = 0;
				ucOTCRcnt = 0;
			}
		}
		else if(uiTempeMax > E2uiTempOTC)
		{
			if(ucOTCRcnt > 0)
			{
				ucOTCRcnt--;
			}
		}
	}

	if(!bUTC)
	{
		if(uiTempeMin < E2uiTempUTC)
		{
			if(++ucUTCcnt >= TEMPE_DELAY_CNT)
			{
				bUTC = 1;
				ucUTCcnt = 0;
				ucUTCRcnt = 0;
			}
		}
		else if(uiTempeMin > E2uiTempUTCR)
		{
			if(ucUTCcnt > 0)
			{
				ucUTCcnt--;
			}
		}
	}
	else
	{
		if(uiTempeMin > E2uiTempUTCR)
		{
			if(++ucUTCRcnt >= TEMPER_DELAY_CNT)
			{
				bUTC = 0;
				ucUTCcnt = 0;
				ucUTCRcnt = 0;
			}
		}
		else if(uiTempeMin < E2uiTempUTC)
		{
			if(ucUTCRcnt > 0)
			{
				ucUTCRcnt--;
			}
		}
	}

	if(!bOTD)
	{
		if(uiTempeMax > E2uiTempOTD)
		{
			if(++ucOTDcnt >= TEMPE_DELAY_CNT)
			{
				bOTD = 1;
				ucOTDcnt = 0;
				ucOTDRcnt = 0;
			}
		}
		else if(uiTempeMax < E2uiTempOTDR)
		{
			if(ucOTDcnt > 0)
			{
				ucOTDcnt--;
			}
		}
	}
	else
	{
		if(uiTempeMax < E2uiTempOTDR)
		{
			if(++ucOTDRcnt >= TEMPER_DELAY_CNT)
			{
				bOTD = 0;
				ucOTDcnt = 0;
				ucOTDRcnt = 0;
			}
		}
		else if(uiTempeMax > E2uiTempOTD)
		{
			if(ucOTDRcnt > 0)
			{
				ucOTDRcnt--;
			}
		}
	}

	if(!bUTD)
	{
		if(uiTempeMin < E2uiTempUTD)
		{
			if(++ucUTDcnt >= TEMPE_DELAY_CNT)
			{
				bUTD = 1;
				ucUTDcnt = 0;
				ucUTDRcnt = 0;
			}
		}
		else if(uiTempeMin > E2uiTempUTDR)
		{
			if(ucUTDcnt > 0)
			{
				ucUTDcnt--;
			}
		}
	}
	else
	{
		if(uiTempeMin > E2uiTempUTDR)
		{
			if(++ucUTDRcnt >= TEMPER_DELAY_CNT)
			{
				bUTD = 0;
				ucUTDcnt = 0;
				ucUTDRcnt = 0;
			}
		}
		else if(uiTempeMin < E2uiTempUTD)
		{
			if(ucUTDRcnt > 0)
			{
				ucUTDRcnt--;
			}
		}
	}
}


/*******************************************************************************
Function: ChkMosStatus(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ChkMosStatus(void)
{
    bCHGMOS = 1;
    bDSGMOS = 1;

	if(bAFE_OV || bCTO)												  
	{
		bCHGMOS = 0;
	}

 	if( bOTD || bUTD || bUV || bOCD || bAFE_SC || (bFD&&bDSGEnd) || bLoadConectFlg || bCTO)
	{
		bDSGMOS = 0;
		PWM2CON &= ~0x01;
		DSG1PWM = 0;
	}
	else
	{
		DSG1PWM = 1;
		if(ucDsgingSpeed != 2)
		{
			PWM2CON |= 0x01;
		}
	}

    if(!bDSGING)
    {
        if(bOTC || bUTC || bHV || bOCC || (bFC&&bCHGEnd))													
        {
            bCHGMOS = 0;
        }
    }
	if(bOCD || bAFE_SC || (bChkChgerFlg&&!bChgerConectFlg))
	{
        bCHGMOS = 0;
	}
}


/*******************************************************************************
Function: ControlMos(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ControlMos(void)
{
    if(bCHGMOS)
    {
        REG.AFESCONF2 |= 0x01;    
    }
    else
    {
        REG.AFESCONF2 &= ~0x01;    
    }

    if(bDSGMOS)
    {
        REG.AFESCONF2 |= 0x02;    
    }
    else
    {
        REG.AFESCONF2 &= ~0x02;    
    }
        
	if(REG.AFESCONF2 != AFESCONF2Bk)			//If the two variables of the same, is not written to AFE
	{
		AFESCONF2Bk = REG.AFESCONF2;
    	TwiWriteAFE(AFE_SCONF2, &REG.AFESCONF2);	 					
	}
}


/*******************************************************************************
Function: RecoveryOC(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void RecoveryOC(void)
{
	if(bOCRC_EN)
	{
		if(bOCD || bAFE_SC)
		{
			if(++uiOCDRcnt > OCDR_DELAY_CNT)
			{
                bChkLoadFlg = 0;
                ucLoadRCnt = 0;    
				uiOCDRcnt = 0;
				bOCD = 0;
                if(bAFE_SC)
                {
    				bAFE_SC = 0;
                    REG.AFESCONF1 |= 0x80;
                    TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
                    REG.AFESCONF1 &= ~0x80;
                    TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
                }
			}
		}
		
		if(bOCC)
		{			
			if(++uiOCCRcnt > OCCR_DELAY_CNT)
			{
				uiOCCRcnt = 0;
				bOCC = 0;

	            bChkChgerRFlg = 0;
				ucChgerRCnt = 0;
			}
		}
	}
}


/*******************************************************************************
Function: CheckLoad(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CheckLoad(void)
{
    if(!bChkLoadFlg)
    {
        if(bUV)
        {
            bLoadConectFlg = 1;
            bUVBkFlg = 1;
        }
        else if(bUVBkFlg && !bUV)
        {
			bUVBkFlg = 0;
            bChkLoadFlg = 1;
			ucLoadRCnt = 0;
    		REG.AFESCONF1 |= 0x02;
        	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				//enable Load Detect	
        }

        if(bOCD || bAFE_SC)
        {
            bChkLoadFlg = 1;
            bLoadConectFlg = 1;
			ucLoadRCnt = 0;
    		REG.AFESCONF1 |= 0x02;
        	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	//使能负载检测
        }
    }
    else
    {
    	TWIReadAFE(AFE_BSTATUS, &REG.AFEBSTATUS);
        if((REG.AFEBSTATUS&0x02) == 0)
        {
            if(++ucLoadRCnt >= (E2ucDelayLoadR*5-1))             //4*125mS
            {
                bChkLoadFlg = 0;
                bLoadConectFlg = 0;
				bChkChgerFlg = 0;
				bOCD = 0;
                ucLoadRCnt = 0;    
        		REG.AFESCONF1 &= ~0x02;
            	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				// close Load Detect
				if(bAFE_SC)
				{
					bAFE_SC = 0;
			        REG.AFESCONF1 |= 0x80;
			        TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
			        REG.AFESCONF1 &= ~0x80;
			        TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
				}
            }
        }
    }
}


/*******************************************************************************
Function: CheckCharger(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CheckCharger(void)
{
    if(bChkChgerFlg)
	{
    	TWIReadAFE(AFE_BSTATUS, &REG.AFEBSTATUS);
        if((REG.AFEBSTATUS&0x01) != 0)
        {
			if(++ucChgerCnt >= E2ucDelayLoadR*5)
			{
				bChkChgerFlg = 0;
                bChgerConectFlg = 1;
				ucChgerCnt = 0;
        		REG.AFESCONF1 &= ~0x01;
            	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				// close Charge detect				
			}
		}
	}

    if(bChkChgerRFlg)
    {
    	TWIReadAFE(AFE_BSTATUS, &REG.AFEBSTATUS);
        if((REG.AFEBSTATUS&0x01) == 0)
        {
            if(++ucChgerRCnt >= E2ucDelayLoadR*5)             //4*125mS
            {
                bChkChgerRFlg = 0;
				bOCC = 0;
                ucChgerRCnt = 0;    
        		REG.AFESCONF1 &= ~0x01;
            	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				// close Charge detect
            }
        }
	}
}


/*******************************************************************************
Function: VolProcess()
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/	
void VolProcess(void)
{
	if(!bBalancingFlg)
	{
	    if(!bFC)
	    {
	     	if((uiCellVmax>E2uiChgEndVol) && (Info.slCurr<=E2siChgEndCur))   //charge end voltage 
	    	{
	    		if(++ucChgEndcnt >= E2ucDelayChgEnd)
	    		{
	    			bFC = 1;
	    			ucChgEndcnt = 0;
	                ucChgEndRcnt = 0;
	    		}
	    	}
	        else
	        {
	    		if(ucChgEndcnt > 0)
	    		{
	    			ucChgEndcnt--;
	    		}
	        }
	    }
	    else
	    {
	    	if(uiCellVmin < E2uiChgEndVol) //charge end recover voltage
	    	{
	    		if(++ucChgEndRcnt >= E2ucDelayChgEnd)
	    		{
	    			bFC = 0;
	                ucChgEndcnt = 0;
	    			ucChgEndRcnt = 0;
	    		}
	    	}
	        else
	        {
	    		if(ucChgEndRcnt > 0)
	    		{
	    			ucChgEndRcnt--;
	    		}
	        }
	    }
	
	    if(!bFD)
	    {
	    	if(uiCellVmin<E2uiDsgEndVol)	  //discharge end voltage 
	    	{
	    		if(++ucDsgEndcnt >= E2ucDelayDsgEnd)
	    		{
	    			bFD = 1;
	    			ucDsgEndcnt = 0;
	                ucDsgEndRcnt = 0;
	    		}
	    	}
	        else
	        {
	    		if(ucDsgEndcnt > 0)
	    		{
	    			ucDsgEndcnt--;
	    		}
	        }
	    }
	    else
	    {
	    	if(uiCellVmin > E2uiDsgEndVol)	   //discharge end recover voltage
	    	{										  
	    		if(++ucDsgEndRcnt >= E2ucDelayDsgEnd)
	    		{
	    			bFD = 0;
	    			ucDsgEndcnt = 0;
	    			ucDsgEndRcnt = 0;
	    		}
	    	}
	        else
	        {
	    		if(ucDsgEndRcnt > 0)
	    		{
	    			ucDsgEndRcnt--;
	    		}
	        }
	    }
	}
}


/*******************************************************************************
Function: CurrProtect(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CurrProtect(void)
{
	if(!bOCC)
    {
		if(slCadcCurrent > E2slOCCvol)			   //CADC  cycle is 64ms
		{
            if(++ucOCCcnt > OCC_DELAY_CNT)
            {
                bOCC = 1;
                ucOCCcnt = 0;

	            bChkChgerRFlg = 1;
				ucChgerRCnt = 0;
	    		REG.AFESCONF1 |= 0x01;
	        	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				// close VADC
            }
		}
		else
		{
            if(ucOCCcnt > 0)
            {
    			ucOCCcnt--;	
            }
		}
    }

	if(!bOCD)
    {
		if(slCadcCurrent < E2slOCDvol)			   //CADC  cycle is 64ms
		{
            if(++ucOCDcnt > OCD_DELAY_CNT)
            {
                ucOCDcnt = 0;
                bOCD = 1;
            }
		}
		else
		{
            if(ucOCDcnt > 0)
            {
    			ucOCDcnt--;	
            }
		}
    }												 
}


/*******************************************************************************
Function: CurrProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CurrProcess(void)
{
	U8 i;
	S32 Tempdata=0;

	TWIReadAFE(AFE_CURH, (U8 xdata *)&AFE.siCurr);	//通过TWI读取CADC采集的电流值

	if((AFE.siCurr&0x1000) != 0)					//根据bit12判断是否为负数(放电电流为负值)，如为负值高位补0
	{
		AFE.siCurr|=0xE000;
	}
	slCadcCurrent = (S32)CALICUR*(AFE.siCurr-E2siCadcOffset)/E2siCadcGain;

	slCadcCurBuf[ucCadcCnt] = slCadcCurrent;		//对连续采集的16次电流取平均值，作为当前电流值
	if(++ucCadcCnt >= 16)
	{
		ucCadcCnt = 0;
	}
	for(i=0; i<16; i++)
	{
		Tempdata += slCadcCurBuf[i];
	}
	slCadcCurAverage = Tempdata/16;				
   
	bDSGING = 0;
	bCHGING = 0;
	if(slCadcCurAverage < (-E2siDfilterCur))
	{
		bDSGING = 1;
		UART_IRQ_DISABLE;
		Info.slCurr = slCadcCurAverage;
		UART_IRQ_ENABLE;
	}
	else if(slCadcCurAverage > E2siDfilterCur)
	{
		bCHGING = 1;	 	
		UART_IRQ_DISABLE;
		Info.slCurr = slCadcCurAverage;
		UART_IRQ_ENABLE;
	}
	else
	{
		UART_IRQ_DISABLE;
		Info.slCurr = 0;
		UART_IRQ_ENABLE;
	}

    if(bCHGING)						//debounce: flick led charging
    {
        if(!bLEDChgFlg)
        {
            if(++ucLedChgCnt > 8)
            {
                bLEDChgFlg = 1;
                ucLedChgCnt = 0;
            }
        }
        else
        {
            if(ucLedChgCnt > 0)
            {
                ucLedChgCnt--;
            }
        }
    }
    else
    {
        if(!bLEDChgFlg)
        {
            if(ucLedChgCnt > 0)
            {
                ucLedChgCnt--;
            }
        }
        else
        {
            if(++ucLedChgCnt > 8)
            {
                bLEDChgFlg = 0;
                ucLedChgCnt = 0;
            }
        }    
    }

	CurrProtect();
}


/*******************************************************************************
Function: AFERamCheck(void)
Description: 
Input:	 	
Output: 
Others:
*******************************************************************************/
void AFERamCheck(void)
{
	U8 xdata RdBuf[2];
	U8 i;

	for(i=3; i<=11; i=i+2)		//从可写寄存器03H开始比较
	{
		TWIReadAFE(i, RdBuf);

        if((RdBuf[0]!=*(&REG.AFEFLAG1+i)) || (RdBuf[1]!=*(&REG.AFEFLAG1+i+1)))
        {
			if(i != 7)
			{
	            InitAFE();		
	            break;
			}
        }
	}
}


/*******************************************************************************
Function: AlarmProcess(void)
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void AlarmProcess(void)
{
	TWIReadAFE(AFE_FLAG1, &REG.AFEFLAG1);	//读取AFE寄存器FLAG1 & FLAG2中的Alarm标志

	if((REG.AFEFLAG2&0x02) != 0)	//CADC 电流转换完成
	{
		bCADCFlg = 1;
	}

	if((REG.AFEFLAG2&0x01) != 0)	//VADC 电压转换完成
	{
		bVADCFlg = 1;
	}

	if((REG.AFEFLAG1&0x08) != 0)	//AFE 短路保护
	{
		bAFE_SC = 1;
		Info.uiPackStatus = uiPackStatus;
	}

	if((REG.AFEFLAG1&0x04) != 0)	//AFE 过压保护
	{
		bAFE_OV = 1;
		Info.uiPackStatus = uiPackStatus;
	}

	if((REG.AFEFLAG2&0x04) != 0)	//判断FLAG2的bit2是否为1，如为1则表示AFE发生过LVR，需要重新初始化AFE寄存器
	{
		InitAFE();
	}
}	
	

/*******************************************************************************
Function:WaitADCConvert(void) 
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
bit WaitADCConvert(void)
{
    U8 i;
    BOOL result=0;

    while(i++ < 60)
    {
        Delay1ms(5);
    	TWIReadAFE(AFE_FLAG1, &REG.AFEFLAG1);		//read AFE FLAG1 search for which state  trigged ALARM
    	if((REG.AFEFLAG2&0x01) != 0)				//VADC interrupt
    	{
			while(i++ < 60)
    		{
		        Delay1ms(5);
		    	TWIReadAFE(AFE_FLAG1, &REG.AFEFLAG1);		//read AFE FLAG1 search for which state  trigged ALARM
		    	if((REG.AFEFLAG2&0x02) != 0)				//CADC interrupt
		    	{
		    		result = 1;
		            break;
		    	}
    		}
            break;
    	}
    }

    return result;
}


/*******************************************************************************
Function: PorOnProtect(void)
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void PorOnProtect(void)
{
	if(uiCellVmax > E2uiOVvol)
	{		
		bHV = 1;
	}

	if(uiCellVmin < E2uiUVvol)
	{		
		bUV = 1;
	    bChkChgerFlg = 1;
	    bChgerConectFlg = 0;
		ucChgerCnt = 0;
		REG.AFESCONF1 |= 0x01;
		TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	 				//enable charger detect 
	}

	if(uiTempeMax > E2uiTempOTC)
	{
		bOTC = 1;
	}

	if(uiTempeMin < E2uiTempUTC)
	{
		bUTC = 1;
	}

	if(uiTempeMax > E2uiTempOTD)
	{
		bOTD = 1;
	}

	if(uiTempeMin < E2uiTempUTD)
	{
		bUTD = 1;
	}

    ChkMosStatus();				 

    ControlMos();
}


/*******************************************************************************
Function: ProtectProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ProtectProcess(void)
{
	if(!bBalancingFlg)
	{
		VolProtect();			
	}

	TempeProtect();			    

    ChkMosStatus();		

    ControlMos(); 

	Info.uiBatStatus = uiBatStatus;
	Info.uiPackStatus = uiPackStatus;

    RecoveryOC();

    CheckLoad();

    CheckCharger();

}


/*******************************************************************************
Function: IntoPowerDown(void)
Description:  
Input:	 	
Output: 
Others:	   FOR UART 
*******************************************************************************/
void IntoPowerDown(void)
{
	REG.AFESCONF10 = 0x33;						//进入Power Down模式
	TwiWriteAFE(AFE_SCONF10, &REG.AFESCONF10);
	REG.AFESCONF1 |= 0x20; 
	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
}

