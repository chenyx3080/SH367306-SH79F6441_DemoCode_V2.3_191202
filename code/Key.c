/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2017/04/01
History:   	Sino
********************************************************************************/
/* ****************************************************************************************************/
#include "system.h"


extern void IntoPowerDown(void);

/*******************************************************************************
Function: ScanKey(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ScanKey(void)
{
	RSTSTAT = 0x00;
	if(!bKeyFlg)
	{
		ucKeyValueBK = KEYVAL_NULL;
		if(!KEY_ON_IO)
		{
			ucKeyValueBK = KEY_ON;
		}
        else if(!KEY_LED_IO)
        {
			ucKeyValueBK = KEY_LED;
        }
		
		if(ucKeyValueBK != ucKeyOldValue)
		{
			ucKeyInvalidCnt++;
			if(ucKeyValidCnt >= KEY_S_TIME)							  
			{
				if(ucKeyInvalidCnt >= KEY_S_TIME)						  
				{
					if(ucKeyValidCnt >= KEY_L_TIME)					  
					{
						ucKeyValue = ucKeyOldValue | (KEY_STATE_LE<<4);	  
					}
					else
					{
						ucKeyValue = ucKeyOldValue | (KEY_STATE_S<<4);	  
					}
					bKeyFlg = 1;
					goto scanend;
				}
				else
				{
					ucKeyValidCnt++;
				}
			}
			else
			{
				goto scanend;
			}
		}
		else
		{
			if(ucKeyValueBK != KEYVAL_NULL)
			{
				ucKeyInvalidCnt = 0;
				ucKeyValidCnt++;
				if(ucKeyValidCnt == KEY_L_TIME)
				{
					ucKeyValue = ucKeyOldValue | (KEY_STATE_L<<4);
					bKeyFlg = 1;
				}
				else if(ucKeyValidCnt == KEY_LC_TIME)
				{
					ucKeyValidCnt = KEY_L_TIME;
					ucKeyValue = ucKeyOldValue | (KEY_STATE_LC<<4);
					bKeyFlg = 1;
				}
			}
			else
			{
				ucKeyValue = KEYVAL_NULL;
scanend:
				ucKeyValidCnt = 0;		//clr count and update key old value
				ucKeyInvalidCnt = 0;
				ucKeyOldValue = ucKeyValueBK;
			}
		}
	}
}

/*******************************************************************************
Function: ProcessKeySpeed(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ProcessKeySpeed(void)
{
	bSlowDischarge = 0;
    bMidDischarge = 0;
	bFastDischarge = 0;

	if(ucDsgingSpeed == 0)
	{
		ucDsgingSpeed = 1;
		bMidDischarge = 1;
		PWM2DL = (U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioH/100;
		PWM2DH = ((U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioH/100) >> 8;
	}
	else if(ucDsgingSpeed == 1)
	{
		ucDsgingSpeed = 2;
		bFastDischarge = 1;
		DSG1PWM = 1;
		PWM2CON &= ~0x01;
	}
	else
	{
		ucDsgingSpeed = 0;
		bSlowDischarge = 1;
		PWM2DL = (U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioL/100;
		PWM2DH = ((U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioL/100) >> 8;
	}

	Info.uiPackStatus = uiPackStatus;
}


/*******************************************************************************
Function: KeyProcess(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void KeyProcess(void)
{    	
    switch(ucKeyValue)
	{
		case KEY_ON_S:
            ProcessKeySpeed();
        break;

		case KEY_LED_S:
			if(!bLEDOpen)
			{
    			bLEDOpen = 1;
    			ucLEDTimeCnt = 0;
    			LEDPowerOn();					//By LED displays battery capacity
			}
            else
            {
                ucLEDTimeCnt = 0;
            }
        break;

		case KEY_LED_L:
            EA = 0;
            IntoPowerDown();
            Delay1ms(10);
            ucResetFlag = 0x12;
            ((void(code*)(void))0x0000)();                         //jump to addr:0x0000				
        break;

		case KEY_ON_L:
			bBLEOPEN = ~bBLEOPEN;
			IO_BLEPW = ~bBLEOPEN;		//长按2S蓝牙电源开启/关闭			
        break;

        default:
        break;
    }
}


