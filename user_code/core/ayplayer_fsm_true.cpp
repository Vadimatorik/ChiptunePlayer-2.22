#include "ayplayer_fsm_step.h"
#include "core_fsm.h"

/*
extern const fsm_step step_gui_init;
extern const fsm_step step_dp_init;
extern const fsm_step step_fat_init;
extern const fsm_step step_waiting_for_food_stabilization;
extern const fsm_step step_sd2_chack;
extern const fsm_step step_sd2_track_file_open;

const fsm_step* gui_init_next_step_array[1] = { &step_dp_init };
const fsm_step step_gui_init = {
	.func_step				= &init_gui,
	.next_step_array		= gui_init_next_step_array,
	.number_array			= 1,
};

const fsm_step* dp_init_next_step_array[1] = { &step_fat_init };
const fsm_step step_dp_init = {
	.func_step				= &dp_init,
	.next_step_array		= dp_init_next_step_array,
	.number_array			= 1
};

const fsm_step* fat_init_next_step_array[1] = { &step_waiting_for_food_stabilization };
const fsm_step step_fat_init = {
	.func_step				= &fat_init,
	.next_step_array		= fat_init_next_step_array,
	.number_array			= 1
};

const fsm_step* step_waiting_for_food_stabilization_next_step_array[1] = { &step_sd2_chack };
const fsm_step step_waiting_for_food_stabilization = {
	.func_step				= &waiting_for_food_stabilization,
	.next_step_array		= step_waiting_for_food_stabilization_next_step_array,
	.number_array			= 1
};

const fsm_step* step_sd2_chack_next_step_array[1] = { &step_sd2_track_file_open };
const fsm_step step_sd2_chack = {
	.func_step				= &sd2_chack,
	.next_step_array		= step_sd2_chack_next_step_array,
    .number_array			= 1
};

const fsm_step* sd2_track_file_open_next_step_array[3] = { nullptr, nullptr, &step_sd2_chack };

const fsm_step step_sd2_track_file_open = {
	.func_step				= &sd2_track_file_open,
	.next_step_array		= sd2_track_file_open_next_step_array,
	.number_array			= 3,
};


*/
