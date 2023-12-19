/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-11-02 17:38:32
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-03 18:27:06
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Home(lv_ui *ui)
{
    My_UI.Window_Load_Anim_Delay_Lock_Flag = false;
    My_UI.Window_Load_Anim_Delay = 4294967295LL; // 窗口等待动画加载延时，初始化设置最大
    My_UI.Window_Unlock_Flag = false;
    My_UI.Window_Initialization_Number = 1;

    N085_Screen_Set(N085_Screen_ALL);

    // Write codes Home
    ui->Home = lv_obj_create(NULL);
    lv_obj_set_size(ui->Home, 128, 128);
    lv_obj_set_scrollbar_mode(ui->Home, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home, &_1_128x128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_imgbtn_1
    ui->Home_imgbtn_1 = lv_imgbtn_create(ui->Home);
    lv_obj_add_flag(ui->Home_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_10_alpha_128x128, NULL);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_10_alpha_128x128, NULL);
    lv_obj_add_flag(ui->Home_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->Home_imgbtn_1_label = lv_label_create(ui->Home_imgbtn_1);
    lv_label_set_text(ui->Home_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->Home_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_imgbtn_1, 0, 0);
    lv_obj_set_size(ui->Home_imgbtn_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui->Home_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Update current screen layout.
    lv_obj_update_layout(ui->Home);

    // Init events for screen.
    events_init_Home(ui);
}
