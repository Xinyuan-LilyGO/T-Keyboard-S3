/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2024-07-05 15:05:22
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-07-06 10:57:32
 * @License: GPL 3.0
 */

#include "USBHID.h"

#if CONFIG_TINYUSB_HID_ENABLED

#include "esp32-hal-log.h"
#include "USB_HID_Template.h"

enum
{
    HID_REPORT_ID_DEFAULT = 0x01, // 默认报点ID
};

ESP_EVENT_DEFINE_BASE(ARDUINO_USB_HID_TEMPLATE_EVENTS);
esp_err_t arduino_usb_event_post(esp_event_base_t event_base, int32_t event_id, void *event_data, size_t event_data_size, TickType_t ticks_to_wait);
esp_err_t arduino_usb_event_handler_register_with(esp_event_base_t event_base, int32_t event_id, esp_event_handler_t event_handler, void *event_handler_arg);

// HID Generic Input, Output & Feature
// - 1st parameter is report size (mandatory)
// - 2nd parameter is report id HID_REPORT_ID(n) (optional)
#define TUD_HID_REPORT_DESC_GENERIC_INOUT_FEATURE(report_size, ...) \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2),                     \
        HID_USAGE(0x01),                                            \
        HID_COLLECTION(HID_COLLECTION_APPLICATION),                 \
        __VA_ARGS__          /* Report ID if any */                 \
            HID_USAGE(0x02), /* Input */                            \
        HID_LOGICAL_MIN(0x00),                                      \
        HID_LOGICAL_MAX(0xff),                                      \
        HID_REPORT_SIZE(8),                                         \
        HID_REPORT_COUNT(report_size),                              \
        HID_INPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE),          \
        HID_USAGE(0x03), /* Output */                               \
        HID_LOGICAL_MIN(0x00),                                      \
        HID_LOGICAL_MAX(0xff),                                      \
        HID_REPORT_SIZE(8),                                         \
        HID_REPORT_COUNT(report_size),                              \
        HID_OUTPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE),         \
        HID_USAGE(0x04), /* Feature */                              \
        HID_LOGICAL_MIN(0x00),                                      \
        HID_LOGICAL_MAX(0xff),                                      \
        HID_REPORT_SIZE(8),                                         \
        HID_REPORT_COUNT(report_size),                              \
        HID_FEATURE(HID_DATA | HID_VARIABLE | HID_ABSOLUTE),        \
        HID_COLLECTION_END

#define TUD_HID_REPORT_DESC_GENERIC_INOUT_FEATURE_LEN 46

// max size is 64 and we need one byte for the report ID
static uint8_t HID_VENDOR_REPORT_SIZE = 63;
static uint8_t feature[64];
static xQueueHandle rx_queue = NULL;
static bool prepend_size = false;

USB_HID_TEMPLATE::USB_HID_TEMPLATE(uint8_t report_size, bool prepend) : hid()
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        hid.addDevice(this, TUD_HID_REPORT_DESC_GENERIC_INOUT_FEATURE_LEN);
        memset(feature, 0, 64);
        if (report_size < 64)
        {
            HID_VENDOR_REPORT_SIZE = report_size;
        }
        prepend_size = prepend;
    }
}

uint16_t USB_HID_TEMPLATE::_onGetDescriptor(uint8_t *dst)
{
    uint8_t report_descriptor[] = {
        TUD_HID_REPORT_DESC_GENERIC_INOUT_FEATURE(HID_VENDOR_REPORT_SIZE, HID_REPORT_ID(HID_REPORT_ID_DEFAULT))};
    memcpy(dst, report_descriptor, sizeof(report_descriptor));
    return sizeof(report_descriptor);
}

void USB_HID_TEMPLATE::prependInputPacketsWithSize(bool enable)
{
    prepend_size = enable;
}

size_t USB_HID_TEMPLATE::setRxBufferSize(size_t rx_queue_len)
{
    if (rx_queue)
    {
        if (!rx_queue_len)
        {
            vQueueDelete(rx_queue);
            rx_queue = NULL;
        }
        return 0;
    }
    rx_queue = xQueueCreate(rx_queue_len, sizeof(uint8_t));
    if (!rx_queue)
    {
        return 0;
    }
    return rx_queue_len;
}

void USB_HID_TEMPLATE::begin()
{
    hid.begin();
    setRxBufferSize(256); // default if not preset
}

void USB_HID_TEMPLATE::end()
{
    setRxBufferSize(0);
}

void USB_HID_TEMPLATE::onEvent(esp_event_handler_t callback)
{
    onEvent(ARDUINO_USB_HID_TEMPLATE_ANY_EVENT, callback);
}

