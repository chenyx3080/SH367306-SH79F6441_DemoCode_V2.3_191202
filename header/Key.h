#ifndef __KEY_H__
#define __KEY_H__

#define KEY_ON_S			0x01
#define KEY_ON_L			0x11
#define KEY_ON_LC			0x21
#define KEY_ON_LE			0x41

#define KEY_LED_S			0x02
#define KEY_LED_L			0x12
#define KEY_LED_LC			0x22
#define KEY_LED_LE			0x42

#define KEY_STATE_S			0		//Key State
#define KEY_STATE_L			1
#define KEY_STATE_LC		2
#define KEY_STATE_LE		4

#define KEY_ON				0x01	//Key Value
#define KEY_LED 			0x02
#define KEYVAL_NULL			0x0F

#define KEY_S_TIME			2		//(2+1)*25ms
#define KEY_L_TIME			80		//80*25ms
#define KEY_LC_TIME			100		//100*25ms


extern void ScanKey();

#endif