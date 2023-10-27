#ifndef __ST7789_H
#define __ST7789_H

#define ABS(x) ((x) < 0 ? -(x) : (x))

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../../lv_conf.h"
#include "../../lvgl/src/lvgl.h"
void ST7789S_Init();
void ST7789S_SetBrightness(uint8_t _value);
void ST7789S_SetArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2);
void ST7789S_FillArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, uint16_t _data);
void ST7789S_FlushArea(uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, uint16_t* _data);
void ST7789S_PutPixel(uint16_t _x, uint16_t _y, uint16_t *_data);
void LVGL_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * color_p);
void Display_Init();


#ifdef __cplusplus
}
#endif

#endif /* __ST7789_H */
