/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-28 13:52:22
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-28 15:14:23
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"

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
