/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-03 18:32:12
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-02 15:03:56
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"
#include "T-Keyboard-S3_Key.h"

uint8_t Key1_Flag = 0;
uint8_t Key2_Flag = 0;
uint8_t Key3_Flag = 0;
uint8_t Key4_Flag = 0;

void T_Keyboard_S3_Key_initialization(void)
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

void Key1_External_Interrupt(void)
{
    if (digitalRead(KEY1) == 0)
    {
        Key1_Flag = 1;
    }
    else
    {
        Key1_Flag = 0;
    }
}
void Key2_External_Interrupt(void)
{
    if (digitalRead(KEY2) == 0)
    {
        Key2_Flag = 1;
    }
    else
    {
        Key2_Flag = 0;
    }
}
void Key3_External_Interrupt(void)
{
    if (digitalRead(KEY3) == 0)
    {
        Key3_Flag = 1;
    }
    else
    {
        Key3_Flag = 0;
    }
}
void Key4_External_Interrupt(void)
{
    if (digitalRead(KEY4) == 0)
    {
        Key4_Flag = 1;
    }
    else
    {
        Key4_Flag = 0;
    }
}

