/*
 * @Description:
    LVGL Configuration file:
    Copy your_arduino_path/libraries/lvgl/lv_conf_template.h
    to your_arduino_path/libraries/lv_conf.h

    In lv_conf.h around line 15, enable config file:
    #if 1 // Set it to "1" to enable content

    Then find and set:
    #define LV_COLOR_DEPTH     16
    #define LV_TICK_CUSTOM     1

    For SPI/parallel 8 display set color swap can be faster, parallel 16/RGB screen don't swap!
    #define LV_COLOR_16_SWAP   1 // for SPI and parallel 8
    #define LV_COLOR_16_SWAP   0 // for parallel 16 and RGB

 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-09-22 11:59:37
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-23 16:18:21
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include "Arduino_GFX_Library.h"
#include "pin_config.h"
#include "gui_guider.h"
#include "events_init.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "custom.h"
#include "FastLED.h"
#include <USB.h>
#include "google_dinosaur.h"

// How many leds in your strip?
#define NUM_LEDS 4

#define DATA_PIN WS2812B_DATA

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

static uint32_t screenWidth = 128;  // screenWidth
static uint32_t screenHeight = 128; // screenHeight

uint32_t Window_CycleTime1 = 0;

// GFX
//  Arduino_DataBus *bus = new Arduino_ESP32SPI(
//      N085_DC /* DC */, -1 /* CS */, N085_SCLK /* SCK */, N085_MOSI /* MOSI */, -1 /* MISO */); // Software SPI

// Arduino_GFX *gfx = new Arduino_GC9107(
//     bus, N085_RST /* RST */, 0 /* rotation */, true /* IPS */,
//     128 /* width */, 128 /* height */,
//     2 /* col offset 1 */, 1 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

// TFT
TFT_eSPI *tft = new TFT_eSPI(screenWidth, screenHeight);

// Define the array of leds
CRGB leds[NUM_LEDS];

lv_ui guider_ui;
My_Lvgl_UI My_UI;

USBHIDKeyboard Keyboard;
USBHIDConsumerControl ConsumerControl;

