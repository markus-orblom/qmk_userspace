#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_RIGHT,
    LAYER_LEFT,
    LAYER_TRI,
    LAYER_POINTER,
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define SPC_RGT LT(LAYER_RIGHT, KC_SPC)
#define ENT_LFT LT(LAYER_LEFT, KC_ENT)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

enum unicode_names {
    U_ARNG_L, // å U+00E5
    U_ARNG_U, // Å U+00C5
    U_ADIA_L, // ä U+00E4
    U_ADIA_U, // Ä U+00C4
    U_ODIA_L, // ö U+00F6
    U_ODIA_U, // Ö U+00D6
};

const uint32_t PROGMEM unicode_map[] = {
    [U_ARNG_L] = 0x00E5, [U_ARNG_U] = 0x00C5,
    [U_ADIA_L] = 0x00E4, [U_ADIA_U] = 0x00C4,
    [U_ODIA_L] = 0x00F6, [U_ODIA_U] = 0x00D6,
};

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off

/**
 * \brief QWERTY base layer adapted from Ferris Sweep (cradio).
 *
 * Home row mods: GUI / CTRL / ALT / SHIFT (matching cradio order).
 * Thumb cluster (3 left + 2 right): ESC | TAB | LT(RIGHT,SPC) || LT(LEFT,ENT) | BSPC
 */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                       KC_ESC,  KC_TAB, SPC_RGT, ENT_LFT, KC_BSPC

/**
 * \brief Right layer: symbols + numbers (from cradio right_layer).
 *
 * Left hand: symbols (! @ { } \ / # $ [ ] ` / % ^ ( ) ~)
 * Right hand: numpad layout (7-9, 4-6, 1-3, 0) + = ; operators
 */
#define LAYOUT_LAYER_RIGHT                                                                    \
    KC_EXCL,   KC_AT, KC_LCBR, KC_RCBR, KC_BSLS, KC_SLSH,    KC_7,    KC_8,    KC_9,  KC_EQL, \
    KC_HASH,  KC_DLR, KC_LBRC, KC_RBRC,  KC_GRV, KC_ASTR,    KC_4,    KC_5,    KC_6, KC_SCLN, \
    KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD, KC_AMPR,    KC_1,    KC_2,    KC_3,    KC_0, \
                      _______, _______, _______, _______,  KC_DEL

/**
 * \brief Left layer: navigation (from cradio left_layer).
 *
 * ESC on Q, minus on A, arrows on right home row, PgDn/PgUp below, [ on P.
 */
#define LAYOUT_LAYER_LEFT                                                                     \
     KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UP(U_ARNG_L, U_ARNG_U), UP(U_ADIA_L, U_ADIA_U), UP(U_ODIA_L, U_ODIA_U), \
    KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, \
                      _______, _______, _______, _______, _______

/**
 * \brief Tri layer: system (QK_BOOT, EE_CLR).
 *
 * Activated when both RIGHT and LEFT layers are held (tri-layer).
 */
#define LAYOUT_LAYER_TRI                                                                      \
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, _______, _______, _______, _______

/**
 * \brief Pointer layer: trackball controls + mouse buttons.
 *
 * Accessed by holding Z (left) or / (right). Symmetrical layout.
 * Auto-sniping is enabled on this layer.
 */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX, XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, \
    _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

/**
 * \brief Add home row mods to a layout (GUI / CTRL / ALT / SHIFT order).
 *
 * Matches the Ferris Sweep (cradio) home row mod order, which differs from
 * the vendor's GACS order (GUI / ALT / CTRL / SHIFT).
 */
#define _HOME_ROW_MOD_GCTS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LCTL_T(L11), LALT_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), LALT_T(R17), RCTL_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GCTS(...) _HOME_ROW_MOD_GCTS(__VA_ARGS__)

/**
 * \brief Add pointer layer hold to bottom corner keys (Z and /).
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE]    = LAYOUT_wrapper(POINTER_MOD(HOME_ROW_MOD_GCTS(LAYOUT_LAYER_BASE))),
  [LAYER_RIGHT]   = LAYOUT_wrapper(LAYOUT_LAYER_RIGHT),
  [LAYER_LEFT]    = LAYOUT_wrapper(LAYOUT_LAYER_LEFT),
  [LAYER_TRI]     = LAYOUT_wrapper(LAYOUT_LAYER_TRI),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Tri-layer: both RIGHT and LEFT held activates TRI.
    state = update_tri_layer_state(state, LAYER_RIGHT, LAYER_LEFT, LAYER_TRI);

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

    return state;
}
