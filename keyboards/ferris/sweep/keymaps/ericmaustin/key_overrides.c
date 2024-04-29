#include QMK_KEYBOARD_H
#include "process_key_override.h"

const key_override_t **key_overrides = (const key_override_t *[]){
    &(ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM)), // ?!
    &(ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN)), // ,;
    &(ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLON)), // .:
    &(ko_make_basic(MOD_MASK_SHIFT, KC_SLASH, KC_BACKSLASH)),
    NULL
};
