/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-25 13:45:02
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-01 09:30:56
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "pin_config.h"
#include "N085.h"

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *N085_Bus = new Arduino_SWSPI(
    N085_DC, -1 /* CS */, N085_SCLK, N085_MOSI, N085_MISO); // Software SPI

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7735(
    N085_Bus, N085_RST, 0 /* rotation */, true /* IPS */,
    128 /* width */, 128 /* height */,
    2 /* col offset 1 */, 1 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */,
    true /* BGR */);

void setup(void)
{
    ledcAttachPin(N085_BL, 1); // assign TFT_BL pin to channel 1
    ledcSetup(1, 2000, 8);     // 12 kHz PWM, 8-bit resolution
    ledcWrite(1, 255);         // brightness 0 - 255

    N085_Screen_Set(N085_Initialize);

    N085_Screen_Set(N085_Screen_ALL);
    gfx->begin();
    gfx->fillScreen(WHITE);
}

void loop()
{
    // for (int i = 0; i < 255; i++)
    // {
    //     ledcWrite(1, i);
    //     delay(50);
    // }
    // for (int i = 255; i > 0; i--)
    // {
    //     ledcWrite(1, i);
    //     delay(50);
    // }
}