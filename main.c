#include "0.h"
N D_id( main, timer_draw );
N E_main_Q_timer_S_hour;
N E_main_Q_timer_S_minute;
N E_main_Q_timer_S_second;
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance
, LPSTR lpCmdLine
, int nCmdShow
){  E_base_M();
    E_wnd_M(hInstance);
    for_n( i, 2 )
    {   N window_id = E_wnd_Q_window_M( hInstance
        , 450, 500
        );
        if( !~window_id )
            V( "E_wnd_Q_window_M" );
        struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
        I object_id = E_wnd_Q_object_Z_frame_M(window);
        for_n( i, 2 )
        {   I id = E_wnd_Q_object_Z_frame_M(window);
            E_wnd_Q_object_I_add( window, object_id, id );
            for_n( i, 5 )
            {   I id_2 = E_wnd_Q_object_Z_frame_M(window);
                E_wnd_Q_object_I_add( window, id, id_2 );
                for_n( i, 2 )
                {   I id_3 = E_wnd_Q_object_Z_frame_M(window);
                    E_wnd_Q_object_I_add( window, id_2, id_3 );
                    for_n( i, 3 )
                    {   I id_4 = E_wnd_Q_object_Z_button_M(window);
                        E_wnd_Q_object_I_add( window, id_3, id_4 );
                        I id_5 = E_wnd_Q_object_Z_font_M( window, 0, "abc" );
                        E_wnd_Q_object_I_add( window, id_4, id_5 );
                    }
                }
                for_n_( i, 2 )
                {   I id_3 = E_wnd_Q_object_Z_button_M(window);
                    E_wnd_Q_object_I_add( window, id_2, id_3 );
                    I id_4 = E_wnd_Q_object_Z_font_M( window, 0, "abcd" );
                    E_wnd_Q_object_I_add( window, id_3, id_4 );
                }
            }
            for_n_( i, 5 )
            {   I id_2 = E_wnd_Q_object_Z_frame_M(window);
                E_wnd_Q_object_I_add( window, id, id_2 );
                I id_3 = E_wnd_Q_object_Z_entry_M( window, 0, "abcdefghijkl" );
                E_wnd_Q_object_I_add( window, id_2, id_3 );
            }
        }
        E_wnd_Q_object_M( window
        , 0
        , 5, 5
        , 61, 61
        , 0
        , E_main_Q_timer_I_draw
        , 0
        );
        E_wnd_Q_object_M( window
        , 0
        , 55, 53
        , 171, 191
        , 0
        , E_main_Q_timer_I_draw
        , 0
        );
        E_wnd_Q_object_M( window
        , 0
        , 151, 191
        , 21, 21
        , 0
        , E_main_Q_timer_I_draw
        , 0
        );
        E_wnd_Q_object_I_lay(window);
    }
    D_M( main, timer_draw );
    MSG msg;
    while( GetMessage( &msg, NULL, 0, 0 ) > 0 )   /* If no error is received... */
    {   TranslateMessage( &msg ); /* Translate key codes to chars if present */
        DispatchMessage( &msg ); /* Send it to WndProc */
    }
    return msg.wParam;
}
D( main, timer_draw )
{   SYSTEMTIME st;
    GetSystemTime( &st );
    E_main_Q_timer_S_hour = st.wHour % 12;
    E_main_Q_timer_S_minute = st.wMinute;
    E_main_Q_timer_S_second = st.wSecond;
    Y_M( main, timer_draw, 1000 );
    I_D
    {   N timer_lost_count;
        Y_B( main, timer_draw );
        GetSystemTime( &st );
        E_main_Q_timer_S_hour = st.wHour % 12;
        E_main_Q_timer_S_minute = st.wMinute;
        E_main_Q_timer_S_second = st.wSecond;
        E_wnd_Q_object_I_draw_Z_draw_proc( E_main_Q_timer_I_draw );
    }
    Y_W( main, timer_draw );
}
void
E_main_I_draw_Z_angle_line(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N arc_i
, N arc_n
, N line_length_i
, N line_length_n
, N32 color
){
    S16 x = line_length_i * ( object->width / 2 - 1 ) / line_length_n;
    S16 y = line_length_i * ( object->height / 2 - 1 ) / line_length_n;
    N l = 2 * ( object->width + object->height );
    N d = arc_i * l / arc_n;
    N a = d % ( l / 8 );
    switch( d / ( l / 8 ))
    { case 0:
            x = a;
            y = -y;
            break;
      case 1:
            y = a - y;
            break;
      case 2:
            y = a;
            break;
      case 3:
            x = x - a;
            break;
      case 4:
            x = -a;
            break;
      case 5:
            x = -x;
            y -= a;
            break;
      case 6:
            x = -x;
            y = -a;
            break;
      case 7:
            x = a - x;
            y = -y;
            break;
    }
    E_wnd_Q_object_I_draw_aa_Z_lines( window, object
    , 2
    , (( POINT[] )
      { { object->width / 2
        , object->height / 2
        }
      , { object->width / 2 + x
        , object->height / 2 + y
        }
      }
    )
    , color
    , 0.01 * object->width * line_length_n / line_length_i
    );
}
//NDFN konkretne stany wyglądu obiektów mające konkretne znaczenia.
void
E_main_Q_timer_I_draw(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
){  E_wnd_Q_object_I_draw_P_color( object, E_wnd_Z_color_M( 0xff, 0xff, 0xff ));
    E_wnd_Q_object_I_draw_Z_rectangles( window, object
    , 1
    , ( RECT[] )
      { 0
      , 0
      , object->width - 1
      , object->height - 1
      }
    );
    E_wnd_Q_object_I_draw_Z_font_Z_s( window, object, 1, 1, 0, 0, "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ\naąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż\n0123456789\n!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\n′−¡‽²➪³№ ‒⁄÷°〃⇢×⁑⁂–—≈±⁃―‣•®℠©™µ❛❝❜❞⁅〈⁆〉 ¦‐՚‛‟‚„‘“’”⏎⁋✓·…‹«›» ¿€¢" );
    E_wnd_Q_object_I_draw_P_color( object, E_wnd_Z_color_M( 0, 0, 0x9f ));
    E_main_I_draw_Z_angle_line( window, object
    , E_main_Q_timer_S_hour
    , 12
    , 1
    , 2
    , E_wnd_Z_color_M( 0, 0, 0x9f )
    );
    E_wnd_Q_object_I_draw_P_color( object, E_wnd_Z_color_M( 0, 0xbf, 0 ));
    E_main_I_draw_Z_angle_line( window, object
    , E_main_Q_timer_S_minute
    , 60
    , 3
    , 4
    , E_wnd_Z_color_M( 0, 0xbf, 0 )
    );
    E_wnd_Q_object_I_draw_P_color( object, E_wnd_Z_color_M( 0, 0, 0 ));
    E_main_I_draw_Z_angle_line( window, object
    , E_main_Q_timer_S_second
    , 60
    , 1
    , 1
    , E_wnd_Z_color_M( 0, 0, 0 )
    );
}

