#include "0.h"
LRESULT CALLBACK E_wnd_I_dnd_wnd_proc( HWND hwnd
, UINT Message
, WPARAM wParam
, LPARAM lParam
){  switch(Message)
    { case WM_CREATE:
        {   RECT rectangle;
            GetClientRect( E_wnd_Q_dnd_window_S.h, &rectangle );
            E_wnd_Q_dnd_window_S.width = rectangle.right;
            E_wnd_Q_dnd_window_S.height = rectangle.bottom;
        }
      case WM_PAINT:
        {   PAINTSTRUCT ps;
            E_wnd_Q_dnd_window_S.dc = BeginPaint( E_wnd_Q_dnd_window_S.h, &ps );
            for_each( object_id, E_wnd_Q_dnd_window_S.object, E_mem_Q_tab ) //NDFN zakładana kolejność od na spodzie do na wierzchu. nie wiadomo, czy “_q” jest konieczne.
            {   E_wnd_S_current_object = object_id;
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, object_id );
                object->draw( &E_wnd_Q_dnd_window_S, object ); //NDFN nieprzerysowywanie wszystkich obiektów dla każdej klatki animacji.
            }
            EndPaint( E_wnd_Q_dnd_window_S.h, &ps );
            break;
        }
      case WM_SIZE:
        {   RECT rectangle;
            GetClientRect( E_wnd_Q_dnd_window_S.h, &rectangle );
            E_wnd_Q_dnd_window_S.width = rectangle.right;
            E_wnd_Q_dnd_window_S.height = rectangle.bottom;
            E_wnd_Q_object_I_lay( &E_wnd_Q_dnd_window_S );
            break;
        }
      case WM_MOUSEMOVE:
        {   WINDOWPLACEMENT wp;
            GetWindowPlacement( E_wnd_Q_dnd_window_S.h, &wp );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , ( wp.showCmd == SW_SHOWNORMAL ? wp.rcNormalPosition.left : wp.ptMaxPosition.x ) + LOWORD(lParam) - 25
            , ( wp.showCmd == SW_SHOWNORMAL ? wp.rcNormalPosition.top : wp.ptMaxPosition.x ) + HIWORD(lParam) - 25
            , 50, 50
            , TRUE
            );
            break;
        }
      case WM_LBUTTONUP:
        {   MoveWindow( E_wnd_Q_dnd_window_S.h, -1, -1, 1, 1, TRUE );
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_HIDE );
            ReleaseCapture();
            E_mem_Q_tab_W( E_wnd_Q_dnd_window_S.object );
            break;
        }
      case WM_DESTROY:
        {   PostQuitMessage(0);
            break;
        }
      default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK E_wnd_I_wnd_proc( HWND hwnd
, UINT Message
, WPARAM wParam
, LPARAM lParam
){  switch(Message)
    { case WM_CREATE:
        {   struct E_wnd_Q_window_Z *window;
            for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
            {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                if( window->h == hwnd )
                    break;
            }
            RECT rectangle;
            GetClientRect( window->h, &rectangle );
            window->width = rectangle.right;
            window->height = rectangle.bottom;
            Mt_( window->object_mask, window->width * window->height );
            if( !window->object_mask )
                return -1;
        }
      case WM_PAINT:
        {   struct E_wnd_Q_window_Z *window;
            for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
            {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                if( window->h == hwnd )
                    break;
            }
            PAINTSTRUCT ps;
            window->dc = BeginPaint( window->h, &ps );
            for_each( object_id, window->object, E_mem_Q_tab ) //NDFN zakładana kolejność od na spodzie do na wierzchu. nie wiadomo, czy “_q” jest konieczne.
            {   E_wnd_S_current_object = object_id;
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
                if( U_R( object->mode, drag_src ))
                {   N32 color = E_wnd_Q_theme.current_brace;
                    if( E_wnd_S_draw_color != color )
                        E_wnd_S_draw_color = color;
                }
                object->draw( window, object ); //NDFN nieprzerysowywanie wszystkich obiektów dla każdej klatki animacji.
            }
            EndPaint( window->h, &ps );
            break;
        }
      case WM_SIZE:
        {   struct E_wnd_Q_window_Z *window;
            for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
            {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                if( window->h == hwnd )
                    break;
            }
            if( wParam == SIZE_MINIMIZED )
                break;
            RECT rectangle;
            GetClientRect( window->h, &rectangle );
            window->width = rectangle.right;
            window->height = rectangle.bottom;
            W( window->object_mask );
            Mt_( window->object_mask, window->width * window->height );
            if( !window->object_mask )
                V();
            E_wnd_Q_object_I_lay(window);
            break;
        }
      case WM_LBUTTONDOWN:
        {   E_wnd_Q_dnd_window_S.object = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_object_Z ), 0 );
            if( !E_wnd_Q_dnd_window_S.object )
                break;
            HDC dc = GetDC( E_wnd_Q_dnd_window_S.h );
            E_wnd_Q_dnd_window_S.pixel_width = (F)GetDeviceCaps( dc, HORZSIZE ) / GetDeviceCaps( dc, HORZRES );
            E_wnd_Q_dnd_window_S.pixel_height = (F)GetDeviceCaps( dc, VERTSIZE ) / GetDeviceCaps( dc, VERTRES );
            ReleaseDC( E_wnd_Q_dnd_window_S.h, dc );
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_SHOWNORMAL );
            WINDOWPLACEMENT wp;
            GetWindowPlacement( E_wnd_Q_dnd_window_S.h, &wp );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , ( wp.showCmd == SW_SHOWNORMAL ? wp.rcNormalPosition.left : wp.ptMaxPosition.x ) + LOWORD(lParam) - 25
            , ( wp.showCmd == SW_SHOWNORMAL ? wp.rcNormalPosition.top : wp.ptMaxPosition.x ) + HIWORD(lParam) - 25
            , 50, 50
            , TRUE
            );
            SetCapture( E_wnd_Q_dnd_window_S.h );
            break;
        }
      case WM_DESTROY:
        {   PostQuitMessage(0);
            break;
        }
      default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
D( wnd_window, cursor )
{   struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, E_wnd_S_cursor_window );
    struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, E_wnd_S_cursor_object );
    struct E_wnd_Q_object_Z_data_Z_entry *object_data = object->data;
    U_L( object_data->state, visible );
    Y_M( wnd_window, cursor, 360 );
    I_D
    {   N lost_count;
        Y_B( wnd_window, cursor );
        if( lost_count % 2 )
            continue;
        B U_L( wnd_object, draw );
        if( !~E_wnd_S_cursor_window )
            continue;
        struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, E_wnd_S_cursor_window );
        struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, E_wnd_S_cursor_object );
        struct E_wnd_Q_object_Z_data_Z_entry *object_data = object->data;
        U_R( object_data->state, visible ) = !U_R( object_data->state, visible );
        E_wnd_Q_object_I_draw(object);
    }
    Y_W( wnd_window, cursor );
}

