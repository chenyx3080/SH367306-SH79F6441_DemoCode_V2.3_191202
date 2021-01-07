#ifndef	_MEMORY_H
#define	_MEMORY_H
#include "c51_type.h"

#define ProtectCnt					0x02D0
#define STACK_ADDR					0xA0   //0XC0


//*****************************BIT MEMORY START***************************//

extern U16  bdata uiPackConfig;				
extern BOOL bCellNum1;
extern BOOL bCellNum2;
extern BOOL bCellNum3;
extern BOOL bLEDNum0;
extern BOOL bLEDNum1;
extern BOOL bTempNum;
extern BOOL bCHGEnd;
extern BOOL bDSGEnd;
extern BOOL bOV_EN;
extern BOOL bSC_EN;
extern BOOL bOCRC_EN;
extern BOOL bBAL_EN;
extern BOOL bCTO_EN;
extern BOOL bEnEEPRomBK;

extern U16  bdata uiPackStatus;				
extern BOOL bCHGMOS;					   //chgmos flag
extern BOOL bDSGMOS;					   //dsgmos flag
extern BOOL bCHGING;				       //charge status flag means connect to charger
extern BOOL bDSGING;				       //discharge status flag means disconnect to charger 
extern BOOL bZeroCharge;				   //charging status flag means have charge current
extern BOOL bSlowCharge;				   //discharging status falg means have discharge current
extern BOOL bFastCharge;				   //0Vcharging status flag
extern BOOL bSlowDischarge;			   	   //charge PWM ratio is max
extern BOOL bMidDischarge;			  	   //charge PWM ratio is max
extern BOOL bFastDischarge;			  	   //charge PWM ratio is min
extern BOOL bChargerERR;				   //discharge PWM ratio is max
extern BOOL bBatteryFail;			       //discharge PWM ratio is min
extern BOOL bCAL;
extern BOOL bVDQ;
extern BOOL bE2RTCON;

extern U16  bdata uiBatStatus;
extern BOOL bHV;
extern BOOL bUV;
extern BOOL bFC;
extern BOOL bFD;
extern BOOL bOCC;
extern BOOL bOCD;
extern BOOL bOTC;
extern BOOL bOTD;
extern BOOL bUTC;
extern BOOL bUTD;

extern BOOL	bTimer25msFlg;
extern BOOL	bTimer1sFlg;
extern BOOL bDataFlashFail;
extern BOOL	bUpdataFlashFlg;
extern BOOL bWriteFlashFlg;
extern BOOL bKeyFlg;
extern BOOL bCADCFlg;						//CADC转码完成标志
extern BOOL	bVADCFlg;
extern BOOL bISPFlg;						//ISP升级标志，进入ISP程序
extern BOOL	bPCSleepFlg;
extern BOOL	bUartSndAckFlg;
extern BOOL bCalibrationFlg;				//上位机发送校准命令后置位该标志
extern BOOL	bAlarmFlg;
extern BOOL	bLEDOpen;
extern BOOL	bLEDChgFlg;
extern BOOL bBLEOPEN;
extern U8 data	ucTimer3Cnt;

//Check Load And Charger
extern	BOOL	bChkLoadFlg;
extern	BOOL    bChkChgerFlg;
extern	BOOL    bChkChgerRFlg;
extern	BOOL    bLoadConectFlg;
extern	BOOL    bChgerConectFlg;
extern	BOOL	bUVBkFlg;
extern	U8  xdata   ucLoadRCnt;
extern	U8  xdata   ucChgerRCnt;
extern	U8  xdata   ucChgerCnt;
extern	U8  xdata   ucLedChgCnt;
extern	U8  xdata	ucLedFlickCnt;
extern	U8  xdata	ucBLEFlickCnt;

//ALARM
extern BOOL	bAFE_SC;					
extern BOOL	bAFE_OV;					
extern BOOL	bAFE_WDT;					
extern BOOL	bAFE_TWI;					
extern BOOL	bAFE_POR;					
extern BOOL	bAFE_ODD_ERR;					
extern BOOL	bAFE_RST;					
extern BOOL	bAFE_VADC;
extern BOOL	bCTO;					

