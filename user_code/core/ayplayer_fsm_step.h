/*!
 * \file
 * \brief   Заголовочный файл, содержащий заголовоки методов-шагов
 *          конечного автомата.
 */

#pragma once

#include "core_fsm.h"

/*!
 * Инициализация GUI.
 */
int init_gui						( const fsm_step* previous_step );

/*!
 * Инициализация потенциометров актуальными значениями.
 */
int dp_init							( const fsm_step* previous_step );

/*!
 * Инициализация единого объекта FAT.
 */
int fat_init						( const fsm_step* previous_step );

/*!
 * Ожидание стабилизации питания на плате.
 */
int waiting_for_food_stabilization	( const fsm_step* previous_step );

/*!
 * Проверка системной карты в слоте.
 * \return
 * - <<0>> - Карта обнаружена.
 * - <<1>> - карта отсутсвует.
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
