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
        {   U_F( E_wnd_S_state, draw_object_drag_move );
            PAINTSTRUCT ps;
            E_wnd_Q_dnd_window_S.dc = BeginPaint( E_wnd_Q_dnd_window_S.h, &ps );
            for_each( object_id, E_wnd_Q_dnd_window_S.object, E_mem_Q_tab ) //NDFN zakładana kolejność od na spodzie do na wierzchu. nie wiadomo, czy “_q” jest konieczne.
            {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, object_id );
                object->draw( &E_wnd_Q_dnd_window_S, object ); //NDFN nieprzerysowywanie wszystkich obiektów dla każdej klatki animacji.
            }
            EndPaint( E_wnd_Q_dnd_window_S.h, &ps );
            U_L( E_wnd_S_state, draw_object_drag_move );
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
            RECT rect;
            GetWindowRect( E_wnd_Q_dnd_window_S.h, &rect );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , wp.rcNormalPosition.left + (S16)LOWORD(lParam) + 1
            , wp.rcNormalPosition.top + (S16)HIWORD(lParam) + 1
            , rect.right - rect.left
            , rect.bottom - rect.top
            , TRUE
            );
            break;
        }
      case WM_LBUTTONUP:
        {   MoveWindow( E_wnd_Q_dnd_window_S.h, -1, -1, 1, 1, TRUE );
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_HIDE );
            ReleaseCapture();
            W( E_wnd_S_drag_object_src );
            E_mem_Q_tab_W( E_wnd_Q_dnd_window_S.object );
            U_L( E_wnd_S_mode, drag );
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
            for_n( i, window->width * window->height )
                window->object_mask[i] = ~0;
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
        {   struct E_wnd_Q_window_Z *window;
            for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
            {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                if( window->h == hwnd )
                    break;
            }
            if( !~window->object_mask[ LOWORD(lParam) + window->width * HIWORD(lParam) ] )
                break;
            I parent_object_id = window->object_mask[ LOWORD(lParam) + window->width * HIWORD(lParam) ];
            struct E_wnd_Q_object_Z *parent_object = E_mem_Q_tab_R( window->object, parent_object_id );
            E_wnd_Q_dnd_window_S.object = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_object_Z ), 0 );
            if( !E_wnd_Q_dnd_window_S.object )
                break;
            I dnd_window_object_id = E_wnd_Q_object_M( &E_wnd_Q_dnd_window_S, 0, 0, 0, parent_object->width, parent_object->height, 0, parent_object->draw, 0 );
            struct E_wnd_Q_object_Z *dnd_window_object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, dnd_window_object_id );
            dnd_window_object->data = parent_object->data;
            Mt_( E_wnd_S_drag_object_src, 1 );
            if( !E_wnd_S_drag_object_src )
            {   E_mem_Q_tab_W( E_wnd_Q_dnd_window_S.object );
                break;
            }
            E_wnd_S_drag_object_src[0].window_id = window_id;
            E_wnd_S_drag_object_src[0].object_id = parent_object_id;
            E_wnd_S_drag_object_src_n = 1;
            N child_expanded_n = 0;
            while( child_expanded_n != E_wnd_S_drag_object_src_n )
            {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, E_wnd_S_drag_object_src[ child_expanded_n ].object_id );
                child_expanded_n++;
                if( !object->child_n )
                    continue;
                if( !E_mem_Q_blk_I_append( &E_wnd_S_drag_object_src, object->child_n ))
                {   W( E_wnd_S_drag_object_src );
                    goto Drag_start_error;
                }
                I parent_id = E_wnd_Q_dnd_window_S.object->index_n - 1;
                for_n( i, object->child_n )
                {   struct E_wnd_Q_object_Z *object_src = E_mem_Q_tab_R( window->object, object->child[i] );
                    U_F( object_src->mode, drag_src );
                    E_wnd_S_drag_object_src[ E_wnd_S_drag_object_src_n + i ].window_id = window_id;
                    E_wnd_S_drag_object_src[ E_wnd_S_drag_object_src_n + i ].object_id = object->child[i];
                    I dnd_window_object_id = E_wnd_Q_object_M( &E_wnd_Q_dnd_window_S, 0, object_src->x - parent_object->x, object_src->y - parent_object->y, object_src->width, object_src->height, 0, object_src->draw, 0 );
                    struct E_wnd_Q_object_Z *dnd_window_object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, dnd_window_object_id );
                    parent_object->data = object_src->data;
                    E_wnd_Q_object_I_add( &E_wnd_Q_dnd_window_S, parent_id, dnd_window_object_id );
                }
                E_wnd_S_drag_object_src_n += object->child_n;
            }
            HDC dc = GetDC( E_wnd_Q_dnd_window_S.h );
            E_wnd_Q_dnd_window_S.pixel_width = (F)GetDeviceCaps( dc, HORZSIZE ) / GetDeviceCaps( dc, HORZRES );
            E_wnd_Q_dnd_window_S.pixel_height = (F)GetDeviceCaps( dc, VERTSIZE ) / GetDeviceCaps( dc, VERTRES );
            ReleaseDC( E_wnd_Q_dnd_window_S.h, dc );
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_SHOWNORMAL );
            WINDOWPLACEMENT wp;
            GetWindowPlacement( E_wnd_Q_dnd_window_S.h, &wp );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , wp.rcNormalPosition.left + LOWORD(lParam) + 1
            , wp.rcNormalPosition.top + HIWORD(lParam) + 1
            , parent_object->width, parent_object->height
            , TRUE
            );
            SetCapture( E_wnd_Q_dnd_window_S.h );
            U_F( E_wnd_S_mode, drag );
Drag_start_error:
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

