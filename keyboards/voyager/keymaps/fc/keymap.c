#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
/* #include <send_string_keycodes.h> */
#include <os_detection.h>
/* #include <keycodes.h> */
/* #include <keymap_french.h> */
#define MOON_LED_LEVEL LED_LEVEL

bool macos_mode = false;

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

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  MA_LED_FULL,
  MA_LED_LIGHT,

  MA_TOBASE,
  //BASE LAYER
  ME_EURO,
  ME_AT,
  ME_MINS,
  ME_PSCR,
  ME_CUT,
  ME_COPY,
  ME_PASTE,
  ME_UNDO,
  ME_LEFT_CTRL_GUI,

  //SHIFT LAYER
  ME_EXCL,
  ME_INSEC,
  ME_DQUO,
  ME_SCLN,
  ME_COLN,
  ME_DEL,
  ME_BSLH,
  ME_DLR1,

  //DEAD LAYER
  ME_ACIR,
  ME_OE,
  ME_OCIR,
  ME_UCIR,
  ME_ECIR,
  ME_ICIR,
  ME_ITRE,
  ME_AE,
  ME_ETC,
  ME_QUOTFR,
  ME_GRV,
  ME_CADR,
  ME_SCADR,
  ME_QCADR,
  ME_LQUOTFR,
  ME_RQUOTFR,
  ME_DLR,
  ME_NTILD,
  ME_MICR,
  ME_SUP2,
  ME_SECT,
  ME_COPYR,
  ME_BULLET,

  // DEAD MAJ LAYER
  ME_ACIRM,
  ME_CCEDM,
  ME_OEM,
  ME_OCIRM,
  ME_UCIRM,
  ME_AGRVM,
  ME_EACUM,
  ME_EGRVM,
  ME_ECIRM,
  ME_ICIRM,
  ME_ITREM,
  ME_UGRVM,
  ME_AEM,
  ME_SUP3,
  ME_NTILDM,
  ME_RGSTRD,

  //ERGOL CODE LAYER
  ME_CIR,
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
  

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_ESCAPE,        KC_B,           MT(MOD_LCTL, FR_EACU),KC_P,           KC_O,           FR_EGRV,                                        FR_CCIRC,       KC_V,           KC_D,           KC_L,           KC_J,           FR_Z,           
    KC_TAB,           FR_A,           KC_U,           KC_I,           KC_E,           FR_COMM,                                        KC_C,           KC_T,           KC_S,           KC_R,           KC_N,           FR_M,           
    KC_LEFT_SHIFT,    FR_AGRV,        KC_Y,           KC_X,           FR_DOT,         KC_K,                                           FR_APOS,        FR_Q,           KC_G,           KC_H,           KC_F,           KC_RIGHT_SHIFT, 
    ME_LEFT_CTRL_GUI, KC_LEFT_GUI,    KC_LEFT_ALT,    FR_W,           MO(1),          ST_MACRO_0,                                     ST_MACRO_1,     MO(2),          KC_COMMA,       KC_DELETE,      KC_BSPC,        MA_TOBASE,          
                                                    KC_SPACE,       LCTL(KC_P),                                     LCTL(LSFT(KC_P)),KC_SPACE
  ),
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT, ME_HASH,        FR_EXLM,        ME_LCBR,        ME_RCBR,        ME_PIPE,                                        ME_TIL,         FR_7,           FR_8,           FR_9,           KC_KP_ASTERISK, ME_ASTR,        
    KC_TRANSPARENT, ME_AT,          FR_DLR,         FR_LPRN,        FR_RPRN,        FR_SLSH,                                        ME_RABK,        FR_4,           FR_5,           FR_6,           KC_KP_PLUS,     ME_MINS,        
    KC_TRANSPARENT, ME_UNDO,        ME_CUT,         ME_COPY,        ME_PASTE,       ME_BSLH,                                        ME_LABK,        FR_1,           FR_2,           FR_3,           KC_KP_SLASH,    FR_EQL,         
    KC_TRANSPARENT, ME_GRV,         KC_TRANSPARENT, FR_AMP,         KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, FR_0,           KC_DOT,         FR_COMM,        FR_PERC,        
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_MS_WH_UP,    KC_HOME,        KC_MS_UP,       KC_END,         ME_EURO,                                        FR_UGRV,        KC_TAB,         KC_UP,          LSFT(KC_TAB),   KC_ENTER,       KC_PAGE_UP,     
    KC_TRANSPARENT, KC_MS_WH_DOWN,  KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    FR_COLN,                                        FR_CCED,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_BSPC,        KC_PGDN,        
    KC_TRANSPARENT, FR_APOS,        FR_DQUO,        ME_LBRC,        ME_RBRC,        FR_SCLN,                                        ME_EXCL,        ME_MINS,        ME_UNDS,        FR_APOS,        KC_DELETE,      KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_MS_BTN1,     KC_MS_BTN3,                                     KC_TRANSPARENT, KC_MS_BTN2
  ),
};


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  // Detect host os
  defer_exec(500, get_host_os, NULL);
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {131,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {25,255,255}, {197,255,255}, {152,255,255}, {197,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {197,255,255}, {25,255,255}, {152,255,255}, {0,245,245}, {0,245,245}, {152,255,255}, {197,255,255}, {152,255,255} },

    [1] = { {0,0,0}, {74,255,255}, {74,255,255}, {169,255,255}, {169,255,255}, {74,255,255}, {0,0,0}, {74,255,255}, {74,255,255}, {169,255,255}, {169,255,255}, {74,255,255}, {0,0,0}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {74,255,255}, {0,0,0}, {74,255,255}, {0,0,0}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {41,255,255}, {0,0,0}, {74,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {41,255,255}, {41,255,255}, {74,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {41,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,245,245}, {0,0,0}, {0,0,0}, {74,255,255}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {25,255,255}, {25,255,255}, {0,0,0}, {25,255,255}, {169,255,255}, {0,0,0}, {25,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,255}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,255}, {25,255,255}, {0,0,0}, {25,255,255}, {0,0,0}, {0,0,0}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

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
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}



#define WINALT1(A) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A)));}
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




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
if (record->event.pressed) { 
    switch (keycode) {
      case ST_MACRO_0: SEND_STRING(SS_LCTL(SS_TAP(X_K)) SS_DELAY(100) SS_LCTL(SS_TAP(X_U))); break;
      case ST_MACRO_1: SEND_STRING(SS_LCTL(SS_TAP(X_K)) SS_DELAY(100) SS_LCTL(SS_TAP(X_C))); break;
      case RGB_SLD: rgblight_mode(1); break;
  
      //ERGO BASE LAYER
      case ME_EURO: if (macos_mode)      OPTION(XKEY(X_RBRC))         else ALTGR(XKEY(X_E));        break;
      case ME_AT:   if (macos_mode)      XKEY(X_NUBS)                 else ALTGR(XKEY(X_0));        break;
      case ME_MINS: if (macos_mode)      XKEY(X_EQL)                  else XKEY(X_6);               break;
      case ME_LEFT_CTRL_GUI: if (macos_mode) SEND_STRING(SS_DOWN(X_LGUI)) else SENS_STRING(SS_DOWN(X_LCTL)) break;   
      case ME_PSCR: if (macos_mode)      SHIFT(COMMAND(XKEY(X_4)))    else XKEY(X_PSCR);            break;
      case ME_CUT: if (macos_mode)       COMMAND(XKEY(X_X))           else CTRL(XKEY(X_X));               break;
      case ME_COPY: if (macos_mode)      COMMAND(XKEY(X_C))           else CTRL(XKEY(X_C));               break;
      case ME_PASTE: if (macos_mode)     COMMAND(XKEY(X_V))           else CTRL(XKEY(X_V));               break;
      case ME_UNDO: if (macos_mode)      COMMAND(XKEY(X_W))           else CTRL(XKEY(X_W));               break;

      //ERGOL SHIFT LAYER
      case ME_EXCL: if (macos_mode)      XKEY(X_8)           else XKEY(X_SLSH);   break;
      case ME_INSEC:if (macos_mode)      UNSHIFT(OPTION(XKEY(X_SPC))) else UNSHIFT(WINALT3(2,5,5)); break; // ALT 255 = insec
      case ME_DQUO: UNSHIFT(XKEY(X_3)); break;  
      case ME_SCLN: UNSHIFT(XKEY(X_COMM)); break; 
      case ME_COLN: UNSHIFT(XKEY(X_DOT)); break;
      case ME_DEL:  UNSHIFT(XKEY(X_DEL)); break;
      case ME_DLR1: UNSHIFT(XKEY(X_RBRC)); break;
      case ME_BSLH: if (macos_mode)      OPTION(XKEY(X_DOT))    else UNSHIFT(ALTGR(XKEY(X_8))); break;
      // ERGOL DEAD LAYER
      case ME_ACIR:   if (macos_mode) XCIRC(X_Q)                else WINALT3(1,3,1); break;// ALT 131 = â
      case ME_OE:     if (macos_mode) OPTION(XKEY(X_O))         else WINALT4(0,1,5,6); break;//ALT 0156 = œ
      case ME_OCIR:   if (macos_mode) XCIRC(X_O)                else WINALT3(1,4,7); break;// ALT 147 = ô
      case ME_UCIR:   if (macos_mode) XCIRC(X_U)                else WINALT3(1,5,0); break;// ALT 150 = û
      case ME_ECIR:   if (macos_mode) OPTION(XKEY(X_E))         else WINALT3(1,3,6); break;// ALT 136 = ê
      case ME_ICIR:   if (macos_mode) OPTION(XKEY(X_I))         else WINALT3(1,4,0); break;// ALT 140 = î
      case ME_ITRE:   if (macos_mode) XTRE(X_I)                 else WINALT3(1,3,9); break;// ALT 139 = ï
      case ME_AE:     if (macos_mode) OPTION(XKEY(X_Q))         else WINALT3(1,4,5); break;// ALT 145 = æ
      case ME_ETC:    if (macos_mode) OPTION(XKEY(X_COMM))      else WINALT4(0,1,3,3); break; // ...
      case ME_QUOTFR: if (macos_mode) SHIFT(OPTION(XKEY(X_4)))  else WINALT4(0,1,4,6); break;//ALT 0146 = ’
      case ME_GRV:    if (macos_mode) XGRV(X_SPC)               else WINALT2(9,6); break; // ALT 96 = ``
      case ME_CADR:   if (macos_mode) OPTION(XKEY(X_EQL))       else WINALT4(0,1,5,1); break;// ALT 151 = 
      case ME_SCADR:  if (macos_mode) SHIFT(OPTION(XKEY(X_EQL)))else WINALT4(0,1,5,0); break;// ALT 0150 = 
      case ME_QCADR:  if (macos_mode) XKEY(X_EQL)               else WINALT4(0,1,7,3); break;// ALT 0173 = - (insec)
      case ME_LQUOTFR: if (macos_mode) OPTION(XKEY(X_7))        else WINALT3(1,7,4); break;// ALT 174 = «
      case ME_RQUOTFR: if (macos_mode) SHIFT(OPTION(XKEY(X_7))) else WINALT3(1,7,5); break;// ALT 175 = »
      case ME_NTILD:  if (macos_mode) XTILD(X_N)                else WINALT3(1,6,4); break;// ALT 164 = ñ
      case ME_MICR:   if (macos_mode) OPTION(XKEY(X_SCLN))      else SHIFT(XKEY(X_NUHS)); break;// ALT 181 = µ
      case ME_SUP2:   if (!macos_mode)                               XKEY(X_GRV); break;// ALT 178 = ²
      case ME_SECT:   if (macos_mode)  XKEY(X_6)                else SHIFT(XKEY(X_SLSH)); break;// ALT 167 = §
      case ME_COPYR:  if (macos_mode)  OPTION(XKEY(X_C))        else WINALT4(0,1,6,9); break;// ALT 0169 = ©
      case ME_BULLET: if (macos_mode)  OPTION(XKEY(X_NUBS))     else WINALT1(7); break;// ALT 7 = •
      //ERGOL DEAD MAJ LAYER
      case ME_ACIRM: if (macos_mode)   XCIRCSHIFT(X_Q)          else WINALT3(1,8,2); break;// ALT 182 = Â
      case ME_CCEDM: if (macos_mode)   OPTION(XKEY(X_9))        else WINALT3(1,2,8); break;// ALT 128 = Ç
      case ME_OEM: if (macos_mode)     SHIFT(OPTION(XKEY(X_O))) else WINALT4(0,1,4,0); break;// ALT 0140 = Œ
      case ME_OCIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_LBRC))) else WINALT3(2,2,6); break;// ALT 226 = Ô
      case ME_UCIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_8))) else WINALT3(2,3,4); break;// ALT 234 = Û
      case ME_AGRVM: if (macos_mode)   SEND_STRING(SS_TAP(X_CAPS) SS_TAP(X_0) SS_TAP(X_CAPS)); else WINALT3(1,8,3); break;//ALT 183 = À
      case ME_EACUM: if (macos_mode)   XACUTSHIFT(X_E)          else WINALT3(1,4,4); break;//ALT 144 = É
      case ME_EGRVM: if (macos_mode)   XGRVSHIFT(X_E)           else WINALT3(2,1,2); break;//ALT 212 = È
      case ME_ECIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_E))) else WINALT3(2,1,0); break;// ALT 210 = Ê
      case ME_ICIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_H))) else WINALT3(2,1,5); break;// ALT 215 = Î
      case ME_ITREM: if (macos_mode)   OPTION(XKEY(X_J))        else WINALT3(2,1,6); break;// ALT 216 = Ï
      case ME_UGRVM: if (macos_mode)   OPTION(XKEY(X_QUOT))     else WINALT3(2,3,5); break;// ALT 235 = Ù
      case ME_AEM:   if (macos_mode)   SHIFT(OPTION(XKEY(X_Q))) else WINALT3(1,4,6); break;// ALT 146 = Æ
      case ME_SUP3:  if (!macos_mode)                                WINALT3(2,5,2); break;// ALT 252 = ³
      case ME_NTILDM: if (macos_mode)  XTILDSHIFT(X_N)          else WINALT3(1,6,5); break;// ALT 165 = Ñ
      case ME_RGSTRD: if (macos_mode)  OPTION(XKEY(X_R))        else WINALT4(0,1,7,4); break; // ALT 0174 = ®
      //ERGOL CODE LAYER
      case ME_CIR:   if (macos_mode)  XCIRC(X_SPC)              else WINALT2(9,4); break; // ALT 94 = ^
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
      
      /* case MA_EOL: WINALT2(2,0); break; // ALT 20 = ¶  */
      
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
  if (record->event.released) { 
      switch (keycode) {
          case ME_LEFT_CTRL_GUI: if (macos_mode) SEND_STRING(SS_UP(X_LGUI)) else SENS_STRING(SS_UP(X_LCTL)) break;
      }
  }
  return true;
}


