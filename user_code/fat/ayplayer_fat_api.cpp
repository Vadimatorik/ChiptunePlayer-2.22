#include "ayplayer_fat_api.h"

//**********************************************************************
// Используемые глобальные объекты.
//**********************************************************************
FATFS                   fat;




// Инициализация FAT объекта (общий на обе карты).
// 0                    - успех.
// ECONNREFUSED         - провал.
// fr                   - в случае провала - причина.
int fat_init ( void ) {
    FRESULT fr;
    fr = f_mount( &fat, "0:", 0 );
    if ( fr != FR_OK ) {
        return ECONNREFUSED;
    }
    return 0;
}

// Пытаемся инициализировать карту (проверяем ее адекватность).
// 0                    - успех.
// ECONNREFUSED         - провал.
int system_card_chack ( void ) {
    DSTATUS r;
    for ( int l = 0; l < 5; l++) {      // Даем 5 попыток инициализировать карту.
        r = disk_initialize(0);
        if ( r == RES_OK ) {
            return 0;
        }
    }


    return ECONNREFUSED;
}
