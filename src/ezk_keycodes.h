// keycodes for ezekiel
// the codes are based on a number of standards. Most codes are based off of ASCII
// keys acquired from modifier keys, e.g !, have an ezk_mod_key combination to get the key,
// and the base key after it. For example ! has a mod of EZK_MOD_SHIFT and a base key of 17 

typedef enum {
EZK_MOD_SHIFT     = 1,
EZK_MOD_CTRL      = 2,
EZK_MOD_ALT       = 4,
EZK_MOD_FN        = 8,
EZK_MOD_ALTGR    = 16,
EZK_MOD_COMMAND  = 32,
EZK_MOD_OPTION   = 64,
EZK_MODKEY_COUNT = 7
} ezk_mod_key;

#define EZK_KEYS_XMACRO \
  EZK_KEY_XM(SPACE,                       "Space", 0, 0) \
  EZK_KEY_XM(EXCLAMATIONMARK,    "!", EZK_MOD_SHIFT, 17) \
  EZK_KEY_XM(DOUBLEQUOTE,       "\"", EZK_MOD_SHIFT, 18) \
  EZK_KEY_XM(HASH,                            "#", , 19) \
  EZK_KEY_XM(DOLLAR,              "$", EZK_MOD_SHIFT, 20) \
  EZK_KEY_XM(PERCENT,             "%", EZK_MOD_SHIFT, 21) \
  EZK_KEY_XM(AMPERSAND,           "&", EZK_MOD_SHIFT, 23) \
  EZK_KEY_XM(SINGLEQUOTE,                     "'", 0, 0) \
  EZK_KEY_XM(OPENBRACKET,         "(", EZK_MOD_SHIFT, 25) \
  EZK_KEY_XM(CLOSEBRACKET,        ")", EZK_MOD_SHIFT, 26) \
  EZK_KEY_XM(ASTERISK,            "*", EZK_MOD_SHIFT, 24) \
  EZK_KEY_XM(PLUS,                "+", EZK_MOD_SHIFT, 29) \
  EZK_KEY_XM(COMMA,                           ",", 0, 0) \
  EZK_KEY_XM(HYPHEN,                          "-", 0, 0) \
  EZK_KEY_XM(PERIOD,                          ".", 0, 0) \
  EZK_KEY_XM(SLASH,                           "/", 0, 0) \
  EZK_KEY_XM(ZERO,                            "0", 0, 0) \
  EZK_KEY_XM(ONE,                             "1", 0, 0) \
  EZK_KEY_XM(TWO,                             "2", 0, 0) \
  EZK_KEY_XM(THREE,                           "3", 0, 0) \
  EZK_KEY_XM(FOUR,                            "4", 0, 0) \
  EZK_KEY_XM(FIVE,                            "5", 0, 0) \
  EZK_KEY_XM(SIX,                             "6", 0, 0) \
  EZK_KEY_XM(SEVEN,                           "7", 0, 0) \
  EZK_KEY_XM(EIGHT,                           "8", 0, 0) \
  EZK_KEY_XM(NINE,                            "9", 0, 0) \
  EZK_KEY_XM(COLON,               ":", EZK_MOD_SHIFT, 27) \
  EZK_KEY_XM(SEMICOLON,                       ";", 0, 0) \
  EZK_KEY_XM(LESSTHAN,            "<", EZK_MOD_SHIFT, 12) \
  EZK_KEY_XM(EQUALS,                          "=", 0, 0) \
  EZK_KEY_XM(GREATERTHAN,         ">", EZK_MOD_SHIFT, 14) \
  EZK_KEY_XM(QUESTIONMARK,        "?", EZK_MOD_SHIFT, 15) \
  EZK_KEY_XM(AMPERSAT,            "@", EZK_MOD_SHIFT, 2) /* UK layout */ \
  EZK_KEY_XM(A,                   "A", EZK_MOD_SHIFT, 65) \
  EZK_KEY_XM(B,                   "B", EZK_MOD_SHIFT, 66) \
  EZK_KEY_XM(C,                   "C", EZK_MOD_SHIFT, 67) \
  EZK_KEY_XM(D,                   "D", EZK_MOD_SHIFT, 68) \
  EZK_KEY_XM(E,                   "E", EZK_MOD_SHIFT, 69) \
  EZK_KEY_XM(F,                   "F", EZK_MOD_SHIFT, 70) \
  EZK_KEY_XM(G,                   "G", EZK_MOD_SHIFT, 71) \
  EZK_KEY_XM(H,                   "H", EZK_MOD_SHIFT, 72) \
  EZK_KEY_XM(I,                   "I", EZK_MOD_SHIFT, 73) \
  EZK_KEY_XM(J,                   "J", EZK_MOD_SHIFT, 74) \
  EZK_KEY_XM(K,                   "K", EZK_MOD_SHIFT, 75) \
  EZK_KEY_XM(L,                   "L", EZK_MOD_SHIFT, 76) \
  EZK_KEY_XM(M,                   "M", EZK_MOD_SHIFT, 77) \
  EZK_KEY_XM(N,                   "N", EZK_MOD_SHIFT, 78) \
  EZK_KEY_XM(O,                   "O", EZK_MOD_SHIFT, 79) \
  EZK_KEY_XM(P,                   "P", EZK_MOD_SHIFT, 80) \
  EZK_KEY_XM(Q,                   "Q", EZK_MOD_SHIFT, 81) \
  EZK_KEY_XM(R,                   "R", EZK_MOD_SHIFT, 82) \
  EZK_KEY_XM(S,                   "S", EZK_MOD_SHIFT, 83) \
  EZK_KEY_XM(T,                   "T", EZK_MOD_SHIFT, 84) \
  EZK_KEY_XM(U,                   "U", EZK_MOD_SHIFT, 85) \
  EZK_KEY_XM(V,                   "V", EZK_MOD_SHIFT, 86) \
  EZK_KEY_XM(W,                   "W", EZK_MOD_SHIFT, 87) \
  EZK_KEY_XM(X,                   "X", EZK_MOD_SHIFT, 88) \
  EZK_KEY_XM(Y,                   "Y", EZK_MOD_SHIFT, 89) \
  EZK_KEY_XM(Z,                   "Z", EZK_MOD_SHIFT, 90) \
  EZK_KEY_XM(OPENBRACKETSQ,                   "[", 0, 0) \
  EZK_KEY_XM(BACKSLASH,                      "\\", 0, 0) \
  EZK_KEY_XM(CLOSEBRACKETSQ,                  "]", 0, 0) \
  EZK_KEY_XM(CIRCUMFLEX,          "^", EZK_MOD_SHIFT, 22) \
  EZK_KEY_XM(UNDERSCORE,          "_", EZK_MOD_SHIFT, 13) \
  EZK_KEY_XM(GRAVE,                           "`", 0, 0) \
  EZK_KEY_XM(a,                               "a", 0, 0) \
  EZK_KEY_XM(b,                               "b", 0, 0) \
  EZK_KEY_XM(c,                               "c", 0, 0) \
  EZK_KEY_XM(d,                               "d", 0, 0) \
  EZK_KEY_XM(e,                               "e", 0, 0) \
  EZK_KEY_XM(f,                               "f", 0, 0) \
  EZK_KEY_XM(g,                               "g", 0, 0) \
  EZK_KEY_XM(h,                               "h", 0, 0) \
  EZK_KEY_XM(i,                               "i", 0, 0) \
  EZK_KEY_XM(j,                               "j", 0, 0) \
  EZK_KEY_XM(k,                               "k", 0, 0) \
  EZK_KEY_XM(l,                               "l", 0, 0) \
  EZK_KEY_XM(m,                               "m", 0, 0) \
  EZK_KEY_XM(n,                               "n", 0, 0) \
  EZK_KEY_XM(o,                               "o", 0, 0) \
  EZK_KEY_XM(p,                               "p", 0, 0) \
  EZK_KEY_XM(q,                               "q", 0, 0) \
  EZK_KEY_XM(r,                               "r", 0, 0) \
  EZK_KEY_XM(s,                               "s", 0, 0) \
  EZK_KEY_XM(t,                               "t", 0, 0) \
  EZK_KEY_XM(u,                               "u", 0, 0) \
  EZK_KEY_XM(v,                               "v", 0, 0) \
  EZK_KEY_XM(w,                               "w", 0, 0) \
  EZK_KEY_XM(x,                               "x", 0, 0) \
  EZK_KEY_XM(y,                               "y", 0, 0) \
  EZK_KEY_XM(z,                               "z", 0, 0) \
  EZK_KEY_XM(OPENBRACE,           "{", EZK_MOD_SHIFT, 59) \
  EZK_KEY_XM(PIPE,                 "|", EZK_MOD_SHIFT, 60) \
  EZK_KEY_XM(CLOSEBRACE,          "}", EZK_MOD_SHIFT, 61) \
  EZK_KEY_XM(TILDE,               "~", EZK_MOD_SHIFT, 3) \
  EZK_KEY_XM(DELETE,                        "DEL", 0, 0) \
  EZK_KEY_XM(STERLING,        "POUND", EZK_MOD_SHIFT, 19) /* Doesn't use character as they are non-ASCII */ \
  EZK_KEY_XM(EURO,             "EURO", EZK_MOD_ALTGR, 20) \
  EZK_KEY_XM(BROKENPIPE,"BROKEN PIPE", EZK_MOD_ALTGR, 64) \
  EZK_KEY_XM(NEGATION,       "NEGATE", EZK_MOD_SHIFT, 64) \
  EZK_KEY_XM(SHIFT,                       "SHIFT", 0, 0) \
  EZK_KEY_XM(CONTROL,                   "CONTROL", 0, 0) \
  EZK_KEY_XM(ALT,                           "ALT", 0, 0) \
  EZK_KEY_XM(ALTGR,                       "ALTGR", 0, 0) \
  EZK_KEY_XM(COMMAND,                   "COMMAND", 0, 0) \
  EZK_KEY_XM(OPTION,                     "OPTION", 0, 0) \
  EZK_KEY_XM(EJECT,                       "EJECT", 0, 0) \
  EZK_KEY_XM(FN,                             "FN", 0, 0) \
  EZK_KEY_XM(ESCAPE,                        "ESC", 0, 0) \
  EZK_KEY_XM(PRINTSCREEN,              "PRNTSCRN", 0, 0) \
  EZK_KEY_XM(CAPSLOCK,                     "CAPS", 0, 0) \
  EZK_KEY_XM(NUMLOCK,                   "NUMLOCK", 0, 0) \
  EZK_KEY_XM(SCROLLLOCK,               "SCRLLOCK", 0, 0) \
  EZK_KEY_XM(PAGEUP,                     "PAGEUP", 0, 0) \
  EZK_KEY_XM(PAGEDOWN,                 "PAGEDOWN", 0, 0) \
  EZK_KEY_XM(INSERT,                        "INS", 0, 0) \
  EZK_KEY_XM(HOME,                         "HOME", 0, 0) \
  EZK_KEY_XM(END,                           "END", 0, 0) \
  EZK_KEY_XM(ENTER,                       "ENTER", 0, 0) \
  EZK_KEY_XM(BACKSPACE,               "BACKSPACE", 0, 0) \
  EZK_KEY_XM(PAUSEBREAK,             "PAUSEBREAK", 0, 0) \
  EZK_KEY_XM(MENU,                         "MENU", 0, 0) \
  EZK_KEY_XM(WINDOWS,                       "WIN", 0, 0) \
  EZK_KEY_XM(NUMPAD0,                      "NUM0", 0, 0) \
  EZK_KEY_XM(NUMPAD1,                      "NUM1", 0, 0) \
  EZK_KEY_XM(NUMPAD2,                      "NUM2", 0, 0) \
  EZK_KEY_XM(NUMPAD3,                      "NUM3", 0, 0) \
  EZK_KEY_XM(NUMPAD4,                      "NUM4", 0, 0) \
  EZK_KEY_XM(NUMPAD5,                      "NUM5", 0, 0) \
  EZK_KEY_XM(NUMPAD6,                      "NUM6", 0, 0) \
  EZK_KEY_XM(NUMPAD7,                      "NUM7", 0, 0) \
  EZK_KEY_XM(NUMPAD8,                      "NUM8", 0, 0) \
  EZK_KEY_XM(NUMPAD9,                      "NUM9", 0, 0) \
  EZK_KEY_XM(NUMPADPOINT,              "NUMPOINT", 0, 0) \
  EZK_KEY_XM(NUMPADDIVIDE,            "NUMDIVIDE", 0, 0) \
  EZK_KEY_XM(NUMPADMULTIPLY,        "NUMMULTIPLY", 0, 0) \
  EZK_KEY_XM(NUMPADSUBTRACT,        "NUMSUBTRACT", 0, 0) \
  EZK_KEY_XM(NUMPADPLUS,                "NUMPLUS", 0, 0) \
  EZK_KEY_XM(NUMPADENTER,              "NUMENTER", 0, 0) \
  EZK_KEY_XM(ARROWUP,                        "UP", 0, 0) \
  EZK_KEY_XM(ARROWDOWN,                    "DOWN", 0, 0) \
  EZK_KEY_XM(ARROWLEFT,                    "LEFT", 0, 0) \
  EZK_KEY_XM(ARROWRIGHT,                  "RIGHT", 0, 0) \
  EZK_KEY_XM(F1,                             "F1", 0, 0) \
  EZK_KEY_XM(F2,                             "F2", 0, 0) \
  EZK_KEY_XM(F3,                             "F3", 0, 0) \
  EZK_KEY_XM(F4,                             "F4", 0, 0) \
  EZK_KEY_XM(F5,                             "F5", 0, 0) \
  EZK_KEY_XM(F6,                             "F6", 0, 0) \
  EZK_KEY_XM(F7,                             "F7", 0, 0) \
  EZK_KEY_XM(F8,                             "F8", 0, 0) \
  EZK_KEY_XM(F9,                             "F9", 0, 0) \
  EZK_KEY_XM(F10,                           "F10", 0, 0) \
  EZK_KEY_XM(F11,                           "F11", 0, 0) \
  EZK_KEY_XM(F12,                           "F12", 0, 0) \
  EZK_KEY_XM(F13,                           "F13", 0, 0) \
  EZK_KEY_XM(F14,                           "F14", 0, 0) \
  EZK_KEY_XM(F15,                           "F15", 0, 0) \
  EZK_KEY_XM(F16,                           "F16", 0, 0) \
  EZK_KEY_XM(F17,                           "F17", 0, 0) \
  EZK_KEY_XM(F18,                           "F18", 0, 0) \
  EZK_KEY_XM(F19,                           "F19", 0, 0) \
  EZK_KEY_XM(F20,                           "F20", 0, 0) \
  EZK_KEY_XM(F21,                           "F21", 0, 0) \
  EZK_KEY_XM(F22,                           "F22", 0, 0) \
  EZK_KEY_XM(F23,                           "F23", 0, 0) \
  EZK_KEY_XM(F24,                           "F24", 0, 0) \
  EZK_KEY_XM(F25,                           "F25", 0, 0) \
  EZK_KEY_XM(F26,                           "F26", 0, 0) \
  EZK_KEY_XM(F27,                           "F27", 0, 0) \
  EZK_KEY_XM(F28,                           "F28", 0, 0) \
  EZK_KEY_XM(F29,                           "F29", 0, 0) \
  EZK_KEY_XM(F30,                           "F30", 0, 0) \
  EZK_KEY_XM(F31,                           "F31", 0, 0) \
  EZK_KEY_XM(F32,                           "F32", 0, 0) \
  EZK_KEY_XM(F33,                           "F33", 0, 0) \
  EZK_KEY_XM(F34,                           "F34", 0, 0) \
  EZK_KEY_XM(F35,                           "F35", 0, 0)

typedef enum {
#define EZK_KEY_XM(key,name,mod,base) EZK_KEYCODE_##key,
  EZK_KEYS_XMACRO
#undef EZK_KEY_XM
EZK_KEY_COUNT
} ezk_key;

#define EZK_KEY_XM(key,name,mod,base) name,
const char* ezk_key_names[] = {
  EZK_KEYS_XMACRO
};
#undef EZK_KEY_XM


#define EZK_KEY_NAME(key) ezk_key_names[(int)key] // simple conversion macro

