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
#define _NAVFUN 2
#define _XCHARS 3
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

//Tap Dance Declarations
enum {
  TD_BSPC_ENT = 0
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Back space, twice for Enter
  [TD_BSPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_ENT)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 *
 * ,----------------------------------.                 ,----------------------------------.
 * |  ' " |  , < |  . > |  p P |  y Y |                 |  f F |  g G |  c C |  r R |  l L |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  a A |  o O |  e E |  u U |  i I |                 |  d D |  h H |  t T |  n N |  s S |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  ; : |  q Q |  j J |  k K |  x X |                 |  b B |  m M |  w W |  v V |  z Z |
 * `----------------------------------'                 `----------------------------------'
 *                  ,--------------------.          ,------,-------------.
 *                  |  Alt |XC Tab| Space|          |BckSpc|NavFun| Shift|
 *                  `-------------| Ctrl |          | Ctrl |------+------.
 *                                |      |          |      |
 *                                `------'          `------'
 */
[_DVORAK] = LAYOUT( \
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    \
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    \
  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    \
OSM(MOD_LALT), LT(_XCHARS,KC_TAB), CTL_T(KC_SPC),   CTL_T(KC_BSPC), MO(_NAVFUN), OSM(MOD_LSFT) \
),

/* Qwerty
 *
 * ,----------------------------------.                 ,----------------------------------.
 * |  q Q |  w W |  e E |  r R |  t T |                 |  y Y | u  U |  i I |  o O |  p P |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  a A |  s S |  d D |  f F |  g G |                 |  h H | j  J |  k K |  l L |  ; : |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  z Z |  x X |  c C |  v V |  b B |                 |  n N | m  M |  , < |  . > |  / ? |
 * `----------------------------------'                 `----------------------------------'
 *                  ,--------------------.          ,------,-------------.
 *                  |      |      |      |          |      |      |      |
 *                  `-------------|      |          |      |------+------.
 *                                |      |          |      |
 *                                `------'          `------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                 _______, _______, _______,         _______, _______,  _______                   \
),

/* Xtra Chars
 *
 * ,----------------------------------.                 ,----------------------------------.
 * |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                 |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  Tab |  ` ~ |  ' " |      |  [ { |                 |  ] } |      |  - _ |  = + |  \ | |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  Esc |      |      |      |      |                 |      |      |      |      |  / ? |
 * `----------------------------------'                 `----------------------------------'
 *                  ,--------------------.          ,------,-------------.
 *                  |      |      |      |          |      |      |      |
 *                  `-------------|      |          |      |------+------.
 *                                |      |          |      |
 *                                `------'          `------'
 */
[_XCHARS] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  KC_GRV,  KC_QUOT, KC_LBRC, _______,      _______, KC_RBRC, KC_MINS, KC_EQL,  KC_BSLS, \
  KC_ESC,  KC_RALT, _______, _______, _______,      _______, _______, _______, _______, KC_SLSH, \
		    _______, _______, _______,      KC_ENT , MO(_ADJUST), _______                \
),

/* NavFun
 *
 * ,----------------------------------.                 ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |                 |  F6  |  F7  |  F8  |  F9  | F10  |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  Tab |      |      |      |      |                 | Left | Down |  Up  | Right| RALT |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  Esc |      |  GUI |      |      |                 | Home | PgDn | PgUp | END  | Del  |
 * `----------------------------------'                 `----------------------------------'
 *                  ,--------------------.          ,------,-------------.
 *                  |      |ADJUST|      |          |      |      |      |
 *                  `-------------|      |          |      |------+------.
 *                                |      |          |      |
 *                                `------'          `------'
 */
[_NAVFUN] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
  KC_TAB,  _______, _______, _______, _______,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS, \
  KC_ESC,  _______, KC_LGUI, _______, _______,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  \
		_______, MO(_ADJUST), _______,      _______, _______, _______                    \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.                 ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |                 |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |                 |      |      |      |LGUI+l|      |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * | Reset|QWERTY|      |      |      |                 |      |      |      |Taskmg|caltde|
 * `----------------------------------'                 `----------------------------------'
 *                  ,--------------------.          ,------,-------------.
 *                  |      | LOWER|      |          |      | RAISE|      |
 *                  `-------------|      |          |      |------+------.
 *                                |      |          |      |
 *                                `------'          `------'
 */
[_ADJUST] =  LAYOUT( \
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
        layer_on(_NAVFUN);
        update_tri_layer(_NAVFUN, _XCHARS, _ADJUST);
      } else {
        layer_off(_NAVFUN);
        update_tri_layer(_NAVFUN, _XCHARS, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_XCHARS);
        update_tri_layer(_NAVFUN, _XCHARS, _ADJUST);
      } else {
        layer_off(_XCHARS);
        update_tri_layer(_NAVFUN, _XCHARS, _ADJUST);
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
