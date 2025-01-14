// keycodes for ezekiel
// these need a way to implement mappings, for example
// the @ sign is SHIFT+2 on US keyboards, but SHIFT+' on UK keyboards 
// also other keyboards like pinyin, zhuyin and arabic script
// others on the list: DVORAK, AZERTY, QWERTZ and Colemak. Kana AND Latin script
// Hangul, Russian, InScript, Nordic languages, Turkish Q & F, potentially braille 
// input, and just other more ergonomic layouts. 

#include "ezk_primitives.h"

typedef enum {
EZK_MOD_SHIFT    = 1 << 0,
EZK_MOD_ALTGR    = 1 << 1,
EZK_MOD_CTRL     = 1 << 2,
EZK_MOD_ALT      = 1 << 3,
EZK_MOD_FN       = 1 << 4,
EZK_MOD_COMMAND  = 1 << 5,
EZK_MOD_OPTION   = 1 << 6,
EZK_MODKEY_COUNT = 7
} ezk_mod_key;

#define shift_down(mod) mod & 1
#define altgr_down(mod) (mod & 2) >> 1
#define ctrl_down(mod) (mod & 4) >> 2
#define alt_down(mod) (mod & 8) >> 3
#define fn_down(mod) (mod & 16) >> 4
#define command_down(mod) (mod & 32) >> 5
#define option_down(mod) (mod & 64) >> 6


