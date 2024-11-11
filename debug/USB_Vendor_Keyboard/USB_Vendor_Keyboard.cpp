/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2024-07-06 10:37:45
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-07-09 14:19:37
 * @License: GPL 3.0
 */
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else
#include <Arduino.h>
#include <USB.h>
#include <USBHIDVendor.h>
#include <USBHIDKeyboard.h>
#include "T-Keyboard_S3_Drive.h"

#define Vendor_DATA_SIZE 63
#define USB_T_KEYBOARD_S3_VID 0xFF81
#define USB_T_KEYBOARD_S3_PID 0x0001
#define USB_T_KEYBOARD_S3_REV 0x0001
#define USB_MANUFACTURER_NAME "LILYGO"

#define KEY1_SET KEY_LEFT_CTRL
#define KEY2_SET 'c'
#define KEY3_SET 'v'
#define KEY4_SET KEY_BACKSPACE

uint8_t Vendor_Data[Vendor_DATA_SIZE] = {0};

static uint8_t KEY1_Lock = 0;
static uint8_t KEY1_Press_Delay = 0;
static uint8_t KEY2_Lock = 0;
static uint8_t KEY2_Press_Delay = 0;
static uint8_t KEY3_Lock = 0;
static uint8_t KEY3_Press_Delay = 0;
static uint8_t KEY4_Lock = 0;
static uint8_t KEY4_Press_Delay = 0;

USBHIDVendor Vendor(Vendor_DATA_SIZE, false);
USBHIDKeyboard Keyboard;

static void Vendor_EventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == ARDUINO_USB_HID_VENDOR_EVENTS)
    {
        arduino_usb_hid_vendor_event_data_t *data = (arduino_usb_hid_vendor_event_data_t *)event_data;
        switch (event_id)
        {
        case ARDUINO_USB_HID_VENDOR_GET_FEATURE_EVENT:
            Serial.printf("HID Get Feature Size: %u\n", data->len);
            Vendor.printf("Ciallo");
            break;
        case ARDUINO_USB_HID_VENDOR_SET_FEATURE_EVENT:
            Serial.printf("HID Set Feature Size: %u\n", data->len);
            Serial.printf("Receive Data: \n    ");
            for (int i = 0; i < Vendor_DATA_SIZE; i++)
            {
                if ((i != 0) && ((i % 10) == 0))
                {
                    Serial.printf("|\n    ");
                }
                Serial.printf("| %d ", Vendor_Data[i]);
            }
            Serial.printf("|\n    ");
            Serial.println();
            break;
        case ARDUINO_USB_HID_VENDOR_OUTPUT_EVENT:
            Serial.printf("HID Available Size: %u\n", data->len);
            break;

        default:
            break;
        }
    }
}

void KEY_Loop(void)
{
    if (Key1_Flag == false)
    {
        Keyboard.release(KEY1_SET);
        KEY1_Press_Delay = 0;
        KEY1_Lock = false;
    }
    else
    {
        if (KEY1_Lock == false)
        {
            Keyboard.press(KEY1_SET);
        }

        if (KEY1_Press_Delay >= 100)
        {
            KEY1_Press_Delay = 100;
            Keyboard.press(KEY1_SET);
        }
        KEY1_Press_Delay++;
        KEY1_Lock = true;
    }

    if (Key2_Flag == false)
    {
        Keyboard.release(KEY2_SET);
        KEY2_Press_Delay = 0;
        KEY2_Lock = false;
    }
    else
    {
        if (KEY2_Lock == false)
        {
            Keyboard.press(KEY2_SET);
        }

        if (KEY2_Press_Delay >= 100)
        {
            KEY2_Press_Delay = 100;
            Keyboard.press(KEY2_SET);
        }
        KEY2_Press_Delay++;
        KEY2_Lock = true;
    }

    if (Key3_Flag == false)
    {
        Keyboard.release(KEY3_SET);
        KEY3_Press_Delay = 0;
        KEY3_Lock = false;
    }
    else
    {
        if (KEY3_Lock == false)
        {
            Keyboard.press(KEY3_SET);
        }

        if (KEY3_Press_Delay >= 100)
        {
            KEY3_Press_Delay = 100;
            Keyboard.press(KEY3_SET);
        }
        KEY3_Press_Delay++;
        KEY3_Lock = true;
    }

    if (Key4_Flag == false)
    {
        Keyboard.release(KEY4_SET);
        KEY4_Press_Delay = 0;
        KEY4_Lock = false;
    }
    else
    {
        if (KEY4_Lock == false)
        {
            Keyboard.press(KEY4_SET);
        }

        if (KEY4_Press_Delay >= 100)
        {
            KEY4_Press_Delay = 100;
            Keyboard.press(KEY4_SET);
        }
        KEY4_Press_Delay++;
        KEY4_Lock = true;
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    T_Keyboard_S3_Key_Initialization();

    Vendor.onEvent(Vendor_EventCallback);
    Vendor.begin();
    Keyboard.begin();

    USB.VID(USB_T_KEYBOARD_S3_VID);
    USB.PID(USB_T_KEYBOARD_S3_PID);
    USB.manufacturerName(USB_MANUFACTURER_NAME);
    USB.firmwareVersion(USB_T_KEYBOARD_S3_REV);

    USB.begin();
}

void loop()
{
    KEY_Loop();

    while (Vendor.available())
    {
        Vendor.read(Vendor_Data, Vendor_DATA_SIZE);

        Serial.printf("Receive Data: \n    ");
        for (int i = 0; i < Vendor_DATA_SIZE; i++)
        {
            if ((i != 0) && ((i % 10) == 0))
            {
                Serial.printf("|\n    ");
            }
            Serial.printf("| %d ", Vendor_Data[i]);
        }
        Serial.printf("|\n    ");
    }
}
#endif /* ARDUINO_USB_MODE */
