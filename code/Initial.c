/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/05/30
History:
	V0.0		2014/05/30		 Preliminary
********************************************************************************/
#include "System.h"
#include "ExtE2PRomRTC.h"
#include "GasGauge.h"
#include "ISP.h"


extern void SystemIntoPD(void);

/*******************************************************************************
Function:InitSealCalibrate() 
Description:  
Input: 	
Output: 
Others:
*******************************************************************************/
void InitSealCalibrate(void)
{
	if(E2ucCalibrated == CALI_FLAG)				//Initialize the Calibration flag
	{
		bCAL = 1;
	}
	else
	{
		bCAL = 0;
	}
}



/*******************************************************************************
Function:InitVar() 
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void InitVar(void)
{
	bTimer1sFlg = 0;
	bTimer25msFlg = 0;
	bDataFlashFail = 0;
	bWriteFlashFlg = 0;
	bUpdataFlashFlg = 0;
	bCADCFlg = 0;
	bISPFlg = 0;

	bUartSndAckFlg = 0;
	bAlarmFlg = 0;
	bLEDOpen = 0;
	bLEDChgFlg = 0;
	bBLEOPEN = 0;
	bCalibrationFlg = 0;

	ucTimer3Cnt = 0;

	bChkLoadFlg = 0;
	bChkChgerFlg = 0;
	bChkChgerRFlg = 0;
	bLoadConectFlg = 0;
	bChgerConectFlg = 0;
	bUVBkFlg = 0;

	ucFlashWrValid = 0;
	ucWriteFlashCnt = 0;
	ucUartTimeoutCnt = 0;
	bIdleFlg = 0;
	bPDFlg = 0;
	bWakeupFlg = 0;
	ucIdleTimerCnt = 0;
	ucPDTimerCnt = 0;
	bKeyFlg = 0;
	ucLEDTimeCnt = 0;
	slCadcCurAverage = 0;
	ucUpDataLimitTime = 0;
	uiPackStatus = 0;
	uiBatStatus = 0;
	AFESCONF2Bk = 0;

	ucOVcnt = 0;
	ucOVRcnt = 0;
	ucUVcnt = 0;
	ucUVRcnt = 0;
	ucOTCcnt = 0;
	ucOTCRcnt = 0;
	ucUTCcnt = 0;
	ucUTCRcnt = 0;
	ucOTDcnt = 0;
	ucOTDRcnt = 0;
	ucUTDcnt = 0;
	ucUTDRcnt = 0;
	ucExtcaliSwitch1 = 0;
	ucExtcaliFlag = 0;

	bBalanceStateFlg = 0;
	bCTOValidFlg = 0;
    bCellOpenDecFlag = 0;
    bBalancingFlg = 0;
    ucCellOpenDecCnt = 0;
    ucBalanceStep = BALANCE_ENABLE;
    ucCtoCnt = 0;

	ucCadcCnt = 0;
	MemorySet((U8 xdata *)slCadcCurBuf, 0, sizeof(slCadcCurBuf));

	bUartSndAckFlg = 0;

	ucBalanceTimeCnt = 0;
	uiBalanceChannel = 0;
	ucLEDTimeCnt = 0;
	bLEDOpen = 0;
	bPCSleepFlg = 0;
	ucTempeMiddle = 80;
	
	MemorySet((U8 xdata *)Info.uiVCell, 0, sizeof(Info.uiVCell));	//clr Info.uiVCell[]
	Info.slCurr = 0;
	Info.uiTemp1 = 2731;				//0
	Info.uiTemp2 = 2731;				//0
}


/*******************************************************************************
Function: InitSysPara()
Description: DataFlash Data write to XRAM  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void InitSysPara(void)
{
    U32 i;
    
    //Starting from the DATAFLASH_ADDR CODE address, read the DATAFLASH_LEN length of the data to the XDATA
	if(!ReadMcuFlash(DATAFLASH_ADDR, DATAFLASH_MAP_ADDR, 512))                      	
    {
        if(!ReadMcuFlash(DATAFLASH_ADDR2, DATAFLASH_MAP_ADDR, 512))         
        {
            while(1)
            {
                RSTSTAT	= 0x00;
                SystemIntoPD();
            }
        }
		else
        {
            FLASHCON = 0x01;
            if(CWORD[DATAFLASH_OK_FLG1_ADDR/2] != 0x5AA5)
            {
                UpEepromNoDelay();
                if(!WriteMcuFlash(DATAFLASH_ADDR))                                 
                {
                    UpEepromNoDelay();
                    WriteMcuFlash(DATAFLASH_ADDR);	
                }
            }
            FLASHCON = 0x00;	
        }
    }
    else
	{
		FLASHCON = 0x01;
		if(CWORD[DATAFLASH_OK_FLG2_ADDR/2] != 0x5AA5)
		{
            UpEepromNoDelay();
			if(!WriteMcuFlash(DATAFLASH_ADDR2))
			{
                UpEepromNoDelay();
				WriteMcuFlash(DATAFLASH_ADDR2);	
			}
		}
		FLASHCON = 0x00;		
	}

    ucFlashWrValid = 0x00;
		
    //intial AFE data
    AFE_Set;													    

    //intial Info	    
	uiPackConfig = E2uiPackConfigMap;
	Info.slCurr = 0;								//After the program is reset, the current default is "0",update after 1'seconds
	Info.ulFCC = E2ulFCC;
	Info.uiCycleCount = E2uiCycleCount;
	Info.uiPackStatus = uiPackStatus;
	Info.uiBatStatus = uiBatStatus;
	Info.uiPackConfig = uiPackConfig;
    
    if(bSC_EN)
    {
        REG.AFESCONF1 |= 0x08;
        REG.AFESCONF6 |= (E2ucAFEProtectConfig&0x0f);
    }
    
    if(bOV_EN)
    {
        REG.AFESCONF1 |= 0x04;
        REG.AFESCONF7 |= (E2ucAFEProtectConfig&0xf0);
        i = (U32)E2uiAFEOVvol*50/293;
        REG.AFESCONF8 = i>>8;
        REG.AFESCONF9 = i;
    }
       
    //Intial cellNum
    ucCellNum = (uiPackConfig&0x0007)+3;												//PackConfigMap last 3 bit set cellnum 3~10
    if(ucCellNum==5 || ucCellNum==10)
    {
        ucCellNumOffset = 0;
    }
    else if(ucCellNum==4 || ucCellNum==9)											//Nomal order	  VC1-VCn
    {
        ucCellNumOffset = 1;
    }
    else
    {
        ucCellNumOffset = 2;
    }
}


/*******************************************************************************
Function: InitIRQ() 
Description: Init EUART,INT0,INT1,TIMER0 Interrupt  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void InitIRQ(void)
{
	EA = 0;

 	IEN0 = 0x30;						//Enable UART0,Timer3 Interrupt
	IEN1 = 0x08;						//Enable INT4
	IENC = 0x20;						//Enable INT45	  ALARM
	IEN0 |= 0x01;						//INT0			  WAKEUP
	TCON = 0x01;						//Exint0：Falling edge trigger
	
	EXF0 = 0x40;						//Exint4：Falling edge trigger
	
	IPL0 = 0x10;
	IPH0 = 0x10;
	IPL1 = 0x00;
	IPH1 = 0x00;						//set uart priority = 3, other interrupt priority  = 0
	
	EA = 1;
}


/*******************************************************************************
Function: InitTimer()
Description: Init Timer3,Set Timer3 time is 25ms 
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void InitTimer(void)
{
	BANK1_SEL;
	T3CON = 0x02;		//外部32.768kHz/128kHz为时钟源，1分频
	TL3 = 0xCD;		 
	TH3 = 0xFC;			//25mS
	TR3 = 1;			//启动定时器3
	BANK0_SEL;
}


/*******************************************************************************
Function: InitGPIO()
Description:
    P0.7[TXD],  P0.6[RXD],  P0.5[SCL],  P0.4[SDA],  P0.3[],     P0.2[],     P0.1[KLED], P0.0[BLPW], 
    P0.7ST[1],  P0.6ST[1],  P0.5ST[1],  P0.4ST[1],  P0.3ST[0]0,  P0.2ST[0],  P0.1ST[1]0,  P0.0ST[0]0,  P0 = 0xF2;
    P0.7CR[1],  P0.6CR[0],  P0.5CR[0],  P0.4CR[0],  P0.3CR[1]1,  P0.2CR[1],  P0.1CR[0]1,  P0.0CR[1]1,  P0CR = 0x8D;
    P0.7PC[1],  P0.6PC[1],  P0.5PC[0],  P0.4PC[0],  P0.3PC[0]0,  P0.2PC[0],  P0.1PC[1]0,  P0.0PC[0]0,  P0PCR = 0xC2;

    P1.7[],     P1.6[],     P1.5[],     P1.4[],     P1.3[],     P1.2[],     P1.1[], 	P1.0[], 
    P1.7ST[0],  P1.6ST[0],  P1.5ST[0],  P1.4ST[0],  P1.3ST[0],  P1.2ST[0],  P1.1ST[0],  P1.0ST[0],  P1 = 0x00;
    P1.7CR[1],  P1.6CR[1],  P1.5CR[1],  P1.4CR[1],  P1.3CR[1],  P1.2CR[1],  P1.1CR[1],  P1.0CR[1],  P1CR = 0xFF;
    P1.7PC[0],  P1.6PC[0],  P1.5PC[0],  P1.4PC[0],  P1.3PC[0],  P1.2PC[0],  P1.1PC[0],  P1.0PC[0],  P1PCR = 0x00;

    P2.7[], 	 P2.6[ALARM],P2.5[CTLD], P2.4[LED5], P2.3[LED4], P2.2[LED3], P2.1[LED2], P2.0[LED1], 
    P2.7ST[0]1,  P2.6ST[1],  P2.5ST[1],  P2.4ST[0],  P2.3ST[0],  P2.2ST[0],  P2.1ST[0],  P2.0ST[0],  P2 = 0x60;
    P2.7CR[1]0,  P2.6CR[0],  P2.5CR[1],  P2.4CR[1],  P2.3CR[1],  P2.2CR[1],  P2.1CR[1],  P2.0CR[1],  P2CR = 0xBF;
    P2.7PC[0]1,  P2.6PC[1],  P2.5PC[0],  P2.4PC[0],  P2.3PC[0],  P2.2PC[0],  P2.1PC[0],  P2.0PC[0],  P2PCR = 0x40;

    P3.7[],     P3.6[],     P3.5[LED6]6, P3.4[XTAL1],P3.3[XTAL2],P3.2[],	 P3.1[KEY],   P3.0[], 
    P3.7ST[0],  P3.6ST[0],  P3.5ST[0]1,  P3.4ST[1],  P3.3ST[1],  P3.2ST[0],  P3.1ST[1]0,  P3.0ST[0]1,  P3 = 0x1A;
    P3.7CR[1],  P3.6CR[1],  P3.5CR[1]0,  P3.4CR[0],  P3.3CR[0],  P3.2CR[1],  P3.1CR[0]1,  P3.0CR[1]0,  P3CR = 0xE5;
    P3.7PC[0],  P3.6PC[0],  P3.5PC[0]1,  P3.4PC[1],  P3.3PC[1],  P3.2PC[0],  P3.1PC[1]0,  P3.0PC[0]1,  P3PCR = 0x1A;
Input:	NULL
Output: NULL
Others:
*******************************************************************************/
void InitGPIO(void)
{	
	P1 = 0x00;
	P1PCR = 0x00;
	P1CR = 0xFF;
	
	P0 = 0xF2;
	P0PCR = 0xC2;
	P0CR = 0x8D;

	P2 = 0x60;
	P2PCR = 0x40;
	P2CR = 0xBF;

	P3 = 0x02;
	P3PCR = 0x02;
	P3CR = 0xFD;
	
	IO_BLEPW = 1;
}


