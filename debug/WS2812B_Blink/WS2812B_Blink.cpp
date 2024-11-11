/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-03 17:37:09
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-21 11:19:57
 * @License: GPL 3.0
 */
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 4

#define DATA_PIN 11

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is typical
    FastLED.setBrightness(50);
}

void loop()
{
    for (int i = 0; i < 5; i++)
    {
        // Turn the LED on, then pause
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(500);
        // Now turn the LED off, then pause
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(500);
    }
}
