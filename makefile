PROJECT_NAME	:= ay_player

#**********************************************************************
# Параметры сборки проекта.
#**********************************************************************
FREE_RTOS_OPTIMIZATION			:= -g3 -Og
STM32_F2_API_OPTIMIZATION		:= -g3 -Og
USER_CODE_OPTIMIZATION			:= -g3 -Og
LCD_LIB_OPTIMIZATION			:= -g3 -Og
SIMPLE_MONO_DRAWING_LIB_OPTIMIZATION	:= -g3 -Og
MINI_GUI_BY_VADIMATORIK_OPTIMIZATION	:= -g3 -Og
MICRO_SD_DRIVER_OPTIMIZATION		:= -g3 -Og
SH_OPTIMIZATION				:= -g3 -Og
MOD_CHIP_OPTIMIZATION			:= -g3 -Og
FAT_FS_OPTIMIZATION			:= -g3 -Og

LD_FILES = -T stm32f2_api/ld/stm32f205xB_mem.ld -T stm32f2_api/ld/stm32f2_section.ld

MK_FLAGS		:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

C_FLAGS			:= $(MK_FLAGS)
# Все предупреждения == ошибки.
C_FLAGS			+= -Werror
# Выдавать предупреждения (ошибки) о сомнительных констукциях.
C_FLAGS			+= -Wall
# Выдавать предупреждение (ошибку) о любых сомнительных действиях.
C_FLAGS			+= -Wextra 
C_FLAGS			+= -std=gnu99 
# Если переменная объявлена как enum, то она должна иметь возможность
# хранить в себе всевозможные состояния этого enum-а (а не только текущее).
C_FLAGS			+= -fshort-enums
# Развертывание циклов.
C_FLAGS			+= -funroll-loops

C_FAT_FS_FLAGS		:= $(MK_FLAGS) -std=gnu89

CPP_FLAGS		:= $(MK_FLAGS)     
CPP_FLAGS		+= -Werror -Wall -Wextra
CPP_FLAGS		+= -std=c++1z
CPP_FLAGS		+= -funroll-loops

LDFLAGS			:= $(MK_FLAGS)
LDFLAGS			+= $(LD_FILES)
LDFLAGS			+= -Werror -Wall -Wextra 
# Размещает каждую функцию в отдельной секции.
LDFLAGS			+= -ffunction-sections -fdata-sections
# Убираем неиспользуемые функции из .elf.
LDFLAGS			+= -Wl,--gc-sections
# Формируем map файл.
#LDFLAGS			+= -Wl,-Map="build/$(PROJECT_NAME).map"

#**********************************************************************
# Параметры toolchain-а.
#**********************************************************************
TOOLCHAIN_PATH	= arm-none-eabi

CC	= $(TOOLCHAIN_PATH)-gcc
CPP	= $(TOOLCHAIN_PATH)-g++
CCDEP	= $(TOOLCHAIN_PATH)-gcc
LD	= $(TOOLCHAIN_PATH)-g++
AR	= $(TOOLCHAIN_PATH)-ar
AS	= $(TOOLCHAIN_PATH)-gcc
OBJCOPY	= $(TOOLCHAIN_PATH)-objcopy
OBJDUMP	= $(TOOLCHAIN_PATH)-objdump
GDB	= $(TOOLCHAIN_PATH)-gdb
SIZE	= $(TOOLCHAIN_PATH)-size

