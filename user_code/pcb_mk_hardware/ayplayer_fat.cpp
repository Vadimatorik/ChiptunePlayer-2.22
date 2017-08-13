#include "ayplayer_fat.h"

extern microsd_spi sd2;

extern "C" {

#if !FF_FS_NORTC && !FF_FS_READONLY
DWORD get_fattime ( void ) {
    return 0;
}
#endif

DSTATUS disk_initialize ( BYTE drv ) {
    ( void )drv;    // Пока пользуемся одной, потом переписать на 2.
    if ( sd2.initialize() != EC_MICRO_SD_TYPE::ERROR ) {
        return 0;
    } else {
        return STA_NOINIT;
    }
}

DSTATUS disk_status ( BYTE pdrv ) {
    ( void )pdrv;

    if ( sd2.get_type() == EC_MICRO_SD_TYPE::ERROR )
        return STA_NOINIT;

    if ( sd2.wake_up() == EC_SD_RESULT::OK )
        return 0;

    return STA_NOINIT;
}

DRESULT disk_read ( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
    ( void )pdrv;
    for (UINT i = 0; i<count; i++){										// Считываем нужное количество блоков.
        if ( sd2.read_sector( sector, buff ) != EC_SD_RESULT::OK ){
            return RES_ERROR;											// Если считать сектор не удалось.
        }
        sector++;
        buff+=512;
    }
    return RES_OK;
}

DRESULT disk_write ( BYTE pdrv, const BYTE* buff, DWORD sector, UINT count ) {
    ( void )pdrv; ( void )buff; ( void )sector;
    BYTE* point_buf = (BYTE*)buff;
    for (UINT i = 0; i<count; i++){
        // Считываем нужное количество блоков ( пока что поблочно ).
        if ( sd2.write_sector( point_buf, sector ) != EC_SD_RESULT::OK ) {
            return RES_ERROR;
        }
        sector++;
        point_buf+=512;
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

// Из примера.
/*
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
}*/
