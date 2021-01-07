#ifndef	_TWI_MODULE_H
#define	_TWI_MODULE_H

#define TWI_MODULE_OPERATE

#ifdef TWI_MODULE_OPERATE

#define AFE_CHIP_ID 			(0x1B<<1)						 //SH367306_ID
#define HTimeoutChk()     		TWITOUT |= 0xc0; TWISTA |=0x01; TWICON |=0X01;

extern void InitTwi(void);
extern bit TwiRead(U8 SlaveID, U16 RdAddr, U8 Length, U8 xdata *RdBuf);
extern bit TwiWrite(U8 SlaveID, U16 WrAddr, U8 Length, U8 xdata *WrBuf);
extern U8 CRC8cal(U8 *p, U8 counter);

#endif

#endif