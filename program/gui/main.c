








N E_main_Q_timer_S_hour;
N E_main_Q_timer_S_minute;
N E_main_Q_timer_S_second;
N E_main_Q_http_req_ret_count;

void
http_req_ret_func( N connection_i
){  E_main_Q_http_req_ret_count++;
    G_(); Gs0( E_net_http_S_connect[ connection_i ].file_name );
    V0( unlink( E_net_http_S_connect[ connection_i ].file_name ) ){}
    E_net_http_S_connect[ connection_i ].ret_func = 0;
}
void
http2_req_ret_func( N connection_i
, I stream_id
){  E_main_Q_http_req_ret_count++;
    struct E_net_http2_Z_stream *stream = E_mem_Q_tab_R( E_net_http2_S_connect[ connection_i ].stream, stream_id );
    G_(); Gs0( stream->file_name );
    V0( unlink( stream->file_name ) ){}
}
int
main(
  int argc
, Pc argv[]
){  E_base_M( argc, argv );
    E_x_M();
    E_ui_M();
#ifndef C_line_report
    I out = E_io_Q_stream_out_M_fd( STDERR_FILENO );
#else
    I out = 0;
#endif
    E_io_Q_stream_out_P( out
    , "\n\"OUX 2\" test sample (c)2017‐2022 overcq"
    , 0
    );
    I_B();
#ifndef C_line_report
    E_io_Q_stream_out_W_(out);
#endif
    I_V()
        goto End;

    SSL_CTX *ssl_ctx = E_net_cli_Q_ssl_M();
    if( !ssl_ctx )
        goto End_3;
    B http2;
    N connection = E_net_cli_Q_ssl_I_connect( ssl_ctx, "gentoo", &http2 );
    if( !~connection )
        goto Skip;
    if(http2)
    {   N ret = E_net_http2_I_request( connection, "/", http2_req_ret_func );
        if(ret)
            goto Skip;
        ret = E_net_http2_I_request( connection, "/", http2_req_ret_func );
        if(ret)
            goto Skip;
    }else
    {   N ret = E_net_http_I_request( connection, "/", http_req_ret_func );
        if(ret)
            goto Skip;
    }
    X_M( net, ret );
    E_main_Q_http_req_ret_count = 0;
    O{  X_B( net, ret, 0 )
            break;
        if(( http2
          && ( !E_net_http2_S_connect_n
            || E_main_Q_http_req_ret_count == 2
          ))
        || ( !http2
          && ( !E_net_http_S_connect_n
            || E_main_Q_http_req_ret_count == 1
        )))
            break;
    }
Skip:
    E_net_cli_Q_ssl_W( ssl_ctx );
End_3:;
    

    E_data_Q_layout_I_add( E_data_Q_field_S_text, "Text input ąę", 5 );
    for_n( i, 42 )
    {   E_data_Q_layout_I_add( E_data_Q_field_S_text, "Second text input ąę", 100 );
        struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, 1 + i );
        input->select_n = 50;
        Mt_( input->select, input->select_n );
        for_n( i, input->select_n )
        {   N l = E_text_Z_n_N_s_G( i, sizeof(i), 10 );
            input->select[i] = M( l + 8 + 210 + 1 );
            E_text_Z_n_N_s( input->select[i] + l, i, sizeof(i), 10 );
            E_text_Z_s_P_s0_copy_0( input->select[i] + l, ". select select select select select select select select select select select select select select select select select select select select select select select select select select select select select select select" );
        }
    }
    E_data_Q_layout_I_add( E_data_Q_field_S_text, "44. text input ąę", 100 );
    E_ncurses_I_lay();

    X_M( x_window, close_window );
    for_n_( i, 1 )
    {   D_M( main, timer_draw )
            goto End_1;
        N display_id = E_x_Q_display_M();
        if( !~display_id )
            goto End_2;
        struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
        for_each( screen_id, display->screen, E_mem_Q_tab )
        {   struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, screen_id );
            U_F( screen->mode, animation );
            for_n( i, 2 )
            {   N window_id = E_x_Q_window_M( display_id, screen_id
                , 450, 500
                );
                struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
                I object_id = E_x_Q_object_Z_frame_M( display, window );
                for_n( i, 3 )
                {   I id = E_x_Q_object_Z_frame_M( display, window );
                    E_x_Q_object_I_add( window, object_id, id );
                    for_n( i, 5 )
                    {   I id_2 = E_x_Q_object_Z_frame_M( display, window );
                        E_x_Q_object_I_add( window, id, id_2 );
                        for_n( i, 2 )
                        {   I id_3 = E_x_Q_object_Z_frame_M( display, window );
                            E_x_Q_object_I_add( window, id_2, id_3 );
                            for_n( i, 3 )
                            {   I id_4 = E_x_Q_object_Z_button_M( display, window );
                                E_x_Q_object_I_add( window, id_3, id_4 );
                                I id_5 = E_x_Q_object_Z_font_M( display, window, 0, "abc" );
                                E_x_Q_object_I_add( window, id_4, id_5 );
                            }
                        }
                        for_n_( i, 2 )
                        {   I id_3 = E_x_Q_object_Z_button_M( display, window );
                            E_x_Q_object_I_add( window, id_2, id_3 );
                            I id_4 = E_x_Q_object_Z_font_M( display, window, 0, "abcd" );
                            E_x_Q_object_I_add( window, id_3, id_4 );
                        }
                    }
                    for_n_( i, 5 )
                    {   I id_2 = E_x_Q_object_Z_frame_M( display, window );
                        E_x_Q_object_I_add( window, id, id_2 );
                        I id_3 = E_x_Q_object_Z_entry_M( display, window, 0, "abcdefghijkl" );
                        E_x_Q_object_I_add( window, id_2, id_3 );
                    }
                }
                E_x_Q_object_M( display, window
                , 0
                , 5, 5
                , 61, 61
                , 0
                , E_main_Q_timer_I_draw
                , 0
                );
                E_x_Q_object_M( display, window
                , 0
                , 55, 53
                , 171, 191
                , 0
                , E_main_Q_timer_I_draw
                , 0
                );
                E_x_Q_object_M( display, window
                , 0
                , 151, 191
                , 21, 21
                , 0
                , E_main_Q_timer_I_draw
                , 0
                );
                E_x_Q_object_I_lay( display, window );
            }
        }
        
        X_B( x_window, close_window, 0 )
            U_F( E_base_S->E_flow_S_signal, exit_all );
        
        E_x_Q_display_W( display_id );
