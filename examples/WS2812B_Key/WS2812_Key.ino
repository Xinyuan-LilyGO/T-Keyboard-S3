/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-28 13:41:49
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-01 14:17:43
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "T-Keyboard-S3_Key.h"
#include "pin_config.h"
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 4

#define DATA_PIN WS2812B_Data

// Define the array of leds
CRGB leds[NUM_LEDS];

void WS2812B_KEY_Loop(void)
{
    switch (Key1_Flag)
    {
    case 0:
        leds[0] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[0] = CRGB::White;
        FastLED.show();
        break;

    default:
        break;
    }

    switch (Key2_Flag)
    {
    case 0:
        leds[1] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[1] = CRGB::White;
        FastLED.show();
        break;

    default:
        break;
    }

    switch (Key3_Flag)
    {
    case 0:
        leds[2] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[2] = CRGB::White;
        FastLED.show();
        break;

    default:
        break;
    }

    switch (Key4_Flag)
    {
    case 0:
        leds[3] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[3] = CRGB::White;
        FastLED.show();
        break;

    default:
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    T_Keyboard_S3_Key_initialization();
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is typical
    FastLED.setBrightness(50);
}

void loop()
{
    WS2812B_KEY_Loop();
}
