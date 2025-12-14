#ifndef EZK_WINDOW_INT_INCL
#define EZK_WINDOW_INT_INCL

#include "ezk_window.h"

void ezk_internal_update_state_flags(ezk_win_id id, ezk_bflag8 state_flags);

void ezk_internal_set_dims(ezk_win_id id, ezk_v2i dims);
void ezk_internal_set_pos(ezk_win_id id, ezk_v2i pos);
void ezk_internal_set_name(ezk_win_id id, ezk_string name);

void ezk_internal_create_window(ezk_win_id id, ezk_win_desc desc);
void ezk_internal_close_window(ezk_win_id id);

ezk_event *ezk_internal_update_evqueue(ezk_win_id id, ezk_u32 *eq_size);

#endif
