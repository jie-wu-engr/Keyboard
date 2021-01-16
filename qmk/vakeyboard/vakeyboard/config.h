#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2040
#define DEVICE_VER      0x0001
#define MANUFACTURER    Vladimir Aubrecht
#define PRODUCT         vakeyboard
#define DESCRIPTION     VA Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */

#define EXP_A0 0xD0
#define EXP_A1 0xD1
#define EXP_A2 0xD2
#define EXP_A3 0xD3
#define EXP_A4 0xD4
#define EXP_A5 0xD5
#define EXP_A6 0xD6
#define EXP_A7 0xD7
#define EXP_B0 0xE0
#define EXP_B1 0xE1
#define EXP_B2 0xE2
#define EXP_B3 0xE3
#define EXP_B4 0xE4
#define EXP_B5 0xE5
#define EXP_B6 0xE6
#define EXP_B7 0xE7

#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0 }
#define MATRIX_COL_PINS { D6, EXP_A0, EXP_A1, EXP_A2, EXP_A3, EXP_A4, EXP_A5, EXP_A6, EXP_A7, EXP_B0, EXP_B1, EXP_B2, EXP_B3, EXP_B4, EXP_B5, EXP_B6, EXP_B7 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* disable these deprecated features by default */
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
#define NO_ACTION_TAPPING
