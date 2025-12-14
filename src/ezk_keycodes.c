// keycodes for ezekiel
// these need a way to implement mappings, for example
// the @ sign is SHIFT+2 on US keyboards, but SHIFT+' on UK keyboards 
// also other keyboards like pinyin, zhuyin and arabic script
// others on the list: DVORAK, AZERTY, QWERTZ and Colemak. Kana AND Latin script
// Hangul, Russian, InScript, Nordic languages, Turkish Q & F, potentially braille 
// input, and just other more ergonomic layouts. 

#include "ezk_keycodes.h"

#define EZK_KEY_XM(key, name) name,
const char *ezk_key_names[] = {
    "NULL",
    _EZK_KEYS_XMACRO
};
#undef EZK_KEY_XM

EZKAPI const char* ezk_key_get_key_name(ezk_key key) {
  return ezk_key_names[key < EZK_KEY_COUNT ? key : EZK_KEY_NULL];
}

#define EZK_ACTIVE_0(name) // has no altgr function
#define EZK_ACTIVE_1(name) #name,
#define EZK_ACTIVE_KEY(name, active) EZK_ACTIVE_##active(name)

#define EZK_CKEY_XM(base, shift, s_type, s_name, altgr, a_type, a_name)  EZK_ACTIVE_KEY(s_type,shift) EZK_ACTIVE_KEY(a_type,altgr)

const char *ezk_ckey_names[] = {
    "NULL",
    _EZK_CKEYS_XMACRO
};

#undef EZK_CKEY_XM
#undef EZK_ACTIVE_0
#undef EZK_ACTIVE_1

EZKAPI const char* ezk_key_get_ckey_name(ezk_ckey ckey) {
  return ezk_ckey_names[ckey < EZK_CKEY_COUNT ? ckey : EZK_CKEY_NULL];
}

#define EZK_CKEY_XM(base, shift, s_type, s_name, altgr, a_type, a_name) {EZK_ACTIVE_KEY(s_type,shift), EZK_ACTIVE_KEY(a_type,altgr)},
#define EZK_ACTIVE_1(name) EZK_CKEY_##name
#define EZK_ACTIVE_0(name) 0 // set it explicitly to 0 to stop the lookup table being jagged

// complex keys lookup table

// first is shift key, then altgr if it exists
static const ezk_ckey ckey_lookup[EZK_KEY_COUNT + 1][2] = {
    {0, 0}, // for null key
    _EZK_CKEYS_XMACRO
};

#undef EZK_ACTIVE_KEY
#undef EZK_ACTIVE_1
#undef EZK_ACTIVE_0

EZKAPI ezk_ckey ezk_key_get_ckey_from_base(ezk_key base, ezk_mod_key mods) {
  if (!(altgr_down(mods) || shift_down(mods))) {
    return EZK_CKEY_NULL;
  }
  return ckey_lookup[base][altgr_down(mods) ? 1 : 0]; // NEEDS WORK: what if shift and altgr are down at the same time? 
}