extern BOOL	bE2PProcessFlg;					//EEPROM处理标志
extern BOOL	bDsgToChgFlg;					//放电转换为充电，需要备份数据
extern BOOL	bChgToDsgFlg;					//充电转换为放电，需要备份数据
extern BOOL	bE2PBKDsgEnd;					//放电结束标志，需要备份信息到外挂EEPROM
extern BOOL bE2PBKDsgEndValid;
extern BOOL	bE2PBKChgStop;					//充电结束标志，需要备份信息到外挂EEPROM
extern BOOL	bE2PBKChgStart;					//充电开始标志，需要备份信息到外挂EEPROM
extern BOOL	bE2PBKRtc;						//RTC定时备份标志，需要备份信息到外挂EEPROM
extern BOOL	bE2PErase;						//擦除外挂EEPROM标志
extern BOOL	bE2PRdData;						//读取外挂EEPROM标志
extern BOOL	bRTCRdTime;						//读取RTC时间标志

//*****************************DATA MEMORY START***************************//
extern U8 idata STACK[];		//堆栈

extern U8  data		ucCellNum;
extern U16 data		uiCellVmax;
extern U16 data		uiCellVmin;
extern U16 data		uiVoltageMin;
extern U16 xdata	uiVadcVmax;				//ADC采集最大值
extern U16 xdata	uiVadcVmin;				//ADC采集最小值
extern U8  xdata	ChgEndTimeCnt;
extern U8  xdata	ChgEndRTimeCnt;
extern U8  xdata	DsgEndTimeCnt;
extern U8  xdata	DsgEndRTimeCnt;
extern U8  xdata	ucBalanceTimeCnt;
extern U16 xdata	uiBalanceChannel;
extern U8  xdata	AFESCONF2Bk;

//VOLTAGE
extern U8   xdata	ucOVcnt;
extern U8	xdata  	ucOVRcnt;
extern U8	xdata  	ucUVcnt;
extern U8	xdata  	ucUVRcnt;
extern U8	xdata  	ucChgEndcnt;
extern U8	xdata  	ucChgEndRcnt;
extern U8	xdata  	ucDsgEndcnt;
extern U8	xdata  	ucDsgEndRcnt;

//TEMP
extern U8	xdata  	ucOTCcnt;
extern U8	xdata  	ucOTCRcnt;
extern U8	xdata  	ucUTCcnt;
extern U8	xdata  	ucUTCRcnt;
extern U8	xdata  	ucOTDcnt;
extern U8	xdata  	ucOTDRcnt;
extern U8	xdata  	ucUTDcnt;
extern U8	xdata  	ucUTDRcnt;

extern U8	data 	ucCellNumOffset;
extern U8	xdata	ucTempeMiddle;

//flash 
extern U8 xdata		ucFlashWrValid;
extern U8 xdata		ucWriteFlashCnt;

//UART
extern	BOOL		bUartReadFlg;
extern	BOOL		bUartWriteFlg;
extern	BOOL		bUartNeedAckFlg;				//UART需要发送ACK给主机
extern U8 xdata		ucUartTimeoutCnt;
extern U8 xdata		ucSubClassID;
extern U8 xdata		ucUartBuf[];
extern U8 xdata		ucUartBufPT;
extern U8 xdata		ucUartSndLength;

//System low power
extern BOOL			bIdleFlg;
extern BOOL			bPDFlg;
extern BOOL			bWakeupFlg;
extern 	U8	xdata	ucIdleTimerCnt;
extern 	U8	xdata	ucPDTimerCnt;
extern 	U8	xdata	ucResetFlag;

//Calibrate
extern U16	xdata	ulExtVPack;
extern  U8  xdata	ucExtcaliSwitch1;
extern  U8  xdata	ucExtcaliFlag;				
extern S32	xdata	slExtCur;
extern U16	xdata	uiExtTemp1;
extern U16	xdata	uiExtTemp2;

//Gauge
extern U16 xdata	uiRCCharge;
extern U16 xdata	uiRCDischarge;
extern U32 xdata	ulDsgCycleCount;
extern U32 xdata	ulFCCCount;
//extern 	BOOL bVDQFlag;

//CADC
extern	U8	 xdata	ucOCCcnt;
extern	U8	 xdata	ucOCDcnt;
extern	U16 xdata	uiOCCRcnt;
extern	U16 xdata	uiOCDRcnt;
extern	U8  xdata	ucCadcCnt;
extern	S32 xdata	slCadcCurBuf[16];

//Balance
extern BOOL			bBalanceFlg;
extern BOOL		    bBalanceOddFlg;
extern U16	xdata	uiBalanceChannel;
//extern U8  xdata	ucBalanceCnt;

//KEY				   
extern U8 	data 	ucKeyValidCnt;
extern U8	data 	ucKeyInvalidCnt;
extern U8	data 	ucKeyValue;
extern U8	data 	ucKeyOldValue;
extern U8	data 	ucKeyValueBK;

