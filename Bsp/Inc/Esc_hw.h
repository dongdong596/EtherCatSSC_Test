#ifndef __ESC_HW_H__
#define __ESC_HW_H__

#include "main.h"
#include "AX58100.h"

// 提供给SSC上层使用
void HW_EscRead(void *pData, uint16_t address, uint16_t len);

void HW_EscWrite(void *pData, uint16_t address, uint16_t len);

uint16_t HW_GetALEventRegister(void);

#define HW_EscReadIsr(pData, address, len)       HW_EscRead((pData), (address), (len))
#define HW_EscWriteIsr(pData, address, len)      HW_EscWrite((pData), (address), (len))

#define HW_EscReadMbxMem(pData, address, len)    HW_EscRead((pData), (address), (len))
#define HW_EscWriteMbxMem(pData, address, len)   HW_EscWrite((pData), (address), (len))

#define HW_EscReadByte(value, address)           ((value) = AX58100_Read8((address)))
#define HW_EscWriteByte(value, address)          AX58100_Write8((address), (uint8_t)(value))
#define HW_EscReadWord(value, address)           ((value) = AX58100_Read16((address)))
#define HW_EscWriteWord(value, address)          AX58100_Write16((address), (uint16_t)(value))

#define HW_EscReadByteIsr(value, address)        HW_EscReadByte((value), (address))
#define HW_GetALEventRegister_Isr()              HW_GetALEventRegister()

#define HW_GetTimer()                            HAL_GetTick()
#define HW_ClearTimer()                          do { } while (0)
#ifndef ECAT_TIMER_INC_P_MS
#define ECAT_TIMER_INC_P_MS                      1
#endif

#define DISABLE_ESC_INT()                        do { } while (0)
#define ENABLE_ESC_INT()                         do { } while (0)
#define ENTER_MBX_CRITICAL                       do { } while (0)
#define LEAVE_MBX_CRITICAL                       do { } while (0)

#endif

