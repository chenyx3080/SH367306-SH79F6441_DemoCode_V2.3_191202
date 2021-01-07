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


/*******************************************************************************
Function: Page1WrRdFuncTable()
Description:
Input:  NULL	
Output: NULL
Others: NULL
*******************************************************************************/
U16 code Page1WrRdFuncTable[18]=
{
    SYS_PARA_MAP_ADDR,               //SubClassID 0x00
    SYSINFO_MAP_ADDR,               //0x01
    CHG_PARA_MAP_ADDR,               //0x02
    DSG_PARA_MAP_ADDR,               //0x03
    0x00,
    DSG_PWM_PARA_MAP_ADDR,            //0x04
    CHG_TEMP_PARA_MAP_ADDR,           //0x05
    DSG_TEMP_PARA_MAP_ADDR,           //0x06                           //0x07
    BAL_PARA_MAP_ADDR,               //0x08
    0x00,                           //0x09
    AFE_PARA_MAP_ADDR,               //0x0A
    CALI_PARA_MAP_ADDR,              //0x0B
    DataflashCheck_Map_ADDR,        //0x0C
    0x00,                           //0x0D
    0x00,                           //0x0E
    0x00,                           //0x0F
    0x00,                           //0x10
    0x00,                           //0x11
};
    
/*******************************************************************************
Function: Page2WrRdFuncTable()
Description:
Input:  NULL	
Output: NULL
Others: NULL
*******************************************************************************/
U16 code Page2WrRdFuncTable[18]=
{
    SYS_PARA_MAP_ADDR+32,            //SubClassID 0x00
    SYSINFO_MAP_ADDR+32,            //0x01
    CHG_PARA_MAP_ADDR+32,            //0x02
    DSG_PARA_MAP_ADDR+32,            //0x03
	0x00,
    DSG_PWM_PARA_MAP_ADDR+32,         //0x04
    CHG_TEMP_PARA_MAP_ADDR+32,        //0x05
    DSG_TEMP_PARA_MAP_ADDR+32,        //0x06                           //0x07
    BAL_PARA_MAP_ADDR+32,            //0x08
    0x00,                           //0x09
    AFE_PARA_MAP_ADDR+32,            //0x0A
    CALI_PARA_MAP_ADDR+32,           //0x0B
    DataflashCheck_Map_ADDR+32,     //0x0C
    0x00,                           //0x0D
    0x00,                           //0x0E
    0x00,                           //0x0F
    0x00,                           //0x10
    0x00,                           //0x11
};

/*******************************************************************************
Function: InitUART0()
Description: Init UART1  
Input:  NULL
Output: NULL
Others:
*******************************************************************************/
void InitUART0(void)
{

    UART0CR = 0x32;
	PCON = 0x00;	
	SCON = 0x50;		//配置Uart工作在模式1
	SBRTH = 0xff;		//配置波特率参数，波特率9600
	SBRTL = 0x64;		//计算公式：(int)X=FSY/(16*波特率) ;  SBRT=32768-X  ;   SFINE=（FSY/波特率）-16*X   FSY=24M
	SFINE = 0x04;
	SADDR = 0x0A;
	SADEN = 0xFF;


	ucUartBufPT = 0;
	ucUartTimeoutCnt = 0;
}


/*******************************************************************************
Function:ISPHandshake() 
Description:  Processing ISP Handshake
Input:	 NULL
Output: NULL
Others:
*******************************************************************************/
//U8 code ISPCODE[8] = {0x05,0x0a,0x09,0x06,'I','S','P'};
U8 code ISPCODE[10] = {0,7,0x05,0x0a,0x09,0x06,'I','S','P'};
void ISPHandshake(void)
{
	U8 i;
	
	for(i=0; i<9; i++)
	{
		if(ucUartBuf[2+i] != ISPCODE[i])
		{
			UART_SEND_NACK;
			return;                  
		}
	}
	bISPFlg = 1;
	bUartSndAckFlg = 0;
	UART_SEND_ACK;
}


