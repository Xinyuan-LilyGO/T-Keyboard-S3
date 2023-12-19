/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 15:20:04
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 17:12:22
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "custom.h"

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1)
        lv_style_reset(style);
    else
        lv_style_init(style);
}

void init_scr_del_flag(lv_ui *ui)
{

    ui->Clock_del = true;
    ui->Home_del = true;
    ui->Key_Mode_del = true;
    ui->Keyboard_del = true;
}

void setup_ui(lv_ui *ui)
{
    My_UI.Window_Current_State = My_UI.Window_Current_Home;
    
    init_scr_del_flag(ui);
    setup_scr_Home(ui);
    lv_scr_load(ui->Home);
}
