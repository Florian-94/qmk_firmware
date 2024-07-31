#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "i18n.h"
#include <os_detection.h>

bool macos_mode = false;



enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  MA_TOBASE,
  ME_EURO,
  ME_AT,
  ME_MINS,
  ME_CUT,
  ME_COPY,
  ME_PASTE,
  ME_UNDO,
  ME_EXCL,
  ME_BSLH,
  ME_GRV,
  ME_TIL,
  ME_LCBR,
  ME_RCBR,
  ME_LBRC,
  ME_RBRC,
  ME_UNDS,
  ME_PLUS,
  ME_ASTR,
  ME_EQL,
  ME_PIPE,
  ME_LABK,
  ME_RABK,
  ME_HASH,
  ME_SECT,
  ME_VSCODE_CTRL_P,
  ME_VSCODE_SHIFT_CTRL_P,
};


enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define WINALT2(A, B) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B)));}
#define WINALT3(A, B, C) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C)));}
#define WINALT4(A, B, C, D) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C) SS_TAP(X_KP_ ## D)));}
#define UNSHIFT(A) {unregister_code(KC_LSFT); A ; register_code(KC_LSFT);}
#define SHIFT(A) {register_code(KC_LSFT); A ; unregister_code(KC_LSFT);}
#define ALTGR(A) {register_code(KC_RALT); A ; unregister_code(KC_RALT);}
#define OPTION(A) {register_code(KC_LOPT); A ; unregister_code(KC_LOPT);}
#define COMMAND(A) {register_code(KC_LGUI); A ; unregister_code(KC_LGUI);}
#define CTRL(A) {register_code(KC_LCTL); A ; unregister_code(KC_LCTL);}
#define XKEY(A) {SEND_STRING(SS_TAP(A));}
#define XCIRC(A) {SEND_STRING(SS_TAP(X_LBRC) SS_TAP(A));}
#define XCIRCSHIFT(A) {SEND_STRING(SS_TAP(X_LBRC) SS_LSFT(SS_TAP(A)));}
#define XACUTSHIFT(A) {SEND_STRING(SS_LSFT(SS_LALT(SS_TAP(X_1))) SS_LSFT(SS_TAP(A)));}
#define XTRE(A) {SEND_STRING(SS_LSFT(SS_TAP(X_LBRC)) SS_TAP(A));}
#define XGRV(A) {SEND_STRING(SS_TAP(X_NUHS) SS_TAP(A));}
#define XGRVSHIFT(A) {SEND_STRING(SS_TAP(X_NUHS) SS_LSFT(SS_TAP(A)));}
#define XTILD(A) {SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_TAP(A));}
#define XTILDSHIFT(A) {SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_LSFT(SS_TAP(A)));}
#define WIN_VSCODE_COMMENT() {SEND_STRING(SS_LCTL(SS_TAP(X_K)) SS_DELAY(100) SS_LCTL(SS_TAP(X_C)));}
#define WIN_VSCODE_UNCOMMENT() {SEND_STRING(SS_LCTL(SS_TAP(X_K)) SS_DELAY(100) SS_LCTL(SS_TAP(X_U)));}
#define MAC_VSCODE_COMMENT() {SEND_STRING(SS_LGUI(SS_TAP(X_K)) SS_DELAY(100) SS_LGUI(SS_TAP(X_C)));}
#define MAC_VSCODE_UNCOMMENT() {SEND_STRING(SS_LGUI(SS_TAP(X_K)) SS_DELAY(100) SS_LGUI(SS_TAP(X_U)));}
#define WIN_VSCODE_CTRL_P() {SEND_STRING(SS_LCTL(SS_TAP(X_P)) SS_DELAY(100) SS_LCTL(SS_TAP(X_C)));}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_ESCAPE,      KC_B,           MT(MOD_LCTL, FR_EACU),KC_P,           KC_O,           FR_EGRV,        FR_CIRC,        KC_V,           KC_D,           KC_L,           KC_J,           FR_Z,           
    KC_TAB,         FR_A,           KC_U,           KC_I,           KC_E,           FR_COMM,        KC_C,           KC_T,           KC_S,           KC_R,           KC_N,           FR_M,           
    KC_LEFT_SHIFT,  MT(MOD_LSFT, FR_AGRV),KC_Y,           KC_X,           FR_DOT,         KC_K,           FR_APOS,        FR_Q,           KC_G,           KC_H,           KC_F,           KC_ENTER,       
    KC_LEFT_CTRL,   KC_LEFT_GUI,    KC_LEFT_ALT,    FR_W,           MO(1),          KC_SPACE,       KC_NO,          MO(2),          KC_COMMA,       KC_DELETE,      KC_BSPC,        MA_TOBASE
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TRANSPARENT, ME_HASH,        ME_SECT,        ME_LCBR,        ME_RCBR,        ME_PIPE,        ME_TIL,        FR_7,           FR_8,           FR_9,           KC_KP_ASTERISK, ME_ASTR,        
    KC_TRANSPARENT, ME_AT,          FR_DLR,         FR_LPRN,        FR_RPRN,        FR_SLSH,        ME_RABK,        FR_4,           FR_5,           FR_6,           KC_KP_PLUS,     ME_MINS,    
    KC_TRANSPARENT, ME_UNDO,        ME_CUT,         ME_COPY,        ME_PASTE,       ME_BSLH,        ME_LABK,        FR_1,           FR_2,           FR_3,           KC_KP_SLASH,    FR_EQL,         
    KC_TRANSPARENT, FR_GRV,         KC_TRANSPARENT, FR_AMP,         KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, FR_0,           FR_DOT,         FR_COMM,        FR_PERC
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_TRANSPARENT, KC_MS_WH_UP,    KC_HOME,        KC_MS_UP,       KC_END,         ME_EURO,        FR_UGRV,        KC_TAB,         KC_UP,          LSFT(KC_TAB),   KC_ENTER,       KC_PAGE_UP,     
    KC_TRANSPARENT, KC_MS_WH_DOWN,  KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    FR_COLN,        FR_CCED,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_BSPC,        KC_PGDN,        
    KC_TRANSPARENT, FR_APOS,        FR_DQUO,        ME_LBRC,        ME_RBRC,        FR_SCLN,        ME_EXCL,        FR_MINS,        FR_UNDS,        FR_APOS,        KC_DELETE,      KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_NO,          KC_TRANSPARENT, KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

};



