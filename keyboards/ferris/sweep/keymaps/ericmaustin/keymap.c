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

/* custom types */
struct macro_t {
  const uint16_t kc;
  const char *str;
};

enum layers {
  BASE,
  // CANARY, // canary alt layout
  SYMS, // symbols layer
  NUMS, // nums and f keys
  NUMPAD, // numpad
  FNS, // f keys, media keys, OSM keys
  NAV, // navigation layer
  MOUSE, // mouse layer
  MACRO // macro layer
};

/* layer keys */
#define LT_SPC LT(SYMS, KC_SPC)
#define LT_BSP LT(NUMS, KC_BSPC)
#define LT_ESC LT(NAV, KC_ESC)
#define LT_DEL LT(NAV, KC_DEL)
#define LT_ENT LT(FNS, KC_ENT)

/* one shot mods */
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_HYPR OSM(MOD_HYPR)
#define OSM_MEH OSM(MOD_MEH)
#define OSM_CAG OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)
#define OSM_AS  OSM(MOD_LSFT | MOD_LALT)

/* media keys */
#define C_PP KC_MEDIA_PLAY_PAUSE
#define C_NXT KC_MEDIA_NEXT_TRACK
#define C_PRV KC_MEDIA_PREV_TRACK
#define C_MUTE KC_AUDIO_MUTE
#define C_VOLU KC_AUDIO_VOL_UP
#define C_VOLD KC_AUDIO_VOL_DOWN
#define C_BRU KC_BRIGHTNESS_UP
#define C_BRD KC_BRIGHTNESS_DOWN

/* MACROS */
enum macros {
  M_SEC0 = SAFE_RANGE,
  M_SEC1,
  M_SEC2,
  M_SEC3,
  M_SEC4,
  M_SEL_WRD,
  M_SEL_LN,
  M_CP_WRD,
  M_CP_LN,
  M_NL_ABV,
  M_NL,
};

const struct macro_t PROGMEM macros[] = {
  {M_SEC0, SECRET_0},
  {M_SEC1, SECRET_1},
  {M_SEC2, SECRET_2},
  {M_SEC3, SECRET_3},
  {M_SEC4, SECRET_4},
  {M_SEL_WRD, SS_TAP(X_RIGHT) SS_LALT(SS_TAP(X_LEFT)) SS_LALT(SS_LSFT(SS_TAP(X_RIGHT)))},
  {M_SEL_LN, SS_TAP(X_HOME) SS_LALT(SS_LSFT(SS_TAP(X_END)))},
  {M_CP_WRD, SS_TAP(X_RIGHT) SS_LALT(SS_TAP(X_LEFT)) SS_LALT(SS_LSFT(SS_TAP(X_RIGHT))) SS_TAP(X_COPY)},
  {M_CP_LN, SS_TAP(X_HOME) SS_LALT(SS_LSFT(SS_TAP(X_END)))  SS_TAP(X_COPY)},
  {M_NL, SS_TAP(X_END) SS_TAP(X_ENTER)},
  {M_NL_ABV, SS_TAP(X_UP) SS_TAP(X_END) SS_TAP(X_ENTER)},
};

enum custom_keycodes {
  KC_LCAR = SAFE_RANGE,
  KC_RCAR
};

// /* tap dance keys */
// enum tap_dance {
//     TD_CAPS  // CW_TOGG, KC_CAPS
// };

// // Tap Dance definitions
// tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(CW_TOGG, KC_CAPS),
// };

/* keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
      KC_Q,         KC_W,         KC_E,         KC_R,          KC_T,             KC_Y,          KC_U,         KC_I,         KC_O,         KC_QUOT,
      LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F),  KC_G,             KC_H,          LSFT_T(KC_J), LGUI_T(KC_K), LALT_T(KC_L), LCTL_T(KC_P),
      KC_Z,         KC_X,         KC_C,         KC_V,          KC_B,             KC_N,          KC_M,         KC_COMM,      KC_DOT,       KC_QUES,
                                                LT_BSP,        LT_DEL,           LT_ENT,        LT_SPC
  ),
  // [CANARY] = LAYOUT(
  //     KC_W,         KC_L,         KC_Y,         KC_P,          KC_B,             KC_Z,          KC_F,         KC_O,         KC_U,         KC_QUOT,
  //     LCTL_T(KC_C), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T),  KC_G,             KC_M,          LSFT_T(KC_N), LGUI_T(KC_E), LALT_T(KC_I), LCTL_T(KC_A),
  //     KC_Q,         KC_J,         KC_V,         KC_D,          KC_K,             KC_X,          KC_H,         KC_COMM,      KC_DOT,       KC_QUES,
  //                                               LT_BSP,        LT_DEL,           LT_ENT,        LT_SPC
  // ),
  [SYMS] = LAYOUT(
      CW_TOGG,        KC_AT,              KC_HASH,            KC_DLR,            KC_PERC,       KC_CIRC,      KC_AMPR,         KC_ASTR,         KC_PIPE,         KC_GRV,
      LCTL_T(KC_TAB), LALT_T(S(KC_LBRC)), LGUI_T(KC_LBRC),    LSFT_T(KC_LPRN),   KC_LCAR,       KC_PLUS,      LSFT_T(KC_MINS), LGUI_T(KC_COLN), LALT_T(KC_SLSH), LCTL_T(S(KC_QUOT)),
      S(KC_TAB),      S(KC_RBRC),         KC_RBRC,            KC_RPRN,           KC_RCAR,       KC_EQUAL,     KC_UNDS,         KC_SCLN,         KC_BSLS,         KC_TILD,
    //                                                                                                      <HELD>
                                                              KC_DEL,            KC_ESC,        LT_ENT,       KC_SPC
  ),
  [NUMS] = LAYOUT(
      KC_F1,        KC_F2,        KC_F3,        KC_F4,         KC_F5,            KC_F6,         KC_F7,        KC_F8,        KC_9,          KC_F10,
      LCTL_T(KC_1), LALT_T(KC_2), LGUI_T(KC_3), LSFT_T(KC_4),  KC_5,             KC_6,          LSFT_T(KC_7), LGUI_T(KC_8), LALT_T(KC_9),  LCTL_T(KC_0),
      KC_F11,       KC_F12,       KC_DOLLAR,    KC_ASTR,       KC_HASH,          KC_EQUAL,      KC_MINS,      KC_PLUS,      KC_DOT,        KC_SLASH,

      //                                        <HELD>
                                                KC_BSPC,       KC_DOT,           LT_ENT,        LT(SYMS, KC_0)
  ),
  [NUMPAD] = LAYOUT(
      KC_EXLM,     KC_AT,         KC_HASH,      KC_DLR,        KC_PERC,          KC_SLSH,        KC_1,         KC_2,         KC_3,         KC_ASTR,
      KC_SPC,      S(KC_RBRC),    KC_LBRC,      KC_LPRN,       KC_LCAR,          KC_MINS,        KC_4,         KC_5,         KC_6,         KC_PLUS,
      KC_BSPC,     S(KC_LBRC),    KC_RBRC,      KC_RPRN,       KC_RCAR,          KC_EQUAL,       KC_7,         KC_8,         KC_9,         KC_DOT,
                                                KC_BSPC,       KC_DEL,           LT_ENT,         LT(SYMS, KC_0)
  ),
  [NAV] = LAYOUT(
      KC_ESC,       C(S(KC_D)),    G(KC_SPC),   A(KC_SPC),     KC_PRINT_SCREEN,  KC_PAGE_UP,     A(KC_LEFT),   KC_UP,       A(KC_RIGHT),   M_NL_ABV,
      KC_LCTL,      KC_LALT,       KC_LGUI,     KC_LSFT,       C(KC_UP),         KC_HOME,        KC_LEFT,      KC_DOWN,     KC_RIGHT,      KC_END,
      S(C(KC_TAB)), S(G(KC_TAB)),  G(KC_TAB),   C(KC_TAB),     C(KC_DOWN),       KC_PAGE_DOWN,   KC_INS,       S(KC_TAB),   KC_TAB,        M_NL,
      //                                                       <HELD>
                                                KC_BSPC,       KC_DEL,           MO(FNS),        KC_SPC
  ),
  [FNS] = LAYOUT(
      C_BRD,        C_BRU,         C_VOLD,      C_VOLU,        C_MUTE,           C_PP,           C_PRV,        C_NXT,       S(C(KC_2)),    S(C(KC_1)),
      OSM_CTL,      OSM_ALT,       OSM_GUI,     OSM_SFT,       M_CP_WRD,         M_SEL_WRD,      TO(BASE),     TO(NUMS),    TO(NAV),       TO(MOUSE),
      KC_UNDO,      KC_CUT,        KC_COPY,     KC_PASTE,      M_CP_LN,          M_SEL_LN,       OSL(MACRO),   OSL(NUMS),   OSL(NAV),      KC_CAPS,
      //                                                                         <HELD>
                                                KC_BSPC,       MO(MOUSE),        KC_TRNS,        KC_NO
  ),
  [MACRO] = LAYOUT(
    KC_NO,         KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,
    KC_NO,         M_SEC4,        M_SEC2,       M_SEC0,        KC_NO,            KC_NO,          M_SEC1,       M_SEC3,       KC_NO,        KC_NO,
    KC_NO,         KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO,          KC_NO,        KC_NO,        KC_NO,        KC_NO,
                                                KC_NO,         KC_NO,            TO(FNS),        KC_NO
  ),
  [MOUSE] = LAYOUT(
      KC_ESC,       KC_MS_ACCEL2,  KC_MS_ACCEL1,KC_MS_ACCEL0,  KC_MS_BTN3,       KC_MS_WH_UP,    KC_MS_WH_UP,  KC_MS_U,    KC_MS_WH_DOWN, KC_DEL,
      KC_LCTL,      KC_LALT,       KC_LGUI,     KC_LSFT,       KC_MS_BTN1,       KC_MS_WH_LEFT,  KC_MS_L,      KC_MS_D,    KC_MS_R,       KC_MS_WH_RIGHT,
      S(C(KC_TAB)), S(G(KC_TAB)),  G(KC_TAB),   C(KC_TAB),     KC_MS_BTN2,       KC_MS_WH_DOWN,  KC_INS,      S(KC_TAB),   KC_TAB,        KC_BSPC,
      //                                                       <HELD>            <HELD>
                                                KC_BSPC,       KC_DEL,           TO(FNS),        KC_SPC
  ),
};

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
  // handle macros
  if (record->event.pressed) {
    for (uint8_t i = 0; i < sizeof(macros) / sizeof(macros[0]); i++) {
      if (keycode == macros[i].kc) {

        break;
      }
    }
  }

  switch(keycode) {
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