//LVCHG
extern U8  xdata	ucLEDTimeCnt;
extern S32 xdata	slCadcCurrent;
extern S32 xdata	slCadcCurAverage;
extern U8  xdata	ucDsgingSpeed;

extern U16 xdata	uiTempeMin;
extern U16 xdata	uiTempeMax;

//cell tap open 
extern BOOL			bBalanceStateFlg;
extern BOOL			bCTOValidFlg;
extern BOOL			bCellOpenDecFlag;
extern BOOL			bBalancingFlg;
extern U8 idata		ucCellOpenDecCnt;
extern U8 idata		ucBalanceStep;
extern U8 idata		ucCtoCnt;

extern U8  xdata	ucExtRTC[6];				//During calibration, the received RTC Time
extern U8  idata	ucUpDataLimitTime;

extern U16 xdata	uiCHGValidTime;

/**************************************************************************************/
//DataFlash中区块地址定义
/**************************************************************************************/
//系统信息区开始 SubClassID=0x00		langth=48
extern U16 xdata 	E2uiPackConfigMap;//		_at_	SYS_PARA_MAP_ADDR; 
extern U16 xdata	E2uiVOC[10];//              _at_	SYS_PARA_MAP_ADDR+20;
extern U32 xdata	E2ulDesignCapacity;//	    _at_	SYS_PARA_MAP_ADDR+22;
extern U32 xdata	E2ulFCC;//					_at_	SYS_PARA_MAP_ADDR+26;
extern U32 xdata	E2ulCycleThreshold;//		_at_	SYS_PARA_MAP_ADDR+30;
extern U16 xdata	E2uiCycleCount;//			_at_	SYS_PARA_MAP_ADDR+34;
extern U16 xdata	E2uiLearnLowTemp;//			_at_	SYS_PARA_MAP_ADDR+36;
extern U16 xdata	E2uiNearFCC;//				_at_	SYS_PARA_MAP_ADDR+38;
extern S16 xdata	E2siDfilterCur;//			_at_	SYS_PARA_MAP_ADDR+40;
extern U8  xdata	E2ucDeleyLowPower;//		_at_	SYS_PARA_MAP_ADDR+42;
extern U8  xdata	E2ucChgBKDelay;//			_at_	SYS_PARA_MAP_ADDR+43;
extern S16 xdata	E2uiChgBKCur;//				_at_	SYS_PARA_MAP_ADDR+44;
extern U8  xdata	E2ucRTCBKDelay;//			_at_	SYS_PARA_MAP_ADDR+46;
extern U8  xdata	ucRamCheckFlg1;//			_at_	SYS_PARA_MAP_ADDR+47;

//用户自定义参数区开始 SubClassID=0x01	langth=50
extern U16 xdata	E2uiSWVersion;//      		_at_	SYSINFO_MAP_ADDR;
extern U16 xdata	E2uiHWVersion;//      		_at_	SYSINFO_MAP_ADDR+2;			
extern U8  xdata	E2ucID;//              		_at_	SYSINFO_MAP_ADDR+4;				
extern U8  xdata	E2ucMNFName[12];//     		_at_	SYSINFO_MAP_ADDR+5;			
extern U32 xdata	E2ulMNFDate;//				_at_	SYSINFO_MAP_ADDR+17;					
extern U16 xdata	E2uiSerialNum;//   			_at_	SYSINFO_MAP_ADDR+21;			
extern U8  xdata	E2ucDeviceName[12];//  		_at_	SYSINFO_MAP_ADDR+23;	
extern U8  xdata	E2ucDeviceChem[12];//  		_at_	SYSINFO_MAP_ADDR+35;		
extern U16 xdata	E2uiChemID;//         		_at_	SYSINFO_MAP_ADDR+47;
extern U8  xdata	ucRamCheckFlg2;//			_at_	SYSINFO_MAP_ADDR+49;