void USB_HID_TEMPLATE::onEvent(arduino_usb_hid_template_event_t event, esp_event_handler_t callback)
{
    arduino_usb_event_handler_register_with(ARDUINO_USB_HID_TEMPLATE_EVENTS, event, callback, this);
}

uint16_t USB_HID_TEMPLATE::_onGetFeature(uint8_t report_id, uint8_t *buffer, uint16_t len)
{
    if (report_id != HID_REPORT_ID_DEFAULT)
    {
        return 0;
    }
    memcpy(buffer, feature, len);
    arduino_usb_hid_template_event_data_t p;
    p.buffer = feature;
    p.len = len;
    arduino_usb_event_post(ARDUINO_USB_HID_TEMPLATE_EVENTS, ARDUINO_USB_HID_TEMPLATE_GET_FEATURE_EVENT, &p, sizeof(arduino_usb_hid_template_event_data_t), portMAX_DELAY);
    return len;
}

void USB_HID_TEMPLATE::_onSetFeature(uint8_t report_id, const uint8_t *buffer, uint16_t len)
{
    if (report_id != HID_REPORT_ID_DEFAULT)
    {
        return;
    }
    memcpy(feature, buffer, len);
    arduino_usb_hid_template_event_data_t p;
    p.buffer = feature;
    p.len = len;
    arduino_usb_event_post(ARDUINO_USB_HID_TEMPLATE_EVENTS, ARDUINO_USB_HID_TEMPLATE_SET_FEATURE_EVENT, &p, sizeof(arduino_usb_hid_template_event_data_t), portMAX_DELAY);
}

void USB_HID_TEMPLATE::_onOutput(uint8_t report_id, const uint8_t *buffer, uint16_t len)
{
    if (report_id != HID_REPORT_ID_DEFAULT)
    {
        return;
    }
    for (uint32_t i = 0; i < len; i++)
    {
        if (rx_queue == NULL || !xQueueSend(rx_queue, buffer + i, 0))
        {
            len = i + 1;
            log_e("RX Queue Overflow");
            break;
        }
    }
    arduino_usb_hid_template_event_data_t p;
    p.buffer = buffer;
    p.len = len;
    arduino_usb_event_post(ARDUINO_USB_HID_TEMPLATE_EVENTS, ARDUINO_USB_HID_TEMPLATE_OUTPUT_EVENT, &p, sizeof(arduino_usb_hid_template_event_data_t), portMAX_DELAY);
}

size_t USB_HID_TEMPLATE::write(const uint8_t *buffer, size_t len)
{
    uint8_t hid_in[HID_VENDOR_REPORT_SIZE];
    const uint8_t *data = (const uint8_t *)buffer;
    uint8_t size_offset = prepend_size ? 1 : 0;
    size_t to_send = len, max_send = HID_VENDOR_REPORT_SIZE - size_offset, will_send = 0;
    while (to_send)
    {
        will_send = to_send;
        if (will_send > max_send)
        {
            will_send = max_send;
        }
        if (prepend_size)
        {
            hid_in[0] = will_send;
        }
        // We can get INPUT only when data length equals the input report size
        memcpy(hid_in + size_offset, data, will_send);
        // pad with zeroes
        memset(hid_in + size_offset + will_send, 0, max_send - will_send);
        if (!hid.SendReport(HID_REPORT_ID_DEFAULT, hid_in, HID_VENDOR_REPORT_SIZE))
        {
            return len - to_send;
        }
        to_send -= will_send;
        data += will_send;
    }
    return len;
}

size_t USB_HID_TEMPLATE::write(uint8_t c)
{
    return write(&c, 1);
}

int USB_HID_TEMPLATE::available(void)
{
    if (rx_queue == NULL)
    {
        return -1;
    }
    return uxQueueMessagesWaiting(rx_queue);
}

int USB_HID_TEMPLATE::peek(void)
{
    if (rx_queue == NULL)
    {
        return -1;
    }
    uint8_t c;
    if (xQueuePeek(rx_queue, &c, 0))
    {
        return c;
    }
    return -1;
}

int USB_HID_TEMPLATE::read(void)
{
    if (rx_queue == NULL)
    {
        return -1;
    }
    uint8_t c = 0;
    if (xQueueReceive(rx_queue, &c, 0))
    {
        return c;
    }
    return -1;
}

size_t USB_HID_TEMPLATE::read(uint8_t *buffer, size_t size)
{
    if (rx_queue == NULL)
    {
        return -1;
    }
    uint8_t c = 0;
    size_t count = 0;
    while (count < size && xQueueReceive(rx_queue, &c, 0))
    {
        buffer[count++] = c;
    }
    return count;
}

void USB_HID_TEMPLATE::flush(void) {}

#endif /* CONFIG_TINYUSB_HID_ENABLED */
