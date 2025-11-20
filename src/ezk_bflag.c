#include "ezk_bflag.h"


// Define EZK_BFLAG_NO_BOUNDS_CHECK when compiling this file to bypass
// the check ensuring the bit index is in bounds. Can improve performance,
// but leads to undefined behaviour if the limits are surpassed.
#ifndef EZK_BFLAG_NO_BOUNDS_CHECK
#define EZK_BFLAG_CHECK_BOUNDS(n, action) if(bit >= n) action
#else 
#define EZK_BFLAG_CHECK_BOUNDS(n, action)
#endif

#define EZK_BFLAG_XMACRO(n) \
EZKAPI ezk_bool ezk_bflag##n##_get(ezk_bflag##n bflag, ezk_u8 bit) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return 0); \
  return ((bflag >> bit) & 0x1); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

#define EZK_BFLAG_XMACRO(n) \
EZKAPI void ezk_bflag##n##_set(ezk_bflag##n *bflag, ezk_u8 bit, ezk_bool v) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return); \
  *bflag = (*bflag & ~((ezk_bflag##n)1 << bit)) | ((ezk_bflag##n)v << bit); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

#define EZK_BFLAG_XMACRO(n) \
EZKAPI void ezk_bflag##n##_flip(ezk_bflag##n *bflag, ezk_u8 bit) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return); \
  *bflag ^= ((ezk_bflag##n)1 << bit); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

#define EZK_BFLAG_XMACRO(n) \
EZKAPI ezk_bool ezk_bflag##n##_all(ezk_bflag##n bflag) { \
  return bflag == ~(ezk_bflag##n)0; \
} // compares to a bflag with all bits set to 1 for type of length n.

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

#undef EZK_BFLAG_CHECK_BOUNDS // no reasonable use to anywhere else
