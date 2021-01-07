/*--------------------------------------------------------------------------
REG79F6441.H

Header file for generic SH79xx series microcontroller.
Copyright (c) 1996-2014 Sionwealth Electronic and Sinowealth Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef REG79F6441_H
#define REG79F6441_H

/*-------------------------- BYTE Register --------------------------*/
/* CPU */
sfr ACC          = 0xE0;
sfr B            = 0xF0;
sfr AUXC         = 0xF1;
sfr PSW          = 0xD0;
sfr SP           = 0x81;
sfr DPL          = 0x82;
sfr DPH          = 0x83;
sfr16 DPTR       = 0x82;
sfr DPL1         = 0x84;
sfr DPH1         = 0x85;
sfr16 DPTR1      = 0x84;
sfr INSCON       = 0x86;

/* power */
sfr PCON         = 0x87;
sfr SUSLO        = 0x8E;

/* FLASH */
sfr IB_OFFSET    = 0xFB;
sfr IB_DATA      = 0xFC;
sfr IB_CON1      = 0xF2;
sfr IB_CON2      = 0xF3;
sfr IB_CON3      = 0xF4;
sfr IB_CON4      = 0xF5;
sfr IB_CON5      = 0xF6;
sfr XPAGE        = 0xF7;
sfr FLASHCON     = 0xA7;

/* WDT */
sfr RSTSTAT      = 0xB1;

/* CLKCTRL */
sfr CLKCON       = 0xB2;

/* INTERRUPT */
sfr IEN0         = 0xA8;
sfr IEN1         = 0xA9;
sfr IEN2         = 0xAA;
sfr IENC         = 0xBA;
sfr IPL0         = 0xB8;
sfr IPH0         = 0xB4;
sfr IPL1         = 0xB9;
sfr IPH1         = 0xB5;
sfr EXF1         = 0xD8;
sfr EXCON        = 0x8B;
sfr EXF0         = 0xE8;
sfr TCON         = 0x88;

/* TWI */
sfr TWICON       = 0xC8;
sfr TWISTA       = 0xD1;
sfr TWIBR        = 0x8A;
sfr TWITOUT      = 0xE6;
sfr TWIDAT       = 0x8D;
sfr TWIADR       = 0x8C;
sfr TWIAMR       = 0x8F;
sfr TWTFREE      = 0x89;

/* PORT */
sfr P0           = 0x80;
sfr P1           = 0x90;
sfr P2           = 0xA0;
sfr P3           = 0xB0;
sfr P4           = 0xC0;
sfr P5           = 0x80;   //BANK1
sfr P0CR         = 0xE1;
sfr P1CR         = 0xE2;
sfr P2CR         = 0xE3;
sfr P3CR         = 0xE4;
sfr P4CR         = 0xE5;
sfr P5CR         = 0x8A;   //BANK1
sfr P0PCR        = 0xE9;
sfr P1PCR        = 0xEA;
sfr P2PCR        = 0xEB;
sfr P3PCR        = 0xEC;
sfr P4PCR        = 0xED;
sfr P5PCR        = 0x8B;   //BANK1
sfr PIMS0        = 0xD2;
sfr PIMS1        = 0xD9;
sfr PIMS2        = 0xDB;

/* TIMER */
sfr T3CON        = 0x88;   //BANK1
sfr TL3          = 0x8C;   //BANK1
sfr TH3          = 0x8D;   //BANK1
sfr16 T3_16      = 0x8C;   //BANK1

/* EUART */
sfr SCON         = 0x98;
sfr SBUF         = 0x99;
sfr SADEN        = 0x9B;
sfr SADDR        = 0x9A;
sfr SBRTL        = 0x9C;
sfr SBRTH        = 0x9D;
sfr16 SBRT_16    = 0x9C;
sfr SFINE        = 0x9E;
sfr SCON1        = 0xA0;    //BANK1
sfr SBUF1        = 0xA1;    //BANK1
sfr SADEN1       = 0xA3;    //BANK1
sfr SADDR1       = 0xA2;    //BANK1
sfr SBRTL1       = 0xA4;    //BANK1
sfr SBRTH1       = 0xA5;    //BANK1
sfr16 SBRT1_16   = 0xA4;    //BANK1
sfr SFINE1       = 0xA6;    //BANK1
sfr PCON1        = 0xA7;    //BANK1
sfr SCON2        = 0x90;    //BANK1
sfr SBUF2        = 0x91;    //BANK1
sfr SADEN2       = 0x93;    //BANK1
sfr SADDR2       = 0x92;    //BANK1
sfr SBRTL2       = 0x94;    //BANK1
sfr SBRTH2       = 0x95;    //BANK1
sfr16 SBRT2_16   = 0x94;    //BANK1
sfr SFINE2       = 0x96;    //BANK1
sfr PCON2        = 0x97;    //BANK1

/* SPI */
sfr SPCON        = 0xA2;
sfr SPSTA        = 0xF8;
sfr SPDAT        = 0xA3;