#define EZK_X11_KC_LOOKUP \
  EZK_X11_LT_XM(SPACE,          65) \
  EZK_X11_LT_XM(HASH,           51) \
  EZK_X11_LT_XM(SINGLEQUOTE,    48) \
  EZK_X11_LT_XM(COMMA,          59) \
  EZK_X11_LT_XM(HYPHEN,         20) \
  EZK_X11_LT_XM(PERIOD,         60) \
  EZK_X11_LT_XM(SLASH,          61) \
  EZK_X11_LT_XM(ZERO,           19) \
  EZK_X11_LT_XM(ONE,            10) \
  EZK_X11_LT_XM(TWO,            11) \
  EZK_X11_LT_XM(THREE,          12) \
  EZK_X11_LT_XM(FOUR,           13) \
  EZK_X11_LT_XM(FIVE,           14) \
  EZK_X11_LT_XM(SIX,            15) \
  EZK_X11_LT_XM(SEVEN,          16) \
  EZK_X11_LT_XM(EIGHT,          17) \
  EZK_X11_LT_XM(NINE,           18) \
  EZK_X11_LT_XM(SEMICOLON,      47) \
  EZK_X11_LT_XM(EQUALS,         21) \
  EZK_X11_LT_XM(OPENBRACKETSQ,  34) \
  EZK_X11_LT_XM(BACKSLASH,      94) \
  EZK_X11_LT_XM(CLOSEBRACKETSQ, 35) \
  EZK_X11_LT_XM(GRAVE,          49) \
  EZK_X11_LT_XM(a,              38) \
  EZK_X11_LT_XM(b,              56) \
  EZK_X11_LT_XM(c,              54) \
  EZK_X11_LT_XM(d,              40) \
  EZK_X11_LT_XM(e,              26) \
  EZK_X11_LT_XM(f,              41) \
  EZK_X11_LT_XM(g,              42) \
  EZK_X11_LT_XM(h,              43) \
  EZK_X11_LT_XM(i,              31) \
  EZK_X11_LT_XM(j,              44) \
  EZK_X11_LT_XM(k,              45) \
  EZK_X11_LT_XM(l,              46) \
  EZK_X11_LT_XM(m,              58) \
  EZK_X11_LT_XM(n,              57) \
  EZK_X11_LT_XM(o,              32) \
  EZK_X11_LT_XM(p,              33) \
  EZK_X11_LT_XM(q,              24) \
  EZK_X11_LT_XM(r,              27) \
  EZK_X11_LT_XM(s,              39) \
  EZK_X11_LT_XM(t,              28) \
  EZK_X11_LT_XM(u,              30) \
  EZK_X11_LT_XM(v,              55) \
  EZK_X11_LT_XM(w,              25) \
  EZK_X11_LT_XM(x,              53) \
  EZK_X11_LT_XM(y,              29) \
  EZK_X11_LT_XM(z,              52) \
  EZK_X11_LT_XM(DELETE,        119) \
  EZK_X11_LT_XM(SHIFT,          50) \
  EZK_X11_LT_XM(CONTROL,        37) \
  EZK_X11_LT_XM(ALT,            64) \
  EZK_X11_LT_XM(ALTGR,         108) \
  EZK_X11_LT_XM(ESCAPE,          9) \
  EZK_X11_LT_XM(PRINTSCREEN,     0) \
  EZK_X11_LT_XM(CAPSLOCK,       66) \
  EZK_X11_LT_XM(TAB,            23) \
  EZK_X11_LT_XM(NUMLOCK,        77) \
  EZK_X11_LT_XM(SCROLLLOCK,     78) \
  EZK_X11_LT_XM(PAGEUP,        112) \
  EZK_X11_LT_XM(PAGEDOWN,      117) \
  EZK_X11_LT_XM(INSERT,        118) \
  EZK_X11_LT_XM(HOME,          110) \
  EZK_X11_LT_XM(END,           115) \
  EZK_X11_LT_XM(ENTER,          36) \
  EZK_X11_LT_XM(BACKSPACE,      22) \
  EZK_X11_LT_XM(PAUSEBREAK,    127) \
  EZK_X11_LT_XM(MENU,          135) \
  EZK_X11_LT_XM(NUMPAD0,        90) \
  EZK_X11_LT_XM(NUMPAD1,        87) \
  EZK_X11_LT_XM(NUMPAD2,        88) \
  EZK_X11_LT_XM(NUMPAD3,        89) \
  EZK_X11_LT_XM(NUMPAD4,        83) \
  EZK_X11_LT_XM(NUMPAD5,        84) \
  EZK_X11_LT_XM(NUMPAD6,        85) \
  EZK_X11_LT_XM(NUMPAD7,        79) \
  EZK_X11_LT_XM(NUMPAD8,        80) \
  EZK_X11_LT_XM(NUMPAD9,        81) \
  EZK_X11_LT_XM(NUMPADPOINT,    91) \
  EZK_X11_LT_XM(NUMPADDIVIDE,  106) \
  EZK_X11_LT_XM(NUMPADMULTIPLY, 63) \
  EZK_X11_LT_XM(NUMPADSUBTRACT, 82) \
  EZK_X11_LT_XM(NUMPADPLUS,     86) \
  EZK_X11_LT_XM(NUMPADENTER,   104) \
  EZK_X11_LT_XM(ARROWUP,       111) \
  EZK_X11_LT_XM(ARROWDOWN,     116) \
  EZK_X11_LT_XM(ARROWLEFT,     113) \
  EZK_X11_LT_XM(ARROWRIGHT,    114) \
  EZK_X11_LT_XM(F1,             67) \
  EZK_X11_LT_XM(F2,             68) \
  EZK_X11_LT_XM(F3,             69) \
  EZK_X11_LT_XM(F4,             70) \
  EZK_X11_LT_XM(F5,             71) \
  EZK_X11_LT_XM(F6,             72) \
  EZK_X11_LT_XM(F7,             73) \
  EZK_X11_LT_XM(F8,             74) \
  EZK_X11_LT_XM(F9,             75) \
  EZK_X11_LT_XM(F10,            76) \
  EZK_X11_LT_XM(F11,            95) \
  EZK_X11_LT_XM(F12,            96)

#define EZK_X11_KEY_LT_LENGTH 136 // needs to be update if more keys are added

#define EZK_X11_LT_XM(k, i) [i] = EZK_KEY_##k,
static const ezk_key x11_ezk_lt[EZK_X11_KEY_LT_LENGTH] = {
    EZK_X11_KC_LOOKUP
};
#undef EZK_X11_LT_XM

