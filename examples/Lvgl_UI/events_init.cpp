/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 15:21:14
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-10 19:00:05
 * @License: GPL 3.0
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

static void set_zoom(void *img, int32_t v)
{
    lv_img_set_zoom((_lv_obj_t *)img, v);
}

static void anim_size_cb(void *var, int32_t v)
{
    lv_obj_set_size((_lv_obj_t *)var, v, v);
}

static void Home_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_anim_t a;

    lv_obj_t *act_scr = lv_scr_act();
    lv_disp_t *d = lv_obj_get_disp(act_scr);

    switch (code)
    {
    case LV_EVENT_PRESSED:
        switch (My_UI.Lvgl_Key_Trigger_State) // 按压后立刻修改按压动画
        {
        case My_UI.Lvgl_Key_Trigger_State_Key1:

            N085_Screen_Set(N085_Screen_1);

            switch (My_UI.Window_Current_State)
            {
            case My_UI.Window_Current_Home:
                Window_Home_Data_Refresh(&guider_ui, &_2_alpha_128x128, &_3_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Home);
                break;

            case My_UI.Window_Current_Home_2:
                Window_Home_Data_Refresh(&guider_ui, &_40_alpha_128x128, &_41_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Home);
                break;

            default:
                break;
            }

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key2:

            N085_Screen_Set(N085_Screen_2);

            Window_Home_Data_Refresh(&guider_ui, &_4_alpha_128x128, &_5_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key3:

            N085_Screen_Set(N085_Screen_3);

            Window_Home_Data_Refresh(&guider_ui, &_6_alpha_128x128, &_7_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key4:

            N085_Screen_Set(N085_Screen_4);

            Window_Home_Data_Refresh(&guider_ui, &_8_alpha_128x128, &_9_alpha_128x128);
            // Update current Clock layout.
            lv_obj_update_layout(guider_ui.Home);

            break;

        case My_UI.Lvgl_Key_Trigger_State_Next_Page:

            switch (My_UI.Window_Current_State)
            {
            case My_UI.Window_Current_Home:

                My_UI.Window_Current_State = My_UI.Window_Current_Home_2;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            case My_UI.Window_Current_Home_2:

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 100, true);
                    guider_ui.Home_del = true;
                }

                break;

            default:
                break;
            }

            break;
        case My_UI.Lvgl_Key_Trigger_State_Previous_Page:

            switch (My_UI.Window_Current_State)
            {
            case My_UI.Window_Current_Home_2:

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            case My_UI.Window_Current_Home:

                My_UI.Window_Current_State = My_UI.Window_Current_Home_2;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            default:
                break;
            }

            break;

        default:
            break;
        }
        break;
    case LV_EVENT_RELEASED:
        switch (My_UI.Lvgl_Key_Trigger_State)
        {
        case My_UI.Lvgl_Key_Trigger_State_Key1:

            switch (My_UI.Window_Current_State)
            {
            case My_UI.Window_Current_Home:

                N085_Screen_Set(N085_Screen_1);

                /*Now create the actual image*/
                lv_img_set_src(img, &_2_alpha_128x128);
                lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

                lv_anim_init(&a);
                lv_anim_set_var(&a, img);
                lv_anim_set_time(&a, 600);
                lv_anim_set_values(&a, 256, 10000);
                // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
                // lv_anim_set_playback_time(&a, 450);

                lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
                lv_anim_set_exec_cb(&a, set_zoom);

                lv_anim_start(&a);

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Keyboard;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
                break;

            case My_UI.Window_Current_Home_2:

                N085_Screen_Set(N085_Screen_1);

                /*Now create the actual image*/
                lv_img_set_src(img, &_40_alpha_128x128);
                lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

                lv_anim_init(&a);
                lv_anim_set_var(&a, img);
                lv_anim_set_time(&a, 600);
                lv_anim_set_values(&a, 256, 10000);
                // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
                // lv_anim_set_playback_time(&a, 450);

                lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
                lv_anim_set_exec_cb(&a, set_zoom);

                lv_anim_start(&a);

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Game;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
                break;

            default:
                break;
            }

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key2:

            N085_Screen_Set(N085_Screen_2);

            /*Now create the actual image*/
            lv_img_set_src(img, &_4_alpha_128x128);
            lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

            lv_anim_init(&a);
            lv_anim_set_var(&a, img);
            lv_anim_set_time(&a, 600);
            lv_anim_set_values(&a, 256, 10000);
            // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
            // lv_anim_set_playback_time(&a, 450);

            lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
            lv_anim_set_exec_cb(&a, set_zoom);

            lv_anim_start(&a);

            My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Volume;

            // Write the load screen code.
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Key_Mode_del == true)
                {
                    setup_scr_Key_Mode(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 200, true);
                guider_ui.Key_Mode_del = true;
            }

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key3:

            N085_Screen_Set(N085_Screen_3);

            /*Now create the actual image*/
            lv_img_set_src(img, &_6_alpha_128x128);
            lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

            lv_anim_init(&a);
            lv_anim_set_var(&a, img);
            lv_anim_set_time(&a, 600);
            lv_anim_set_values(&a, 256, 10000);
            // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
            // lv_anim_set_playback_time(&a, 450);

            lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
            lv_anim_set_exec_cb(&a, set_zoom);

            lv_anim_start(&a);

            My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Brightness;

            // Write the load screen code.
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Key_Mode_del == true)
                {
                    setup_scr_Key_Mode(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 200, true);
                guider_ui.Key_Mode_del = true;
            }

            break;

        case My_UI.Lvgl_Key_Trigger_State_Key4:

            N085_Screen_Set(N085_Screen_4);

            /*Now create the actual image*/
            lv_img_set_src(img, &_8_alpha_128x128);
            lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

            lv_anim_init(&a);
            lv_anim_set_var(&a, img);
            lv_anim_set_time(&a, 600);
            lv_anim_set_values(&a, 256, 10000);
            // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
            // lv_anim_set_playback_time(&a, 450);

            lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
            lv_anim_set_exec_cb(&a, set_zoom);

            lv_anim_start(&a);

            // Write the load screen code.
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Clock_del == true)
                {
                    setup_scr_Clock(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Clock, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 200, true);
                guider_ui.Clock_del = true;
            }

            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void events_init_Home(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Home_imgbtn_1, Home_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
}

