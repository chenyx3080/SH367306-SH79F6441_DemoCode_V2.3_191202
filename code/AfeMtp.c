/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/08/28		 Preliminary
********************************************************************************/
#include "System.h"


/*******************************************************************************
Function:TwiWriteAFE(U8 WrAddr, U8 xdata *WrBuf) 
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
bit TwiWriteAFE(U8 WrAddr, U8 xdata *WrBuf)					//write only one byte once
{
    BOOL result = 0;							
    U8 times = 0;

    while(times++ < TRY_TIMES)
    {
		result = TwiWrite(AFE_CHIP_ID, WrAddr, 1, WrBuf);
		if(result)
		{
			break;
		}
		else
		{
			Delay1ms(1);
		}
    }
    
    return  result;
}


/*******************************************************************************
Function:TWIReadAFE(U8 RdAddr, U8 xdata *RdBuf) 
Description:  
Input:		
Output: 
Others:
*******************************************************************************/
bit TWIReadAFE(U8 RdAddr, U8 xdata *RdBuf)		//��AFE
{
    BOOL result = 0;							
    U8 times = 0;

    while(times++ < TRY_TIMES)					//�������������Try 5��
    {
		result = TwiRead(AFE_CHIP_ID, RdAddr, 2, RdBuf);	//��ȡ���ݳ��ȹ̶�Ϊ2Bytes
		if(result)								//��������ɹ���CRCУ����ȷ�����˳�ѭ�����سɹ����־
		{
			break;
		}
		else									//���TWI������CRCУ��ʧ�ܣ�����ʱ1mS֮���ٶ�ȡ
		{
			Delay1ms(1);
		}
    }
    
    return  result;
}


/*******************************************************************************
Function:ClearAFEFlg(void) 
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void ClearAFEFlg(void)
{
	TWIReadAFE(AFE_FLAG1, &REG.AFEFLAG1);		//read AFE FLAG1 search for which state  trigged ALARM
	if((REG.AFEFLAG1!=0) || (REG.AFEFLAG2!=0))								
	{
        REG.AFESCONF1 |= 0x80;
        TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
        REG.AFESCONF1 &= ~0x80;
        TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);
	}
}


/*******************************************************************************
Function:InitAFE() 
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
bit InitAFE(void)
{
	U8 i;
	BOOL result=1;

	for(i=0; i<11; i++)
	{
		if(!TwiWriteAFE(AFE_INT_EN+i, &REG.AFEINTEN+i))
		{
        	result = 0;
    		break;
		}
	}

	return result;
}


/*******************************************************************************
Function:EnableAFEWdtCadc()  
Description:ʹ��CHG&DSG&PCHG�������ʹ��WDT��CADCģ��
Input: 	
Output: 
Others:
*******************************************************************************/
//void EnableAFEWdtCadc(void)
//{
//	ucMTPConfVal |= 0x7c;
//	MTPWrite(MTP_CONF, 1, &ucMTPConfVal);
//}