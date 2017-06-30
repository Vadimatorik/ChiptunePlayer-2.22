PROJECT_NAME	:= ay_player

#**********************************************************************
# Параметры сборки проекта.
#**********************************************************************
FREE_RTOS_OPTIMIZATION		:= -g3 -Os
STM32_F2_API_OPTIMIZATION	:= -g3 -Os
USER_CODE_OPTIMIZATION		:= -g3 -Os

LD_FILES = -T stm32f2_api/ld/stm32f205xB_mem.ld -T stm32f2_api/ld/stm32f2_section.ld

MK_FLAGS		:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft
# Размещает каждую функцию в отдельной секции.
MK_FLAGS		+= -ffunction-sections
MK_FLAGS		+= -fdata-sections

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

CPP_FLAGS		:= $(MK_FLAGS)     
CPP_FLAGS		+= -Werror -Wall -Wextra
CPP_FLAGS		+= -std=c++14
CPP_FLAGS		+= -fshort-enums

LDFLAGS			:= $(MK_FLAGS)
LDFLAGS			+= $(LD_FILES)
LDFLAGS			+= -Werror -Wall -Wextra 
# Убираем неиспользуемые функции из .elf.
LDFLAGS			+= -Wl,--gc-sections
LDFLAGS			+= -Ofast -funroll-loops
# Развертывание циклов.
LDFLAGS			+= -funroll-loops
# Удаление из elf неиспользуемого кода.
LDFLAGS			+= -Wl,-Map="build/$(PROJECT_NAME).map"

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
FREE_RTOS_OBJ_FILE	:= $(patsubst %.c, %.obj, $(FREE_RTOS_OBJ_FILE))

FREE_RTOS_INCLUDE_FILE	:= -include"./FreeRTOS_for_stm32f2/include/StackMacros.h"
# Сборка FreeRTOS.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/FreeRTOS_for_stm32f2/%.obj:	FreeRTOS_for_stm32f2/%.c 
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(FREE_RTOS_INCLUDE_FILE) -c $< -o $@

#**********************************************************************
# Для сборки stm32f2_api.
#**********************************************************************
# Собираем все необходимые .h файлы библиотеки.
STM32_F2_API_H_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.h" )

# Получаем список .cpp файлов ( путь + файл.c ).
STM32_F2_API_CPP_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.cpp" )

# Директории библиотеки.
STM32_F2_API_DIR	:= $(shell find stm32f2_api/ -maxdepth 3 -type d -name "*" )

# Подставляем перед каждым путем директории префикс -I.
STM32_F2_API_PATH	:= $(addprefix -I, $(STM32_F2_API_DIR))

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
STM32_F2_API_OBJ_FILE	:= $(addprefix build/obj/, $(STM32_F2_API_CPP_FILE))
# Затем меняем у всех .c на .o.
STM32_F2_API_OBJ_FILE	:= $(patsubst %.cpp, %.obj, $(STM32_F2_API_OBJ_FILE))

# Сборка stm32f2_api.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/stm32f2_api/%.obj:	stm32f2_api/%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(STM32_F2_API_PATH) $(USER_CFG_PATH) $(FREE_RTOS_PATH) $(STM32_F2_API_OPTIMIZATION) -c $< -o $@

#**********************************************************************
# Сборка кода пользователя.
# Весь код пользователя должен быть в корневой папке.
#**********************************************************************
# Собираем все необходимые .h файлы библиотеки.
USER_H_FILE	:= $(wildcard ./*.h)	

# Получаем список .cpp файлов ( путь + файл.cpp ).
USER_CPP_FILE	:= $(wildcard ./*.cpp)	

# Директории библиотеки.
USER_DIR	:= ./

# Подставляем перед каждым путем директории префикс -I.
USER_PATH	:= $(addprefix -I, $(USER_DIR))

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
USER_OBJ_FILE	:= $(addprefix build/obj/, $(USER_CPP_FILE))
# Затем меняем у всех .c на .o.
USER_OBJ_FILE	:= $(patsubst %.cpp, %.obj, $(USER_OBJ_FILE))

# Сборка файлов пользователя.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/%.obj:	%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(USER_PATH) $(STM32_F2_API_PATH) $(USER_CFG_PATH) $(FREE_RTOS_PATH) $(USER_CODE_OPTIMIZATION) -c $< -o $@

#**********************************************************************
# Компановка проекта.
#**********************************************************************
PROJECT_OBJ_FILE	:= $(FREE_RTOS_OBJ_FILE) $(STM32_F2_API_OBJ_FILE) $(USER_OBJ_FILE)

build/$(PROJECT_NAME).elf:	$(PROJECT_OBJ_FILE)
	@echo 'Project Composition:'
	@echo ' '

#$(LD)	$(LDFLAGS) -o build/$(PROJECT_NAME).elf
	@$(LD) $(LDFLAGS) $(PROJECT_OBJ_FILE)  -o build/$(PROJECT_NAME).elf
	@echo 'Finished building target: $@'
	@echo ' '

$(PROJECT_NAME).siz:	build/$(PROJECT_NAME).elf
	@echo 'Print Size:'
	@arm-none-eabi-size --format=berkeley "build/$(PROJECT_NAME).elf"
	@echo ' '

all:	$(PROJECT_NAME).siz
	@$(OBJDUMP) -D build/$(PROJECT_NAME).elf > build/$(PROJECT_NAME).asm
	@$(OBJCOPY) build/$(PROJECT_NAME).elf build/$(PROJECT_NAME).bin -O binary