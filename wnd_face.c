#include "0.h"
struct E_mem_Q_tab_Z *E_wnd_Q_window_S;
struct E_wnd_Q_window_Z E_wnd_Q_dnd_window_S;
struct E_wnd_Q_theme_Z E_wnd_Q_theme;
struct E_wnd_Z_drag_object_src *E_wnd_S_drag_object_src;
N E_wnd_S_drag_object_src_n;
I E_wnd_S_cursor_window = ~0;
I E_wnd_S_cursor_object;
I E_wnd_S_current_object;
B U_R( E_wnd_S_mode, drag ) = no;
B U_R( E_wnd_S_state, draw_object_drag_move ) = no;
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
    Mt_( window->object_mask, width * height );
    if( !window->object_mask )
    {   E_mem_Q_tab_W( window->object );
        E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
        return ~0;
    }
    window->h = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "WindowClass", "Caption"
    , WS_VISIBLE | WS_OVERLAPPEDWINDOW
    , CW_USEDEFAULT, CW_USEDEFAULT
    , width + 1, height + 1
    , NULL, NULL
    , hInstance
    , NULL
    );
    if( !window->h )
    {   W( window->object_mask );
        E_mem_Q_tab_W( window->object );
        E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
        return ~0;
    }
    HDC dc = GetDC( window->h );
    window->pixel_width = (F)GetDeviceCaps( dc, HORZSIZE ) / GetDeviceCaps( dc, HORZRES );
    window->pixel_height = (F)GetDeviceCaps( dc, VERTSIZE ) / GetDeviceCaps( dc, VERTRES );
    ReleaseDC( window->h, dc );
    WINDOWPLACEMENT wp;
    GetWindowPlacement( window->h, &wp );
    MoveWindow( window->h, wp.rcNormalPosition.left, wp.rcNormalPosition.top, width, height, TRUE );
    return window_id;
}
void
E_wnd_Q_window_W( I window_id
){  struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
    DestroyWindow( window->h );
    W( window->object_mask );
    E_mem_Q_tab_W( window->object );
    E_mem_Q_tab_I_rem( E_wnd_Q_window_S, window_id );
}

