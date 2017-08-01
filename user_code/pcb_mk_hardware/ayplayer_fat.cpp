#include "ayplayer_fat.h"

extern microsd_spi sd2;

extern "C" {
#if !FF_FS_NORTC && !FF_FS_READONLY
DWORD get_fattime ( void ) {
    return 0;
}
#endif

/*
 * Временный костыль.
 * При каждом чтении/записи заново переинициализируется.
 * Пока так...
 */
DSTATUS disk_initialize ( BYTE drv ) {
    ( void )drv;
    return ~STA_NOINIT;
}

DSTATUS disk_status ( BYTE pdrv ) {
    ( void )pdrv;
    return ~STA_NOINIT;
}

DRESULT disk_read ( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
    ( void )pdrv;
    for (UINT i = 0; i<count; i++){										// Считываем нужное количество блоков.
        if ( sd2.read_sector( buff, sector) != EC_FRESULT::OK ){
            return RES_ERROR;											// Если считать сектор не удалось.
        }
        sector+=512;		// Смещаемся на ячейку (Тут учесть прикол с возможной адресацией по блокам. Сейчас побайтово).
        buff+=512;
    }
    return RES_OK;
}

DRESULT disk_write ( BYTE pdrv, const BYTE* buff, DWORD sector, UINT count ) {
    ( void )pdrv;
    BYTE* point_buf = (BYTE*)buff;
    for (UINT i = 0; i<count; i++){										// Считываем нужное количество блоков.
        if ( sd2.write_sector( sector, point_buf ) != EC_FRESULT::OK ) {
            return RES_ERROR;											// Если считать сектор не удалось.
        }
        sector+=512;		// Смещаемся на ячейку (Тут учесть прикол с возможной адресацией по блокам. Сейчас побайтово).
        buff+=512;
    }
    return RES_OK;
}

DRESULT disk_ioctl ( BYTE pdrv, BYTE cmd, void* buff ) {
    ( void )pdrv;
    ( void )cmd;
    ( void )buff;
    return RES_OK;
}

}

/*
Из примера.
DWORD get_fattime (void)
{
    RTCTIME rtc;

 Get local time
    if (!rtc_gettime(&rtc)) return 0;

 Pack date and time into a DWORD variable
    return	  ((DWORD)(rtc.year - 1980) << 25)
            | ((DWORD)rtc.month << 21)
            | ((DWORD)rtc.mday << 16)
            | ((DWORD)rtc.hour << 11)
            | ((DWORD)rtc.min << 5)
            | ((DWORD)rtc.sec >> 1);
}
  */
