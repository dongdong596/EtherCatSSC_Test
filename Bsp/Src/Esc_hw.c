#include "Esc_hw.h"

void HW_EscRead(uint8_t *pData, uint16_t address, uint16_t len)
{
    AX58100_ReadBuffer(address, pData, len);
}

void HW_EscWrite(uint8_t *pData, uint16_t address, uint16_t len)
{
    AX58100_WriteBuffer(address, pData, len);
}

uint16_t HW_GetALEventRegister(void)
{
    return AX58100_Read16(0x0220);
}


