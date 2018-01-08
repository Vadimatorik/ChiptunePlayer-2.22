#include "ayplayer_fsm_step.h"
#include "core_fsm.h"

extern const fsm_step step_gui_init;
extern const fsm_step step_dp_init;
extern const fsm_step step_fat_init;
extern const fsm_step step_waiting_for_food_stabilization;
extern const fsm_step step_sd2_connect;

const fsm_step step_gui_init = {
	.func_step				= &init_gui,
	.number_step_true		= &step_dp_init,
	.number_step_false		= nullptr,
	.repeat_step			= 0
};

const fsm_step step_dp_init = {
	.func_step				= &dp_init,
	.number_step_true		= &step_fat_init,
	.number_step_false		= nullptr,
	.repeat_step			= 0
};

const fsm_step step_fat_init = {
	.func_step				= &fat_init,
	.number_step_true		= &step_waiting_for_food_stabilization,
	.number_step_false		= nullptr,
	.repeat_step			= 0
};

const fsm_step step_waiting_for_food_stabilization = {
	.func_step				= &waiting_for_food_stabilization,
	.number_step_true		= &step_sd2_connect,
	.number_step_false		= nullptr,
	.repeat_step			= 0
};

const fsm_step step_sd2_connect = {
	.func_step				= &sd2_connect,
	.number_step_true		= nullptr,
	.number_step_false		= nullptr,
	.repeat_step			= 0
};
