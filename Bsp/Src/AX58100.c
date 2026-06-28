#include "AX58100.h"
#include "main.h"

volatile uint16_t g_ax58100_escType;
volatile uint16_t g_ax58100_alEvent;
volatile uint16_t g_ax58100_alStatus;
volatile uint8_t g_ax58100_sm0Pass;
volatile uint8_t g_ax58100_sm1Pass;
volatile uint8_t g_ax58100_sm2Pass;
volatile uint8_t g_ax58100_sm3Pass;
volatile uint8_t g_ax58100_allPass;
volatile uint16_t g_ax58100_testAddr;
volatile uint16_t g_ax58100_testLen;
volatile uint16_t g_ax58100_failIndex;
volatile uint8_t g_ax58100_testTx[128];
volatile uint8_t g_ax58100_testRx[128];

static void AX58100_WaitSpiIdle(void)
{
    while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY) == SET)
    {
        /* code */
    }
}

static void AX58100_BuildAddrCmd(uint16_t addr, uint8_t cmd, uint8_t *txBuf)
{
    txBuf[0] = (uint8_t)((addr >> 5) & 0xFF);
    txBuf[1] = (uint8_t)(((addr & 0x1F) << 3) | (cmd & 0x07));
}

void AX58100_WriteBuffer(uint16_t addr, const uint8_t *buf, uint16_t len)
{
    uint8_t tx[2];

    if (buf == NULL || len == 0)
    {
        return;
    }

    AX58100_BuildAddrCmd(addr, AX58100_CMD_WRITE, tx);

    AX58100_CS_LOW();

    HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)buf, len, HAL_MAX_DELAY);

    AX58100_WaitSpiIdle();
    AX58100_CS_HIGH();
}

void AX58100_ReadBuffer(uint16_t addr, uint8_t *buf, uint16_t len)
{
    uint8_t txBuf[2];
    uint8_t stopFlag = 0;
    uint16_t i;
    if (buf == NULL || len == 0)
    {
        return;
    }
    
    AX58100_BuildAddrCmd(addr, AX58100_CMD_READ_BLOCK, txBuf);

    AX58100_CS_LOW();

    HAL_SPI_Transmit(&hspi1, txBuf, 2, HAL_MAX_DELAY);

    // 10个NOP 确保AX58100准备好发送数据
    for (i = 0; i < 10; i++)
    {
        __NOP();
    }
    // __NOP();
    for ( i = 0; i < len; i++)
    {
        stopFlag = (i == (len - 1)) ? 0xFF : 0x00; // 0xFF 为读取结束标志位
        HAL_SPI_TransmitReceive(&hspi1, &stopFlag, &buf[i], 1, HAL_MAX_DELAY);
    }
    AX58100_WaitSpiIdle();
    AX58100_CS_HIGH();
    
}

uint8_t AX58100_Read8(uint16_t addr)
{
    uint8_t value = 0;
    AX58100_ReadBuffer(addr, &value, 1);
    return value;
}

uint16_t AX58100_Read16(uint16_t addr)
{
    uint8_t buf[2];

    AX58100_ReadBuffer(addr, buf, 2);

    return ((uint16_t)buf[1] << 8) | buf[0];
}

uint32_t AX58100_Read32(uint16_t addr)
{
    uint8_t buf[4];

    AX58100_ReadBuffer(addr, buf, 4);

    return ((uint32_t)buf[3] << 24)
         | ((uint32_t)buf[2] << 16)
         | ((uint32_t)buf[1] << 8)
         | buf[0];
}

void AX58100_Write8(uint16_t addr, uint8_t value)
{
    AX58100_WriteBuffer(addr, &value, 1);
}

void AX58100_Write16(uint16_t addr, uint16_t value)
{
    uint8_t buf[2];

    buf[0] = (uint8_t)(value & 0xFF);
    buf[1] = (uint8_t)((value >> 8) & 0xFF);

    AX58100_WriteBuffer(addr, buf, 2);
}

void AX58100_Write32(uint16_t addr, uint32_t value)
{
    uint8_t buf[4];

    buf[0] = (uint8_t)(value & 0xFF);
    buf[1] = (uint8_t)((value >> 8) & 0xFF);
    buf[2] = (uint8_t)((value >> 16) & 0xFF);
    buf[3] = (uint8_t)((value >> 24) & 0xFF);

    AX58100_WriteBuffer(addr, buf, 4);
}

uint16_t AX58100_GetALEvent(void)
{
    return AX58100_Read16(AX58100_REG_AL_EVENT);
}

uint8_t AX58100_WaitReady(uint32_t timeoutMs)
{
    uint32_t start = HAL_GetTick();

    while ((HAL_GetTick() - start) < timeoutMs)
    {
        uint8_t smCount = AX58100_Read8(0x0005);
        uint16_t dpramSize = AX58100_Read16(0x0006);
        uint16_t eepromStatus = AX58100_Read16(0x0502);

        if (smCount >= 4 &&
            dpramSize != 0 &&
            !(eepromStatus & 0x8000) &&
            !(eepromStatus & 0x1800))
        {
            return 1;
        }

        HAL_Delay(10);
    }

    return 0;
}

static uint8_t AX58100_TestMemory(uint16_t addr, uint16_t len, uint8_t seed)
{
    uint16_t i;

    g_ax58100_testAddr = addr;
    g_ax58100_testLen = len;
    g_ax58100_failIndex = 0xFFFF;

    for (i = 0; i < len; i++)
    {
        g_ax58100_testTx[i] = (uint8_t)(seed + i);
        g_ax58100_testRx[i] = 0;
    }

    AX58100_WriteBuffer(addr, (const uint8_t *)g_ax58100_testTx, len);
    AX58100_ReadBuffer(addr, (uint8_t *)g_ax58100_testRx, len);

    for (i = 0; i < len; i++)
    {
        if (g_ax58100_testRx[i] != g_ax58100_testTx[i])
        {
            g_ax58100_failIndex = i;
            return 0;
        }
    }

    return 1;
}

void AX58100_SelfTest(void)
{
    g_ax58100_escType = AX58100_Read16(0x0000);
    g_ax58100_alEvent = AX58100_Read16(0x0220);
    g_ax58100_alStatus = AX58100_Read16(0x0130);

    g_ax58100_sm0Pass = 0;
    g_ax58100_sm1Pass = 0;
    g_ax58100_sm2Pass = 0;
    g_ax58100_sm3Pass = 0;
    g_ax58100_allPass = 0;

    g_ax58100_sm0Pass = AX58100_TestMemory(0x1000, 128, 0x10);
    if (g_ax58100_sm0Pass)
    {
        g_ax58100_sm1Pass = AX58100_TestMemory(0x1080, 128, 0x30);
    }
    if (g_ax58100_sm1Pass)
    {
        g_ax58100_sm2Pass = AX58100_TestMemory(0x1100, 32, 0xA0);
    }
    if (g_ax58100_sm2Pass)
    {
        g_ax58100_sm3Pass = AX58100_TestMemory(0x1120, 32, 0xC0);
    }

    g_ax58100_allPass = g_ax58100_sm0Pass
                      && g_ax58100_sm1Pass
                      && g_ax58100_sm2Pass
                      && g_ax58100_sm3Pass;

    while (1)
    {
        /* 用 Watch 看 escType/alEvent/alStatus/testRx */
    }
}

