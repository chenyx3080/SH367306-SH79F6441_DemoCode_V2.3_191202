#ifndef __MAIN_H
#define __MAIN_H

extern void AFERamCheck(void);
extern void	AlarmProcess(void);
extern void BatteryInfoManage(void);
extern void BalProcess(void);
extern void	BalManage(void)	;
extern void CellOpenProcess(void);
extern void CurrProcess(void);
extern void	CaliProcess(void);
extern bit CaliCurOffsetSub(void);
extern void CloseBal(void);
extern void Delay1ms(U8 delaycnt);
extern void E2PRomBKCheck(void);
extern void E2PRomBKProcess(void);
extern void FlashProcess(void);
extern void GaugeManage(void);
extern void Initial(void);
extern void InitClk(void);
extern void InitIRQ(void);
extern void InitSysPara(void);
extern void RamCheckProcess(void);
extern void ISPProcess(void);
extern bit 	TwiWriteAFE(U8 WrAddr, U8 xdata *WrBuf);
extern void KeyProcess(void);
extern void	LEDPowerOn(void);
extern void LEDPowerOff(void);
extern void LowPowerCheck(void);
extern void LowPowerProcess(void);
extern void ResetInit(void);
extern void ResetAFE(void);
extern void ProtectProcess(void);
extern void VolProcess(void);
extern void WriteFlashCheck(void);
extern void WakeUpProcess(void);


#endif