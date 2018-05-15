#pragma once

// В проекте используется FreeRTOS.
#include "freertos_headers.h"

//**********************************************************************
//					Для связи с используемой OS.
//**********************************************************************

/*
 * Очереди.
 */

// Буффер по данные очереди.
#define USER_OS_STATIC_QUEUE_STRUCT												StaticQueue_t
// Тип переменной-очереди.
#define USER_OS_STATIC_QUEUE													QueueHandle_t

// Длина очереди (в количестве элементов!),
// размер одного элемента в байтах,
// указатель на uint8_t байт
// указатель на внутренную структуру самой очереди.
#define USER_OS_STATIC_QUEUE_CREATE(QUEUE_LENGTH,ITEM_SIZE,P_BUF,P_OBJ_ST)		xQueueCreateStatic( QUEUE_LENGTH, ITEM_SIZE, P_BUF, P_OBJ_ST )
#define USER_OS_QUEUE_RECEIVE(QUEUE,P_BUF,TIMEOUT)								xQueueReceive(QUEUE,P_BUF,(TickType_t)TIMEOUT)
#define USER_OS_QUEUE_SEND(QUEUE,P_BUF,TIMEOUT)									xQueueSend(QUEUE,P_BUF,(TickType_t)TIMEOUT)

// Очистить очередь.
#define USER_OS_QUEUE_RESET(QUEUE)												xQueueReset(QUEUE)

// Количество элементов в очереди.
#define USER_OS_QUEUE_CHECK_WAIT_ITEM(QUEUE)									uxQueueMessagesWaiting(QUEUE)

/*
 * mutex-ы.
 */
// Тип переменной-буфера, в которую будет создан mutex.
#define USER_OS_STATIC_MUTEX_BUFFER							 StaticSemaphore_t
// Тип переменной mutex-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_MUTEX								SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере mutex.
#define USER_OS_STATIC_MUTEX_CREATE(P_BUF)					xSemaphoreCreateMutexStatic( P_BUF )
// E\Удалить мутекс.
#define USER_OS_STATIC_MUTEX_DELETE( MUTEX )				vSemaphoreDelete( MUTEX )
// Метод должен принять mutex в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание mutex-а) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_MUTEX(MUTEX,EXPECTATION)				xSemaphoreTake( MUTEX, ( TickType_t )EXPECTATION )
// Метод должен отдать mutex в потоке.
// Метод ничего не возвращает.
#define USER_OS_GIVE_MUTEX(MUTEX)							xSemaphoreGive( MUTEX )
/// Возвращает 1, если mutex свободен. 0 - если занят.
#define USER_OS_CHECK_MUTEX_AVAILABLE(MUTEX)				uxSemaphoreGetCount( MUTEX )
/*
 * Симафоры.
 */
// Тип переменной-буфера, в которую будет создан бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_BUFFER					StaticSemaphore_t
// Тип переменной бинарного semaphore-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_BIN_SEMAPHORE						SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_CREATE(P_BUF)			xSemaphoreCreateBinaryStatic( P_BUF )
// Тип переменной, которая содержит в себе указания для метода выдачи семафора и прерывания о том,
// стоит ли удерживать данную задачу от вытеснения разблокированной с большим приоритетом (
// если вдруг симафор таковую разблокирует) или нет.
#define USER_OS_PRIO_TASK_WOKEN								BaseType_t
// Метод должен выдать семафор из прерывания.
#define USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR(P_BUF,P_PRIO)	xSemaphoreGiveFromISR( P_BUF, P_PRIO )
#define USER_OS_GIVE_BIN_SEMAPHORE(P_BUF)					xSemaphoreGive( P_BUF )

// Метод должен принять симафор в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание семафора) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_BIN_SEMAPHORE(SEMAPHORE,EXPECTATION)	xSemaphoreTake( SEMAPHORE, ( TickType_t )EXPECTATION )

