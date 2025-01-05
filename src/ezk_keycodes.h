// keycodes for ezekiel

typedef enum {
EZK_MOD_SHIFT    = 1 << 0,
EZK_MOD_CTRL     = 1 << 1,
EZK_MOD_ALT      = 1 << 2,
EZK_MOD_FN       = 1 << 3,
EZK_MOD_ALTGR    = 1 << 4,
EZK_MOD_COMMAND  = 1 << 5,
EZK_MOD_OPTION   = 1 << 6,
EZK_MODKEY_COUNT = 7
} ezk_mod_key;

#define EZK_IKEYS_XMACRO \
  EZK_IKEY_XM(SPACE,                       "Space") \
  EZK_IKEY_XM(EXCLAMATIONMARK,                 "!") \
  EZK_IKEY_XM(HASH,                            "#") \
  EZK_IKEY_XM(SINGLEQUOTE,                     "'") \
  EZK_IKEY_XM(COMMA,                           ",") \
  EZK_IKEY_XM(HYPHEN,                          "-") \
  EZK_IKEY_XM(PERIOD,                          ".") \
  EZK_IKEY_XM(SLASH,                           "/") \
  EZK_IKEY_XM(ZERO,                            "0") \
  EZK_IKEY_XM(ONE,                             "1") \
  EZK_IKEY_XM(TWO,                             "2") \
  EZK_IKEY_XM(THREE,                           "3") \
  EZK_IKEY_XM(FOUR,                            "4") \
  EZK_IKEY_XM(FIVE,                            "5") \
  EZK_IKEY_XM(SIX,                             "6") \
  EZK_IKEY_XM(SEVEN,                           "7") \
  EZK_IKEY_XM(EIGHT,                           "8") \
  EZK_IKEY_XM(NINE,                            "9") \
  EZK_IKEY_XM(SEMICOLON,                       ";") \
  EZK_IKEY_XM(EQUALS,                          "=") \
  EZK_IKEY_XM(OPENBRACKETSQ,                   "[") \
  EZK_IKEY_XM(BACKSLASH,                      "\\") \
  EZK_IKEY_XM(CLOSEBRACKETSQ,                  "]") \
  EZK_IKEY_XM(GRAVE,                           "`") \
  EZK_IKEY_XM(a,                               "a") \
  EZK_IKEY_XM(b,                               "b") \
  EZK_IKEY_XM(c,                               "c") \
  EZK_IKEY_XM(d,                               "d") \
  EZK_IKEY_XM(e,                               "e") \
  EZK_IKEY_XM(f,                               "f") \
  EZK_IKEY_XM(g,                               "g") \
  EZK_IKEY_XM(h,                               "h") \
  EZK_IKEY_XM(i,                               "i") \
  EZK_IKEY_XM(j,                               "j") \
  EZK_IKEY_XM(k,                               "k") \
  EZK_IKEY_XM(l,                               "l") \
  EZK_IKEY_XM(m,                               "m") \
  EZK_IKEY_XM(n,                               "n") \
  EZK_IKEY_XM(o,                               "o") \
  EZK_IKEY_XM(p,                               "p") \
  EZK_IKEY_XM(q,                               "q") \
  EZK_IKEY_XM(r,                               "r") \
  EZK_IKEY_XM(s,                               "s") \
  EZK_IKEY_XM(t,                               "t") \
  EZK_IKEY_XM(u,                               "u") \
  EZK_IKEY_XM(v,                               "v") \
  EZK_IKEY_XM(w,                               "w") \
  EZK_IKEY_XM(x,                               "x") \
  EZK_IKEY_XM(y,                               "y") \
  EZK_IKEY_XM(z,                               "z") \
  EZK_IKEY_XM(DELETE,                        "DEL") \
  EZK_IKEY_XM(SHIFT,                       "SHIFT") \
  EZK_IKEY_XM(CONTROL,                   "CONTROL") \
  EZK_IKEY_XM(ALT,                           "ALT") \
  EZK_IKEY_XM(ALTGR,                       "ALTGR") \
  EZK_IKEY_XM(COMMAND,                   "COMMAND") \
  EZK_IKEY_XM(OPTION,                     "OPTION") \
  EZK_IKEY_XM(EJECT,                       "EJECT") \
  EZK_IKEY_XM(FN,                             "FN") \
  EZK_IKEY_XM(ESCAPE,                        "ESC") \
  EZK_IKEY_XM(PRINTSCREEN,              "PRNTSCRN") \
  EZK_IKEY_XM(CAPSLOCK,                     "CAPS") \
  EZK_IKEY_XM(NUMLOCK,                   "NUMLOCK") \
  EZK_IKEY_XM(SCROLLLOCK,               "SCRLLOCK") \
  EZK_IKEY_XM(PAGEUP,                     "PAGEUP") \
  EZK_IKEY_XM(PAGEDOWN,                 "PAGEDOWN") \
  EZK_IKEY_XM(INSERT,                        "INS") \
  EZK_IKEY_XM(HOME,                         "HOME") \
  EZK_IKEY_XM(END,                           "END") \
  EZK_IKEY_XM(ENTER,                       "ENTER") \
  EZK_IKEY_XM(BACKSPACE,               "BACKSPACE") \
  EZK_IKEY_XM(PAUSEBREAK,             "PAUSEBREAK") \
  EZK_IKEY_XM(MENU,                         "MENU") \
  EZK_IKEY_XM(WINDOWS,                       "WIN") \
  EZK_IKEY_XM(NUMPAD0,                      "NUM0") \
  EZK_IKEY_XM(NUMPAD1,                      "NUM1") \
  EZK_IKEY_XM(NUMPAD2,                      "NUM2") \
  EZK_IKEY_XM(NUMPAD3,                      "NUM3") \
  EZK_IKEY_XM(NUMPAD4,                      "NUM4") \
  EZK_IKEY_XM(NUMPAD5,                      "NUM5") \
  EZK_IKEY_XM(NUMPAD6,                      "NUM6") \
  EZK_IKEY_XM(NUMPAD7,                      "NUM7") \
  EZK_IKEY_XM(NUMPAD8,                      "NUM8") \
  EZK_IKEY_XM(NUMPAD9,                      "NUM9") \
  EZK_IKEY_XM(NUMPADPOINT,              "NUMPOINT") \
  EZK_IKEY_XM(NUMPADDIVIDE,            "NUMDIVIDE") \
  EZK_IKEY_XM(NUMPADMULTIPLY,        "NUMMULTIPLY") \
  EZK_IKEY_XM(NUMPADSUBTRACT,        "NUMSUBTRACT") \
  EZK_IKEY_XM(NUMPADPLUS,                "NUMPLUS") \
  EZK_IKEY_XM(NUMPADENTER,              "NUMENTER") \
  EZK_IKEY_XM(ARROWUP,                        "UP") \
  EZK_IKEY_XM(ARROWDOWN,                    "DOWN") \
  EZK_IKEY_XM(ARROWLEFT,                    "LEFT") \
  EZK_IKEY_XM(ARROWRIGHT,                  "RIGHT") \
  EZK_IKEY_XM(F1,                             "F1") \
  EZK_IKEY_XM(F2,                             "F2") \
  EZK_IKEY_XM(F3,                             "F3") \
  EZK_IKEY_XM(F4,                             "F4") \
  EZK_IKEY_XM(F5,                             "F5") \
  EZK_IKEY_XM(F6,                             "F6") \
  EZK_IKEY_XM(F7,                             "F7") \
  EZK_IKEY_XM(F8,                             "F8") \
  EZK_IKEY_XM(F9,                             "F9") \
  EZK_IKEY_XM(F10,                           "F10") \
  EZK_IKEY_XM(F11,                           "F11") \
  EZK_IKEY_XM(F12,                           "F12") \
  EZK_IKEY_XM(F13,                           "F13") \
  EZK_IKEY_XM(F14,                           "F14") \
  EZK_IKEY_XM(F15,                           "F15") \
  EZK_IKEY_XM(F16,                           "F16") \
  EZK_IKEY_XM(F17,                           "F17") \
  EZK_IKEY_XM(F18,                           "F18") \
  EZK_IKEY_XM(F19,                           "F19") \
  EZK_IKEY_XM(F20,                           "F20") \
  EZK_IKEY_XM(F21,                           "F21") \
  EZK_IKEY_XM(F22,                           "F22") \
  EZK_IKEY_XM(F23,                           "F23") \
  EZK_IKEY_XM(F24,                           "F24") \
  EZK_IKEY_XM(F25,                           "F25") \
  EZK_IKEY_XM(F26,                           "F26") \
  EZK_IKEY_XM(F27,                           "F27") \
  EZK_IKEY_XM(F28,                           "F28") \
  EZK_IKEY_XM(F29,                           "F29") \
  EZK_IKEY_XM(F30,                           "F30") \
  EZK_IKEY_XM(F31,                           "F31") \
  EZK_IKEY_XM(F32,                           "F32") \
  EZK_IKEY_XM(F33,                           "F33") \
  EZK_IKEY_XM(F34,                           "F34") \
  EZK_IKEY_XM(F35,                           "F35")

