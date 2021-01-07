/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2018/08/30
History:
	V0.0		2018/08/30		 Preliminary
********************************************************************************/

#include "System.h"
#include "ExtE2PRomRTC.h"


#ifdef TWI_IO_OPERATE
/*******************************************************************************
Function: CRC8Table[]
Description:
Input:
Output:
Others:
*******************************************************************************/
U8 code CRC8Table[]=
{							//120424-1			CRC Table
	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
	0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
	0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
	0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
	0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
	0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
	0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
	0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
	0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
	0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
	0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
	0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
	0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
	0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
	0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
	0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
};

/*******************************************************************************
Function: Delay4us()
Description: 
Input:
Output:
Others:
*******************************************************************************/
void Delay4us(void)
{
	U8 i;
	for(i=0; i<13; i++)
	{
	}
}

/*******************************************************************************
Function:
1. TwiStart()		
2. TwiReStart()
3. TwiStop()
Input: 
Output:
********************************************************************************/
void TwiStart(void)
{
    TWI_DAT_OUT;
	TWI_CLK_OUT;
    
	TWI_DAT_HIGH;
	TWI_CLK_HIGH;
	TWI_DAT_OUT;
	TWI_CLK_OUT;
	TWI_DAT_LOW;
	Delay4us();
	TWI_CLK_LOW;
}

void TwiReStart(void)
{
	TWI_DAT_HIGH;
	TWI_CLK_HIGH;
	Delay4us();
	TWI_DAT_LOW;
	Delay4us();
	TWI_CLK_LOW;
}

void TwiStop(void)
{
	TWI_DAT_OUT;
	TWI_DAT_LOW;
	Delay4us();
	TWI_CLK_HIGH;
	Delay4us();
	TWI_DAT_HIGH;
	Delay4us();
	TWI_DAT_IN;
	TWI_CLK_IN;
}

bit TwiChkClkRelease(void)
{
	U16 TimeoutCnt=1000;				//If Clock is not released within 4ms, is considered overtime
	BOOL result=0;

	TWI_CLK_IN;
	while(TimeoutCnt--)
	{
		RSTSTAT = 0x00;
		Delay4us();
		if(TWI_RD_CLK)
		{
			result = 1;
			break;
		}
	}

	TWI_CLK_HIGH;
	TWI_CLK_OUT;
	
	return result;
}


/*******************************************************************************
Function: TwiSendData()
Description: 
Input: 
Output:
********************************************************************************/

bit TwiSendData(U8 Data, U8 ClkFlg)
{
	U8 i;
	BOOL result=0;

//1. After sending the Start signal, there is no need to detect Clock is released, And sending the first bit
	if(Data&0x80)
	{
		TWI_DAT_HIGH;
	}
	else
	{
		TWI_DAT_LOW;
	}
	if(ClkFlg == 1)
	{
		Delay4us();
		if(TwiChkClkRelease())
		{
			TWI_CLK_LOW;
		}
		else
		{
			return result;
		}
	}
	else
	{
		Delay4us();
		TWI_CLK_HIGH;
		Delay4us();
		TWI_CLK_LOW;
	}
	
//2. Send the remaining seven bit
	Data = Data<<1;
	for(i=0; i<7; i++)
	{
		if(Data&0x80)
		{
			TWI_DAT_HIGH;
		}
		else
		{
			TWI_DAT_LOW;
		}
		Data = Data<<1;
		Delay4us();
		TWI_CLK_HIGH;
		Delay4us();
		TWI_CLK_LOW;
	}
	TWI_DAT_IN;
	Delay4us();
	
	for(i=0; i<10; i++)
	{
		if(TWI_RD_DAT == 0)
		{
			result = 1;
			break;
		}
	}
	TWI_CLK_HIGH;

	Delay4us();
	TWI_DAT_LOW;
	TWI_DAT_OUT;
	TWI_CLK_LOW;
	Delay4us();
	
	return result;
}


/*******************************************************************************
Function: TwiGetData()
Description: i2c get data(one byte)
Input: 		R6: 0 means no need send ack
Output:	A: the data received
********************************************************************************/
U8 TwiGetData(U8 AckFlg)
{
	U8 i, RdData=0;
	
	TWI_DAT_IN;
	Delay4us();

	for(i=0; i<8; i++)
	{
		TWI_CLK_HIGH;
		Delay4us();
		if(TWI_RD_DAT)
		{
			RdData |= (1<<(7-i));
		}
		TWI_CLK_LOW;
		Delay4us();
	}

	TWI_DAT_OUT;
	if(AckFlg != 0)
	{
		TWI_DAT_LOW;
	}
	else
	{
		TWI_DAT_HIGH;
	}
	TWI_CLK_HIGH;
	Delay4us();
	TWI_CLK_LOW;
	Delay4us();
	
	return RdData;
}


