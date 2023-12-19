/*
 * @Description: Test whether T-Keyboard-S3 is working properly
 * @version: V1.0.1
 * @Author: LILYGO_L
 * @Date: 2023-06-10 17:30:22
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-04 17:23:38
 */
#include <Arduino.h>
#include "lvgl.h"
#include "TFT_eSPI.h"
#include "pin_config.h"
#include "T-Keyboard_S3_Drive.h"
#include "FastLED.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "xinyuandianzi"
#define WIFI_PASSWORD "AA15994823428"

#define WIFI_CONNECT_WAIT_MAX (5000)

// How many leds in your strip?
#define NUM_LEDS 4
#define DATA_PIN WS2812B_DATA

#define NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2 "time.nist.gov"
#define GMT_OFFSET_SEC 8 * 3600 // Time zone setting function, written as 8 * 3600 in East Eighth Zone (UTC/GMT+8:00)
#define DAY_LIGHT_OFFSET_SEC 0  // Fill in 3600 for daylight saving time, otherwise fill in 0

uint8_t Tim0Flag1 = 0;
hw_timer_t *Tim0 = NULL;
bool wifi_connection_failure_flag = false;

static uint32_t TFT_Color[4] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK};
static uint32_t WS2812B_Color[4] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Black};

/*Change to your screen resolution*/
static const uint16_t screenWidth = 128;
static const uint16_t screenHeight = 128;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

// Define the array of leds
CRGB leds[NUM_LEDS];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

void IRAM_ATTR Tim0_Interrupt(void)
{
    Tim0Flag1 = true;
}

void WS2812B_KEY_Lvgl_Loop(void)
{
    switch (Key1_Flag)
    {
    case 0:
        leds[0] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[0] = CRGB::White;
        FastLED.show();

        N085_Screen_Set(N085_Screen_1);
        break;

    default:
        break;
    }

    switch (Key2_Flag)
    {
    case 0:
        leds[1] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[1] = CRGB::White;
        FastLED.show();

        N085_Screen_Set(N085_Screen_2);
        break;

    default:
        break;
    }

    switch (Key3_Flag)
    {
    case 0:
        leds[2] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[2] = CRGB::White;
        FastLED.show();

        N085_Screen_Set(N085_Screen_3);
        break;

    default:
        break;
    }

    switch (Key4_Flag)
    {
    case 0:
        leds[3] = CRGB::Black;
        FastLED.show();
        break;
    case 1:
        leds[3] = CRGB::White;
        FastLED.show();

        N085_Screen_Set(N085_Screen_4);
        break;

    default:
        break;
    }
}

void IO_initialization(void)
{
    pinMode(GPIO_NUM_1, OUTPUT);
    pinMode(GPIO_NUM_2, OUTPUT);
    pinMode(GPIO_NUM_4, OUTPUT);
    pinMode(GPIO_NUM_5, OUTPUT);
    pinMode(GPIO_NUM_6, OUTPUT);
    pinMode(GPIO_NUM_7, OUTPUT);
    pinMode(GPIO_NUM_8, OUTPUT);
    pinMode(GPIO_NUM_15, OUTPUT);
    pinMode(GPIO_NUM_16, OUTPUT);
    pinMode(GPIO_NUM_17, OUTPUT);
    pinMode(GPIO_NUM_18, OUTPUT);
    pinMode(GPIO_NUM_40, OUTPUT);
    pinMode(GPIO_NUM_41, OUTPUT);
    pinMode(GPIO_NUM_42, OUTPUT);
}

void IO_Test(void)
{
    static bool IO_Flag = 0;

    digitalWrite(GPIO_NUM_1, IO_Flag);
    digitalWrite(GPIO_NUM_2, IO_Flag);
    digitalWrite(GPIO_NUM_4, IO_Flag);
    digitalWrite(GPIO_NUM_5, IO_Flag);
    digitalWrite(GPIO_NUM_6, IO_Flag);
    digitalWrite(GPIO_NUM_7, IO_Flag);
    digitalWrite(GPIO_NUM_8, IO_Flag);
    digitalWrite(GPIO_NUM_15, IO_Flag);
    digitalWrite(GPIO_NUM_16, IO_Flag);
    digitalWrite(GPIO_NUM_17, IO_Flag);
    digitalWrite(GPIO_NUM_18, IO_Flag);
    digitalWrite(GPIO_NUM_40, IO_Flag);
    digitalWrite(GPIO_NUM_41, IO_Flag);
    digitalWrite(GPIO_NUM_42, IO_Flag);

    IO_Flag = !IO_Flag;
}

