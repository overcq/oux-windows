#include "0.h"
struct E_base_Z *E_base_S;
HANDLE E_base_S_log_file = 0;
void
E_mem_M_blk( void
){  SYSTEM_INFO si;
    GetSystemInfo( &si );
    N page_size = si.dwPageSize;
    N initial_size = E_simple_Z_n_I_align_up_to_v_2( sizeof( *E_base_S ) + sizeof( struct E_mem_Q_blk_Z_mapped ) + sizeof( struct E_mem_Q_blk_Z_free ) + 4 * sizeof( struct E_mem_Q_blk_Z_allocated ), page_size );
    if( !~(N)( E_base_S = VirtualAlloc( 0
    , initial_size
    , MEM_COMMIT
    , PAGE_READWRITE
    )))
    {   V( "VirtualAlloc" );
    }
    E_base_S->E_mem_S_page_size = page_size;
    E_base_S->E_mem_Q_blk_S_table_allocated_id = 2;
    E_base_S->E_mem_Q_blk_S_allocated = (P)( (Pc)E_base_S + sizeof( *E_base_S ) + sizeof( struct E_mem_Q_blk_Z_mapped ) + sizeof( struct E_mem_Q_blk_Z_free ));
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].p = (Pc)E_base_S + sizeof( *E_base_S );
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].u = sizeof( struct E_mem_Q_blk_Z_mapped );
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].n = 1;
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p = (P)( (Pc)E_base_S + sizeof( *E_base_S ) + sizeof( struct E_mem_Q_blk_Z_mapped ));
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].u = sizeof( struct E_mem_Q_blk_Z_free );
    E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n = 1;
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].p = (P)E_base_S->E_mem_Q_blk_S_allocated;
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].u = sizeof( struct E_mem_Q_blk_Z_allocated );
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n = 4;
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id + 1 ].p = (P)E_base_S;
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id + 1 ].u = 1;
    E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id + 1 ].n = sizeof( *E_base_S );
    struct E_mem_Q_blk_Z_mapped *mapped_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].p;
    mapped_p->p = (P)E_base_S;
    mapped_p->l = initial_size;
    struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
    free_p->p = (P)( (Pc)E_base_S->E_mem_Q_blk_S_allocated + E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n * E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].u );
    free_p->l = mapped_p->p + mapped_p->l - free_p->p;
}
void
E_mem_M_file( void
){  E_base_S->E_mem_Q_file_S = E_mem_Q_tab_M( sizeof( struct E_mem_Q_file_Z ), 0 );
    if( !E_base_S->E_mem_Q_file_S )
        V( "E_mem_Q_tab_M" );
    E_base_S->E_mem_Q_file_S_buffer_l = E_base_S->E_mem_S_page_size; //CONF wartość optymalna, ale może być wymagana większa.
    E_base_S->E_mem_Q_file_S_buffer = VirtualAlloc( 0
    , E_base_S->E_mem_Q_file_S_buffer_l
    , MEM_COMMIT
    , PAGE_READWRITE
    );
}
void
E_wnd_M_font( void
){  E_wnd_Q_font_S = E_mem_Q_tab_M( sizeof( struct E_mem_Q_tab_Z ), 1 );
    if( !E_wnd_Q_font_S )
        V( "E_mem_Q_tab_M" );
    struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, 0 );
    font->name = "default";
    font->height = 8;
    font->bitmap_n = 177;
    Mt_( font->bitmap, font->bitmap_n );
    if( !font->bitmap )
        V( "Mt_( font->bitmap" );
    for_n( i, font->bitmap_n )
    {   N8 *bitmap;
        switch(i)
        { case 0:
              font->bitmap[i].u = '_';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 1:
              font->bitmap[i].u = 'A';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 3, 3, 0
              , 3, 1, 1, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 2:
              font->bitmap[i].u = L'Ą';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 3, 3, 0
              , 3, 1, 1, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 0, 0, 1, 2
              , 0, 0, 2, 1
              })[0];
              break;
          case 3:
              font->bitmap[i].u = 'B';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 4:
              font->bitmap[i].u = 'C';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 1, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 5:
              font->bitmap[i].u = L'Ć';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 3
              , 3, 0, 2, 0
              , 3, 0, 2, 0
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 1, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 6:
              font->bitmap[i].u = 'D';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 7:
              font->bitmap[i].u = 'E';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 8:
              font->bitmap[i].u = L'Ę';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 1, 2
              , 0, 0, 2, 0
              })[0];
              break;
          case 9:
              font->bitmap[i].u = 'F';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 10:
              font->bitmap[i].u = 'G';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 3
              , 3, 0, 0, 0
              , 3, 0, 3, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 2
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 11:
              font->bitmap[i].u = 'H';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 12:
              font->bitmap[i].u = 'I';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 3
              , 3
              , 3
              , 3
              , 3
              , 0
              , 0
              })[0];
              break;
          case 13:
              font->bitmap[i].u = 'J';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 3
              , 0, 0, 3
              , 0, 0, 3
              , 0, 0, 3
              , 3, 0, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 14:
              font->bitmap[i].u = 'K';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 3
              , 3, 0, 3, 0
              , 3, 3, 0, 0
              , 3, 3, 0, 0
              , 3, 0, 3, 0
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 15:
              font->bitmap[i].u = 'L';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 0
              , 3, 0, 0
              , 3, 0, 0
              , 3, 0, 0
              , 3, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 16:
              font->bitmap[i].u = L'Ł';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 0
              , 3, 0, 3
              , 2, 3, 0
              , 3, 0, 0
              , 3, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 17:
              font->bitmap[i].u = 'M';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 3, 0, 0, 0, 3
              , 3, 2, 0, 2, 3
              , 3, 3, 1, 3, 3
              , 3, 1, 3, 1, 3
              , 3, 0, 3, 0, 3
              , 3, 0, 0, 0, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 18:
              font->bitmap[i].u = 'N';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 3
              , 3, 2, 0, 3
              , 3, 3, 1, 3
              , 3, 1, 3, 3
              , 3, 0, 2, 3
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 19:
              font->bitmap[i].u = L'Ń';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 3, 2
              , 3, 2, 0, 3
              , 3, 3, 1, 3
              , 3, 1, 3, 3
              , 3, 0, 2, 3
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 20:
              font->bitmap[i].u = 'O';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 21:
              font->bitmap[i].u = L'Ó';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 2, 3
              , 3, 2, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 22:
              font->bitmap[i].u = 'P';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 23:
              font->bitmap[i].u = 'Q';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 2, 0
              , 0, 0, 1, 2
              })[0];
              break;
          case 24:
              font->bitmap[i].u = 'R';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 3, 0, 3, 0
              , 3, 0, 1, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 25:
              font->bitmap[i].u = 'S';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 2
              , 2, 0, 0, 0
              , 1, 3, 0, 0
              , 0, 0, 3, 1
              , 0, 0, 0, 2
              , 2, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 26:
              font->bitmap[i].u = L'Ś';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 2
              , 2, 0, 0, 3
              , 1, 3, 1, 0
              , 0, 0, 3, 1
              , 0, 0, 0, 2
              , 2, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 27:
              font->bitmap[i].u = 'T';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 3, 3
              , 0, 3, 0
              , 0, 3, 0
              , 0, 3, 0
              , 0, 3, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 28:
              font->bitmap[i].u = 'U';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 29:
              font->bitmap[i].u = 'V';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 2, 1, 2
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 30:
              font->bitmap[i].u = 'W';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 3, 0, 0, 0, 3
              , 3, 0, 2, 0, 3
              , 3, 0, 3, 0, 2
              , 3, 0, 3, 0, 3
              , 2, 1, 2, 1, 2
              , 0, 3, 0, 3, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 31:
              font->bitmap[i].u = 'X';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 3
              , 3, 0, 3
              , 0, 3, 0
              , 0, 3, 0
              , 3, 0, 3
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 32:
              font->bitmap[i].u = 'Y';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 3
              , 3, 0, 3
              , 3, 1, 3
              , 0, 3, 0
              , 0, 3, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 33:
              font->bitmap[i].u = 'Z';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 0, 0, 1, 2
              , 0, 0, 3, 0
              , 0, 3, 0, 0
              , 2, 1, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 34:
              font->bitmap[i].u = L'Ź';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 3, 0, 0, 2
              , 2, 0, 3, 0
              , 0, 3, 0, 0
              , 2, 1, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 35:
              font->bitmap[i].u = L'Ż';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 0, 0, 1, 2
              , 2, 1, 3, 0
              , 0, 3, 1, 2
              , 2, 1, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 36:
              font->bitmap[i].u = 'a';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 1, 3, 3, 1
              , 0, 0, 0, 3
              , 1, 3, 3, 3
              , 3, 0, 0, 3
              , 1, 3, 2, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 37:
              font->bitmap[i].u = L'ą';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 1, 3, 3, 1
              , 0, 0, 0, 3
              , 1, 3, 3, 3
              , 3, 0, 0, 3
              , 1, 3, 2, 3
              , 0, 0, 3, 0
              , 0, 0, 2, 3
              })[0];
              break;
          case 38:
              font->bitmap[i].u = 'b';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 0
              , 3, 0, 0, 0
              , 3, 2, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 39:
              font->bitmap[i].u = 'c';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 1, 3, 3
              , 3, 0, 0
              , 3, 0, 0
              , 1, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 40:
              font->bitmap[i].u = L'ć';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 1, 3
              , 0, 3, 0
              , 1, 3, 3
              , 3, 0, 0
              , 3, 0, 0
              , 1, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 41:
              font->bitmap[i].u = 'd';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 3
              , 0, 0, 0, 3
              , 1, 3, 2, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 42:
              font->bitmap[i].u = 'e';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 1, 3, 3, 1
              , 3, 0, 0, 3
              , 2, 3, 3, 2
              , 3, 0, 0, 0
              , 1, 3, 3, 2
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 43:
              font->bitmap[i].u = L'ę';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 1, 3, 3, 1
              , 3, 0, 0, 3
              , 2, 3, 3, 2
              , 3, 0, 0, 0
              , 1, 3, 3, 2
              , 0, 0, 3, 0
              , 0, 0, 2, 3
              })[0];
              break;
          case 44:
              font->bitmap[i].u = 'f';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 2, 3
              , 0, 3, 0
              , 3, 3, 3
              , 0, 3, 0
              , 0, 3, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 45:
              font->bitmap[i].u = 'g';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 1, 3, 3, 2
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 2
              , 0, 0, 0, 3
              , 2, 3, 3, 2
              })[0];
              break;
          case 46:
              font->bitmap[i].u = 'h';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 0
              , 3, 0, 0, 0
              , 2, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 47:
              font->bitmap[i].u = 'i';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 0
              , 3
              , 3
              , 3
              , 3
              , 0
              , 0
              })[0];
              break;
          case 48:
              font->bitmap[i].u = 'j';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 0, 0
              , 0, 3
              , 0, 3
              , 0, 3
              , 0, 3
              , 0, 3
              , 3, 2
              })[0];
              break;
          case 49:
              font->bitmap[i].u = 'k';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 0
              , 3, 0, 0, 3
              , 3, 0, 3, 1
              , 3, 3, 3, 0
              , 3, 0, 1, 2
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 50:
              font->bitmap[i].u = 'l';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 0
              , 3, 0
              , 3, 0
              , 3, 0
              , 3, 0
              , 2, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 51:
              font->bitmap[i].u = L'ł';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 3, 0
              , 0, 3, 3
              , 1, 3, 1
              , 3, 3, 0
              , 0, 3, 0
              , 0, 2, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 52:
              font->bitmap[i].u = 'm';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 3, 3, 2, 3, 2
              , 3, 0, 3, 0, 3
              , 3, 0, 3, 0, 3
              , 3, 0, 3, 0, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 53:
              font->bitmap[i].u = 'n';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 3, 2
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 54:
              font->bitmap[i].u = L'ń';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 1, 3
              , 0, 3, 0
              , 3, 3, 2
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 55:
              font->bitmap[i].u = 'o';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 2, 3, 2
              , 3, 0, 3
              , 3, 0, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 56:
              font->bitmap[i].u = L'ó';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 1, 3
              , 0, 3, 0
              , 2, 3, 2
              , 3, 0, 3
              , 3, 0, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 57:
              font->bitmap[i].u = 'p';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 3, 2, 3, 1
              , 3, 0, 0, 0
              , 3, 0, 0, 0
              })[0];
              break;
          case 58:
              font->bitmap[i].u = 'q';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 1, 3, 3, 3
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 2, 3
              , 0, 0, 0, 3
              , 0, 0, 0, 3
              })[0];
              break;
          case 59:
              font->bitmap[i].u = 'r';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 2, 3
              , 3, 0
              , 3, 0
              , 3, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 60:
              font->bitmap[i].u = 's';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 1, 3, 2
              , 2, 0, 0
              , 1, 3, 1
              , 0, 0, 2
              , 2, 3, 1
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 61:
              font->bitmap[i].u = L'ś';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 3
              , 1, 3, 2
              , 2, 0, 0
              , 1, 3, 1
              , 0, 0, 2
              , 2, 3, 1
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 62:
              font->bitmap[i].u = 't';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 3, 0
              , 0, 3, 0
              , 3, 3, 3
              , 0, 3, 0
              , 0, 3, 0
              , 0, 2, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 63:
              font->bitmap[i].u = 'u';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 2, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 64:
              font->bitmap[i].u = 'v';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 0, 3
              , 3, 0, 3
              , 2, 1, 2
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 65:
              font->bitmap[i].u = 'w';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 3, 0, 2, 0, 2
              , 3, 0, 3, 0, 3
              , 2, 1, 2, 1, 2
              , 0, 3, 0, 3, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 66:
              font->bitmap[i].u = 'x';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 0, 3
              , 0, 3, 0
              , 0, 3, 0
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 67:
              font->bitmap[i].u = 'y';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 0, 3
              , 3, 0, 3
              , 2, 1, 2
              , 0, 3, 0
              , 1, 2, 0
              , 3, 0, 0
              })[0];
              break;
          case 68:
              font->bitmap[i].u = 'z';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 3, 3
              , 0, 2, 1
              , 1, 2, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 69:
              font->bitmap[i].u = L'ź';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 1, 2
              , 0, 2, 0
              , 3, 3, 3
              , 0, 2, 1
              , 1, 2, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 70:
              font->bitmap[i].u = L'ż';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 3, 0
              , 0, 0, 0
              , 3, 3, 3
              , 0, 2, 1
              , 1, 2, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 71:
              font->bitmap[i].u = ' ';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 72:
              font->bitmap[i].u = '0';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 1, 3, 3
              , 3, 3, 1, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 73:
              font->bitmap[i].u = '1';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 3
              , 0, 3, 3
              , 3, 1, 3
              , 1, 0, 3
              , 0, 0, 3
              , 0, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 74:
              font->bitmap[i].u = '2';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 0, 0, 0, 3
              , 0, 0, 3, 0
              , 0, 3, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 75:
              font->bitmap[i].u = '3';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 2, 3, 3, 2
              , 0, 0, 0, 3
              , 0, 3, 3, 2
              , 0, 0, 0, 3
              , 0, 0, 0, 3
              , 2, 3, 3, 2
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 76:
              font->bitmap[i].u = '4';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 3, 2
              , 0, 3, 1, 3
              , 3, 1, 0, 3
              , 2, 3, 3, 3
              , 0, 0, 0, 3
              , 0, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 77:
              font->bitmap[i].u = '5';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 3, 0, 0, 0
              , 2, 3, 3, 1
              , 0, 0, 0, 3
              , 0, 0, 0, 3
              , 2, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 78:
              font->bitmap[i].u = '6';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 1, 2, 3
              , 2, 1, 0, 0
              , 3, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 79:
              font->bitmap[i].u = '7';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 3
              , 0, 0, 1, 2
              , 0, 0, 3, 0
              , 0, 1, 2, 0
              , 0, 3, 0, 0
              , 3, 1, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 80:
              font->bitmap[i].u = '8';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 81:
              font->bitmap[i].u = '9';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 0, 0, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 3
              , 0, 0, 1, 2
              , 3, 2, 1, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 82:
              font->bitmap[i].u = '!';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 3
              , 3
              , 3
              , 0
              , 3
              , 0
              , 0
              })[0];
              break;
          case 83:
              font->bitmap[i].u = '\"';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 3
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 84:
              font->bitmap[i].u = '#';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 3, 0, 3, 0
              , 3, 3, 3, 3, 3
              , 0, 3, 0, 3, 0
              , 0, 3, 0, 3, 0
              , 3, 3, 3, 3, 3
              , 0, 3, 0, 3, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 85:
              font->bitmap[i].u = '$';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 3, 0
              , 1, 3, 2
              , 2, 0, 0
              , 1, 3, 1
              , 0, 0, 2
              , 2, 3, 1
              , 0, 3, 0
              , 0, 0, 0
              })[0];
              break;
          case 86:
              font->bitmap[i].u = '%';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 3, 0, 3
              , 3, 0, 3, 1
              , 2, 0, 3, 0
              , 0, 3, 0, 2
              , 1, 3, 0, 3
              , 3, 0, 3, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 87:
              font->bitmap[i].u = '&';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 1, 0
              , 3, 0, 3, 0
              , 1, 3, 1, 0
              , 3, 0, 1, 3
              , 3, 0, 0, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 88:
              font->bitmap[i].u = '\'';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 3
              , 0
              , 0
              , 0
              , 0
              , 0
              , 0
              })[0];
              break;
          case 89:
              font->bitmap[i].u = '(';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 3, 0
              , 3, 0
              , 3, 0
              , 3, 0
              , 0, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 90:
              font->bitmap[i].u = ')';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 0
              , 0, 3
              , 0, 3
              , 0, 3
              , 0, 3
              , 3, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 91:
              font->bitmap[i].u = '*';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 1, 3, 1
              , 3, 3, 3
              , 1, 3, 1
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 92:
              font->bitmap[i].u = '+';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 3, 0
              , 3, 3, 3
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 93:
              font->bitmap[i].u = ',';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 3
              , 2, 1
              , 0, 0
              })[0];
              break;
          case 94:
              font->bitmap[i].u = '-';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 95:
              font->bitmap[i].u = '.';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 0
              , 0
              , 0
              , 0
              , 0
              , 3
              , 0
              , 0
              })[0];
              break;
          case 96:
              font->bitmap[i].u = '/';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 3
              , 0, 0, 2, 1
              , 0, 0, 3, 0
              , 0, 3, 0, 0
              , 1, 2, 0, 0
              , 3, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 97:
              font->bitmap[i].u = ':';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 0
              , 0
              , 3
              , 0
              , 0
              , 3
              , 0
              , 0
              })[0];
              break;
          case 98:
              font->bitmap[i].u = ';';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 0, 3
              , 0, 0
              , 0, 0
              , 0, 3
              , 2, 1
              , 0, 0
              })[0];
              break;
          case 99:
              font->bitmap[i].u = '<';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 3
              , 0, 3, 0
              , 3, 0, 0
              , 3, 0, 0
              , 0, 3, 0
              , 0, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 100:
              font->bitmap[i].u = '=';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 101:
              font->bitmap[i].u = '>';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 3, 0, 0
              , 0, 3, 0
              , 0, 0, 3
              , 0, 0, 3
              , 0, 3, 0
              , 3, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 102:
              font->bitmap[i].u = '?';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 2, 0, 3
              , 0, 0, 3
              , 0, 3, 0
              , 0, 0, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 103:
              font->bitmap[i].u = '@';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 1, 3, 3, 3, 1
              , 3, 0, 1, 1, 3
              , 3, 0, 2, 2, 3
              , 3, 0, 2, 2, 2
              , 3, 0, 0, 0, 0
              , 1, 3, 3, 3, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 104:
              font->bitmap[i].u = '[';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 3
              , 3, 0
              , 3, 0
              , 3, 0
              , 3, 0
              , 3, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 105:
              font->bitmap[i].u = '\\';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 0, 0
              , 0, 2, 0, 0
              , 0, 3, 0, 0
              , 0, 0, 3, 0
              , 0, 0, 2, 0
              , 0, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 106:
              font->bitmap[i].u = ']';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 3
              , 0, 3
              , 0, 3
              , 0, 3
              , 0, 3
              , 3, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 107:
              font->bitmap[i].u = '^';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 3, 0, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 108:
              font->bitmap[i].u = '`';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 2, 0
              , 1, 3
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 109:
              font->bitmap[i].u = '{';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 2, 1
              , 0, 3, 0
              , 1, 2, 0
              , 3, 2, 0
              , 0, 3, 0
              , 0, 2, 1
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 110:
              font->bitmap[i].u = '|';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 3
              , 3
              , 3
              , 3
              , 3
              , 3
              , 0
              })[0];
              break;
          case 111:
              font->bitmap[i].u = '}';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 2, 0
              , 0, 3, 0
              , 0, 2, 1
              , 0, 2, 3
              , 0, 3, 0
              , 1, 2, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 112:
              font->bitmap[i].u = '~';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 1, 3, 0, 3
              , 3, 0, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 113:
              font->bitmap[i].u = L'′';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 3, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 114:
              font->bitmap[i].u = L'−';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 115:
              font->bitmap[i].u = L'¡';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 0
              , 3
              , 0
              , 3
              , 3
              , 3
              , 3
              , 0
              })[0];
              break;
          case 116:
              font->bitmap[i].u = L'‽';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 2, 2, 3
              , 0, 2, 3
              , 0, 3, 0
              , 0, 0, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 117:
              font->bitmap[i].u = L'²';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 2, 0, 3
              , 0, 3, 0
              , 3, 2, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 118:
              font->bitmap[i].u = L'➪';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 3, 0, 0
              , 3, 3, 3, 3, 0
              , 3, 0, 0, 0, 3
              , 3, 3, 3, 3, 0
              , 0, 0, 3, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 119:
              font->bitmap[i].u = L'³';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 2, 3, 2
              , 0, 0, 3
              , 0, 3, 2
              , 0, 0, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 120:
              font->bitmap[i].u = L'№';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 3, 0, 3, 0, 0
              , 3, 1, 3, 0, 0
              , 3, 3, 3, 2, 3
              , 3, 2, 3, 2, 3
              , 3, 1, 3, 0, 0
              , 3, 0, 3, 2, 2
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 121:
              font->bitmap[i].u = L' ';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 0
              , 0
              , 0
              , 0
              , 0
              , 0
              , 0
              , 0
              })[0];
              break;
          case 122:
              font->bitmap[i].u = L'‒';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 123:
              font->bitmap[i].u = L'⁄';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 2, 3
              , 0, 0, 0, 3, 0
              , 0, 0, 3, 1, 0
              , 0, 1, 3, 0, 0
              , 0, 3, 0, 0, 0
              , 3, 2, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 124:
              font->bitmap[i].u = L'÷';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 3, 0
              , 0, 0, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 125:
              font->bitmap[i].u = L'°';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 3, 0, 3
              , 1, 3, 1
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 126:
              font->bitmap[i].u = L'〃';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 3, 0, 3
              , 0, 3, 0, 3, 0
              , 0, 3, 0, 3, 0
              , 3, 0, 3, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 127:
              font->bitmap[i].u = L'⇢';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 3, 0
              , 3, 0, 3, 3, 3
              , 0, 0, 0, 3, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 128:
              font->bitmap[i].u = L'×';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 3, 0, 0, 3
              , 0, 3, 3, 0
              , 0, 3, 3, 0
              , 3, 0, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 129:
              font->bitmap[i].u = L'⁑';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 1, 3, 1
              , 3, 3, 3
              , 1, 3, 1
              , 1, 3, 1
              , 3, 3, 3
              , 1, 3, 1
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 130:
              font->bitmap[i].u = L'⁂';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 1, 3, 1, 0
              , 0, 3, 3, 3, 0
              , 0, 1, 3, 1, 0
              , 1, 3, 1, 3, 1
              , 3, 3, 3, 3, 3
              , 1, 3, 1, 3, 1
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 131:
              font->bitmap[i].u = L'–';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 3, 3, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 132:
              font->bitmap[i].u = L'—';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 3, 3, 3, 3, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 133:
              font->bitmap[i].u = L'≈';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 1, 3, 1, 3
              , 3, 1, 3, 1
              , 0, 0, 0, 0
              , 1, 3, 1, 3
              , 3, 1, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 134:
              font->bitmap[i].u = L'±';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 3, 0
              , 3, 3, 3
              , 0, 3, 0
              , 3, 3, 3
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 135:
              font->bitmap[i].u = L'⁃';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 2, 2
              , 3, 3
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 136:
              font->bitmap[i].u = L'―';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 3, 3, 3, 3, 3
              , 3, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 137:
              font->bitmap[i].u = L'‣';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 2, 0
              , 3, 3, 3
              , 3, 2, 0
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 138:
              font->bitmap[i].u = L'•';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 2, 3, 2
              , 3, 3, 3
              , 2, 3, 2
              , 0, 0, 0
              , 0, 0, 0
              , 0, 0, 0
              })[0];
              break;
          case 139:
              font->bitmap[i].u = L'®';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 3, 3, 1
              , 3, 1, 2, 3
              , 3, 1, 2, 3
              , 1, 3, 3, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 140:
              font->bitmap[i].u = L'℠';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 3, 2, 0, 3
              , 3, 0, 3, 2, 3
              , 0, 3, 2, 3, 3
              , 3, 0, 3, 0, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 141:
              font->bitmap[i].u = L'©';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 1, 3, 3, 3, 1
              , 3, 1, 2, 0, 3
              , 3, 2, 0, 0, 3
              , 3, 1, 2, 0, 3
              , 1, 3, 3, 3, 1
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 142:
              font->bitmap[i].u = L'™';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 3, 3, 3, 0, 3
              , 0, 3, 2, 2, 3
              , 0, 3, 2, 3, 3
              , 0, 3, 2, 0, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 143:
              font->bitmap[i].u = L'µ';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 3, 0, 3
              , 3, 0, 3
              , 3, 0, 3
              , 2, 3, 3
              , 3, 0, 0
              , 3, 0, 0
              })[0];
              break;
          case 144:
              font->bitmap[i].u = L'❛';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 1, 2
              , 3, 0
              , 3, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 145:
              font->bitmap[i].u = L'❝';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 2, 1, 2
              , 3, 0, 3, 0
              , 3, 0, 3, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 146:
              font->bitmap[i].u = L'❜';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 0, 3
              , 2, 1
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 147:
              font->bitmap[i].u = L'❞';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 3, 0, 3
              , 0, 3, 0, 3
              , 2, 1, 2, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 148:
              font->bitmap[i].u = L'⁅';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 3
              , 3, 0
              , 3, 3
              , 3, 0
              , 3, 0
              , 3, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 149:
              font->bitmap[i].u = L'〈';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 1, 1
              , 3, 0
              , 3, 0
              , 1, 1
              , 0, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 150:
              font->bitmap[i].u = L'⁆';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 3
              , 0, 3
              , 3, 3
              , 0, 3
              , 0, 3
              , 3, 3
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 151:
              font->bitmap[i].u = L'〉';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 0
              , 1, 1
              , 0, 3
              , 0, 3
              , 1, 1
              , 3, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 152:
              font->bitmap[i].u = L' ';
              font->bitmap[i].width = 0;
              break;
          case 153:
              font->bitmap[i].u = L'¦';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 3
              , 1
              , 1
              , 3
              , 3
              , 0
              , 0
              })[0];
              break;
          case 154:
              font->bitmap[i].u = L'‐';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 0, 0
              , 3, 3
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 155:
              font->bitmap[i].u = L'՚';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 3
              , 2
              , 0
              , 0
              , 0
              , 0
              , 0
              , 0
              })[0];
              break;
          case 156:
              font->bitmap[i].u = L'‛';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 3, 0
              , 1, 2
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 157:
              font->bitmap[i].u = L'‟';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 0, 3, 0
              , 1, 2, 1, 2
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 158:
              font->bitmap[i].u = L'‚';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 3
              , 2, 1
              , 0, 0
              })[0];
              break;
          case 159:
              font->bitmap[i].u = L'„';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 3, 0, 3
              , 2, 1, 2, 1
              , 0, 0, 0, 0
              })[0];
              break;
          case 160:
              font->bitmap[i].u = L'‘';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 1, 2
              , 3, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 161:
              font->bitmap[i].u = L'“';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 1, 2, 1, 2
              , 3, 0, 3, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 162:
              font->bitmap[i].u = L'’';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 3
              , 2, 1
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 163:
              font->bitmap[i].u = L'”';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 3, 0, 3
              , 2, 1, 2, 1
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 164:
              font->bitmap[i].u = L'⏎';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 3, 3
              , 0, 3, 0, 3, 3
              , 1, 3, 3, 3, 3
              , 3, 0, 0, 0, 3
              , 1, 3, 3, 3, 3
              , 0, 3, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 165:
              font->bitmap[i].u = L'⁋';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 3, 3, 3, 1
              , 3, 0, 3, 3
              , 3, 0, 3, 1
              , 3, 0, 3, 0
              , 3, 0, 3, 0
              , 3, 0, 3, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 166:
              font->bitmap[i].u = L'✓';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 3
              , 0, 0, 0, 3, 0
              , 0, 0, 0, 2, 0
              , 0, 0, 3, 0, 0
              , 3, 0, 2, 0, 0
              , 0, 3, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 167:
              font->bitmap[i].u = L'·';
              font->bitmap[i].width = 1;
              bitmap = &((N8 [])
              { 0
              , 0
              , 0
              , 3
              , 0
              , 0
              , 0
              , 0
              })[0];
              break;
          case 168:
              font->bitmap[i].u = L'…';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 3, 0, 3, 0, 3
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 169:
              font->bitmap[i].u = L'‹';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 0, 3
              , 3, 0
              , 0, 3
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 170:
              font->bitmap[i].u = L'«';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 3, 0, 3
              , 3, 0, 3, 0
              , 0, 3, 0, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 171:
              font->bitmap[i].u = L'›';
              font->bitmap[i].width = 2;
              bitmap = &((N8 [])
              { 0, 0
              , 0, 0
              , 3, 0
              , 0, 3
              , 3, 0
              , 0, 0
              , 0, 0
              , 0, 0
              })[0];
              break;
          case 172:
              font->bitmap[i].u = L'»';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 0, 0
              , 0, 0, 0, 0
              , 3, 0, 3, 0
              , 0, 3, 0, 3
              , 3, 0, 3, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 173:
              font->bitmap[i].u = L' ';
              font->bitmap[i].width = 5;
              bitmap = &((N8 [])
              { 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              , 0, 0, 0, 0, 0
              })[0];
              break;
          case 174:
              font->bitmap[i].u = L'¿';
              font->bitmap[i].width = 3;
              bitmap = &((N8 [])
              { 0, 0, 0
              , 0, 0, 0
              , 0, 3, 0
              , 0, 0, 0
              , 0, 3, 0
              , 3, 0, 0
              , 3, 0, 2
              , 1, 3, 1
              })[0];
              break;
          case 175:
              font->bitmap[i].u = L'€';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 1, 3, 3
              , 1, 3, 0, 0
              , 3, 2, 2, 0
              , 3, 2, 2, 0
              , 1, 3, 0, 0
              , 0, 1, 3, 3
              , 0, 0, 0, 0
              , 0, 0, 0, 0
              })[0];
              break;
          case 176:
              font->bitmap[i].u = L'¢';
              font->bitmap[i].width = 4;
              bitmap = &((N8 [])
              { 0, 0, 2, 0
              , 0, 3, 3, 3
              , 2, 1, 2, 0
              , 3, 0, 2, 0
              , 2, 1, 2, 0
              , 0, 3, 3, 3
              , 0, 0, 2, 0
              , 0, 0, 0, 0
              })[0];
              break;
        }
        Mt_( font->bitmap[i].bitmap, font->bitmap[i].width * font->height / 4 + ( font->bitmap[i].width * font->height % 4 ? 1 : 0 ));
        if( !font->bitmap[i].bitmap )
            V( "Mt_( font->bitmap[i].bitmap" );
        N8 c;
        N k = 0;
        for_n( j, font->bitmap[i].width * font->height )
        {   if( j % 4 == 0 )
                c = 0;
            c |= bitmap[j] << ( j % 4 * 2 );
            if( j % 4 == 3 )
            {   font->bitmap[i].bitmap[k] = c;
                k++;
            }
        }
        if( j % 4 == 1 || j % 4 == 2 || j % 4 == 3 )
            font->bitmap[i].bitmap[k] = c;
    }
}
void
E_wnd_M_theme( void
){  E_wnd_Q_theme = ( struct E_wnd_Q_theme_Z )
    { .window_bg = E_wnd_Z_color_M( 0xa2, 0xa2, 0xa2 )
    , .object_bg = E_wnd_Z_color_M( 0xca, 0xca, 0xca )
    , .volatile_window_bg = E_wnd_Z_color_M( 0xdf, 0xde, 0xff )
    , .line = E_wnd_Z_color_M( 0x7a, 0x7a, 0x7f )
    , .text = E_wnd_Z_color_M( 0, 0, 0 )
    , .inactive_text = E_wnd_Z_color_M( 0x57, 0x57, 0x57 )
    , .line_numbers = E_wnd_Z_color_M( 0x5f, 0x5f, 0x5f )
    , .current_line_number = E_wnd_Z_color_M( 0x4a, 0x4a, 0x4f )
    , .current_line = E_wnd_Z_color_M( 0xce, 0xce, 0xce )
    , .cursor = E_wnd_Z_color_M( 0xbf, 0x5f, 0 )
    , .current_brace = E_wnd_Z_color_M( 0x2b, 0x5f, 0xff )
    , .search_bg = E_wnd_Z_color_M( 0xc7, 0x9c, 0x9c )
    , .selection_bg = E_wnd_Z_color_M( 0xc4, 0x9c, 0x9c )
    , .line_selection_bg = E_wnd_Z_color_M( 0xb8, 0xb8, 0xb8 )
    , .cursor_jump_bg = E_wnd_Z_color_M( 0xb6, 0xb6, 0xb6 )
    , .code =
      { .comment = E_wnd_Z_color_M( 0x5f, 0x5f, 0x5f )
      , .doc_comment = E_wnd_Z_color_M( 0x2b, 0x37, 0x5f )
      , .label = E_wnd_Z_color_M( 0x5f, 0, 0 )
      , .keyword = E_wnd_Z_color_M( 0, 0, 0x5f )
      , .preprocessor_markup = E_wnd_Z_color_M( 0, 0x2b, 0 )
      , .type = E_wnd_Z_color_M( 0, 0x5f, 0 )
      , .number = E_wnd_Z_color_M( 0x5f, 0, 0x37 )
      , .text = E_wnd_Z_color_M( 0x5f, 0x37, 0 )
      , .character = E_wnd_Z_color_M( 0x5f, 0x37, 0 )
      }
    , .terminal =
      { .bg = E_wnd_Z_color_M( 0, 0, 0 )
      , .text = E_wnd_Z_color_M( 0xee, 0xee, 0xec )
      }
    };
}
void
E_wnd_M( HINSTANCE hInstance
){  E_wnd_M_theme();
    E_wnd_M_font();
    E_wnd_Q_dnd_window_S.object = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_object_Z ), 0 );
    if( !E_wnd_Q_dnd_window_S.object )
        V( "E_mem_Q_tab_M" );
    WNDCLASSEX wc;
    _0_( &wc );
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = E_wnd_I_dnd_wnd_proc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.lpszClassName = "DndWindowClass";
    if( !RegisterClassEx( &wc ))
        V( "RegisterClassEx" );
    U_L( E_wnd_Q_dnd_window_S.state, created );
    E_wnd_Q_dnd_window_S.h = CreateWindowEx( WS_EX_TOPMOST, "DndWindowClass", "DndCaption"
    , WS_POPUP
    , -1, -1
    , 1, 1
    , NULL, NULL
    , hInstance
    , NULL
    );
    if( !E_wnd_Q_dnd_window_S.h )
        V( "CreateWindowEx" );
    HDC dc = GetDC( E_wnd_Q_dnd_window_S.h );
    if( !dc )
        V( "GetDC" );
    E_wnd_Q_dnd_window_S.pixel_width = (F)GetDeviceCaps( dc, HORZSIZE ) / GetDeviceCaps( dc, HORZRES );
    E_wnd_Q_dnd_window_S.pixel_height = (F)GetDeviceCaps( dc, VERTSIZE ) / GetDeviceCaps( dc, VERTRES );
    ReleaseDC( E_wnd_Q_dnd_window_S.h, dc );
    _0_( &wc );
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = E_wnd_I_wnd_proc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION ); /* Load a standard icon */
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION ); /* use the name "A" to use the project icon */
    if( !RegisterClassEx( &wc ))
        V( "RegisterClassEx" );
    E_wnd_Q_window_S = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_window_Z ), 0 );
    if( !E_wnd_Q_window_S )
        V( "E_mem_Q_tab_M" );
}
void
E_base_M( void
){  E_base_S_log_file = CreateFile( "log.txt", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    if( E_base_S_log_file == INVALID_HANDLE_VALUE )
        V( "CreateFile" );
    if( SetFilePointer( E_base_S_log_file, 0, 0, FILE_END ) == INVALID_SET_FILE_POINTER )
        V( "SetFilePointer" );
    E_mem_M_blk();
    E_mem_M_file();
}

