#ifndef __AX58100_H__
#define __AX58100_H__

#include "main.h"
#include <stdint.h>

#define AX58100_CMD_READ_BLOCK    0x02
#define AX58100_CMD_READ_SINGLE   0x03
#define AX58100_CMD_WRITE         0x04

#define AX58100_REG_AL_EVENT      0x0220

#define AX58100_CS_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define AX58100_CS_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

extern volatile uint16_t g_ax58100_escType;
extern volatile uint16_t g_ax58100_alEvent;
extern volatile uint16_t g_ax58100_alStatus;
extern volatile uint8_t g_ax58100_sm0Pass;
extern volatile uint8_t g_ax58100_sm1Pass;
extern volatile uint8_t g_ax58100_sm2Pass;
extern volatile uint8_t g_ax58100_sm3Pass;
extern volatile uint8_t g_ax58100_allPass;
extern volatile uint16_t g_ax58100_testAddr;
extern volatile uint16_t g_ax58100_testLen;
extern volatile uint16_t g_ax58100_failIndex;
extern volatile uint8_t g_ax58100_testTx[128];
extern volatile uint8_t g_ax58100_testRx[128];

uint8_t  AX58100_Read8(uint16_t addr);
uint16_t AX58100_Read16(uint16_t addr);
uint32_t AX58100_Read32(uint16_t addr);

void AX58100_Write8(uint16_t addr, uint8_t value);
void AX58100_Write16(uint16_t addr, uint16_t value);
void AX58100_Write32(uint16_t addr, uint32_t value);

void AX58100_ReadBuffer(uint16_t addr, uint8_t *buf, uint16_t len);
void AX58100_WriteBuffer(uint16_t addr, const uint8_t *buf, uint16_t len);
uint8_t AX58100_WaitReady(uint32_t timeoutMs);

uint16_t AX58100_GetALEvent(void);
void AX58100_SelfTest(void);

#endif


