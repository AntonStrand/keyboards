// #ifdef TAPPING_TERM
// #    undef TAPPING_TERM
// #endif
//
// #define TAPPING_TERM 200
//
// #if !defined(TAPPING_TOGGLE)
// #    define TAPPING_TOGGLE 2
// #endif

#define TAPPING_TERM 200
#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped this number of times again. */
#define ONESHOT_TIMEOUT 1000  /* Time (in ms) before the one shot key is released */

#ifndef NO_DEBUG
#   define NO_DEBUG
#endif // !NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#   define NO_PRINT
#endif // !NO_PRINT

// this makes it possible to do rolling combos (fa) with keys that
// convert to other keys on hold (f becomes cmd when you hold it,
// and when this option isn't enabled, f rapidly followed by a
// actually sends Cmd-a. That's bad.)
#undef PERMISSIVE_HOLD