/*******************************************************************************
Function:UartHandshake() 
Description:  PC and slave handshake
Input:  NULL
Output: NULL
Others:
*******************************************************************************/
void UartHandshake(void)
{
	if(ucUartBuf[2] == 0x00)        //Testing equipment is properly
	{
		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;
	}
}


 /*******************************************************************************
Function:UartWriteInfo() 
Description:  write the information: MCU Info
Input:  *prt---Data storage address
Output: NULL
Others:
*******************************************************************************/
void UartWriteInfo(U8 xdata *ptr)                   //PC write to MCU
{
	U8 i;
	
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		for(i=0; i<ucUartBuf[UART_LENGTH]; i++)
		{
			RSTSTAT = 0x00;
			*ptr = ucUartBuf[3+i];
			ptr++;
		}
		
		bWriteFlashFlg = 1;         //Updated parameters, and written to the flash
//        UpEepromWithDelay();
		ucWriteFlashCnt=0;
		
		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;
	}
}


 /*******************************************************************************
Function:UartReadInfo() 
Description:  Read the information: Battery Info, MCU Info, MTP Info
Input:  *prt---Data storage address
Output: NULL
Others:
*******************************************************************************/
void UartReadInfo(U8 xdata *ptr)
{
	U8 i;

	if(ucUartBuf[UART_LENGTH] > 140)
	{
		ucUartBuf[UART_LENGTH] = 0;
	}
	
	for(i=0; i<ucUartBuf[UART_LENGTH]; i++)
	{
		RSTSTAT = 0x00;
		ucUartBuf[3+i] =  *ptr;
		ptr++;
	}
	ucUartBuf[3+ucUartBuf[UART_LENGTH]] = CRC8cal(&ucUartBuf,ucUartBuf[UART_LENGTH]+3);
	
	UART_SEND_DATA;			//Start Send Data; Set UART REG
}

/*******************************************************************************
Function:WriteManufacture() 
Description:  write the information: User-defined,  For example, a software reset and forced into sleep
Input:  *prt---Data storage address
Output: NULL
Others:
*******************************************************************************/
void WriteManufacture(void)
{ 
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		if(ucUartBuf[4] == 0x41)            //0x0041: Reset system
		{
			ucResetFlag = 0x12;
		}
		else if(ucUartBuf[4] == 0x05)         //0x0005: Enter sleep mode
		{
			bPCSleepFlg = 1;
		}
		bUartSndAckFlg = 0;
		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;
	}
}


void ReadSubClassID(void)
{
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		ucSubClassID=ucUartBuf[3];
		
		bUartSndAckFlg = 0;
		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;
	}
}



/*******************************************************************************
Function:UartRdCmdProcess() 
Description:  Processing Uart read command  
Input:   NULL
Output: NULL
Others:
*******************************************************************************/
void UartRdCmdProcess(void)
{
    U8 xdata *rdaddr;
    
    switch(ucUartBuf[UART_CMD_NO])
    {
        case 0xA0:
            UartHandshake();
        break;

        case CELL1:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset]);
        break;

        case CELL2:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+1]);
        break;

        case CELL3:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+2]);
        break;

        case CELL4:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+3]);
        break;

        case CELL5:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+4]);
        break;

        case CELL6:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+5]);
        break;

        case CELL7:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+6]);
        break;

        case CELL8:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+7]);
        break;

        case CELL9:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+8]);
        break;

        case CELL10:
            UartReadInfo((U8 xdata *)&Info.uiVCell[ucCellNumOffset+9]);
        break;
		
		case TOTAL_VOLTAGE:
            UartReadInfo((U8 xdata *)&Info.ulVoltage);
        break;

        case CADC_CURRENT:
            UartReadInfo((U8 xdata *)&Info.slCurr);
        break;
		
        case EXT_TEMP1:
            UartReadInfo((U8 xdata *)&Info.uiTemp1);
        break;

        case EXT_TEMP2:
            UartReadInfo((U8 xdata *)&Info.uiTemp2);
        break;

        case DIE_TEMP1:
            UartReadInfo((U8 xdata *)&Info.uiICTemp1);
        break;

        case DIE_TEMP2:
         UartReadInfo((U8 xdata *)&Info.uiICTemp2);
        break;

        case FULL_CHG_CAP:
            UartReadInfo((U8 xdata *)&Info.ulFCC);
        break;

        case REMAIN_CAP:
            UartReadInfo((U8 xdata *)&Info.ulRC);
        break;

        case R_SOC:
            UartReadInfo((U8 xdata *)&Info.uiRSOC);
        break;

        case CYCLE_COUNT:
            UartReadInfo((U8 xdata *)&Info.uiCycleCount);
        break;

        case PACK_STATUS:
            UartReadInfo((U8 xdata *)&Info.uiPackStatus);
        break;

        case BATTERY_STATUS:
            UartReadInfo((U8 xdata *)&Info.uiBatStatus);
        break;

        case PACK_CONFIG:
            UartReadInfo((U8 xdata *)&Info.uiPackConfig);
        break;

        case MANUFACTURE_COMMAND:
            UartReadInfo((U8 xdata *)&Info.uiManuCommand);
        break;

        case ISP_COMMAND:
            ISPHandshake();
        break;
		
        default:    //read extern EEPRom data
            if(ucUartBuf[UART_LENGTH] >= 128)
			{
				bE2PProcessFlg = 1;
                bE2PRdData = 1;
			}
			else if(ucUartBuf[UART_CMD_NO] == SUB_PAGE1 && ucSubClassID == RTC_SUBID)
            {
				bE2PProcessFlg = 1;
				bRTCRdTime = 1;
			}
			else if(ucUartBuf[UART_CMD_NO] == SUB_PAGE1)
            {
                rdaddr = (U8 xdata *)Page1WrRdFuncTable[ucSubClassID];
                UartReadInfo(rdaddr);
            }
            else if(ucUartBuf[UART_CMD_NO] == SUB_PAGE2)
            {
                rdaddr = (U8 xdata *)Page2WrRdFuncTable[ucSubClassID];
                UartReadInfo(rdaddr);
            }
			break;
    }
}


