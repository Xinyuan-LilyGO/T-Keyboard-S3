/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2024-07-06 10:37:45
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-07-06 11:01:57
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

#define KEY_1 0
#define Vendor_DATA_SIZE 63
#define USB_T_KEYBOARD_S3_VID 0xFF81
#define USB_T_KEYBOARD_S3_PID 0x0001
#define USB_T_KEYBOARD_S3_REV 0x0001
#define USB_MANUFACTURER_NAME "LILYGO"

uint8_t Vendor_Data[Vendor_DATA_SIZE] = {0};

USBHIDVendor Vendor(Vendor_DATA_SIZE, false);

static void Vendor_EventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == ARDUINO_USB_HID_VENDOR_EVENTS)
    {
        arduino_usb_hid_vendor_event_data_t *data = (arduino_usb_hid_vendor_event_data_t *)event_data;
        switch (event_id)
        {
        case ARDUINO_USB_HID_VENDOR_GET_FEATURE_EVENT:
            Serial.printf("HID Get Feature Size: %u\n", data->len);
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

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(KEY_1, INPUT_PULLUP);

    Vendor.onEvent(Vendor_EventCallback);
    Vendor.begin();

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
        Vendor.printf("Ciallo");
    }

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