void wifi_test(void)
{
    String text;
    int wifi_num = 0;

    tft.setTextColor(TFT_GREEN);

    Serial.println("\nScanning wifi");
    tft.printf("Scanning wifi\n");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    wifi_num = WiFi.scanNetworks();
    if (wifi_num == 0)
    {
        text = "\nWiFi scan complete !\nNo wifi discovered.\n";
    }
    else
    {
        text = "\nWiFi scan complete !\n";
        text += wifi_num;
        text += " wifi discovered.\n\n";

        for (int i = 0; i < wifi_num; i++)
        {
            text += (i + 1);
            text += ": ";
            text += WiFi.SSID(i);
            text += " (";
            text += WiFi.RSSI(i);
            text += ")";
            text += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " \n" : "*\n";
            delay(10);
        }
    }

    Serial.println(text);
    tft.println(text);

    delay(3000);
    text.clear();
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);

    text = "Connecting to ";
    Serial.print("Connecting to ");
    tft.printf("Connecting to\n");
    text += WIFI_SSID;
    text += "\n";

    Serial.print(WIFI_SSID);
    tft.printf("%s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t last_tick = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        tft.printf(".");
        text += ".";
        delay(100);

        if (millis() - last_tick > WIFI_CONNECT_WAIT_MAX)
        {
            wifi_connection_failure_flag = true;
            break;
        }
    }

    if (!wifi_connection_failure_flag)
    {
        text += "\nThe connection was successful ! \nTakes ";
        Serial.print("\nThe connection was successful ! \nTakes ");
        tft.printf("\nThe connection was successful ! \nTakes ");
        text += millis() - last_tick;
        Serial.print(millis() - last_tick);
        tft.print(millis() - last_tick);
        text += " ms\n";
        Serial.println(" ms\n");
        tft.printf(" ms\n");

        tft.setTextColor(TFT_GREEN);
        tft.printf("\nWifi test passed!");
    }
    else
    {
        tft.setTextColor(TFT_RED);
        tft.printf("\nWifi test error!\n");
    }
}

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 10000))
    {
        Serial.println("Failed to obtain time");
        tft.setCursor(20, 90);
        tft.setTextColor(TFT_RED);
        tft.print("Failed to obtain time!");
        return;
    }
    Serial.println("Get time success");
    Serial.println(&timeinfo, "%A,%B %d %Y %H:%M:%S"); // Format Output
    tft.setCursor(30, 90);
    tft.setTextColor(TFT_ORANGE);
    tft.print(&timeinfo, " %Y");
    tft.setCursor(30, 100);
    tft.print(&timeinfo, "%B %d");
    tft.setCursor(30, 110);
    tft.print(&timeinfo, "%H:%M:%S");
}

// /*Read the touchpad*/
// void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
// {
//     uint16_t touchX, touchY;

//     bool touched = tft.getTouch( &touchX, &touchY, 600 );

//     if( !touched )
//     {
//         data->state = LV_INDEV_STATE_REL;
//     }
//     else
//     {
//         data->state = LV_INDEV_STATE_PR;

//         /*Set the coordinates*/
//         data->point.x = touchX;
//         data->point.y = touchY;

//         Serial.print( "Data x " );
//         Serial.println( touchX );

//         Serial.print( "Data y " );
//         Serial.println( touchY );
//     }
// }

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    uint16_t touchX = 64, touchY = 64;

    bool touched = Key1_Flag || Key2_Flag || Key3_Flag || Key4_Flag;

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        // Serial.print("Data x ");
        // Serial.println(touchX);

        // Serial.print("Data y ");
        // Serial.println(touchY);
    }
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void lvgl_initialization()
{
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println(LVGL_Arduino);
    Serial.println("I am LVGL_Arduino");

    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

void lvgl_background()
{
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xAFF1FF), LV_PART_MAIN);
}

