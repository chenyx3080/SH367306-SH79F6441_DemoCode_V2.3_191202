/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "system.h"
#include "ISP.h"


/********************************************************************************
ucUartBuf[0]--Slave Addr
ucUartBuf[1]--length
ucUartBuf[2]--Command-H
ucUartBuf[3]--Command-L
********************************************************************************/
void ISPProcess(void)
{
	EA = 0;
	SP = STACK - 1;
 	CLKCON	= 0x08;								//SETB HFON
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLKCON |= 0x04;								//SETB	FS, SYSCLK=24M

	ucUartBufPT = 0;
	ucUartBuf[0] = 0;
	ucUartBuf[1] = 0;
	ucUartBuf[2] = 0;
	ucUartBuf[3] = 0;
	ucUartSndLength = 0;
	
	P0 = 0xF2;
	P0PCR = 0xC2;
	P0CR = 0x81;

	SCON = 0x50;		//配置Uart工作在模式1
	SBRTH = 0xff;		//配置波特率参数，波特率9600
	SBRTL = 0x64;		//计算公式：(int)X=FSY/(16*波特率) ;  SBRT=32768-X  ;   SFINE=（FSY/波特率）-16*X   FSY=24M
	SFINE = 0x04;
	SADDR = 0x0A;
	SADEN = 0xFF;
	
	while(1)
	{
		RSTSTAT = 0x00;
		if(RI)
		{
			ucUartBuf[ucUartBufPT] = SBUF;
			ucUartBufPT++;
			if(ucUartBuf[0]  != SADDR)
			{
				ucUartBufPT = 0;
				ucUartBuf[1] = 0;
			}
			else if(ucUartBuf[1] == CMD_ISP_HANDSHAKE)
			{
				if(ucUartBufPT > (ucUartBuf[3]+3))        //If a write operation, and complete all the data has been received
				{
					ucUartBufPT = 0;
					ucUartSndLength = 1;
					if((ucUartBuf[8]!='I') || (ucUartBuf[9]!='S') || (ucUartBuf[10]!='P'))
					{
						UART_SEND_NACK;
					}
					else
					{
						UART_SEND_ACK;
					}
				}
			}
			else if(ucUartBufPT > 2)
			{
				if(ucUartBufPT >= ucUartBuf[1])
				{
					ISPProcessCMD();
					ucUartBufPT = 0;
				}
			}
			RI = 0;
		}
		
		if(TI)
		{
			ucUartBufPT++;
			if(ucUartBufPT >= ucUartSndLength)
			{
				REN = 1;                                       //Allow UART receive data
				ucUartBufPT = 0;
			}
			else
			{
				REN = 0;                                       //Disable Receive
				SBUF = ucUartBuf[ucUartBufPT];
			}
			TI = 0;
		}
	}
}

