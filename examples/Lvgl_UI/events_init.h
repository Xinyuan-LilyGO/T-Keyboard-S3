/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-25 15:21:14
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-06 16:10:26
 * @License: GPL 3.0
 */

#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "gui_guider.h"

    void events_init(lv_ui *ui);

    void events_init_Clock(lv_ui *ui);
    void events_init_Home(lv_ui *ui);
    void events_init_Key_Mode(lv_ui *ui);
    void events_init_Keyboard(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