End_2:  D_W( main, timer_draw );
        if( U_R( E_base_S->E_flow_S_signal, exit_all ))
            break;
    }
End_1:
    X_W( x_window, close_window );
End:E_ui_W();
    E_x_W();
    E_base_W();
    return 0;
}


    
    
    
    
            
        
            
        
        
        
            
            
            
                
                    
            
            
            
        
        
        
    
    

_internal I D_id( main, timer_draw ) = ~0; D( main, timer_draw )
{   time_t time_u = time(0);
    struct tm *time_s = localtime( &time_u );
    E_main_Q_timer_S_hour = time_s->tm_hour % 12;
    E_main_Q_timer_S_minute = time_s->tm_min;
    E_main_Q_timer_S_second = time_s->tm_sec;
    I timer = Y_M(1000000);
    I_D
    {   N timer_lost_count;
        Y_B( timer, &timer_lost_count )
            break;
        E_main_Q_timer_S_second += 1 + timer_lost_count;
        E_main_Q_timer_S_hour += E_main_Q_timer_S_second / 3600;
        E_main_Q_timer_S_second %= 3600;
        E_main_Q_timer_S_minute += E_main_Q_timer_S_second / 60;
        E_main_Q_timer_S_second %= 60;
        E_main_Q_timer_S_hour += E_main_Q_timer_S_minute / 60;
        E_main_Q_timer_S_minute %= 60;
        E_main_Q_timer_S_hour %= 12;
        E_x_Q_object_I_draw_Z_draw_proc( E_main_Q_timer_I_draw, !!timer_lost_count );
    }
    Y_W(timer);
}
#define E_main_I_draw_Z_angle_line_(arc_i,arc_n,line_length_i,line_length_n,color)    E_main_I_draw_Z_angle_line( display, screen, window, object, arc_i, arc_n, line_length_i, line_length_n, color )
void
E_main_I_draw_Z_angle_line(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
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
    if( !U_R( display->mode, draw_simple ))
        E_x_Q_object_I_draw_aa_Z_lines( display, screen, window, object
        , 2
        , (( xcb_point_t[] )
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
    else
    {   xcb_point_t points[2] =
        { { object->width / 2
          , object->height / 2
          }
        , { object->width / 2 + x
          , object->height / 2 + y
          }
        };
        E_x_Q_object_I_draw_P_color_(color);
        E_x_Q_object_I_draw_Z_lines_(points);
    }
}

void
E_main_Q_timer_I_draw(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
){  E_x_Q_object_I_draw_P_color_( E_x_Z_color_M( 0xff, 0xff, 0xff ));
    E_x_Q_object_I_draw_Z_rectangles_(
      (( xcb_rectangle_t[] )
      { 0
      , 0
      , object->width - 1
      , object->height - 1
      })
    );
    E_x_Q_object_I_draw_Z_font_Z_s_( 1, 1, 0, 0, "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ\naąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż\n0123456789\n!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\n′−¡‽²➪³№ ‒⁄÷°〃⇢×⁑⁂–—≈±⁃―‣•®℠©™µ❛❝❜❞⁅〈⁆〉 ¦‐՚‛‟‚„‘“’”⏎⁋✓·…‹«›» ¿€¢" );
    E_x_Q_object_I_draw_P_color_( E_x_Z_color_M( 0, 0, 0x9f ));
    E_main_I_draw_Z_angle_line_(
      E_main_Q_timer_S_hour
    , 12
    , 1
    , 2
    , E_x_Z_color_M( 0, 0, 0x9f )
    );
    E_x_Q_object_I_draw_P_color_( E_x_Z_color_M( 0, 0xbf, 0 ));
    E_main_I_draw_Z_angle_line_(
      E_main_Q_timer_S_minute
    , 60
    , 3
    , 4
    , E_x_Z_color_M( 0, 0xbf, 0 )
    );
    E_x_Q_object_I_draw_P_color_( E_x_Z_color_M( 0, 0, 0 ));
    E_main_I_draw_Z_angle_line_(
      E_main_Q_timer_S_second
    , 60
    , 1
    , 1
    , E_x_Z_color_M( 0, 0, 0 )
    );
    E_x_Q_object_I_draw_P_color_( E_x_Z_color_M( 0, 0, 0xff ));
    E_x_Q_object_I_fill_Z_arcs_(
      (( xcb_arc_t[] )
      { 100
      , 100
      , 50
      , 100
      })
    );
}

void
E_flow_Q_process_call_I_func( P data
){
}