void Lvgl_WS2812B_Key_Loop(void)
{
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_CtrlCV ||
        My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_OSU)
    {
        if (Key1_Flag == true)
        {
            leds[0] = CRGB::White;
            FastLED.show();

            Keyboard.press(My_UI.Window_Keyboard_Key_Attribute[0]);
        }
        else
        {
            leds[0] = CRGB::Black;
            FastLED.show();

            Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[0]);
        }

        if (Key2_Flag == true)
        {
            leds[1] = CRGB::White;
            FastLED.show();

            Keyboard.press(My_UI.Window_Keyboard_Key_Attribute[1]);
        }
        else
        {
            leds[1] = CRGB::Black;
            FastLED.show();

            Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[1]);
        }

        if (Key3_Flag == true)
        {
            leds[2] = CRGB::White;
            FastLED.show();

            Keyboard.press(My_UI.Window_Keyboard_Key_Attribute[2]);
        }
        else
        {
            leds[2] = CRGB::Black;
            FastLED.show();

            Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[2]);
        }

        if (Key4_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();

            Keyboard.press(My_UI.Window_Keyboard_Key_Attribute[3]);
        }
        else
        {
            leds[3] = CRGB::Black;
            FastLED.show();

            Keyboard.release(My_UI.Window_Keyboard_Key_Attribute[3]);
        }
    }
    else if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Volume_Windows)
    {
        if (Key1_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[2] == 0)
            {
                leds[0] = CRGB::White;
                FastLED.show();

                ConsumerControl.press(CONSUMER_CONTROL_MUTE);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[2] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[2] = 20;
                ConsumerControl.press(CONSUMER_CONTROL_MUTE);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[2]++;
            My_UI.Window_Keyboard_Key_Lock[2] = 1;
        }
        else
        {
            leds[0] = CRGB::Black;
            FastLED.show();

            ConsumerControl.release();

            My_UI.Window_Keyboard_Key_Press_Delay[2] = 0;
            My_UI.Window_Keyboard_Key_Lock[2] = 0;
        }

        if (Key2_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[0] == 0)
            {
                leds[1] = CRGB::White;
                FastLED.show();

                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[0] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[0] = 20;
                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[0]++;
            My_UI.Window_Keyboard_Key_Lock[0] = 1;
        }
        else
        {
            leds[1] = CRGB::Black;
            FastLED.show();

            ConsumerControl.release();

            My_UI.Window_Keyboard_Key_Press_Delay[0] = 0;
            My_UI.Window_Keyboard_Key_Lock[0] = 0;
        }

        if (Key3_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[1] == 0)
            {
                leds[2] = CRGB::White;
                FastLED.show();

                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[1] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[1] = 20;
                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[1]++;
            My_UI.Window_Keyboard_Key_Lock[1] = 1;
        }
        else
        {
            leds[2] = CRGB::Black;
            FastLED.show();

            ConsumerControl.release();

            My_UI.Window_Keyboard_Key_Press_Delay[1] = 0;
            My_UI.Window_Keyboard_Key_Lock[1] = 0;
        }

        if (Key4_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();

            for (int i = 0; i < 100; i++)
            {
                ConsumerControl.press(CONSUMER_CONTROL_VOLUME);
                ConsumerControl.release();
            }
        }
        else
        {
            leds[3] = CRGB::Black;
            FastLED.show();
        }
    }
    else if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_Windows)
    {
        if (Key1_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();
            for (int i = 0; i < 100; i++)
            {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
                ConsumerControl.release();
            }
        }
        else
        {
            leds[0] = CRGB::Black;
            FastLED.show();
        }

        if (Key2_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[0] == 0)
            {
                leds[1] = CRGB::White;
                FastLED.show();

                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[0] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[0] = 20;
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[0]++;
            My_UI.Window_Keyboard_Key_Lock[0] = 1;
        }
        else
        {
            leds[1] = CRGB::Black;
            FastLED.show();

            ConsumerControl.release();

            My_UI.Window_Keyboard_Key_Press_Delay[0] = 0;
            My_UI.Window_Keyboard_Key_Lock[0] = 0;
        }

        if (Key3_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[1] == 0)
            {
                leds[2] = CRGB::White;
                FastLED.show();

                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[1] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[1] = 20;
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[1]++;
            My_UI.Window_Keyboard_Key_Lock[1] = 1;
        }
        else
        {
            leds[2] = CRGB::Black;
            FastLED.show();

            ConsumerControl.release();

            My_UI.Window_Keyboard_Key_Press_Delay[1] = 0;
            My_UI.Window_Keyboard_Key_Lock[1] = 0;
        }

        if (Key4_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();

            for (int i = 0; i < 100; i++)
            {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
                ConsumerControl.release();
            }
        }
        else
        {
            leds[3] = CRGB::Black;
            FastLED.show();
        }
    }
    else if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_MCU)
    {
        if (Key1_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();

            My_UI.LCD_Screen_Brightness = 0;
            ledcWrite(1, My_UI.LCD_Screen_Brightness);
        }
        else
        {
            leds[0] = CRGB::Black;
            FastLED.show();
        }

        if (Key2_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[0] == 0)
            {
                leds[1] = CRGB::White;
                FastLED.show();

                My_UI.LCD_Screen_Brightness--;
                if (My_UI.LCD_Screen_Brightness < 0)
                {
                    My_UI.LCD_Screen_Brightness = 0;
                }
                ledcWrite(1, My_UI.LCD_Screen_Brightness);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[0] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[0] = 20;
                My_UI.LCD_Screen_Brightness--;
                if (My_UI.LCD_Screen_Brightness < 0)
                {
                    My_UI.LCD_Screen_Brightness = 0;
                }
                ledcWrite(1, My_UI.LCD_Screen_Brightness);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[0]++;
            My_UI.Window_Keyboard_Key_Lock[0] = 1;
        }
        else
        {
            leds[1] = CRGB::Black;
            FastLED.show();

            My_UI.Window_Keyboard_Key_Press_Delay[0] = 0;
            My_UI.Window_Keyboard_Key_Lock[0] = 0;
        }

        if (Key3_Flag == true)
        {
            if (My_UI.Window_Keyboard_Key_Lock[1] == 0)
            {
                leds[2] = CRGB::White;
                FastLED.show();

                My_UI.LCD_Screen_Brightness++;
                if (My_UI.LCD_Screen_Brightness > 255)
                {
                    My_UI.LCD_Screen_Brightness = 255;
                }
                ledcWrite(1, My_UI.LCD_Screen_Brightness);
            }

            if (My_UI.Window_Keyboard_Key_Press_Delay[1] >= 20)
            {
                My_UI.Window_Keyboard_Key_Press_Delay[1] = 20;
                My_UI.LCD_Screen_Brightness++;
                if (My_UI.LCD_Screen_Brightness > 255)
                {
                    My_UI.LCD_Screen_Brightness = 255;
                }
                ledcWrite(1, My_UI.LCD_Screen_Brightness);
            }
            My_UI.Window_Keyboard_Key_Press_Delay[1]++;
            My_UI.Window_Keyboard_Key_Lock[1] = 1;
        }
        else
        {
            leds[2] = CRGB::Black;
            FastLED.show();

            My_UI.Window_Keyboard_Key_Press_Delay[1] = 0;
            My_UI.Window_Keyboard_Key_Lock[1] = 0;
        }

        if (Key4_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();

            My_UI.LCD_Screen_Brightness = 255;
            ledcWrite(1, My_UI.LCD_Screen_Brightness);
        }
        else
        {
            leds[3] = CRGB::Black;
            FastLED.show();
        }
    }
    else
    {
        if (Key1_Flag == true)
        {
            leds[0] = CRGB::White;
            FastLED.show();
        }
        else
        {
            leds[0] = CRGB::Black;
            FastLED.show();
        }
        if (Key2_Flag == true)
        {
            leds[1] = CRGB::White;
            FastLED.show();
        }
        else
        {
            leds[1] = CRGB::Black;
            FastLED.show();
        }
        if (Key3_Flag == true)
        {
            leds[2] = CRGB::White;
            FastLED.show();
        }
        else
        {
            leds[2] = CRGB::Black;
            FastLED.show();
        }
        if (Key4_Flag == true)
        {
            leds[3] = CRGB::White;
            FastLED.show();
        }
        else
        {
            leds[3] = CRGB::Black;
            FastLED.show();
        }
    }
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    // GFX
    //  #if (LV_COLOR_16_SWAP != 0)
    //      gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
    //  #else
    //      gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
    //  #endif

    // TFT
    tft->startWrite();
    tft->setAddrWindow(area->x1, area->y1, w, h);
    tft->pushColors((uint16_t *)&color_p->full, w * h, true);
    tft->endWrite();

    lv_disp_flush_ready(disp);
}

