#include "main.h"

#include "ayplayer_hardware.h"
#include "freertos_headers.h"
#include "ayplayer_housekeeping.h"
#include "ayplayer_button.h"
#include "ayplayer_shift_register.h"
#include "ayplayer_core.h"

/*!
 * \brief Метод совершает все необходимые действия до запуска
 * планировщика FreeRTOS и запускает планировщик.
 *
 * Метод:
 * - инициализирует всю аппаратную периферию микроконтроллера;
 * - инициализирует некоторые внешние аппаратные блоки, расположенные на плате;
 * - создает необходимые задачи, которые будут выполняться FreeRTOS;
 * - запускает планировщик FreeRTOS
 */
extern "C" {

int main ( void ) {
	ayplayer_mc_hardware();
	ayplayer_housekeeping_init();
	ayplayer_button_init();
	ayplayer_shift_register();
	ayplayer_ay_init();
	ayplayer_core_init();

    vTaskStartScheduler();
    while ( true );
}

}
