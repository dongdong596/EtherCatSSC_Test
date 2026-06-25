#include "Esc_hw.h"

MEM_ADDR s_timerBase = 0;

void HW_EscRead(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    AX58100_ReadBuffer(address, (uint8_t *)pData, len);
}

void HW_EscWrite(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    AX58100_WriteBuffer(address, (uint8_t *)pData, len);
}

UINT16 HW_GetALEventRegister(void)
{
    return AX58100_Read16(0x0220);
}

MEM_ADDR HW_GetTimer(void)
{
    return HAL_GetTick() - s_timerBase;
}

void HW_ClearTimer(void)
{
    s_timerBase = HAL_GetTick();
}

void HW_EscWriteIsr(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    HW_EscWrite(pData, address, len);
}

void HW_EscReadIsr(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    HW_EscRead(pData, address, len);
}


void HW_EscReadMbxMem(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    HW_EscRead(pData, address, len);
}
void HW_EscWriteMbxMem(MEM_ADDR *pData, UINT16 address, UINT16 len)
{
    HW_EscWrite(pData, address, len);
}

void HW_SetLed(UINT8 runLed, UINT8 errLed)
{

}