/* ADC */
sfr ADCON1       = 0x93;
sfr ADCON2       = 0x92;
sfr SEQCON       = 0x91;
sfr SEQCHx       = 0x9F;
sfr ADDxL        = 0x96;
sfr ADDxH        = 0x97;
sfr16 ADDx_16    = 0x96;
sfr ADCH1        = 0x95;
sfr ADCH2        = 0xA6;
sfr ADT          = 0x94;

/* PWM */
sfr PWM0CON      = 0xC7;
sfr PWM1CON      = 0xB6;
sfr PWM2CON      = 0xB7;
sfr PWM0PH       = 0xCD;
sfr PWM0PL       = 0xCC;
sfr16 PWM0P_16   = 0xCC;
sfr PWM1PH       = 0xAF;
sfr PWM1PL       = 0xAE;
sfr16 PWM1P_16   = 0xAE;
sfr PWM2PH       = 0xBD;
sfr PWM2PL       = 0xBC;
sfr16 PWM2P_16   = 0xBC;
sfr PWM0DH       = 0xCF;
sfr PWM0DL       = 0xCE;
sfr16 PWM0D_16   = 0xCE;
sfr PWM1DH       = 0xA5;
sfr PWM1DL       = 0xA4;
sfr16 PWM1D_16   = 0xA4;
sfr PWM2DH       = 0xBF;
sfr PWM2DL       = 0xBE;
sfr16 PWM2D_16   = 0xBE;

/* PCA */
sfr P0CF         = 0x98;     //BANK1
sfr P0CMD        = 0x99;     //BANK1
sfr P0CPM0       = 0x9A;     //BANK1
sfr P0CPM1       = 0x9B;     //BANK1
sfr P0TOPL       = 0x9E;     //BANK1
sfr P0TOPH       = 0x9F;     //BANK1
sfr16 P0TOP_16   = 0x9E;     //BANK1
sfr P0CPL0       = 0x9C;     //BANK1
sfr P0CPH0       = 0x9D;     //BANK1
sfr16 P0CP0_16   = 0x9C;     //BANK1
sfr P0CPL1       = 0xD4;     //BANK1
sfr P0CPH1       = 0xD5;     //BANK1
sfr16 P0CP1_16   = 0xD4;     //BANK1
sfr PCACON       = 0xD8;     //BANK1
sfr P0FORCE      = 0xDC;     //BANK1
sfr P1CF         = 0xC0;     //BANK1
sfr P1CMD        = 0xC1;     //BANK1
sfr P1CPM0       = 0xC2;     //BANK1
sfr P1CPM1       = 0xC3;     //BANK1
sfr P1TOPL       = 0xC6;     //BANK1
sfr P1TOPH       = 0xC7;     //BANK1
sfr16 P1TOP_16   = 0xC6;     //BANK1
sfr P1CPL0       = 0xC4;     //BANK1
sfr P1CPH0       = 0xC5;     //BANK1
sfr16 P1CP0_16   = 0xC4;     //BANK1
sfr P1CPL1       = 0xE4;     //BANK1
sfr P1CPH1       = 0xE5;     //BANK1
sfr16 P1CP1_16   = 0xE4;     //BANK1
sfr P1FORCE      = 0xEC;     //BANK1
sfr P2CF         = 0xC8;     //BANK1
sfr P2CMD        = 0xC9;     //BANK1
sfr P2CPM0       = 0xCA;     //BANK1
sfr P2CPM1       = 0xCB;     //BANK1
sfr P2TOPL       = 0xCE;     //BANK1
sfr P2TOPH       = 0xCF;     //BANK1
sfr16 P2TOP_16   = 0xCE;     //BANK1
sfr P2CPL0       = 0xCC;     //BANK1
sfr P2CPH0       = 0xCD;     //BANK1
sfr16 P2CP0_16   = 0xCC;     //BANK1
sfr P2CPL1       = 0xF4;     //BANK1
sfr P2CPH1       = 0xF5;     //BANK1
sfr16 P2CP1_16   = 0xF4;     //BANK1
sfr P2FORCE      = 0xFC;     //BANK1

/* LPD*/
sfr LPDCON       = 0xB3;
sfr LPDSEL       = 0xBB;

/* CRC */
sfr CRCCON       = 0xC1;
sfr CRCDH        = 0xC3;
sfr CRCDL        = 0xC2;
sfr16 CRCD_16    = 0xC2;
sfr CRCSTAL      = 0xD4;
sfr CRCSTAH      = 0xD5;
sfr16 CRCSTA_16  = 0xD4;
sfr CRCSTOL      = 0xDC;
sfr CRCSTOH      = 0xDD;
sfr16 CRCSTO_16  = 0xDC;

/* LCM */
sfr UART0CR      = 0xC4;
sfr UART1CR      = 0xC5;
sfr TWICR        = 0xC6;
sfr PWMCR        = 0xCA;
sfr CEXCR        = 0xCB;
sfr ECICR        = 0xC9;

/*--------------------------  BIT Register --------------------------*/
/* SPSTA */
sbit SPEN  = 0xFF;
sbit SPIF  = 0xFE;
sbit MODF  = 0xFD;
sbit WCOL  = 0xFC;
sbit RXOV  = 0xFB;

