// keycodes for ezekiel
// the codes are based on a number of standards. Most codes are based off of ASCII
// keys acquired from modifier keys are also added here.

#define EZK_KEYS_XMACRO \
  EZK_KEY_XM(SPACE,               "Space") \
  EZK_KEY_XM(EXCLAMATIONMARK,         "!") \
  EZK_KEY_XM(DOUBLEQUOTE,            "\"") \
  EZK_KEY_XM(HASH,                    "#") \
  EZK_KEY_XM(DOLLAR,                  "$") \
  EZK_KEY_XM(PERCENT,                 "%") \
  EZK_KEY_XM(AMPERSAND,               "&") \
  EZK_KEY_XM(SINGLEQUOTE,             "'") \
  EZK_KEY_XM(OPENBRACKET,             "(") \
  EZK_KEY_XM(CLOSEBRACKET,            ")") \
  EZK_KEY_XM(ASTERISK,                "*") \
  EZK_KEY_XM(PLUS,                    "+") \
  EZK_KEY_XM(COMMA,                   ",") \
  EZK_KEY_XM(HYPHEN,                  "-") \
  EZK_KEY_XM(PERIOD,                  ".") \
  EZK_KEY_XM(SLASH,                   "/") \
  EZK_KEY_XM(ZERO,                    "0") \
  EZK_KEY_XM(ONE,                     "1") \
  EZK_KEY_XM(TWO,                     "2") \
  EZK_KEY_XM(THREE,                   "3") \
  EZK_KEY_XM(FOUR,                    "4") \
  EZK_KEY_XM(FIVE,                    "5") \
  EZK_KEY_XM(SIX,                     "6") \
  EZK_KEY_XM(SEVEN,                   "7") \
  EZK_KEY_XM(EIGHT,                   "8") \
  EZK_KEY_XM(NINE,                    "9") \
  EZK_KEY_XM(COLON,                   ":") \
  EZK_KEY_XM(SEMICOLON,               ";") \
  EZK_KEY_XM(LESSTHAN,                "<") \
  EZK_KEY_XM(EQUALS,                  "=") \
  EZK_KEY_XM(GREATERTHAN,             ">") \
  EZK_KEY_XM(QUESTIONMARK,            "?") \
  EZK_KEY_XM(AMPERSAT,                "@") \
  EZK_KEY_XM(A,                       "A") \
  EZK_KEY_XM(B,                       "B") \
  EZK_KEY_XM(C,                       "C") \
  EZK_KEY_XM(D,                       "D") \
  EZK_KEY_XM(E,                       "E") \
  EZK_KEY_XM(F,                       "F") \
  EZK_KEY_XM(G,                       "G") \
  EZK_KEY_XM(H,                       "H") \
  EZK_KEY_XM(I,                       "I") \
  EZK_KEY_XM(J,                       "J") \
  EZK_KEY_XM(K,                       "K") \
  EZK_KEY_XM(L,                       "L") \
  EZK_KEY_XM(M,                       "M") \
  EZK_KEY_XM(N,                       "N") \
  EZK_KEY_XM(O,                       "O") \
  EZK_KEY_XM(P,                       "P") \
  EZK_KEY_XM(Q,                       "Q") \
  EZK_KEY_XM(R,                       "R") \
  EZK_KEY_XM(S,                       "S") \
  EZK_KEY_XM(T,                       "T") \
  EZK_KEY_XM(U,                       "U") \
  EZK_KEY_XM(V,                       "V") \
  EZK_KEY_XM(W,                       "W") \
  EZK_KEY_XM(X,                       "X") \
  EZK_KEY_XM(Y,                       "Y") \
  EZK_KEY_XM(Z,                       "Z") \
  EZK_KEY_XM(OPENBRACKETSQ,           "[") \
  EZK_KEY_XM(BACKSLASH,              "\\") \
  EZK_KEY_XM(CLOSEBRACKETSQ,          "]") \
  EZK_KEY_XM(CIRCUMFLEX,              "^") \
  EZK_KEY_XM(UNDERSCORE,              "_") \
  EZK_KEY_XM(GRAVE,                   "`") \
  EZK_KEY_XM(a,                       "a") \
  EZK_KEY_XM(b,                       "b") \
  EZK_KEY_XM(c,                       "c") \
  EZK_KEY_XM(d,                       "d") \
  EZK_KEY_XM(e,                       "e") \
  EZK_KEY_XM(f,                       "f") \
  EZK_KEY_XM(g,                       "g") \
  EZK_KEY_XM(h,                       "h") \
  EZK_KEY_XM(i,                       "i") \
  EZK_KEY_XM(j,                       "j") \
  EZK_KEY_XM(k,                       "k") \
  EZK_KEY_XM(l,                       "l") \
  EZK_KEY_XM(m,                       "m") \
  EZK_KEY_XM(n,                       "n") \
  EZK_KEY_XM(o,                       "o") \
  EZK_KEY_XM(p,                       "p") \
  EZK_KEY_XM(q,                       "q") \
  EZK_KEY_XM(r,                       "r") \
  EZK_KEY_XM(s,                       "s") \
  EZK_KEY_XM(t,                       "t") \
  EZK_KEY_XM(u,                       "u") \
  EZK_KEY_XM(v,                       "v") \
  EZK_KEY_XM(w,                       "w") \
  EZK_KEY_XM(x,                       "x") \
  EZK_KEY_XM(y,                       "y") \
  EZK_KEY_XM(z,                       "z") \
  EZK_KEY_XM(OPENBRACE,               "{") \
  EZK_KEY_XM(BAR,                     "|") \
  EZK_KEY_XM(CLOSEBRACE,              "}") \
  EZK_KEY_XM(TILDE,                   "~") \
  EZK_KEY_XM(DELETE,                "DEL") \
  EZK_KEY_XM(STERLING,            "POUND") /* Doesn't use character as they are non-ASCII */ \
  EZK_KEY_XM(EURO,                 "EURO") \
  EZK_KEY_XM(BROKENPIPE,    "BROKEN PIPE") \
  EZK_KEY_XM(NEGATION,           "NEGATE") \
  EZK_KEY_XM(SHIFT,               "SHIFT") \
  EZK_KEY_XM(CONTROL,           "CONTROL") \
  EZK_KEY_XM(ALT,                   "ALT") \
  EZK_KEY_XM(ALTGR,               "ALTGR") \
  EZK_KEY_XM(COMMAND,           "COMMAND") \
  EZK_KEY_XM(OPTION,             "OPTION") \
  EZK_KEY_XM(EJECT,               "EJECT") \
  EZK_KEY_XM(FN,                     "FN") \
  EZK_KEY_XM(ESCAPE,                "ESC") \
  EZK_KEY_XM(PRINTSCREEN,      "PRNTSCRN") \
  EZK_KEY_XM(CAPSLOCK,             "CAPS") \
  EZK_KEY_XM(NUMLOCK,           "NUMLOCK") \
  EZK_KEY_XM(SCROLLLOCK,       "SCRLLOCK") \
  EZK_KEY_XM(PAGEUP,             "PAGEUP") \
  EZK_KEY_XM(PAGEDOWN,         "PAGEDOWN") \
  EZK_KEY_XM(INSERT,                "INS") \
  EZK_KEY_XM(HOME,                 "HOME") \
  EZK_KEY_XM(END,                   "END") \
  EZK_KEY_XM(ENTER,               "ENTER") \
  EZK_KEY_XM(BACKSPACE,       "BACKSPACE") \
  EZK_KEY_XM(PAUSEBREAK,     "PAUSEBREAK") \
  EZK_KEY_XM(MENU,                 "MENU") \
  EZK_KEY_XM(WINDOWS,               "WIN") \
  EZK_KEY_XM(NUMPAD0,              "NUM0") \
  EZK_KEY_XM(NUMPAD1,              "NUM1") \
  EZK_KEY_XM(NUMPAD2,              "NUM2") \
  EZK_KEY_XM(NUMPAD3,              "NUM3") \
  EZK_KEY_XM(NUMPAD4,              "NUM4") \
  EZK_KEY_XM(NUMPAD5,              "NUM5") \
  EZK_KEY_XM(NUMPAD6,              "NUM6") \
  EZK_KEY_XM(NUMPAD7,              "NUM7") \
  EZK_KEY_XM(NUMPAD8,              "NUM8") \
  EZK_KEY_XM(NUMPAD9,              "NUM9") \
  EZK_KEY_XM(NUMPADPOINT,      "NUMPOINT") \
  EZK_KEY_XM(NUMPADDIVIDE,    "NUMDIVIDE") \
  EZK_KEY_XM(NUMPADMULTIPLY,"NUMMULTIPLY") \
  EZK_KEY_XM(NUMPADSUBTRACT,"NUMSUBTRACT") \
  EZK_KEY_XM(NUMPADPLUS,        "NUMPLUS") \
  EZK_KEY_XM(NUMPADENTER,      "NUMENTER") \
  EZK_KEY_XM(ARROWUP,                "UP") \
  EZK_KEY_XM(ARROWDOWN,            "DOWN") \
  EZK_KEY_XM(ARROWLEFT,            "LEFT") \
  EZK_KEY_XM(ARROWRIGHT,          "RIGHT") \
  EZK_KEY_XM(F1,                     "F1") \
  EZK_KEY_XM(F2,                     "F2") \
  EZK_KEY_XM(F3,                     "F3") \
  EZK_KEY_XM(F4,                     "F4") \
  EZK_KEY_XM(F5,                     "F5") \
  EZK_KEY_XM(F6,                     "F6") \
  EZK_KEY_XM(F7,                     "F7") \
  EZK_KEY_XM(F8,                     "F8") \
  EZK_KEY_XM(F9,                     "F9") \
  EZK_KEY_XM(F10,                   "F10") \
  EZK_KEY_XM(F11,                   "F11") \
  EZK_KEY_XM(F12,                   "F12") \
  EZK_KEY_XM(F13,                   "F13") \
  EZK_KEY_XM(F14,                   "F14") \
  EZK_KEY_XM(F15,                   "F15") \
  EZK_KEY_XM(F16,                   "F16") \
  EZK_KEY_XM(F17,                   "F17") \
  EZK_KEY_XM(F18,                   "F18") \
  EZK_KEY_XM(F19,                   "F19") \
  EZK_KEY_XM(F20,                   "F20") \
  EZK_KEY_XM(F21,                   "F21") \
  EZK_KEY_XM(F22,                   "F22") \
  EZK_KEY_XM(F23,                   "F23") \
  EZK_KEY_XM(F24,                   "F24") \
  EZK_KEY_XM(F25,                   "F25") \
  EZK_KEY_XM(F26,                   "F26") \
  EZK_KEY_XM(F27,                   "F27") \
  EZK_KEY_XM(F28,                   "F28") \
  EZK_KEY_XM(F29,                   "F29") \
  EZK_KEY_XM(F30,                   "F30") \
  EZK_KEY_XM(F31,                   "F31") \
  EZK_KEY_XM(F32,                   "F32") \
  EZK_KEY_XM(F33,                   "F33") \
  EZK_KEY_XM(F34,                   "F34") \
  EZK_KEY_XM(F35,                   "F35")

typedef enum {
#define EZK_KEY_XM(key,name) EZK_KEYCODE_##key,
  EZK_KEYS_XMACRO
#undef EZK_KEY_XM
EZK_KEY_COUNT
} ezk_key;

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

#define EZK_KEY_XM(key,name) name,
const char* ezk_key_names[] = {
  EZK_KEYS_XMACRO
};
#undef EZK_KEY_XM


#define EZK_KEY_NAME(key) ezk_key_names[(int)key] // simple conversion macro
