#include "0.h"
N E_wnd_S_drag_pointer_dx = 4, E_wnd_S_drag_pointer_dy = 4;
LRESULT CALLBACK E_wnd_I_dnd_wnd_proc( HWND hwnd
, UINT Message
, WPARAM wParam
, LPARAM lParam
){  switch(Message)
    { case WM_PAINT:
        {   SetWindowRgn( E_wnd_Q_dnd_window_S.h, E_wnd_S_drag_region_window, FALSE );
            DeleteObject( E_wnd_S_drag_region );
            E_wnd_S_drag_region = CreateRectRgn( 0, 0, 0, 0 );
            if( !E_wnd_S_drag_region )
                V( "CreateRectRgn" );
            U_F( E_wnd_S_state, draw_object_drag_move );
            for_each( object_id, E_wnd_Q_dnd_window_S.object, E_mem_Q_tab ) //NDFN zakładana kolejność od na spodzie do na wierzchu. nie wiadomo, czy “_q” jest konieczne.
            {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, object_id );
                object->draw( &E_wnd_Q_dnd_window_S, object ); //NDFN nieprzerysowywanie wszystkich obiektów dla każdej klatki animacji.
            }
            U_L( E_wnd_S_state, draw_object_drag_move );
            SetWindowRgn( E_wnd_Q_dnd_window_S.h, E_wnd_S_drag_region, TRUE );
            PAINTSTRUCT ps;
            HDC dc = BeginPaint( E_wnd_Q_dnd_window_S.h, &ps );
            BitBlt( dc, 0, 0, E_wnd_Q_dnd_window_S.width, E_wnd_Q_dnd_window_S.height, E_wnd_Q_dnd_window_S.drawable_dc, 0, 0, SRCCOPY );
            EndPaint( E_wnd_Q_dnd_window_S.h, &ps );
            break;
        }
      case WM_SIZE:
        {   E_wnd_Q_dnd_window_S.width = LOWORD(lParam);
            E_wnd_Q_dnd_window_S.height = HIWORD(lParam);
            if( U_R( E_wnd_Q_dnd_window_S.state, created ))
                DeleteObject( E_wnd_S_drag_region_window );
            E_wnd_S_drag_region_window = CreateRectRgn( 0, 0, E_wnd_Q_dnd_window_S.width, E_wnd_Q_dnd_window_S.height );
            if( !E_wnd_S_drag_region_window )
                V( "CreateRectRgn" );
            HDC dc = GetDC( E_wnd_Q_dnd_window_S.h );
            if( !dc )
                V( "GetDC" );
            if( !U_R( E_wnd_Q_dnd_window_S.state, created ))
            {   E_wnd_S_drag_region = CreateRectRgn( 0, 0, 0, 0 );
                if( !E_wnd_S_drag_region )
                    V( "CreateRectRgn" );
                E_wnd_S_drag_region_pixel = CreateRectRgn( 0, 0, 1, 1 );
                if( !E_wnd_S_drag_region_pixel )
                    V( "CreateRectRgn" );
                E_wnd_Q_dnd_window_S.drawable_dc = CreateCompatibleDC(dc);
            }
            if( U_R( E_wnd_Q_dnd_window_S.state, created ))
            {   if( !SelectObject( E_wnd_Q_dnd_window_S.drawable_dc, E_wnd_Q_dnd_window_S.default_drawable ))
                    V( "SelectObject" );
                DeleteObject( E_wnd_Q_dnd_window_S.drawable );
            }
            E_wnd_Q_dnd_window_S.drawable = CreateCompatibleBitmap( dc, E_wnd_Q_dnd_window_S.width, E_wnd_Q_dnd_window_S.height );
            ReleaseDC( E_wnd_Q_dnd_window_S.h, dc );
            if( !E_wnd_Q_dnd_window_S.drawable )
                V( "CreateCompatibleBitmap" );
            E_wnd_Q_dnd_window_S.default_drawable = SelectObject( E_wnd_Q_dnd_window_S.drawable_dc, E_wnd_Q_dnd_window_S.drawable );
            if( !E_wnd_Q_dnd_window_S.default_drawable )
                V( "SelectObject" );
            if( !U_R( E_wnd_Q_dnd_window_S.state, created ))
                U_F( E_wnd_Q_dnd_window_S.state, created );
            break;
        }
      case WM_SHOWWINDOW:
            if( wParam )
                break;
            DeleteObject( E_wnd_S_drag_region_window );
            DeleteObject( E_wnd_S_drag_region );
            DeleteObject( E_wnd_S_drag_region_pixel );
            DeleteDC( E_wnd_Q_dnd_window_S.drawable_dc );
            DeleteObject( E_wnd_Q_dnd_window_S.drawable );
            U_L( E_wnd_Q_dnd_window_S.state, created );
            break;
      case WM_MOUSEMOVE:
        {   WINDOWPLACEMENT wp;
            GetWindowPlacement( E_wnd_Q_dnd_window_S.h, &wp );
            RECT rect;
            GetWindowRect( E_wnd_Q_dnd_window_S.h, &rect );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , wp.rcNormalPosition.left + (S16)LOWORD(lParam) + E_wnd_S_drag_pointer_dx
            , wp.rcNormalPosition.top + (S16)HIWORD(lParam) + E_wnd_S_drag_pointer_dy
            , rect.right - rect.left
            , rect.bottom - rect.top
            , TRUE
            );
            break;
        }
      case WM_LBUTTONUP:
