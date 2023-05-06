#pragma once

// #undef PRODUCT
// #define PRODUCT   Crkbd Naginata Style V15

#define MASTER_LEFT
#define USE_SERIAL_PD2
#define SPLIT_USB_DETECT

#define TAPPING_TERM 300
#define USB_MAX_POWER_CONSUMPTION 100

#define OLED_UPDATE_INTERVAL 100
#define OLED_TIMEOUT 60000

// LinuxでのUNICODE入力のために必要な設定
#define USB_POLLING_INTERVAL_MS 8
#define TAP_CODE_DELAY 24