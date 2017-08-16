#include "ayplayer_gui_window_sd_card_error.h"

char s_err_disk_err[]           = "DISK ERR!";          // Произошла невосстановимая ошибка на низком уровне (функции I/O диска).

char s_err_int_err[]            = "INT ERR!";           // Ошибка Assert. Внутри процесса что-то пошло не так. Возможны следующие варианты.
                                                        // Любая ошибка структуры FAT на томе.
                                                        // Рабочая область (file system object,
                                                        // file object или что-то подобное) испорчена из-за переполнения стека или другого приложения.
                                                        // Эта причина ошибки бывает чаще всего.

char s_err_not_ready[]          = "NOT READY!";         // Драйв диска не может работать из-за некорректного извлечения носителя или ошибки функции disk_initialize.

char s_err_no_file[]            = "NO FILE!";           // Файл не найден.

char s_err_no_path[]            = "NO PATH!";           // Не найден путь.

char s_err_invalid_name[]       = "INVALID NAME!";      // Указанная строка содержит недопустимое имя пути (path name).

char s_err_denied[]             = "DENIED!";            // Требуемый доступ был отклонен по одной из следующих причин:

                                                        // Открытие файла в режиме записи, когда файл имеет атрибут read-only (только чтение).
                                                        // Удаление файла или директории, которые имеют атрибут read-only.
                                                        // Удаление непустой директории или текущей директории.
                                                        // Чтение файла, открытого без флага FA_READ.
                                                        // Любая модификация файла, открытого без флага FA_WRITE.
                                                        // Невозможно создать файл или директорию из-за того, что таблица директорий переполнена.
                                                        // Невозможно создать директорию из-за того, что том переполнен.

char s_err_exist[]              = "EXIST!";             // Уже есть любой объект (файл или папка) с таким же именем.

char s_err_invalid_object[]     = "INVALID OBJECT!";    // Предоставленная структура объекта файла/директории ошибочна.

char s_err_write_protected[]    = "WRITE PROTECTED!";   // Любое действие записи произведено на защищенном от записи носителе данных (write-protected media).

char s_err_invalid_drive[]      = "INVALID DRIVE!";     // Указан недопустимый номер драйва (диска). См. также опцию _VOLUMES.

char s_err_not_enabled[]        = "NOT ENABLED!";       // Рабочая область логического диска не зарегистрирована вызовом функции f_mount.

char s_err_no_filesystem[]      = "NO FILESYSTEM!";     // На диске нет допустимого тома с файловой системой FAT.

char s_err_mkfs_aborted[]       = "MKFS ABORTED!";      // Функция f_mkfs была остановлена (aborted) перед началом форматирования по одной из следующих причин:
                                                        // Размер диска слишком мал.
                                                        // Нет допустимого размера кластера для этого диска. Это может произойти, когда количество кластеров становится близким к значению 0xFF7 и 0xFFF7.


char s_err_timeout[]            = "TIMEOUT!";           // Функция остановлена из-за таймаута в безопасном управлении потоками (thread-safe control). См. также опцию _TIMEOUT.

char s_err_locked[]             = "LOCKED!";            // Доступ к файлу отклонен управлением совместного доступа к файлу (file sharing control). См. также опцию _FS_SHARE.

char s_err_not_enough_core[]    = "NOT ENOUGH_CORE!";   // Недостаточно памяти для выполнения операции. Это произошло по следующим причинам:
                                                        // Нельзя выделить память для рабочего буфера LFN (Long File Name, длинное имя файла). См. также опцию _USE_LFN.
                                                        // Указанный размер таблицы недостаточен.

char s_err_too_many_open_files[]     = "TOO MANY OPEN FILES!";  // Количество открытых файлов достигло максимального значения и больше файлов открыть нельзя. См. также опцию _FS_SHARE.

char s_err_invalid_parameter[]       = "INVALID PARAMETER!";    // казанный параметр недопустим или в параметре имеется любое несоответствие.

extern const MakiseFont F_minecraft_rus_regular_8;

MakiseStyle_SMessageWindow smw = {
    .font               = &F_minecraft_rus_regular_8,
    .font_line_spacing  = 2,

    .bg_color           = MC_White,
    .font_col           = MC_Black,
    .border_color       = MC_Black,
};

void ayplayer_error_microsd_draw ( MContainer* c, FRESULT r, MMessageWindow* mw ) {
    char *s;
    switch ( r ) {
    case FR_DISK_ERR:               s = s_err_disk_err;                 break;
    case FR_INT_ERR:                s = s_err_int_err;                  break;
    case FR_NOT_READY:              s = s_err_not_ready;                break;
    case FR_NO_FILE:                s = s_err_no_file;                  break;
    case FR_NO_PATH:                s = s_err_no_path;                  break;
    case FR_INVALID_NAME:           s = s_err_invalid_name;             break;
    case FR_DENIED:                 s = s_err_denied;                   break;
    case FR_EXIST:                  s = s_err_exist;                    break;
    case FR_INVALID_OBJECT:         s = s_err_invalid_object;           break;
    case FR_WRITE_PROTECTED:        s = s_err_write_protected;          break;
    case FR_INVALID_DRIVE:          s = s_err_invalid_drive;            break;
    case FR_NOT_ENABLED:            s = s_err_not_enabled;              break;
    case FR_NO_FILESYSTEM:          s = s_err_no_filesystem;            break;
    case FR_MKFS_ABORTED:           s = s_err_mkfs_aborted;             break;
    case FR_TIMEOUT:                s = s_err_timeout;                  break;
    case FR_LOCKED:                 s = s_err_locked;                   break;
    case FR_NOT_ENOUGH_CORE:        s = s_err_not_enough_core;          break;
    case FR_TOO_MANY_OPEN_FILES:    s = s_err_too_many_open_files;      break;
    case FR_INVALID_PARAMETER:      s = s_err_invalid_parameter;        break;

    default:
        return;
    }

    m_create_message_window( mw, c, mp_rel( 9, 10, 108, 44 ), s, &smw );
}
