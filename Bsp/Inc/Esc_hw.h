#ifndef __ESC_HW_H__
#define __ESC_HW_H__

#include "ecat_def.h"
#include "AX58100.h"

#ifndef ECAT_TIMER_INC_P_MS 
#define ECAT_TIMER_INC_P_MS 1  /*具体数值和HW_GetTimer相关*/
#endif
#define HW_EscReadByte(ByteValue, Address) ((ByteValue) = AX58100_Read8((Address)))
#define HW_EscWriteByte(ByteValue, Address) AX58100_Write8((Address), (ByteValue))

#define HW_EscReadWord(ByteValue, Address) ((ByteValue) = AX58100_Read16((Address)))
#define HW_EscWriteWord(ByteValue, Address) AX58100_Write16((Address), (ByteValue))

// 提供给SSC上层使
void HW_EscRead(MEM_ADDR *pData, UINT16 address, UINT16 len);
void HW_EscWrite(MEM_ADDR *pData, UINT16 address, UINT16 len);

void HW_EscWriteIsr(MEM_ADDR *pData, UINT16 address, UINT16 len);
void HW_EscReadIsr(MEM_ADDR *pData, UINT16 address, UINT16 len);

void HW_EscReadMbxMem(MEM_ADDR *pData, UINT16 address, UINT16 len);
void HW_EscWriteMbxMem(MEM_ADDR *pData, UINT16 address, UINT16 len);

UINT16 HW_GetALEventRegister(void);

// SSC内部调用 获取当前时间戳
MEM_ADDR HW_GetTimer(void);
void HW_ClearTimer(void);

void HW_SetLed(UINT8 runLed, UINT8 errLed);
#endif

