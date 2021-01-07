/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "System.h"


/*******************************************************************************
Function: LEDPowerOn(), LEDPowerOff()
Description:  By LED displays battery capacity, long display time 4s
	bLEDNum1,0: The total number of LED
	Info.uiRSOC:   The percentage of remaining capacity
Input:
Output: 
Others:
*******************************************************************************/
void LEDPowerOn(void)
{	
	if(!bLEDNum1 && bLEDNum0)					//3'LED
	{
		if(Info.uiRSOC > 60)
		{
			LEDOn3;
		}
		else if(Info.uiRSOC > 20)
		{
			LEDOn2;
		}
		else if(Info.uiRSOC > 0)
		{
			LEDOn1;
		}
		else
		{
			LEDOff;
		}
	}
	else if(bLEDNum1 && !bLEDNum0)			//4'LED
	{
		if(Info.uiRSOC > 75)
		{
			LEDOn4;
		}
		else if(Info.uiRSOC > 50)
		{
			LEDOn3;
		}
		else if(Info.uiRSOC > 25)
		{
			LEDOn2;
		}
		else if(Info.uiRSOC > 0)
		{
			LEDOn1;
		}
		else
		{
			LEDOff;
		}
	}
	else if(bLEDNum1 && bLEDNum0)			//5'LED
	{
		if(Info.uiRSOC > 80)
		{
			LEDOn5;
		}
		else if(Info.uiRSOC > 60)
		{
			LEDOn4;
		}
		else if(Info.uiRSOC > 40)
		{
			LEDOn3;
		}
		else if(Info.uiRSOC > 20)
		{
			LEDOn2;
		}
		else if(Info.uiRSOC > 0)
		{
			LEDOn1;
		}
		else
		{
			LEDOff;
		}
	}
}

void LEDPowerOff(void)
{
	if(bLEDOpen)						//LED display time counting
	{
		if(++ucLEDTimeCnt >= 4)
		{
			ucLEDTimeCnt = 0;
			bLEDOpen = 0;
			LEDOff;
		}
	}
}

