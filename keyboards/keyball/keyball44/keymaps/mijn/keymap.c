#include QMK_KEYBOARD_H

#include "quantum.h"

#ifdef MACCEL_ENABLE
    #include "maccel/maccel.h"
#endif


enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _CONTROL,
  CONF
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define KC_MTCT MT(MOD_LCTL, KC_TAB) 
#define MT_C(X) MT(MOD_LCTL, X)
#define MT_A(X) MT(MOD_LALT, X)
#define MT_G(X) MT(MOD_LGUI, X)
#define MT_S(X) MT(MOD_LSFT, X)
#define _CTL(X) LT(_CONTROL, X)


const uint16_t PROGMEM test_combo1[] = {MT_C(KC_F), MT_C(KC_J), COMBO_END};
combo_t key_combos[1] = {
  COMBO(test_combo1, QK_CAPS_WORD_TOGGLE)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_universal(
      QK_GESC,   KC_Q,       KC_W,       KC_E,       KC_R, KC_T,          KC_Y,        KC_U,       KC_I,       KC_O,    KC_P,  KC_BSPC,
      KC_MTCT,   _CTL(KC_A), MT_G(KC_S), MT_S(KC_D), MT_C(KC_F), KC_G,          KC_H,  MT_C(KC_J), MT_S(KC_K), MT_G(KC_L), _CTL(KC_SCLN), KC_ENTER,
      KC_LSFT,   KC_Z,       KC_X,       KC_C,       KC_V, KC_B,          KC_N,        KC_M,    KC_COMM,     KC_DOT, KC_SLSH, KC_BSLS,
      KC_PGDN,KC_PGUP,  MT_G(KC_ESC), LT(_LOWER,KC_BSPC),  SCRL_MO,  LT(_RAISE, KC_ENTER), LT(_RAISE,KC_SPC), _______,   _______  , KC_MPLY
    ),                         

  [_LOWER] = LAYOUT_universal(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS,  KC_EQL,  KC_DEL,
      KC_TAB,  KC_TILD, KC_UNDS, KC_PLUS, KC_PIPE, KC_DQT,                       KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT,KC_DQT, KC_GRV,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_TRNS, _______,
      _______  , _______ , _______  ,         _______  , _______  ,        _______  , _______  , _______       , _______  , _______
    ),

  [_RAISE] = LAYOUT_universal(
  //,-----------------------------------------------------.                    ,---------------------------------------------------
       KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MTCT,  KC_GRV, KC_MINS, KC_EQL,  KC_BSLS, KC_QUOT,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,KC_QUOTE,KC_ENTER,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_COLN,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU,
      _______  , _______ , _______  ,         _______  , _______  ,        _______  , _______  , _______       , _______  , _______
 ),

  [_CONTROL] = LAYOUT_universal(
     KC_TRNS,  KC_GRV, KC_TRNS, KC_TRNS, KC_BTN3, KC_PGUP,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS,  KC_TAB, KC_TRNS, KC_BTN2, KC_BTN1, KC_PGDN,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
     KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
      _______  , _______ , _______  ,         _______  , _______  ,        _______  , _______  , _______       , _______  , _______
  ),

  [CONF] = LAYOUT_universal(
  QK_BOOT, _______, _______, _______, CPI_D100, CPI_I100,            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
  _______, _______, KBC_SAVE, _______, SCRL_DVD, SCRL_DVI,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, _______, _______, _______, _______, _______,            KC_F11,  KC_F12,  _______, _______, _______, _______,
  _______  , _______ , _______  ,         _______  , _______  ,        _______  , _______  , _______       , _______  , _______
   )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, CONF);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_G(KC_S):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT_S(KC_D):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT_C(KC_F):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT_C(KC_J):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT_S(KC_K):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT_G(KC_L):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    //keyball_oled_render_keyinfo();
    //keyball_oled_render_ballinfo();
    //keyball_oled_render_layerinfo();
}
#endif

#ifdef MACCEL_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (!keyball_get_scroll_mode())
    {
      return pointing_device_task_maccel(mouse_report);
    }
  else
    { return mouse_report; }
}
#endif
