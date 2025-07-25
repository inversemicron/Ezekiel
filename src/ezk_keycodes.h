// keycodes for ezekiel
// these need a way to implement mappings, for example
// the @ sign is SHIFT+2 on US keyboards, but SHIFT+' on UK keyboards 
// also other keyboards like pinyin, zhuyin and arabic script
// others on the list: DVORAK, AZERTY, QWERTZ and Colemak. Kana AND Latin script
// Hangul, Russian, InScript, Nordic languages, Turkish Q & F, potentially braille 
// input, and just other more ergonomic layouts. 

#include "ezk_primitives.h"
#include "ezk_platform.h"

typedef enum {
    EZK_MOD_SHIFT = 1 << 0,
    EZK_MOD_ALTGR = 1 << 1,
    EZK_MOD_CTRL = 1 << 2,
    EZK_MOD_ALT = 1 << 3,
    EZK_MOD_FN = 1 << 4,
    EZK_MOD_COMMAND = 1 << 5,
    EZK_MOD_OPTION = 1 << 6,
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

#define EZK_KEY_XM(key, name) EZK_KEY_##key,
typedef enum {
    EZK_KEY_NULL,
    EZK_KEYS_XMACRO
    EZK_KEY_COUNT
} ezk_key;
#undef EZK_KEY_XM

#define EZK_KEY_XM(key, name) name,
const char *ezk_key_names[] = {
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
#define EZK_ACTIVE_KEY(name, active) EZK_ACTIVE_##active(name)

// complex keys enum

#define EZK_CKEY_XM(base, shift, s_type, s_name, altgr, a_type, a_name) EZK_ACTIVE_KEY(s_type,shift) EZK_ACTIVE_KEY(a_type,altgr)
typedef enum {
    EZK_CKEY_NULL,
    EZK_CKEYS_XMACRO
    EZK_CKEY_COUNT
} ezk_ckey;

#undef EZK_ACTIVE_1
#define EZK_ACTIVE_1(name) #name,

#undef EZK_CKEY_XM
#define EZK_CKEY_XM(base, shift, s_type, s_name, altgr, a_type, a_name)  EZK_ACTIVE_KEY(s_type,shift) EZK_ACTIVE_KEY(a_type,altgr)

const char *ezk_ckey_names[] = {
    "NULL",
    EZK_CKEYS_XMACRO
};

#undef EZK_CKEY_XM
#define EZK_CKEY_XM(base, shift, s_type, s_name, altgr, a_type, a_name) {EZK_ACTIVE_KEY(s_type,shift), EZK_ACTIVE_KEY(a_type,altgr)},

#undef EZK_ACTIVE_0
#undef EZK_ACTIVE_1

#define EZK_ACTIVE_1(name) EZK_CKEY_##name
#define EZK_ACTIVE_0(name) 0 // set it explicitly to 0 to stop the lookup table being jagged

// complex keys lookup table

// first is shift key, then altgr if it exists
static const ezk_ckey ckey_lookup[EZK_KEY_COUNT + 1][2] = {
    {0, 0}, // for null key
    EZK_CKEYS_XMACRO
};

#undef EZK_ACTIVE_KEY
#undef EZK_ACTIVE_1
#undef EZK_ACTIVE_0

ezk_ckey ezk_get_ckey_from_base(ezk_key base, ezk_mod_key mods) {
  if (!(altgr_down(mods) || shift_down(mods))) {
    return EZK_CKEY_NULL;
  }
  return ckey_lookup[base][altgr_down(mods) ? 1 : 0]; // NEEDS WORK: what if shift and altgr are down at the same time? 
}

// Note these are hardware values, so a layout can be applied later

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

#define EZK_X11_KEY_LT_LENGTH 136 // needs to be updated if more keys are added

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

ezk_key ezk_key_ezk_to_x11(int keycode) {
  if (keycode < 0 || keycode >= EZK_X11_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return ezk_x11_lt[keycode];
}


ezk_key ezk_key_x11_to_ezk(int keycode) {
  if (keycode < 0 || keycode >= EZK_X11_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return x11_ezk_lt[keycode];
}

#ifdef EZK_WINDOWS
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

#define EZK_WIN32_KEY_LT_LENGTH 253 // needs to be updated if more keys are added

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

ezk_key ezk_key_ezk_to_win32(int keycode)  {
  if (keycode < 0 || keycode >= EZK_WIN32_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return ezk_win32_lt[keycode];
}

ezk_key ezk_key_win32_to_ezk(int keycode)  {
  if (keycode < 0 || keycode >= EZK_WIN32_KEY_LT_LENGTH) return EZK_KEY_NULL;
  return win32_ezk_lt[keycode];
}

#endif
