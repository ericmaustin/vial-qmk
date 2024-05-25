// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "util.h"
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include "keymap_us.h"
#include "caps_word.h"
#include "secrets.h"
#include "send_string_keycodes.h"
#include "process_auto_shift.h"
#include "process_key_override.h"

enum layers {
  BSE, // base layer
  SYM, // symbols layer
  NMS, // nums and F key layers
  NMD, // numpad layer
  LNV, // left navigation layer
  RNV, // right navigation layer
  FNS, // f keys, media keys, OSM keys
  MSE, // mouse layer
};

/* one shot mods */
#define OS_SFT OSM(MOD_LSFT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_GUI OSM(MOD_LGUI)

/* lt keys */
#define L_SPC  LT(SYM, KC_SPC)
#define L_BSPC LT(NMS, KC_BSPC)
#define L_TAB  LT(MSE, KC_TAB)
#define L_ENT  LT(RNV, KC_ENT)
#define L_DEL  LT(LNV, KC_DEL)
#define L_ESC  LT(FNS, KC_ESC)

/* media keys */
#define C_PLP KC_MEDIA_PLAY_PAUSE
#define C_NXT KC_MEDIA_NEXT_TRACK
#define C_PRV KC_MEDIA_PREV_TRACK
#define C_MTE KC_AUDIO_MUTE
#define C_VLU KC_AUDIO_VOL_UP
#define C_VLD KC_AUDIO_VOL_DOWN
#define C_BRU KC_BRIGHTNESS_UP
#define C_BRD KC_BRIGHTNESS_DOWN

/* mouse key shortcuts */
#define MS_UP KC_MS_UP
#define MS_DN KC_MS_DOWN
#define MS_LT KC_MS_LEFT
#define MS_RT KC_MS_RIGHT
#define MS_LCK KC_MS_BTN1
#define MS_RCK KC_MS_BTN2
#define MS_MCK KC_MS_BTN3
#define MS_WUP KC_MS_WH_UP
#define MS_WDN KC_MS_WH_DOWN
#define MS_WLT KC_MS_WH_LEFT
#define MS_WRT KC_MS_WH_RIGHT
#define MS_AC0 KC_MS_ACCEL0
#define MS_AC1 KC_MS_ACCEL1
#define MS_AC2 KC_MS_ACCEL2

/* modded kp aliases */
#define A_RGHT LALT(KC_RGHT) // alt left
#define A_LEFT LALT(KC_LEFT) // alt right
#define S_TAB LSFT(KC_TAB) // shift alt tab
#define KC_LBCE S(KC_LBRC) // {
#define KC_RBCE S(KC_RBRC) // }
#define C_TAB C(KC_TAB) // ctrl tab
#define CS_TAB S(C(KC_TAB)) // ctrl shift tab
#define G_TAB G(KC_TAB) // gui tab
#define GS_TAB S(G(KC_TAB))  // shift gui tab
#define RYCST LCTL(KC_SPC)  // raycast
#define SPLT  G(KC_SPC) // split view
#define GS_1  G(S(KC_1))
#define GS_2  G(S(KC_2))
#define GS_3  G(S(KC_3))
#define PK_CLR G(C(A(KC_M)))

/* modded arrows */
#define C_LT    C(KC_LEFT)
#define C_RT    C(KC_RGHT)
#define C_UP    C(KC_UP)
#define C_DN    C(KC_DOWN)
#define G_LT    G(KC_LEFT)
#define G_RT    G(KC_RIGHT)
#define G_UP    G(KC_UP)
#define G_DN    G(KC_DOWN)

/* mac keycodes */
#define UNDO    G(KC_Z)
#define REDO    G(S(KC_Z))
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define QUIT    G(KC_A)
#define SAVE    G(KC_S)
#define OPEN    G(KC_O)
#define CLOSE   G(KC_W)
#define DOCK    G(A(KC_D))
#define SETG    G(KC_COMMA)
#define ZOOMIN  G(KC_EQL)
#define ZOOMOUT G(KC_MINS)
#define MINIM   G(KC_M)

/* hr mods */

