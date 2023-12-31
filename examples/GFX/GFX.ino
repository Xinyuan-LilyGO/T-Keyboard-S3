/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-25 13:45:02
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-06 13:38:44
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "Arduino_GFX_Library.h"
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"

Arduino_DataBus *bus = new Arduino_ESP32SPI(
    N085_DC /* DC */, -1 /* CS */, N085_SCLK /* SCK */, N085_MOSI /* MOSI */, -1 /* MISO */); 

Arduino_GFX *gfx = new Arduino_GC9107(
    bus, N085_RST /* RST */, 0 /* rotation */, true /* IPS */,
    128 /* width */, 128 /* height */,
    2 /* col offset 1 */, 1 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

void setup(void)
{
    ledcAttachPin(N085_BL, 1); // assign TFT_BL pin to channel 1
    ledcSetup(1, 2000, 8);     // 12 kHz PWM, 8-bit resolution
    ledcWrite(1, 255);         // brightness 0 - 255

    N085_Screen_Set(N085_Initialize);

    N085_Screen_Set(N085_Screen_ALL);
    gfx->begin();
    gfx->fillScreen(BLACK);

    N085_Screen_Set(N085_Screen_1);
    gfx->setCursor(5, 60);
    gfx->setTextColor(YELLOW);
    gfx->println("Ciallo1~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_2);
    gfx->setCursor(5, 60);
    gfx->setTextColor(YELLOW);
    gfx->println("Ciallo2~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_3);
    gfx->setCursor(5, 60);
    gfx->setTextColor(YELLOW);
    gfx->println("Ciallo3~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_4);
    gfx->setCursor(5, 60);
    gfx->setTextColor(YELLOW);
    gfx->println("Ciallo4~(L *##*L)^**");
    delay(1000);
}

void loop()
{
}