#ifndef	_TWI_IO_H
#define	_TWI_IO_H

//#define TWI_IO_OPERATE

#ifdef TWI_IO_OPERATE
//Define For I2C Driver

#define AFE_CHIP_ID 			(0x1B<<1)						 //SH367306_ID

#define TRY_TIMES     5

#define RTC_REG_STATUS			0x07

#define SDA_BIT			0x10
#define SCL_BIT			0x20
#define SDA				P0_4
#define SCL				P0_5

#define TWI_CLK_OUT		P0CR |= SCL_BIT;
#define TWI_CLK_IN		P0CR &= ~SCL_BIT;
#define TWI_CLK_HIGH	TWI_CLK_IN; SCL = 1;
#define TWI_CLK_LOW	    TWI_CLK_OUT; SCL = 0;

#define TWI_DAT_OUT		P0CR |= SDA_BIT;
#define TWI_DAT_IN      P0CR &= ~SDA_BIT;
#define TWI_DAT_HIGH	TWI_DAT_IN; SDA = 1;
#define TWI_DAT_LOW	    TWI_DAT_OUT; SDA = 0;

#define TWI_RD_DAT		SDA
#define TWI_RD_CLK		SCL

extern void InitTwi(void);
extern bit TwiRead(U8 SlaveID, U16 RdAddr, U8 Length, U8 xdata *RdBuf);
extern bit TwiWrite(U8 SlaveID, U16 WrAddr, U8 Length, U8 xdata *WrBuf);
extern U8 CRC8cal(U8 *p, U8 counter);


#endif

#endif