// /*Read the touchpad*/
// void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
// {
//     if (touchpad.available())
//     {
//         if (touchpad.finger_num > 0)
//         {
//             data->state = LV_INDEV_STATE_PR;

//             /*Set the coordinates*/
//             data->point.x = touchpad.x;
//             data->point.y = touchpad.y;

//             // Serial.print("Data x ");
//             // Serial.println(touchpad.x);

//             // Serial.print("Data y ");
//             // Serial.println(touchpad.y);
//         }
//         else
//         {
//             data->state = LV_INDEV_STATE_REL;
//         }
//     }
// }

/*Get the currently being pressed key.  0 if no key is pressed*/
static bool keypad_get_key(void)
{
    delay(50); // 延时触发判断

    switch (T_Keyboard_S3_Key_Trigger())
    {
    case 0:
        return false;
        break;
    case 1:

        if (My_UI.Window_Current_State == My_UI.Window_Current_Home ||
            My_UI.Window_Current_State == My_UI.Window_Current_Home_2 ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Game)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Key1;
            return true;
        }
        return false;
        break;
    case 2:

        if (My_UI.Window_Current_State == My_UI.Window_Current_Home ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Key2;
            return true;
        }
        return false;
        break;
    case 3:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Home ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Key3;
            return true;
        }
        return false;
        break;
    case 4:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Home ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Key4;
            return true;
        }
        return false;
        break;
    case 5:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Home_2 ||
            My_UI.Window_Current_State == My_UI.Window_Current_Home)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Previous_Page;
            return true;
        }
        return false;
        break;
    case 7:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Clock ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness ||
            My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Game ||
            My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_CtrlCV ||
            My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Volume_Windows ||
            My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_Windows ||
            My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_MCU ||
            My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Game_Google_Dinosaur)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Back;
            return true;
        }
        return false;
        break;
    case 8:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_OSU)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Back_Home;
            return true;
        }
        return false;
        break;
    case 9:
        if (My_UI.Window_Current_State == My_UI.Window_Current_Home ||
            My_UI.Window_Current_State == My_UI.Window_Current_Home_2)
        {
            My_UI.Lvgl_Key_Trigger_State = My_UI.Lvgl_Key_Trigger_State_Next_Page;
            return true;
        }
        return false;
        break;

    default:
        return false;
        break;
    }
    return false;
}

