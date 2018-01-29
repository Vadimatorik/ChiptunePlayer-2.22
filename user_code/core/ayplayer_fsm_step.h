/*!
 * \file
 * \brief   Заголовочный файл, содержащий заголовоки методов-шагов
 *          конечного автомата.
 */

#pragma once

#include "core_fsm.h"

/*!
 * Инициализация GUI.
 * \return всегда <<0>>.
 */
int init_gui						( const fsm_step* previous_step );

/*!
 * Инициализация потенциометров актуальными значениями.
 *
 * - <<0>> - инициализация прошла успешно.
 * - <<FSM_RET_ERROR>> - ошибка на низком уровне. Выход из автомата.
 */
int dp_init							( const fsm_step* previous_step );

/*!
 * Инициализация единого объекта FAT.
 * \return
 * - <<0>> - инициализация прошла успешно.
 * - <<FSM_RET_ERROR>> - ошибка на низком уровне. Выход из автомата.
 */
int fat_init						( const fsm_step* previous_step );

/*!
 * Ожидание стабилизации питания на плате.
 * \return всегда <<0>>.
 */
int waiting_for_food_stabilization	( const fsm_step* previous_step );

/*!
 * Проверка системной карты в слоте.
 * \return
 * - <<0>> - карта обнаружена.
 * - <<FSM_RET_REPEAT>> - карта отсутсвует.
 */
int sd2_chack 						( const fsm_step* previous_step );

/*!
 * Проверка наличия файла-списка в основной директории на системной карте.
 * \return
 * - <<0>> - файл уже существует.
 * - <<1>> - файл отсуствует.
 * - <<2>> - невозможно прочитать информацию с microsd.
 */
int sd2_track_file_open				( const fsm_step* previous_step );
