/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/08/28		 Preliminary
********************************************************************************/
#include "System.h"
#include "ExtE2PRomRTC.h"


/*******************************************************************************
Function: RTCWrite(U8 WrAddr, U8 Length, U8 xdata *WrBuf)
Description: 
Input: 
Output: 
Others:
********************************************************************************/
bit RTCWrite(U8 WrAddr, U8 Length, U8 xdata *WrBuf)
{
 	BOOL result=1;

	if(!TwiWrite(RTC_ID, WrAddr, Length, WrBuf))
	{
		result = TwiWrite(RTC_ID, WrAddr, Length, WrBuf);
	}

	return result;
}


/*******************************************************************************
Function: RTCRead(U8 RdAddr, U8 Length, U8 xdata *RdBuf)
Description: 
Input: 
Output: 
Others:
********************************************************************************/
bit RTCRead(U8 RdAddr, U8 Length, U8 xdata *RdBuf)
{
 	BOOL result=1;
	
	if(!TwiRead(RTC_ID, RdAddr, Length, RdBuf))
	{
		result = TwiRead(RTC_ID, RdAddr, Length, RdBuf);
	}

	return result;
}


/*******************************************************************************
Function: RTCReadTime(void)
Description: 
Input: 
Output: 
Others:
********************************************************************************/
bit RTCReadTime(void)
{
	U8 xdata rtcbuf[9];
	BOOL result = 0;
	
	if(RTCRead(0x00, 9, &rtcbuf))
	{
		if((rtcbuf[7]&0x01) == 0x00)			//judge RTCF bit
		{
			RTC.Second = rtcbuf[0];
			RTC.Minute = rtcbuf[1];
			RTC.Hour = rtcbuf[2]&0x1F;
			RTC.Date = rtcbuf[3];
			RTC.Month = rtcbuf[4];
			RTC.Year = rtcbuf[5];
			RTC.Week = rtcbuf[6];
			result = 1;
		}
		else
		{
			rtcbuf[0] = RTC.Second;
			rtcbuf[1] = RTC.Minute;
			rtcbuf[2] = RTC.Hour|0x80;
			rtcbuf[3] = RTC.Date;
			rtcbuf[4] = RTC.Month;
			rtcbuf[5] = RTC.Year;
			rtcbuf[6] = RTC.Week;
			rtcbuf[7] = 0x90;
			rtcbuf[8] = 0x00;
			RTCWrite(0x00, 9, &rtcbuf);			
		}
	}

	return result;
}


/*******************************************************************************
Function: RTCModifyTime()
Description: modify RTC time, include year, month, date, week, hour, minute, second
Input: RTC
Output:
********************************************************************************/
bit RTCModifyTime(void)
{
	BOOL result = 0;
	U8 xdata rtcdata;
	U8 xdata rtctemp[7];
	
	rtcdata = 0x90;
	result = RTCWrite(RTC_REG_STATUS, 1, &rtcdata);
	
	rtctemp[0] = RTC.Second;
	rtctemp[1] = RTC.Minute;
	rtctemp[2] = RTC.Hour|0x80;
	rtctemp[3] = RTC.Date;
	rtctemp[4] = RTC.Month;
	rtctemp[5] = RTC.Year;
	rtctemp[6] = RTC.Week;		 		

	result = RTCWrite(RTC_REG_SECOND, 7, (U8 xdata *)&rtctemp);

	return  result;
}


/*******************************************************************************
Function: RTCInit()
Description: init rtc hardware
Input: Null
Output: 
Others:
********************************************************************************/
void InitRTC(void)
{
	U8 xdata rtcbuf[7];
	U8 i, checksum=0;
	U8 xdata rtcdata1;
	U8 xdata rtcbuf2[8];
    
	if(!bEnEEPRomBK)
    {
        bE2RTCON = 0;
    }
    else if(!bE2RTCON)
    {
        bE2RTCON = 1;
		
		MemorySet(rtcbuf, 0, sizeof(rtcbuf));		//clr rtcbuf[]
		MemorySet(rtcbuf2, 0, sizeof(rtcbuf2));		//clr rtcbuf2[]

		E2PRomRead(E2PROM_RTC_ADDR, 8, rtcbuf2);		//Read the backup RTC time in the EEPROM
		for(i=0; i<6; i++)
		{
			checksum += rtcbuf2[i];
		}
		
		if((rtcbuf2[6]!=checksum) || (rtcbuf2[7]!=0x5a))			//If there is no RTC backup, set the default RTC Time: 2015/03/06/12:00:00
		{
			rtcbuf[0] = 0x00;			//second
			rtcbuf[1] = 0x00;			//minute
			rtcbuf[2] = 0x12;			//hour
			rtcbuf[3] = 0x05;			//week
			rtcbuf[4] = 0x15;			//date
			rtcbuf[5] = 0x03;			//month
			rtcbuf[6] = 0x19;			//year
		}
		else
		{
			rtcbuf[0] = rtcbuf2[0];		//second
			rtcbuf[1] = rtcbuf2[1];		//minute
			rtcbuf[2] = rtcbuf2[2];		//hour
			rtcbuf[3] = 0x05;			//week
			rtcbuf[4] = rtcbuf2[3];		//date
			rtcbuf[5] = rtcbuf2[4];		//month
			rtcbuf[6] = rtcbuf2[5];		//year		
		}

		MemoryCopy(rtcbuf, (U8 xdata *)&RTC, 7);

		rtcbuf[0] = RTC.Second;
		rtcbuf[1] = RTC.Minute;
		rtcbuf[2] = RTC.Hour|0x80;
		rtcbuf[3] = RTC.Date;
		rtcbuf[4] = RTC.Month;
		rtcbuf[5] = RTC.Year;
		rtcbuf[6] = RTC.Week;

		rtcdata1 = 0x90;
		RTCWrite(RTC_REG_STATUS, 1, &rtcdata1);
		rtcdata1 = 0x01;
		RTCWrite(RTC_REG_WEEK, 1, &rtcdata1);

		if(RTCReadTime())
		{
			RTCWrite(0x00, 7, (U8 xdata *)&rtcbuf);
		}
	}
}

