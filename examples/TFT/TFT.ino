/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-25 13:45:02
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-19 16:17:11
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "TFT_eSPI.h"
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"

TFT_eSPI tft;

void setup(void)
{
    ledcAttachPin(N085_BL, 1);   // assign TFT_BL pin to channel 1
    ledcSetup(1, 2000, 8); // 2 kHz PWM, 8-bit resolution
    ledcWrite(1, 255);     // brightness 0 - 255

    N085_Screen_Set(N085_Initialize);

    N085_Screen_Set(N085_Screen_ALL);
    tft.begin();
    // tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    // loop_image();

    N085_Screen_Set(N085_Screen_1);
    tft.setCursor(5, 60);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Ciallo1~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_2);
    tft.setCursor(5, 60);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Ciallo2~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_3);
    tft.setCursor(5, 60);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Ciallo3~(L *##*L)^**");

    N085_Screen_Set(N085_Screen_4);
    tft.setCursor(5, 60);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Ciallo4~(L *##*L)^**");
}

void loop()
{
}