// querty
#define MT_A LCTL_T(KC_A)
#define MT_S LALT_T(KC_S)
#define MT_D LGUI_T(KC_D)
#define MT_F LSFT_T(KC_F)
#define MT_J RSFT_T(KC_J)
#define MT_K RGUI_T(KC_K)
#define MT_L RALT_T(KC_L)
#define MT_P RCTL_T(KC_P)
// symbols
#define MT_LCAR LCTL_T(KC_LCAR)
#define MT_LBCE LALT_T(KC_LBCE)
#define MT_LBRC LGUI_T(KC_LBRC)
#define MT_LPRN LSFT_T(KC_LPRN)
#define MT_SLSH RSFT_T(KC_SLSH)
#define MT_UNDS RGUI_T(KC_UNDS)
#define MT_SCLN RGUI_T(KC_SCLN)
#define MT_COLN RALT_T(KC_COLN)
#define MT_DQUO RCTL_T(KC_DQUO)
// nums
#define MT_1 LCTL_T(KC_1)
#define MT_2 LALT_T(KC_2)
#define MT_3 LGUI_T(KC_3)
#define MT_4 LSFT_T(KC_4)
#define MT_7 LSFT_T(KC_7)
#define MT_8 LGUI_T(KC_8)
#define MT_9 LALT_T(KC_9)
#define MT_0 LCTL_T(KC_0)

enum custom_keycodes {
  KC_LCAR = SAFE_RANGE, // left caret
  KC_RCAR, // right caret
  KC_LDQUO, // left double quote
  KC_RDQUO, // right double quote
  KC_LQUO,  // left single quote
  KC_RQUO, // right single quote
  KC_EMDS, // emdash
  KC_ENDS, // endash
  /* editing macros */
  M_NLNB, // new line below
  M_NLNA, // new line above
  M_SL_WD, // select word
  /* secrets */
  M_SEC_0,
  M_SEC_1,
  M_SEC_2,
  M_SEC_3,
  M_SEC_4,
  M_SEC_5,
  M_SEC_6,
  M_SEC_7,
};