/*******************************************************************************
Function: InitClk()
Description: Set system clock = 16.6M/12 
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void InitClk(void)
{
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
}


/*******************************************************************************
Function: InitPWM()
Description: InitPWM2 
Input:	NULL   	
Output: NULL
Others:
*******************************************************************************/
void InitPWM(void)
{
    PWM2CON = 0xb0;						      	  //系统时钟/64
    PWM2PL = 375000/E2uiDSG1PWMFreq;	 		  //PWM2P=24000000/(64*E2uiDSG1PWMFreq);
	PWM2PH = (375000/E2uiDSG1PWMFreq) >> 8;
    PWM2DL = (U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioL/100;
	PWM2DH = ((U16)(PWM2PL+PWM2PH*256)*E2ucDSG1PWMRatioL/100) >> 8;
	bSlowDischarge = 0;
	bMidDischarge = 0;
	ucDsgingSpeed = 2;
	bFastDischarge = 1;
}


/*******************************************************************************
Function:PartialInitial()  
Description:  
Input: 	
Output: 
Others:
*******************************************************************************/
void PartialInitial(void)
{
	InitGPIO();						//初始化GPIO

	InitTimer();					//初始化Timer

	InitUART0();					//初始化UART模块

	InitTwi();						//初始化TWI模块

	InitSysPara();					//初始化系统参数

	InitVar();						//初始化变量
	
	InitPWM();						//初始化PWM

	if(InitAFE())					//初始化 306
	{
        ClearAFEFlg();

        if(WaitADCConvert())
        {
    		BatteryInfoManage();			//电池信息管理：获取电压、电流、温度
			
    		PorOnProtect();					//开机保护
    
    		InitGasGauge();					//初始化容量信息，RSOC
   
    	    InitIRQ();						//初始化中断
        }
        else
        {
	    	IntoPowerDown();
        }
	}
	else
	{
		IntoPowerDown();
	}
	
	InitSealCalibrate();			//判断是否做过校准全部参数

	if(bEnEEPRomBK)					//如果支持外部RTC和EEPROM，需要初始化
	{
		InitE2PRom();
		InitRTC();
	}

}


/*******************************************************************************
Function: AllInitial()
Description:  
Input:	NULL 	
Output: NULL
Others:
*******************************************************************************/
void AllInitial(void)
{
	InitGPIO();						//初始化GPIO

	ClrRam();						//清空MCU RAM
	
	InitTimer();					//初始化Timer

	InitUART0();					//初始化UART1模块

	InitTwi();						//初始化TWI模块

	InitSysPara();					//初始化系统参数

	InitVar();						//初始化变量

	InitPWM();						//初始化PWM

	if(InitAFE())					//初始化 306
	{
        ClearAFEFlg();

        if(WaitADCConvert())
        {
    		BatteryInfoManage();			//电池信息管理：获取电压、电流、温度
			
    		PorOnProtect();					//开机保护
    
    		InitGasGauge();					//初始化容量信息，RSOC
   
    	    InitIRQ();						//初始化中断
        }
        else
        {
	    	IntoPowerDown();
        }
	}
	else
	{
		IntoPowerDown();
	}
	
	InitSealCalibrate();			//判断是否做过校准全部参数

	if(bEnEEPRomBK)					//如果支持外部RTC和EEPROM，需要初始化
	{
		InitE2PRom();
		InitRTC();
	}

}


/*******************************************************************************
Function: Initial()
Description:  ALLInitial()--Initial all data; PartialInitial()--Initial part data;
Input: 	NULL
Output: NULL
Others:
*******************************************************************************/
void Initial(void)
{
	FLASHCON = 0x00;
    if(CWORD[510/2] != 0x5AA5)	//程序检测第一个1K数据最后两个字节是否为0x5AA5，如果不是则认为程序异常，直接进入ISP
	{
        ISPProcess();
	}

	if(((RSTSTAT&0x38)!=0) || (ucResetFlag==0x12))	//POR+LVR+ResetPin+PC instruction
	{
	 	RSTSTAT	= 0x00;
		ucResetFlag = 0;
		
		AllInitial();
	}
	else			//WDT+OVL复位
	{
	 	RSTSTAT	= 0x00;
		PartialInitial();
	}
}






