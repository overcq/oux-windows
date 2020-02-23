#include "0.h"
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance
, LPSTR lpCmdLine
, int nCmdShow
){  E_base_M();
    E_wnd_M(hInstance);
    N l = GetCurrentDirectory( 0, 0 );
    if( !l )
        V( "GetCurrentDirectory" );
    Pc current_dir = M( l + 2 );
    if( GetCurrentDirectory( l, current_dir ) != l - 1 )
        V( "GetCurrentDirectory" );
    l += 2;
    current_dir[ l - 3 ] = '\\';
    current_dir[ l - 2 ] = '*';
    current_dir[ l - 1 ] = '\0';
    for_n( i, 2 )
    {   N window_id = E_wnd_Q_window_M( hInstance
        , 450, 500
        );
        if( !~window_id )
            V( "E_wnd_Q_window_M" );
        struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
        SetWindowText( window->h, current_dir );
        WIN32_FIND_DATA fd;
        HANDLE find_handle = FindFirstFile( current_dir, &fd );
        if( find_handle == INVALID_HANDLE_VALUE )
            V( "FindFirstFile" );
        I root_frame_id = E_wnd_Q_object_Z_frame_M(window);
        if( !~root_frame_id )
            V( "E_wnd_Q_object_Z_frame_M" );
        O{ if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
                if( !~frame_id )
                    V( "E_wnd_Q_object_Z_frame_M" );
                if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                    V( "E_wnd_Q_object_I_add" );
                I dir_id = E_wnd_Q_object_Z_button_M(window);
                if( !~dir_id )
                    V( "E_wnd_Q_object_Z_button_M" );
                if( !~E_wnd_Q_object_I_add( window, frame_id, dir_id ))
                    V( "E_wnd_Q_object_I_add" );
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, dir_id );
                object->click = dir_click;
                Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
                if( !s )
                    V( "M" );
                E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, current_dir, l - 2 ), fd.cFileName );
                object->data = s;
                Pc dir_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
                if( !dir_utf8 )
                    V( "E_text_Z_s_Z_ansi_R_utf8" );
                I font_id = E_wnd_Q_object_Z_font_M( window, 0, dir_utf8 );
                if( !~font_id )
                    V( "E_wnd_Q_object_Z_font_M" );
                if( !~E_wnd_Q_object_I_add( window, dir_id, font_id ))
                    V( "E_wnd_Q_object_I_add" );
            }
            if( !FindNextFile( find_handle, &fd ))
            {   if( GetLastError() == ERROR_NO_MORE_FILES )
                    break;
                V( "FindNextFile" );
            }
        }
        if( !FindClose( find_handle ))
            V( "FindClose" );
        find_handle = FindFirstFile( current_dir, &fd );
        if( find_handle == INVALID_HANDLE_VALUE )
            V( "FindFirstFile" );
        O{ if( !( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
            {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
                if( !~frame_id )
                    V( "E_wnd_Q_object_Z_frame_M" );
                if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                    V( "E_wnd_Q_object_I_add" );
                I file_id = E_wnd_Q_object_Z_button_M(window);
                if( !~file_id )
                    V( "E_wnd_Q_object_Z_button_M" );
                if( !~E_wnd_Q_object_I_add( window, frame_id, file_id ))
                    V( "E_wnd_Q_object_I_add" );
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, file_id );
                object->click = file_click;
                Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
                if( !s )
                    V( "M" );
                E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, current_dir, l - 2 ), fd.cFileName );
                object->data = s;
                Pc file_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
                if( !file_utf8 )
                    V( "E_text_Z_s_Z_ansi_R_utf8" );
                I font_id = E_wnd_Q_object_Z_font_M( window, 0, file_utf8 );
                if( !~font_id )
                    V( "E_wnd_Q_object_Z_font_M" );
                if( !~E_wnd_Q_object_I_add( window, file_id, font_id ))
                    V( "E_wnd_Q_object_I_add" );
            }
            if( !FindNextFile( find_handle, &fd ))
            {   if( GetLastError() == ERROR_NO_MORE_FILES )
                    break;
                V( "FindNextFile" );
            }
        }
        if( !FindClose( find_handle ))
            V( "FindClose" );
        E_wnd_Q_object_I_lay(window);
    }
    W( current_dir );
    MSG msg;
    while( GetMessage( &msg, NULL, 0, 0 ) > 0 )   /* If no error is received... */
    {   TranslateMessage( &msg ); /* Translate key codes to chars if present */
        DispatchMessage( &msg ); /* Send it to WndProc */
    }
    return msg.wParam;
}
void
dir_click(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N8 button
, N8 sequence
){  Pc file = E_text_Z_s0_R_search_last_c( object->data, '\\' ) + 1;
    if( E_text_Z_s0_T_eq( file, "." ))
        return;
    Pc dir;
    N l;
    if( E_text_Z_s0_T_eq( file, ".." ))
    {   Pc parent_dir_ = E_text_Z_s_R_search_last_c( object->data, file - 1, '\\' );
        if( parent_dir_ == object->data )
            return;
        l = parent_dir_ - (Pc)object->data + 3;
        dir = M(l);
        E_text_Z_s_P_copy_( dir, object->data, parent_dir_ );
    }else
    {   l = E_text_Z_s0_R_l( object->data ) + 3;
        dir = M(l);
        E_text_Z_s0_P_copy( dir, object->data );
    }
    dir[ l - 3 ] = '\\';
    dir[ l - 2 ] = '*';
    dir[ l - 1 ] = '\0';
    WIN32_FIND_DATA fd;
    HANDLE find_handle = FindFirstFile( dir, &fd );
    if( find_handle == INVALID_HANDLE_VALUE )
    {   W(dir);
        MessageBox( window->h, "FindFirstFile", "err", MB_OK );
        return;
    }
    for_each_rev( object_id, window->object, E_mem_Q_tab )
        E_wnd_Q_object_W( window, object_id );
    I root_frame_id = E_wnd_Q_object_Z_frame_M(window);
    if( !~root_frame_id )
        V( "E_wnd_Q_object_Z_frame_M" );
    O{ if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
            if( !~frame_id )
                V( "E_wnd_Q_object_Z_frame_M" );
            if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                V( "E_wnd_Q_object_I_add" );
            I dir_id = E_wnd_Q_object_Z_button_M(window);
            if( !~dir_id )
                V( "E_wnd_Q_object_Z_button_M" );
            if( !~E_wnd_Q_object_I_add( window, frame_id, dir_id ))
                V( "E_wnd_Q_object_I_add" );
            struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, dir_id );
            object->click = dir_click;
            Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
            if( !s )
                V( "M" );
            E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, dir, l - 2 ), fd.cFileName );
            object->data = s;
            Pc dir_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
            if( !dir_utf8 )
                V( "E_text_Z_s_Z_ansi_R_utf8" );
            I font_id = E_wnd_Q_object_Z_font_M( window, 0, dir_utf8 );
            if( !~font_id )
                V( "E_wnd_Q_object_Z_font_M" );
            if( !~E_wnd_Q_object_I_add( window, dir_id, font_id ))
                V( "E_wnd_Q_object_I_add" );
        }
        if( !FindNextFile( find_handle, &fd ))
        {   if( GetLastError() == ERROR_NO_MORE_FILES )
                break;
            V( "FindNextFile" );
        }
    }
    if( !FindClose( find_handle ))
        V( "FindClose" );
    find_handle = FindFirstFile( dir, &fd );
    if( find_handle == INVALID_HANDLE_VALUE )
        V( "FindFirstFile" );
    O{ if( !( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
        {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
            if( !~frame_id )
                V( "E_wnd_Q_object_Z_frame_M" );
            if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                V( "E_wnd_Q_object_I_add" );
            I file_id = E_wnd_Q_object_Z_button_M(window);
            if( !~file_id )
                V( "E_wnd_Q_object_Z_button_M" );
            if( !~E_wnd_Q_object_I_add( window, frame_id, file_id ))
                V( "E_wnd_Q_object_I_add" );
            struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, file_id );
            object->click = file_click;
            Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
            if( !s )
                V( "M" );
            E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, dir, l - 2 ), fd.cFileName );
            object->data = s;
            Pc file_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
            if( !file_utf8 )
                V( "E_text_Z_s_Z_ansi_R_utf8" );
            I font_id = E_wnd_Q_object_Z_font_M( window, 0, file_utf8 );
            if( !~font_id )
                V( "E_wnd_Q_object_Z_font_M" );
            if( !~E_wnd_Q_object_I_add( window, file_id, font_id ))
                V( "E_wnd_Q_object_I_add" );
        }
        if( !FindNextFile( find_handle, &fd ))
        {   if( GetLastError() == ERROR_NO_MORE_FILES )
                break;
            V( "FindNextFile" );
        }
    }
    if( !FindClose( find_handle ))
        V( "FindClose" );
    SetWindowText( window->h, dir );
    W(dir);
    E_wnd_Q_object_I_lay(window);
    RECT rectangle =
    { 0, 0
    , window->width, window->height
    };
    InvalidateRect( window->h, &rectangle, TRUE );
}
void
file_click(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N8 button
, N8 sequence
){  N ret = (N)ShellExecute( window->h, 0, object->data, 0, 0, SW_SHOWNORMAL );
    if( ret == SE_ERR_NOASSOC )
        MessageBox( window->h, "not associated", "err", MB_OK );
    else if( ret == SE_ERR_FNF )
    {   Pc file = E_text_Z_s0_R_search_last_c( object->data, '\\' ) + 1;
        N l = file - (Pc)object->data + 2;
        Pc dir = M(l);
        E_text_Z_s_P_copy_( dir, object->data, file );
        dir[ l - 2 ] = '*';
        dir[ l - 1 ] = '\0';
        WIN32_FIND_DATA fd;
        HANDLE find_handle = FindFirstFile( dir, &fd );
        if( find_handle == INVALID_HANDLE_VALUE )
        {   W(dir);
            MessageBox( window->h, "FindFirstFile", "err", MB_OK );
            return;
        }
        for_each_rev( object_id, window->object, E_mem_Q_tab )
            E_wnd_Q_object_W( window, object_id );
        I root_frame_id = E_wnd_Q_object_Z_frame_M(window);
        if( !~root_frame_id )
            V( "E_wnd_Q_object_Z_frame_M" );
        O{ if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
                if( !~frame_id )
                    V( "E_wnd_Q_object_Z_frame_M" );
                if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                    V( "E_wnd_Q_object_I_add" );
                I dir_id = E_wnd_Q_object_Z_button_M(window);
                if( !~dir_id )
                    V( "E_wnd_Q_object_Z_button_M" );
                if( !~E_wnd_Q_object_I_add( window, frame_id, dir_id ))
                    V( "E_wnd_Q_object_I_add" );
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, dir_id );
                object->click = dir_click;
                Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
                if( !s )
                    V( "M" );
                E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, dir, l - 2 ), fd.cFileName );
                object->data = s;
                Pc dir_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
                if( !dir_utf8 )
                    V( "E_text_Z_s_Z_ansi_R_utf8" );
                I font_id = E_wnd_Q_object_Z_font_M( window, 0, dir_utf8 );
                if( !~font_id )
                    V( "E_wnd_Q_object_Z_font_M" );
                if( !~E_wnd_Q_object_I_add( window, dir_id, font_id ))
                    V( "E_wnd_Q_object_I_add" );
            }
            if( !FindNextFile( find_handle, &fd ))
            {   if( GetLastError() == ERROR_NO_MORE_FILES )
                    break;
                V( "FindNextFile" );
            }
        }
        if( !FindClose( find_handle ))
            V( "FindClose" );
        find_handle = FindFirstFile( dir, &fd );
        if( find_handle == INVALID_HANDLE_VALUE )
            V( "FindFirstFile" );
        O{ if( !( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
            {   I frame_id = E_wnd_Q_object_Z_frame_M(window);
                if( !~frame_id )
                    V( "E_wnd_Q_object_Z_frame_M" );
                if( !~E_wnd_Q_object_I_add( window, root_frame_id, frame_id ))
                    V( "E_wnd_Q_object_I_add" );
                I file_id = E_wnd_Q_object_Z_button_M(window);
                if( !~file_id )
                    V( "E_wnd_Q_object_Z_button_M" );
                if( !~E_wnd_Q_object_I_add( window, frame_id, file_id ))
                    V( "E_wnd_Q_object_I_add" );
                struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, file_id );
                object->click = file_click;
                Pc s = M( l - 2 + E_text_Z_s0_R_l( fd.cFileName ) + 1 );
                if( !s )
                    V( "M" );
                E_text_Z_s0_P_copy_0( E_text_Z_s_P_copy_l( s, dir, l - 2 ), fd.cFileName );
                object->data = s;
                Pc file_utf8 = E_text_Z_s_Z_ansi_R_utf8( fd.cFileName );
                if( !file_utf8 )
                    V( "E_text_Z_s_Z_ansi_R_utf8" );
                I font_id = E_wnd_Q_object_Z_font_M( window, 0, file_utf8 );
                if( !~font_id )
                    V( "E_wnd_Q_object_Z_font_M" );
                if( !~E_wnd_Q_object_I_add( window, file_id, font_id ))
                    V( "E_wnd_Q_object_I_add" );
            }
            if( !FindNextFile( find_handle, &fd ))
            {   if( GetLastError() == ERROR_NO_MORE_FILES )
                    break;
                V( "FindNextFile" );
            }
        }
        if( !FindClose( find_handle ))
            V( "FindClose" );
        W(dir);
        E_wnd_Q_object_I_lay(window);
        RECT rectangle =
        { 0, 0
        , window->width, window->height
        };
        InvalidateRect( window->h, &rectangle, TRUE );
    }
}

