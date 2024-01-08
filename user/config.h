#ifndef USERSPACE
#define USERSPACE

#include "combos_config.h"

// #define RGB_DISABLE_WHEN_USB_SUSPENDED true

#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif

#define TAPPING_TERM 200

#if !defined(TAPPING_TOGGLE)
#    define TAPPING_TOGGLE 2
#endif

// this makes it possible to do rolling combos (fa) with keys that
// convert to other keys on hold (f becomes cmd when you hold it,
// and when this option isn't enabled, f rapidly followed by a
// actually sends Cmd-a. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD

// A side effect by lowering this number is that macros/send_string are typed faster.
#define USB_POLLING_INTERVAL_MS 2

#if defined(OLED_FONT_H)
#    undef OLED_FONT_H
#endif

#define OLED_FONT_H "users/antonstrand/glcdfont.c"

#endif