/*******************************************************************************
Function:CalibVoltage() 
Description:  Prepare calibration voltage, include pack voltage & cell voltage
Input:	 NULL
Output: NULL
Others:
*******************************************************************************/
void CalibVoltage(void)
{	
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		bCalibrationFlg = 1;
		ulExtVPack = ((U16)ucUartBuf[3]<<8)|ucUartBuf[4];
		ucExtcaliSwitch1 |= 0x01;

		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;	
	}
}


/*******************************************************************************
Function:CalibCurrent() 
Description:  Prepare calibration zero current and discharge current
Input:	 NULL
Output: NULL
Others:
*******************************************************************************/
void CalibCurrent(void)
{
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		bCalibrationFlg = 1;
		slExtCur = ((U32)ucUartBuf[3]<<24)
						| ((U32)ucUartBuf[4]<<16)
						| ((U32)ucUartBuf[5]<<8)
						| ((U32)ucUartBuf[6]);
		ucExtcaliSwitch1 |= 0x10;

		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;
	}
}


void CalibCurOffset(void)
{
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		bCalibrationFlg = 1;					//Calibration offset Current
		ucExtcaliSwitch1 |= 0x20;

		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;	
	}
}


/*******************************************************************************
Function:CalibTemperature() 
Description:  Prepare calibration temperature
Input:	 NULL
Output: NULL
Others:
*******************************************************************************/
void CalibTS1(void)
{
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		bCalibrationFlg = 1;					//Calibration TS1
		uiExtTemp1 = ((U16)ucUartBuf[3]<<8)|ucUartBuf[4];
		ucExtcaliSwitch1 |= 0x04;

		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;	
	}
}


void CalibTS2(void)
{
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		bCalibrationFlg = 1;					//Calibration TS2
		uiExtTemp2 = ((U16)ucUartBuf[3]<<8)|ucUartBuf[4];
		ucExtcaliSwitch1 |= 0x08;

		UART_SEND_ACK;
	}
	else
	{
		UART_SEND_NACK;	
	}
}