#define EZK_KEYS_XMACRO \
  EZK_KEY_XM(SPACE,                "Space") \
  EZK_KEY_XM(HASH,                     "#") \
  EZK_KEY_XM(SINGLEQUOTE,              "'") \
  EZK_KEY_XM(COMMA,                    ",") \
  EZK_KEY_XM(HYPHEN,                   "-") \
  EZK_KEY_XM(PERIOD,                   ".") \
  EZK_KEY_XM(SLASH,                    "/") \
  EZK_KEY_XM(ZERO,                     "0") \
  EZK_KEY_XM(ONE,                      "1") \
  EZK_KEY_XM(TWO,                      "2") \
  EZK_KEY_XM(THREE,                    "3") \
  EZK_KEY_XM(FOUR,                     "4") \
  EZK_KEY_XM(FIVE,                     "5") \
  EZK_KEY_XM(SIX,                      "6") \
  EZK_KEY_XM(SEVEN,                    "7") \
  EZK_KEY_XM(EIGHT,                    "8") \
  EZK_KEY_XM(NINE,                     "9") \
  EZK_KEY_XM(SEMICOLON,                ";") \
  EZK_KEY_XM(EQUALS,                   "=") \
  EZK_KEY_XM(OPENBRACKETSQ,            "[") \
  EZK_KEY_XM(BACKSLASH,               "\\") \
  EZK_KEY_XM(CLOSEBRACKETSQ,           "]") \
  EZK_KEY_XM(GRAVE,                    "`") \
  EZK_KEY_XM(a,                        "a") \
  EZK_KEY_XM(b,                        "b") \
  EZK_KEY_XM(c,                        "c") \
  EZK_KEY_XM(d,                        "d") \
  EZK_KEY_XM(e,                        "e") \
  EZK_KEY_XM(f,                        "f") \
  EZK_KEY_XM(g,                        "g") \
  EZK_KEY_XM(h,                        "h") \
  EZK_KEY_XM(i,                        "i") \
  EZK_KEY_XM(j,                        "j") \
  EZK_KEY_XM(k,                        "k") \
  EZK_KEY_XM(l,                        "l") \
  EZK_KEY_XM(m,                        "m") \
  EZK_KEY_XM(n,                        "n") \
  EZK_KEY_XM(o,                        "o") \
  EZK_KEY_XM(p,                        "p") \
  EZK_KEY_XM(q,                        "q") \
  EZK_KEY_XM(r,                        "r") \
  EZK_KEY_XM(s,                        "s") \
  EZK_KEY_XM(t,                        "t") \
  EZK_KEY_XM(u,                        "u") \
  EZK_KEY_XM(v,                        "v") \
  EZK_KEY_XM(w,                        "w") \
  EZK_KEY_XM(x,                        "x") \
  EZK_KEY_XM(y,                        "y") \
  EZK_KEY_XM(z,                        "z") \
  EZK_KEY_XM(DELETE,                 "DEL") \
  EZK_KEY_XM(SHIFT,                "SHIFT") \
  EZK_KEY_XM(CONTROL,            "CONTROL") \
  EZK_KEY_XM(ALT,                    "ALT") \
  EZK_KEY_XM(ALTGR,                "ALTGR") \
  EZK_KEY_XM(ESCAPE,                 "ESC") \
  EZK_KEY_XM(PRINTSCREEN,       "PRNTSCRN") \
  EZK_KEY_XM(CAPSLOCK,              "CAPS") \
  EZK_KEY_XM(TAB,                    "TAB") \
  EZK_KEY_XM(NUMLOCK,            "NUMLOCK") \
  EZK_KEY_XM(SCROLLLOCK,        "SCRLLOCK") \
  EZK_KEY_XM(PAGEUP,              "PAGEUP") \
  EZK_KEY_XM(PAGEDOWN,          "PAGEDOWN") \
  EZK_KEY_XM(INSERT,                 "INS") \
  EZK_KEY_XM(HOME,                  "HOME") \
  EZK_KEY_XM(END,                    "END") \
  EZK_KEY_XM(ENTER,                "ENTER") \
  EZK_KEY_XM(BACKSPACE,        "BACKSPACE") \
  EZK_KEY_XM(PAUSEBREAK,      "PAUSEBREAK") \
  EZK_KEY_XM(MENU,                  "MENU") \
  EZK_KEY_XM(NUMPAD0,               "NUM0") \
  EZK_KEY_XM(NUMPAD1,               "NUM1") \
  EZK_KEY_XM(NUMPAD2,               "NUM2") \
  EZK_KEY_XM(NUMPAD3,               "NUM3") \
  EZK_KEY_XM(NUMPAD4,               "NUM4") \
  EZK_KEY_XM(NUMPAD5,               "NUM5") \
  EZK_KEY_XM(NUMPAD6,               "NUM6") \
  EZK_KEY_XM(NUMPAD7,               "NUM7") \
  EZK_KEY_XM(NUMPAD8,               "NUM8") \
  EZK_KEY_XM(NUMPAD9,               "NUM9") \
  EZK_KEY_XM(NUMPADPOINT,       "NUMPOINT") \
  EZK_KEY_XM(NUMPADDIVIDE,     "NUMDIVIDE") \
  EZK_KEY_XM(NUMPADMULTIPLY, "NUMMULTIPLY") \
  EZK_KEY_XM(NUMPADSUBTRACT, "NUMSUBTRACT") \
  EZK_KEY_XM(NUMPADPLUS,         "NUMPLUS") \
  EZK_KEY_XM(NUMPADENTER,       "NUMENTER") \
  EZK_KEY_XM(ARROWUP,                 "UP") \
  EZK_KEY_XM(ARROWDOWN,             "DOWN") \
  EZK_KEY_XM(ARROWLEFT,             "LEFT") \
  EZK_KEY_XM(ARROWRIGHT,           "RIGHT") \
  EZK_KEY_XM(F1,                      "F1") \
  EZK_KEY_XM(F2,                      "F2") \
  EZK_KEY_XM(F3,                      "F3") \
  EZK_KEY_XM(F4,                      "F4") \
  EZK_KEY_XM(F5,                      "F5") \
  EZK_KEY_XM(F6,                      "F6") \
  EZK_KEY_XM(F7,                      "F7") \
  EZK_KEY_XM(F8,                      "F8") \
  EZK_KEY_XM(F9,                      "F9") \
  EZK_KEY_XM(F10,                    "F10") \
  EZK_KEY_XM(F11,                    "F11") \
  EZK_KEY_XM(F12,                    "F12") \
  EZK_KEY_XM(F13,                    "F13") \
  EZK_KEY_XM(F14,                    "F14") \
  EZK_KEY_XM(F15,                    "F15") \
  EZK_KEY_XM(F16,                    "F16") \
  EZK_KEY_XM(F17,                    "F17") \
  EZK_KEY_XM(F18,                    "F18") \
  EZK_KEY_XM(F19,                    "F19") \
  EZK_KEY_XM(F20,                    "F20") \
  EZK_KEY_XM(F21,                    "F21") \
  EZK_KEY_XM(F22,                    "F22") \
  EZK_KEY_XM(F23,                    "F23") \
  EZK_KEY_XM(F24,                    "F24") \
  EZK_KEY_XM(F25,                    "F25") \
  EZK_KEY_XM(F26,                    "F26") \
  EZK_KEY_XM(F27,                    "F27") \
  EZK_KEY_XM(F28,                    "F28") \
  EZK_KEY_XM(F29,                    "F29") \
  EZK_KEY_XM(F30,                    "F30") \
  EZK_KEY_XM(F31,                    "F31") \
  EZK_KEY_XM(F32,                    "F32") \
  EZK_KEY_XM(F33,                    "F33") \
  EZK_KEY_XM(F34,                    "F34") \
  EZK_KEY_XM(F35,                    "F35")

