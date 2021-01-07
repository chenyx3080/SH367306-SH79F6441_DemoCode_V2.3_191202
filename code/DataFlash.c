/********************************************************************************
Copyright (C), Sinowealth Electronic. Ltd.
Author: 	Sino
Version: 	V0.0
Date: 		2014/09/10
History:
	V0.0		2014/09/10		 Preliminary
********************************************************************************/
#define RAM_CHECK_DATA			0x5A


unsigned char code dataflash[] =
{
/*****************************************************************************************************************/
//备份A区
/*****************************************************************************************************************/
//系统信息区开始 SubClassID=0x00		langth=48
	0x2b, 0x37,							// U16 xdata PackConfigMap		_at_ 	SYS_PARA_MAP_ADDR; 
	0x00C,0x080,						// U16 xdata VOC10              _at_ 	SYS_PARA_MAP_ADDR+2;
	0x00D,0x048,						// U16 xdata VOC20              _at_ 	SYS_PARA_MAP_ADDR+4;
	0x00D,0x0DE,						// U16 xdata VOC30              _at_ 	SYS_PARA_MAP_ADDR+6;
	0x00E,0x074,						// U16 xdata VOC40              _at_ 	SYS_PARA_MAP_ADDR+8;
	0x00E,0x0D8,				    	// U16 xdata VOC50              _at_ 	SYS_PARA_MAP_ADDR+10;	  
	0x00F,0x03C,						// U16 xdata VOC60              _at_ 	SYS_PARA_MAP_ADDR+12;			
	0x00F,0x0A0,						// U16 xdata VOC70              _at_ 	SYS_PARA_MAP_ADDR+14;				
	0x010,0x004,						// U16 xdata VOC80              _at_ 	SYS_PARA_MAP_ADDR+16;				
	0x010,0x036,						// U16 xdata VOC90              _at_ 	SYS_PARA_MAP_ADDR+18;				
	0x010,0x068,						// U16 xdata VOC100             _at_ 	SYS_PARA_MAP_ADDR+20;				
	0X000,0X000,0x008,0x098,			// U32 xdata DesignCapacity	    _at_ 	SYS_PARA_MAP_ADDR+22;	2200mAh
	0X000,0X000,0x008,0x098,			// U32 xdata FullChargeCapacity	_at_ 	SYS_PARA_MAP_ADDR+26;	2200
	0X000,0X000,0x008,0x034,			// U32 xdata CycleThreshold		_at_ 	SYS_PARA_MAP_ADDR+30;	2100
	0X000,0X000,						// U16 xdata CycleCount			_at_ 	SYS_PARA_MAP_ADDR+34;
	0x00a,0x0ab,						// U16 xdata LearnLowTemp		_at_ 	SYS_PARA_MAP_ADDR+36;	2731
	0x000,0x0C8,						// U16 xdata NearFull			_at_ 	SYS_PARA_MAP_ADDR+38;	200
	0x000,0x064,						// S16 xdata DfilterCur			_at_ 	SYS_PARA_MAP_ADDR+40;	100
	0x014,								// U8  xdata DeleyLowPower		_at_ 	SYS_PARA_MAP_ADDR+42;	20s
	0x001,						 		// U8  xdata E2ucChgBKDelay		_at_	SYS_PARA_MAP_ADDR+43;	1min
	0x000,0x064,						// S16 xdata E2uiChgBKCur		_at_	SYS_PARA_MAP_ADDR+44;	100mA
	0x005,								// U8  xdata E2ucRTCBKDelay		_at_	SYS_PARA_MAP_ADDR+46;	5s
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg1		_at_	SYS_PARA_MAP_ADDR+47;

//用户自定义参数区开始 SubClassID=0x01	langth=50
	0x002,0x030,						// U16 xdata SWVersion	        _at_ 	SYSINFO_MAP_ADDR;		V2.0	
	0x004,0x010,						// U16 xdata HWVersion       	_at_ 	SYSINFO_MAP_ADDR+2;		V4.0	
	0x000,								// U8  xdata ID              	_at_ 	SYSINFO_MAP_ADDR+4;				
	'S','i','n','o',					// U8  xdata MNFName[12]     	_at_ 	SYSINFO_MAP_ADDR+5;
	'w','e','a','l','t','h',
	0x000,0x000,								

	0x020,0x019,0x012,0x002,			// U32 xdata MNFDate			_at_ 	SYSINFO_MAP_ADDR+17;					
	0x000,0x000,						// U16 xdata SerialNum    		_at_ 	SYSINFO_MAP_ADDR+21;			
	'S','H','3','6','7','3','0','6',	// U8  xdata DeviceName[12]  	_at_ 	SYSINFO_MAP_ADDR+23;
	0x000,0x000,0x000,0x000,					

	'L','I','O','N',					// U8  xdata DeviceChem[12]  	_at_ 	SYSINFO_MAP_ADDR+35;
	0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,				

	0x000,0x000,						// U16 xdata ChemID          	_at_ 	SYSINFO_MAP_ADDR+47;
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg2     _at_	SYSINFO_MAP_ADDR+49;

//充电参数区开始 SubClassID=0x02		langth=18			
	0x010,0x09A,						// U16 xdata OVvol				_at_ 	CHG_PARA_MAP_ADDR;		4250
	0x010,0x036,						// U16 xdata OVRvol         	_at_ 	CHG_PARA_MAP_ADDR+2;	4150
	0x002,								// U8  xdata DelayOV       		_at_ 	CHG_PARA_MAP_ADDR+4;	2
	0x002,								// U8  xdata DelayOVR    		_at_ 	CHG_PARA_MAP_ADDR+5;	2
	0x010,0x068,						// U16 xdata ChgEndvol   	    _at_ 	CHG_PARA_MAP_ADDR+6;	4200	
	0x000,0x064,						// S16 xdata ChgEndCur	      	_at_ 	CHG_PARA_MAP_ADDR+8;	100
	0x005,								// U8  xdata DelayChgEnd   		_at_ 	CHG_PARA_MAP_ADDR+10;	5
	0x000,0x000,0x00B,0x0B8,			// S32 xdata OCCvol 			_at_ 	CHG_PARA_MAP_ADDR+11;	3000
	0x002,								// U8  xdata DelayOCC			_at_ 	CHG_PARA_MAP_ADDR+15;	2
	0x00a,								// U8  xdata DelayOCCR			_at_ 	CHG_PARA_MAP_ADDR+16;	10
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg3     _at_	CHG_PARA_MAP_ADDR+17;

//放电参数区开始 SubClassID=0x03		langth=21
	0x00A,0x08C,					 	// U16 xdata UVvol          	_at_ 	DSG_PARA_MAP_ADDR;		2700
	0x00B,0x0B8,						// U16 xdata UVRvol          	_at_ 	DSG_PARA_MAP_ADDR+2;	3000
	0x002,								// U8  xdata DelayUV        	_at_ 	DSG_PARA_MAP_ADDR+4;	2		// all the delay unit is 500mS
	0x002,								// U8  xdata DelayUVR        	_at_ 	DSG_PARA_MAP_ADDR+5;	2
	0x00B,0x054,						// U16 xdata DsgEndvol       	_at_ 	DSG_PARA_MAP_ADDR+6;	2900
	0x005,								// U8  xdata DelayDsgEnd     	_at_ 	DSG_PARA_MAP_ADDR+8;	5
	0xFF,0xFF,0x0B1,0x0E0,				// U16 xdata OCDvol		  	 	_at_ 	DSG_PARA_MAP_ADDR+9;
	0x002,								// U8  xdata DelayOCD	 	  	_at_ 	DSG_PARA_MAP_ADDR+13;	2
	0xFF,0xFF,0x063,0x0c0,				// S32 xdata OCD2vol		  	_at_ 	DSG_PARA_MAP_ADDR+14;
	0x002,								// U8  xdata DelayOCD2	 	  	_at_ 	DSG_PARA_MAP_ADDR+18;	2
	0x004,								// U8  xdata DelayLoadR	 	  	_at_ 	DSG_PARA_MAP_ADDR+19;	4
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg4     _at_	DSG_PARA_MAP_ADDR+20;

//放电PWM参数区开始 SubClassID=0x04		langth=5
	0x00F,0x0A0,						// U16 xdata DSG1PWMFreq	   	_at_ 	DSG_PWM_PARA_MAP_ADDR;		4000Hz
	0x01e,								// U8  xdata DSG1PWMRatioL   	_at_ 	DSG_PWM_PARA_MAP_ADDR+2;	30%
	0x046,								// U8  xdata DSG1PWMRatioH   	_at_ 	DSG_PWM_PARA_MAP_ADDR+3;	70%				
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg5		_at_ 	DSG_PWM_PARA_MAP_ADDR+4;

//充电温度保护参数开始 SubClassID=0x05	langth=11
	0x00C,0x09F,						// U16 xdata TempOTC      		_at_ 	CHG_TEMP_PARA_MAP_ADDR;		3231-2731=500
	0x00C,0x06D,						// U16 xdata TempOTCR      		_at_ 	CHG_TEMP_PARA_MAP_ADDR+2;	3181-2731=450
	0x00A,0x0AB,						// U16 xdata TempUTC        	_at_ 	CHG_TEMP_PARA_MAP_ADDR+4;	2731
	0x00A,0x0DD,						// U16 xdata TempUTCR       	_at_ 	CHG_TEMP_PARA_MAP_ADDR+6;	2781-2731=50
	0x003,								// U8  xdata DelayOTC      		_at_ 	CHG_TEMP_PARA_MAP_ADDR+8;	3
	0x003,								// U8  xdata DelayOTCR	      	_at_ 	CHG_TEMP_PARA_MAP_ADDR+9;	3
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg6		_at_ 	CHG_TEMP_PARA_MAP_ADDR+10;

//放电温度保护参数开始 SubClassID=0x06	langth=9
	0x00D,0x067,						// U16 xdata TempOTD       	 	_at_ 	DSG_TEMP_PARA_MAP_ADDR;		3431-2731=700
	0x00C,0x0D1,						// U16 xdata TempOTDR       	_at_ 	DSG_TEMP_PARA_MAP_ADDR+2;	3281-2731=550
	0x00A,0x047,						// U16 xdata TempUTD        	_at_ 	DSG_TEMP_PARA_MAP_ADDR+4;	2631-2731=-100
	0x00A,0x079,						// U16 xdata TempUTDR       	_at_ 	DSG_TEMP_PARA_MAP_ADDR+6;	2681-2731=-50
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg7		_at_ 	DSG_TEMP_PARA_MAP_ADDR+8;

//平衡参数区开始 SubClassID=0x08		langth=8
	0x010,0x054,						// U16 xdata BalanceVol      	_at_	BAL_PARA_MAP_ADDR;		4180
	0x000,0x014,						// U16 xdata BalanceVolDiff  	_at_	BAL_PARA_MAP_ADDR+2;	20	
	0x000,0x064,						// S16 xdata BalCurrent			_at_ 	BAL_PARA_MAP_ADDR+4;	100
	0x002,								// U8  xdata BalanceDelay    	_at_ 	BAL_PARA_MAP_ADDR+6;	2
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg8		_at_ 	BAL_PARA_MAP_ADDR+7;

//AFE参数区开始 SubClassID=0x0A			langth=4
	0x074,								// U8  xdata AFEProtectConfig	_at_ 	AFE_PARA_MAP_ADDR;
	0x011,0x030,						// U16 xdata AFEOVvol			_at_ 	AFE_PARA_MAP_ADDR+2;	4400
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg9		_at_ 	AFE_PARA_MAP_ADDR+3;

//校准参数区开始 SubClassID=0x0B		langth=12
	0x00A,0x022,						// U16 xdata VPackGain			_at_	CALI_PARA_MAP_ADDR;		2594
	0x0FF,0x0AE,						// S16 xdata CadcGain			_at_ 	CALI_PARA_MAP_ADDR+2;	-82
	0x000,0x001,						// S16 xdata CadcOffset			_at_	CALI_PARA_MAP_ADDR+4;
	0x000,0x000,						// S16 xdata TS1Offset			_at_	CALI_PARA_MAP_ADDR+6;
	0x000,0x000,						// S16 xdata TS2Offset			_at_	CALI_PARA_MAP_ADDR+8;
	0x000,								// U8  xdata E2ucCalibrated		_at_	CALI_PARA_MAP_ADDR+10;
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg10	_at_	CALI_PARA_MAP_ADDR+11;

//Reserved
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,

	0x05A,0x0A5,				   	 // U16 xdata FlashCheck			_at_ 	DataflashCheck_Map_ADDR;		



/*****************************************************************************************************************/
//备份B区
/*****************************************************************************************************************/
//系统信息区开始 SubClassID=0x00		langth=48
	0x2b, 0x37,							// U16 xdata PackConfigMap		_at_ 	SYS_PARA_MAP_ADDR; 
	0x00C,0x080,						// U16 xdata VOC10              _at_ 	SYS_PARA_MAP_ADDR+2;
	0x00D,0x048,						// U16 xdata VOC20              _at_ 	SYS_PARA_MAP_ADDR+4;
	0x00D,0x0DE,						// U16 xdata VOC30              _at_ 	SYS_PARA_MAP_ADDR+6;
	0x00E,0x074,						// U16 xdata VOC40              _at_ 	SYS_PARA_MAP_ADDR+8;
	0x00E,0x0D8,				    	// U16 xdata VOC50              _at_ 	SYS_PARA_MAP_ADDR+10;	  
	0x00F,0x03C,						// U16 xdata VOC60              _at_ 	SYS_PARA_MAP_ADDR+12;			
	0x00F,0x0A0,						// U16 xdata VOC70              _at_ 	SYS_PARA_MAP_ADDR+14;				
	0x010,0x004,						// U16 xdata VOC80              _at_ 	SYS_PARA_MAP_ADDR+16;				
	0x010,0x036,						// U16 xdata VOC90              _at_ 	SYS_PARA_MAP_ADDR+18;				
	0x010,0x068,						// U16 xdata VOC100             _at_ 	SYS_PARA_MAP_ADDR+20;				
	0X000,0X000,0x008,0x098,			// U32 xdata DesignCapacity	    _at_ 	SYS_PARA_MAP_ADDR+22;	2200mAh
	0X000,0X000,0x008,0x098,			// U32 xdata FullChargeCapacity	_at_ 	SYS_PARA_MAP_ADDR+26;	2200
	0X000,0X000,0x008,0x034,			// U32 xdata CycleThreshold		_at_ 	SYS_PARA_MAP_ADDR+30;	2100
	0X000,0X000,						// U16 xdata CycleCount			_at_ 	SYS_PARA_MAP_ADDR+34;
	0x00a,0x0ab,						// U16 xdata LearnLowTemp		_at_ 	SYS_PARA_MAP_ADDR+36;	2731
	0x000,0x0C8,						// U16 xdata NearFull			_at_ 	SYS_PARA_MAP_ADDR+38;	200
	0x000,0x064,						// S16 xdata DfilterCur			_at_ 	SYS_PARA_MAP_ADDR+40;	100
	0x014,								// U8  xdata DeleyLowPower		_at_ 	SYS_PARA_MAP_ADDR+42;	20s
	0x001,						 		// U8  xdata E2ucChgBKDelay		_at_	SYS_PARA_MAP_ADDR+43;	1min
	0x000,0x064,						// S16 xdata E2uiChgBKCur		_at_	SYS_PARA_MAP_ADDR+44;	100mA
	0x005,								// U8  xdata E2ucRTCBKDelay		_at_	SYS_PARA_MAP_ADDR+46;	5s
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg1		_at_	SYS_PARA_MAP_ADDR+47;

//用户自定义参数区开始 SubClassID=0x01	langth=50
	0x002,0x030,						// U16 xdata SWVersion	        _at_ 	SYSINFO_MAP_ADDR;		V2.0	
	0x004,0x010,						// U16 xdata HWVersion       	_at_ 	SYSINFO_MAP_ADDR+2;		V4.0	
	0x000,								// U8  xdata ID              	_at_ 	SYSINFO_MAP_ADDR+4;				
	'S','i','n','o',					// U8  xdata MNFName[12]     	_at_ 	SYSINFO_MAP_ADDR+5;
	'w','e','a','l','t','h',
	0x000,0x000,								

	0x020,0x019,0x012,0x002,			// U32 xdata MNFDate			_at_ 	SYSINFO_MAP_ADDR+17;					
	0x000,0x000,						// U16 xdata SerialNum    		_at_ 	SYSINFO_MAP_ADDR+21;			
	'S','H','3','6','7','3','0','6',	// U8  xdata DeviceName[12]  	_at_ 	SYSINFO_MAP_ADDR+23;
	0x000,0x000,0x000,0x000,					

	'L','I','O','N',					// U8  xdata DeviceChem[12]  	_at_ 	SYSINFO_MAP_ADDR+35;
	0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,				

	0x000,0x000,						// U16 xdata ChemID          	_at_ 	SYSINFO_MAP_ADDR+47;
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg2     _at_	SYSINFO_MAP_ADDR+49;

//充电参数区开始 SubClassID=0x02		langth=18			
	0x010,0x09A,						// U16 xdata OVvol				_at_ 	CHG_PARA_MAP_ADDR;		4250
	0x010,0x036,						// U16 xdata OVRvol         	_at_ 	CHG_PARA_MAP_ADDR+2;	4150
	0x002,								// U8  xdata DelayOV       		_at_ 	CHG_PARA_MAP_ADDR+4;	2
	0x002,								// U8  xdata DelayOVR    		_at_ 	CHG_PARA_MAP_ADDR+5;	2
	0x010,0x068,						// U16 xdata ChgEndvol   	    _at_ 	CHG_PARA_MAP_ADDR+6;	4200	
	0x000,0x064,						// S16 xdata ChgEndCur	      	_at_ 	CHG_PARA_MAP_ADDR+8;	100
	0x005,								// U8  xdata DelayChgEnd   		_at_ 	CHG_PARA_MAP_ADDR+10;	5
	0x000,0x000,0x00B,0x0B8,			// S32 xdata OCCvol 			_at_ 	CHG_PARA_MAP_ADDR+11;	3000
	0x002,								// U8  xdata DelayOCC			_at_ 	CHG_PARA_MAP_ADDR+15;	2
	0x00a,								// U8  xdata DelayOCCR			_at_ 	CHG_PARA_MAP_ADDR+16;	10
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg3     _at_	CHG_PARA_MAP_ADDR+17;

//放电参数区开始 SubClassID=0x03		langth=21
	0x00A,0x08C,					 	// U16 xdata UVvol          	_at_ 	DSG_PARA_MAP_ADDR;		2700
	0x00B,0x0B8,						// U16 xdata UVRvol          	_at_ 	DSG_PARA_MAP_ADDR+2;	3000
	0x002,								// U8  xdata DelayUV        	_at_ 	DSG_PARA_MAP_ADDR+4;	2		// all the delay unit is 500mS
	0x002,								// U8  xdata DelayUVR        	_at_ 	DSG_PARA_MAP_ADDR+5;	2
	0x00B,0x054,						// U16 xdata DsgEndvol       	_at_ 	DSG_PARA_MAP_ADDR+6;	2900
	0x005,								// U8  xdata DelayDsgEnd     	_at_ 	DSG_PARA_MAP_ADDR+8;	5
	0xFF,0xFF,0x0B1,0x0E0,				// U16 xdata OCDvol		  	 	_at_ 	DSG_PARA_MAP_ADDR+9;
	0x002,								// U8  xdata DelayOCD	 	  	_at_ 	DSG_PARA_MAP_ADDR+13;	2
	0xFF,0xFF,0x063,0x0c0,				// S32 xdata OCD2vol		  	_at_ 	DSG_PARA_MAP_ADDR+14;
	0x002,								// U8  xdata DelayOCD2	 	  	_at_ 	DSG_PARA_MAP_ADDR+18;	2
	0x004,								// U8  xdata DelayLoadR	 	  	_at_ 	DSG_PARA_MAP_ADDR+19;	4
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg4     _at_	DSG_PARA_MAP_ADDR+20;

//放电PWM参数区开始 SubClassID=0x04		langth=5
	0x00F,0x0A0,						// U16 xdata DSG1PWMFreq	   	_at_ 	DSG_PWM_PARA_MAP_ADDR;		4000Hz
	0x01e,								// U8  xdata DSG1PWMRatioL   	_at_ 	DSG_PWM_PARA_MAP_ADDR+2;	30%
	0x046,								// U8  xdata DSG1PWMRatioH   	_at_ 	DSG_PWM_PARA_MAP_ADDR+3;	70%				
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg5		_at_ 	DSG_PWM_PARA_MAP_ADDR+4;

//充电温度保护参数开始 SubClassID=0x05	langth=11
	0x00C,0x09F,						// U16 xdata TempOTC      		_at_ 	CHG_TEMP_PARA_MAP_ADDR;		3231-2731=500
	0x00C,0x06D,						// U16 xdata TempOTCR      		_at_ 	CHG_TEMP_PARA_MAP_ADDR+2;	3181-2731=450
	0x00A,0x0AB,						// U16 xdata TempUTC        	_at_ 	CHG_TEMP_PARA_MAP_ADDR+4;	2731
	0x00A,0x0DD,						// U16 xdata TempUTCR       	_at_ 	CHG_TEMP_PARA_MAP_ADDR+6;	2781-2731=50
	0x003,								// U8  xdata DelayOTC      		_at_ 	CHG_TEMP_PARA_MAP_ADDR+8;	3
	0x003,								// U8  xdata DelayOTCR	      	_at_ 	CHG_TEMP_PARA_MAP_ADDR+9;	3
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg6		_at_ 	CHG_TEMP_PARA_MAP_ADDR+10;

//放电温度保护参数开始 SubClassID=0x06	langth=9
	0x00D,0x067,						// U16 xdata TempOTD       	 	_at_ 	DSG_TEMP_PARA_MAP_ADDR;		3431-2731=700
	0x00C,0x0D1,						// U16 xdata TempOTDR       	_at_ 	DSG_TEMP_PARA_MAP_ADDR+2;	3281-2731=550
	0x00A,0x047,						// U16 xdata TempUTD        	_at_ 	DSG_TEMP_PARA_MAP_ADDR+4;	2631-2731=-100
	0x00A,0x079,						// U16 xdata TempUTDR       	_at_ 	DSG_TEMP_PARA_MAP_ADDR+6;	2681-2731=-50
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg7		_at_ 	DSG_TEMP_PARA_MAP_ADDR+8;

//平衡参数区开始 SubClassID=0x08		langth=8
	0x010,0x054,						// U16 xdata BalanceVol      	_at_	BAL_PARA_MAP_ADDR;		4180
	0x000,0x014,						// U16 xdata BalanceVolDiff  	_at_	BAL_PARA_MAP_ADDR+2;	20	
	0x000,0x064,						// S16 xdata BalCurrent			_at_ 	BAL_PARA_MAP_ADDR+4;	100
	0x002,								// U8  xdata BalanceDelay    	_at_ 	BAL_PARA_MAP_ADDR+6;	2
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg8		_at_ 	BAL_PARA_MAP_ADDR+7;

//AFE参数区开始 SubClassID=0x0A			langth=4
	0x074,								// U8  xdata AFEProtectConfig	_at_ 	AFE_PARA_MAP_ADDR;
	0x011,0x030,						// U16 xdata AFEOVvol			_at_ 	AFE_PARA_MAP_ADDR+2;	4400
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg9		_at_ 	AFE_PARA_MAP_ADDR+3;

//校准参数区开始 SubClassID=0x0B		langth=12
	0x00A,0x022,						// U16 xdata VPackGain			_at_	CALI_PARA_MAP_ADDR;		2594
	0x0FF,0x0AE,						// S16 xdata CadcGain			_at_ 	CALI_PARA_MAP_ADDR+2;	-82
	0x000,0x001,						// S16 xdata CadcOffset			_at_	CALI_PARA_MAP_ADDR+4;
	0x000,0x000,						// S16 xdata TS1Offset			_at_	CALI_PARA_MAP_ADDR+6;
	0x000,0x000,						// S16 xdata TS2Offset			_at_	CALI_PARA_MAP_ADDR+8;
	0x000,								// U8  xdata E2ucCalibrated		_at_	CALI_PARA_MAP_ADDR+10;
	RAM_CHECK_DATA,						// U8  xdata ucRamCheckFlg10	_at_	CALI_PARA_MAP_ADDR+11;

//Reserved
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,

	0x05A,0x0A5,				   	 // U16 xdata FlashCheck			_at_ 	DataflashCheck_Map_ADDR;		


};


