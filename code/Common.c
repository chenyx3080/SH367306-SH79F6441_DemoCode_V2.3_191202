/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "System.h"


#define RAM_CHECK_DATA			0x5A

/*******************************************************************************
Function: Delay1ms()
Description: system clock = 16.6MHz
Input: NULL
Output: NULL
Others: �ر�ע��ú�������ʱ׼ȷ�����⣬�ڲ�ͬ�Ż��ȼ�ʱ������಻ͬ�����ʱ��һ�£�ʵ�����£�
1.������ѡ����Ĵ����Ż��ȼ�����Ϊ3ʱ��j=1670������ֹ�����жϣ���ʵ����ʱΪ3.484ms������ֹ�ж������ж�Ӱ�죬�ﵽ3.804ms
2.������ѡ����Ĵ����Ż��ȼ�����Ϊ3ʱ��j=480������ֹ�����жϣ���ʵ����ʱΪ1.010ms������ֹ�ж������ж�Ӱ�죬�ﵽ1.104ms
3.������ѡ����Ĵ����Ż��ȼ�����Ϊ7ʱ��j=1670������ֹ�����жϣ���ʵ����ʱΪ1.002ms������ֹ�ж������ж�Ӱ�죬�ﵽ1.090ms
*******************************************************************************/
void Delay1ms(U8 delaycnt)
{
	U8 i;
	U16 j;
	
	for(i=0; i<delaycnt; i++)				//system clock = 24MHz
	{
		for(j=0; j<1670; j++)
		{
		}
	}
}


/*******************************************************************************
Function:  ClrRam()
Description: Clear idata space:0x08~STACK_ADDR-1
			 Clear XDATA space:0x0000~0x2FFF  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void ClrRam(void)
{
 	U8 idata *ptr1;
	U8 xdata *ptr2;
	U8 xdata i;
	U16 idata j;

	for(i = 0x08; i <= STACK_ADDR-1; i++)	//clear ram address: 08H~STACK_ADDR-1
	{
		ptr1 = (U8 idata *)i;
		*ptr1 = 0;
	}

	for(j=0; j<=0xAFF; j++)					//clear XDATA address:0000H-0AFFH
	{
		ptr2 = (U8 xdata *)j;
		*ptr2 = 0;
	}
}


/*******************************************************************************
Function:
Description: Clear idata space:0x08~STACK_ADDR-1
			 Clear XDATA space:0x0000~0x2FFF  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void RamCheckProcess(void)
{
    if((ucRamCheckFlg1  != RAM_CHECK_DATA)
    || (ucRamCheckFlg2  != RAM_CHECK_DATA)
    || (ucRamCheckFlg3  != RAM_CHECK_DATA)
    || (ucRamCheckFlg4  != RAM_CHECK_DATA)
    || (ucRamCheckFlg5  != RAM_CHECK_DATA)
    || (ucRamCheckFlg6  != RAM_CHECK_DATA)
    || (ucRamCheckFlg7  != RAM_CHECK_DATA)
    || (ucRamCheckFlg8  != RAM_CHECK_DATA)
    || (ucRamCheckFlg9  != RAM_CHECK_DATA)
    || (ucRamCheckFlg10 != RAM_CHECK_DATA)
    || (E2uiCheckFlag != 0x5AA5))
    {
        InitSysPara();
    }
}


/*******************************************************************************
Function: MemorySet()
Description:
Input:	pt--memoryָ��
		setval---��Ҫ��ֵ������
		length---��Ҫ��ֵ��memory����(Byres)
Output: 
Others:
*******************************************************************************/
void MemorySet(U8 xdata *pt, U8 setval, U8 length)
{
	U8 i;
	for(i=0; i<length; i++)
	{
		*pt = setval;
		pt++;
	}
}


/*******************************************************************************
Function: MemoryCopy()
Description:
Input:	source--ԴMemoryָ��
		target---Ŀ��Memoryָ��
		length---��Ҫ���������ݳ���(Byres)
Output: 
Others:
*******************************************************************************/
void MemoryCopy(U8 xdata *source, U8 xdata *target, U8 length)
{
	U8 i;
	for(i=0; i<length; i++)
	{
		*target = *source;
		target++;
		source++;
	}
}


/*******************************************************************************
Function: IntoIdle()
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void IntoIdle(void)
{
	SUSLO = 0x55;
	PCON |= 0x01;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/*******************************************************************************
Function: IntoPD(void)
Description:  
Input:	 	
Output: 
Others:
*******************************************************************************/
void IntoPD(void)
{
	SUSLO = 0x55;
	PCON |= 0x02;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}


/*******************************************************************************
Function: ResetInit()
Description:MCU����λ����0��ַ��ʼִ��
Input:	 	
Output: 
Others:
*******************************************************************************/
void ResetInit(void)
{	
 	IEN0 = 0x00;						//Disable Interrupt
	IEN1 = 0x00;	
	TCON = 0x00;
	EXF0 = 0x00;

	SBRTH = 0x00;						//Disable UART0
	SBRTL = 0x00;
	SCON = 0x00;
	
	((void(code*)(void))0x0000)();		
}