#define EZK_KEY_XM(key,name) EZK_KEY_##key,
typedef enum {
  EZK_KEY_NULL,
  EZK_KEYS_XMACRO
  EZK_KEY_COUNT
} ezk_key;
#undef EZK_KEY_XM

#define EZK_KEY_XM(key,name) name,
const char* ezk_key_names[] = {
  "NULL",
  EZK_KEYS_XMACRO
};
#undef EZK_KEY_XM

// ckeys - complex keys - are keys that require a modifier to type
// arg 1 is the base key, 
// arg 2 is whether a key is made when shift is pressed down
// arg 3 is the key made when shift is pressed
// arg 4 is the name of the key made when shift is down
// arg 5 is whether a key is made when altgr is pressed down
// args 6 & 7 are the type and name of the key 

#define EZK_CKEYS_XMACRO \
  EZK_CKEY_XM(SPACE,          0,0,0,                             0,0,0) \
  EZK_CKEY_XM(HASH,           1,TILDE,"`",                       1,GRAVEACCENT,"GRAVE ACCENT") \
  EZK_CKEY_XM(SINGLEQUOTE,    1,AMPERSAT,"@",                    1,CIRCUMFLEX,"CIRCUMFLEX") /*UK layout*/ \
  EZK_CKEY_XM(COMMA,          1,LESSTHAN,"<",                    1,BULLET,"BULLET") \
  EZK_CKEY_XM(HYPHEN,         1,UNDERSCORE,"_",                  0,0,0) \
  EZK_CKEY_XM(PERIOD,         1,GREATERTHAN,">",                 1,INTERPUNCT,"INTERPUNCT") \
  EZK_CKEY_XM(SLASH,          1,QUESTIONMARK,"?",                1,UNDERDOT,"UNDERDOT") \
  EZK_CKEY_XM(ZERO,           1,CLOSEBRACKET,")",                0,0,0) \
  EZK_CKEY_XM(ONE,            1,EXCLAMATIONMARK,"!",             1,SUPERSCRIPTONE,"SUPERSCRIPT 1") \
  EZK_CKEY_XM(TWO,            1,DOUBLEQUOTE,"\"",                1,SUPERSCRIPTWO,"SUPERSCRIPT 2") \
  EZK_CKEY_XM(THREE,          1,STERLING,"POUND",                1,SUPERSCRIPTTHREE,"SUPERSCRIPT 3") /*ditto*/ \
  EZK_CKEY_XM(FOUR,           1,DOLLAR,"$",                      1,EURO,"EURO") \
  EZK_CKEY_XM(FIVE,           1,PERCENT,"%",                     1,FRACTIONHALF,"ONE HALF FRACTION") \
  EZK_CKEY_XM(SIX,            1,CARET,"^",                       1,FRACTIONTHREEQUARTERS,"THREE QUARTERS FRACTION") \
  EZK_CKEY_XM(SEVEN,          1,AMPERSAND,"&",                   0,0,0) \
  EZK_CKEY_XM(EIGHT,          1,ASTERISK,"*",                    0,0,0) \
  EZK_CKEY_XM(NINE,           1,OPENBRACKET,"(",                 0,0,0) \
  EZK_CKEY_XM(SEMICOLON,      1,COLON,":",                       1,ACUTEACCENT,"ACUTE ACCENT") \
  EZK_CKEY_XM(EQUALS,         1,PLUS,"+",                        1,CEDILLA,"CEDILLA") \
  EZK_CKEY_XM(OPENBRACKETSQ,  1,OPENBRACE,"{",                   1,DOUBLEOVERDOT,"DOUBLE OVERDOT") \
  EZK_CKEY_XM(BACKSLASH,      1,PIPE,"|",                        0,0,0) \
  EZK_CKEY_XM(CLOSEBRACKETSQ, 1,CLOSEBRACE,"}",                  1,TILDEACCENT,"TILDE ACCENT") \
  EZK_CKEY_XM(GRAVE,          1,NEGATION,"NEGATE",               1,BROKENPIPE,"BROKEN PIPE") \
  EZK_CKEY_XM(a,              1,A,"A",                           1,ASHLETTER,"ASH LETTER") \
  EZK_CKEY_XM(b,              1,B,"B",                           1,SMARTQUOTESOPEN,"OPEN SMART QUOTATION MARKS") \
  EZK_CKEY_XM(c,              1,C,"C",                           1,CENTSYMBOL,"CENT") \
  EZK_CKEY_XM(d,              1,D,"D",                           1,OLOWERWITHTILDE,"o WITH TILDE ACCENT") \
  EZK_CKEY_XM(e,              1,E,"E",                           0,0,0) \
  EZK_CKEY_XM(f,              1,F,"F",                           1,DLOWERWITHSTROKE,"d WITH STROKE") \
  EZK_CKEY_XM(g,              1,G,"G",                           1,ENDLETTER,"ENG LETTER") \
  EZK_CKEY_XM(h,              1,H,"H",                           1,HLOWERWITHSTROKE,"h WITH STROKE") \
  EZK_CKEY_XM(i,              1,I,"I",                           1,ARROWCHARRIGHT,"RIGHT ARROW") \
  EZK_CKEY_XM(j,              1,J,"J",                           1,HOOKABOVE,"HOOK ACCENT") \
  EZK_CKEY_XM(k,              1,K,"K",                           1,KRALETTER,"KRA LETTER") \
  EZK_CKEY_XM(l,              1,L,"L",                           1,LLOWERWITHSTROKE,"l WITH STROKE") \
  EZK_CKEY_XM(m,              1,M,"M",                           1,MULETTER,"MU LETTER") \
  EZK_CKEY_XM(n,              1,N,"N",                           1,SMARTQUOTESCLOSE,"CLOSING SMART QUOTATION MARKS") \
  EZK_CKEY_XM(o,              1,O,"O",                           1,OSCANDINAVIANLOWER,"SCANDINAVIAN o") \
  EZK_CKEY_XM(p,              1,P,"P",                           1,THORNLETTER,"THORN LETTER") \
  EZK_CKEY_XM(q,              1,Q,"Q",                           0,0,0) \
  EZK_CKEY_XM(r,              1,R,"R",                           1,PILCROW,"PILCROW") \
  EZK_CKEY_XM(s,              1,S,"S",                           1,ESZETTLETTER,"ESZETT LETTER") \
  EZK_CKEY_XM(t,              1,T,"T",                           1,TLOWERWITHSTROKE,"t WITH STROKE") \
  EZK_CKEY_XM(u,              1,U,"U",                           1,ARROWCHARDOWN,"DOWN ARROW") \
  EZK_CKEY_XM(v,              1,V,"V",                           1,DOUBLECOMMA,"DOUBLE COMMA") \
  EZK_CKEY_XM(w,              1,W,"W",                           1,LONGS,"LONG S") \
  EZK_CKEY_XM(x,              1,X,"X",                           1,DOUBLEARROW,"DOUBLE ARROW") \
  EZK_CKEY_XM(y,              1,Y,"Y",                           1,ARROWCHARLEFT,"LEFT ARROW") \
  EZK_CKEY_XM(z,              1,Z,"Z",                           1,DOUBLEBACKARROW,"DOUBLE BACK ARROW") \
  EZK_CKEY_XM(DELETE,         0,0,0,                             0,0,0) \
  EZK_CKEY_XM(SHIFT,          0,0,0,                             0,0,0) \
  EZK_CKEY_XM(CONTROL,        0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ALT,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ALTGR,          0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ESCAPE,         0,0,0,                             0,0,0) \
  EZK_CKEY_XM(PRINTSCREEN,    1,SYSRQ,"SYSRQ",                   0,0,0) \
  EZK_CKEY_XM(CAPSLOCK,       0,0,0,                             0,0,0) \
  EZK_CKEY_XM(TAB,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMLOCK,        0,0,0,                             0,0,0) \
  EZK_CKEY_XM(SCROLLLOCK,     0,0,0,                             0,0,0) \
  EZK_CKEY_XM(PAGEUP,         0,0,0,                             0,0,0) \
  EZK_CKEY_XM(PAGEDOWN,       0,0,0,                             0,0,0) \
  EZK_CKEY_XM(INSERT,         0,0,0,                             0,0,0) \
  EZK_CKEY_XM(HOME,           0,0,0,                             0,0,0) \
  EZK_CKEY_XM(END,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ENTER,          0,0,0,                             0,0,0) \
  EZK_CKEY_XM(BACKSPACE,      0,0,0,                             0,0,0) \
  EZK_CKEY_XM(PAUSEBREAK,     0,0,0,                             0,0,0) \
  EZK_CKEY_XM(MENU,           0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPAD0,        1,NUMPADINS,"NUMPAD INS",          0,0,0) \
  EZK_CKEY_XM(NUMPAD1,        1,NUMPADEND,"NUMPAD END",          0,0,0) \
  EZK_CKEY_XM(NUMPAD2,        1,NUMPADDOWN,"NUMPAD DOWN",        0,0,0) \
  EZK_CKEY_XM(NUMPAD3,        1,NUMPADPGDOWN,"NUMPAD PAGE DOWN", 0,0,0) \
  EZK_CKEY_XM(NUMPAD4,        1,NUMPADLEFT,"NUMPAD LEFT",        0,0,0) \
  EZK_CKEY_XM(NUMPAD5,        0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPAD6,        1,NUMPADRIGHT,"NUMPAD RIGHT",      0,0,0) \
  EZK_CKEY_XM(NUMPAD7,        1,NUMPADHOME,"NUMPAD HOME",        0,0,0) \
  EZK_CKEY_XM(NUMPAD8,        1,NUMPADUP,"NUMPAD UP",            0,0,0) \
  EZK_CKEY_XM(NUMPAD9,        1,NUMPADPGUP,"NUMPAD PAGE UP",     0,0,0) \
  EZK_CKEY_XM(NUMPADPOINT,    1,NUMPADDEL,"NUMPAD DELETE",       0,0,0) \
  EZK_CKEY_XM(NUMPADDIVIDE,   0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPADMULTIPLY, 0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPADSUBTRACT, 0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPADPLUS,     0,0,0,                             0,0,0) \
  EZK_CKEY_XM(NUMPADENTER,    0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ARROWUP,        0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ARROWDOWN,      0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ARROWLEFT,      0,0,0,                             0,0,0) \
  EZK_CKEY_XM(ARROWRIGHT,     0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F1,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F2,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F3,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F4,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F5,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F6,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F7,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F8,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F9,             0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F10,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F11,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F12,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F13,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F14,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F15,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F16,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F17,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F18,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F19,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F20,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F21,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F22,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F23,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F24,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F25,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F26,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F27,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F28,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F29,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F30,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F31,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F32,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F33,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F34,            0,0,0,                             0,0,0) \
  EZK_CKEY_XM(F35,            0,0,0,                             0,0,0)

