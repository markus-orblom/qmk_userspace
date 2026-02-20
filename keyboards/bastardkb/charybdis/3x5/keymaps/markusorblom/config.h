#pragma once

#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif // VIA_ENABLE

#ifndef __arm__
#    define NO_ACTION_ONESHOT
#endif // __arm__
