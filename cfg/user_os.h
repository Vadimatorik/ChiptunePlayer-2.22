#pragma once

// В проекте используется FreeRTOS.
#include "freertos_headers.h"

//**********************************************************************
//                    Для связи с используемой OS.
//**********************************************************************

/*
 * Очереди.
 */

// Буффер по данные очереди.
#define USER_OS_STATIC_QUEUE_STRUCT                                             StaticQueue_t
// Данные, которыми будет заполнена переменная-буффер при старте.
#define USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE                  \
{                                                               \
    .pvDummy1 = {nullptr, nullptr, nullptr},                    \
    .u = {                                                      \
        .pvDummy2 = NULL,                                       \
    },                                                          \
    .xDummy3 = { { 0,nullptr, { 0,{ nullptr, nullptr } } },     \
                 { 0,nullptr, { 0,{ nullptr, nullptr } } } },   \
    .uxDummy4 = { 0, 0, 0 },                                    \
    .ucDummy5 = { 0, 0 },                                       \
    .ucDummy6 = 0                                               \
}
// Тип переменной-очереди.
#define USER_OS_STATIC_QUEUE                                                    QueueHandle_t

// Длина очереди (в количестве элементов!),
// размер одного элемента в байтах,
// указатель на uint8_t байт
// указатель на внутренную структуру самой очереди.
#define USER_OS_STATIC_QUEUE_CREATE(QUEUE_LENGTH,ITEM_SIZE,P_BUF,P_OBJ_ST)      xQueueCreateStatic( QUEUE_LENGTH, ITEM_SIZE, P_BUF, P_OBJ_ST )

/*
 * mutex-ы.
 */
// Тип переменной-буфера, в которую будет создан mutex.
#define USER_OS_STATIC_MUTEX_BUFFER                         StaticSemaphore_t
// Начальное значение буфера.
#define USER_OS_STATIC_MUTEX_BUFFER_INIT_VALUE              USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE
// Тип переменной mutex-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_MUTEX                                SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере mutex.
#define USER_OS_STATIC_MUTEX_CREATE(P_BUF)                  xSemaphoreCreateMutexStatic( P_BUF )
// Метод должен принять mutex в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание mutex-а) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_MUTEX(MUTEX,EXPECTATION)               xSemaphoreTake( MUTEX, ( TickType_t )EXPECTATION )
// Метод должен отдать mutex в потоке.
// Метод ничего не возвращает.
#define USER_OS_GIVE_MUTEX(MUTEX)                           xSemaphoreGive( MUTEX )

/*
 * Симафоры.
 */
// Тип переменной-буфера, в которую будет создан бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_BUFFER                 StaticSemaphore_t
// Данные, которыми будет заполнена переменная-буффер при старте.
#define USER_OS_STATIC_BIN_SEMAPHORE_BUFFER_INIT_VALUE      USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE
// Тип переменной бинарного semaphore-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_BIN_SEMAPHORE                        SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_CREATE(P_BUF)          xSemaphoreCreateBinaryStatic( P_BUF )
// Тип переменной, которая содержит в себе указания для метода выдачи семафора и прерывания о том,
// стоит ли удерживать данную задачу от вытеснения разблокированной с большим приоритетом (
// если вдруг симафор таковую разблокирует) или нет.
#define USER_OS_PRIO_TASK_WOKEN                             BaseType_t
// Метод должен выдать семафор из прерывания.
#define USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR(P_BUF,P_PRIO)   xSemaphoreGiveFromISR( P_BUF, P_PRIO )
// Метод должен принять симафор в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание семафора) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_BIN_SEMAPHORE(SEMAPHORE,EXPECTATION)   xSemaphoreTake( SEMAPHORE, ( TickType_t )EXPECTATION )

/*
 * Созданиче задач.
 */
#define USER_OS_STATIC_TASK_CREATE(FUNC,STRING_NAME,STACK_SIZE,PARAM,PRIO,P_STACK,P_STUCT)     xTaskCreateStatic( FUNC, STRING_NAME, STACK_SIZE, PARAM, PRIO, P_STACK, P_STUCT )
#define USER_OS_STATIC_STACK_TYPE                                                              StackType_t
#define USER_OS_STATIC_TASK_STRUCT_TYPE                                                        StaticTask_t
#define USER_OS_STATIC_TASK_STRUCT_INIT_VALUE                                                                           \
{                                                                                                                       \
    .pxDummy1       = nullptr,                                                                                          \
    .xDummy3        = { { 0, { nullptr, nullptr, nullptr, nullptr } }, { 0, { nullptr, nullptr, nullptr, nullptr } } }, \
    .uxDummy5       = 0,                                                                                                \
    .pxDummy6       = nullptr,                                                                                          \
    .ucDummy7       = { 0 },                                                                                            \
    .uxDummy12      = { 0 },                                                                                            \
    .ulDummy18      = 0,                                                                                                \
    .ucDummy19      = 0,                                                                                                \
    .uxDummy20      = 0                                                                                                 \
}

/*
 * Прочее.
 */

#define USER_OS_DELAY_MS(DELAY_MS)                          vTaskDelay( (TickType_t)DELAY_MS )
