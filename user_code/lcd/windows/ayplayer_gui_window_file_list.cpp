#include "ayplayer_gui_window_file_list.h"

extern const MakiseFont F_minecraft_rus_regular_8;

/*
uint8_t folder_bitmap_data[8] = {
    0b00111111,
    0b01000001,
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b11111111
};

MakiseBitmap folder_bitmap_st = {
    .width_pixel            = 8,
    .height_pixel           = 8,
    .data                   = folder_bitmap_data
};

MakiseStyle_PlayListItem fv_item_st = {
    .font                       = &F_minecraft_rus_regular_8,
    .font_line_spacing          = 0,

    { MC_White, MC_Black, MC_Black, MC_Black, 0 },              // Нормальный.
    { MC_White, MC_Black, MC_Black, MC_Black, 0 },              // Фокус.
    { MC_White, MC_Black, MC_Black, MC_Black, 0 },              // Активен.
};


*/
MakiseStyle_PlayListItem s_pl_item_st = {
    .font                       = &F_minecraft_rus_regular_8,
    .font_line_spacing          = 0,

    { MC_White, MC_Black, MC_Black, 0 },              // Нормальный.
    { MC_White, MC_Black, MC_Black, 0 },              // Фокус.
    { MC_White, MC_Black, MC_Black, 0 },              // Активен.
};

MakiseStyle_PlayList s_pl_st = {
    .font                       = &F_minecraft_rus_regular_8,
    .font_line_spacing          = 0,
    .left_margin                = 0,
    .item_margin                = 0,
    .scroll_width               = 5,
    .scroll_bg_color            = MC_White,
    .scroll_color               = MC_Black,
    .normal                     = { MC_White, MC_Black, MC_Black, 0 },  // Не активен.
    .focused                    = { MC_White, MC_Black, MC_Black, 0 },  // Нормальный.
    .active                     = { MC_White, MC_Black, MC_Black, 0 }   // Фокус.
};

MPlayList_CallbackFunc pl_func_st = {
    .item_selected      = nullptr,
    .item_click         = nullptr,
    .get_file_count_of_dir     = nullptr
};

static char s_file_manager[] = "Выбор трека:";

void ayplayer_gui_window_file_list_creature ( MContainer* c, MPlayList* pl, MPlayList_Item* pl_array, uint32_t array_len, char* dir ) {
    (void)dir;
    m_create_play_list ( pl, c,
                         mp_rel( 0,   0,
                                 128, 64 ),
                         s_file_manager,
                         dir,
                         &pl_func_st,
                         &s_pl_st,
                         &s_pl_item_st );

    m_play_list_set_array ( pl, pl_array, array_len );
  /*  m_create_fsviewer( fv, c,
                       mp_rel( 0,   0,
                               128, 64 ),
                       dir,
                       nullptr,
                       nullptr,
                       MFSViewer_SingleSelect,
                       &fv_st,
                       &fv_item_st );

    fsviewer_open( fv, dir );*/
}
