/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2019/03/13
History:
	V0.0		2019/03/13		 Preliminary
********************************************************************************/

#include "System.h"
#include "ExtE2PRomRTC.h"


#ifdef TWI_MODULE_OPERATE

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
Function:
TWICheckStatus()
Input: 
Output:
********************************************************************************/
bit TWICheckStatus(U8 Status)
{
	BOOL result = 1;
    U16 timeoutcount = 48000;

	while((TWICON&0x08)==0)             //等待TWI通讯结束
    {
		RSTSTAT = 0x00;
        if(timeoutcount)
        {
            timeoutcount--;
        }
        else
        {
            break;
        }
    }
	if((TWISTA&0xf8) != Status)
	{
		result = 0;                     //Error
	}
	
	return result;
}


/*******************************************************************************
Function: CRC8cal()
Description:
Input: 
Output: 
********************************************************************************/
U8 CRC8cal(U8 *p, U8 counter)    		   //look-up table calculte CRC 
{    
    U8 crc8 = 0;    
    
	for( ; counter > 0; counter--)
	{
		RSTSTAT = 0x00;		
		crc8 = CRC8Table[crc8^*p];    
	    p++;    
    }    
    return(crc8);    
}   


/*******************************************************************************
Function: TwiWrite()
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
	BOOL result = 1;
	U16 timeoutcount = 48000;
	
    TempBuf[0] = SlaveID;
    TempBuf[1] = (U8)WrAddr;
    TempBuf[2] = *WrBuf;
    TempBuf[3] = CRC8cal(TempBuf, 3);

	if(Length > 0)
	{
		HTimeoutChk();
		TWICON = 0x60;					//Start
		if((!TWICheckStatus(0x08))&&(!TWICheckStatus(0x10)))
		{
			result = 0;
			goto WrErr;
		}
		
		TWIDAT = SlaveID;				//Slave地址
		TWICON = 0x40;
		if(!TWICheckStatus(0x18))
		{
			result = 0;
			goto WrErr;
		}
		
		if(SlaveID == E2PROM_ID)
		{
			TWIDAT = (U8)(WrAddr>>8);	//写寄存器高字节地址-仅针对外挂EEPROM
			TWICON = 0x40;
			if(!TWICheckStatus(0x28))
			{
				result = 0;
				goto WrErr;
			}
		}

		TWIDAT = (U8)WrAddr;			//写寄存器地址
		TWICON = 0x40;
		if(!TWICheckStatus(0x28))
		{
			result = 0;
			goto WrErr;
		}
		
		if(SlaveID == AFE_CHIP_ID)		//如果是写AFE寄存器，则固定写一个字节+CRC
		{
			TWIDAT = *WrBuf;			//Write Data
			TWICON = 0x40;
			if(!TWICheckStatus(0x28))
			{
				result = 0;
				goto WrErr;
			}
			
			TWIDAT = TempBuf[3];			//Write CRC
			TWICON = 0x40;
			if(!TWICheckStatus(0x28))
			{
				result = 0;
				goto WrErr;
			}
		}
		else							//写EEPROM和RTC
		{
			for(i=0; i<Length; i++)
			{
				RSTSTAT = 0x00;
				TWIDAT = *WrBuf;
				TWICON = 0x40;
				if(!TWICheckStatus(0x28))
				{
					result = 0;
					goto WrErr;
				}
				WrBuf++;
			}
		}
WrErr:
		TWICON = 0x50;
		while((TWICON&0x10)!=0)
        {
			RSTSTAT = 0x00;
            if(timeoutcount)
            {
                timeoutcount--;
            }
            else
            {
                break;
            }
        }
	}
	
	return result;
}


/*******************************************************************************
Function: TwiRead()
Description:read rtc register
Input:   RdAddr--register addr
            Lenth   --read data length
            RdBuf   --data buffer
Output: 
Others:
********************************************************************************/
bit TwiRead(U8 SlaveID, U16 RdAddr, U8 Length, U8 xdata *RdBuf)
{
	BOOL result=1;
	U8 i;
    U8 xdata TempBuf[46];
    U8 RdCrc=0;
    U16 timeoutcount = 48000;

    TempBuf[0] = SlaveID;
    TempBuf[1] = (U8)RdAddr;
//    TempBuf[2] = Length;
    TempBuf[2] = SlaveID | 0x01;
	
	if(Length > 0)
	{
		HTimeoutChk();
		TWICON = 0x60;				//Start
		if((!TWICheckStatus(0x08))&&(!TWICheckStatus(0x10)))
		{
			result = 0;
			goto RdErr;
		}
		
		TWIDAT = SlaveID;			//Slave地址
		TWICON = 0x40;
		if(!TWICheckStatus(0x18))
		{
			result = 0;
			goto RdErr;
		}

		if(SlaveID == E2PROM_ID)
		{
			TWIDAT = (U8)(RdAddr>>8);//读寄存器高字节地址-仅针对外挂EEPROM
			TWICON = 0x40;
			if(!TWICheckStatus(0x28))
			{
				result = 0;
				goto RdErr;
			}
		}
		
		TWIDAT = (U8)RdAddr;		//发送寄存器地址
		TWICON = 0x40;
		if(!TWICheckStatus(0x28))
		{
			result = 0;
			goto RdErr;
		}
		
//		if(SlaveID == AFE_CHIP_ID)
//		{
//			TWIDAT = Length;		//发送读取数据长度，只有SH367309 IC需要发送长度
//			TWICON = 0x40;
//			if(!TWICheckStatus(0x28))
//			{
//				result = 0;
//				goto RdErr;
//			}
//		}
		
		TWICON = 0x60;				//RStart
		if((!TWICheckStatus(0x08))&&(!TWICheckStatus(0x10)))
		{
			result = 0;
			goto RdErr;
		}

		TWIDAT = SlaveID|0x01;		//Slave Address and Read
		TWICON = 0x40;
		if(!TWICheckStatus(0x40))
		{
			result = 0;
			goto RdErr;
		}

		for(i=0; i<Length; i++)
		{
			RSTSTAT = 0x00;
			if((SlaveID!=AFE_CHIP_ID))		//Read E2PROM RTC
			{
				if(i == Length-1)
				{
					TWICON = 0x40;          //No ACK
					TWICheckStatus(0x58);
				}
				else
				{
					TWICON = 0x44;          //ACK
					TWICheckStatus(0x50);
				}
				*RdBuf = TWIDAT;
				RdBuf++;
			}
			else
			{
				TWICON = 0x44;					//ACK
				TWICheckStatus(0x50);
				TempBuf[3+i] = TWIDAT;
			}
		}
		
		if(SlaveID == AFE_CHIP_ID)
		{
			TWICON = 0x40;						//No ACK
			TWICheckStatus(0x58);
			RdCrc = TWIDAT;
			if(RdCrc ==  CRC8cal(TempBuf, 3+Length))
			{
				for(i=0; i<Length; i++)
				{
					*RdBuf = TempBuf[3+i];
					RdBuf++;
				}
			}
			else
			{
				result = 0;
				goto RdErr;
			}
		}
RdErr:
		TWICON = 0x50;                  //TWI Stop
		while((TWICON&0x10)!=0)
        {
			RSTSTAT = 0x00;
            if(timeoutcount)
            {
                timeoutcount--;
            }
            else
            {
                break;
            }
        }
	}
	
	return result;
}


/*******************************************************************************
Function: InitTwi()
Description: Init TWI Module  
Input:  NULL
Output: NULL
Others:
*******************************************************************************/
void InitTwi(void)
{
	TWICR = 0x32;		//默认配置：SCL--P0.5；SDA--P0.4
	TWITOUT = 0x00;		//外部有上拉电阻，故芯片内部上拉不用使能
	TWIBR = 0x02;		//配置发送波特率，禁止总线超时判断，f=fsys/(16+2*CR*TWIBR)=24MHz/(16+2*64*2)=90KHz
	TWISTA = 0x00;		//64分频
	TWICON = 0x40;		//ENTWI ，禁止高电平超时
	TWTFREE = 0xff;		//最大超时配置
	TWIDAT = 0x00;
}

#endif