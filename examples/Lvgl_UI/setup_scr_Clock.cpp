/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 15:19:41
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-06 10:34:14
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Clock(lv_ui *ui)
{
    My_UI.Window_Current_State = My_UI.Window_Current_Clock;

    My_UI.Window_Load_Anim_Delay_Lock_Flag = false;
    My_UI.Window_Load_Anim_Delay = 4294967295LL; // 窗口等待动画加载延时，初始化设置最大
    My_UI.Window_Unlock_Flag = false;
    My_UI.Window_Initialization_Number = 1;

    // N085_Screen_Set(N085_Screen_ALL);

    // Write codes Clock
    ui->Clock = lv_obj_create(NULL);
    lv_obj_set_size(ui->Clock, 128, 128);
    lv_obj_set_scrollbar_mode(ui->Clock, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Clock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Clock, &_1_128x128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Clock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_cont_1
    ui->Clock_cont_1 = lv_obj_create(ui->Clock);
    lv_obj_set_pos(ui->Clock_cont_1, 4, 4);
    lv_obj_set_size(ui->Clock_cont_1, 120, 120);
    lv_obj_set_scrollbar_mode(ui->Clock_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Clock_cont_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Clock_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Clock_cont_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Clock_cont_1, lv_color_hex(0x101010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Clock_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Clock_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Clock_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Clock_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Clock_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_label_2
    ui->Clock_label_2 = lv_label_create(ui->Clock_cont_1);
    lv_label_set_text_fmt(ui->Clock_label_2, "%02d", 0);
    lv_label_set_long_mode(ui->Clock_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Clock_label_2, -10, 20);
    lv_obj_set_size(ui->Clock_label_2, 140, 110);
    lv_obj_set_scrollbar_mode(ui->Clock_label_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Clock_label_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Clock_label_2, &lv_font_clock, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Clock_label_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Clock_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Clock_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_cont_2
    ui->Clock_cont_2 = lv_obj_create(ui->Clock_cont_1);
    lv_obj_set_pos(ui->Clock_cont_2, 0, 10);
    lv_obj_set_size(ui->Clock_cont_2, 120, 1);
    lv_obj_set_scrollbar_mode(ui->Clock_cont_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Clock_cont_2, lv_color_hex(0x101010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Clock_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_label_1
    ui->Clock_label_1 = lv_label_create(ui->Clock_cont_2);
    lv_label_set_text_fmt(ui->Clock_label_1, "%02d", 0);
    lv_label_set_long_mode(ui->Clock_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Clock_label_1, -10, 10);
    lv_obj_set_size(ui->Clock_label_1, 140, 110);
    lv_obj_set_scrollbar_mode(ui->Clock_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Clock_label_1, lv_color_hex(0xFFC886), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Clock_label_1, &lv_font_clock, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Clock_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Clock_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Clock_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_cont_3
    ui->Clock_cont_3 = lv_obj_create(ui->Clock_cont_1);
    lv_obj_set_pos(ui->Clock_cont_3, 0, 60);
    lv_obj_set_size(ui->Clock_cont_3, 120, 60);
    lv_obj_set_scrollbar_mode(ui->Clock_cont_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Clock_cont_3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Clock_cont_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Clock_cont_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Clock_img_1
    ui->Clock_img_1 = lv_img_create(ui->Clock_cont_1);
    lv_obj_add_flag(ui->Clock_img_1, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->Clock_img_1, &_11_alpha_100x100);
    lv_img_set_pivot(ui->Clock_img_1, 50, 50);
    lv_img_set_angle(ui->Clock_img_1, 0);
    lv_obj_set_pos(ui->Clock_img_1, 10, 9);
    lv_obj_set_size(ui->Clock_img_1, 100, 100);
    lv_obj_set_scrollbar_mode(ui->Clock_img_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Clock_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Clock_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Update current Clock layout.
    lv_obj_update_layout(ui->Clock);

    // Init events for Clock.
    events_init_Clock(ui);
}
