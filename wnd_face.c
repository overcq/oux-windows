#include "0.h"
struct E_mem_Q_tab_Z *E_wnd_Q_window_S;
struct E_wnd_Q_window_Z E_wnd_Q_dnd_window_S;
struct E_wnd_Q_window_Z *E_wnd_S_creating_window;
struct E_wnd_Q_theme_Z E_wnd_Q_theme;
struct E_wnd_Z_drag_object_src *E_wnd_S_drag_object_src;
N E_wnd_S_drag_object_src_n;
I E_wnd_S_cursor_window = ~0;
I E_wnd_S_cursor_object;
I E_wnd_S_current_object;
B U_R( E_wnd_S_mode, drag ) = no;
B U_R( E_wnd_S_state, draw_object_drag_move ) = no;
HRGN E_wnd_S_drag_region;
HRGN E_wnd_S_drag_region_window;
HRGN E_wnd_S_drag_region_pixel;
I
E_wnd_Q_window_M( HINSTANCE hInstance
, N16 width
, N16 height
){  I window_id = E_mem_Q_tab_I_add( E_wnd_Q_window_S );
    if( !~window_id )
        return window_id;
    struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
    window->object = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_object_Z ), 0 );
    if( !window->object )
    {   E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
        return ~0;
    }
    E_wnd_S_creating_window = window;
    U_L( window->state, created );
    window->h = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "WindowClass", "Caption"
    , WS_OVERLAPPEDWINDOW
    , CW_USEDEFAULT, CW_USEDEFAULT
    , width, height
    , NULL, NULL
    , hInstance
    , NULL
    );
    if( !window->h )
    {   E_mem_Q_tab_W( window->object );
        E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
        return ~0;
    }
    ShowWindow( window->h, SW_SHOWDEFAULT );
    return window_id;
}
void
E_wnd_Q_window_W( I window_id
){  struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
    DeleteObject( window->drawable );
    DeleteDC( window->drawable_dc );
    DestroyWindow( window->h );
    W( window->object_mask );
    E_mem_Q_tab_W( window->object );
    E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
}

