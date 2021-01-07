#ifndef	_SCI_H
#define	_SCI_H

#define AFE_CHIP_ID 		(0x1B<<1)						 //SH367306_ID

#define TRY_TIMES     		5
#define AFE_WDT_DISABLE		REG.AFESCONF1 &= ~0x10; TwiWriteAFE(AFE_SCONF1, &REG.AFESCONF1);	//¹Ø±ÕWDT	
#define AFE_Set				REG.AFEINTEN=0x6C;REG.AFESCONF1=0x40;REG.AFESCONF2=0x00;REG.AFESCONF3=0xF8;REG.AFESCONF4=0x00;REG.AFESCONF5=0x00;REG.AFESCONF6=0x70 ;REG.AFESCONF7=0x01;REG.AFESCONF8=0x03;REG.AFESCONF9=0xff;REG.AFESCONF10=0x00;

//Define AFE register addr
#define AFE_FLAG1			0x00
#define AFE_FLAG2	    	0x01
#define AFE_BSTATUS	    	0x02
#define AFE_INT_EN		    0x03
#define AFE_SCONF1 			0x04
#define AFE_SCONF2			0x05
#define AFE_SCONF3    		0x06
#define AFE_SCONF4			0x07
#define AFE_SCONF5			0x08
#define AFE_SCONF6			0x09
#define AFE_SCONF7			0x0A
#define AFE_SCONF8			0x0B
#define AFE_SCONF9			0x0C
#define AFE_SCONF10			0x0D

#define AFE_CELL1H			0x0E
#define AFE_CELL1L			0x0F
#define AFE_CELL2H			0x10
#define AFE_CELL2L			0x11
#define AFE_CELL3H			0x12									    
#define AFE_CELL3L			0x13
#define AFE_CELL4H			0x14
#define AFE_CELL4L			0x15
#define AFE_CELL5H			0x16
#define AFE_CELL5L			0x17
#define AFE_CELL6H			0x18
#define AFE_CELL6L			0x19
#define AFE_CELL7H			0x1A
#define AFE_CELL7L			0x1B
#define AFE_CELL8H			0x1C
#define AFE_CELL8L			0x1D
#define AFE_CELL9H			0x1E
#define AFE_CELL9L			0x1F
#define AFE_CELL10H			0x20
#define AFE_CELL10L			0x21
#define AFE_TS1H			0x22
#define AFE_TS1L			0x23
#define AFE_TS2H			0x24
#define AFE_TS2L			0x25
#define AFE_TEMP1H			0x26
#define AFE_TEMP1L			0x27
#define AFE_TEMP2H			0x28
#define AFE_TEMP2L			0x29
#define AFE_CURH			0x2A
#define AFE_CURL  			0x2B

#define OV_DELAY_CNT        (E2ucDelayOV*20)
#define OVR_DELAY_CNT       (E2ucDelayOVR*20) 
#define UV_DELAY_CNT        (E2ucDelayUV*20)
#define UVR_DELAY_CNT       (E2ucDelayUVR*20)
#define TEMPE_DELAY_CNT     (E2ucDelayTemp*40)
#define TEMPER_DELAY_CNT    (E2ucDelayTemp*40)
#define OCC_DELAY_CNT       (E2ucDelayOCC<<3)
#define OCD_DELAY_CNT       (E2ucDelayOCD<<3)
#define OCCR_DELAY_CNT      (E2ucDelayOCCR*40)
#define OCDR_DELAY_CNT      (E2ucDelayOCCR*40)
#define BAL_DELAY_CNT		(E2ucBalanceDelay*10)

#define BALANCE_ENABLE  	1
#define BALANCE_START   	2
#define BALANCING       	3
#define BALANCE_DISABLE 	4
#define BALANCE_NULL    	5

extern bit TwiWriteAFE(U8 WrAddr, U8 xdata *WrBuf);
extern bit TWIReadAFE(U8 RdAddr, U8 xdata *RdBuf);
extern bit InitAFE(void);
extern void ClearAFEFlg(void);
extern bit WaitADCConvert(void);
extern void PorOnProtect(void);
extern void IntoPowerDown(void);


#endif