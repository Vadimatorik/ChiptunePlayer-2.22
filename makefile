PROJECT_NAME	:= ay_player

#**********************************************************************
# Параметры сборки проекта.
#**********************************************************************
MODULE_FREE_RTOS_OPTIMIZATION						:= -g3 -O0
MODULE_FAT_FS_OPTIMIZATION							:= -g3 -O0 
MODULE_STM32_F2_API_OPTIMIZATION					:= -g3 -O0 
MODULE_BUT_OPTIMIZATION								:= -g3 -O0 
MODULE_MOD_CHIP_OPTIMIZATION						:= -g3 -O0
MODULE_MAKISE_GUI_OPTIMIZATION						:= -g3 -O0 
MODULE_MATH_OPTIMIZATION							:= -g3 -O0 
MODULE_MICRO_SD_DRIVER_OPTIMIZATION					:= -g3 -O0 
MODULE_LCD_LIB_OPTIMIZATION							:= -g3 -O0 
MODULE_RUN_TIME_LOGGER_OPTIMIZATION					:= -g3 -O0 
MODULE_SH_OPTIMIZATION								:= -g3 -O0
MODULE_SYSTEM_DUMMY_OPTIMIZATION					:= -g3 -O0
MODULE_USER_CODE_OPTIMIZATION						:= -g3 -O0

DEFINE_PROJ	:= -DSTM32F205xx

LD_FILES = -T module_stm32f2_low_level_by_st/LD/STM32F205xG.ld

MK_FLAGS									:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft --specs=nano.specs

C_FLAGS										:= $(MK_FLAGS) 
# Все предупреждения == ошибки.
#C_FLAGS			+= -Werror
# Выдавать предупреждения (ошибки) о сомнительных констукциях.
#C_FLAGS			+= -Wall
# Выдавать предупреждение (ошибку) о любых сомнительных действиях.
#C_FLAGS			+= -Wextra 
C_FLAGS										+= -std=c99 
# Если переменная объявлена как enum, то она должна иметь возможность
# хранить в себе всевозможные состояния этого enum-а (а не только текущее).
C_FLAGS										+= -fshort-enums

CPP_FLAGS									:= $(MK_FLAGS)     
CPP_FLAGS									+= -Werror -Wall -Wextra
CPP_FLAGS									+= -std=c++14
CPP_FLAGS									+= -fno-exceptions

LDFLAGS			:= $(MK_FLAGS) $(LD_FILES) -fno-exceptions

# Размещает каждую функцию в отдельной секции.
LDFLAGS			+= -ffunction-sections -Wl,--gc-sections

# Формируем map файл.
LDFLAGS			+= -Wl,-Map="build/$(PROJECT_NAME).map"

#**********************************************************************
# Параметры toolchain-а.
#**********************************************************************
TOOLCHAIN_PATH	= arm-none-eabi

CC				= $(TOOLCHAIN_PATH)-gcc
CPP				= $(TOOLCHAIN_PATH)-g++
CCDEP			= $(TOOLCHAIN_PATH)-gcc
LD				= $(TOOLCHAIN_PATH)-g++
AR				= $(TOOLCHAIN_PATH)-ar
AS				= $(TOOLCHAIN_PATH)-gcc
OBJCOPY			= $(TOOLCHAIN_PATH)-objcopy
OBJDUMP			= $(TOOLCHAIN_PATH)-objdump
GDB				= $(TOOLCHAIN_PATH)-gdb
SIZE			= $(TOOLCHAIN_PATH)-size

PL				= plantuml_to_fsm_tree_generator/build/plantuml_to_fsm_tree_generator

# Все субмодули пишут в эти переменные.
PROJECT_OBJ_FILE 	:=
PROJECT_PATH		:=

