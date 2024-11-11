/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-09-20 13:32:45
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-06 13:38:07
 * @License: GPL 3.0
 */

#include <Arduino.h>
#include "T-Keyboard-S3_Key.h"
#include "pin_config.h"
#include "FastLED.h"
#include "BleKeyboard.h"

#define KEY1_SET 'd'
#define KEY2_SET 'f'
#define KEY3_SET 'j'
#define KEY4_SET 'k'

// How many leds in your strip?
#define NUM_LEDS 4

#define DATA_PIN WS2812B_DATA

// Define the array of leds
CRGB leds[NUM_LEDS];

BleKeyboard *bleKeyboard = new BleKeyboard("T-Keyboard-S3");

uint8_t KEY1_Lock = 0;
uint8_t KEY1_Press_Delay = 0;
uint8_t KEY2_Lock = 0;
uint8_t KEY2_Press_Delay = 0;
uint8_t KEY3_Lock = 0;
uint8_t KEY3_Press_Delay = 0;
uint8_t KEY4_Lock = 0;
uint8_t KEY4_Press_Delay = 0;

void WS2812B_KEY_Loop(void)
{
    switch (Key1_Flag)
    {
    case 0:
        leds[0] = CRGB::Black;
        FastLED.show();

        bleKeyboard->release(KEY1_SET);
        KEY1_Press_Delay = 0;
        KEY1_Lock = 0;
        break;
    case 1:
        if (KEY1_Lock == 0)
        {
            leds[0] = CRGB::White;
            FastLED.show();
            bleKeyboard->press(KEY1_SET);
        }

        if (KEY1_Press_Delay >= 100)
        {
            KEY1_Press_Delay = 100;
            bleKeyboard->press(KEY1_SET);
        }
        KEY1_Press_Delay++;
        KEY1_Lock = 1;
        break;

    default:
        break;
    }

    switch (Key2_Flag)
    {
    case 0:
        leds[1] = CRGB::Black;
        FastLED.show();

        bleKeyboard->release(KEY2_SET);
        KEY2_Press_Delay = 0;
        KEY2_Lock = 0;
        break;
    case 1:
        if (KEY2_Lock == 0)
        {
            leds[1] = CRGB::White;
            FastLED.show();
            bleKeyboard->press(KEY2_SET);
        }

        if (KEY2_Press_Delay >= 100)
        {
            KEY2_Press_Delay = 100;
            bleKeyboard->press(KEY2_SET);
        }
        KEY2_Press_Delay++;
        KEY2_Lock = 1;
        break;

    default:
        break;
    }

    switch (Key3_Flag)
    {
    case 0:
        leds[2] = CRGB::Black;
        FastLED.show();

        bleKeyboard->release(KEY3_SET);
        KEY3_Press_Delay = 0;
        KEY3_Lock = 0;
        break;
    case 1:
        if (KEY3_Lock == 0)
        {
            leds[2] = CRGB::White;
            FastLED.show();
            bleKeyboard->press(KEY3_SET);
        }

        if (KEY3_Press_Delay >= 100)
        {
            KEY3_Press_Delay = 100;
            bleKeyboard->press(KEY3_SET);
        }
        KEY3_Press_Delay++;
        KEY3_Lock = 1;
        break;

    default:
        break;
    }

    switch (Key4_Flag)
    {
    case 0:
        leds[3] = CRGB::Black;
        FastLED.show();

        bleKeyboard->release(KEY4_SET);
        KEY4_Press_Delay = 0;
        KEY4_Lock = 0;
        break;
    case 1:
        if (KEY4_Lock == 0)
        {
            leds[3] = CRGB::White;
            FastLED.show();
            bleKeyboard->press(KEY4_SET);
        }

        if (KEY4_Press_Delay >= 100)
        {
            KEY4_Press_Delay = 100;
            bleKeyboard->press(KEY4_SET);
        }
        KEY4_Press_Delay++;
        KEY4_Lock = 1;
        break;

    default:
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    T_Keyboard_S3_Key_initialization();
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is typical
    FastLED.setBrightness(50);

    bleKeyboard->begin();

    while (!bleKeyboard->isConnected())
    {
        Serial.println("Bluetooth keyboard is connecting......");
        delay(100);
    }
}

void loop()
{
    if (!bleKeyboard->isConnected())
    {
        Serial.println("Bluetooth keyboard is connecting......");
        delay(100);
    }
    else
    {
        WS2812B_KEY_Loop();
    }
}
