/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"


void main(void)
{
	Initial();								//Initialize the system
	
	while(1)
	{
		RSTSTAT = 0x00;
	
		if((ucResetFlag==0x12) && bUartSndAckFlg)		//Software reset occurs, and ended UART communication
		{
			EA = 0;
			ResetInit();					//Reset MCU
		}

		if(bISPFlg && bUartSndAckFlg)
		{
			bISPFlg = 0;
			AFE_WDT_DISABLE;
			ISPProcess();
		}
		
		if(bWakeupFlg)						//The charger / load, keys, communication can wake up the system
		{
			bWakeupFlg = 0;
			WakeUpProcess();				//System to be awakened
		}

		if(bKeyFlg)							//timeinterrupt will dectect keyprocess(),  if detected effective key
		{
            bKeyFlg = 0;
			KeyProcess();
		}

		if(bAlarmFlg)
		{
		 	bAlarmFlg = 0;
			AlarmProcess();
		}

		if(bCADCFlg)
		{
			bCADCFlg = 0;
			CurrProcess();					//Calculate the current value and determines the state of charge and discharge
		}

		if(bVADCFlg)
		{			
            bVADCFlg = 0;
			BatteryInfoManage();		  	//Get battery voltage and temperature information

			BalManage();					//Process external voltage balance

			CellOpenProcess();

			BalProcess();
		}

		if(bCalibrationFlg)
		{
			bCalibrationFlg = 0;
			CaliProcess();					//PC calibration
		}

		if(bUpdataFlashFlg)
		{
			bUpdataFlashFlg = 0;
			FlashProcess();
		}

		if(bEnEEPRomBK && bE2PProcessFlg)
		{
			bE2PProcessFlg = 0;
			E2PRomBKProcess();
		}

		if(bTimer25msFlg)
		{
            bTimer25msFlg = 0;								  
 			ProtectProcess();			 	//Detection of battery charge and discharge cut-off voltage
        }

		if(bTimer1sFlg)						//timer is 1s
		{
			bTimer1sFlg = 0;

			RamCheckProcess();              //Detect the xdata block data			

			LEDPowerOff();					//When the LED display 4s, turn off the LED

			VolProcess();					//Detection of battery charge and discharge cut-off voltage

			GaugeManage();					//Calculate the battery charge and discharge capacity

			AFERamCheck();	                //Check AFE Register		

			WriteFlashCheck();
			
            if(bEnEEPRomBK)
            {
    			E2PRomBKCheck();			//Detecting whether to backup EEPRom
            }

			LowPowerCheck();				//Detecting whether to enter a low-power
				
		}
		
		LowPowerProcess();
	}
}