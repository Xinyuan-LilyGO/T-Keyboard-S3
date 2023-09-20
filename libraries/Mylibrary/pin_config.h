/*
 * @Description: None
 * @version: None
 * @Author: None
 * @Date: 2023-06-05 13:01:59
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-31 15:28:27
 */
#pragma once

// N085-1212TBWIG06-C08
#define N085_CS1 12
#define N085_CS2 13
#define N085_CS3 14
#define N085_CS4 21
#define N085_DC 45
#define N085_SCLK 47
#define N085_MOSI 48
#define N085_MISO -1
#define N085_RST 38
#define N085_BL 39

enum
{
    N085_Initialize = 0,
    N085_Screen_1,
    N085_Screen_2,
    N085_Screen_3,
    N085_Screen_4,
    N085_Screen_ALL,
};

// N085-1212TBWIG06-C08
#define KEY1 10
#define KEY2 9
#define KEY3 46
#define KEY4 3

// WS2812B
#define WS2812B_Data 11