#define EZK_IKEY_XM(key,name) EZK_IKEY_##key,
typedef enum {
  EZK_IKEYS_XMACRO
  EZK_IKEY_COUNT
} ezk_input_key;
#undef EZK_IKEY_XM

#define EZK_IKEY_XM(key,name) name,
const char* ezk_input_key_names[] = {
  EZK_IKEYS_XMACRO
};
#undef EZK_IKEY_XM

// ckeys - complex keys - are keys that require a modifier to type
#define EZK_CKEYS_XMACRO \
  EZK_CKEY_XM(DOUBLEQUOTE,                    "\"") \
  EZK_CKEY_XM(DOLLAR,                          "$") \
  EZK_CKEY_XM(PERCENT,                         "%") \
  EZK_CKEY_XM(AMPERSAND,                       "&") \
  EZK_CKEY_XM(OPENBRACKET,                     "(") \
  EZK_CKEY_XM(CLOSEBRACKET,                    ")") \
  EZK_CKEY_XM(ASTERISK,                        "*") \
  EZK_CKEY_XM(PLUS,                            "+") \
  EZK_CKEY_XM(COLON,                           ":") \
  EZK_CKEY_XM(LESSTHAN,                        "<") \
  EZK_CKEY_XM(GREATERTHAN,                     ">") \
  EZK_CKEY_XM(QUESTIONMARK,                    "?") \
  EZK_CKEY_XM(AMPERSAT,                        "@") /* UK layout */ \
  EZK_CKEY_XM(A,                               "A") \
  EZK_CKEY_XM(B,                               "B") \
  EZK_CKEY_XM(C,                               "C") \
  EZK_CKEY_XM(D,                               "D") \
  EZK_CKEY_XM(E,                               "E") \
  EZK_CKEY_XM(F,                               "F") \
  EZK_CKEY_XM(G,                               "G") \
  EZK_CKEY_XM(H,                               "H") \
  EZK_CKEY_XM(I,                               "I") \
  EZK_CKEY_XM(J,                               "J") \
  EZK_CKEY_XM(K,                               "K") \
  EZK_CKEY_XM(L,                               "L") \
  EZK_CKEY_XM(M,                               "M") \
  EZK_CKEY_XM(N,                               "N") \
  EZK_CKEY_XM(O,                               "O") \
  EZK_CKEY_XM(P,                               "P") \
  EZK_CKEY_XM(Q,                               "Q") \
  EZK_CKEY_XM(R,                               "R") \
  EZK_CKEY_XM(S,                               "S") \
  EZK_CKEY_XM(T,                               "T") \
  EZK_CKEY_XM(U,                               "U") \
  EZK_CKEY_XM(V,                               "V") \
  EZK_CKEY_XM(W,                               "W") \
  EZK_CKEY_XM(X,                               "X") \
  EZK_CKEY_XM(Y,                               "Y") \
  EZK_CKEY_XM(Z,                               "Z") \
  EZK_CKEY_XM(CIRCUMFLEX,                      "^") \
  EZK_CKEY_XM(UNDERSCORE,                      "_") \
  EZK_CKEY_XM(OPENBRACE,                       "{") \
  EZK_CKEY_XM(PIPE,                            "|") \
  EZK_CKEY_XM(CLOSEBRACE,                      "}") \
  EZK_CKEY_XM(TILDE,                           "~") \
  EZK_CKEY_XM(STERLING,                    "POUND") /* Doesn't use character for name as they are non-ASCII */ \
  EZK_CKEY_XM(EURO,                         "EURO") \
  EZK_CKEY_XM(BROKENPIPE,            "BROKEN PIPE") \
  EZK_CKEY_XM(NEGATION,                   "NEGATE")

