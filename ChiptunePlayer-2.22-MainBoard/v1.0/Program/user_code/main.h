#pragma once

#include "ayplayer.h"
#include "stm32f2xx_hal.h"

extern Wdt											wdtObj;
extern ayplayerGpio									gpioStruct;
extern GlobalPort									gp;
extern Uart											usart3;
extern Rcc											ayplayer_rcc;
extern SpiMaster8Bit								spi1;
extern SpiMaster8Bit								spi2;
extern SpiMaster8Bit								spi3;
extern AdcOneChannel								adcBat;
extern TimCompOneChannel							ayClk;
extern TimPwmOneChannel								lcdPwm;
extern TimInterrupt									interruptAy;
extern RunTimeLogger								ayLog;
extern Pwr											pwr;

extern ShiftRegister								srAy;
extern ShiftRegister								srButton;
extern ButtonsThroughShiftRegisterOneInputPin		button;
extern ad5204										soundDp;
extern freeRtosObj									osData;
extern AyYmLowLavel									ayLow;
extern ST7565										lcd;
extern MicrosdBase*									sdArray[2];
extern AyYmFilePlay									ayYmFilePlay;

#ifdef configGENERATE_RUN_TIME_STATS
extern TimCounter									timRunTimeStats;
#endif

#ifdef __cplusplus
extern "C" {
#endif

int main ( void );

#ifdef __cplusplus
}
#endif