// comma -> semi-colon
const key_override_t ko_comma = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SEMICOLON);
// period -> colon
const key_override_t ko_dot = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLON);
// question mark -> exclamation mark
const key_override_t ko_ques = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
// slash -> backslash
const key_override_t ko_slsh = ko_make_basic(MOD_MASK_SHIFT, KC_SLASH, KC_BACKSLASH);
// left quote -> left double quote
const key_override_t ko_lquo = ko_make_basic(MOD_MASK_SHIFT, KC_LDQUO, KC_LQUO);
// right quote -> right double quote
const key_override_t ko_rquo = ko_make_basic(MOD_MASK_SHIFT, KC_RDQUO, KC_RQUO);
// emdash -> endash
const key_override_t ko_emds = ko_make_basic(MOD_MASK_SHIFT, KC_EMDS, KC_ENDS);
// endash -> emdash
const key_override_t ko_ends = ko_make_basic(MOD_MASK_SHIFT, KC_ENDS, KC_EMDS);
// caps word -> caps lock
const key_override_t ko_cw_togg = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
  &ko_comma,
	&ko_dot,
	&ko_ques,
	&ko_slsh,
	&ko_lquo,
	&ko_rquo,
	&ko_cw_togg,
  &ko_emds,
  &ko_ends,
	NULL // Null terminate the array of overrides!
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BSE] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         MT_A,    MT_S,    MT_D,    MT_F,    KC_G,                         KC_H,    MT_J,    MT_K,    MT_L,    MT_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_QUES,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                   L_ESC,  L_BSPC,   L_DEL,      L_ENT,   L_SPC,   L_TAB
                             //`--------------------------'  `--------------------------'

  ),
    [SYM] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      TO(BSE),   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE, KC_DQUO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      MT_LCAR, MT_LBCE, MT_LBRC, MT_LPRN, KC_LDQUO,                     KC_UNDS, MT_SLSH, MT_SCLN, MT_COLN, MT_DQUO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_RCAR, KC_RBCE, KC_RBRC, KC_RPRN, KC_RDQUO,                     KC_BSLS, KC_TILD, KC_EMDS, KC_EMDS, KC_EXLM,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  KC_EQL, KC_MINS, KC_PLUS,    XXXXXXX, _______, XXXXXXX
                             //`--------------------------'  `--------------------------'

  ),
    [NMS] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4  , KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         MT_1,    MT_2,    MT_3,    MT_4,    KC_5,                         KC_6,    MT_7,    MT_8,    MT_9,    MT_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_F11,  KC_PERC,  KC_HASH, KC_DLR, KC_LPRN,                      KC_RPRN,  KC_EQL, KC_ASTR, KC_SLSH,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                XXXXXXX, _______, XXXXXXX,     KC_MINS,  KC_PLUS,   KC_0
                             //`--------------------------'  `--------------------------'

  ),
    [NMD] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
     TO(BSE), KC_EXLM,  KC_HASH,  KC_DLR, KC_PERC,                  KC_KP_SLASH, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCTL, KC_LOPT, KC_LGUI, KC_LSFT,  KC_TAB,               KC_KP_ASTERISK, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCAR, KC_RCAR, KC_LPRN, KC_RPRN, KC_TILD,                  KC_KP_EQUAL, KC_KP_7, KC_KP_8, KC_KP_9,  KC_DOT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  KC_ESC, KC_BSPC, KC_DEL,      KC_ENT,  KC_SPC, KC_KP_0
                             //`--------------------------'  `--------------------------'

  ),
    [LNV] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      TO(BSE), KC_PGDN,   KC_UP, KC_PGUP, KC_HYPR,                       M_NLNA,  KC_PGUP,  KC_UP, KC_PGDN, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_RSFT, KC_LSFT,  KC_MEH,                       M_NLNB, A_LEFT,  M_SL_WD,  A_RGHT,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, XXXXXXX, _______,        CUT,    COPY,   PASTE
                             //`--------------------------'  `--------------------------'

  ),
  [RNV] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      TO(BSE),  KC_PGDN,  KC_UP, KC_PGUP,  M_NLNA,                     KC_HYPR,  KC_PGDN,  KC_UP, KC_PGUP,  XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_INS,  A_LEFT,  M_SL_WD, A_RGHT,  M_NLNB,                       KC_MEH, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                   PASTE,    COPY,     CUT,    _______,  XXXXXXX, XXXXXXX
                             //`--------------------------'  `--------------------------'

  ),
    [MSE] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      TO(BSE), XXXXXXX,    DOCK, XXXXXXX,  MS_RCK,                       MS_MCK,  MS_WLT,   MS_UP,  MS_WRT,  MS_RCK,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,  MS_LCK,                       MS_WUP,   MS_LT,   MS_DN,   MS_RT,  MS_LCK,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         G_LT,    G_DN,    G_UP,    G_RT,  MS_MCK,                       MS_WDN,    C_LT,    C_DN,    C_UP,    C_RT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  MS_AC2,  MS_AC1,  MS_AC0,    XXXXXXX, XXXXXXX, _______
                             //`--------------------------'  `--------------------------'

  ),
    [FNS] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      M_SEC_0, M_SEC_1, M_SEC_2, M_SEC_3, M_SEC_4,                      TO(SYM), TO(NMD), TO(MSE), TO(RNV), TO(LNV),
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OS_CTL,  OS_ALT,  OS_GUI,  OS_SFT, XXXXXXX,                      DM_RSTP, DM_REC1, DM_PLY1, DM_REC2, DM_PLY2,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         UNDO,     CUT,    COPY,   PASTE,    REDO,                        C_VLD,   C_VLU,   C_BRD,   C_BRU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                               _______, XXXXXXX, XXXXXXX,        C_MTE,   C_PLP,   C_NXT
                            //`--------------------------'  `--------------------------'

  ),
  //   [EDITOR] = LAYOUT_split_3x5_3(
  // //,--------------------------------------------.                    ,--------------------------------------------.
  //     XXXXXXX,  CD_RUN, CD_RENM, CD_TERM, CD_STRC,                      XXXXXXX,  CD_RUN, XXXXXXX, XXXXXXX, XXXXXXX,
  // //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
  //     CD_PROJ, CD_STRC, CD_DEBG, CD_FND,  CD_FIND,                     CD_CRHOM,CD_CREND, CD_PRV,   CD_NXT, CD_CTAG,
  // //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
  //      CD_RUN, CD_PROB, CD_TODO, CD_GIT,  CD_BKMK,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
  //                               CD_PRTAB,CD_NXTAB, CD_XTAB,    _______, XXXXXXX, XXXXXXX
  //                            //`--------------------------'  `--------------------------'

  // ),
};


/* autoshift mods */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MT_A:
            return true;
        case MT_S:
            return true;
        case MT_D:
            return true;
        case MT_F:
            return true;
        case MT_J:
            return true;
        case MT_K:
            return true;
        case MT_L:
            return true;
        case MT_P:
            return true;
        default:
            return false;
    }
}

/* custom record processing */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LQUO:
      if (record->event.pressed) {
        send_string("“");
      }
      return false;
    case KC_RQUO:
      if (record->event.pressed) {
        send_string("”");
      }
      return false;
    case KC_EMDS:
      if (record->event.pressed) {
        send_string("—");
      }
      return false;
    case M_SL_WD:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_RIGHT) SS_LALT(SS_TAP(X_LEFT)) SS_LALT(SS_LSFT(SS_TAP(X_RIGHT))));
      }
      return false;
    case M_SPLT_DN:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_K)) SS_TAP(X_DOWN));
      }
      return false;
    case M_SPLT_LT:
        if (record->event.pressed) {
          SEND_STRING(SS_LGUI(SS_TAP(X_K)) SS_TAP(X_LEFT));
        }
        return false;
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