//充电参数区开始 SubClassID=0x02		langth=18		
extern U16 xdata  	E2uiOVvol;//				_at_	CHG_PARA_MAP_ADDR;
extern U16 xdata  	E2uiOVRvol;//         		_at_	CHG_PARA_MAP_ADDR+2;
extern U8  xdata  	E2ucDelayOV ;//      		_at_	CHG_PARA_MAP_ADDR+4;
extern U8  xdata  	E2ucDelayOVR ;//   			_at_	CHG_PARA_MAP_ADDR+5;
extern U16 xdata  	E2uiChgEndVol;//   	    	_at_	CHG_PARA_MAP_ADDR+6;
extern S16 xdata	E2siChgEndCur;// 	      	_at_	CHG_PARA_MAP_ADDR+8;
extern U8  xdata  	E2ucDelayChgEnd ;//  		_at_	CHG_PARA_MAP_ADDR+10;
extern S32 xdata	E2slOCCvol;// 				_at_	CHG_PARA_MAP_ADDR+11;
extern U8  xdata   	E2ucDelayOCC;//				_at_	CHG_PARA_MAP_ADDR+15;
extern U8  xdata  	E2ucDelayOCCR;//			_at_	CHG_PARA_MAP_ADDR+16;
extern U8  xdata	ucRamCheckFlg3;//			_at_	CHG_PARA_MAP_ADDR+17;

//放电参数区开始 SubClassID=0x03		langth=21
extern U16 xdata  	E2uiUVvol;//           		_at_	DSG_PARA_MAP_ADDR;
extern U16 xdata  	E2uiUVRvol;//           	_at_	DSG_PARA_MAP_ADDR+2;
extern U8  xdata  	E2ucDelayUV;//         		_at_	DSG_PARA_MAP_ADDR+4;					  // all the delay unit is 10mS
extern U8  xdata  	E2ucDelayUVR;//         	_at_	DSG_PARA_MAP_ADDR+5;
extern U16 xdata  	E2uiDsgEndVol;//        	_at_	DSG_PARA_MAP_ADDR+6;
extern U8  xdata  	E2ucDelayDsgEnd;//      	_at_	DSG_PARA_MAP_ADDR+8;
extern S32 xdata	E2slOCDvol;// 		  	 	_at_	DSG_PARA_MAP_ADDR+9;
extern U8  xdata	E2ucDelayOCD;// 	 	  	_at_	DSG_PARA_MAP_ADDR+13;
extern S32 xdata	E2slOCD2vol;//		  	 	_at_	DSG_PARA_MAP_ADDR+14;
extern U8  xdata	E2ucDelayOCD2;//	 	  	_at_	DSG_PARA_MAP_ADDR+18;
extern U8  xdata	E2ucDelayLoadR;//	 	  	_at_	DSG_PARA_MAP_ADDR+19;
extern U8  xdata	ucRamCheckFlg4;//			_at_	DSG_PARA_MAP_ADDR+20;

//放电PWM参数区开始 SubClassID=0x04		langth=5
extern U16 xdata 	E2uiDSG1PWMFreq;//	   		_at_	DSG_PWM_PARA_MAP_ADDR; 
extern U8  xdata  	E2ucDSG1PWMRatioL;//   		_at_	DSG_PWM_PARA_MAP_ADDR+2;				 
extern U8  xdata  	E2ucDSG1PWMRatioH;//   		_at_	DSG_PWM_PARA_MAP_ADDR+3;				 
extern U8  xdata	ucRamCheckFlg5;//			_at_ 	DSG_PWM_PARA_MAP_ADDR+4;

//充电温度保护参数开始 SubClassID=0x05	langth=11
extern U16 xdata  	E2uiTempOTC;//      		_at_	CHG_TEMP_PARA_MAP_ADDR;;
extern U16 xdata  	E2uiTempOTCR;//      		_at_	CHG_TEMP_PARA_MAP_ADDR;+2;
extern U16 xdata  	E2uiTempOTD;//        		_at_	CHG_TEMP_PARA_MAP_ADDR;+4;
extern U16 xdata  	E2uiTempOTDR;//       		_at_	CHG_TEMP_PARA_MAP_ADDR;+6;
extern U8  xdata  	E2ucDelayTemp;//      		_at_	CHG_TEMP_PARA_MAP_ADDR;+8;
extern U8  xdata  	E2ucDelayTempR;//	      	_at_	CHG_TEMP_PARA_MAP_ADDR;+9;
extern U8  xdata	ucRamCheckFlg6;//			_at_ 	CHG_TEMP_PARA_MAP_ADDR+10;

//放电温度保护参数开始 SubClassID=0x06	langth=9
extern U16 xdata  	E2uiTempUTC;//        		_at_	DSG_TEMP_PARA_MAP_ADDR;
extern U16 xdata  	E2uiTempUTCR;//       		_at_	DSG_TEMP_PARA_MAP_ADDR+2;
extern U16 xdata  	E2uiTempUTD;//        		_at_	DSG_TEMP_PARA_MAP_ADDR+4;
extern U16 xdata  	E2uiTempUTDR;//       		_at_	DSG_TEMP_PARA_MAP_ADDR+6;
extern U8  xdata	ucRamCheckFlg7;//			_at_ 	DSG_TEMP_PARA_MAP_ADDR+8;