/*******************************************************************************
Function: CRC8cal()
Description: 
Input: 
Output:
********************************************************************************/
U8 CRC8cal(U8 *p, U8 Length)    		   //look-up table calculte CRC 
{    
    U8 crc8 = 0;    
    
	for(; Length > 0; Length--)
	{
		RSTSTAT = 0x00;		
        crc8 = CRC8Table[crc8^*p];    
	    p++;    
    } 
       
    return(crc8);       
}


/*******************************************************************************
Function: TWIWrite()
Description:  write one byte
Input: SlaveID--Slave Address
          RegAddr--register addr
          RegData--register data 
Output: CY:1--OK
                  0--Error
********************************************************************************/
bit TwiWrite(U8 SlaveID, U16 WrAddr, U8 Length, U8 xdata *WrBuf)
{
	U8 i;
    U8 TempBuf[4];
	BOOL result = 0;

    TempBuf[0] = SlaveID;
    TempBuf[1] = (U8)WrAddr;
    TempBuf[2] = *WrBuf;
    TempBuf[3] = CRC8cal(TempBuf, 3);
	
	EA = 0;
	if(Length > 0)
	{
		TwiStart();
		
		if(!TwiSendData(SlaveID, 1))			//Send Slave E2ucID
		{
			goto WrErr;
		}
		
		if(SlaveID == E2PROM_ID)
		{
			if(!TwiSendData(WrAddr>>8, 0))		//Send Write Address(High 8bit) For EEPROM
			{
				goto WrErr;
			}
		}
		if(TwiSendData(WrAddr, 0))					//Send Write Address(Low 8bit)
		{
			result = 1;
			for(i=0; i<Length; i++)
			{
				RSTSTAT = 0x00;
				if(TwiSendData(*WrBuf, 0))			//Send Write Data
				{
					WrBuf++;
				}
				else
				{
					result = 0;
					break;
				}
			}

            if(SlaveID == AFE_CHIP_ID)
            {
                if(!TwiSendData(TempBuf[3], 0))            //write CRC
                {
                    result = 0;
                }
            }
		}
WrErr:
		TwiStop();
	}
	EA =1;
	
	return result;
}


/*******************************************************************************
Function: TWIRead()
Description:read rtc register
Input:   RdAddr--register addr
            Lenth   --read data length
            RdBuf   --data buffer
Output: 
Others:
********************************************************************************/
bit TwiRead(U8 SlaveID, U16 RdAddr, U8 Length, U8 xdata *RdBuf)
{
	U8 i;
	BOOL result=0;
    U8 xdata TempBuf[46];
    U8 RdCrc=0;

    TempBuf[0] = SlaveID;
    TempBuf[1] = (U8)RdAddr;
//    TempBuf[2] = Length;
    TempBuf[2] = SlaveID | 0x01;
	
	EA = 0;
	if(Length > 0)
	{
		TwiStart();
		
		if(!TwiSendData(SlaveID, 1))			//Send Slave E2ucID
		{
			goto RdErr;
		}
		
		if(SlaveID == E2PROM_ID)
		{
			if(!TwiSendData(RdAddr>>8, 0))		//Send Read Address(High 8bit) For EEPROM
			{
				goto RdErr;
			}
		}
		if(!TwiSendData(RdAddr, 0))				//Send Read Address(Low 8bit)
		{
			goto RdErr;
		}

//        if(SlaveID==AFE_CHIP_ID)          //CRC
//        {
//            if(!TwiSendData(Length, 0))
//            {
//                goto RdErr;
//            }
//        }
		
		TwiReStart();
		
		if(TwiSendData(SlaveID|0x1, 0))			//Send Slave E2ucID
		{
			result = 1;
            if(SlaveID==AFE_CHIP_ID)
            {
    			for(i=0; i<Length+1; i++)
    			{
            		if(i == Length)
            		{
                        RdCrc = TwiGetData(0);      //Get Data
            		}
            		else
            		{
                        TempBuf[3+i] = TwiGetData(1);     //Get Data
            		}
    			}

                if(RdCrc != CRC8cal(TempBuf, 3+Length))
                {
                    result = 0;    
                }
                else
                {
                    for(i=0; i<Length; i++)
                    {
                        *RdBuf = TempBuf[3+i];
                        RdBuf++;   
                    }
                }
            }
            else
            {
                for(i=0; i<Length; i++)
                {
					RSTSTAT = 0x00;
        			*RdBuf = TwiGetData(Length-i-1);//Get Data
                    RdBuf++;
                }
            }
		}
	
RdErr:
		TwiStop();
	}
	EA = 1;
	return result;
}


void InitTwi(void)
{
	
}
#endif


