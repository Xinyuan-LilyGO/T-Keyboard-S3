/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 14:11:16
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 17:55:22
 * @License: GPL 3.0
 */
/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

    typedef struct
    {
        lv_obj_t *Home;
        bool Home_del;
        lv_obj_t *Home_imgbtn_1;
        lv_obj_t *Home_imgbtn_1_label;

        lv_obj_t *Clock;
        bool Clock_del;
        lv_obj_t *Clock_cont_1;
        lv_obj_t *Clock_label_2;
        lv_obj_t *Clock_cont_2;
        lv_obj_t *Clock_label_1;
        lv_obj_t *Clock_cont_3;
        lv_obj_t *Clock_img_1;

        lv_obj_t *Key_Mode;
        bool Key_Mode_del;
        lv_obj_t *Key_Mode_imgbtn_1;
        lv_obj_t *Key_Mode_imgbtn_1_label;

        lv_obj_t *Keyboard;
        bool Keyboard_del;
        lv_obj_t *Keyboard_imgbtn_1;
        lv_obj_t *Keyboard_imgbtn_1_label;

    } lv_ui;

    void ui_init_style(lv_style_t *style);
    void init_scr_del_flag(lv_ui *ui);
    void setup_ui(lv_ui *ui);
    extern lv_ui guider_ui;

    void setup_scr_Clock(lv_ui *ui);
    void setup_scr_Home(lv_ui *ui);
    void setup_scr_Key_Mode(lv_ui *ui);
    void setup_scr_Keyboard(lv_ui *ui);

    LV_IMG_DECLARE(_1_128x128);

    // Home
    LV_IMG_DECLARE(_2_alpha_128x128); // 键盘
    LV_IMG_DECLARE(_3_alpha_128x128);
    LV_IMG_DECLARE(_4_alpha_128x128); // 声音
    LV_IMG_DECLARE(_5_alpha_128x128);
    LV_IMG_DECLARE(_6_alpha_128x128); // 亮度
    LV_IMG_DECLARE(_7_alpha_128x128);
    LV_IMG_DECLARE(_8_alpha_128x128); // 时钟
    LV_IMG_DECLARE(_9_alpha_128x128);
    LV_IMG_DECLARE(_10_alpha_128x128); // 预加载界面缓冲图片

    LV_IMG_DECLARE(_11_alpha_100x100); // 太阳图片
    LV_IMG_DECLARE(_12_alpha_100x100); // 月亮图片

    // Key Mode Keyboard
    LV_IMG_DECLARE(_13_alpha_128x128); // Ctrl+C or Ctrl+V
    LV_IMG_DECLARE(_16_alpha_128x128);
    LV_IMG_DECLARE(_14_alpha_128x128); // OSU
    LV_IMG_DECLARE(_17_alpha_128x128);
    LV_IMG_DECLARE(_15_alpha_128x128); // 空白

    // Keyboard Ctel C V
    LV_IMG_DECLARE(_18_alpha_128x128); // Ctrl
    LV_IMG_DECLARE(_19_alpha_128x128); // C
    LV_IMG_DECLARE(_20_alpha_128x128); // V
    LV_IMG_DECLARE(_21_alpha_128x128);
    LV_IMG_DECLARE(_22_alpha_128x128); // Ctrl+C
    LV_IMG_DECLARE(_23_alpha_128x128); // Ctrl+V

    // Keyboard OSU
    LV_IMG_DECLARE(_24_alpha_128x128); // D
    LV_IMG_DECLARE(_25_alpha_128x128); // F
    LV_IMG_DECLARE(_26_alpha_128x128); // J
    LV_IMG_DECLARE(_27_alpha_128x128); // K

    // Keyboard Volume
    LV_IMG_DECLARE(_28_alpha_128x128);
    LV_IMG_DECLARE(_29_alpha_128x128);
    LV_IMG_DECLARE(_30_alpha_128x128);
    LV_IMG_DECLARE(_31_alpha_128x128);

    // Key Mode Brightness
    LV_IMG_DECLARE(_32_alpha_128x128); // Windows
    LV_IMG_DECLARE(_33_alpha_128x128);
    LV_IMG_DECLARE(_34_alpha_128x128); // MCU
    LV_IMG_DECLARE(_35_alpha_128x128);

    // Keyboard Brightness
    LV_IMG_DECLARE(_36_alpha_128x128);
    LV_IMG_DECLARE(_37_alpha_128x128);
    LV_IMG_DECLARE(_38_alpha_128x128);
    LV_IMG_DECLARE(_39_alpha_128x128);

    // Gif
    LV_IMG_DECLARE(_1_gif_128x128);

    // Home 2
    LV_IMG_DECLARE(_40_alpha_128x128);
    LV_IMG_DECLARE(_41_alpha_128x128);

    // Key Mode Game
    LV_IMG_DECLARE(_42_alpha_128x128);
    LV_IMG_DECLARE(_43_alpha_128x128);

    LV_FONT_DECLARE(lv_font_montserratMedium_16)

    LV_FONT_DECLARE(lv_font_clock)

#ifdef __cplusplus
}
#endif
#endif
