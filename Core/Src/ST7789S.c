#include "ST7789S.h"

#include "ST7789S_driver.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../lv_conf.h"
#include "../../lvgl/src/lvgl.h"

#define DISP_MADCTL_MY 0x80
#define DISP_MADCTL_MX 0x40
#define DISP_MADCTL_MV 0x20

static lv_color_t buf[320 * 240];

void LVGL_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * buf){

		ST7789S_FlushArea(area->x1, area->y1, area->x2, area->y2, buf);
		
	    /* IMPORTANT!!!
	     * Inform LVGL that you are ready with the flushing and buf is not used anymore*/
	    lv_disp_flush_ready(disp);
	

}
void Display_Init(){

	ST7789S_Init();
	lv_disp_t * disp = lv_disp_create(320, 240);
	lv_disp_set_draw_buffers(disp, buf, NULL, sizeof(buf), LV_DISP_RENDER_MODE_DIRECT);
	lv_disp_set_flush_cb(disp, LVGL_flush);
}


static void WriteSequence(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        uint16_t value = va_arg(args, uint32_t);
        LcdWriteData(value);
    }
    va_end(args);
}

void ST7789S_Init()
{


    LcdDelay(100);

    LcdResetPinWrite(false);
    LcdDelay(10);
    LcdResetPinWrite(true);
    LcdDelay(10);

    //---------------------------------------------------------------------------------------------------//
    LcdWriteComm(0x28); // DISPOFF
    LcdWriteComm(0x11); // SLPOUT
    LcdDelay(150);

    //--------------------------------ST7789S Frame rate setting----------------------------------//
    LcdWriteComm(0xb2);
    WriteSequence(5, 0x0c, 0x0c, 0x00, 0x33, 0x33);
    LcdWriteComm(0xb7);
    LcdWriteData(0x35);

    //---------------------------------ST7789S Power setting--------------------------------------//
    LcdWriteComm(0xbb); // VCOM Setting
    LcdWriteData(0x28);
    LcdWriteComm(0xc0);
    LcdWriteData(0x2c);
    LcdWriteComm(0xc2); //
    WriteSequence(2, 0x01, 0xFF);
    LcdWriteComm(0xc3); // VRH Set
    LcdWriteData(0x11);
    LcdWriteComm(0xc4); // VDV Setting
    LcdWriteData(0x20);
    LcdWriteComm(0xc6); // Frame Rate Control in Normal Mode
    LcdWriteData(0x0f);
    LcdWriteComm(0xd0); // Power Control 1
    WriteSequence(2, 0xa4, 0xa1);
    //--------------------------------ST7789S gamma setting---------------------------------------//
    LcdWriteComm(0xe0);
    WriteSequence(14, 0xd0, 0x01, 0x08, 0x0f, 0x11, 0x2a, 0x36, 0x55, 0x44, 0x3a, 0x0b, 0x06, 0x11,
                  0x20);
    LcdWriteComm(0xe1);
    WriteSequence(14, 0xd0, 0x02, 0x07, 0x0a, 0x0b, 0x18, 0x34, 0x43, 0x4a, 0x2b, 0x1b, 0x1c, 0x22,
                  0x1f);

    //------------------------------display and color format
    // setting--------------------------------//

    LcdWriteComm(0x36); // MADCTL
    LcdWriteData(DISP_MADCTL_MV |
                 DISP_MADCTL_MX); // MV + MY - rotate -90 degree, MV + MX - rotate +90 degree
    LcdDelay(100);                // Need to
    LcdWriteComm(0x3A);           // COLMOD
    LcdWriteData(0x05);           // 16 BITS/PIXEL
    LcdDelay(100);                // Need to

    //--------------------------------ST7789S PWM BL
    // setting---------------------------------------//
    LcdWriteComm(0xC7);
    LcdWriteData(0x02); // PWMON
    LcdWriteComm(0xCC);
    LcdWriteData(0x15); // 5kHz PWM
    LcdWriteComm(0x29); // DISPON



}

void ST7789S_SetBrightness(uint8_t _value)
{
    LcdWriteComm(0x51);
    LcdWriteData(_value);
}

void ST7789S_SetArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2)
{
    LcdWriteComm(0x2A);
    WriteSequence(4, (_x1 >> 8) & 0xFF, (_x1 >> 0) & 0xFF, (_x2 >> 8) & 0xFF, (_x2 >> 0) & 0xFF);
    LcdWriteComm(0x2B);
    WriteSequence(4, (_y1 >> 8) & 0xFF, (_y1 >> 0) & 0xFF, (_y2 >> 8) & 0xFF, (_y2 >> 0) & 0xFF);
}

void ST7789S_FillArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, uint16_t _data)
{
    ST7789S_SetArea(_x1, _y1, _x2, _y2);
    LcdWriteComm(0x2C);
    for (int i = 0; i < (_x2 - _x1 + 1) * (_y2 - _y1 + 1); i++)
    {
        LcdWriteData(_data);
    }
}

void ST7789S_FlushArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, uint16_t* _data)
{
    ST7789S_SetArea(_x1, _y1, _x2, _y2);
    LcdWriteComm(0x2C);
    for (int i = 0; i < (_x2 - _x1 + 1) * (_y2 - _y1 + 1); i++)
    {
        LcdWriteData(_data[i]);
    }
}

void ST7789S_PutPixel(uint16_t _x, uint16_t _y, uint16_t *_data)
{
    static uint16_t TFT_X = 0;
    static uint16_t TFT_Y = 0;
    if (_x != TFT_X || _y != TFT_Y)
    {
        TFT_X = _x;
        TFT_Y = _y;
        ST7789S_SetArea(_x, _y, 319, _y);
        LcdWriteComm(0x2C);
    }
    LcdWriteData(*_data);
    TFT_X++;
}
