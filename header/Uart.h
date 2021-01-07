#ifndef __UART_H
#define __UART_H

#define UART_IRQ_ENABLE			IEN0|=0x10;
#define UART_IRQ_DISABLE		IEN0&=~0x10;

#define UART_SLAVE_ADDR			0x00
#define UART_CMD_NO				0x01
#define UART_LENGTH				0x02
#define UART_DATA				0x03

#define CMD_RD_EEPROM       	0x78

//主信息扫描命令字
#define CELL1					0X01
#define CELL2					0X02
#define CELL3					0X03
#define CELL4					0X04
#define CELL5					0X05
#define CELL6					0X06
#define CELL7					0X07
#define CELL8					0X08
#define CELL9					0X09
#define CELL10					0X0A
#define TOTAL_VOLTAGE			0X0B
#define EXT_TEMP1				0X0C
#define EXT_TEMP2				0X0D
#define DIE_TEMP1				0X0E
#define DIE_TEMP2				0X0F
#define CADC_CURRENT			0X10
#define FULL_CHG_CAP			0X11
#define REMAIN_CAP				0X12
#define R_SOC					0X13
#define CYCLE_COUNT				0X14
#define PACK_STATUS				0X15
#define BATTERY_STATUS			0X16
#define PACK_CONFIG				0X17
#define MANUFACTURE_COMMAND		0X18

//MCU参数区子命令号
#define	DATA_FLASH_COMMAND		0x77
#define SUB_PAGE1				0x78
#define SUB_PAGE2				0x79
#define SUB_PAGE3				0x7A
#define SUB_PAGE4				0x7B
#define SUB_PAGE5				0x7C
#define SUB_PAGE6				0x7D
#define SUB_PAGE7				0x7E
#define SUB_PAGE8				0x7F

#define RTC_SUBID				0x0C

//校准命令字
#define CALI_VOL_COMMAND		0xA0
#define CALI_TS1_COMMAND		0xA1
#define CALI_TS2_COMMAND		0xA2
#define CALI_CUR_COMMAND		0xA3
#define CALI_ZERO_CUR_COMMAND	0xA4
#define CALI_RTC_COMMAND		0xAF

#define CMD_E2PROM_ERASE 		0xB0
#define CMD_E2PROM_ERASE_4K 	0xB1

#define UART_SEND_ACK			REN=0;SBUF=CMD_VALID_ACK;
#define UART_SEND_NACK			REN=0;SBUF=CMD_INVALID_ACK;
#define UART_SEND_DATA			REN=0;SBUF=ucUartBuf[ucUartBufPT];

#define CMD_VALID_ACK			0x5A
#define CMD_INVALID_ACK			0xFF

extern void InitUART0(void);

#endif