// couple helper macros so nothing is added for keys where altgr does nothing
#define EZK_ACTIVE_1(name) EZK_CKEY_##name, // has an altgr function
#define EZK_ACTIVE_0(name) // has no altgr function
#define EZK_ACTIVE_KEY(name,active) EZK_ACTIVE_##active(name)

// complex keys enum

#define EZK_CKEY_XM(base,shift,s_type,s_name,altgr,a_type,a_name) EZK_ACTIVE_KEY(s_type,shift) EZK_ACTIVE_KEY(a_type,altgr) 
typedef enum {
  EZK_CKEY_NULL,
  EZK_CKEYS_XMACRO
  EZK_CKEY_COUNT
} ezk_ckey;

#undef EZK_ACTIVE_1
#define EZK_ACTIVE_1(name) #name,

#undef EZK_CKEY_XM
#define EZK_CKEY_XM(base,shift,s_type,s_name,altgr,a_type,a_name)  EZK_ACTIVE_KEY(s_type,shift) EZK_ACTIVE_KEY(a_type,altgr)

const char* ezk_ckey_names[] = {
  "NULL",
  EZK_CKEYS_XMACRO
};

#undef EZK_CKEY_XM
#define EZK_CKEY_XM(base,shift,s_type,s_name,altgr,a_type,a_name) {EZK_ACTIVE_KEY(s_type,shift), EZK_ACTIVE_KEY(a_type,altgr)},

