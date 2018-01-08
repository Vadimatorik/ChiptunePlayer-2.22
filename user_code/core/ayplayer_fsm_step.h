#pragma once

#include "core_fsm.h"

int init_gui						( const fsm_step* previous_step );
int dp_init							( const fsm_step* previous_step );
int fat_init						( const fsm_step* previous_step );
int waiting_for_food_stabilization	( const fsm_step* previous_step );
int sd2_chack 						( const fsm_step* previous_step );
int sd2_track_file_open				( const fsm_step* previous_step );