#define EZK_X11_LT_XM(k, i) [EZK_KEY_##k] = i,
static const ezk_key ezk_x11_lt[EZK_X11_KEY_LT_LENGTH] = {
    EZK_X11_KC_LOOKUP
};
#undef EZK_X11_LT_XM

EZKAPI ezk_key ezk_key_ezk_to_x11(int keycode) {
  if (keycode < 0 || keycode >= EZK_X11_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return ezk_x11_lt[keycode];
}

EZKAPI ezk_key ezk_key_x11_to_ezk(int keycode) {
  if (keycode < 0 || keycode >= EZK_X11_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return x11_ezk_lt[keycode];
}

#ifdef EZK_WIN32
#include <windows.h>

#define EZK_WIN32_KC_LOOKUP \
  EZK_WIN32_LT_XM(SPACE,         VK_SPACE) \
  EZK_WIN32_LT_XM(HASH,          VK_OEM_3) \
  EZK_WIN32_LT_XM(SINGLEQUOTE,   VK_OEM_7) \
  EZK_WIN32_LT_XM(COMMA,         VK_OEM_COMMA) \
  EZK_WIN32_LT_XM(HYPHEN,        VK_OEM_MINUS) \
  EZK_WIN32_LT_XM(PERIOD,        VK_OEM_PERIOD) \
  EZK_WIN32_LT_XM(SLASH,         VK_OEM_2) \
  EZK_WIN32_LT_XM(ZERO,          '0') \
  EZK_WIN32_LT_XM(ONE,           '1') \
  EZK_WIN32_LT_XM(TWO,           '2') \
  EZK_WIN32_LT_XM(THREE,         '3') \
  EZK_WIN32_LT_XM(FOUR,          '4') \
  EZK_WIN32_LT_XM(FIVE,          '5') \
  EZK_WIN32_LT_XM(SIX,           '6') \
  EZK_WIN32_LT_XM(SEVEN,         '7') \
  EZK_WIN32_LT_XM(EIGHT,         '8') \
  EZK_WIN32_LT_XM(NINE,          '9') \
  EZK_WIN32_LT_XM(SEMICOLON,     VK_OEM_1) \
  EZK_WIN32_LT_XM(EQUALS,        VK_OEM_PLUS) \
  EZK_WIN32_LT_XM(OPENBRACKETSQ, VK_OEM_4) \
  EZK_WIN32_LT_XM(BACKSLASH,     VK_OEM_5) \
  EZK_WIN32_LT_XM(CLOSEBRACKETSQ, VK_OEM_6) \
  EZK_WIN32_LT_XM(GRAVE,         VK_OEM_3) \
  EZK_WIN32_LT_XM(a,             'A') \
  EZK_WIN32_LT_XM(b,             'B') \
  EZK_WIN32_LT_XM(c,             'C') \
  EZK_WIN32_LT_XM(d,             'D') \
  EZK_WIN32_LT_XM(e,             'E') \
  EZK_WIN32_LT_XM(f,             'F') \
  EZK_WIN32_LT_XM(g,             'G') \
  EZK_WIN32_LT_XM(h,             'H') \
  EZK_WIN32_LT_XM(i,             'I') \
  EZK_WIN32_LT_XM(j,             'J') \
  EZK_WIN32_LT_XM(k,             'K') \
  EZK_WIN32_LT_XM(l,             'L') \
  EZK_WIN32_LT_XM(m,             'M') \
  EZK_WIN32_LT_XM(n,             'N') \
  EZK_WIN32_LT_XM(o,             'O') \
  EZK_WIN32_LT_XM(p,             'P') \
  EZK_WIN32_LT_XM(q,             'Q') \
  EZK_WIN32_LT_XM(r,             'R') \
  EZK_WIN32_LT_XM(s,             'S') \
  EZK_WIN32_LT_XM(t,             'T') \
  EZK_WIN32_LT_XM(u,             'U') \
  EZK_WIN32_LT_XM(v,             'V') \
  EZK_WIN32_LT_XM(w,             'W') \
  EZK_WIN32_LT_XM(x,             'X') \
  EZK_WIN32_LT_XM(y,             'Y') \
  EZK_WIN32_LT_XM(z,             'Z') \
  EZK_WIN32_LT_XM(DELETE,        VK_DELETE) \
  EZK_WIN32_LT_XM(SHIFT,         VK_SHIFT) \
  EZK_WIN32_LT_XM(CONTROL,       VK_CONTROL) \
  EZK_WIN32_LT_XM(ALT,           VK_MENU) \
  EZK_WIN32_LT_XM(ALTGR,         VK_RMENU) \
  EZK_WIN32_LT_XM(ESCAPE,        VK_ESCAPE) \
  EZK_WIN32_LT_XM(PRINTSCREEN,   VK_SNAPSHOT) \
  EZK_WIN32_LT_XM(CAPSLOCK,      VK_CAPITAL) \
  EZK_WIN32_LT_XM(TAB,           VK_TAB) \
  EZK_WIN32_LT_XM(NUMLOCK,       VK_NUMLOCK) \
  EZK_WIN32_LT_XM(SCROLLLOCK,    VK_SCROLL) \
  EZK_WIN32_LT_XM(PAGEUP,        VK_PRIOR) \
  EZK_WIN32_LT_XM(PAGEDOWN,      VK_NEXT) \
  EZK_WIN32_LT_XM(INSERT,        VK_INSERT) \
  EZK_WIN32_LT_XM(HOME,          VK_HOME) \
  EZK_WIN32_LT_XM(END,           VK_END) \
  EZK_WIN32_LT_XM(ENTER,         VK_RETURN) \
  EZK_WIN32_LT_XM(BACKSPACE,     VK_BACK) \
  EZK_WIN32_LT_XM(PAUSEBREAK,    VK_PAUSE) \
  EZK_WIN32_LT_XM(MENU,          VK_APPS) \
  EZK_WIN32_LT_XM(NUMPAD0,       VK_NUMPAD0) \
  EZK_WIN32_LT_XM(NUMPAD1,       VK_NUMPAD1) \
  EZK_WIN32_LT_XM(NUMPAD2,       VK_NUMPAD2) \
  EZK_WIN32_LT_XM(NUMPAD3,       VK_NUMPAD3) \
  EZK_WIN32_LT_XM(NUMPAD4,       VK_NUMPAD4) \
  EZK_WIN32_LT_XM(NUMPAD5,       VK_NUMPAD5) \
  EZK_WIN32_LT_XM(NUMPAD6,       VK_NUMPAD6) \
  EZK_WIN32_LT_XM(NUMPAD7,       VK_NUMPAD7) \
  EZK_WIN32_LT_XM(NUMPAD8,       VK_NUMPAD8) \
  EZK_WIN32_LT_XM(NUMPAD9,       VK_NUMPAD9) \
  EZK_WIN32_LT_XM(NUMPADPOINT,   VK_DECIMAL) \
  EZK_WIN32_LT_XM(NUMPADDIVIDE,  VK_DIVIDE) \
  EZK_WIN32_LT_XM(NUMPADMULTIPLY, VK_MULTIPLY) \
  EZK_WIN32_LT_XM(NUMPADSUBTRACT, VK_SUBTRACT) \
  EZK_WIN32_LT_XM(NUMPADPLUS,    VK_ADD) \
  EZK_WIN32_LT_XM(NUMPADENTER,   VK_RETURN) \
  EZK_WIN32_LT_XM(ARROWUP,       VK_UP) \
  EZK_WIN32_LT_XM(ARROWDOWN,     VK_DOWN) \
  EZK_WIN32_LT_XM(ARROWLEFT,     VK_LEFT) \
  EZK_WIN32_LT_XM(ARROWRIGHT,    VK_RIGHT) \
  EZK_WIN32_LT_XM(F1,            VK_F1) \
  EZK_WIN32_LT_XM(F2,            VK_F2) \
  EZK_WIN32_LT_XM(F3,            VK_F3) \
  EZK_WIN32_LT_XM(F4,            VK_F4) \
  EZK_WIN32_LT_XM(F5,            VK_F5) \
  EZK_WIN32_LT_XM(F6,            VK_F6) \
  EZK_WIN32_LT_XM(F7,            VK_F7) \
  EZK_WIN32_LT_XM(F8,            VK_F8) \
  EZK_WIN32_LT_XM(F9,            VK_F9) \
  EZK_WIN32_LT_XM(F10,           VK_F10) \
  EZK_WIN32_LT_XM(F11,           VK_F11) \
  EZK_WIN32_LT_XM(F12,           VK_F12)


#define EZK_WIN32_LT_XM(k,i) [i] = EZK_KEY_##k,
static const ezk_key win32_ezk_lt[EZK_WIN32_KEY_LT_LENGTH] = {
  EZK_WIN32_KC_LOOKUP
};
#undef EZK_WIN32_LT_XM

#define EZK_WIN32_LT_XM(k,i) [EZK_KEY_##k] = i,
static const ezk_key ezk_win32_lt[EZK_WIN32_KEY_LT_LENGTH] = {
  EZK_WIN32_KC_LOOKUP
};
#undef EZK_WIN32_LT_XM

EZKAPI ezk_key ezk_key_ezk_to_win32(int keycode)  {
  if (keycode < 0 || keycode >= EZK_WIN32_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return ezk_win32_lt[keycode];
}

EZKAPI ezk_key ezk_key_win32_to_ezk(int keycode)  {
  if (keycode < 0 || keycode >= EZK_WIN32_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return win32_ezk_lt[keycode];
}

#endif
