/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-06-21 18:42:16
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 09:26:35
 * @License: GPL 3.0
 */
#include <Arduino.h>

uint8_t Data[100] = {0};

void setup()
{
    Serial.begin(115200);
    Serial.println("c");
}

void loop()
{
    // reply only when you receive data:
    if (Serial.available() > 0)
    {
Serial.read(Data, sizeof(Data));
        Serial.printf("%s\n", Data);
    }
}