//**********************************************************************
// Созданиче задач.
//**********************************************************************
#define USER_OS_STATIC_TASK_CREATE(FUNC,STRING_NAME,STACK_SIZE,PARAM,PRIO,P_STACK,P_STRUCT)		xTaskCreateStatic( FUNC, STRING_NAME, STACK_SIZE, PARAM, PRIO, P_STACK, P_STRUCT )
#define USER_OS_STATIC_STACK_TYPE																StackType_t
#define USER_OS_STATIC_TASK_STRUCT_TYPE															StaticTask_t

/*!
 * Таймеры.
 */
#define USER_OS_TIMER																			TimerHandle_t
#define USER_OS_TIMER_STATIC_STRUCT																StaticTimer_t
#define USER_OS_STATIC_TIMER_CREATE(STRING_NAME,PERIOD_MS,PARAM,FUNC,P_STRUCT)					xTimerCreateStatic(STRING_NAME,PERIOD_MS/portTICK_RATE_MS,pdTRUE,PARAM,FUNC,P_STRUCT)
#define USER_OS_STATIC_TIMER_START(TIMER)														xTimerStart(TIMER,portMAX_DELAY)
#define USER_OS_STATIC_TIMER_CHANGE_PERIOD(TIMER,PERIOD)										xTimerChangePeriod(TIMER,PERIOD,portMAX_DELAY)
#define USER_OS_STATIC_TIMER_GET_PERIOD(TIMER)													xTimerGetPeriod(TIMER)
#define USER_OS_STATIC_TIMER_STOP(TIMER)														xTimerStop(TIMER,portMAX_DELAY)
#define USER_OS_STATIC_TIMER_RESET(TIMER)														xTimerReset(TIMER,portMAX_DELAY)


//**********************************************************************
// Прочее.
//**********************************************************************
#define USER_OS_TICK_TYPE									TickType_t
#define USER_OS_DELAY_MS(DELAY_MS)							vTaskDelay( ( TickType_t )DELAY_MS )
#define USER_OS_TASK_GET_TICK_COUNT							xTaskGetTickCount
#define USER_OS_TASK_DELAY_UNTIL(LWT,D)						vTaskDelayUntil(LWT,D)				// last_wake_time, time_out.


//**********************************************************************
//								Определения, не касающиеся основных модулей.
//**********************************************************************
#define BIT_BAND_SRAM_REF	0x20000000
#define BIT_BAND_SRAM_BASE	0x22000000

//Получаем адрес бита RAM в Bit Banding области.
#define MACRO_GET_BB_P_SRAM(reg, bit) ((BIT_BAND_SRAM_BASE + (reg - BIT_BAND_SRAM_REF)*32 + (bit * 4)))

#define BIT_BAND_PER_REF	((uint32_t)0x40000000)
#define BIT_BAND_PER_BASE	((uint32_t)0x42000000)

// Получаем адрес бита периферии в Bit Banding области.
#define M_GET_BB_P_PER(ADDRESS,BIT) ((BIT_BAND_PER_BASE + (ADDRESS - BIT_BAND_PER_REF)*32 + (BIT * 4)))

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Причем запрещает переписывать то, что по указателю (только чтение).
#define M_U32_TO_P_CONST(point)		 ( ( const uint32_t *const )( point ) )

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Данные по указателю можно изменять.
#define M_U32_TO_P(point)				( ( uint32_t * )point )

// Преобразует enum class в uint8_t.
#define M_EC_TO_U8(ENUM_VALUE)			( ( uint8_t )ENUM_VALUE )

// Преобразует enum class в uint32_t.
#define M_EC_TO_U32(ENUM_VALUE)		 ( ( uint32_t )ENUM_VALUE )


// Возвращаем размер массива.
#define M_SIZE_ARRAY(ARRAY)			 (sizeof(ARRAY)/sizeof(ARRAY[0]))

// Служит для записи таблицы векторов прерываний.
#define M_ISR_TO_CONST_P_VOID(POINT)	((void*)(POINT))
