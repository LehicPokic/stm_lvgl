#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

void LcdWriteComm(uint16_t _cmd);
void LcdWriteData(uint16_t _data);
void LcdResetPinWrite(bool value);
void LcdDelay(uint32_t value);
