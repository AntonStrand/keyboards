#ifdef COMBO_TERM
#    undef COMBO_TERM
// Combo feature timeout (defaults to TAPPING_TERM)
#endif
#define COMBO_TERM 150

#ifdef COMBO_COUNT
#    undef COMBO_COUNT
#endif
// Size of combo_events enum.
#define COMBO_COUNT 4
