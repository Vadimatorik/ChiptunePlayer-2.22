PROJECT_NAME		:= AyPlayer

DEFINE_PROJ			:=	-DSTM32F205xx -DSTM32F2 -DSTM32 -DDEBUG

DEFINE_PROJ			+=	-DMODULE_BUTTONS_THROUGH_SHIFT_REGISTER_ONE_INPUT_PIN_ENABLED

DEFINE_PROJ			+=	-DMODULE_AY_YM_FILE_PLAY_ENABLED
DEFINE_PROJ			+=	-DMODULE_AY_YM_LOW_LAVEL_ENABLED
#DEFINE_PROJ			+=	-DMODULE_AY_YM_NOTE_MODE_ENABLED

DEFINE_PROJ			+=	-DMODULE_DIGITAL_POTENTIOMETER_ENABLED

DEFINE_PROJ			+=	-DMODULE_FSM_ENABLED
DEFINE_PROJ			+=	-DMODULE_ARITHMETIC_MEAN_ENABLED
DEFINE_PROJ			+=	-DMODULE_MICROSD_CARD_SDIO_ENABLED
DEFINE_PROJ			+=	-DMODULE_MICROSD_CARD_SPI_ENABLED
DEFINE_PROJ			+=	-DMODULE_MONO_LCD_ST7565_ENABLED
DEFINE_PROJ			+=	-DMODULE_RUN_TIME_LOGGER_ENABLED
DEFINE_PROJ			+=	-DMODULE_SHIFT_REGISTER_ENABLED
DEFINE_PROJ			+=	-DMODULE_CPP_SYSTEM_CALLS_DUMMY_ENABLED

DEFINE_PROJ			+=	-DELEMENT_FSVIEWER_FATFS_ENABLED
DEFINE_PROJ			+=	-DELEMENT_PLAY_BAR_ENABLED
DEFINE_PROJ			+=	-DELEMENT_PLAY_LIST_ENABLED
DEFINE_PROJ			+=	-DELEMENT_PLAYER_STATUS_BAR_ENABLED
DEFINE_PROJ			+=	-DELEMENT_PROGRESS_BAR_ENABLED
DEFINE_PROJ			+=	-DELEMENT_SLIST_ENABLED
DEFINE_PROJ			+=	-DELEMENT_SCROLL_STRING_ENABLED
DEFINE_PROJ			+=	-DELEMENT_SLIM_HORIZONTAL_LIST_ENABLED

CODE_OPTIMIZATION	:=	-O0 -g3

LD_FILES			= -T submodule/module_stm32f2_low_level_by_st/ld/STM32F205xG.ld
STARTUPE_S_NAME		=  submodule/module_stm32f2_low_level_by_st/startupe/startup_stm32f205xx.s

MK_FLAGS			:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft --specs=nano.specs

C_FLAGS				:= $(MK_FLAGS) 
# Все предупреждения == ошибки.
#C_FLAGS			+= -Werror
# Выдавать предупреждения (ошибки) о сомнительных констукциях.
#C_FLAGS			+= -Wall
# Выдавать предупреждение (ошибку) о любых сомнительных действиях.
#C_FLAGS			+= -Wextra 
C_FLAGS				+= -std=c99 
# Если переменная объявлена как enum, то она должна иметь возможность
# хранить в себе всевозможные состояния этого enum-а (а не только текущее).
C_FLAGS				+= -fshort-enums

CPP_FLAGS			:= $(MK_FLAGS)     
CPP_FLAGS			+= -Werror -Wall -Wextra
CPP_FLAGS			+= -std=c++14
CPP_FLAGS			+= -fno-exceptions

LDFLAGS				:= $(MK_FLAGS) $(LD_FILES) -fno-exceptions

# FreeRTOS.
LDFLAGS				+= -Wl,--undefined=uxTopUsedPriority

# Размещает каждую функцию в отдельной секции.
LDFLAGS				+= -ffunction-sections -Wl,--gc-sections