/*Read the touchpad*/
void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    uint16_t touchX = 1, touchY = 1;

    if (T_Keyboard_S3_Key_Trigger() == false)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        if (keypad_get_key() == true)
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = touchX;
            data->point.y = touchY;

            // Serial.print("Data x ");
            // Serial.println(touchX);

            // Serial.print("Data y ");
            // Serial.println(touchY);

            // data->key = act_key;
        }
    }
}

void Lvgl_Initialization(void)
{
    lv_init();

    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    while (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        delay(1000);
    }

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 40);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = keypad_read;
    lv_indev_drv_register(&indev_drv);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(N085_BL, OUTPUT);

    ledcAttachPin(N085_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, My_UI.LCD_Screen_Brightness); // brightness 0 - 255

    T_Keyboard_S3_Key_Initialization();

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is typical
    FastLED.setBrightness(50);

    Keyboard.begin();
    ConsumerControl.begin();
    USB.begin();

    N085_Screen_Set(N085_Initialize);
    N085_Screen_Set(N085_Screen_ALL);

    // GFX
    //  // Init Display
    //  if (!gfx->begin())
    //  {
    //      Serial.println("gfx->begin() failed!");
    //  }
    //  gfx->fillScreen(WHITE);

    // TFT
    tft->begin();
    tft->fillScreen(TFT_BLACK);

    Lvgl_Initialization();

    for (uint16_t i = 0; i < 255; i++) // 打开屏幕
    {
        My_UI.LCD_Screen_Brightness++;
        ledcWrite(1, My_UI.LCD_Screen_Brightness);
        delay(2);
    }

    lv_obj_t *img = lv_gif_create(lv_scr_act());
    lv_gif_set_src(img, &_1_gif_128x128);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    LV_Delay(8800);
    lv_obj_del(img);

    setup_ui(&guider_ui);
    events_init(&guider_ui);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    // delay(5);

    Lvgl_WS2812B_Key_Loop();

    // Home
    if (My_UI.Window_Current_State == My_UI.Window_Current_Home)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 200; // 设置等待动画时间200ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Home_Loop();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
    }

    // Home 2
    if (My_UI.Window_Current_State == My_UI.Window_Current_Home_2)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 200; // 设置等待动画时间200ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Home_2_Loop();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
    }

    // Clock
    if (My_UI.Window_Current_State == My_UI.Window_Current_Clock)
    {
        My_UI.Window_Clock_Refresh_Second = millis() / 1000 % 60;         // 刷新秒时间
        My_UI.Window_Clock_Refresh_Minute = millis() / 1000 / 60 % 60;    // 刷新分时间
        My_UI.Window_Clock_Refresh_Hour = millis() / 1000 / 60 / 24 % 24; // 刷新时时间

        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 300; // 设置等待动画时间300ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            My_UI.Window_Load_Anim_Delay = 0; // 任何时间都大于他

            if (millis() > Window_CycleTime1)
            {
                Window_Clock_Loop();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
    }

    // Key Mode Keyboard
    if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Keyboard)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Key_Mode_Keyboard_Loop();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
    }

    // Keyboard CtrlCV
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_CtrlCV)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 200; // 设置等待动画时间200ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if ((millis() > My_UI.Window_Load_Anim_Delay) && (My_UI.Window_Unlock_Flag == false)) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Keyboard_CtrlCV_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            Window_Keyboard_CtrlCV_Loop();
        }
    }

    // Keyboard OSU
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_OSU)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 200; // 设置等待动画时间200ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Keyboard_OSU_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            // Window_Keyboard_OSU_Loop();
        }
    }

    // Keyboard Volume
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Volume_Windows)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if ((millis() > My_UI.Window_Load_Anim_Delay) && (My_UI.Window_Unlock_Flag == false)) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Keyboard_Volume_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            Window_Keyboard_Volume_Loop();
        }
    }

    // Key Mode Volume
    if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Volume)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Key_Mode_Volume_Loop();
                Window_CycleTime1 = millis() + 20; // 20ms
            }
        }
    }

    // Key Mode Brightness
    if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Brightness)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Key_Mode_Brightness_Loop();
                Window_CycleTime1 = millis() + 20; // 20ms
            }
        }
    }

    // Key Mode Game
    if (My_UI.Window_Current_State == My_UI.Window_Current_Key_Mode_Game)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if (millis() > My_UI.Window_Load_Anim_Delay) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Key_Mode_Game_Loop();
                Window_CycleTime1 = millis() + 20; // 20ms
            }
        }
    }

    // Keyboard Brightness Windows
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_Windows)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if ((millis() > My_UI.Window_Load_Anim_Delay) && (My_UI.Window_Unlock_Flag == false)) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Keyboard_Brightness_Windows_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            Window_Keyboard_Brightness_Windows_Loop();
        }
    }

    // Keyboard Brightness MCU
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Brightness_MCU)
    {
        if (My_UI.Window_Load_Anim_Delay_Lock_Flag == false) // 如果动画等待设定没有锁的话
        {
            My_UI.Window_Load_Anim_Delay = millis() + 400; // 设置等待动画时间400ms
            My_UI.Window_Load_Anim_Delay_Lock_Flag = true; // 将动画等待设定锁起来
        }

        if ((millis() > My_UI.Window_Load_Anim_Delay) && (My_UI.Window_Unlock_Flag == false)) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Window_Keyboard_Brightness_MCU_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            Window_Keyboard_Brightness_MCU_Loop();
        }
    }

    // Keyboard Game Google Dinosaur
    if (My_UI.Window_Current_State == My_UI.Window_Current_Keyboard_Game_Google_Dinosaur)
    {
        if ((millis() > My_UI.Window_Load_Anim_Delay) && (My_UI.Window_Unlock_Flag == false)) // 等待动画加载完成
        {
            if (millis() > Window_CycleTime1)
            {
                Google_Dinosaur_Initialization();
                Window_CycleTime1 = millis() + 10; // 10ms
            }
        }
        else
        {
            Google_Dinosaur_Loop();
        }
    }
}