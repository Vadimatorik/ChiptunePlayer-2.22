######################################################################
# ��������� ������ �������.
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
# ��������� toolchain-�.
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
# ������������ ������� ������������.
######################################################################
# ��� ����� �� ����� cfg � �������� �������.
USER_CFG_H_FILE		:= $(wildcard ./cfg/*.h) 
USER_CFG_DIR		:= ./cfg
USER_CFG_PATH		:= -I$(USER_CFG_DIR)

# ������ ���� ������ ��� �������� ������������� FreeRTOS �� 
# CPP ����. ��� ��� �� ������� �������� �� ������� FreeRTOS
# � ���������� �����, ��� ������������ FreeRTOS.
USER_CFG_H_FILE		+= ./FreeRTOS_for_stm32f2/freertos_headers.h
	
######################################################################
# ��� ������ FreeRTOS.
######################################################################
# �������� ��� ����������� .h ����� FreeRTOS.
FREE_RTOS_H_FILE	:= $(wildcard ./FreeRTOS_for_stm32f2/include/*.h)	

# ����������, � ������� ����� ����� FreeRTOS.
FREE_RTOS_DIR		:= ./FreeRTOS_for_stm32f2
FREE_RTOS_DIR		+= ./FreeRTOS_for_stm32f2/include

# ����������� ����� ������ ����� ���������� ������� -I.
FREE_RTOS_PATH		:= $(addprefix -I, $(FREE_RTOS_DIR))

# �������� ������ .c ������ ( ���� + ����.c ).
FREE_RTOS_C_FILE	:= $(wildcard ./FreeRTOS_for_stm32f2/*.c)

# �������� ������ .o ������ ( ���� + ����.o ).
# ������� ���������� ������� ( ����� ��� .o ������ � ��������� ����������
# � ����������� ��������.
FREE_RTOS_O_FILE	:= $(addprefix ./build/o/, $(FREE_RTOS_C_FILE))
# ����� ������ � ���� .c �� .o.
FREE_RTOS_O_FILE	:= $(patsubst %.c, %.o, $(FREE_RTOS_O_FILE))   

all:	$(FREE_RTOS_O_FILE)	

# ������ FreeRTOS.
# $< - ������� .c ���� (�����������).
# $@ - ������� ���� (����������� .o ����).
# $(dir ����) - ������� ����� ��� ����, ����� ���� ����� �����������.
$(FREE_RTOS_O_FILE):	$(FREE_RTOS_C_FILE) $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE)
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(FREE_RTOS_PATH) $(USER_CFG_PATH) -c $< -o $@  
	 
	 