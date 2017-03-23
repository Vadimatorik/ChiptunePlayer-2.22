#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * В данном файле находится таблица векторов-прерываний (указатель на вершину стека + массив
 * указателей на функции), а так же функции-заглушеки (while(1){}; циклы) для неиспользуемых
 * прерываний (на каждый вектор прерывания своя заглушка, для более удобной фиксации причины
 * остановки программы).
 * */

/*
 * Данные значения (указатели на области памяти контроллера) берутся из section.ld файла.
 */
extern uint32_t *_sidata;			// Начальный адрес содержимого .data области во flash
									// (то, что будет скопировано в RAM).
extern uint32_t *_sdata;			// Начальный адрес .data области в RAM
									// (то, что будет скопировано с области по указателю _sidata (из flash в ram).
extern uint32_t *_edata;			// Конечный адрес .data области в RAM (проверяется операцией <, т.к. байт,
									// адрес которого записан в эту переменную, копировать не нужно. Только то,
									// что до него).

extern uint32_t *__bss_start__;		// Начальный и адрес BSS области
									// (будет заполнено 0-ми. Стирать нужно уже с этого адреса).
extern uint32_t *__bss_end__;		// Конечный адрес BSS области.
									// (По этому адресу записывать уже не нужно (проверяется по <)).
extern uint32_t *_stack;			// Вершина стека (конец RAM).

// У каждого handler-а есть свое тело.
// В случае, если пользователь не объявил его у себя в коде - используется тело-заглушка
// на основе слабой ссылки (дополнительная надежность и удобство при отладке).
void __attribute__((weak)) nmi_handler(void) { while(1); };
void __attribute__((weak)) hard_fault_handler(void) { while(1); };
void __attribute__((weak)) mem_manage_handler(void) { while(1); };
void __attribute__((weak)) bus_fault_handler(void) { while(1); };
void __attribute__((weak)) usage_fault_handler(void) { while(1); };
void __attribute__((weak)) sv_call_handler(void) { while(1); };
void __attribute__((weak)) debug_monitor_handler(void) { while(1); };
void __attribute__((weak)) pend_sv_handler(void) { while(1); };
void __attribute__((weak)) sys_tick_handler(void) { while(1); };