#**********************************************************************
# Конфигурация проекта пользователя.
#**********************************************************************
# Все файлы из папки cfg в каталоге проекта.
USER_CFG_H_FILE		:= $(wildcard cfg/*.h)
USER_CFG_DIR		:= cfg
USER_CFG_PATH		:= -I$(USER_CFG_DIR)

PROJECT_PATH		+= $(USER_CFG_PATH)

# В эту переменную инклуды запишет module_stm32f2_low_level_by_st. 
# Так же ее использует module_system_dummy затем.
PATH_USER_MC_LOW_LAVEL	:=

include module_run_time_logger/makefile
include module_fsm/makefile
include module_button/makefile
include module_chiptune/makefile
include module_digital_potentiometer/makefile
include module_fatfs_by_chan/makefile
include module_makise_gui/makefile
include module_math/makefile
include module_mc_hardware_interfaces/makefile
include	module_microsd_low_level_driver/makefile
include	module_shift_register/makefile
include	module_stm32f2_low_level_by_st/makefile
include module_freertos_for_stm32f2/makefile
include module_mono_lcd_lib/makefile
include module_system_dummy/makefile 

#**********************************************************************
# Сборка кода пользователя.
# Весь код пользователя должен быть в корневой папке.
#**********************************************************************
USER_H_FILE				:= $(shell find user_code/ -maxdepth 5 -type f -name "*.h" )
USER_CPP_FILE			:= $(shell find user_code/ -maxdepth 5 -type f -name "*.cpp" )
USER_C_FILE				:= $(shell find user_code/ -maxdepth 5 -type f -name "*.c" )
USER_DIR				:= $(shell find user_code/ -maxdepth 5 -type d -name "*" )
USER_PATH				:= $(addprefix -I, $(USER_DIR))
USER_OBJ_FILE			:= $(addprefix build/obj/, $(USER_CPP_FILE))
USER_OBJ_FILE			+= $(addprefix build/obj/, $(USER_C_FILE))
USER_OBJ_FILE			:= $(patsubst %.cpp, %.o, $(USER_OBJ_FILE))
USER_OBJ_FILE			:= $(patsubst %.c, %.o, $(USER_OBJ_FILE))

PROJECT_PATH			+= $(USER_PATH)
PROJECT_OBJ_FILE		+= $(USER_OBJ_FILE)

FSM_PU_FILE				= $(shell find user_code/ -maxdepth 5 -type f -name "*.pu" )
FSM_CPP_FILE			+= $(patsubst %.pu, %.cpp, $(FSM_PU_FILE))
FSM_OBJ_FILE			+= $(patsubst %.pu, build/obj/%.o, $(FSM_PU_FILE))

PROJECT_PATH			+= -Ifsm_build/
PROJECT_OBJ_FILE		+= $(FSM_OBJ_FILE)

%.cpp:	%.pu
	@echo [PL] $<
	@$(PL) $< $@ ay_player_class ayplayer.h

build/obj/%.o:	%.c	
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) 					\
	$(DEFINE_PROJ)						\
	$(PROJECT_PATH)						\
	$(MODULE_USER_CODE_OPTIMIZATION)	\
	-c $< -o $@
	
build/obj/%.o:	%.cpp	
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) 				\
	$(DEFINE_PROJ)						\
	$(MODULE_USER_CODE_OPTIMIZATION)	\
	$(PROJECT_PATH)						\
	-c $< -o $@

build/$(PROJECT_NAME).elf:	$(PROJECT_OBJ_FILE)
	@$(LD) $(LDFLAGS) $(PROJECT_OBJ_FILE)  -o build/$(PROJECT_NAME).elf
	@echo ' '
	@echo 'Finished building target: $@'
	@echo ' '

$(PROJECT_NAME).siz:	build/$(PROJECT_NAME).elf
	@echo 'Print Size:'
	@arm-none-eabi-size --format=berkeley "build/$(PROJECT_NAME).elf"
	@echo ' '

all:	$(PROJECT_NAME).siz
#@$(OBJDUMP) -D build/$(PROJECT_NAME).elf > build/$(PROJECT_NAME).asm
#@$(OBJCOPY) build/$(PROJECT_NAME).elf build/$(PROJECT_NAME).bin -O binary
	
pfsm_build:	
	mkdir -p plantuml_to_fsm_tree_generator/build
	cd plantuml_to_fsm_tree_generator/build && qmake -qt=qt5 .. && make

pfsm_clean:
	cd plantuml_to_fsm_tree_generator/ && rm -R build

pfsm_rebuild:
	cd plantuml_to_fsm_tree_generator/ && rm -R build
	mkdir plantuml_to_fsm_tree_generator/build
	cd plantuml_to_fsm_tree_generator/build && qmake -qt=qt5 .. && make

clean:	
	@rm -R ./build
	@echo 'Project cline!'
	@echo ' '
