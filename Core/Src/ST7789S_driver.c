#include "ST7789S_driver.h"

#include "stm32f4xx.h"

#include <stdarg.h>
#include <stdint.h>

#define IO_RESET  GPIOC
#define PIN_RESET GPIO_PIN_1

// ��� ����������� RS � ������ FSMC_A(�) ���� � LCD_DATA ���������� � ������� �+1 ���
// � ������ ������ A16 (1 << (16+1) = 0x20000)
// ����� ��� ����� ������������ ���:
// FSMC_NORSRAM_BANK1 - 0x60000000
// FSMC_NORSRAM_BANK2 - 0x64000000
// FSMC_NORSRAM_BANK3 - 0x68000000
// FSMC_NORSRAM_BANK4 - 0x6C000000
#define LCD_COMMAND_BASE ((uint32_t)(0x6C000000))
#define LCD_DATA_BASE    ((uint32_t)(0x6C000002))
#define LCD_COMMAND      *((volatile uint16_t*)LCD_COMMAND_BASE)
#define LCD_DATA         *((volatile uint16_t*)LCD_DATA_BASE)


void LcdWriteComm(uint16_t _cmd)
{
    LCD_COMMAND = _cmd;
}

void LcdWriteData(uint16_t _data)
{
    LCD_DATA = _data;
}

void LcdResetPinWrite(bool value)
{
    HAL_GPIO_WritePin(IO_RESET, PIN_RESET, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LcdDelay(uint32_t value)
{
    HAL_Delay(value);
}
