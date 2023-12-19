/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-28 13:52:22
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 17:05:00
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"

bool Key1_Flag = false;
bool Key2_Flag = false;
bool Key3_Flag = false;
bool Key4_Flag = false;

void Key1_External_Interrupt(void)
{
    if (digitalRead(KEY1) == 0)
    {
        Key1_Flag = true;
    }
    else
    {
        Key1_Flag = false;
    }
}
void Key2_External_Interrupt(void)
{
    if (digitalRead(KEY2) == 0)
    {
        Key2_Flag = true;
    }
    else
    {
        Key2_Flag = false;
    }
}
void Key3_External_Interrupt(void)
{
    if (digitalRead(KEY3) == 0)
    {
        Key3_Flag = true;
    }
    else
    {
        Key3_Flag = false;
    }
}
void Key4_External_Interrupt(void)
{
    if (digitalRead(KEY4) == 0)
    {
        Key4_Flag = true;
    }
    else
    {
        Key4_Flag = false;
    }
}

void N085_Screen_Set(uint8_t N085_Screen)
{
    switch (N085_Screen)
    {
    case N085_Initialize:
        pinMode(N085_CS1, OUTPUT);
        pinMode(N085_CS2, OUTPUT);
        pinMode(N085_CS3, OUTPUT);
        pinMode(N085_CS4, OUTPUT);
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, HIGH);
        break;
    case N085_Screen_1:
        digitalWrite(N085_CS1, LOW);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, HIGH);
        break;
    case N085_Screen_2:
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, LOW);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, HIGH);
        break;
    case N085_Screen_3:
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, LOW);
        digitalWrite(N085_CS4, HIGH);
        break;
    case N085_Screen_4:
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, LOW);
        break;

    case N085_Screen_ALL:
        digitalWrite(N085_CS1, LOW);
        digitalWrite(N085_CS2, LOW);
        digitalWrite(N085_CS3, LOW);
        digitalWrite(N085_CS4, LOW);
        break;

    default:
        break;
    }
}

void N085_Screen_Set_Unlocked(uint8_t N085_Screen)
{
    switch (N085_Screen)
    {
    case N085_Initialize:
        pinMode(N085_CS1, OUTPUT);
        pinMode(N085_CS2, OUTPUT);
        pinMode(N085_CS3, OUTPUT);
        pinMode(N085_CS4, OUTPUT);
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, HIGH);
        break;
    case N085_Screen_1:
        digitalWrite(N085_CS1, LOW);
        break;
    case N085_Screen_2:
        digitalWrite(N085_CS2, LOW);
        break;
    case N085_Screen_3:
        digitalWrite(N085_CS3, LOW);
        break;
    case N085_Screen_4:
        digitalWrite(N085_CS4, LOW);
        break;

    case N085_Screen_ALL:
        digitalWrite(N085_CS1, LOW);
        digitalWrite(N085_CS2, LOW);
        digitalWrite(N085_CS3, LOW);
        digitalWrite(N085_CS4, LOW);
        break;

    case N085_Screen_Clear:
        digitalWrite(N085_CS1, HIGH);
        digitalWrite(N085_CS2, HIGH);
        digitalWrite(N085_CS3, HIGH);
        digitalWrite(N085_CS4, HIGH);
        break;

    default:
        break;
    }
}

void T_Keyboard_S3_Key_Initialization(void)
{
    pinMode(KEY1, INPUT_PULLUP);
    pinMode(KEY2, INPUT_PULLUP);
    pinMode(KEY3, INPUT_PULLUP);
    pinMode(KEY4, INPUT_PULLUP);

    attachInterrupt(KEY1, Key1_External_Interrupt, CHANGE);
    attachInterrupt(KEY2, Key2_External_Interrupt, CHANGE);
    attachInterrupt(KEY3, Key3_External_Interrupt, CHANGE);
    attachInterrupt(KEY4, Key4_External_Interrupt, CHANGE);
}

uint8_t T_Keyboard_S3_Key_Trigger(void)
{
    if ((Key1_Flag && Key2_Flag && Key3_Flag && Key4_Flag) == true)
    {
        return 8;
    }

    if ((Key1_Flag && Key2_Flag) == true)
    {
        return 5;
    }
    if ((Key1_Flag && Key3_Flag) == true)
    {
        return 6;
    }
    if ((Key2_Flag && Key3_Flag) == true)
    {
        return 7;
    }
    if ((Key3_Flag && Key4_Flag) == true)
    {
        return 9;
    }


    if (Key1_Flag == true)
    {
        return 1;
    }
    if (Key2_Flag == true)
    {
        return 2;
    }
    if (Key3_Flag == true)
    {
        return 3;
    }
    if (Key4_Flag == true)
    {
        return 4;
    }

    return 0;
}
