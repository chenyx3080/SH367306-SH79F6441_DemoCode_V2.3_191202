#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "SH79F6441.h"
#include "ABSACC.H"
#include "INTRINS.H"
#include "C51_TYPE.H"
#include "Main.h"
#include "Uart.h"
#include "Led.h"
#include "Memory.h"
#include "McuFlash.h"
#include "TwiIO.h"
#include "TwiModule.h"
#include "Common.h"
#include "Key.h"
#include "AfeMtp.h"


#define UpEepromWithDelay() {ucFlashWrValid = 0x55; ucUpDataLimitTime = 50;}
#define UpEepromNoDelay() {ucFlashWrValid = 0x55; ucUpDataLimitTime = 0;}

//定义寄存器的Bank
#define BANK0_SEL	INSCON = 0x00;
#define BANK1_SEL	INSCON = 0x40;

//定义I/O
#define DSG1PWM     		P2_5

#define KEY_ON_IO      		P3_1
#define KEY_LED_IO     		P0_1
#define IO_BLEPW			P0_0

#define VOL_CELL_CUT_1380MV		(VOL_CELL_CUT_1200MV+VOL_CELL_CUT_180MV)
#define VOL_CELL_CUT_1200MV		1200
#define VOL_CELL_CUT_180MV		180

#define TIME_50MS_500MS		10
#define TIME_50MS_1S		20
#define TIME_50MS_2S		40
#define TIME_50MS_2250MS	45

#endif

