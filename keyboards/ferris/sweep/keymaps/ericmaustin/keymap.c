// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include <avr/pgmspace.h>
#include QMK_KEYBOARD_H

#define KC_CTSC RCTL_T(KC_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_RLSH RSFT_T(KC_SLSH)
#define KC_SPM2 LT(2, KC_SPC)
#define KC_BSM1 LT(1, KC_BSPC)
#define KC_GUTA GUI_T(KC_TAB)
#define KC_CLGV CTL_T(KC_GRV)

enum custom_keycodes {
  KC_QST_EXCL = SAFE_RANGE,
  KC_COMMA_SEMI,
  KC_DOT_COLN,
};

struct timed_key {
  uint16_t keycode;
  uint32_t timer;
};

// return true if shift key is currently held
bool shift_held(void) {
  return get_mods() & MOD_BIT(KC_LSFT | KC_RSFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_QST_EXCL:
      if (record->event.pressed) {
        if (shift_held()) {
          SEND_STRING("!");
        } else {
          SEND_STRING("?");
        }
      }
      return false;
      break;
    case KC_COMMA_SEMI:
      if (record->event.pressed) {
        if (shift_held()) {
          SEND_STRING(";");
        } else {
          SEND_STRING(",");
        }
      }
      return false;
      break;
    case KC_DOT_COLN:
      if (record->event.pressed) {
        if (shift_held()) {
          SEND_STRING(":");
        } else {
          SEND_STRING(".");
        }
      }
      return false;
      break;
    default:
      break;
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
                                                    LAYER 0 (default with autoshift enabled)
       q         w         e         r         t              y         u        i       o        ->4
       a         s         d         f         g              h         j        k       l        p
       z         x         c         v         b              n         m        ,       .        ?!
                                    bspc[LS]  esc[L2]      ent[L3]    spc[L1]
  */

  /*
                                                    LAYER 1
      caps       @         #         $         %              ^         &        *       |        `
      tab        <         {         [         (              +         -        :       /        "
      sh(tab)    >         }         ]         )              =         _        ~       \        !
                                         del      tab     none      [X]
  */

  /*
                                                    LAYER 2
       f1        f2        f3        f4        f5              +         1        2       3        *
      lsh      lctl       lopt      lcmd       meh             -         4        5       6        =
       ~         >         }         ]         .               0         7        8       9        /
                                        [X]     none       ent   spc
  */


   /*
                                                    LAYER 2
       f1        f2        f3        f4        f5               f10      f1        f2       f3       f11
    f6(ls)   f7(lctl)   f8(lopt)  f9(lcmd)   f10(meh)         LA(tab)         f4        f5       f6
       ~         >         }         ]         )                         f7        f8       f9       f12
                                        [X]     none       ent   spc
  */

  [0] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    KC_CTLA, KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN,
    KC_LSHZ, KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,  KC_COMM, KC_DOT, KC_RLSH,
                                    KC_CLGV, KC_BSM1, KC_SPM2, KC_GUTA
  ),

  [1] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    QK_GESC, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT(
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
