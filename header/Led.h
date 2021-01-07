#ifndef __LED_H
#define __LED_H

#define LED1		P2_0
#define LED2		P2_1
#define LED3		P2_2
#define LED4		P2_3
#define LED5		P2_4
#define LED_CHARGE  P3_5

#define LEDOn5		LED1=1; LED2=1; LED3=1; LED4=1; LED5=1;
#define LEDOn4		LED1=0; LED2=1; LED3=1; LED4=1; LED5=1;
#define LEDOn3		LED1=0; LED2=0; LED3=1; LED4=1; LED5=1;
#define LEDOn2		LED1=0; LED2=0; LED3=0; LED4=1; LED5=1;
#define LEDOn1		LED1=0; LED2=0; LED3=0; LED4=0; LED5=1;
#define LEDOff		LED1=0; LED2=0; LED3=0; LED4=0; LED5=0;

extern void LEDPowerOn(void);

#endif