static void Clock_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t *act_scr = lv_scr_act();
    lv_disp_t *d = lv_obj_get_disp(act_scr);

    switch (code)
    {
    case LV_EVENT_RELEASED:

        switch (My_UI.Lvgl_Key_Trigger_State)
        {
        case My_UI.Lvgl_Key_Trigger_State_Back:

            My_UI.Window_Current_State = My_UI.Window_Current_Home;

            // Write the load screen code.
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                guider_ui.Home_del = true;
            }
            break;

        default:
            break;
        }

        break;

    default:
        break;
    }
}
void events_init_Clock(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Clock, Clock_event_handler, LV_EVENT_ALL, NULL);
}

static void Key_Mode_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t *act_scr = lv_scr_act();
    lv_disp_t *d = lv_obj_get_disp(act_scr);

    switch (code)
    {
    case LV_EVENT_PRESSED:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_13_alpha_128x128, &_16_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_14_alpha_128x128, &_17_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                N085_Screen_Set(N085_Screen_3);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                N085_Screen_Set(N085_Screen_4);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_32_alpha_128x128, &_33_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                N085_Screen_Set(N085_Screen_3);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                N085_Screen_Set(N085_Screen_4);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_32_alpha_128x128, &_33_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_34_alpha_128x128, &_35_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                N085_Screen_Set(N085_Screen_3);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                N085_Screen_Set(N085_Screen_4);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Game)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_42_alpha_128x128, &_42_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                N085_Screen_Set(N085_Screen_3);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                N085_Screen_Set(N085_Screen_4);

                Window_Key_Mode_Data_Refresh(&guider_ui, &_15_alpha_128x128, &_15_alpha_128x128);
                // Update current Clock layout.
                lv_obj_update_layout(guider_ui.Key_Mode);

                break;

            default:
                break;
            }
        }

        break;

    case LV_EVENT_RELEASED:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_CtrlCV;
                My_UI.Window_Keyboard_Key_Attribute[0] = KEY_LEFT_CTRL;
                My_UI.Window_Keyboard_Key_Attribute[1] = 'c';
                My_UI.Window_Keyboard_Key_Attribute[2] = 'v';
                My_UI.Window_Keyboard_Key_Attribute[3] = KEY_RETURN;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Keyboard_del == true)
                    {
                        setup_scr_Keyboard(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Keyboard, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 100, true);
                    guider_ui.Keyboard_del = true;
                }
                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_OSU;
                My_UI.Window_Keyboard_Key_Attribute[0] = 'd';
                My_UI.Window_Keyboard_Key_Attribute[1] = 'f';
                My_UI.Window_Keyboard_Key_Attribute[2] = 'j';
                My_UI.Window_Keyboard_Key_Attribute[3] = 'k';

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Keyboard_del == true)
                    {
                        setup_scr_Keyboard(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Keyboard, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 100, true);
                    guider_ui.Keyboard_del = true;
                }

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Back:

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_Volume_Windows;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Keyboard_del == true)
                    {
                        setup_scr_Keyboard(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Keyboard, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 100, true);
                    guider_ui.Keyboard_del = true;
                }
                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Back:

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_Brightness_Windows;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Keyboard_del == true)
                    {
                        setup_scr_Keyboard(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Keyboard, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 100, true);
                    guider_ui.Keyboard_del = true;
                }
                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                N085_Screen_Set(N085_Screen_2);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_Brightness_MCU;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Keyboard_del == true)
                    {
                        setup_scr_Keyboard(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Keyboard, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 100, true);
                    guider_ui.Keyboard_del = true;
                }

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Back:

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            default:
                break;
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Game)
        {
            switch (My_UI.Lvgl_Key_Trigger_State)
            {
            case My_UI.Lvgl_Key_Trigger_State_Key1:

                N085_Screen_Set(N085_Screen_1);

                My_UI.Window_Current_State = My_UI.Window_Current_Keyboard_Game_Google_Dinosaur;

                My_UI.Window_Unlock_Flag = false;

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key2:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key3:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Key4:

                // Code

                break;

            case My_UI.Lvgl_Key_Trigger_State_Back:

                My_UI.Window_Current_State = My_UI.Window_Current_Home_2;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                    guider_ui.Home_del = true;
                }
                break;

            default:
                break;
            }
        }

        break;

    default:
        break;
    }
}
void events_init_Key_Mode(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Key_Mode_imgbtn_1, Key_Mode_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
}

