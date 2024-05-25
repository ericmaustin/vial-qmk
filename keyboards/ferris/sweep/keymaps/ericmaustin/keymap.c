// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
#include <stdint.h>
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include "keymap_us.h"
#include "caps_word.h"
#include "secrets.h"
#include "send_string_keycodes.h"
#include "process_auto_shift.h"

enum layers {
  BASE,
  COLEMAK, // classic querty layout
  SYMS, // symbols layer
  NUMS, // nums and f keys
  NUMPAD, // numpad
  FNS, // f keys, media keys, OSM keys
  NAV, // navigation layer
  // MOUSE, // mouse layer
  MACRO // macro layer
};

/* one shot mods */
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)

/* hr mods */
#define HR_CTL_A LCTL_T(KC_A)
#define HR_ALT_S LALT_T(KC_S)
#define HR_GUI_D LGUI_T(KC_D)
#define HR_SFT_F LSFT_T(KC_F)

#define HR_SFT_J LSFT_T(KC_J)
#define HR_GUI_K LGUI_T(KC_K)
#define HR_ALT_L LALT_T(KC_L)
#define HR_CTL_P LCTL_T(KC_P)

/* lt keys */
#define LT_BSPC LT(NUMS, KC_BSPC)
#define LT_SPC  LT(SYMS, KC_SPC)
#define LT_TAB  LT(FNS, KC_TAB)
#define LT_ENT  LT(FNS, KC_ENT)

/* media keys */
#define C_PLP KC_MEDIA_PLAY_PAUSE
#define C_NXT KC_MEDIA_NEXT_TRACK
#define C_PRV KC_MEDIA_PREV_TRACK
#define C_MTE KC_AUDIO_MUTE
#define C_VLU KC_AUDIO_VOL_UP
#define C_VLD KC_AUDIO_VOL_DOWN
#define C_BRU KC_BRIGHTNESS_UP
#define C_BRD KC_BRIGHTNESS_DOWN

/* mouse keys */
#define M_UP KC_MS_UP
#define M_DN KC_MS_DOWN
#define M_LT KC_MS_LEFT
#define M_RT KC_MS_RIGHT
#define M_LCK KC_MS_BTN1
#define M_RCK KC_MS_BTN2
#define M_MCK KC_MS_BTN3
#define M_WUP KC_MS_WH_UP
#define M_WDN KC_MS_WH_DOWN
#define M_WLT KC_MS_WH_LEFT
#define M_WRT KC_MS_WH_RIGHT

enum custom_keycodes {
  KC_LCAR = SAFE_RANGE,
  KC_RCAR,
  M_SEC_0,
  M_SEC_1,
  M_SEC_2,
  M_SEC_3,
  M_SEC_4,
  M_SEC_5,
  M_SEC_6,
  M_SEC_7,
};

/* autoshift mods */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LCTL_T(KC_A):
            return true;
        case LALT_T(KC_S):
            return true;
        default:
            return false;
    }
}

/* keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
      KC_Q,         KC_W,         KC_E,         KC_R,          KC_T,             KC_Y,          KC_U,         KC_I,         KC_O,         KC_QUOT,
      HR_CTL_A,     HR_ALT_S,     HR_GUI_D,     HR_SFT_F,      KC_G,             KC_H,          LSFT_T(KC_J), LGUI_T(KC_K), LALT_T(KC_L), LCTL_T(KC_P),
      KC_Z,         KC_V,         KC_X,         KC_C,          KC_B,             KC_K,          KC_M,         KC_COMM,      KC_DOT,       KC_QUES,
                                  LT(NUMS, KC_BSPC),  LT(NAV, KC_ENT),     LT(FNS, KC_TAB), LT(SYMS, KC_SPC)
  ),
  [SYMS] = LAYOUT(
      CW_TOGG,        KC_AT,              KC_HASH,            KC_DLR,            KC_PERC,       KC_CIRC,      KC_AMPR,         KC_ASTR,         KC_PIPE,         KC_CAPS_LOCK,
      KC_GRAVE, LALT_T(S(KC_LBRC)), LGUI_T(KC_LBRC),    LSFT_T(KC_LPRN),         KC_LCAR,       KC_PLUS,      LSFT_T(KC_MINS), LGUI_T(KC_COLN), LALT_T(KC_SLSH), KC_ENT,
      KC_TILD,        S(KC_RBRC),         KC_RBRC,            KC_RPRN,           KC_RCAR,       KC_EQUAL,     KC_UNDS,         KC_SCLN,         KC_BSLS,         S(KC_QUOTE),
    //                                                                                                          <HELD>
                                                              KC_DEL,            KC_ESC,        LT(FNS, KC_TAB), KC_SPC
  ),
  [NUMS] = LAYOUT(
      KC_F1,        KC_F2,        KC_F3,        KC_F4,         KC_F5,            KC_F6,         KC_F7,        KC_F8,        KC_9,          KC_F10,
      LCTL_T(KC_1), LALT_T(KC_2), LGUI_T(KC_3), LSFT_T(KC_4),  KC_5,             KC_6,          LSFT_T(KC_7), LGUI_T(KC_8), LALT_T(KC_9),  LCTL_T(KC_0),
      KC_F11,       KC_DOLLAR,    KC_KP_ASTERISK, KC_HASH,     KC_KP_SLASH,      KC_KP_EQUAL,   KC_KP_MINUS,  KC_KP_PLUS,   KC_KP_DOT,     KC_F12,

      //                                        <HELD>
                                                KC_BSPC,       KC_ENT,          LT(FNS, S(KC_TAB)), LT(NUMPAD, KC_0)
  ),
  [NUMPAD] = LAYOUT(
      KC_EXLM,     KC_AT,         KC_HASH,      KC_DLR,        KC_PERC,          KC_SLSH,        KC_1,         KC_2,         KC_3,         KC_ASTR,
      KC_SPC,      S(KC_RBRC),    KC_LBRC,      KC_LPRN,       KC_LCAR,          KC_MINS,        KC_4,         KC_5,         KC_6,         KC_PLUS,
      KC_BSPC,     S(KC_LBRC),    KC_RBRC,      KC_RPRN,       KC_RCAR,          KC_EQUAL,       KC_7,         KC_8,         KC_9,         KC_DOT,
                                                KC_BSPC,       KC_ENT,           TO(FNS),        LT(SYMS, KC_0)
  ),
  [NAV] = LAYOUT(
      KC_ESC,       C(S(KC_D)),    G(KC_SPC),   A(KC_SPC),     KC_PRINT_SCREEN,  KC_PAGE_UP,     A(KC_LEFT),   KC_UP,       A(KC_RIGHT),   KC_NO,
      KC_LCTL,      KC_LALT,       KC_LGUI,     KC_LSFT,       C(KC_UP),         KC_HOME,        KC_LEFT,      KC_DOWN,     KC_RIGHT,      KC_END,
      S(C(KC_TAB)), S(G(KC_TAB)),  G(KC_TAB),   C(KC_TAB),     C(KC_DOWN),       KC_PAGE_DOWN,   KC_INS,       S(KC_TAB),   KC_TAB,        KC_NO,
      //                                                       <HELD>
                                                KC_BSPC,       KC_ENT,           LT(FNS, S(KC_TAB)),  KC_SPC
  ),
  [FNS] = LAYOUT(
      C_BRD,        C_BRU,         C_VLD,       C_VLU,         C_MTE,             C_PLP,       C_PRV,        C_NXT,       S(C(KC_2)),    S(C(KC_1)),
      OSM_CTL,      OSM_ALT,       OSM_GUI,     OSM_SFT,       KC_NO,             KC_NO,       TO(BASE),     TO(NUMS),    TO(NAV),       TO(MOUSE),
      G(KC_Z),      G(KC_X),       G(KC_C),     G(KC_V),       KC_NO,             KC_NO,       OSL(MACRO),   OSL(NUMS),   OSL(NAV),      OSL(MOUSE),
      //                                                                         <HELD>
                                                KC_BSPC,       MO(MOUSE),        KC_TRNS,        KC_NO
  ),
  [MACRO] = LAYOUT(
    KC_NO,         KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,
    M_SEC_3,       M_SEC_2,       M_SEC_1,      M_SEC_0,       KC_NO,            KC_NO,          KC_NO,        KC_NO,       KC_NO,        KC_NO,
    KC_NO,         KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                                KC_NO,         KC_NO,            TO(FNS),        KC_NO
  ),
  // [MOUSE] = LAYOUT(
  //     KC_ESC,       KC_MS_ACCEL2,  KC_MS_ACCEL1,KC_MS_ACCEL0,  KC_MS_BTN3,       KC_MS_WH_UP,    KC_MS_WH_UP,  KC_MS_U,    KC_MS_WH_DOWN, KC_DEL,
  //     KC_LCTL,      KC_LALT,       KC_LGUI,     KC_LSFT,       KC_MS_BTN1,       KC_MS_WH_LEFT,  KC_MS_L,      KC_MS_D,    KC_MS_R,       KC_MS_WH_RIGHT,
  //     S(C(KC_TAB)), S(G(KC_TAB)),  G(KC_TAB),   C(KC_TAB),     KC_MS_BTN2,       KC_MS_WH_DOWN,  KC_INS,      S(KC_TAB),   KC_TAB,        KC_BSPC,
  //     //                                                       <HELD>            <HELD>
  //                                               KC_BSPC,       KC_ENT,           TO(FNS),        KC_SPC
  // ),
// };

// /* key overrides */
// const key_override_t **key_overrides = (const key_override_t *[]){
//     // SHIFT(?) = !
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM)),
//     // SHIFT(,) = ;
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN)),
//     // SHIFT(.) = :
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLON)),
//     /* SHIFT(/) = \ */
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_SLASH, KC_BACKSLASH)),
//     /* SHIFT(spc) = tab */
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB)),
//     /* SHIFT(bspc) = del */
//     &(ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL)),
//     NULL
// };

