#pragma once

#include "core_fsm.h"

bool init_gui						( const fsm_step* previous_step );
bool dp_init						( const fsm_step* previous_step );
bool fat_init						( const fsm_step* previous_step );
bool waiting_for_food_stabilization ( const fsm_step* previous_step );
bool sd2_connect 					( const fsm_step* previous_step );
