#ifndef __ESC_HW_H__
#define __ESC_HW_H__

#include "main.h"
#include "AX58100.h"

// 提供给SSC上层使用
void HW_EscRead(uint8_t *pData, uint16_t address, uint16_t len);

void HW_EscWrite(uint8_t *pData, uint16_t address, uint16_t len);

uint16_t HW_GetALEventRegister(void);

#endif

