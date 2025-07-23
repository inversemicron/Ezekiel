#ifndef EZK_PRIMS_INCL
#define EZK_PRIMS_INCL

//typedef enum {
//    false = 0,
//    true = 1
//} ezk_bool;

typedef bool ezk_bool;

typedef unsigned char ezk_u8;
typedef unsigned short int ezk_u16;
typedef unsigned int ezk_u32;
typedef unsigned long int ezk_u64;

typedef char ezk_i8;
typedef short int ezk_i16;
typedef int ezk_i32;
typedef long int ezk_i64;

typedef float ezk_f32;
typedef double ezk_f64;

typedef char ezk_byte;
typedef char* ezk_string;

typedef struct {ezk_f32 x,y;} ezk_v2;
typedef struct {ezk_f32 x,y,z;} ezk_v3;
typedef struct {ezk_f32 x,y,z,w;} ezk_v4;

typedef struct {ezk_i32 x,y;} ezk_v2_i;
typedef struct {ezk_i32 x,y,z;} ezk_v3_i;
typedef struct {ezk_i32 x,y,z,w;} ezk_v4_i;

typedef struct {
    ezk_u64 seconds; // since the epoch
    ezk_u32 nanoseconds; // since the last second
} ezk_time;

#define EZK_CALLBACK(name, ret, ...)  ret (*name)(__VA_ARGS__)

#endif
