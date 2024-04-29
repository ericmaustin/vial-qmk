#pragma once
#include QMK_KEYBOARD_H

#define KC_CTSC RCTL_T(KC_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_RLSH RSFT_T(KC_SLSH)
#define KC_GUTA GUI_T(KC_TAB)
#define KC_CLGV CTL_T(KC_GRV)

// Layer keys
#define KC_SPM2 LT(2, KC_SPC)
#define KC_BSM1 LT(1, KC_BSPC)
#define KC_ENTM3 LT(3, KC_ENT)
#define KC_ESCM4 LT(4, KC_ESC)

// mods
#define KC_LSHA LSFT_T(KC_A)
#define KC_LCTLS LCTRL_T(KC_S)
#define KC_LALTD LALT_T(KC_D)
#define KC_LGUIF LGUI_T(KC_F)
#define KC_RGUIKJ RGUI_T(KC_J)
#define KC_RALTT RALT_T(KC_K)
#define KC_RCTLL RCTL_T(KC_L)
#define KC_RSFTP RSFT_T(KC_P)
#define KC_LSHSPC LSFT_T(KC_SPC)

// common symbols
#define KC_LBRACE LSFT(KC_LBRC) // {
#define KC_RBRACE LSFT(KC_RBRC)  // }
#define KC_STAB LSFT(KC_TAB) // Shift + Tab