extern rgb_config_t rgb_matrix_config;


uint32_t get_host_os(uint32_t trigger_time, void *cb_arg) {
  switch(detected_host_os()) {
    case OS_MACOS:
      macos_mode = true;
      break;
    case OS_IOS:
      macos_mode = true;
      break;
    default:
      macos_mode = false;
      break;
  }
  return 0;
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,255}, {141,255,233}, {85,203,158}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,255}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {85,203,158}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,255}, {85,203,158}, {85,203,158}, {85,203,158}, {141,255,233}, {14,255,255}, {0,0,255}, {14,255,255}, {30,96,255}, {0,183,238}, {0,183,238}, {14,255,255} },

    [1] = { {169,120,255}, {50,153,244}, {50,153,244}, {146,224,255}, {146,224,255}, {50,153,244}, {50,153,244}, {0,205,155}, {0,205,155}, {0,205,155}, {31,255,255}, {146,224,255}, {0,0,0}, {50,153,244}, {50,153,244}, {146,224,255}, {141,255,233}, {50,153,244}, {50,153,244}, {0,205,155}, {0,205,155}, {0,205,155}, {105,255,255}, {105,255,255}, {85,203,158}, {15,97,236}, {0,0,0}, {15,97,236}, {15,97,236}, {50,153,244}, {50,153,244}, {0,205,155}, {0,205,155}, {0,205,155}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {50,153,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,205,155}, {0,0,0}, {0,0,0}, {154,255,255} },

    [2] = { {0,0,0}, {0,0,0}, {31,255,255}, {31,255,255}, {31,255,255}, {141,255,233}, {141,255,233}, {85,203,158}, {32,176,255}, {85,203,158}, {0,0,255}, {31,255,255}, {0,0,0}, {0,0,0}, {31,255,255}, {31,255,255}, {31,255,255}, {141,255,233}, {141,255,233}, {32,176,255}, {32,176,255}, {32,176,255}, {0,204,255}, {31,255,255}, {85,203,158}, {141,255,233}, {141,255,233}, {146,224,255}, {146,224,255}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,204,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {31,255,255}, {0,0,0}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
if (record->event.pressed) { 
    switch (keycode) {
      // case ST_MACRO_0: if (macos_mode) MAC_VSCODE_COMMENT() else WIN_VSCODE_COMMENT(); break;
      // case ST_MACRO_1: if (macos_mode) MAC_VSCODE_UNCOMMENT() else WIN_VSCODE_UNCOMMENT(); break;
      case ME_VSCODE_CTRL_P: if (macos_mode) COMMAND(XKEY(X_P)) else CTRL(XKEY(X_P)); break;
      case ME_VSCODE_SHIFT_CTRL_P: if (macos_mode) SHIFT(COMMAND(XKEY(X_P))) else SHIFT(CTRL(XKEY(X_P))); break;
      case RGB_SLD: rgblight_mode(1); break;
  
  
      case ME_EURO: if (macos_mode)      OPTION(XKEY(X_RBRC))         else ALTGR(XKEY(X_E));        break;
      case ME_AT:   if (macos_mode)      XKEY(X_NUBS)                 else ALTGR(XKEY(X_0));        break;
      case ME_MINS: if (macos_mode)      XKEY(X_EQL)                  else XKEY(X_6);               break;
      case ME_CUT: if (macos_mode)       COMMAND(XKEY(X_X))           else CTRL(XKEY(X_X));               break;
      case ME_COPY: if (macos_mode)      COMMAND(XKEY(X_C))           else CTRL(XKEY(X_C));               break;
      case ME_PASTE: if (macos_mode)     COMMAND(XKEY(X_V))           else CTRL(XKEY(X_V));               break;
      case ME_UNDO: if (macos_mode)      COMMAND(XKEY(X_W))           else CTRL(XKEY(X_W));               break;


      case ME_EXCL: if (macos_mode)      XKEY(X_8)           else XKEY(X_SLSH);   break; // !
  
    
      case ME_BSLH: if (macos_mode)      OPTION(XKEY(X_DOT))    else UNSHIFT(ALTGR(XKEY(X_8))); break;
      case ME_GRV:    if (macos_mode) XGRV(X_SPC)               else WINALT2(9,6); break; // ALT 96 = ``
      case ME_TIL:   if (macos_mode)  XTILD(X_SPC)              else WINALT3(1,2,6); break; // ALT 126 = ~
      case ME_LCBR:  if (macos_mode)  OPTION(XKEY(X_5))         else ALTGR(XKEY(X_4)); break; // {
      case ME_RCBR:  if (macos_mode)  OPTION(XKEY(X_MINS))      else ALTGR(XKEY(X_EQL)); break; // {
      case ME_LBRC:  if (macos_mode)  SHIFT(OPTION(XKEY(X_5)))  else ALTGR(XKEY(X_5)); break; // [
      case ME_RBRC:  if (macos_mode)  SHIFT(OPTION(XKEY(X_MINS))) else ALTGR(XKEY(X_MINS)); break; // ]
      case ME_UNDS:  if (macos_mode)  SHIFT(XKEY(X_EQL))        else XKEY(X_8); break; // _
      case ME_PLUS:  if (macos_mode)  SHIFT(XKEY(X_SLSH))       else SHIFT(XKEY(X_EQL)); break; // +
      case ME_EQL:   if (macos_mode)  XKEY(X_SLSH)              else XKEY(X_EQL); break; // =
      case ME_ASTR:  if (macos_mode)  SHIFT(XKEY(X_RBRC))       else XKEY(X_NUHS); break; // *
      case ME_PIPE:  if (macos_mode)  SHIFT(OPTION(XKEY(X_L)))  else ALTGR(XKEY(X_6)); break; // |
      case ME_LABK:  if (macos_mode)  XKEY(X_GRV)               else XKEY(X_NUBS); break; // <
      case ME_RABK:  if (macos_mode)  SHIFT(XKEY(X_GRV))        else SHIFT(XKEY(X_NUBS)); break; // >
      case ME_HASH:  if (macos_mode)  SHIFT(XKEY(X_NUBS))       else ALTGR(XKEY(X_3)); break; // #
      case ME_SECT:   if (macos_mode)  XKEY(X_6)                else SHIFT(XKEY(X_SLSH)); break;// ALT 167 = §
      
      case MA_TOBASE:
        get_host_os(0, NULL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_RALT);  
        unregister_code(KC_LGUI); 
        unregister_code(KC_LCTL);
        if (host_keyboard_led_state().caps_lock) {
          register_code(KC_LSFT);
          unregister_code(KC_LSFT);
        }
        if (!host_keyboard_led_state().num_lock) {
          XKEY(X_NUM_LOCK);
        }
        if (host_keyboard_led_state().scroll_lock) {
          XKEY(X_SCROLL_LOCK);
        }
        layer_clear();
        break;

    }
  }

  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint8_t layer_state_set_user(uint8_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



