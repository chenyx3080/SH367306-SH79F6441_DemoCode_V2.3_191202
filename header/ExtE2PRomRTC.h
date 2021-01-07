#ifndef	_EXT_E2PROM_RTC_H
#define	_EXT_E2PROM_RTC_H


//#define AFE_CHIP_ID			0x34
#define E2PROM_ID				0xA0

//Define EEPROM Size
#define E2PROM_SIZE				0x10000
#define E2PROM_BOOT_ADDR		0x10000-0x20
#define E2PROM_RTC_ADDR			0x10000-0x10


//Define For RTC Module
#define RTC_ID					0xDE
#define RTC_REG_SECOND			0x00
#define RTC_REG_MINUTE			0x01
#define RTC_REG_HOUR			0x02
#define RTC_REG_DATE			0x03
#define RTC_REG_MONTH			0x04
#define RTC_REG_YEAR			0x05
#define RTC_REG_WEEK			0x06
#define RTC_REG_STATUS			0x07


extern bit RTCReadTime(void);
extern bit E2PRomRead(U16 RdAddr, U8 Length, U8 xdata *RdBuf);
extern bit RTCModifyTime(void);
extern void InitE2PRom(void);
extern void InitRTC(void);

#endif