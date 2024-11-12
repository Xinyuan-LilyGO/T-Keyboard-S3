/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2024-07-04 14:03:07
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-07-06 10:46:27
 * @License: GPL 3.0
 */

#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include <Arduino.h>
#include <USB.h>
#include "USB_HID_Template.h"

#define KEY_1 0
#define ENDPOINT_DEFAULT_DATA_SIZE 63
#define USB_T_KEYBOARD_S3_VID 0xFF81
#define USB_T_KEYBOARD_S3_PID 0x0001
#define USB_T_KEYBOARD_S3_REV 0x0001
#define USB_MANUFACTURER_NAME "LILYGO"

uint8_t Endpoint_Default_Data[ENDPOINT_DEFAULT_DATA_SIZE] = {0};

USB_HID_TEMPLATE Endpoint_Default(ENDPOINT_DEFAULT_DATA_SIZE, false);

static void Template_EventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == ARDUINO_USB_HID_TEMPLATE_EVENTS)
    {
        arduino_usb_hid_template_event_data_t *data = (arduino_usb_hid_template_event_data_t *)event_data;
        switch (event_id)
        {
        case ARDUINO_USB_HID_TEMPLATE_GET_FEATURE_EVENT:
            Serial.printf("HID Get Feature Size: %u\n", data->len);
            break;
        case ARDUINO_USB_HID_TEMPLATE_SET_FEATURE_EVENT:
            Serial.printf("HID Set Feature Size: %u\n", data->len);
            Serial.printf("Receive Data: \n    ");
            for (int i = 0; i < ENDPOINT_DEFAULT_DATA_SIZE; i++)
            {
                if ((i != 0) && ((i % 10) == 0))
                {
                    Serial.printf("|\n    ");
                }
                Serial.printf("| %d ", Endpoint_Default_Data[i]);
            }
            Serial.printf("|\n    ");
            Serial.println();
            break;
        case ARDUINO_USB_HID_TEMPLATE_OUTPUT_EVENT:
            Serial.printf("HID Available Size: %u\n", data->len);
            break;

        default:
            break;
        }
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(KEY_1, INPUT_PULLUP);

    Endpoint_Default.onEvent(Template_EventCallback);
    Endpoint_Default.begin();

    USB.VID(USB_T_KEYBOARD_S3_VID);
    USB.PID(USB_T_KEYBOARD_S3_PID);
    USB.manufacturerName(USB_MANUFACTURER_NAME);
    USB.firmwareVersion(USB_T_KEYBOARD_S3_REV);

    USB.begin();
}

void loop()
{
    if (digitalRead(KEY_1) == LOW)
    {
        delay(300);
        Endpoint_Default.printf("Ciallo");
    }

    while (Endpoint_Default.available())
    {
        Endpoint_Default.read(Endpoint_Default_Data, ENDPOINT_DEFAULT_DATA_SIZE);

        Serial.printf("Receive Data: \n    ");
        for (int i = 0; i < ENDPOINT_DEFAULT_DATA_SIZE; i++)
        {
            if ((i != 0) && ((i % 10) == 0))
            {
                Serial.printf("|\n    ");
            }
            Serial.printf("| %d ", Endpoint_Default_Data[i]);
        }
        Serial.printf("|\n    ");
    }
}
#endif /* ARDUINO_USB_MODE */