static void Keyboard_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_LONG_PRESSED:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_OSU)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back_Home)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                for (int i = 0; i < 4; i++)
                {
                    Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[i]);
                }

                My_UI.Window_Current_State = My_UI.Window_Current_Home;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Home_del == true)
                    {
                        setup_scr_Home(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 100, true);
                    guider_ui.Home_del = true;
                }
            }
        }
        break;

    case LV_EVENT_RELEASED:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_CtrlCV)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                for (int i = 0; i < 4; i++)
                {
                    Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[i]);
                }

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Keyboard;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Volume_Windows)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                ConsumerControl.release();

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Volume;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_Windows)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                ConsumerControl.release();

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Brightness;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_MCU)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Brightness;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
            }
        }

        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Game_Google_Dinosaur)
        {
            if (My_UI.Lvgl_Key_Trigger_State == My_UI.Lvgl_Key_Trigger_State_Back)
            {
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);

                My_UI.Window_Current_State = My_UI.Window_Current_Key_Mode_Game;

                // Write the load screen code.
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Key_Mode_del == true)
                    {
                        setup_scr_Key_Mode(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Key_Mode, LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 200, true);
                    guider_ui.Key_Mode_del = true;
                }
            }
        }

        break;

    default:
        break;
    }
}

void events_init_Keyboard(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Keyboard_imgbtn_1, Keyboard_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{
}