#**********************************************************************
# Конфигурация проекта пользователя.
#**********************************************************************
# Все файлы из папки cfg в каталоге проекта.
USER_CFG_H_FILE		:= $(wildcard cfg/*.h)
USER_CFG_DIR		:= cfg
USER_CFG_PATH		:= -I$(USER_CFG_DIR)

#**********************************************************************
# Интерфейсы микроконтроллера.
#**********************************************************************
# Все файлы из папки cfg в каталоге проекта.
MK_INTER_H_FILE		:= $(wildcard mk_hardware_interfaces/*.h)
MK_INTER_DIR		:= mk_hardware_interfaces
MK_INTER_PATH		:= -I$(MK_INTER_DIR)

#**********************************************************************
# Для сборки FreeRTOS.
#**********************************************************************
# Собираем все необходимые .h файлы FreeRTOS.
# FreeRTOS.h должен обязательно идти первым! 
FREE_RTOS_H_FILE	:= FreeRTOS_for_stm32f2/FreeRTOS.h
FREE_RTOS_H_FILE	+= $(wildcard FreeRTOS_for_stm32f2/include/*.h)

# Директории, в которых лежат файлы FreeRTOS.
FREE_RTOS_DIR		:= FreeRTOS_for_stm32f2
FREE_RTOS_DIR		+= FreeRTOS_for_stm32f2/include

# Подставляем перед каждым путем директории префикс -I.
FREE_RTOS_PATH		:= $(addprefix -I, $(FREE_RTOS_DIR))

# Получаем список .c файлов ( путь + файл.c ).
FREE_RTOS_C_FILE	:= $(wildcard FreeRTOS_for_stm32f2/*.c)

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
FREE_RTOS_OBJ_FILE	:= $(addprefix build/obj/, $(FREE_RTOS_C_FILE))
# Затем меняем у всех .c на .o.
FREE_RTOS_OBJ_FILE	:= $(patsubst %.c, %.o, $(FREE_RTOS_OBJ_FILE))

FREE_RTOS_INCLUDE_FILE	:= -include"./FreeRTOS_for_stm32f2/include/StackMacros.h"
# Сборка FreeRTOS.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/FreeRTOS_for_stm32f2/%.o:	FreeRTOS_for_stm32f2/%.c 
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(FREE_RTOS_INCLUDE_FILE) -c $< -o $@

	
#**********************************************************************
# Для сборки FatFS.
#**********************************************************************
FAT_FS_H_FILE	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type f -name "*.h" )
FAT_FS_CPP_FILE	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type f -name "*.c" )
FAT_FS_DIR	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type d -name "*" )
FAT_FS_PATH	:= $(addprefix -I, $(FAT_FS_DIR))
FAT_FS_OBJ_FILE	:= $(addprefix build/obj/, $(FAT_FS_CPP_FILE))
FAT_FS_OBJ_FILE	:= $(patsubst %.c, %.o, $(FAT_FS_OBJ_FILE))
build/obj/module_fat_fs_by_chan/%.o:	module_fat_fs_by_chan/%.c $(USER_CFG_H_FILE)
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FAT_FS_FLAGS) $(FAT_FS_PATH) $(USER_CFG_PATH) $(FAT_FS_OPTIMIZATION) -c $< -o $@
	
#**********************************************************************
# Для сборки stm32f2_api.
#**********************************************************************
STM32_F2_API_H_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.h" )
STM32_F2_API_CPP_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.cpp" )
STM32_F2_API_DIR	:= $(shell find stm32f2_api/ -maxdepth 3 -type d -name "*" )
STM32_F2_API_PATH	:= $(addprefix -I, $(STM32_F2_API_DIR))
STM32_F2_API_OBJ_FILE	:= $(addprefix build/obj/, $(STM32_F2_API_CPP_FILE))
STM32_F2_API_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(STM32_F2_API_OBJ_FILE))
build/obj/stm32f2_api/%.o:	stm32f2_api/%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE) $(MK_INTER_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(STM32_F2_API_PATH) $(USER_CFG_PATH) $(FREE_RTOS_PATH) $(STM32_F2_API_OPTIMIZATION) $(MK_INTER_PATH) -c $< -o $@

#**********************************************************************
# Для сборки библиотеки LCD драйверов (mono_lcd_lib).
#**********************************************************************
LCD_LIB_H_FILE		:= $(shell find mono_lcd_lib/ -maxdepth 3 -type f -name "*.h" )
LCD_LIB_CPP_FILE	:= $(shell find mono_lcd_lib/ -maxdepth 3 -type f -name "*.cpp" )
LCD_LIB_DIR		:= $(shell find mono_lcd_lib/ -maxdepth 3 -type d -name "*" )
LCD_LIB_PATH		:= $(addprefix -I, $(LCD_LIB_DIR))
LCD_LIB_OBJ_FILE	:= $(addprefix build/obj/, $(LCD_LIB_CPP_FILE))
LCD_LIB_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(LCD_LIB_OBJ_FILE))
build/obj/mono_lcd_lib/%.o:	mono_lcd_lib/%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE) $(MK_INTER_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(LCD_LIB_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(LCD_LIB_OPTIMIZATION) $(MK_INTER_PATH) -c $< -o $@

#**********************************************************************
# Для сборки библиотеки рисования приметивов (simple_mono_drawing_lib).
#**********************************************************************
SIMPLE_MONO_DRAWING_LIB_H_FILE		:= $(shell find simple_mono_drawing_lib/ -maxdepth 3 -type f -name "*.h" )
SIMPLE_MONO_DRAWING_LIB_CPP_FILE	:= $(shell find simple_mono_drawing_lib/ -maxdepth 3 -type f -name "*.cpp" )
SIMPLE_MONO_DRAWING_LIB_DIR		:= $(shell find simple_mono_drawing_lib/ -maxdepth 3 -type d -name "*" )
SIMPLE_MONO_DRAWING_LIB_PATH		:= $(addprefix -I, $(SIMPLE_MONO_DRAWING_LIB_DIR))
SIMPLE_MONO_DRAWING_LIB_OBJ_FILE	:= $(addprefix build/obj/, $(SIMPLE_MONO_DRAWING_LIB_CPP_FILE))
SIMPLE_MONO_DRAWING_LIB_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(SIMPLE_MONO_DRAWING_LIB_OBJ_FILE))
build/obj/simple_mono_drawing_lib/%.o:	simple_mono_drawing_lib/%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(SIMPLE_MONO_DRAWING_LIB_PATH) $(LCD_LIB_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(SIMPLE_MONO_DRAWING_LIB_OPTIMIZATION) -c $< -o $@

#**********************************************************************
# Для сборки библиотеки GUI объектов (mini_gui_by_vadimatorik)
#**********************************************************************
MINI_GUI_BY_VADIMATORIK_H_FILE		:= $(shell find mini_gui_by_vadimatorik/ -maxdepth 3 -type f -name "*.h" )
MINI_GUI_BY_VADIMATORIK_CPP_FILE	:= $(shell find mini_gui_by_vadimatorik/ -maxdepth 3 -type f -name "*.cpp" )
MINI_GUI_BY_VADIMATORIK_DIR		:= $(shell find mini_gui_by_vadimatorik/ -maxdepth 3 -type d -name "*" )
MINI_GUI_BY_VADIMATORIK_PATH		:= $(addprefix -I, $(MINI_GUI_BY_VADIMATORIK_DIR))
MINI_GUI_BY_VADIMATORIK_OBJ_FILE	:= $(addprefix build/obj/, $(MINI_GUI_BY_VADIMATORIK_CPP_FILE))
MINI_GUI_BY_VADIMATORIK_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(MINI_GUI_BY_VADIMATORIK_OBJ_FILE))
build/obj/mini_gui_by_vadimatorik/%.o:	mini_gui_by_vadimatorik/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(MINI_GUI_BY_VADIMATORIK_PATH) $(USER_CFG_PATH) $(SIMPLE_MONO_DRAWING_LIB_PATH) $(MINI_GUI_BY_VADIMATORIK_OPTIMIZATION) -c $< -o $@
	
#**********************************************************************
# Драйвер SD карты (micro_sd_driver_by_vadimatorik).
#**********************************************************************
MICRO_SD_DRIVER_H_FILE		:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type f -name "*.h" )
MICRO_SD_DRIVER_CPP_FILE	:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type f -name "*.cpp" )
MICRO_SD_DRIVER_DIR		:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type d -name "*" )
MICRO_SD_DRIVER_PATH		:= $(addprefix -I, $(MICRO_SD_DRIVER_DIR))
MICRO_SD_DRIVER_OBJ_FILE	:= $(addprefix build/obj/, $(MICRO_SD_DRIVER_CPP_FILE))
MICRO_SD_DRIVER_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(MICRO_SD_DRIVER_OBJ_FILE))
build/obj/micro_sd_driver_by_vadimatorik/%.o:	micro_sd_driver_by_vadimatorik/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(MK_INTER_PATH) $(MICRO_SD_DRIVER_PATH) $(USER_CFG_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH)  $(MICRO_SD_DRIVER_OPTIMIZATION) -c $< -o $@
	
#**********************************************************************
# module_shift_register
#**********************************************************************
SH_H_FILE	:= $(shell find module_shift_register/ -maxdepth 3 -type f -name "*.h" )
SH_CPP_FILE	:= $(shell find module_shift_register/ -maxdepth 3 -type f -name "*.cpp" )
SH_DIR		:= $(shell find module_shift_register/ -maxdepth 3 -type d -name "*" )
SH_PATH		:= $(addprefix -I, $(SH_DIR))
SH_OBJ_FILE	:= $(addprefix build/obj/, $(SH_CPP_FILE))
SH_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(SH_OBJ_FILE))
build/obj/module_shift_register/%.o:	module_shift_register/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(MK_INTER_PATH) $(SH_PATH) $(USER_CFG_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH)  $(SH_OPTIMIZATION) -c $< -o $@

#**********************************************************************
# module_chiptune
#**********************************************************************
MOD_CHIP_H_FILE		:= $(shell find module_chiptune/ -maxdepth 3 -type f -name "*.h" )
MOD_CHIP_CPP_FILE	:= $(shell find module_chiptune/ -maxdepth 3 -type f -name "*.cpp" )
MOD_CHIP_DIR		:= $(shell find module_chiptune/ -maxdepth 3 -type d -name "*" )
MOD_CHIP_PATH		:= $(addprefix -I, $(MOD_CHIP_DIR))
MOD_CHIP_OBJ_FILE	:= $(addprefix build/obj/, $(MOD_CHIP_CPP_FILE))
MOD_CHIP_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(MOD_CHIP_OBJ_FILE))
build/obj/module_chiptune/%.o:	module_chiptune/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(MK_INTER_PATH) $(FAT_FS_PATH) $(MOD_CHIP_PATH) $(USER_CFG_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH) $(SH_PATH) $(MOD_CHIP_OPTIMIZATION) -c $< -o $@
	
#**********************************************************************
# module_digital_potentiometer (сделано на шаблонах, все .h).
#**********************************************************************
DP_H_FILE	:= $(shell find module_digital_potentiometer/ -maxdepth 3 -type f -name "*.h" )
DP_DIR		:= $(shell find module_digital_potentiometer/ -maxdepth 3 -type d -name "*" )
DP_PATH		:= $(addprefix -I, $(DP_DIR))
	
#**********************************************************************
# Сборка кода пользователя.
# Весь код пользователя должен быть в корневой папке.
#**********************************************************************
USER_H_FILE		:= $(shell find user_code/ -maxdepth 5 -type f -name "*.h" )
USER_CPP_FILE		:= $(shell find user_code/ -maxdepth 5 -type f -name "*.cpp" )
USER_DIR		:= $(shell find user_code/ -maxdepth 5 -type d -name "*" )
USER_PATH		:= $(addprefix -I, $(USER_DIR))
USER_OBJ_FILE		:= $(addprefix build/obj/, $(USER_CPP_FILE))
USER_OBJ_FILE		:= $(patsubst %.cpp, %.o, $(USER_OBJ_FILE))
build/obj/%.o:	%.cpp	
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) 						\
	$(USER_PATH) $(FAT_FS_PATH) $(MK_INTER_PATH)  			\
	$(STM32_F2_API_PATH) $(USER_CFG_PATH) $(FREE_RTOS_PATH) 	\
	$(LCD_LIB_PATH) $(SIMPLE_MONO_DRAWING_LIB_PATH) 		\
	$(MINI_GUI_BY_VADIMATORIK_PATH) $(MICRO_SD_DRIVER_PATH) 	\
	$(SH_PATH) $(MOD_CHIP_PATH) $(DP_PATH)				\
	 $(USER_CODE_OPTIMIZATION) -c $< -o $@

#**********************************************************************
# Компановка проекта.
#**********************************************************************
PROJECT_OBJ_FILE	:= 	$(FAT_FS_OBJ_FILE) $(FREE_RTOS_OBJ_FILE) 	\
				$(STM32_F2_API_OBJ_FILE) 			\
				$(LCD_LIB_OBJ_FILE) 				\
				$(SIMPLE_MONO_DRAWING_LIB_OBJ_FILE) 		\
				$(MINI_GUI_BY_VADIMATORIK_OBJ_FILE) 		\
				$(USER_OBJ_FILE)				\
				$(MICRO_SD_DRIVER_OBJ_FILE) 			\
				$(SH_OBJ_FILE) 					\
				$(MOD_CHIP_OBJ_FILE)					

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
	
clean:	
	@rm -R ./build
	@echo 'Project cline!'
	@echo ' '
