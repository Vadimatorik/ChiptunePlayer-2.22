######################################################################
# Параметры сборки проекта.
######################################################################
FREE_RTOS_OPTIMIZATION	:= -g3 -Og

MK_FLAGS		:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

C_FLAGS			:= $(MK_FLAGS)		
C_FLAGS			+= -fmessage-length=0 
C_FLAGS			+= -fsigned-char 
C_FLAGS			+= -ffunction-sections
C_FLAGS			+= -fdata-sections
C_FLAGS			+= -Wall
C_FLAGS			+= -Wextra 
C_FLAGS			+= -std=gnu99 
C_FLAGS			+= -fshort-enums

######################################################################
# Параметры toolchain-а.
######################################################################
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

######################################################################
# Конфигурация проекта пользователя.
######################################################################
# Все файлы из папки cfg в каталоге проекта.
USER_CFG_H_FILE		:= $(wildcard ./cfg/*.h) 
USER_CFG_DIR		:= ./cfg
USER_CFG_PATH		:= -I$(USER_CFG_DIR)

# Данный файл служит для удобного использования FreeRTOS из 
# CPP кода. Так что он вынесен отдельно от проекта FreeRTOS
# и вызывается везде, где используется FreeRTOS.
USER_CFG_H_FILE		+= ./FreeRTOS_for_stm32f2/freertos_headers.h
	
######################################################################
# Для сборки FreeRTOS.
######################################################################
# Собираем все необходимые .h файлы FreeRTOS.
FREE_RTOS_H_FILE	:= $(wildcard ./FreeRTOS_for_stm32f2/include/*.h)	

# Директории, в которых лежат файлы FreeRTOS.
FREE_RTOS_DIR		:= ./FreeRTOS_for_stm32f2
FREE_RTOS_DIR		+= ./FreeRTOS_for_stm32f2/include

# Подставляем перед каждым путем директории префикс -I.
FREE_RTOS_PATH		:= $(addprefix -I, $(FREE_RTOS_DIR))

# Получаем список .c файлов ( путь + файл.c ).
FREE_RTOS_C_FILE	:= $(wildcard ./FreeRTOS_for_stm32f2/*.c)

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
FREE_RTOS_O_FILE	:= $(addprefix ./build/o/, $(FREE_RTOS_C_FILE))
# Затем меняем у всех .c на .o.
FREE_RTOS_O_FILE	:= $(patsubst %.c, %.o, $(FREE_RTOS_O_FILE))   

all:	$(FREE_RTOS_O_FILE)	

# Сборка FreeRTOS.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
$(FREE_RTOS_O_FILE):	$(FREE_RTOS_C_FILE) $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE)
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(FREE_RTOS_PATH) $(USER_CFG_PATH) -c $< -o $@  
	 
	 