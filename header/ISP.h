#ifndef __ISP_H
#define __ISP_H


#define STATE_OK				0x5a
#define STATE_ERROR				0xff

#define UART_ERASE				0xfe
#define UART_PROGRAM			0xfd
#define UART_BLANK_CHECK		0xfc
#define UART_CHECKSUM_CHECK		0xfb
#define UART_READ				0xfa
#define UART_READ4B				0xf9
#define UART_SOFT_RESET			0xf8

#define ISP_COMMAND				0x55  		//	 0xB0
//#define CMD_HANDSHAKE			0xA0
#define CMD_ISP_HANDSHAKE		0x55

#define CODE_SECTOR             1           //512Bytes
#define CODE_SIZE               122         //64KBytes = 512byte*128，最后2Kbyte用于ISP程序，预留4K EEPROM

#define E2P_SECTOR              1           //512Bytes(EEPROM One Sector Size，单位为512Bytes)
#define E2P_SIZE                8           //8KBytes(EEPROM all Sector Size，单位为512Bytes)

#define PROGRAM_LENGTH          64


extern U8 xdata ucUartBuf[];
extern U8 xdata ucUartBufPT;
extern U8 xdata ucUartSndLength;

void ISPProcessCMD(void);
//void ClrIspUartBuf(void);
void ISPProcess(void);

#endif