# Формируем map файл.
#LDFLAGS			+= -Wl,-Map="build/$(PROJECT_NAME).map"

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
PROJ_CFG_H_FILE		:= $(wildcard cfg/*.h)
PROJ_CFG_DIR		:= cfg
PROJ_CFG_PATH		:= -I$(PROJ_CFG_DIR)

PROJECT_PATH		+= $(PROJ_CFG_PATH)

PROJ_H_FILE				:= $(shell find user_code/ -maxdepth 10 -type f -name "*.h" )
PROJ_H_FILE				+= $(shell find submodule/ -maxdepth 10 -type f -name "*.h" )

PROJ_CPP_FILE			:= $(shell find user_code/ -maxdepth 10 -type f -name "*.cpp" )
PROJ_CPP_FILE			+= $(shell find submodule/ -maxdepth 10 -type f -name "*.cpp" )

PROJ_C_FILE				:= $(shell find user_code/ -maxdepth 10 -type f -name "*.c" )
PROJ_C_FILE				+= $(shell find submodule/ -maxdepth 10 -type f -name "*.c" )

PROJ_S_FILE				= $(STARTUPE_S_NAME)

PROJ_DIR				:= $(shell find user_code/ -maxdepth 10 -type d -name "*" )
PROJ_DIR				+= $(shell find submodule/ -maxdepth 10 -type d -name "*" )

PROJ_PATH				:= $(addprefix -I, $(PROJ_DIR))
PROJ_OBJ_FILE			:= $(addprefix build/obj/, $(PROJ_CPP_FILE))
PROJ_OBJ_FILE			+= $(addprefix build/obj/, $(PROJ_C_FILE))
PROJ_OBJ_FILE			+= $(addprefix build/obj/, $(PROJ_S_FILE))

PROJ_OBJ_FILE			:= $(patsubst %.cpp, %.o, $(PROJ_OBJ_FILE))
PROJ_OBJ_FILE			:= $(patsubst %.c, %.o, $(PROJ_OBJ_FILE))
PROJ_OBJ_FILE			:= $(patsubst %.s, %.o, $(PROJ_OBJ_FILE))

PROJECT_PATH			+= $(PROJ_PATH)
PROJECT_OBJ_FILE		+= $(PROJ_OBJ_FILE)

FSM_PU_FILE				= $(shell find user_code/ -maxdepth 10 -type f -name "*.pu" )
FSM_CPP_FILE			+= $(patsubst %.pu, %.cpp, $(FSM_PU_FILE))
FSM_OBJ_FILE			+= $(patsubst %.pu, build/obj/%.o, $(FSM_PU_FILE))

PROJECT_PATH			+= -Ifsm_build/
PROJECT_OBJ_FILE		+= $(FSM_OBJ_FILE)

%.cpp:	%.pu
	@echo [PL] $<
	@$(PL) $< $@

build/obj/%.o:	%.s
	@echo [AS] $<
	@mkdir -p $(dir $@)
	@$(AS)								\
	$(DEFINE_PROJ)						\
	$(CODE_OPTIMIZATION)				\
	$(PROJECT_PATH)						\
	-c $< -o $@


build/obj/%.o:	%.c	
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) 					\
	$(DEFINE_PROJ)						\
	$(CODE_OPTIMIZATION)				\
	$(PROJECT_PATH)						\
	-c $< -o $@
	
build/obj/%.o:	%.cpp	
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) 				\
	$(DEFINE_PROJ)						\
	$(CODE_OPTIMIZATION)				\
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
	cd plantuml_to_fsm_tree_generator/build && qmake .. && make

pfsm_clean:
	cd plantuml_to_fsm_tree_generator/ && rm -R build

pfsm_rebuild:
	cd plantuml_to_fsm_tree_generator/ && rm -R build
	mkdir plantuml_to_fsm_tree_generator/build
	cd plantuml_to_fsm_tree_generator/build && qmake .. && make

clean:	
	@rm -R ./build
	@echo 'Project cline!'
	@echo ' '
