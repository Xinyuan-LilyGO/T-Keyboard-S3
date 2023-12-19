/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 14:11:58
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 18:05:48
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "gui_guider.h"

void LV_Delay(uint32_t lv_delay)
{
    for (uint32_t i = 0; i < lv_delay; i++)
    {
        lv_timer_handler();
        delay(1);
    }
}

void Window_Home_Data_Refresh(lv_ui *ui,
                              const lv_img_dsc_t *img_reserved, const lv_img_dsc_t *img_pressed)
{
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, img_reserved, NULL);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, img_pressed, NULL);
}

void Window_Clock_Data_Refresh(lv_ui *ui,
                               uint8_t current_time, uint8_t refresh_time)
{
    lv_obj_set_style_bg_color(ui->Clock_cont_1, lv_color_hex(0x101010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_width(ui->Clock_cont_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Clock_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_clear_flag(ui->Clock_cont_3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->Clock_cont_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui->Clock_label_2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_pos(ui->Clock_cont_2, 0, 10);
    lv_obj_set_size(ui->Clock_cont_2, 120, 1);

    lv_label_set_text_fmt(ui->Clock_label_2, "%02d", current_time);
    lv_label_set_text_fmt(ui->Clock_label_1, "%02d", refresh_time);

    lv_obj_add_flag(ui->Clock_img_1, LV_OBJ_FLAG_HIDDEN);
}

void Window_Clock_Sun_Refresh(lv_ui *ui)
{
    lv_obj_set_style_bg_color(ui->Clock_cont_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_1, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_width(ui->Clock_cont_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Clock_cont_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_clear_flag(ui->Clock_img_1, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(ui->Clock_cont_3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->Clock_cont_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->Clock_label_2, LV_OBJ_FLAG_HIDDEN);

    lv_img_set_src(ui->Clock_img_1, &_11_alpha_100x100);
}

void Window_Clock_Moon_Refresh(lv_ui *ui)
{
    lv_obj_set_style_bg_color(ui->Clock_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Clock_cont_1, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_width(ui->Clock_cont_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Clock_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Clock_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_clear_flag(ui->Clock_img_1, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(ui->Clock_cont_3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->Clock_cont_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->Clock_label_2, LV_OBJ_FLAG_HIDDEN);

    lv_img_set_src(ui->Clock_img_1, &_12_alpha_100x100);
}

void Window_Clock_Data_Refresh_Anim(void)
{
    // Write animation: Clock_cont_2 scale in width
    lv_anim_t Clock_cont_2_anim_width;
    lv_anim_init(&Clock_cont_2_anim_width);
    lv_anim_set_var(&Clock_cont_2_anim_width, guider_ui.Clock_cont_2);
    lv_anim_set_time(&Clock_cont_2_anim_width, 1000);
    lv_anim_set_delay(&Clock_cont_2_anim_width, 0);
    lv_anim_set_exec_cb(&Clock_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
    lv_anim_set_values(&Clock_cont_2_anim_width, lv_obj_get_width(guider_ui.Clock_cont_2), 120);
    lv_anim_set_path_cb(&Clock_cont_2_anim_width, &lv_anim_path_linear);
    Clock_cont_2_anim_width.repeat_cnt = 0;
    lv_anim_start(&Clock_cont_2_anim_width);
    // Write animation: Clock_cont_2 scale in height
    lv_anim_t Clock_cont_2_anim_height;
    lv_anim_init(&Clock_cont_2_anim_height);
    lv_anim_set_var(&Clock_cont_2_anim_height, guider_ui.Clock_cont_2);
    lv_anim_set_time(&Clock_cont_2_anim_height, 1000);
    lv_anim_set_delay(&Clock_cont_2_anim_height, 0);
    lv_anim_set_exec_cb(&Clock_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
    lv_anim_set_values(&Clock_cont_2_anim_height, lv_obj_get_height(guider_ui.Clock_cont_2), 100);
    lv_anim_set_path_cb(&Clock_cont_2_anim_height, &lv_anim_path_linear);
    Clock_cont_2_anim_height.repeat_cnt = 0;
    lv_anim_start(&Clock_cont_2_anim_height);
}

void Window_Key_Mode_Data_Refresh(lv_ui *ui,
                                  const lv_img_dsc_t *img_reserved, const lv_img_dsc_t *img_pressed)
{
    lv_imgbtn_set_src(ui->Key_Mode_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, img_reserved, NULL);
    lv_imgbtn_set_src(ui->Key_Mode_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, img_pressed, NULL);
}

void Window_Keyboard_Data_Refresh(lv_ui *ui,
                                  const lv_img_dsc_t *img_reserved, const lv_img_dsc_t *img_pressed)
{
    lv_obj_set_style_bg_color(ui->Keyboard, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_imgbtn_set_src(ui->Keyboard_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, img_reserved, NULL);
    lv_imgbtn_set_src(ui->Keyboard_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, img_pressed, NULL);
}

void Window_Home_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Home_Data_Refresh(&guider_ui, &_2_alpha_128x128, &_3_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Home_Data_Refresh(&guider_ui, &_4_alpha_128x128, &_5_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Home_Data_Refresh(&guider_ui, &_6_alpha_128x128, &_7_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Home_Data_Refresh(&guider_ui, &_8_alpha_128x128, &_9_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Home_2_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Home_Data_Refresh(&guider_ui, &_40_alpha_128x128, &_41_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Home_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Home_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Home_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Clock_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            if (My_UI.Window_Clock_Current_Hour >= 18 &&
                My_UI.Window_Clock_Current_Hour <= 6)
            {
                Window_Clock_Moon_Refresh(&guider_ui);
            }
            else
            {
                Window_Clock_Sun_Refresh(&guider_ui);
            }

            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Clock);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Clock_Data_Refresh(&guider_ui,
                                      My_UI.Window_Clock_Current_Hour,
                                      My_UI.Window_Clock_Refresh_Hour);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Clock);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Clock_Data_Refresh(&guider_ui,
                                      My_UI.Window_Clock_Current_Minute,
                                      My_UI.Window_Clock_Refresh_Minute);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Clock);

            My_UI.Window_Initialization_Number++;
            break;
        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Clock_Data_Refresh(&guider_ui,
                                      My_UI.Window_Clock_Current_Second,
                                      My_UI.Window_Clock_Refresh_Second);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Clock);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
        if (My_UI.Window_Clock_Current_Second != My_UI.Window_Clock_Refresh_Second)
        {
            N085_Screen_Set(N085_Screen_4);

            Window_Clock_Data_Refresh(&guider_ui,
                                      My_UI.Window_Clock_Current_Second,
                                      My_UI.Window_Clock_Refresh_Second);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Clock);

            Window_Clock_Data_Refresh_Anim();

            My_UI.Window_Clock_Current_Second = My_UI.Window_Clock_Refresh_Second;
        }

        if (My_UI.Window_Clock_Current_Minute != My_UI.Window_Clock_Refresh_Minute ||
            My_UI.Window_Clock_Current_Hour != My_UI.Window_Clock_Refresh_Hour)
        {
            My_UI.Window_Clock_Current_Minute = My_UI.Window_Clock_Refresh_Minute;
            My_UI.Window_Clock_Current_Hour = My_UI.Window_Clock_Refresh_Hour;

            My_UI.Window_Initialization_Number = 1;
            My_UI.Window_Unlock_Flag = false;
        }
    }
}

void Window_Key_Mode_Keyboard_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_13_alpha_128x128, &_16_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_14_alpha_128x128, &_17_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Keyboard_CtrlCV_Initialization(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Keyboard_Data_Refresh(&guider_ui, &_18_alpha_128x128, &_18_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Keyboard_Data_Refresh(&guider_ui, &_19_alpha_128x128, &_19_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Keyboard_Data_Refresh(&guider_ui, &_20_alpha_128x128, &_20_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Keyboard_Data_Refresh(&guider_ui, &_21_alpha_128x128, &_21_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_CtrlCV_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == true)
    {
        uint8_t key_trigger = T_Keyboard_S3_Key_Trigger();

        if (key_trigger != false)
        {
            switch (key_trigger)
            {
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1;

                N085_Screen_Set(N085_Screen_1);

                Window_Keyboard_Data_Refresh(&guider_ui, &_18_alpha_128x128, &_18_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xFF6A6A), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key2:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key2;

                N085_Screen_Set(N085_Screen_2);

                Window_Keyboard_Data_Refresh(&guider_ui, &_19_alpha_128x128, &_19_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xBA55D3), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key3:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key3;

                N085_Screen_Set(N085_Screen_3);

                Window_Keyboard_Data_Refresh(&guider_ui, &_20_alpha_128x128, &_20_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xBA55D3), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key4:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key4;

                N085_Screen_Set(N085_Screen_4);

                Window_Keyboard_Data_Refresh(&guider_ui, &_21_alpha_128x128, &_21_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xBA55D3), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1_Key2:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1_Key2;

                N085_Screen_Set_Unlocked(N085_Screen_Clear);
                N085_Screen_Set_Unlocked(N085_Screen_1);
                N085_Screen_Set_Unlocked(N085_Screen_2);

                Window_Keyboard_Data_Refresh(&guider_ui, &_22_alpha_128x128, &_22_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xB1D85C), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1_Key3:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1_Key2;

                N085_Screen_Set_Unlocked(N085_Screen_Clear);
                N085_Screen_Set_Unlocked(N085_Screen_1);
                N085_Screen_Set_Unlocked(N085_Screen_3);

                Window_Keyboard_Data_Refresh(&guider_ui, &_23_alpha_128x128, &_23_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xB1D85C), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;

            default:
                break;
            }
        }
        else
        {
            if (My_UI.Window_Keyboard_Key_Trigger_State != My_UI.Window_Keyboard_Key_Trigger_State_NULL)
            {
                My_UI.Window_Initialization_Number = 1;
                My_UI.Window_Unlock_Flag = false;
            }
            My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_NULL;
        }
    }
}

void Window_Keyboard_OSU_Initialization(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Keyboard_Data_Refresh(&guider_ui, &_24_alpha_128x128, &_24_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Keyboard_Data_Refresh(&guider_ui, &_25_alpha_128x128, &_25_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Keyboard_Data_Refresh(&guider_ui, &_26_alpha_128x128, &_26_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Keyboard_Data_Refresh(&guider_ui, &_27_alpha_128x128, &_27_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_OSU_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == true)
    {
        switch (T_Keyboard_S3_Key_Trigger())
        {
        case My_UI.Window_Keyboard_Key_Trigger_State_Key1:
            /* code */
            break;
        case My_UI.Window_Keyboard_Key_Trigger_State_Key2:
            /* code */
            break;
        case My_UI.Window_Keyboard_Key_Trigger_State_Key3:
            /* code */
            break;
        case My_UI.Window_Keyboard_Key_Trigger_State_Key4:
            /* code */
            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_Volume_Initialization(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Keyboard_Data_Refresh(&guider_ui, &_28_alpha_128x128, &_28_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Keyboard_Data_Refresh(&guider_ui, &_29_alpha_128x128, &_29_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Keyboard_Data_Refresh(&guider_ui, &_30_alpha_128x128, &_30_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Keyboard_Data_Refresh(&guider_ui, &_31_alpha_128x128, &_31_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_Volume_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == true)
    {
        uint8_t key_trigger = T_Keyboard_S3_Key_Trigger();

        if (key_trigger != false)
        {
            switch (key_trigger)
            {
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1;

                N085_Screen_Set(N085_Screen_1);

                Window_Keyboard_Data_Refresh(&guider_ui, &_28_alpha_128x128, &_28_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x483D8B), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key2:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key2;

                N085_Screen_Set(N085_Screen_2);

                Window_Keyboard_Data_Refresh(&guider_ui, &_29_alpha_128x128, &_29_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x6B8E23), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key3:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key3;

                N085_Screen_Set(N085_Screen_3);

                Window_Keyboard_Data_Refresh(&guider_ui, &_30_alpha_128x128, &_30_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xFF1493), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key4:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key4;

                N085_Screen_Set(N085_Screen_4);

                Window_Keyboard_Data_Refresh(&guider_ui, &_31_alpha_128x128, &_31_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xB22222), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;

            default:
                break;
            }
        }
        else
        {
            if (My_UI.Window_Keyboard_Key_Trigger_State != My_UI.Window_Keyboard_Key_Trigger_State_NULL)
            {
                My_UI.Window_Initialization_Number = 1;
                My_UI.Window_Unlock_Flag = false;
            }
            My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_NULL;
        }
    }
}

void Window_Key_Mode_Volume_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_32_alpha_128x128, &_33_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Key_Mode_Brightness_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_32_alpha_128x128, &_33_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_34_alpha_128x128, &_35_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Key_Mode_Game_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_42_alpha_128x128, &_42_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Key_Mode);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }

    if (My_UI.Window_Unlock_Flag == true)
    {
    }
}

void Window_Keyboard_Brightness_Windows_Initialization(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Keyboard_Data_Refresh(&guider_ui, &_38_alpha_128x128, &_38_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Keyboard_Data_Refresh(&guider_ui, &_37_alpha_128x128, &_37_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Keyboard_Data_Refresh(&guider_ui, &_36_alpha_128x128, &_36_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Keyboard_Data_Refresh(&guider_ui, &_39_alpha_128x128, &_39_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_Brightness_Windows_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == true)
    {
        uint8_t key_trigger = T_Keyboard_S3_Key_Trigger();

        if (key_trigger != false)
        {
            switch (key_trigger)
            {
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1;

                N085_Screen_Set(N085_Screen_1);

                Window_Keyboard_Data_Refresh(&guider_ui, &_38_alpha_128x128, &_38_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x483D8B), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key2:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key2;

                N085_Screen_Set(N085_Screen_2);

                Window_Keyboard_Data_Refresh(&guider_ui, &_37_alpha_128x128, &_37_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x6B8E23), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key3:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key3;

                N085_Screen_Set(N085_Screen_3);

                Window_Keyboard_Data_Refresh(&guider_ui, &_36_alpha_128x128, &_36_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xFF1493), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key4:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key4;

                N085_Screen_Set(N085_Screen_4);

                Window_Keyboard_Data_Refresh(&guider_ui, &_39_alpha_128x128, &_39_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xB22222), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;

            default:
                break;
            }
        }
        else
        {
            if (My_UI.Window_Keyboard_Key_Trigger_State != My_UI.Window_Keyboard_Key_Trigger_State_NULL)
            {
                My_UI.Window_Initialization_Number = 1;
                My_UI.Window_Unlock_Flag = false;
            }
            My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_NULL;
        }
    }
}

void Window_Keyboard_Brightness_MCU_Initialization(void)
{
    if (My_UI.Window_Unlock_Flag == false)
    {
        switch (My_UI.Window_Initialization_Number)
        {
        case 1:
            N085_Screen_Set(N085_Screen_1);

            Window_Keyboard_Data_Refresh(&guider_ui, &_38_alpha_128x128, &_38_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 2:
            N085_Screen_Set(N085_Screen_2);

            Window_Keyboard_Data_Refresh(&guider_ui, &_37_alpha_128x128, &_37_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 3:
            N085_Screen_Set(N085_Screen_3);

            Window_Keyboard_Data_Refresh(&guider_ui, &_36_alpha_128x128, &_36_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 4:
            N085_Screen_Set(N085_Screen_4);

            Window_Keyboard_Data_Refresh(&guider_ui, &_39_alpha_128x128, &_39_alpha_128x128);
            // Update current Key_Mode layout.
            lv_obj_update_layout(guider_ui.Keyboard);

            My_UI.Window_Initialization_Number++;
            break;

        case 5:
            My_UI.Window_Initialization_Number = 0;
            My_UI.Window_Unlock_Flag = true;

            break;

        default:
            break;
        }
    }
}

void Window_Keyboard_Brightness_MCU_Loop(void)
{
    if (My_UI.Window_Unlock_Flag == true)
    {
        uint8_t key_trigger = T_Keyboard_S3_Key_Trigger();

        if (key_trigger != false)
        {
            switch (key_trigger)
            {
            case My_UI.Window_Keyboard_Key_Trigger_State_Key1:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key1;

                N085_Screen_Set(N085_Screen_1);

                Window_Keyboard_Data_Refresh(&guider_ui, &_38_alpha_128x128, &_38_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x483D8B), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key2:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key2;

                N085_Screen_Set(N085_Screen_2);

                Window_Keyboard_Data_Refresh(&guider_ui, &_37_alpha_128x128, &_37_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0x6B8E23), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key3:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key3;

                N085_Screen_Set(N085_Screen_3);

                Window_Keyboard_Data_Refresh(&guider_ui, &_36_alpha_128x128, &_36_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xFF1493), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;
            case My_UI.Window_Keyboard_Key_Trigger_State_Key4:

                My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_Key4;

                N085_Screen_Set(N085_Screen_4);

                Window_Keyboard_Data_Refresh(&guider_ui, &_39_alpha_128x128, &_39_alpha_128x128);
                lv_obj_set_style_bg_color(guider_ui.Keyboard, lv_color_hex(0xB22222), LV_PART_MAIN | LV_STATE_DEFAULT);

                // Update current Key_Mode layout.
                lv_obj_update_layout(guider_ui.Keyboard);

                break;

            default:
                break;
            }
        }
        else
        {
            if (My_UI.Window_Keyboard_Key_Trigger_State != My_UI.Window_Keyboard_Key_Trigger_State_NULL)
            {
                My_UI.Window_Initialization_Number = 1;
                My_UI.Window_Unlock_Flag = false;
            }
            My_UI.Window_Keyboard_Key_Trigger_State = My_UI.Window_Keyboard_Key_Trigger_State_NULL;
        }
    }
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}
