#include "minidox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

// Toggle on and off qwert layer
#define QWERTY TG(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   '  |   ,  |   .  |   P  |   Y  |           |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  |           |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  |           |   B  |   M  |   W  |   V  |   Z  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER| Space|    |      | RAISE| Shift|
 *                  `-------------| Ctrl |    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_DVORAK] = KEYMAP( \
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    \
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    \
  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    \
                    KC_LSFT, LOWER, CTL_T(KC_SPC),  KC_BSPC, RAISE, OSM(MOD_LSFT) \
),

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  q Q |  w W |  e E |  r R |  t T |           |  y Y | u  U |  i I |  o O |  p P |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  a A |  s S |  d D |  f F |  g G |           |  h H | j  J |  k K |  l L |  ; : |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  z Z |  x X |  c C |  v V |  b B |           |  n N | m  M |  , < |  . > |  / ? |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = KEYMAP( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    _______, _______, _______,      _______, _______,  _______                   \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  1 ! |  2 @ |  3 # |  4 $ |  5 % |           |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |  ` ~ |  ' " |   (  |  [ { |           |  ] } |   )  |  - _ |  = + |  \ | |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |  GUI |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE|      |
 *                  `-------------| Alt  |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = KEYMAP( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  KC_GRV, KC_QUOT, KC_LPRN,  KC_LBRC,      KC_RBRC, KC_RPRN, KC_MINS, KC_EQL,  KC_BSLS, \
  _______, _______, KC_LGUI, _______, _______,      _______, _______, _______, _______, _______, \
	      OSM(MOD_LCTL), _______, OSM(MOD_LALT),_______, _______, _______                    \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |      |      |      |      |           | Left | Down |  Up  | Right| RALT |  
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|      |      |      |      |           | Home | PgDn | PgUp | END  |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = KEYMAP( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_ESC,  _______, _______, _______, _______,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RALT, \
  KC_CAPS, _______, _______, _______, _______,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, \
                    _______, _______, _______,      KC_ENT,  _______, KC_DEL                    \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |LGUI+l|      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|QWERTY|      |      |      |           |      |      |      |Taskmg|caltde|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,  \
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, LGUI(KC_L), _______, \
  RESET,   QWERTY,  _______, _______, _______,      _______, _______, _______, TSKMGR,     CALTDEL, \
                    _______, _______, _______,      _______,  _______, _______                      \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
  }
  return true;
}
