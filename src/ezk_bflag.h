#ifndef EZK_BFLAG_INCL
#define EZK_BFLAG_INCL

#include "ezk_api.h"
#include "ezk_primitives.h"

// Define EZK_BFLAG_NO_BOUNDS_CHECK before including this file to bypass
// the check ensuring the bit index is in bounds. Can improve performance,
// but leads to undefined behaviour if the limits are surpassed.
#ifndef EZK_BFLAG_NO_BOUNDS_CHECK
#define EZK_BFLAG_CHECK_BOUNDS(n, action) if(bit >= n) action
#else 
#define EZK_BFLAG_CHECK_BOUNDS(n, action)
#endif

#define EZK_BFLAG_WIDTHS \
  EZK_BFLAG_XMACRO(8)    \
  EZK_BFLAG_XMACRO(16)   \
  EZK_BFLAG_XMACRO(32)   \
  EZK_BFLAG_XMACRO(64)   

#define EZK_BFLAG_XMACRO(n) typedef ezk_u##n ezk_bflag##n;

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

/*
 * Gets bit `bit` of the passed bflag of n bits, from 0 to (n-1), where 0 is the LSB.
 * Any number higher than (n-1) or lower than 0 will simply return false.
 */

#define EZK_BFLAG_XMACRO(n) \
EZKAPI inline ezk_bool ezk_bflag##n##_get(ezk_bflag##n bflag, ezk_u8 bit) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return 0); \
  return ((bflag >> bit) & 0x1); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO


/*
 * Sets bit `bit` of the passed bflag of n bits to v. Bit 0 is the LSB.
 * Any number higher than (n-1) or lower than 0 will result in no changes.
*/

#define EZK_BFLAG_XMACRO(n) \
EZKAPI inline void ezk_bflag##n##_set(ezk_bflag##n *bflag, ezk_u8 bit, ezk_bool v) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return); \
  *bflag = (*bflag & ~((ezk_bflag##n)1 << bit)) | ((ezk_bflag##n)v << bit); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

/*
 * Flips bit `bit` of the passed bflag of n bits. Bit 0 is the LSB.
 * Any number higher than (n-1) or lower than 0 will result in no changes.
*/

#define EZK_BFLAG_XMACRO(n) \
EZKAPI inline void ezk_bflag##n##_flip(ezk_bflag##n bflag, ezk_u8 bit) { \
  EZK_BFLAG_CHECK_BOUNDS(n,return); \
  *bflag ^= ((ezk_bflag##n)1 << bit); \
}

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

/*
 * Checks if every bit is set to 1 in the flag. To check if every bit is 0,
 * simply compare the flag to 0.
*/

#define EZK_BFLAG_XMACRO(n) \
EZKAPI inline ezk_bool ezk_bflag##n##_all(ezk_bflag##n bflag) { \
  return bflag == ~(ezk_bflag##n)0; \
} // compares to a bflag with all bits set to 1 for type of length n.

EZK_BFLAG_WIDTHS
#undef EZK_BFLAG_XMACRO

#undef EZK_BFLAG_CHECK_BOUNDS // no reasonable use to anywhere else

#endif //EZK_BFLAG_INCL