Drag_error:
        {   ReleaseCapture();
            MoveWindow( E_wnd_Q_dnd_window_S.h, -1, -1, 1, 1, TRUE );
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_HIDE );
            for_n( i, E_wnd_S_drag_object_src_n )
            {   struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, E_wnd_S_drag_object_src[i].window_id );
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, E_wnd_S_drag_object_src[i].object_id );
                U_L( object->mode, drag_src );
                RECT rectangle =
                { object->x, object->y
                , object->x + object->width, object->y + object->height
                };
                InvalidateRect( window->h, &rectangle, TRUE );
            }
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
    { case WM_PAINT:
        {   struct E_wnd_Q_window_Z *window;
            for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
            {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                if( window->h == hwnd )
                    break;
            }
            for_n( i, window->width * window->height )
                window->object_mask[i] = ~0;
            RECT rectangle = { 0, 0, window->width, window->height };
            FillRect( window->drawable_dc, &rectangle, window->background_brush );
            for_each( object_id, window->object, E_mem_Q_tab ) //NDFN zakładana kolejność od na spodzie do na wierzchu. nie wiadomo, czy “_q” jest konieczne.
            {   E_wnd_S_current_object = object_id;
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
                if( U_R( object->mode, drag_src ))
                    E_wnd_S_draw_color = E_wnd_Q_theme.current_brace;
                object->draw( window, object ); //NDFN nieprzerysowywanie wszystkich obiektów dla każdej klatki animacji.
            }
            PAINTSTRUCT ps;
            HDC dc = BeginPaint( window->h, &ps );
            BitBlt( dc, 0, 0, window->width, window->height, window->drawable_dc, 0, 0, SRCCOPY );
            EndPaint( window->h, &ps );
            break;
        }
      case WM_SIZE:
        {   if( wParam == SIZE_MINIMIZED )
                break;
            struct E_wnd_Q_window_Z *window = E_wnd_S_creating_window;
            if( U_R( window->state, created ))
            {   for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
                {   window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
                    if( window->h == hwnd )
                        break;
                }
            }
            B size_changed;
            if( !U_R( window->state, created )
            || window->width != LOWORD(lParam)
            || window->height != HIWORD(lParam)
            )
            {   size_changed = yes;
                window->width = LOWORD(lParam);
                window->height = HIWORD(lParam);
                if( U_R( window->state, created ))
                    W( window->object_mask );
                Mt_( window->object_mask, window->width * window->height );
                if( !window->object_mask )
                    V( "Mt_( window->object_mask" );
            }else
               size_changed = no; 
            HDC dc = GetDC( window->h );
            if( !dc )
                V( "GetDC" );
            if( !U_R( window->state, created ))
            {   window->pixel_width = (F)GetDeviceCaps( dc, HORZSIZE ) / GetDeviceCaps( dc, HORZRES );
                window->pixel_height = (F)GetDeviceCaps( dc, VERTSIZE ) / GetDeviceCaps( dc, VERTRES );
                window->drawable_dc = CreateCompatibleDC(dc);
            }
            if( size_changed )
            {   if( U_R( window->state, created ))
                {   if( !SelectObject( window->drawable_dc, window->default_drawable ))
                        V( "SelectObject" );
                    DeleteObject( window->drawable );
                }
                window->drawable = CreateCompatibleBitmap( dc, window->width, window->height );
                if( !window->drawable )
                    V( "CreateCompatibleBitmap" );
                window->default_drawable = SelectObject( window->drawable_dc, window->drawable );
                if( !window->default_drawable )
                    V( "SelectObject" );
                E_wnd_Q_object_I_lay(window);
                RECT rectangle =
                { 0, 0
                , window->width, window->height
                };
                InvalidateRect( window->h, &rectangle, TRUE );
            }
            ReleaseDC( window->h, dc );
            if( !U_R( window->state, created ))
            {   window->background_brush = CreateSolidBrush( E_wnd_Q_theme.window_bg );
                if( !window->background_brush )
                    V( "CreateSolidBrush" );
                U_F( window->state, created );
            }
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
            U_F( parent_object->mode, drag_src );
            RECT rectangle =
            { parent_object->x, parent_object->y
            , parent_object->x + parent_object->width, parent_object->y + parent_object->height
            };
            InvalidateRect( window->h, &rectangle, TRUE );
            E_wnd_Q_dnd_window_S.object = E_mem_Q_tab_M( sizeof( struct E_wnd_Q_object_Z ), 0 );
            if( !E_wnd_Q_dnd_window_S.object )
                break;
            I dnd_window_object_id = E_wnd_Q_object_M( &E_wnd_Q_dnd_window_S, 0, 0, 0, parent_object->width, parent_object->height, 0, parent_object->draw, 0 );
            if( !~dnd_window_object_id )
            {   E_mem_Q_tab_W( E_wnd_Q_dnd_window_S.object );
                break;
            }
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
                    if( !~dnd_window_object_id )
                    {   W( E_wnd_S_drag_object_src );
                        for_each( object_id, E_wnd_Q_dnd_window_S.object, E_mem_Q_tab )
                            E_wnd_Q_object_W( &E_wnd_Q_dnd_window_S, object_id );
                        goto Drag_start_error;
                    }
                    struct E_wnd_Q_object_Z *dnd_window_object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, dnd_window_object_id );
                    dnd_window_object->data = object_src->data;
                    E_wnd_Q_object_I_add( &E_wnd_Q_dnd_window_S, parent_id, dnd_window_object_id );
                }
                E_wnd_S_drag_object_src_n += object->child_n;
            }
            ShowWindow( E_wnd_Q_dnd_window_S.h, SW_SHOWNOACTIVATE );
            WINDOWPLACEMENT wp;
            GetWindowPlacement( window->h, &wp );
            MoveWindow( E_wnd_Q_dnd_window_S.h
            , wp.rcNormalPosition.left + LOWORD(lParam) + E_wnd_S_drag_pointer_dx
            , wp.rcNormalPosition.top + HIWORD(lParam) + E_wnd_S_drag_pointer_dy
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