// /* combos */
// enum combos {
//   HJ_COPY,
//   YJ_CUT,
//   GB_PASTE,
//   FB_UNDO,
// };
//
// define this
// hello my name is This

// const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
// const uint16_t PROGMEM yj_combo[] = {KC_Y, KC_J, COMBO_END};
// const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
// const uint16_t PROGMEM fb_combo[] = {KC_F, KC_B, COMBO_END};

// combo_t key_combos[] = {
//   [HJ_COPY] = COMBO(hj_combo, KC_COPY),
//   [YJ_CUT] = COMBO(yj_combo, KC_CUT),
//   [GB_PASTE] = COMBO(gb_combo, KC_PASTE),
//   [FB_UNDO] = COMBO(fb_combo, KC_UNDO),
// };

/* custom record processing */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_SEC_0:
      if (record->event.pressed) {
        send_string(SECRET_0);
      }
      return false;
    case M_SEC_1:
        if (record->event.pressed) {
          send_string(SECRET_1);
        }
        return false;
    case M_SEC_2:
        if (record->event.pressed) {
          send_string(SECRET_2);
        }
        return false;
    case M_SEC_3:
        if (record->event.pressed) {
          send_string(SECRET_3);
        }
        return false;
    case M_SEC_4:
        if (record->event.pressed) {
          send_string(SECRET_4);
        }
        return false;
    case M_SEC_5:
        if (record->event.pressed) {
          send_string(SECRET_5);
        }
        return false;
    case KC_LCAR:
      if (record->event.pressed) {
        send_string("<");
      }
      return false;
    case KC_RCAR:
      if (record->event.pressed) {
        send_string(">");
      }
      return false;
  }

  return true;
};