void __attribute__((weak)) wwdg_handler(void) { while(1); };
void __attribute__((weak)) pvd_handler(void) { while(1); };
void __attribute__((weak)) tamp_stamp_handler(void) { while(1); };
void __attribute__((weak)) rtc_wkup_handler(void) { while(1); };
void __attribute__((weak)) flash_handler(void) { while(1); };
void __attribute__((weak)) rcc_handler(void) { while(1); };
void __attribute__((weak)) exti_0_handler(void) { while(1); };
void __attribute__((weak)) exti_1_handler(void) { while(1); };
void __attribute__((weak)) exti_2_handler(void) { while(1); };
void __attribute__((weak)) exti_3_handler(void) { while(1); };
void __attribute__((weak)) exti_4_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream0_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream1_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream2_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream3_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream4_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream5_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream6_handler(void) { while(1); };
void __attribute__((weak)) adc_handler(void) { while(1); };
void __attribute__((weak)) can1_tx_handler(void) { while(1); };
void __attribute__((weak)) can1_rx0_handler(void) { while(1); };
void __attribute__((weak)) can1_rx1_handler(void) { while(1); };
void __attribute__((weak)) can1_sce_handler(void) { while(1); };
void __attribute__((weak)) exti_9_5_handler(void) { while(1); };
void __attribute__((weak)) tim1_brk_and_tim9_handler(void) { while(1); };
void __attribute__((weak)) tim1_up_and_tim10_handler(void) { while(1); };
void __attribute__((weak)) tim1_trg_com_and_tim11_handler(void) { while(1); };
void __attribute__((weak)) tim1_capture_compare_handler(void) { while(1); };
void __attribute__((weak)) tim2_handler(void) { while(1); };
void __attribute__((weak)) tim3_handler(void) { while(1); };
void __attribute__((weak)) tim4_handler(void) { while(1); };
void __attribute__((weak)) i2c1_ev_handler(void) { while(1); };
void __attribute__((weak)) i2c1_er_handler(void) { while(1); };
void __attribute__((weak)) i2c2_ev_handler(void) { while(1); };
void __attribute__((weak)) i2c2_er_handler(void) { while(1); };
void __attribute__((weak)) spi1_handler(void) { while(1); };
void __attribute__((weak)) spi2_handler(void) { while(1); };
void __attribute__((weak)) usart1_handler(void) { while(1); };
void __attribute__((weak)) usart2_handler(void) { while(1); };
void __attribute__((weak)) usart3_handler(void) { while(1); };
void __attribute__((weak)) exti_15_10_handler(void) { while(1); };
void __attribute__((weak)) rtc_alarm_handler(void) { while(1); };
void __attribute__((weak)) otg_fs_wkup_handler(void) { while(1); };
void __attribute__((weak)) tim8_brk_and_tim12_handler(void) { while(1); };
void __attribute__((weak)) tim8_up_and_tim13_handler(void) { while(1); };
void __attribute__((weak)) tim8_trg_com_and_tim14_handler(void) { while(1); };
void __attribute__((weak)) tim8_cc_handler(void) { while(1); };
void __attribute__((weak)) dma1_stream7_handler(void) { while(1); };
void __attribute__((weak)) fsmc_handler(void) { while(1); };
void __attribute__((weak)) sdio_handler(void) { while(1); };
void __attribute__((weak)) tim5_handler(void) { while(1); };
void __attribute__((weak)) spi3_handler(void) { while(1); };
void __attribute__((weak)) uart4_handler(void) { while(1); };
void __attribute__((weak)) uart5_handler(void) { while(1); };
void __attribute__((weak)) tim6_and_dac_handler(void) { while(1); };
void __attribute__((weak)) tim7_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream0_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream1_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream2_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream3_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream4_handler(void) { while(1); };
void __attribute__((weak)) eth_handler(void) { while(1); };
void __attribute__((weak)) eth_wkup_handler(void) { while(1); };
void __attribute__((weak)) can2_tx_handler(void) { while(1); };
void __attribute__((weak)) can2_rx0_handler(void) { while(1); };
void __attribute__((weak)) can2_rx1_handler(void) { while(1); };
void __attribute__((weak)) can2_sce_handler(void) { while(1); };
void __attribute__((weak)) otg_fs_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream5_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream6_handler(void) { while(1); };
void __attribute__((weak)) dma2_stream7_handler(void) { while(1); };
void __attribute__((weak)) usart6_handler(void) { while(1); };
void __attribute__((weak)) i2c3_ev_handler(void) { while(1); };
void __attribute__((weak)) i2c3_er_handler(void) { while(1); };
void __attribute__((weak)) otg_hs_ep1_out_handler(void) { while(1); };
void __attribute__((weak)) otg_hs_ep1_in_handler(void) { while(1); };
void __attribute__((weak)) otg_hs_wkup_handler(void) { while(1); };
void __attribute__((weak)) otg_hs_handler(void) { while(1); };
void __attribute__((weak)) dcmi_handler(void) { while(1); };
void __attribute__((weak)) cryp_handler(void) { while(1); };
void __attribute__((weak)) hash_and_rng_handler(void) { while(1); };

// Выполнение программы начинается с данного метода.
void reset_handler(void);

/*
 * Вершина стека (указатель на последний байт RAM) + таблица указателей на функции-обработчики.
 * В случае, если пользователь не использует собственные функции для какого-либо из векторов прерываний,
 * используются заглушки по-умолчанию (описаны выше).
 */
