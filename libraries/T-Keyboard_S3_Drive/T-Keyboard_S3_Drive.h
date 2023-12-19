/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-28 13:52:30
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-03 17:53:46
 * @License: GPL 3.0
 */
#pragma once

enum
{
    N085_Initialize = 0,
    N085_Screen_1,
    N085_Screen_2,
    N085_Screen_3,
    N085_Screen_4,
    N085_Screen_ALL,
    N085_Screen_Clear,
};

void N085_Screen_Set(uint8_t N085_Screen);
void N085_Screen_Set_Unlocked(uint8_t N085_Screen);
void T_Keyboard_S3_Key_Initialization(void);
void Key1_External_Interrupt(void);
void Key2_External_Interrupt(void);
void Key3_External_Interrupt(void);
void Key4_External_Interrupt(void);
uint8_t T_Keyboard_S3_Key_Trigger(void);

extern bool Key1_Flag;
extern bool Key2_Flag;
extern bool Key3_Flag;
extern bool Key4_Flag;