#undef EZK_ACTIVE_0
#undef EZK_ACTIVE_1

#define EZK_ACTIVE_1(name) EZK_CKEY_##name
#define EZK_ACTIVE_0(name) 0 // set it explicitly to 0 to stop the lookup table being jagged

// complex keys lookup table

// first is shift key, then altgr if it exists
static const ezk_ckey ckey_lookup[EZK_KEY_COUNT + 1][2] = {
  {0,0}, // for null key
  EZK_CKEYS_XMACRO
};

#undef EZK_ACTIVE_KEY
#undef EZK_ACTIVE_1
#undef EZK_ACTIVE_0

ezk_ckey ezk_get_ckey_from_base(ezk_key base, ezk_mod_key mods) {
  if(!(altgr_down(mods) || shift_down(mods))) {
    return EZK_CKEY_NULL;
  }
  return ckey_lookup[base][altgr_down(mods) ? 1 : 0]; // NEEDS WORK: what if shift and altgr are down at the same time? 
}

#define EZK_X11_KC_LOOKUP \
  EZK_X11_LT_XM(SPACE,          32) \
  EZK_X11_LT_XM(HASH,           35) \
  EZK_X11_LT_XM(SINGLEQUOTE,    39) \
  EZK_X11_LT_XM(COMMA,          44) \
  EZK_X11_LT_XM(HYPHEN,         45) \
  EZK_X11_LT_XM(PERIOD,         46) \
  EZK_X11_LT_XM(SLASH,          47) \
  EZK_X11_LT_XM(ZERO,           48) \
  EZK_X11_LT_XM(ONE,            49) \
  EZK_X11_LT_XM(TWO,            50) \
  EZK_X11_LT_XM(THREE,          51) \
  EZK_X11_LT_XM(FOUR,           52) \
  EZK_X11_LT_XM(FIVE,           53) \
  EZK_X11_LT_XM(SIX,            54) \
  EZK_X11_LT_XM(SEVEN,          55) \
  EZK_X11_LT_XM(EIGHT,          56) \
  EZK_X11_LT_XM(NINE,           57) \
  EZK_X11_LT_XM(SEMICOLON,      59) \
  EZK_X11_LT_XM(EQUALS,         61) \
  EZK_X11_LT_XM(OPENBRACKETSQ,  91) \
  EZK_X11_LT_XM(BACKSLASH,      92) \
  EZK_X11_LT_XM(CLOSEBRACKETSQ, 93) \
  EZK_X11_LT_XM(GRAVE,          96) \
  EZK_X11_LT_XM(a,              97) \
  EZK_X11_LT_XM(b,              98) \
  EZK_X11_LT_XM(c,              99) \
  EZK_X11_LT_XM(d,              100) \
  EZK_X11_LT_XM(e,              101) \
  EZK_X11_LT_XM(f,              102) \
  EZK_X11_LT_XM(g,              103) \
  EZK_X11_LT_XM(h,              104) \
  EZK_X11_LT_XM(i,              105) \
  EZK_X11_LT_XM(j,              106) \
  EZK_X11_LT_XM(k,              107) \
  EZK_X11_LT_XM(l,              108) \
  EZK_X11_LT_XM(m,              109) \
  EZK_X11_LT_XM(n,              110) \
  EZK_X11_LT_XM(o,              111) \
  EZK_X11_LT_XM(p,              112) \
  EZK_X11_LT_XM(q,              113) \
  EZK_X11_LT_XM(r,              114) \
  EZK_X11_LT_XM(s,              115) \
  EZK_X11_LT_XM(t,              116) \
  EZK_X11_LT_XM(u,              117) \
  EZK_X11_LT_XM(v,              118) \
  EZK_X11_LT_XM(w,              119) \
  EZK_X11_LT_XM(x,              120) \
  EZK_X11_LT_XM(y,              121) \
  EZK_X11_LT_XM(z,              122) \
  EZK_X11_LT_XM(DELETE,         65535) \
  EZK_X11_LT_XM(SHIFT,          65505) \
  EZK_X11_LT_XM(CONTROL,        65507) \
  EZK_X11_LT_XM(ALT,            65513) \
  EZK_X11_LT_XM(ALTGR,          65027) \
  EZK_X11_LT_XM(ESCAPE,         65307) \
  EZK_X11_LT_XM(PRINTSCREEN,    65377) \
  EZK_X11_LT_XM(CAPSLOCK,       65509) \
  EZK_X11_LT_XM(TAB,            65289) \
  EZK_X11_LT_XM(NUMLOCK,        65047) \
  EZK_X11_LT_XM(SCROLLLOCK,     65300) \
  EZK_X11_LT_XM(PAGEUP,         65365) \
  EZK_X11_LT_XM(PAGEDOWN,       65366) \
  EZK_X11_LT_XM(INSERT,         65379) \
  EZK_X11_LT_XM(HOME,           65360) \
  EZK_X11_LT_XM(END,            65367) \
  EZK_X11_LT_XM(ENTER,          65293) \
  EZK_X11_LT_XM(BACKSPACE,      65288) \
  EZK_X11_LT_XM(PAUSEBREAK,     65299) \
  EZK_X11_LT_XM(MENU,           65438) \
  EZK_X11_LT_XM(NUMPAD0,        65438) \
  EZK_X11_LT_XM(NUMPAD1,        65436) \
  EZK_X11_LT_XM(NUMPAD2,        65433) \
  EZK_X11_LT_XM(NUMPAD3,        65435) \
  EZK_X11_LT_XM(NUMPAD4,        65430) \
  EZK_X11_LT_XM(NUMPAD5,        65437) \
  EZK_X11_LT_XM(NUMPAD6,        65432) \
  EZK_X11_LT_XM(NUMPAD7,        65429) \
  EZK_X11_LT_XM(NUMPAD8,        65431) \
  EZK_X11_LT_XM(NUMPAD9,        65434) \
  EZK_X11_LT_XM(NUMPADPOINT,    65439) \
  EZK_X11_LT_XM(NUMPADDIVIDE,   65455) \
  EZK_X11_LT_XM(NUMPADMULTIPLY, 65450) \
  EZK_X11_LT_XM(NUMPADSUBTRACT, 65453) \
  EZK_X11_LT_XM(NUMPADPLUS,     65451) \
  EZK_X11_LT_XM(NUMPADENTER,    65421) \
  EZK_X11_LT_XM(ARROWUP,        65362) \
  EZK_X11_LT_XM(ARROWDOWN,      65364) \
  EZK_X11_LT_XM(ARROWLEFT,      65361) \
  EZK_X11_LT_XM(ARROWRIGHT,     65363) \
  EZK_X11_LT_XM(F1,             65470) \
  EZK_X11_LT_XM(F2,             65471) \
  EZK_X11_LT_XM(F3,             65472) \
  EZK_X11_LT_XM(F4,             65473) \
  EZK_X11_LT_XM(F5,             65474) \
  EZK_X11_LT_XM(F6,             65475) \
  EZK_X11_LT_XM(F7,             65476) \
  EZK_X11_LT_XM(F8,             65477) \
  EZK_X11_LT_XM(F9,             65478) \
  EZK_X11_LT_XM(F10,            65479) \
  EZK_X11_LT_XM(F11,            65480) \
  EZK_X11_LT_XM(F12,            65481) \
  EZK_X11_LT_XM(F13,            65482) \
  EZK_X11_LT_XM(F14,            65483) \
  EZK_X11_LT_XM(F15,            65484) \
  EZK_X11_LT_XM(F16,            65485) \
  EZK_X11_LT_XM(F17,            65486) \
  EZK_X11_LT_XM(F18,            65487) \
  EZK_X11_LT_XM(F19,            65488) \
  EZK_X11_LT_XM(F20,            65489) \
  EZK_X11_LT_XM(F21,            65490) \
  EZK_X11_LT_XM(F22,            65491) \
  EZK_X11_LT_XM(F23,            65492) \
  EZK_X11_LT_XM(F24,            65493) \
  EZK_X11_LT_XM(F25,            65494) \
  EZK_X11_LT_XM(F26,            65495) \
  EZK_X11_LT_XM(F27,            65496) \
  EZK_X11_LT_XM(F28,            65497) \
  EZK_X11_LT_XM(F29,            65498) \
  EZK_X11_LT_XM(F30,            65499) \
  EZK_X11_LT_XM(F31,            65500) \
  EZK_X11_LT_XM(F32,            65501) \
  EZK_X11_LT_XM(F33,            65502) \
  EZK_X11_LT_XM(F34,            65503) \
  EZK_X11_LT_XM(F35,            65504)

//ezk_key ezk_get_x11_key(int key)  {
//  if (key < 0 || key >= EZK_KEY_COUNT) return EZK_KEY_NULL;
//  return x11_kc_lookup[key];
//}