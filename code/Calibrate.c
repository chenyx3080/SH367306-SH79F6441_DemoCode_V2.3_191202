/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"
#include "ExtE2PRomRTC.h"
#include "Calibrate.h"


/*******************************************************************************
Function: CaliVoltageSub(void)
Description:  Calibration of the total voltage, Update "E2uiVPackGain"
Input:
Output: 
Others:
*******************************************************************************/
bit CaliVoltageSub(void)
{
	U8 i;
	U16 VPackTemp = 0;
	BOOL result = 0;
		
	for(i=ucCellNumOffset; i<(ucCellNumOffset+ucCellNum); i++)
	{
		result = TWIReadAFE(AFE_CELL1H+2*i,(U8 xdata *)(&AFE.uiCell[0+i]));
		VPackTemp += AFE.uiCell[i];											 
	}
	if(result)
	{
		E2uiVPackGain = (U32)CALIPACKVOL*VPackTemp/ulExtVPack;					   //not really gain  really gain=3800/VpackGain
	}
	
	return  result;
}


/*******************************************************************************
Function: CaliCurrentSub(void)
Description:  Calibration current, update current gain"E2siCadcGain"
Input:
Output: 
Others:
*******************************************************************************/
bit CaliCurrentSub(void)
{
    S16 xdata TempCur1,TempCur2,TempGain;
	BOOL result = 0;

	result = TWIReadAFE(AFE_CURH,(U8 xdata *)&TempCur1);
    Delay1ms(80);
	result = TWIReadAFE(AFE_CURH,(U8 xdata *)&TempCur2);

	if(result)
	{
	    AFE.siCurr = (TempCur1+TempCur2)/2;
		if((AFE.siCurr&0x1000) != 0)									  //must turn the REG to data of S16
		{
			AFE.siCurr |= 0xE000;
		}
	
		TempGain = (S32)CALICUR*(AFE.siCurr-E2siCadcOffset)/slExtCur;		    
		if(TempGain != 0)
		{
		  E2siCadcGain = TempGain;
		}
	}
	
	return  result;
}


/*******************************************************************************
Function: CaliCurOffsetSub(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
bit CaliCurOffsetSub(void)
{
    S16 xdata TempCur1,TempCur2;
	BOOL result = 0;

	result = TWIReadAFE(AFE_CURH,(U8 xdata *)&TempCur1);
    Delay1ms(80);
	result = TWIReadAFE(AFE_CURH,(U8 xdata *)&TempCur2);

	if(result)
	{
		if((TempCur1&0x1000) != 0)									  //must turn the REG to data of S16
		{
			TempCur1 |= 0xE000;
		}
		if((TempCur2&0x1000) != 0)									  //must turn the REG to data of S16
		{
			TempCur2 |= 0xE000;
		}
	    AFE.siCurr = (TempCur1+TempCur2)/2;
	    E2siCadcOffset = AFE.siCurr;
	}
	
	return  result;
}


/*******************************************************************************
Function: CaliTS1Sub(void)
Description:  Calibration temperature, update temperature offset
Input: 
Output: 
Others:
*******************************************************************************/
bit CaliTS1Sub(void)
{
	S16 Tempe;
	BOOL result = 0;	
	
	result = TWIReadAFE(AFE_TS1H,(U8 xdata *)&AFE.uiTS1);

	if(result)
	{
		Tempe = uiExtTemp1-CalcuTemp(AFE.uiTS1);

		if(((Tempe-E2siTS1Offset)<150) && ((Tempe-E2siTS1Offset)>-150))
		{
		 	E2siTS1Offset = Tempe;
		}

	}
	
	return  result;
}


/*******************************************************************************
Function: CaliTS2Sub(void)
Description:  Calibration temperature, update temperature offset
Input: 
Output: 
Others:
*******************************************************************************/
bit CaliTS2Sub(void)
{
	S16 Tempe;
	BOOL result = 0;	

	result = TWIReadAFE(AFE_TS2H,(U8 xdata *)&AFE.uiTS2);

	if(result)
	{
		Tempe = uiExtTemp2-CalcuTemp(AFE.uiTS2);
	
		if(((Tempe-E2siTS2Offset)<150) && ((Tempe-E2siTS2Offset)>-150))
		{
		 	E2siTS2Offset = Tempe;
		}
	}

	return  result;
}


/*******************************************************************************
Function: CaliRTCTime(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
bit CaliRTCTime(void)
{
	BOOL result = 0;

	RTC.Year = ucExtRTC[5];
	RTC.Month = ucExtRTC[4];
	RTC.Date = ucExtRTC[3];
	RTC.Hour = ucExtRTC[2];
	RTC.Minute = ucExtRTC[1];
	RTC.Second = ucExtRTC[0];
	
	result = RTCModifyTime();
	
	bE2PProcessFlg = 1;
	bE2PBKRtc = 1;

	return  result;
}


/*******************************************************************************
Function: CaliProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CaliProcess(void)
{
	BOOL result = 1;

	if((ucExtcaliSwitch1 & 0x01) != 0)					//Calibration of the total voltage
	{
		if(!CaliVoltageSub())
		{
			result = 0;
		}
		else
		{
			ucExtcaliFlag |= 0x03;
		}
	}
	
	if((ucExtcaliSwitch1 & 0x04) != 0)					//Calibration TS1					
	{
		if(!CaliTS1Sub())
		{
			result = 0;
		}
		else
		{
			ucExtcaliFlag |= 0x04;
		}
	}
	
	if((ucExtcaliSwitch1 & 0x08) != 0)					//Calibration TS2
	{
		if(!CaliTS2Sub())
		{
			result = 0;
		}
		else
		{
			ucExtcaliFlag |= 0x08;
		}
	}
	
	if((ucExtcaliSwitch1 & 0x10) != 0)					//Calibration current
	{
		if(!CaliCurrentSub())
		{
			result = 0;
		}
		else
		{
			ucExtcaliFlag |= 0x10;
		}
	}
	
	if((ucExtcaliSwitch1 & 0x20) != 0)					//Calibration CADC Current offset
	{
		if(!CaliCurOffsetSub())
		{
			result = 0;
		}
		else
		{
			ucExtcaliFlag |= 0x20;
		}
	}	

//	if(ucExtcaliFlag == 0x3f)
//	{
//		ucExtcaliFlag = 0;
//		bCAL = 1;
//	    bUpdataFlashFlg = 1;
//	}
//    else
//    {
//	    bWriteFlashFlg = 1;					//Updated calibration parameters, and written to the flash
//		ucWriteFlashCnt=0;
//    }
//	ucExtcaliSwitch1 = 0;	

	if((ucExtcaliSwitch1 & 0x80) != 0)					//Calibration RTC
	{
		if(!CaliRTCTime())
		{
			result = 0;
		}
		else
		{
	    	ucExtcaliFlag |= 0x80;
		}
	}
	
	if(bEnEEPRomBK)
	{
		if(ucExtcaliFlag == 0xBF)
		{
			goto CaliAllOk;
		}
	}
	else if(ucExtcaliFlag == 0x3f)
	{
CaliAllOk:
		ucExtcaliFlag = 0;
		bCAL = 1;
		E2ucCalibrated = CALI_FLAG;
		bUpdataFlashFlg = 1;
	}
	
	ucExtcaliSwitch1 = 0;
	bWriteFlashFlg = 1;					//Updated calibration parameters, and written to the flash
//    UpEepromWithDelay();

    if(result)
    {
    	UART_SEND_ACK;
    }
    else
    {
    	UART_SEND_NACK;
    }    
}




