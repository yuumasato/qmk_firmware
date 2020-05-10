#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _XCHARS 1
#define _NAVFUN 2
#define _ADJUST 16

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  XCHARS,
  NAVFUN,
  ADJUST,
  ALT_TAB,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |  ; : |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |  , < |  . > |  / ? |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl |XCHARS|      |    |      |NAVFUN| Shift|
 *                  `-------------| Space|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
*/
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
           KC_LALT, XCHARS,  LCTL_T(KC_SPC),        KC_BSPC, NAVFUN,  OSM(MOD_LSFT)              \
),

/* NavFun
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |C_PgUp|      |C_PgDn|      |           | Home | PgDn | PgUp | End  | Del  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |      |AltTab|      |      |           | Left | Down |  Up  |Right |Insert|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      | Super|      |      |           | Esc  |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |XCHARS|      |    |      |NAVFUN|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 a*                                `------'    `------'
 */
[_NAVFUN] = LAYOUT( \
  _______, _______, _______, _______, _______,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  \
  KC_TAB, C(KC_PGUP), ALT_TAB, C(KC_PGDN), _______,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,  \
  _______, _______, KC_LGUI, _______, _______,      KC_ESC,  _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______                    \
),

/* XChars
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  1 ! |  2 @ |  3 # |  4 $ |  5 % |           |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |  ` ~ |      |           |      |  - _ |  = + |  [ { |  ] } |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |  ' " |  \ | |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |XCHARS|      |    |      |NAVFUN|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_XCHARS] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  _______, _______, _______, KC_GRV,  _______,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
  _______, _______, _______, _______, _______,      _______, KC_QUOT, KC_BSLS, _______, _______, \
                    _______, _______, _______,      KC_ENT,  _______, _______                    \
),

/* Adjust (XChars + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |XCHARS|      |    |      |NAVFUN|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, _______, _______, \
  RESET,   _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______                    \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case XCHARS:
      if (record->event.pressed) {
        layer_on(_XCHARS);
        update_tri_layer(_XCHARS, _NAVFUN, _ADJUST);
      } else {
        layer_off(_XCHARS);
        update_tri_layer(_XCHARS, _NAVFUN, _ADJUST);
      }
      return false;
      break;
    case NAVFUN:
      if (record->event.pressed) {
        layer_on(_NAVFUN);
        update_tri_layer(_XCHARS, _NAVFUN, _ADJUST);
      } else {
        layer_off(_NAVFUN);
        update_tri_layer(_XCHARS, _NAVFUN, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case ALT_TAB:
      if (record->event.pressed) {
          if (!is_alt_tab_active) {
              is_alt_tab_active = true;
              register_code(KC_LALT);
          }
          alt_tab_timer = timer_read();
          register_code(KC_TAB);
      } else {
          unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 700) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
