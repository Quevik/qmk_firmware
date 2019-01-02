#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#ifdef TAP_DANCE_ENABLE
#include "q_tap_dance.h"
#endif

#ifdef TAP_DANCE_ENABLE
#define TDLT TD(TD_LT)
#define TDGT TD(TD_GT)
#define TDMD TD(TD_MEDIADN)
#define TDMU TD(TD_MEDIAUP)
#endif
