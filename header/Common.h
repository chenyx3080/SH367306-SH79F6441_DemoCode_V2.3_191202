#ifndef __COMMON_H
#define __COMMON_H


extern void Delay1ms(U8 delaycnt);
extern void MemorySet(U8 xdata *pt, U8 setval, U8 length);
extern void MemoryCopy(U8 xdata *source, U8 xdata *target, U8 length);
extern void IntoIdle(void);
extern void IntoPD(void);
extern void IntoSleep(void);
extern void ResetInit(void);
extern void ClrRam(void);

#endif