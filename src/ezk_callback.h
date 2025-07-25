#ifndef EZK_CB_INCL
#define EZK_CB_INCL

#include "ezk_primitives.h"

#define EZK_CALLBACK(name, ret, ...)  ret (*name)(__VA_ARGS__)

#define EZK_CALLBACK_TYPEDEF(name, ret, ...) typedef EZK_CALLBACK(name,ret,__VA_ARGS__)

// random typedefs that are never used in the library but that i assume will be useful somewhere?
// yes please

EZK_CALLBACK_TYPEDEF(ezk_void_callback, void);

EZK_CALLBACK_TYPEDEF(ezk_bool_callback, ezk_bool);

EZK_CALLBACK_TYPEDEF(ezk_u8_callback, ezk_u8);
EZK_CALLBACK_TYPEDEF(ezk_u16_callback, ezk_u16);
EZK_CALLBACK_TYPEDEF(ezk_u32_callback, ezk_u32);
EZK_CALLBACK_TYPEDEF(ezk_u64_callback, ezk_u64);

EZK_CALLBACK_TYPEDEF(ezk_i8_callback, ezk_i8);
EZK_CALLBACK_TYPEDEF(ezk_i16_callback, ezk_i16);
EZK_CALLBACK_TYPEDEF(ezk_i32_callback, ezk_i32);
EZK_CALLBACK_TYPEDEF(ezk_i64_callback, ezk_i64);

EZK_CALLBACK_TYPEDEF(ezk_f32_callback, ezk_f32);
EZK_CALLBACK_TYPEDEF(ezk_f64_callback, ezk_f64);

EZK_CALLBACK_TYPEDEF(ezk_byte_callback, ezk_byte);
EZK_CALLBACK_TYPEDEF(ezk_string_callback, ezk_string);

EZK_CALLBACK_TYPEDEF(ezk_v2_callback, ezk_v2);
EZK_CALLBACK_TYPEDEF(ezk_v3_callback, ezk_v3);
EZK_CALLBACK_TYPEDEF(ezk_v4_callback, ezk_v4);

EZK_CALLBACK_TYPEDEF(ezk_v2i_callback, ezk_v2i);
EZK_CALLBACK_TYPEDEF(ezk_v3i_callback, ezk_v3i);
EZK_CALLBACK_TYPEDEF(ezk_v4i_callback, ezk_v4i);

EZK_CALLBACK_TYPEDEF(ezk_time_callback, ezk_time);

#endif // EZK_CB_INCL
