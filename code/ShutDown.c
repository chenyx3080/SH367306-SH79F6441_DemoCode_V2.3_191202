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


extern void InitClk(void);

/*******************************************************************************
Function: WakeUpProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void WakeUpProcess(void)
{
	bWakeupFlg = 0;
	if(bIdleFlg || bPDFlg)
	{
		InitClk();

		bPDFlg = 0;
		bIdleFlg = 0;
		ucIdleTimerCnt = 0;
		ucPDTimerCnt = 0;		 
		ucTimer3Cnt = 0;

		Delay1ms(1);
		ENTWI = 1;
		InitIRQ();

		REG.AFEINTEN = 0x6C;					//Enable SC, OV, CD
		TwiWriteAFE(AFE_INT_EN, &REG.AFEINTEN);
	
		REG.AFESCONF1 |= 0x10;					//Enable WDT
		TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
	}

		ucIdleTimerCnt = 0;
		ucPDTimerCnt = 0;
		bPCSleepFlg = 0;
		bIdleFlg = 0; 
		ucUartTimeoutCnt = 0;		
}


/*******************************************************************************
Function: SystemIntoPD(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void SystemIntoPD(void)
{	
	PWM2CON &= ~0x01;
	DSG1PWM = 0;
	
	bBLEOPEN = 0;
	IO_BLEPW = 1;
	
    IEN0 = 0x00;							//disable Interrupt
	IEN1 = 0x00;						
	LEDOff;								    //shut down LED

	IntoPowerDown();	
}


/*******************************************************************************
Function: SystemIntoIdle(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void SystemIntoIdle(void)    
{	
	REG.AFESCONF1 &= ~0x10;					//关闭WDT
	TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);

	REG.AFEINTEN = 0x70;					//开启SC,OV,CD的Alarm功能
	TwiWriteAFE(AFE_INT_EN, &REG.AFEINTEN);
	
	LEDOff;								//shut down LED
	bBLEOPEN = 0;
	IO_BLEPW = 1;
	PWM2CON &= ~0x01;
	if(bDSGMOS)
	{
		DSG1PWM = 1;
	}
	else
	{
		DSG1PWM = 0;
	}

	Delay1ms(1);
	ENTWI = 0;
	
	CLKCON &= ~0x04;					//Set sysclk 32kHz
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLKCON &= ~0x08;					//Close  sysclk 24MHz

	EA = 0;
	IEN0 = 0x00;
	IEN1 = 0x08;						//Enable INT4
	IENC = 0x20;						//Enable INT45
	IEN0 |= 0x01;						//INT0			  WAKEUP
	EA = 1;

	IntoPD();							//MCU into PD
}


/*******************************************************************************
Function: LowPowerCheck(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void LowPowerCheck(void)
{
	if(bPCSleepFlg && bUartSndAckFlg)
	{
		bPCSleepFlg = 0;
		bPDFlg = 1;		
	}
    else if(bCTO)
    {
		if(++ucPDTimerCnt >= E2ucDeleyLowPower)
		{
			ucPDTimerCnt = E2ucDeleyLowPower;
			bPDFlg = 1;		
		}
    }
	else if(!bLEDOpen)					//LED display off and then wait to enter a low-power
	{
		if(!bCHGING && !bDSGING)
		{
			if(bUV)
			{
				if(++ucPDTimerCnt >= E2ucDeleyLowPower)
				{
					ucPDTimerCnt = E2ucDeleyLowPower;
					bPDFlg = 1;		
				}
			}
			else
			{
                ucPDTimerCnt = 0;
                if(!(bOTC | bUTC | bHV | bOCC | bOTD | bUTD | bUV | bOCD | bAFE_SC | bBLEOPEN))
                {
    				if(++ucIdleTimerCnt >= E2ucDeleyLowPower)
    				{
    					ucIdleTimerCnt = E2ucDeleyLowPower;
    					bIdleFlg = 1;		
    				}
                }
                else
                {
                    ucIdleTimerCnt = 0;
                }
			}
		}
		else
		{
			ucIdleTimerCnt = 0;
			ucPDTimerCnt = 0;
		}
	}
	else
	{
		ucIdleTimerCnt = 0;
		ucPDTimerCnt = 0;
	}
}


/*******************************************************************************
Function: LowPowerProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void LowPowerProcess(void)
{
	if(!bIdleFlg && !bPDFlg)
	{
		EA = 0;
		if(!(bKeyFlg | bAlarmFlg | bCADCFlg | bCalibrationFlg | bUpdataFlashFlg | bWakeupFlg | bISPFlg | bVADCFlg | bTimer1sFlg) && (ucResetFlag!=0x12))
		{
			EA = 1;
			IntoIdle();
		}
		EA = 1;	 	
	}
	else if(bPDFlg)
	{
		SystemIntoPD();
	}
	else if(bIdleFlg)
	{
		SystemIntoIdle();
	}
}