#define EZK_CKEY_XM(key,name) EZK_CKEY_##key,
typedef enum {
  EZK_CKEYS_XMACRO
  EZK_CKEY_COUNT
} ezk_complex_key;
#undef EZK_CKEY_XM

#define EZK_CKEY_XM(key,name) name,
const char* ezk_complex_key_names[] = {
  EZK_CKEYS_XMACRO
};
#undef EZK_CKEY_XM

#define EZK_COMPLEX_KEY_NAME(key) ezk_complex_key_names[(int)key]

#define EZK_IKEY_XM(key,name) EZK_KEY_##key,
#define EZK_CKEY_XM(key,name) EZK_KEY_##key,
typedef enum {
  EZK_IKEYS_XMACRO
  EZK_CKEYS_XMACRO
  EZK_KEY_COUNT
} ezk_key;
#undef EZK_IKEY_XM
#undef EZK_CKEY_XM

#define EZK_CKEY_XM(key,name) name,
#define EZK_IKEY_XM(key,name) name,
const char* ezk_key_names[] = {
  EZK_IKEYS_XMACRO
  EZK_CKEYS_XMACRO
};
#undef EZK_IKEY_XM
#undef EZK_CKEY_XM

#define EZK_KEY_NAME(key) ezk_key_names[(int)key]