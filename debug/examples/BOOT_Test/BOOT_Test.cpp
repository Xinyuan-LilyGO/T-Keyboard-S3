/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-22 10:19:40
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-18 15:20:24
 * @License: GPL 3.0
 */
#include <Arduino.h>

void setup(void)
{
    Serial.begin(115200);

    pinMode(10, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(46, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);
}

void loop(void)
{
    // digitalWrite(0, HIGH);
    // delay(1000);
    // digitalWrite(0, LOW);
    // delay(1000);
    if (digitalRead(3) == 0)
    {
        Serial.println("0");
    }
    else if (digitalRead(3) == 1)
    {
        Serial.println("1");
    }
    delay(100);
}