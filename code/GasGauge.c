/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"
#include "GasGauge.h"


/*******************************************************************************
Function: GaugeManage(void)
Description: 
Input: 
Output: 
Others:
********************************************************************************/
void GaugeManage(void)
{
	U16 FccDelta;

	if(bCHGING | bAFE_SC | bOCC | bOCD)						//If the charge or discharge overcurrent
	{
		bVDQ = 0;
	}
	else
	{
		if(!bVDQ && (Info.ulRC>(Info.ulFCC-E2uiNearFCC)) && (uiTempeMin>E2uiLearnLowTemp))
		{
    		bVDQ = 1;
    		ulFCCCount = 0;
		}
	}

	if(bCHGING)										//charging 
	{
		uiRCCharge += slCadcCurAverage;					
		while(uiRCCharge >= VALUE_mAH)				
		{
			uiRCCharge -= VALUE_mAH;			
			if(Info.ulRC < Info.ulFCC)
			{
				UART_IRQ_DISABLE;
				Info.ulRC++;							//have charged 1mAh
				UART_IRQ_ENABLE;
			}
			else	  
			{
				UART_IRQ_DISABLE;
				Info.ulRC = Info.ulFCC;				
				UART_IRQ_ENABLE;			
				uiRCCharge = 0;
			}
		}
	}
	else if(bDSGING)													//discharging
	{
		uiRCDischarge += -slCadcCurAverage;
		if(uiRCDischarge >= VALUE_mAH)
		{
			while(uiRCDischarge >= VALUE_mAH)					
			{
				uiRCDischarge -= VALUE_mAH;
				ulDsgCycleCount++;							
				if(Info.ulRC > 0)
				{
					UART_IRQ_DISABLE;
					Info.ulRC--;
					UART_IRQ_ENABLE;
				}
				if(bVDQ)
				{
					ulFCCCount++;
				}
			}
			
			if(ulDsgCycleCount >= E2ulCycleThreshold)				
			{
				ulDsgCycleCount -= E2ulCycleThreshold;
				E2uiCycleCount++;
 			    Info.uiCycleCount = E2uiCycleCount;
				bWriteFlashFlg = 1;									//write E2uiCycleCount to flash flag
				ucWriteFlashCnt=0;
//		        UpEepromWithDelay();
			}
		}
	}
	
	if(Info.ulRC < Info.ulFCC)											//Calculate RSOC
	{
		UART_IRQ_DISABLE;
		Info.uiRSOC = (U32)Info.ulRC*100/Info.ulFCC;
		UART_IRQ_ENABLE;
	}
	else												
	{
		UART_IRQ_DISABLE;
		Info.uiRSOC = 100;
		UART_IRQ_ENABLE;
	}

	if(bFD)	//Discharge end
	{
		if(bVDQ)														        //E2ulFCC updata
		{
			FccDelta = (Info.ulFCC/10)*FCC_UPDATE_PERCENT;
			
			if(ulFCCCount > Info.ulFCC+FccDelta)
			{
				ulFCCCount = Info.ulFCC + FccDelta;
			}
			else if(ulFCCCount+FccDelta < Info.ulFCC)
			{
				ulFCCCount = Info.ulFCC - FccDelta;
			}
			UART_IRQ_DISABLE;
			Info.ulFCC = ulFCCCount;											//write E2ulFCC to flash
			UART_IRQ_ENABLE;
			E2ulFCC = ulFCCCount;
			bVDQ = 0;
    	    bWriteFlashFlg = 1;					//Updated calibration parameters, and written to the flash
    		ucWriteFlashCnt=0;
//	        UpEepromWithDelay();
		}


		UART_IRQ_DISABLE;
		if(Info.uiRSOC > 10)
		{
			Info.uiRSOC = 10;
		}
		Info.ulRC = Info.ulFCC*Info.uiRSOC/100;
		UART_IRQ_ENABLE;
	}
	else if(bFC)	//Charge end
	{
		UART_IRQ_DISABLE;
		Info.ulRC = Info.ulFCC;
		Info.uiRSOC = 100;
		UART_IRQ_ENABLE;
	}
	
	UART_IRQ_DISABLE;
	if(bUV)																			//OverVoltage Protect
	{
		Info.ulRC = 0;																
		Info.uiRSOC = 0;
	}
	else if(bHV)																	//UnderVoltage Protect
	{
		Info.ulRC = Info.ulFCC;
		Info.uiRSOC = 100;
	}
	UART_IRQ_ENABLE;
}


/*******************************************************************************
Function:InitGasGauge() 
Description: Calculate the remaining capacity according to pack voltage  
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
void InitGasGauge(void)
{
	U8 i;
	
	Info.uiRSOC = 100;
	for(i=0; i<10; i++)
	{
		if(Info.ulVoltage < E2uiVOC[i]*ucCellNum)
		{
			if(i == 0)
			{
				if(Info.ulVoltage < E2uiDsgEndVol*ucCellNum)
				{
					Info.uiRSOC = 0;	
				}
				else
				{
				 	Info.uiRSOC = (U32)(Info.ulVoltage-E2uiDsgEndVol*ucCellNum)*10/((E2uiVOC[0]-E2uiDsgEndVol)*ucCellNum);	
				}
				break;
			}
			else
			{
				Info.uiRSOC = 10*i + (U32)(Info.ulVoltage-E2uiVOC[i-1]*ucCellNum)*10/((E2uiVOC[i]-E2uiVOC[i-1])*ucCellNum);
				break;
			}
		}
	}

	Info.ulRC = E2ulFCC*Info.uiRSOC/100;
}