void lv_style_img(void)
{
    static lv_style_t style;                               // 创建样式
    lv_style_init(&style);                                 // 初始化样式
    lv_style_set_border_side(&style, LV_BORDER_SIDE_NONE); // 设置样式边框显示范围
    // lv_style_set_radius(&style, 0); // 设置圆角半径

    LV_IMG_DECLARE(LOGO2);                         // 加载图片声明 .c文件的图片
    lv_style_set_bg_img_src(&style, &LOGO2);       // 设置背景图片
    lv_style_set_bg_img_opa(&style, LV_OPA_COVER); // 设置背景图片透明度
    // lv_style_set_bg_img_recolor(&style, lv_palette_main(LV_PALETTE_INDIGO)); // 设置背景图片重着色
    // lv_style_set_bg_img_recolor_opa(&style, LV_OPA_20);                      // 设置背景图片重着色透明度
    lv_style_set_bg_img_tiled(&style, false); // 设置背景图片平铺

    lv_style_set_x(&style, lv_pct(10)); // 设置样式的x位置 ，基准点左上角
    lv_style_set_y(&style, 79);         // 设置样式的y位置

    /*Create an object with the new style*/
    lv_obj_t *obj = lv_obj_create(lv_scr_act()); // 创建对象
    lv_obj_add_style(obj, &style, 0);            // 设置对象的样式
    lv_obj_set_size(obj, 105, 45);               // 设置对象的尺寸

    // lv_obj_center(obj);
}

static void anim_x_cb(void *var, int32_t v)
{
    lv_obj_set_x((_lv_obj_t *)var, v);
}

static void sw_event_cb(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);

    if (lv_obj_has_state(sw, LV_STATE_CHECKED))
    {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, lv_obj_get_x(label), 11);
        lv_anim_set_time(&a, 500);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
        lv_anim_start(&a);
    }
    else
    {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, lv_obj_get_x(label), -lv_obj_get_width(label));
        lv_anim_set_time(&a, 500);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
        lv_anim_start(&a);
    }
}

/**
 * Start animation on an event
 */
void lv_example_anim_1(void)
{
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_recolor(label, true);
    lv_label_set_text(label, "         #FF864C Ciallo#\n#195194 T-Keyboard-S3#");
    lv_obj_set_pos(label, -150, 12);

    lv_obj_t *sw = lv_switch_create(lv_scr_act());
    lv_obj_center(sw);
    lv_obj_add_state(sw, LV_STATE_CHECKED);
    lv_obj_clear_state(sw, LV_STATE_CHECKED);
    lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_VALUE_CHANGED, label);
}

void setup()
{
    /* TFT init */
    Serial.begin(115200);
    Serial.println("Ciallo");

    // Tim0
    Tim0 = timerBegin(0, 80, true);
    timerAttachInterrupt(Tim0, &Tim0_Interrupt, true);
    timerAlarmWrite(Tim0, 1000000ul, true);
    timerAlarmEnable(Tim0);

    IO_initialization();

    T_Keyboard_S3_Key_Initialization();

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is typical
    FastLED.setBrightness(50);

    ledcAttachPin(N085_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, 0);

    N085_Screen_Set(N085_Initialize);
    N085_Screen_Set(N085_Screen_ALL);
    tft.begin();
    tft.setRotation(0);
    tft.fillScreen(TFT_WHITE);

    for (int j = 0; j < 3; j++)
    {
        tft.fillScreen(TFT_Color[j]);
        for (int i = 0; i < 255; i++)
        {
            ledcWrite(1, i);
            delay(2);
        }
        leds[0] = WS2812B_Color[j];
        leds[1] = WS2812B_Color[j];
        leds[2] = WS2812B_Color[j];
        leds[3] = WS2812B_Color[j];
        FastLED.show();
        delay(3000);
        for (int i = 255; i > 0; i--)
        {
            ledcWrite(1, i);
            delay(5);
        }
        delay(1000);
    }

    leds[0] = WS2812B_Color[3];
    leds[1] = WS2812B_Color[3];
    leds[2] = WS2812B_Color[3];
    leds[3] = WS2812B_Color[3];
    FastLED.show();

    tft.fillScreen(TFT_BLACK);
    delay(2000);

    tft.setCursor(0, 0);
    ledcWrite(1, 255);

    // Wifi Test
    wifi_test();

    delay(2000);

    if (!wifi_connection_failure_flag)
    {
        // Obtain and set the time from the network time server
        // After successful acquisition, the chip will use the RTC clock to update the holding time
        configTime(GMT_OFFSET_SEC, DAY_LIGHT_OFFSET_SEC, NTP_SERVER1, NTP_SERVER2);

        delay(3000);

        printLocalTime();
    }
    else
    {
        tft.setCursor(20, 100);
        tft.setTextColor(TFT_RED);
        tft.print("Not connected to the network");
    }
    delay(5000);

    lvgl_initialization();

    lvgl_background();

    lv_style_img();

    lv_example_anim_1();

    // Update current screen layout.
    lv_obj_update_layout(lv_scr_act());
}

void loop()
{
    lv_timer_handler();
    // delay(5);

    WS2812B_KEY_Lvgl_Loop();

    if (Tim0Flag1 == true)
    {
        Tim0Flag1 = false;

        IO_Test();
    }
}
