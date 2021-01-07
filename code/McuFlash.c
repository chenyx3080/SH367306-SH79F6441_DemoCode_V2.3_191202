/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	
Version: 	V0.0
Date: 		2016/05/18
History:
	        V0.0		2016/05/18		 Preliminary
********************************************************************************/
#include "System.h"


/*******************************************************************************
Function:void Flash_wirte_one_byte(U16 xdata ADRS,U8 xdata WDAT)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void Flash_wirte_one_byte(U16 xdata ADRS,U8 xdata WDAT)
{
    EA = 0;
    FLASHCON = 1;

    XPAGE = ADRS / 256;
    IB_OFFSET = ADRS % 256;

    IB_DATA = WDAT;

    IB_CON1 = 0x6E;	
    IB_CON2 = 0x05;
    IB_CON3 = 0x0A;
    IB_CON4 = 0x09;
    IB_CON5 = 0x06;
    _nop_();		
    _nop_();
    _nop_(); 
    _nop_();
	_nop_();
	
    FLASHCON = 0;	
    EA = 1;
}


/*******************************************************************************
Function:BlackE2CheckUp(U16 Saddr, U16 num) 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
BOOL BlackE2CheckUp(U16 Saddr)
{
    U16 i;
    
    FLASHCON = 0x01;
    RSTSTAT = 0x00;
    
    for(i=0; i<512; i++)
    {
		RSTSTAT = 0x00;
        if(CBYTE[Saddr+i] != 0x00)
        {
            return 0;
        }
    }
    
    return 1;
}


/*******************************************************************************
Function:WriteE2Sector(U16 Saddr, U16 num) 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
BOOL WriteE2Sector(U16 Saddr)
{
    U16 i;
    U8 xdata *data ptr = 0;
    BOOL returnflg = 0;
    
    RSTSTAT = 0x00;

    for(i=0; i<512; i++)
    {
		RSTSTAT = 0x00;
        IB_OFFSET = Saddr+i;
        XPAGE = (Saddr+i)>>8;
        IB_DATA = *(ptr+i);
        
        if(ucUpDataLimitTime == 0)
        {
            IB_CON1 = 0x6E;
            if(!EA)
            {
                IB_CON2 = 0x05;
                if(FLASHCON)
                {
                    IB_CON3 = 0x0A;
                    if(ucFlashWrValid == 0x55)
                    {
                        IB_CON4 = 0x09;
                        if(XPAGE == ((Saddr+i)>>8))
                        {
                            IB_CON5 = 0x06;
                            _nop_();
                            _nop_();
                            _nop_();
                            _nop_();
                            _nop_();
                            
                            returnflg = 1;
                        }
                        else break;
                    }
                    else break;
                }
                else break;
            }
            else break;
        }
        else break;
    }
    return returnflg;
}


/*******************************************************************************
Function:WriteMcuFlash(U16 Saddr) 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
BOOL WriteMcuFlash(U16 Saddr)	//write dataflash from xdata map
{													//Saddr:dataflash addr	,num:length of data, dataaddr: addr of map in xdata
    BOOL returnflg = 0;

    RSTSTAT = 0x00;
	EA = 0;
	FLASHCON = 0x01;
	XPAGE = Saddr >> 8;
    
    if(ucUpDataLimitTime == 0)
    {
        IB_CON1 = 0xE6;
        if(!EA)
        {
            IB_CON2 = 0x05;
            if(FLASHCON)
            {
                IB_CON3 = 0x0A;
                if(ucFlashWrValid == 0x55)
                {
                    IB_CON4 = 0x09;
                    if(XPAGE == (Saddr >> 8))
                    {
                        IB_CON5 = 0x06;
                        _nop_();
                        _nop_();
                        _nop_();
                        _nop_();
                        _nop_();

                        if(BlackE2CheckUp(Saddr))                   
                        {
                            E2uiCheckFlag = 0x5AA5;
                            
                            if(WriteE2Sector(Saddr))                    
                            {
                                if(E2DataCheckUp(Saddr))              
                                {
                                    returnflg = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    IB_CON1 = 0;
    IB_CON2 = 0;
    IB_CON3 = 0;
    IB_CON4 = 0;
    IB_CON5 = 0;
    
    FLASHCON = 0x00;
    XPAGE = 0x00;
    EA = 1;
    
    return returnflg;
}


/*******************************************************************************
Function:E2DataCheckUp() 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
BOOL E2DataCheckUp(U16 Saddr)
{
    U8 xdata *data ptr = 0;
    U16 i;
    
    FLASHCON = 0x01;
    RSTSTAT = 0x00;
    
    for(i=0; i<512; i++)
    {
		RSTSTAT = 0x00;
        if(CBYTE[Saddr+i] != *(ptr+i))
        {
            return 0;
        }
    }
    return 1;
}


/*******************************************************************************
Function:Dataflash_Check() 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
//bit Dataflash_Check(U16 Flashaddr, U16 num, U8 xdata *dataaddr)
//{
//	U8  temp;
//	U16 i;
//	BOOL result=0;
//	FLASHCON = 0x01;
//
//	for(i=0; i<num; i++)
//	{
//	 	temp = CBYTE[Flashaddr+i];
//		if(temp!=*(dataaddr+i))
//		{
//			result=0;
//			goto loop;
//		}
//	}
//	result=1;
//loop:
//	
//	FLASHCON = 0x00;
//	return result;
//
//}


/*******************************************************************************
Function:FlashProcess() 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void FlashProcess(void)
{
	BOOL E2S0WRFailFlg=0, E2S1WRFailFlg=0;
    ucFlashWrValid = 0x55;

	if(ucCellNum > 5)
	{
		uiVoltageMin = 10000;
	}
	else
	{
		uiVoltageMin = 5000;
	}
	
    if((Info.ulVoltage >= uiVoltageMin)&&(E2uiCheckFlag == 0x5AA5))                  //10V
    {
        if(!WriteMcuFlash(DATAFLASH_ADDR))
        {
            if(!WriteMcuFlash(DATAFLASH_ADDR))
            {
                E2S0WRFailFlg = 1;
                E2uiCheckFlag = 0xFFFF;
                Flash_wirte_one_byte(DATAFLASH_ADDR+510,0xFF);
                Flash_wirte_one_byte(DATAFLASH_ADDR+511,0xFF);				
            }
            else if(!WriteMcuFlash(DATAFLASH_ADDR2))
            {
                if(!WriteMcuFlash(DATAFLASH_ADDR2))
                {
                    E2S1WRFailFlg = 1;
                    E2uiCheckFlag = 0xFFFF;
                    Flash_wirte_one_byte(DATAFLASH_ADDR2+510,0xFF);
                    Flash_wirte_one_byte(DATAFLASH_ADDR2+511,0xFF);
                }	
            }			
        }

        else if(!WriteMcuFlash(DATAFLASH_ADDR2))
        {
            if(!WriteMcuFlash(DATAFLASH_ADDR2))
            {
                E2S1WRFailFlg = 1;
                E2uiCheckFlag = 0xFFFF;
                Flash_wirte_one_byte(DATAFLASH_ADDR2+510,0xFF);
                Flash_wirte_one_byte(DATAFLASH_ADDR2+511,0xFF);				
            }	
        }
    }
    else
    {
        E2S0WRFailFlg = 1;
        E2S1WRFailFlg = 1;
    }

    ucFlashWrValid = 0x00;

	if(bUartNeedAckFlg)		
    {
        bUartNeedAckFlg = 0;
        
        if(E2S0WRFailFlg & E2S1WRFailFlg)
        {
            UART_SEND_NACK;
        }
        else
        {
            UART_SEND_ACK;	
        }	
    }
}


/*******************************************************************************
Function: ReadMcuFlash(U16 SourceAddr, U16 DestAddr, U8 Length)
Description:  
Input: 	
Output: 
Others:
*******************************************************************************/
BOOL ReadMcuFlash(U16 SourceAddr, U8 xdata *DestAddr, U16 Length)
{
	U16 i;
    BOOL result = 0;
    U8 xdata *data DestAddr1 = DestAddr;

	EA = 0;
	FLASHCON = 0x01;
    
    if(CWORD[(SourceAddr+510)/2] == 0x5AA5)
    {
        for(i=0; i<=Length; i++)
        {
			RSTSTAT = 0x00;
            *DestAddr1 = CBYTE[SourceAddr+i];
            DestAddr1++;
        }
        result = 1;
    }

	FLASHCON = 0x00;
    return result;
}


/*******************************************************************************
Function: WriteFlashCheck(void)
Description:  
Input: 	
Output: 
Others:
*******************************************************************************/
void WriteFlashCheck(void)
{
	if(bWriteFlashFlg)
	{
	 	if(++ucWriteFlashCnt >= 2)
		{
		 	ucWriteFlashCnt = 0;
			bWriteFlashFlg = 0;
			bUpdataFlashFlg = 1;	
		}
	}
}
