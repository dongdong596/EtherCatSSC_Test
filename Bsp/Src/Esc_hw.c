#include "Esc_hw.h"
#include "ecatappl.h"

void HW_EscRead(void *pData, uint16_t address, uint16_t len)
{
    AX58100_ReadBuffer(address, (uint8_t *)pData, len);
}

void HW_EscWrite(void *pData, uint16_t address, uint16_t len)
{
    AX58100_WriteBuffer(address, (const uint8_t *)pData, len);
}

uint16_t HW_GetALEventRegister(void)
{
    return AX58100_Read16(0x0220);
}

UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize)
{
    if (pInputSize != 0)
    {
        *pInputSize = 0;
    }

    if (pOutputSize != 0)
    {
        *pOutputSize = 0;
    }

    return 0;
}

UINT16 APPL_StartMailboxHandler(void)
{
    return 0;
}

UINT16 APPL_StopMailboxHandler(void)
{
    return 0;
}

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    (void)pIntMask;
    return 0;
}

UINT16 APPL_StopInputHandler(void)
{
    return 0;
}

UINT16 APPL_StartOutputHandler(void)
{
    return 0;
}

UINT16 APPL_StopOutputHandler(void)
{
    return 0;
}

void APPL_AckErrorInd(UINT16 stateTrans)
{
    (void)stateTrans;
}

void APPL_InputMapping(UINT16 *pData)
{
    (void)pData;
}

void APPL_OutputMapping(UINT16 *pData)
{
    (void)pData;
}

void APPL_Application(void)
{
}