__attribute__ ((section(".irq_table")))
void (*const interrupt_vectors[])(void) =
{
	(void (*)(void))(_stack),
	reset_handler,
	nmi_handler,
	hard_fault_handler,
	mem_manage_handler,
	bus_fault_handler,
	usage_fault_handler,
    0,
    0,
    0,
    0,
	sv_call_handler,
	debug_monitor_handler,
    0,
	pend_sv_handler,
	sys_tick_handler,
  
    // Прерывания от периферии.
    wwdg_handler,
	pvd_handler,
	tamp_stamp_handler,
	rtc_wkup_handler,
	flash_handler,
	rcc_handler,
	exti_0_handler,
	exti_1_handler,
	exti_2_handler,
	exti_3_handler,
	exti_4_handler,
	dma1_stream0_handler,
	dma1_stream1_handler,
	dma1_stream2_handler,
	dma1_stream3_handler,
	dma1_stream4_handler,
	dma1_stream5_handler,
	dma1_stream6_handler,
	adc_handler,
	can1_tx_handler,
	can1_rx0_handler,
	can1_rx1_handler,
	can1_sce_handler,
	exti_9_5_handler,
	tim1_brk_and_tim9_handler,
	tim1_up_and_tim10_handler,
	tim1_trg_com_and_tim11_handler,
	tim1_capture_compare_handler,
	tim2_handler,
	tim3_handler,
	tim4_handler,
	i2c1_ev_handler,
	i2c1_er_handler,
	i2c2_ev_handler,
	i2c2_er_handler,
	spi1_handler,
	spi2_handler,
	usart1_handler,
	usart2_handler,
	usart3_handler,
	exti_15_10_handler,
	rtc_alarm_handler,
	otg_fs_wkup_handler,
	tim8_brk_and_tim12_handler,
	tim8_up_and_tim13_handler,
	tim8_trg_com_and_tim14_handler,
	tim8_cc_handler,
	dma1_stream7_handler,
	fsmc_handler,
	sdio_handler,
	tim5_handler,
	spi3_handler,
	uart4_handler,
	uart5_handler,
	tim6_and_dac_handler,
	tim7_handler,
	dma2_stream0_handler,
	dma2_stream1_handler,
	dma2_stream2_handler,
	dma2_stream3_handler,
	dma2_stream4_handler,
	eth_handler,
	eth_wkup_handler,
	can2_tx_handler,
	can2_rx0_handler,
	can2_rx1_handler,
	can2_sce_handler,
	otg_fs_handler,
	dma2_stream5_handler,
	dma2_stream6_handler,
	dma2_stream7_handler,
	usart6_handler,
	i2c3_ev_handler,
	i2c3_er_handler,
	otg_hs_ep1_out_handler,
	otg_hs_ep1_in_handler,
	otg_hs_wkup_handler,
	otg_hs_handler,
	dcmi_handler,
	cryp_handler,
	hash_and_rng_handler
};

/*
 * Функции, необходимые для начальной инициализации контроллера.
 */
/* Заполняем 0-ми bss в RAM. */
inline void __attribute__((always_inline))
__initialize_bss(uint32_t *section_begin, uint32_t *section_end){
	uint32_t *p = section_begin;
	while (p < section_end){
		*section_begin++ = 0;
	}
}

/* Копируем область ".data" из flash в ram. */
inline void __attribute__((always_inline))
__initialize_data(uint32_t *from, uint32_t *section_begin, uint32_t *section_end){
	uint32_t *p = section_begin;
	while (p < section_end){
		*p++ = *from++;
	}
}

/*
 * Функции, необходимые для поддержания C++.
 */
void __attribute__((weak))
_exit(int code __attribute__((unused))){
	while (1);
}

int __attribute__((weak))
_kill(int pid __attribute__((unused)), int sig __attribute__((unused))){
	return -1;
}

int __attribute__((weak))
_getpid (int n __attribute__ ((unused))){
	return 1;
}

/*
 * С этого метода начинается выполнение программы.
 * В нем производится инициализация RAM,
 * после чего управление передается программе пользователя.
 */

extern int main();									// Функция main должна быть объявлена в коде пользователя.

void reset_handler(void) {
	__initialize_bss(__bss_start__, __bss_end__);	// Заполняем bss область нулями.
	__initialize_data(_sidata, _sdata, _edata);		// Копируем начальные значения изменяемых данных в ram.
    main();
}

#ifdef __cplusplus
}
#endif

