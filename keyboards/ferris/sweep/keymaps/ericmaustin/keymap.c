// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "keymap_us.h"

enum layers {
  BASE,
  SYMS,
  NUMS,
  SEL, // layer selector
  SYMS_LOCK, // syms layer selected in layer selector
  NUMS_LOCK, // nums layer selected in layer selector
  NAV, // navigation layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
       q         w         e         r         t              y         u        i       o        ->SEL
       a         s         d         f         g              h         j        k       l        p
       z         x         c         v         b              n         m        ,       .        ?!
                                    bspc[L2]  esc[L4]      ent[L3]    spc[L1]

      combos:
        , + . = -
        , + ? = _
        . + ? = /
  */
  [BASE] = LAYOUT(
    KC_Q,      KC_W,     KC_E,    KC_R,     KC_T,            KC_Y,    KC_U,     KC_I,    KC_O,   TO(4),
    KC_CTLA,   KC_S,     KC_D,    KC_F,     KC_G,            KC_H,    KC_J,     KC_K,    KC_L,   KC_P,
    KC_LSHZ,   KC_X,     KC_C,    KC_V,     KC_B,            KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_QUES,
                                     KC_CLGV, KC_BSM1,   KC_SPM2, KC_GUTA
  ),
  /*
                                                 LAYER SELECTOR
      caps       @         #         $         %              ^         &        *       `       |
      tab        <         {         [         (              +        ->NUMS   ->NAV       '       /
      sh(tab)    >         }         ]         )              =         _        ~       "       \
                                         del   TRANS        TRANS      [X]
  */
  [SYMS] = LAYOUT(
      KC_CAPS,   KC_AT,   KC_HASH,   KC_DOLLAR, KC_PERC,       KC_CIRC,    KC_AMPR,   KC_ASTR,  KC_PIPE,      KC_GRV,
      KC_TAB,    KC_LABK, S(KC_LBRC), KC_LBRC,  KC_END,        KC_PLUS,    KC_MINUS,  KC_COLN,  KC_SLASH,     KC_QUOT,
      S(KC_TAB), KC_RABK, S(KC_RBRC), KC_BTN1,  KC_BTN2,       KC_EQUAL,   KC_UNDS,   KC_TILD,  KC_BACKSLASH, KC_EXLM,
                                         KC_DEL, KC_TRNS,   KC_TRNS, KC_TRNS
    ),
  /*
                                                    SYMBOLS
      caps       @         #         $         %              ^         &        *       `       |
      tab        <         {         [         (              +         -        :       '       /
      sh(tab)    >         }         ]         )              =         _        ~       "       \
                                         del   TRANS        TRANS      [X]
  */
  [SYMS] = LAYOUT(
      KC_CAPS,   KC_AT,   KC_HASH,   KC_DOLLAR, KC_PERC,       KC_CIRC,    KC_AMPR,   KC_ASTR,  KC_PIPE,      KC_GRV,
      KC_TAB,    KC_LABK, S(KC_LBRC), KC_LBRC,  KC_END,        KC_PLUS,    KC_MINUS,  KC_COLN,  KC_SLASH,     KC_QUOT,
      S(KC_TAB), KC_RABK, S(KC_RBRC), KC_BTN1,  KC_BTN2,       KC_EQUAL,   KC_UNDS,   KC_TILD,  KC_BACKSLASH, KC_EXLM,
                                         KC_DEL, KC_TRNS,   KC_TRNS, KC_TRNS
    ),
  /*
                                                     NUMBERS
       f1        f2        f3        f4        f5              f6        f7       f8      f9      f10
       1         2         3         4         5               6         7        8       9        0
       f11       f12       #         $         =               +         -        .       ,        /
                                        [X]     none       ent   spc
  */


   /*
                                                      NAV
       f1        f2        f3        f4        f5               f10      f1        f2       f3       f11
    f6(ls)   f7(lctl)   f8(lopt)  f9(lcmd)   f10(meh)         LA(tab)         f4        f5       f6
       ~         >         }         ]         )                         f7        f8       f9       f12
                                        [X]     none       ent   spc
  */


  [NUMS] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, QK_BOOT,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [3] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [4] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [5] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [6] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [7] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};