/* B */

/*  EXF0  */
sbit IT41 = 0xEF; 
sbit IT40 = 0xEE;
sbit IT31 = 0xED;
sbit IT30 = 0xEC;
sbit IT21 = 0xEB;
sbit IT20 = 0xEA;
sbit IE3  = 0xE9;
sbit IE2  = 0xE8;
/* ACC */

/*  EXF1  */
sbit IF47 = 0xDF;
sbit IF46 = 0xDE;
sbit IF45 = 0xDD;
sbit IF44 = 0xDC; 
sbit IF43 = 0xDB;
sbit IF42 = 0xDA;
sbit IF41 = 0xD9;
sbit IF40 = 0xD8;

/*  PSW   */
sbit CY  = 0xD7;
sbit AC  = 0xD6;
sbit F0  = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV  = 0xD2;
sbit F1  = 0xD1;
sbit P   = 0xD0;

/*TWICON*/
sbit TOUT  = 0xCF;
sbit ENTWI = 0xCE;
sbit STA   = 0xCD;
sbit STO   = 0xCC;
sbit TWINT = 0xCB;
sbit AA    = 0xCA;
sbit TFREE = 0xC9;
sbit EFREE = 0xC8;

/* P5 */
sbit P5_0 = P5^0;    //BANK1
sbit P5_1 = P5^1;    //BANK1


/* P4 */
sbit P4_0 = P4^0;
sbit P4_1 = P4^1;
sbit P4_2 = P4^2;
sbit P4_3 = P4^3;
sbit P4_4 = P4^4;
sbit P4_5 = P4^5;
sbit P4_6 = P4^6;
sbit P4_7 = P4^7;

/*  IPL0   */
sbit PINTL   = 0xBF; 
sbit PADCL   = 0xBE;
sbit PT3L    = 0xBD;
sbit PS0L    = 0xBC;
sbit PCF1L   = 0xBB;
sbit PX1L    = 0xBA;
sbit PCF0L   = 0xB9;
sbit PX0L    = 0xB8;

/* P3 */
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

/*  IEN0   */
sbit EA     = 0xAF;
sbit EADC   = 0xAE;
sbit ET3    = 0xAD;
sbit ES0    = 0xAC;
sbit EPCA1  = 0xAB;
sbit EX1    = 0xAA;
sbit EPCA0  = 0xA9;
sbit EX0    = 0xA8;

/* P2 */
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7; 

/*  SCON  */
sbit SM0_FE    = 0x9F;
sbit SM1_RXOV  = 0x9E;
sbit SM2_TXCOL = 0x9D;
sbit REN       = 0x9C;
sbit TB8       = 0x9B;
sbit RB8       = 0x9A;
sbit TI        = 0x99;
sbit RI        = 0x98;

/* P1 */
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

/*  TCON  */

sbit IE1  = 0x8B;   
sbit IT1  = 0x8A;   
sbit IE0  = 0x89;    
sbit IT0  = 0x88;   

/* P0 */
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;

/*  PCACON  */
sbit PR2 = 0xDA;    //BANK1
sbit PR1 = 0xD9;    //BANK1
sbit PR0 = 0xD8;    //BANK1

/*  P2CF  */
sbit CF2    = 0xCF;  //BANK1
sbit P2CCF1 = 0xC9;  //BANK1
sbit P2CCF0 = 0xC8;  //BANK1

/*  P1CF  */
sbit CF1    = 0xC7;  //BANK1
sbit P1CCF1 = 0xC1;  //BANK1
sbit P1CCF0 = 0xC0;  //BANK1

/*  SCON1  */          
sbit SM10_FE1    = 0xA7;   //BANK1
sbit SM11_RXOV1  = 0xA6;   //BANK1
sbit SM12_TXCOL1 = 0xA5;   //BANK1
sbit REN1        = 0xA4;   //BANK1
sbit TB81        = 0xA3;   //BANK1
sbit RB81        = 0xA2;   //BANK1
sbit TI1         = 0xA1;   //BANK1
sbit RI1         = 0xA0;   //BANK1

/*  P0CF  */          
sbit CF0    = 0x9F;   //BANK1
sbit P0CCF1 = 0x99;   //BANK1
sbit P0CCF0 = 0x98;   //BANK1

/*  SCON2  */          
sbit SM20_FE2    = 0x97;  //BANK1
sbit SM21_RXOV2  = 0x96;  //BANK1
sbit SM22_TXCOL2 = 0x95;  //BANK1
sbit REN2        = 0x94;  //BANK1
sbit TB82        = 0x93;  //BANK1
sbit RB82        = 0x92;  //BANK1
sbit TI2         = 0x91;  //BANK1
sbit RI2         = 0x90;  //BANK1

/*  T3CON  */
sbit TF3         = 0x8F;  //BANK1
sbit T3PS1       = 0x8D;  //BANK1
sbit T3PS0       = 0x8C;  //BANK1
sbit TR3         = 0x8A;  //BANK1
sbit T3CLKS1     = 0x89;  //BANK1
sbit T3CLKS0     = 0x88;  //BANK1

#endif