/*******************************************************************************
Function: CaliRTC(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void CalibRTC(void)
{
	U8 i;
	
	if(ucUartBuf[3+ucUartBuf[UART_LENGTH]] == CRC8cal(&ucUartBuf, ucUartBuf[UART_LENGTH]+3))
	{
		for(i=0; i<6; i++)
		{
			bCalibrationFlg = 1;
			ucExtRTC[i] = ucUartBuf[3+i];
			ucExtcaliSwitch1 |= 0x80;
		}
	}
}


/*******************************************************************************
Function:UartWrCmdProcess() 
Description:  Processing Uart write command  
Input:   NULL
Output: NULL
Others:
*******************************************************************************/
void UartWrCmdProcess(void)
{
    U8 xdata *rdaddr;
    switch(ucUartBuf[UART_CMD_NO])
    {
        case MANUFACTURE_COMMAND:
            WriteManufacture();
        break;
        case DATA_FLASH_COMMAND:  
            ReadSubClassID();               //accept command is dataflashcommand 0x77
        break;
        case CALI_CUR_COMMAND:
            CalibCurrent();
        break;
        case CALI_VOL_COMMAND:
            CalibVoltage();
        break;
        case CALI_ZERO_CUR_COMMAND:
            CalibCurOffset();
        break;
        case CALI_TS1_COMMAND:
            CalibTS1();
        break;
        case CALI_TS2_COMMAND:
            CalibTS2();
        break;

        case CALI_RTC_COMMAND:
            CalibRTC();
        break;
//        case ISP_COMMAND:
//            ISPHandshake();
//        break;
        case SUB_PAGE1:
            rdaddr = (U8 xdata *)Page1WrRdFuncTable[ucSubClassID];
            UartWriteInfo(rdaddr);
        break;
        case SUB_PAGE2:
            rdaddr = (U8 xdata *)Page2WrRdFuncTable[ucSubClassID];
            UartWriteInfo(rdaddr);
        break;
        
        case CMD_E2PROM_ERASE:
            if(ucUartBuf[UART_DATA] == 0x55)    //Testing equipment is properly
            {
                bE2PProcessFlg = 1;
                bE2PErase = 1;
                UART_SEND_ACK;
            }
            else
            {
                UART_SEND_NACK;
            }
        break;
    }
}



/*******************************************************************************
Function:  InterruptUART()
Description:  Receive and transmit data via UART
	ucUartBuf[0]--Slave Addr
	ucUartBuf[1]--CMD No.
	ucUartBuf[2]--Offset
	ucUartBuf[3]--Data Length
	ucUartBuf[4...]--Data
Input:	 	
Output: 
Others:
*******************************************************************************/

void InterruptUART(void) interrupt 4
{
	_push_(INSCON);
    BANK0_SEL;

	if(RI)                              //RT1 interrupt means MCU recept data though UART
	{
		ucUartBuf[ucUartBufPT] = SBUF;                  //transfer SBUF to the ucUartBuf
		ucUartBufPT++;
		if(ucUartBufPT >= 80)
		{
			ucUartBufPT = 0;
		}
		if(ucUartBufPT == 1)
		{
			if((ucUartBuf[UART_SLAVE_ADDR]&0xFE) == SADDR)      //received first data is not the slave ADDR
			{
				if((ucUartBuf[UART_SLAVE_ADDR]&0x01)==0)         //bit 7 of UartADDR is R/W 0--R, 1--W
				{
					bUartReadFlg = 1;					//this communication is read
				}
				else
				{
					bUartWriteFlg = 1;					//this communication is write        
				}
			}
			else
			{
				ucUartBufPT = 0;                       //ucUartBufPT reset to 0  
			}
		}
		if(bUartReadFlg)
		{
			if(ucUartBufPT == 3 
				&& ucUartBuf[UART_CMD_NO] != ISP_COMMAND)
			{
				UartRdCmdProcess();                 //Read the command process			
			}
			else if	(ucUartBuf[UART_CMD_NO] == ISP_COMMAND
						&& ucUartBufPT > (ucUartBuf[3]+3))
			{
				ucUartBufPT = 0;
                ucUartSndLength = 1;
				ISPHandshake();
			}
		}
		
		if(bUartWriteFlg)
		{
			if(ucUartBufPT > (ucUartBuf[UART_LENGTH]+3))        //If a write operation, and complete all the data has been received
			{
				UartWrCmdProcess();					//Write the command peocess
				bUartWriteFlg = 0;					//PC write MCU communiaction over
				ucUartBufPT = 0;
			}
		}
		RI = 0;
		bUartSndAckFlg = 0;
	}
	
	if(TI)
	{
		if((ucUartBufPT==0) || (ucUartBufPT>=ucUartBuf[UART_LENGTH]+3))
		{
			REN = 1;					//Allow UART receive data
			ucUartBufPT = 0;
			bUartReadFlg = 0;			//PC read MCU communication over
			ucUartBuf[0] = 0;
			ucUartBuf[1] = 0;
			ucUartBuf[2] = 0;
			ucUartBuf[3] = 0;
		}
		else
		{
			ucUartBufPT++;
			SBUF = ucUartBuf[ucUartBufPT];
		}
		TI = 0;
		bUartSndAckFlg = 1;
	}
		
	ucIdleTimerCnt = 0;
	ucPDTimerCnt = 0;			//If communication is clear the count
	ucUartTimeoutCnt = 0;

	_pop_(INSCON);
}

