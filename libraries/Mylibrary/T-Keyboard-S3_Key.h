/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-03 18:32:12
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-20 12:06:00
 * @License: GPL 3.0
 */
#pragma once

extern uint8_t Key1_Flag;
extern uint8_t Key2_Flag;
extern uint8_t Key3_Flag;
extern uint8_t Key4_Flag;

void T_Keyboard_S3_Key_initialization(void);
void Key1_External_Interrupt(void);
void Key2_External_Interrupt(void);
void Key3_External_Interrupt(void);
void Key4_External_Interrupt(void);