//平衡参数区开始 SubClassID=0x08		langth=8
extern U16 xdata	E2uiBalanceVol;//      		_at_	BAL_PARA_MAP_ADDR;		
extern U16 xdata	E2uiBalanceVolDiff;//  		_at_	BAL_PARA_MAP_ADDR+2;		
extern S16 xdata	E2siBalCurrent;//			_at_	BAL_PARA_MAP_ADDR+4;	
extern U8  xdata	E2ucBalanceDelay;//    		_at_	BAL_PARA_MAP_ADDR+6;	
extern U8  xdata	ucRamCheckFlg8;//			_at_ 	BAL_PARA_MAP_ADDR+7;

//AFE参数区开始 SubClassID=0x0A			langth=4
extern U8  xdata	E2ucAFEProtectConfig;//		_at_	AFE_PARA_MAP_ADDR;
extern U16 xdata	E2uiAFEOVvol;//				_at_	AFE_PARA_MAP_ADDR+1;
extern U8  xdata	ucRamCheckFlg9;//			_at_ 	AFE_PARA_MAP_ADDR+3;

//校准参数区开始 SubClassID=0x0B		langth=12
extern U16 xdata 	E2uiVPackGain;//			_at_	CALI_PARA_MAP_ADDR;		
extern S16 xdata 	E2siCadcGain;//				_at_ 	CALI_PARA_MAP_ADDR+2;
extern S16 xdata 	E2siCadcOffset;//			_at_	CALI_PARA_MAP_ADDR+4;			
extern S16 xdata 	E2siTS1Offset;//			_at_	CALI_PARA_MAP_ADDR+6;
extern S16 xdata 	E2siTS2Offset;//			_at_	CALI_PARA_MAP_ADDR+8;
extern U8  xdata	E2ucCalibrated;//			_at_	CALI_PARA_MAP_ADDR+10;
extern U8  xdata	ucRamCheckFlg10;//			_at_	CALI_PARA_MAP_ADDR+11;

//DataflashCheck
extern U16 xdata	E2uiCheckFlag;	//			_at_    DATAFLASH_MAP_ADDR+510	 		


//Struct
typedef struct	_SYSINFOR_						//data for up-computer monitor	
{
U16		uiPackStatus;								//packstatus include 
U16		uiBatStatus;
U16		uiVCell[20];
U16		ulVoltage;
S32		slCurr;
U16		uiTemp1;
U16		uiTemp2;
U16		uiICTemp1;
U16		uiICTemp2;
U32		ulFCC;									
U32		ulRC;
U16		uiRSOC;
U16		uiCycleCount;
U16		uiPackConfig;
U16		uiManuCommand;
}SYSINFOR;

extern SYSINFOR	 xdata	Info;


typedef struct	_AFEDATA_						//data  get form AFE 
{
	U16 uiCell[10];
	U16 uiTS1;									//TS1 is external tempe
	U16 uiTS2;
	U16 uiICTemp1;								//DieTempe
	U16 uiICTemp2;
	S16	siCurr;
}AFEDATA;

extern AFEDATA xdata AFE;


typedef struct	_AFEREG_					   //data for AFE set in init
{
	U8  AFEFLAG1;
	U8  AFEFLAG2;
	U8  AFEBSTATUS;
	U8  AFEINTEN;
	U8  AFESCONF1;
	U8  AFESCONF2;
	U8  AFESCONF3;
	U8  AFESCONF4;
	U8  AFESCONF5;
	U8  AFESCONF6;
	U8  AFESCONF7;
	U8  AFESCONF8;
	U8  AFESCONF9;
	U8  AFESCONF10;
}AFEREG;

extern AFEREG xdata  REG ;

typedef struct _RTC_VAR_					//BCD Type
{
	U8 Second;
	U8 Minute;
	U8 Hour;
	U8 Week;
	U8 Date;
	U8 Month;
	U8 Year;
}RTC_VAR;
extern RTC_VAR xdata RTC;
extern U16	xdata	uiE2PDataAddr;
extern U8   xdata	ucRTCBKTime1;
extern U16  xdata	uiRTCBKTime2;
extern U8   xdata	ucRTCBuf[];

#endif