/*******************************************************************************
Function: ISPProcessCMD()
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void ISPProcessCMD(void)
{
	U8 data i, DataChksum, SendState;
	U16 data j, UartStartAddr, UartDataLen, UartChksum;
	
	if((ucUartBuf[2]==0xff) && (ucUartBuf[4]=='I') && (ucUartBuf[5]=='S') && (ucUartBuf[6]=='P'))
	{
//Erase Sector
		if(ucUartBuf[3] == UART_ERASE)					
		{
			FLASHCON = ucUartBuf[7];
//			if((FLASHCON&0x01) == 0)
//			{
//				UartDataLen = CODE_SECTOR*512;
//				XPAGE = ucUartBuf[8]<<1;					//Code Area
//			}
//			else
			{
				UartDataLen = E2P_SECTOR*512;
				XPAGE = ucUartBuf[8]<<1;                     //EEPRom
			}
			
            IB_CON1 = 0xE6;
            IB_CON2 = 0x05;
            IB_CON3 = 0x0A;
            IB_CON4 = 0x09;
            IB_CON5 = 0x06;
            _nop_();
            _nop_();
            _nop_();
            _nop_();
            
			
			SendState = STATE_OK;						//Send Data: Erase OK
			for(j=0; j<UartDataLen; j++)
			{
				RSTSTAT = 0x00;
				if(CBYTE[j+(U16)ucUartBuf[8]*512] != 0)
				{
					SendState = STATE_ERROR;            //Send Data: Blank check error
					break;
				}
			}
			ucUartBufPT = 0;
			ucUartSndLength = 1;
			
			REN = 0;                                   //Disable Receive
			SBUF = SendState;                          //Send Data: Erase OK
		}
//Program
		else if(ucUartBuf[3] == UART_PROGRAM)
		{
 			DataChksum = 0;                             //checksum ok or error?
			for(i=0; i<PROGRAM_LENGTH; i++)
			{
				RSTSTAT = 0x00;
				DataChksum += ucUartBuf[10+i];
			}
			
			if(DataChksum != ucUartBuf[10+i])
			{
				SendState = STATE_ERROR;                //Send Data: Erase Error
			}
			else
			{			
				FLASHCON = ucUartBuf[7];
				XPAGE = ucUartBuf[8];                   //EEPRom
				IB_OFFSET = ucUartBuf[9];
				for(i=0; i<PROGRAM_LENGTH; i++)
				{
					RSTSTAT = 0x00;
					IB_DATA = ucUartBuf[10+i];
					IB_CON1 = 0x6E;
					IB_CON2 = 0x05;
					IB_CON3 = 0x0A;
					IB_CON4 = 0x09;
					IB_CON5 = 0x06;
					_nop_();
					_nop_();
					_nop_();
					_nop_();
					IB_OFFSET++;
				}
				SendState = STATE_OK;					//Send Data: Erase OK
			}
			ucUartBufPT = 0;
			ucUartSndLength = 1;
			REN = 0;                                   //Disable Receive
			SBUF = SendState;                          //Send Data: Erase OK
		}

// Checksum Check
		else if(ucUartBuf[3] == UART_CHECKSUM_CHECK)
		{
			UartChksum = 0;
			FLASHCON = ucUartBuf[7];
			XPAGE = ucUartBuf[8];
			UartStartAddr = ((U16)ucUartBuf[8]<<8) | ucUartBuf[9];
			UartDataLen = ((U16)ucUartBuf[10]<<8) | ucUartBuf[11];
			for(j=0; j<UartDataLen; j++)
			{
				RSTSTAT = 0x00;
				UartChksum += CBYTE[UartStartAddr+j];
			}
			
			ucUartBufPT = 0;
			ucUartSndLength = 1;
			if(UartChksum != (((U16)ucUartBuf[12]<<8)|ucUartBuf[13]))
			{
				REN = 0;										//Disable Receive
				SBUF = STATE_ERROR;							//Send Data: Checksum check error
			}
			else
			{
				REN = 0;										//Disable Receive
				SBUF = STATE_OK;                               //Send Data: Checksum check ok
			}
		}
//Read Code or EEPRom
		else if(ucUartBuf[3] == UART_READ)
		{
			FLASHCON = ucUartBuf[7];
			UartStartAddr = ((U16)ucUartBuf[8]<<8) | ucUartBuf[9];
			DataChksum = 0;
			for(i=0; i<PROGRAM_LENGTH; i++)
			{
				RSTSTAT = 0x00;
				ucUartBuf[i] = CBYTE[UartStartAddr+i];
				DataChksum += ucUartBuf[i];
			}
			ucUartBuf[i] = DataChksum;

			ucUartBufPT = 0;
			ucUartSndLength = PROGRAM_LENGTH+1;                   //Modify length,  Old value+64Bytes data+1byte checksum
			REN = 0;                                           //Disable Receive
			SBUF = ucUartBuf[ucUartBufPT];                         //Send Data
		}
//Read 4Bytes info(Code and EEPRom Sector size)
		else if(ucUartBuf[3] == UART_READ4B)
		{			
			ucUartBuf[0] = CODE_SECTOR;
			ucUartBuf[1] = CODE_SIZE;
			ucUartBuf[2] = E2P_SECTOR;
			ucUartBuf[3] = E2P_SIZE;
			DataChksum = ucUartBuf[0]+ucUartBuf[1]+ucUartBuf[2]+ucUartBuf[3];
			ucUartBuf[4] = DataChksum;
			ucUartBufPT = 0;
			ucUartSndLength = 4+1;                                //Modify length,  Old value+4Bytes data+1byte checksum
			REN = 0;                                           //Disable Receive
			SBUF = ucUartBuf[ucUartBufPT];                         //Send Data
		}
//Soft Reset
		else if(ucUartBuf[3] == UART_SOFT_RESET)
		{
			if(ucUartBuf[7] == 0x7f)
			{
				FLASHCON = 0;
				XPAGE = 0;
				ucResetFlag=0x12;
				((void(code*)(void))0x0000)();                  //jump to addr:0x0000				
			}
		}
	}

	FLASHCON = 0;
	XPAGE = 0;
}


