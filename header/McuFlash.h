#ifndef __MCU_FLASH_H
#define __MCU_FLASH_H


#define DATAFLASH_MAP_ADDR	        0x0000
#define DATAFLASH_ADDR				0x0000
#define	DATAFLASH_ADDR2             (DATAFLASH_ADDR + 512)
#define DATAFLASH_OK_FLG1_ADDR      (DATAFLASH_ADDR + 510)
#define DATAFLASH_OK_FLG2_ADDR      (DATAFLASH_ADDR2 + 510)


/**************************************************************************************/
//DataFlash�������ַ����
/**************************************************************************************/
//ϵͳ��Ϣ����ʼ SubClassID=0x00
#define SYS_PARA_MAP_ADDR		    0x0000
#define SYS_PARA_LEN				48

//�û��Զ����������ʼ SubClassID=0x01
#define SYSINFO_MAP_ADDR			SYS_PARA_MAP_ADDR+SYS_PARA_LEN
#define SYSINFO_LEN					50

//����������ʼ SubClassID=0x02
#define CHG_PARA_MAP_ADDR			SYSINFO_MAP_ADDR+SYSINFO_LEN	
#define	CHG_PARA_LEN				18

//�ŵ��������ʼ SubClassID=0x03
#define	DSG_PARA_MAP_ADDR			CHG_PARA_MAP_ADDR+CHG_PARA_LEN
#define DSG_PARA_LEN				21

//�ŵ�PWM��������ʼ SubClassID=0x04
#define DSG_PWM_PARA_MAP_ADDR		DSG_PARA_MAP_ADDR+DSG_PARA_LEN
#define DSG_PWM_PARA_LEN			5

//����¶ȱ���������ʼ SubClassID=0x05
#define CHG_TEMP_PARA_MAP_ADDR		DSG_PWM_PARA_MAP_ADDR+DSG_PWM_PARA_LEN
#define CHG_TEMP_PARA_LEN			11

//�ŵ��¶ȱ���������ʼ SubClassID=0x06
#define DSG_TEMP_PARA_MAP_ADDR		CHG_TEMP_PARA_MAP_ADDR+CHG_TEMP_PARA_LEN
#define	DSG_TEMP_PARA_LEN			9

//ƽ���������ʼ SubClassID=0x08
#define	BAL_PARA_MAP_ADDR			DSG_TEMP_PARA_MAP_ADDR+DSG_TEMP_PARA_LEN
#define	BAL_PARA_LEN				8

//AFE��������ʼ SubClassID=0x0A
#define	AFE_PARA_MAP_ADDR			BAL_PARA_MAP_ADDR+BAL_PARA_LEN
#define	AFE_PARA_LEN				4

//У׼��������ʼ SubClassID=0x0B
#define CALI_PARA_MAP_ADDR			AFE_PARA_MAP_ADDR+AFE_PARA_LEN
#define	CALI_PARA_LEN				12

#define RESERVED_DATA_MAP_ADDR		CALI_PARA_MAP_ADDR+CALI_PARA_LEN
#define	RESERVED_DATA_LEN			(510-(RESERVED_DATA_MAP_ADDR))

#define DataflashCheck_Map_ADDR		0xfe
#define DataflashCheck_LEN			0x0002


//Define system macro
#define	CALI_FLAG					0xaa


extern void Flash_wirte_one_byte(U16 xdata ADRS,U8 xdata WDAT);
extern BOOL WriteMcuFlash(U16 Saddr);
extern BOOL BlackE2CheckUp(U16 Saddr);
extern BOOL WriteE2Sector(U16 Saddr);
extern BOOL E2DataCheckUp(U16 Saddr);
extern void FlashProcess(void);
extern BOOL ReadMcuFlash(U16 SourceAddr, U8 xdata *DestAddr, U16 Length);

#endif