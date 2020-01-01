#include <windows.h>
#include <commctrl.h>
#include <math.h>
#include "1.h"
#include "2.h"
#include "simple.h"
struct E_base_Z
{ HANDLE E_mem_Q_blk_S_threads_sync_mutex;
  N E_mem_S_page_size;
  struct E_mem_Q_blk_Z_allocated *E_mem_Q_blk_S_allocated;
  N E_mem_Q_blk_S_table_allocated_id;
  struct E_mem_Q_tab_Z *E_mem_Q_file_S;
  Pc E_mem_Q_file_S_buffer;
  N E_mem_Q_file_S_buffer_l;
  unsigned U_R( E_flow_S_signal, exit_all )             :1;
};
#include "M.h"
#define E_mem_Q_blk_S_allocated_S_mapped_id ( E_base_S->E_mem_Q_blk_S_table_allocated_id - 2 )
#define E_mem_Q_blk_S_allocated_S_free_id   ( E_base_S->E_mem_Q_blk_S_table_allocated_id - 1 )
struct E_mem_Q_blk_Z_mapped ///obszary stron pamięci otrzymane z systemu operacyjnego.
{ Pc p; ///“0” tutaj i w “l” oznacza pusty wpis; ale wystarczy sprawdzić jedno.
  N l;
};
struct E_mem_Q_blk_Z_free ///dla optymalizacji wyszukiwania obszaru nowej ‘alokacji’.
{ Pc p; ///“0” tutaj i w “l” oznacza pusty wpis; ale wystarczy sprawdzić jedno.
  N l;
};
struct E_mem_Q_blk_Z_allocated ///dla kontroli poprawności wydawania i oddawania ‘alokacji’.
{ Pc p; ///“0” oznacza pusty wpis.
  N u; ///‘unit’
  N n; ///w niepustym wpisie— “0” oznacza ‛zerowy wpis’.
};
#include "mem_blk.h"
struct E_mem_Q_tab_Z
{ Pc *index; ///tablica mapowania indeksów do adresów w “data”.
  Pc data; ///dane ciągłe.
  N u; ///rozmiar elementu tablicy.
  struct E_mem_Q_tab_Z *iterator;
  I index_n;
  I data_n;
};
struct E_mem_Q_tab_S_iterator_Z
{ I *index; ///dowolna sekwencja ‹identyfikatorów› (indeksów) danych, ale bez powtórzeń.
  I n;
};
#include "mem_tab.h"
struct E_flow_Z_args
{ N argc;
  Pc *argv;
};
#include "text.h"
struct E_mem_Q_rel_map_blk_Z
{ N pos;
  N l;
  Pc data;
};
struct E_mem_Z_range
{ N pos;
  N pos_end;
};
struct E_mem_Q_file_Z
{ struct E_mem_Q_rel_map_blk_Z *blk; ///tablica bloków danych wczytanych uporządkowana wg pozycji danych w pliku.
  N blk_n;
  struct E_mem_Z_range *unsaved; ///tablica zakresów danych nie zapisanych uporządkowana wg pozycji danych w pliku.
  N unsaved_n;
  N pos;
  N current_blk;
  N current_blk_pos;
  HANDLE fd;
  N l;
  N st_mode;
  unsigned U_R( current_blk, valid )    :1;
  unsigned U_R( current_blk, valid_sob ):1;
  unsigned U_R( current_blk, valid_eob ):1;
};
#include "mem_file.h"
struct E_wnd_Q_window_Z
{ struct E_mem_Q_tab_Z *object;
  HWND h;
  I *object_mask;
  F pixel_width, pixel_height;
  N16 width, height;
  HDC dc;
};
#include "wnd_face.h"
struct E_wnd_Q_object_Z;
typedef
void
(*draw_object_proc)(
  struct E_wnd_Q_window_Z *
, struct E_wnd_Q_object_Z *
);
typedef
void
(*click_object_proc)(
  struct E_wnd_Q_window_Z *
, struct E_wnd_Q_object_Z *
, N8
, N8
);
struct E_wnd_Q_object_Z
{ draw_object_proc draw; ///ale obiekt zawiera punkty, które narysuje ta funkcja w czasie wywołania.
  click_object_proc click;
  void
  (*clear_data)(P);
  N child_n;
  I *child;
  P data;
  S16 x, y;
  N16 width, height; ///prostokąt oczekiwanej widoczności obiektu.
  unsigned U_R( mode, lay_height ):1;
  unsigned U_R( mode, draggable ) :1;
  unsigned U_R( mode, drag_src )  :1;
};
struct E_wnd_Q_object_Z_data_Z_entry
{ I font;
  Pc text;
  N text_start;
  N cursor_pos;
  unsigned U_R( state, visible )  :1;
};
#include "wnd_obj.h"
struct E_wnd_Q_theme_Z
{ N32 window_bg, object_bg, volatile_window_bg;
  N32 line, text, inactive_text;
  N32 line_numbers, current_line_number, current_line;
  N32 cursor, current_brace;
  N32 search_bg, selection_bg, line_selection_bg, cursor_jump_bg;
  struct
  { N32 comment, doc_comment;
    N32 label, keyword, preprocessor_markup;
    N32 type, number, text, character;
  }code;
  struct
  { N32 bg, text;
  }terminal;
};
struct E_wnd_Q_font_Z_bitmap
{ U u;
  N width;
  N16 *bitmap;
};
struct E_wnd_Q_font_Z
{ Pc name;
  N height;
  N bitmap_n;
  struct E_wnd_Q_font_Z_bitmap *bitmap;
};
struct E_wnd_Q_object_Z_data_Z_font
{ I font;
  Pc label;
};
#include "wnd_font.h"
enum E_wnd_Z_aa_pixel
{ Z_aa_pixel_S_e = 1 << 0,
  Z_aa_pixel_S_se = 1 << 1,
  Z_aa_pixel_S_s = 1 << 2,
  Z_aa_pixel_S_sw = 1 << 3,
  Z_aa_pixel_S_w = 1 << 4,
  Z_aa_pixel_S_nw = 1 << 5,
  Z_aa_pixel_S_n = 1 << 6,
  Z_aa_pixel_S_ne = 1 << 7
};
struct E_wnd_Z_points
{ F x, y;
};
#include "wnd_draw.h"
#include "wnd_drv.h"
#include "main.h"

