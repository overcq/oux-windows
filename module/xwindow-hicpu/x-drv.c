



















    #ifdef E_flow_C_thread_system_unblock_reports
_internal
void
E_x_window_D_events_I_unblock( P display_id
){  struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, *( I * )display_id );
    struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, 0 );
    struct E_x_Q_window_Z *window = &screen->dnd_window;
    xcb_client_message_event_t x_client =
    { .response_type = XCB_CLIENT_MESSAGE
    , .format = 32
    , .window = XCB_NONE
    , .type = XCB_NONE
    };
    xcb_send_event( display->x_display
    , no
    , window->x_window
    , XCB_EVENT_MASK_STRUCTURE_NOTIFY
    , (P)&x_client
    );
    xcb_flush( display->x_display );
}
_internal I D_id( x_window, events_pointer_button_check ) = ~0; D( x_window, events_pointer_button_check )
{   Yi_M( x_window, events_pointer_button_check );
    I_D
    {   Yi_B( x_window, events_pointer_button_check )
            break;
        E_flow_Q_thread_system_unblock_report_I_unblock( D_id(x_window,events), 0 ); 
    }
    Yi_W( x_window, events_pointer_button_check );
}
    #endif
_internal I D_id( x_window, events ) = ~0; D( x_window, events )
{   Dh_();
        #ifdef E_flow_C_thread_system_unblock_reports
    I display_id = *( I * )thread_proc_arg;
        #endif
    Xh_A( E_x_window_D_events_I_unblock );
    X_A( x_window, draw );
    X_A( x_window, close_window );
    X_A( x_window, flush );











        #ifndef E_flow_C_thread_system_unblock_reports
    I timer = Y_M(182999);
        #else
    Yi_A( x_window, events_pointer_button_check );
    D_M( x_window, events_pointer_button_check )
        return;
        #endif
    I_D
    {
            #ifndef E_flow_C_thread_system_unblock_reports
        for_each( display_id, E_x_Q_display_S, E_mem_Q_tab )
            #endif
        {   struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
                #ifndef E_flow_C_thread_system_unblock_reports
            xcb_generic_event_t *x_event = xcb_poll_for_event( display->x_display );
            int e;
            if( e = xcb_connection_has_error( display->x_display ))
            {   GV(NA); Gd(e); V(); 
            }
                #else
            xcb_connection_t *x_display = display->x_display;
            Xh_B_();
            xcb_generic_event_t *x_event = xcb_wait_for_event( x_display );
            Xh_B()
            {   free( x_event );
                break;
            }
            if( !x_event )
            {   int e = xcb_connection_has_error( display->x_display );
                GV(NA); Gd(e); V(); 
            }
            display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
                #endif
            struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, display->drag_S_dnd_window_screen_id );
            B U_L( drag, motion );
            B U_L( window, postproc );
            xcb_window_t drag_S_motion_x_root_window;
            S16 drag_S_motion_root_x, drag_S_motion_root_y;
            B U_L( drag_S_motion, oth_screen );
                #ifndef E_flow_C_thread_system_unblock_reports
            if( x_event )
                #endif
            do
            {   if( !x_event->response_type )
                {   xcb_generic_error_t *x_error = (P)x_event;
                    GV(NA); Gd( x_error->sequence ); Gd( x_error->major_code ); Gd( x_error->minor_code ); Gd( x_error->error_code ); Gd( x_error->resource_id ); V(); 
                }
                xcb_window_t x_event_window;
                
                switch( x_event->response_type )
                { case XCB_KEY_PRESS:
                  case XCB_KEY_RELEASE:
                    {   xcb_key_press_event_t *x_key = (P)x_event;
                        x_event_window = x_key->event;
                        break;
                    }
                  case XCB_BUTTON_PRESS:
                  case XCB_BUTTON_RELEASE:
                    {   xcb_button_press_event_t *x_button = (P)x_event;
                        x_event_window = x_button->event;
                        break;
                    }
                  case XCB_ENTER_NOTIFY:
                  case XCB_LEAVE_NOTIFY:
                    {   xcb_enter_notify_event_t *x_enter = (P)x_event;
                        x_event_window = x_enter->event;
                        break;
                    }
                  case XCB_MOTION_NOTIFY:
                    {   xcb_motion_notify_event_t *x_motion = (P)x_event;
                        x_event_window = x_motion->event;
                        break;
                    }
                  case XCB_FOCUS_IN:
                  case XCB_FOCUS_OUT:
                    {   xcb_focus_in_event_t *x_focus = (P)x_event;
                        x_event_window = x_focus->event;
                        break;
                    }
                  case XCB_EXPOSE:
                    {   xcb_expose_event_t *x_expose = (P)x_event;
                        x_event_window = x_expose->window;
                        break;
                    }
                  case XCB_GRAPHICS_EXPOSURE:
                    {   xcb_graphics_exposure_event_t *x_exposure = (P)x_event;
                        x_event_window = x_exposure->drawable;
                        break;
                    }
                  case XCB_NO_EXPOSURE:
                    {   xcb_no_exposure_event_t *x_exposure = (P)x_event;
                        x_event_window = x_exposure->drawable;
                        break;
                    }
                  case XCB_VISIBILITY_NOTIFY:
                    {   xcb_visibility_notify_event_t *x_visibility = (P)x_event;
                        x_event_window = x_visibility->window;
                        break;
                    }
                  case XCB_DESTROY_NOTIFY:
                    {   xcb_destroy_notify_event_t *x_destroy = (P)x_event;
                        x_event_window = x_destroy->window;
                        break;
                    }
                  case XCB_UNMAP_NOTIFY:
                    {   xcb_unmap_notify_event_t *x_unmap = (P)x_event;
                        x_event_window = x_unmap->window;
                        break;
                    }
                  case XCB_MAP_NOTIFY:
                    {   xcb_map_notify_event_t *x_map = (P)x_event;
                        x_event_window = x_map->window;
                        break;
                    }
                  case XCB_REPARENT_NOTIFY:
                    {   xcb_reparent_notify_event_t *x_reparent = (P)x_event;
                        x_event_window = x_reparent->window;
                        break;
                    }
                  case XCB_RESIZE_REQUEST:
                    {   xcb_resize_request_event_t *x_resize_req = (P)x_event;
                        x_event_window = x_resize_req->window;
                        break;
                    }
                  case XCB_GRAVITY_NOTIFY:
                    {   xcb_gravity_notify_event_t *x_gravity = (P)x_event;
                        x_event_window = x_gravity->window;
                        break;
                    }
                  default:
                        switch( XCB_EVENT_RESPONSE_TYPE( x_event ))
                        { case XCB_CONFIGURE_NOTIFY:
                            {   xcb_configure_notify_event_t *x_configure = (P)x_event;
                                x_event_window = x_configure->window;
                                break;
                            }
                          case XCB_CLIENT_MESSAGE:
                            {   xcb_client_message_event_t *x_client = (P)x_event;
                                x_event_window = x_client->window;
                                break;
                            }
                          default:
                            {   GV(NKN); Gd( XCB_EVENT_RESPONSE_TYPE( x_event ));
                                goto Loop;
                            }
                        }
                        break;
                }
                I window_id = ~0;
                struct E_x_Q_window_Z *window = 0;
                if( U_R( display->mode, drag )
                || U_R( display->mode, drag_stop )
                )
                {   if( x_event_window == screen->dnd_window.x_window )
                        window = &screen->dnd_window;
                }
                if( !window )
                {   for_each_( window_id, display->window, E_mem_Q_tab )
                    {   window = E_mem_Q_tab_R( display->window, window_id );
                        if( x_event_window == window->x_window )
                            break;
                    }
                    if( !~window_id )
                    {   GV(NXP); Gd( XCB_EVENT_RESPONSE_TYPE( x_event )); Gd( x_event_window ); 
                        goto Loop;
                    }
                }
                switch( x_event->response_type )
                { case XCB_KEY_PRESS:
                    {   G(); Gs0_( "key press" );
                        xcb_key_press_event_t *x_key = (P)x_event;
                        window->user_activity_time = x_key->time;
                        U_F( window, postproc );
                        B ctrl = no, alt = no, alt_r = no, logo = no;
                        N modifier = 0;
                            #ifdef __gnu_linux__
                        xcb_xkb_get_state_cookie_t xkb_get_state_req_id = xcb_xkb_get_state_unchecked( display->x_display, display->xkb_keyboard );
                        xcb_xkb_get_state_reply_t *ret = xcb_xkb_get_state_reply( display->x_display, xkb_get_state_req_id, 0 );
                        if( ret->group == 1 )
                            modifier = 2;
                        else if( ret->group == 2 )
                            modifier = 6;
                        free(ret);
                            #endif
                        if( x_key->state & 0x80 ) 
                        {   alt_r = yes;
                            if( !modifier )
                                modifier = 4;
                        }
                        if( x_key->state & 0x40 )
                            logo = yes;
                        if( x_key->state & XCB_MOD_MASK_1 ) 
                            alt = yes;
                        if( x_key->state & XCB_MOD_MASK_CONTROL )
                            ctrl = yes;
                        B shift = no;
                        if((( x_key->state & XCB_MOD_MASK_SHIFT ) && (( x_key->state & XCB_MOD_MASK_LOCK ) == 0 ))
                          || ((( x_key->state & XCB_MOD_MASK_SHIFT ) == 0 ) && ( x_key->state & XCB_MOD_MASK_LOCK ))
                        )
                        {   if( x_key->state & XCB_MOD_MASK_SHIFT )
                                shift = yes;
                            modifier++;
                        }
                        xcb_keysym_t keysym = E_x_Q_display_R_keysym( display, x_key->detail, modifier );
                        U u;
                        if(((( x_key->state & XCB_MOD_MASK_SHIFT ) && (( x_key->state & XCB_MOD_MASK_LOCK ) == 0 ))
                          || ((( x_key->state & XCB_MOD_MASK_SHIFT ) == 0 ) && ( x_key->state & XCB_MOD_MASK_LOCK ))
                        ) && !keysym
                        )
                        {   xcb_keysym_t keysym_ = E_x_Q_display_R_keysym( display, x_key->detail, modifier - 1 );
                            u = E_x_Q_display_I_keysym_to_unicode( display, keysym_ );
                            if( !~u || !iswprint(u) )
                            {   keysym = keysym_;
                                modifier--;
                            }else
                                u = ~0;
                        }else
                            u = E_x_Q_display_I_keysym_to_unicode( display, keysym );
                        G_(); Gd( x_key->detail ); Gh( x_key->state ); Gh(keysym); Gd(modifier); Gh(u);
                        for_n( i, display->keyboard_mapping->keysyms_per_keycode )
                        {   xcb_keysym_t keysym = E_x_Q_display_R_keysym( display, x_key->detail, i );
                            G_(); Gd(keysym); Gd(i);
                        }
                        if( display->pointer_button_S_seq_i )
                            break;
                        if( ~display->cursor_window )
                        {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, display->cursor_window );
                            struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, display->cursor_object );
                            if( object->draw == E_x_Q_object_Z_entry_I_draw )
                            {   struct E_x_Q_object_Z_data_Z_entry *object_data = object->data;
                                if( ~u && iswprint(u) )
                                {   Pc s = object_data->text;
                                    for_n( i, object_data->cursor_pos )
                                    {   U u = ~0;
                                        s = E_text_Z_su_R_u( s, &u );
                                        if( !~u )
                                        {   GV_(bad UTF-8 character); V();
                                        }
                                    }
                                    C s_[6];
                                    N n = E_text_Z_u_R_su( u, &s_[0] );
                                    i = s - object_data->text;
                                    E_mem_Q_blk_I_insert( &object_data->text, i, n );
                                    E_text_Z_s_P_sl_copy( object_data->text + i, &s_[0], n );
                                    object_data->cursor_pos++;
                                    s = object_data->text;
                                    for_n_( i, object_data->text_start )
                                    {   U u = ~0;
                                        s = E_text_Z_su_R_u( s, &u );
                                        if( !~u )
                                        {   GV_(bad UTF-8 character); V();
                                        }
                                    }
                                    struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, object_data->font );
                                    S16 x = 0;
                                    for_n_( i, object_data->cursor_pos - object_data->text_start )
                                    {   U u = ~0;
                                        s = E_text_Z_su_R_u( s, &u );
                                        if( !~u )
                                        {   GV_(bad UTF-8 character); V();
                                        }
                                        for_n( i, font->bitmap_n )
                                            if( font->bitmap[i].u == u )
                                            {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                                                break;
                                            }
                                        if( i == font->bitmap_n )
                                            x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
                                    }
                                    if( x >= object->width )
                                    {   x = object->width;
                                        object_data->text_start = object_data->cursor_pos;
                                        O{  U u = ~0;
                                            s = E_text_Z_su_R_u_rev( s, &u );
                                            if( !~u )
                                            {   GV_(bad UTF-8 character); V();
                                            }
                                            for_n( i, font->bitmap_n )
                                                if( font->bitmap[i].u == u )
                                                {   x -= ( x != object->width ? 1 : 0 ) + font->bitmap[i].width;
                                                    break;
                                                }
                                            if( i == font->bitmap_n )
                                                x -= ( x != object->width ? 1 : 0 ) + font->bitmap[0].width;
                                            if( x < 0 )
                                                break;
                                            object_data->text_start--;
                                        }
                                    }
                                }else if( !alt && !alt_r && !ctrl && !logo && !shift )
                                    switch(keysym)
                                    { case XK_Return:
                                      case XK_KP_Enter:
                                            if( U_E( object_data->state, cursor_visible_ ))
                                                E_x_Q_object_I_draw(window);
                                            display->cursor_window = ~0;
                                            break;
                                      case XK_Home:
                                      case XK_KP_Home:
                                            object_data->text_start = 0;
                                            object_data->cursor_pos = 0;
                                            break;
                                      case XK_Left:
                                      case XK_KP_Left:
                                            if( !object_data->cursor_pos )
                                                break;
                                            object_data->cursor_pos--;
                                            if( object_data->cursor_pos )
                                            {   if( object_data->text_start > object_data->cursor_pos - 1 )
                                                    object_data->text_start = object_data->cursor_pos - 1;
                                            }else
                                                if( object_data->text_start )
                                                    object_data->text_start = 0;
                                            break;
                                      case XK_Right:
                                      case XK_KP_Right:
                                        {   if( object_data->cursor_pos == E_text_Z_su0_R_l( object_data->text ) )
                                                break;
                                            object_data->cursor_pos++;
                                            struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, object_data->font );
                                            Pc s = object_data->text;
                                            for_n( i, object_data->text_start )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            S16 x = 0;
                                            for_n_( i, object_data->cursor_pos - object_data->text_start )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                for_n( i, font->bitmap_n )
                                                    if( font->bitmap[i].u == u )
                                                    {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                                                        break;
                                                    }
                                                if( i == font->bitmap_n )
                                                    x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
                                            }
                                            if( x >= object->width )
                                            {   x = object->width;
                                                object_data->text_start = object_data->cursor_pos;
                                                O{  U u = ~0;
                                                    s = E_text_Z_su_R_u_rev( s, &u );
                                                    if( !~u )
                                                    {   GV_(bad UTF-8 character); V();
                                                    }
                                                    for_n( i, font->bitmap_n )
                                                        if( font->bitmap[i].u == u )
                                                        {   x -= ( x != object->width ? 1 : 0 ) + font->bitmap[i].width;
                                                            break;
                                                        }
                                                    if( i == font->bitmap_n )
                                                        x -= ( x != object->width ? 1 : 0 ) + font->bitmap[0].width;
                                                    if( x < 0 )
                                                        break;
                                                    object_data->text_start--;
                                                }
                                            }
                                            break;
                                        }
                                      case XK_End:
                                      case XK_KP_End:
                                        {   object_data->text_start = E_text_Z_su0_R_l( object_data->text );
                                            struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, object_data->font );
                                            S16 x = object->width;
                                            Pc s = E_text_Z_s0_R_end( object_data->text );
                                            while( object_data->text_start )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u_rev( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                for_n( i, font->bitmap_n )
                                                    if( font->bitmap[i].u == u )
                                                    {   x -= ( x != object->width ? 1 : 0 ) + font->bitmap[i].width;
                                                        break;
                                                    }
                                                if( i == font->bitmap_n )
                                                    x -= ( x != object->width ? 1 : 0 ) + font->bitmap[0].width;
                                                if( x < 0 )
                                                    break;
                                                object_data->text_start--;
                                            }
                                            object_data->cursor_pos = E_text_Z_su0_R_l( object_data->text );
                                            break;
                                        }
                                      case XK_BackSpace:
                                        {   if( !object_data->cursor_pos )
                                                break;
                                            object_data->cursor_pos--;
                                            if( object_data->cursor_pos
                                            && object_data->text_start > object_data->cursor_pos - 1
                                            )
                                                object_data->text_start = object_data->cursor_pos - 1;
                                            Pc s = object_data->text;
                                            for_n( i, object_data->cursor_pos )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            U u = ~0;
                                            Pc s_ = E_text_Z_su_R_u( s, &u );
                                            if( !~u )
                                            {   GV_(bad UTF-8 character); V();
                                            }
                                            E_mem_Q_blk_I_remove( &object_data->text, s - object_data->text, s_ - s );
                                            break;
                                        }
                                      case XK_Delete:
                                      case XK_KP_Delete:
                                        {   if( object_data->cursor_pos == E_text_Z_su0_R_l( object_data->text ))
                                                break;
                                            Pc s = object_data->text;
                                            for_n( i, object_data->cursor_pos )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            U u = ~0;
                                            Pc s_ = E_text_Z_su_R_u( s, &u );
                                            if( !~u )
                                            {   GV_(bad UTF-8 character); V();
                                            }
                                            E_mem_Q_blk_I_remove( &object_data->text, s - object_data->text, s_ - s );
                                            break;
                                        }
                                    }
                                else if( !alt && !alt_r && ctrl && !logo && !shift )
                                    switch(keysym)
                                    { case XK_Left:
                                      case XK_KP_Left:
                                        {   if( !object_data->cursor_pos )
                                                break;
                                            Pc s = object_data->text;
                                            for_n( i, object_data->cursor_pos )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            U u = ~0;
                                            s = E_text_Z_su_R_u_rev( s, &u );
                                            if( !~u )
                                            {   GV_(bad UTF-8 character); V();
                                            }
                                            B space = iswspace(u);
                                            object_data->cursor_pos--;
                                            while( space && s != object_data->text )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u_rev( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                space = iswspace(u);
                                                object_data->cursor_pos--;
                                            }
                                            while( s != object_data->text )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u_rev( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                space = iswspace(u);
                                                if(space)
                                                    break;
                                                object_data->cursor_pos--;
                                            }
                                            if( object_data->cursor_pos )
                                            {   if( object_data->text_start > object_data->cursor_pos - 1 )
                                                    object_data->text_start = object_data->cursor_pos - 1;
                                            }else
                                                if( object_data->text_start )
                                                    object_data->text_start = 0;
                                            break;
                                        }
                                      case XK_Right:
                                      case XK_KP_Right:
                                        {   if( object_data->cursor_pos == E_text_Z_su0_R_l( object_data->text ) )
                                                break;
                                            Pc s = object_data->text;
                                            for_n( i, object_data->cursor_pos )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            U u = ~0;
                                            s = E_text_Z_su_R_u( s, &u );
                                            if( !~u )
                                            {   GV_(bad UTF-8 character); V();
                                            }
                                            B space = iswspace(u);
                                            object_data->cursor_pos++;
                                            while( space && *s )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                space = iswspace(u);
                                                object_data->cursor_pos++;
                                            }
                                            while( *s )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                space = iswspace(u);
                                                if(space)
                                                    break;
                                                object_data->cursor_pos++;
                                            }
                                            struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, object_data->font );
                                            s = object_data->text;
                                            for_n_( i, object_data->text_start )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                            }
                                            S16 x = 0;
                                            for_n_( i, object_data->cursor_pos - object_data->text_start )
                                            {   U u = ~0;
                                                s = E_text_Z_su_R_u( s, &u );
                                                if( !~u )
                                                {   GV_(bad UTF-8 character); V();
                                                }
                                                for_n( i, font->bitmap_n )
                                                    if( font->bitmap[i].u == u )
                                                    {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                                                        break;
                                                    }
                                                if( i == font->bitmap_n )
                                                    x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
                                            }
                                            if( x >= object->width )
                                            {   x = object->width;
                                                object_data->text_start = object_data->cursor_pos;
                                                O{  U u = ~0;
                                                    s = E_text_Z_su_R_u_rev( s, &u );
                                                    if( !~u )
                                                    {   GV_(bad UTF-8 character); V();
                                                    }
                                                    for_n( i, font->bitmap_n )
                                                        if( font->bitmap[i].u == u )
                                                        {   x -= ( x != object->width ? 1 : 0 ) + font->bitmap[i].width;
                                                            break;
                                                        }
                                                    if( i == font->bitmap_n )
                                                        x -= ( x != object->width ? 1 : 0 ) + font->bitmap[0].width;
                                                    if( x < 0 )
                                                        break;
                                                    object_data->text_start--;
                                                }
                                            }
                                            break;
                                        }
                                    }
                            }
                        }
                        break;
                    }
                  case XCB_KEY_RELEASE:
                    {   G(); Gs0_( "key release" );
                        break;
                    }
                  case XCB_BUTTON_PRESS:
                    {   xcb_button_press_event_t *x_button = (P)x_event;
                        G(); Gs0_( "button press" ); Gd( x_button->detail );
                        window->user_activity_time = x_button->time;
                        U_F( window, postproc );
                        xcb_timestamp_t xbutton_time = display->pointer_button_S_time;
                        display->pointer_button_S_time = x_button->time;
                        U_F( display->state, pointer_button_S_pressing );
                        if( display->pointer_button_S_seq_i & 1 ) 
                        {   display->pointer_button_S_seq_i = 0; 
                            break;
                        }
                        if( !display->pointer_button_S_seq_i ) 
                        {   unsigned button_mask = 0;
                            if( U_R( display->mode, drag ))
                                switch( display->drag_S_pointer_button ) 
                                { case XCB_BUTTON_INDEX_1:
                                        button_mask = XCB_BUTTON_MASK_1;
                                        break;
                                  case XCB_BUTTON_INDEX_2:
                                        button_mask = XCB_BUTTON_MASK_2;
                                        break;
                                  case XCB_BUTTON_INDEX_3:
                                        button_mask = XCB_BUTTON_MASK_3;
                                        break;
                                  case XCB_BUTTON_INDEX_4:
                                        button_mask = XCB_BUTTON_MASK_4;
                                        break;
                                  case XCB_BUTTON_INDEX_5:
                                        button_mask = XCB_BUTTON_MASK_5;
                                        break;
                                }
                            if(( x_button->state & ( XCB_BUTTON_MASK_1 | XCB_BUTTON_MASK_2 | XCB_BUTTON_MASK_3 | XCB_BUTTON_MASK_4 | XCB_BUTTON_MASK_5 )) != button_mask ) 
                                break;
                        }else if( x_button->detail != display->pointer_button ) 
                            display->pointer_button_S_seq_i = 0;
                        if( display->pointer_button_S_seq_i
                        && x_button->time - xbutton_time > display->pointer_button_C_seq_timeout
                        )
                            display->pointer_button_S_seq_i = 0;
                        if( !display->pointer_button_S_seq_i
                        && x_button->time - xbutton_time < display->pointer_button_C_restart_delay
                        )
                            break;
                        if( !display->pointer_button_S_seq_i )
                        {   display->pointer_button_S_start_time = display->pointer_button_S_time;
                            display->pointer_button = x_button->detail;
                            display->pointer_button_S_root_x = x_button->root_x;
                            display->pointer_button_S_root_y = x_button->root_y;
                            display->pointer_button_S_window_id = window_id;
                            display->pointer_button_S_x = x_button->event_x;
                            display->pointer_button_S_y = x_button->event_y;
                        }
                        display->pointer_button_S_seq_i++;
                        break;
                    }
                  case XCB_BUTTON_RELEASE:
                    {   xcb_button_press_event_t *x_button = (P)x_event;
                        G(); Gs0_( "button release" ); Gd( x_button->detail );
                        xcb_timestamp_t xbutton_time = display->pointer_button_S_time;
                        display->pointer_button_S_time = x_button->time;
                        unsigned button_mask = 0;
                        switch( x_button->detail )
                        { case XCB_BUTTON_INDEX_1:
                                button_mask = XCB_BUTTON_MASK_1;
                                break;
                          case XCB_BUTTON_INDEX_2:
                                button_mask = XCB_BUTTON_MASK_2;
                                break;
                          case XCB_BUTTON_INDEX_3:
                                button_mask = XCB_BUTTON_MASK_3;
                                break;
                          case XCB_BUTTON_INDEX_4:
                                button_mask = XCB_BUTTON_MASK_4;
                                break;
                          case XCB_BUTTON_INDEX_5:
                                button_mask = XCB_BUTTON_MASK_5;
                                break;
                        }
                        U_R( display->state, pointer_button_S_pressing ) = ( x_button->state & ( XCB_BUTTON_MASK_1 | XCB_BUTTON_MASK_2 | XCB_BUTTON_MASK_3 | XCB_BUTTON_MASK_4 | XCB_BUTTON_MASK_5 )) != button_mask ? yes : no;
                        if( x_button->detail != display->pointer_button ) 
                            display->pointer_button_S_seq_i = 0;
                        if( U_R( display->mode, drag )
                        && !U_R( display->mode, drag_stop )
                        && x_button->detail == display->drag_S_pointer_button
                        )
                        {   U_F( display->mode, drag_stop );
                            U_L( display->mode_ex, drag_stop_S_cancel );
                            display->drag_S_stop_root_x = display->pointer_button_S_root_x;
                            display->drag_S_stop_root_y = display->pointer_button_S_root_y;
                            break;
                        }
                        if( display->pointer_button_S_seq_i )
                        {   if( x_button->time - xbutton_time > display->pointer_button_C_release_timeout )
                                display->pointer_button_S_seq_i = 0;
                            else
                                display->pointer_button_S_seq_i++;
                        }
                        break;
                    }
                  case XCB_ENTER_NOTIFY:
                    {   xcb_enter_notify_event_t *x_enter_notify = (P)x_event;
                        G(); Gs0_( "enter" ); Gd( x_enter_notify->mode ); Gd( x_enter_notify->detail );
                        
                        if( x_enter_notify->mode == XCB_NOTIFY_MODE_UNGRAB )
                        {   U_L( display->req, pointer_S_ungrab );
                            if( !U_R( display->state, pointer_S_in_window ))
                                display->pointer_button_S_seq_i = 0;
                        }else if( !U_R( display->mode, drag ))
                            display->pointer_button_S_seq_i = 0;
                        U_F( display->state, pointer_S_in_window );
                        U_R( display->state, pointer_button_S_pressing ) = x_enter_notify->state & ( XCB_BUTTON_MASK_1 | XCB_BUTTON_MASK_2 | XCB_BUTTON_MASK_3 | XCB_BUTTON_MASK_4 | XCB_BUTTON_MASK_5 ) ? yes : no;
                        break;
                    }
                  case XCB_LEAVE_NOTIFY:
                    {   xcb_leave_notify_event_t *x_leave_notify = (P)x_event;
                        G(); Gs0_( "leave" ); Gd( x_leave_notify->mode ); Gd( x_leave_notify->detail );
                        if( x_leave_notify->mode == XCB_NOTIFY_MODE_NORMAL )
                        {   U_L( display->state, pointer_S_in_window );
                            if( !U_R( display->mode, drag ))
                                display->pointer_button_S_seq_i = 0;
                        }else if( x_leave_notify->mode == XCB_NOTIFY_MODE_UNGRAB )
                        {   U_L( display->req, pointer_S_ungrab );
                            if( U_R( display->mode, drag ))
                                U_F( display->mode, drag_stop );
                                #ifdef E_flow_C_thread_system_unblock_reports
                            Yi_L( x_window, events_pointer_button_check );
                                #endif
                            display->pointer_button_S_seq_i = 0;
                        }
                        break;
                    }
                  case XCB_MOTION_NOTIFY:
                    {   xcb_motion_notify_event_t *x_motion = (P)x_event;
                        drag_S_motion_x_root_window = x_motion->root;
                        drag_S_motion_root_x = x_motion->root_x;
                        drag_S_motion_root_y = x_motion->root_y;
                        if( x_motion->same_screen == 0 )
                            U_F( drag_S_motion, oth_screen );
                        U_F( drag, motion );
                        break;
                    }
                  case XCB_FOCUS_IN:
                    {   G(); Gs0_( "focus in" );
                        break;
                    }
                  case XCB_FOCUS_OUT:
                    {   G(); Gs0_( "focus out" );
                        break;
                    }
                  case XCB_EXPOSE:
                    {   G(); Gs0_( "expose" );
                        U_F( window->req, draw );
                        U_F( display->req, draw );
                        break;
                    }
                  case XCB_GRAPHICS_EXPOSURE:
                    {   G(); Gs0_( "graphics expose" );
                        break;
                    }
                  case XCB_NO_EXPOSURE:
                    {   G(); Gs0_( "no expose" );
                        break;
                    }
                  case XCB_VISIBILITY_NOTIFY:
                    {   xcb_visibility_notify_event_t *x_visibility = (P)x_event;
                        G(); Gs0_( "visibility" ); Gd( x_visibility->state );
                        if( !U_R( window->state, visible ))
                        {   if( x_visibility->state != XCB_VISIBILITY_FULLY_OBSCURED )
                            {   U_F( window->state, visible );
                                if( U_R( window->req, resize ))
                                    U_F( window, postproc );
                                else if( U_R( window->req, draw ))
                                    U_F( display->req, draw );
                            }
                        }else if( x_visibility->state == XCB_VISIBILITY_FULLY_OBSCURED )
                            U_L( window->state, visible );
                        break;
                    }
                  case XCB_DESTROY_NOTIFY:
                    {   G(); Gs0_( "destroy" );
                        break;
                    }
                  case XCB_UNMAP_NOTIFY:
                    {   G(); Gs0_( "unmap" );
                        U_L( window->state, visible );
                        break;
                    }
                  case XCB_MAP_NOTIFY:
                    {   G(); Gs0_( "map" );
                        break;
                    }
                  case XCB_REPARENT_NOTIFY:
                    {   G(); Gs0_( "reparent" );
                        break;
                    }
                  case XCB_RESIZE_REQUEST: 
                    {   xcb_resize_request_event_t *x_resize_req = (P)x_event;
                        G(); Gs0_( "resize request" ); Gd( x_resize_req->width ); Gd( x_resize_req->height );
                        if( window->width_new != x_resize_req->width
                        || window->height_new != x_resize_req->height
                        )
                        {   U_F( window->mode, resize );
                            
                                xcb_change_window_attributes( display->x_display
                                , window->x_window
                                , XCB_CW_OVERRIDE_REDIRECT
                                , ( N32[] )
                                  { yes
                                  }
                                );
                            xcb_configure_window( display->x_display
                            , window->x_window
                            , XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
                            , ( N32[] )
                              { x_resize_req->width
                              , x_resize_req->height
                              }
                            );
                            
                                xcb_change_window_attributes( display->x_display
                                , window->x_window
                                , XCB_CW_OVERRIDE_REDIRECT
                                , ( N32[] )
                                  { no
                                  }
                                );
                            U_F( display->req, flush );
                        }
                        break;
                    }
                  case XCB_GRAVITY_NOTIFY:
                    {   G(); Gs0_( "gravity notify" );
                        break;
                    }
                  default:
                        
                        switch( XCB_EVENT_RESPONSE_TYPE( x_event ))
                        { case XCB_CONFIGURE_NOTIFY:
                            {   xcb_configure_notify_event_t *x_configure = (P)x_event;
                                G(); Gs0_( "configure notify" ); Gd( x_configure->above_sibling ); Gd( x_configure->x ); Gd( x_configure->y ); Gd( x_configure->width ); Gd( x_configure->height );
                                
                                window->width_new = x_configure->width;
                                window->height_new = x_configure->height;
                                U_L( window->mode, resize );
                                if( U_R( display->mode, drag_stop )
                                && window == &screen->dnd_window
                                )
                                    break;
                                U_F( window->req, resize );
                                U_F( window, postproc );
                                if( !U_R( display->mode, drag )
                                && !x_configure->above_sibling
                                && ( x_configure->x != window->x
                                  || x_configure->y != window->y
                                ))
                                {   window->x = x_configure->x;
                                    window->y = x_configure->y;
                                    if( window_id == display->pointer_button_S_window_id )
                                        display->pointer_button_S_seq_i = 0;
                                }
                                break;
                            }
                          case XCB_CLIENT_MESSAGE:
                            {   G(); Gs0_( "client" );
                                xcb_client_message_event_t *x_client = (P)x_event;
                                if( x_client->type != E_x_Z_atom_R( display, WM_PROTOCOLS ))
                                {   xcb_get_atom_name_cookie_t ret_id = xcb_get_atom_name_unchecked( display->x_display, x_client->type );
                                    xcb_get_atom_name_reply_t *ret = xcb_get_atom_name_reply( display->x_display, ret_id, 0 );
                                    Pc message_type = xcb_get_atom_name_name(ret);
                                    GV(NKN); Gs0( message_type ); 
                                    free(ret);
                                    break;
                                }
                                xcb_atom_t name = x_client->data.data32[0];
                                if( name == E_x_Z_atom_R( display, _NET_WM_PING ))
                                {   struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, window->screen_id );
                                    x_client->window = screen->x_root_window;
                                    xcb_send_event( display->x_display
                                    , no
                                    , x_client->window
                                    , XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
                                    , (P)x_client
                                    );
                                    U_F( display->req, flush );
                                }else if( name == E_x_Z_atom_R( display, WM_DELETE_WINDOW ))
                                {   if( U_R( display->mode, drag ))
                                        U_F( display->mode, drag_stop );
                                    U_F( window->req, close );
                                    U_F( x_window, close_window );
                                }else
                                {   xcb_get_atom_name_cookie_t ret_id = xcb_get_atom_name_unchecked( display->x_display, x_client->data.data8[0] );
                                    xcb_get_atom_name_reply_t *ret = xcb_get_atom_name_reply( display->x_display, ret_id, 0 );
                                    Pc message_type = xcb_get_atom_name_name(ret);
                                    GV(NKN); Gs0( message_type ); 
                                    free(ret);
                                }
                                break;
                            }
                      }
                      break;
                }
Loop:           free( x_event );
            }while( x_event = xcb_poll_for_queued_event( display->x_display )); 
            
            if( U_R( display->mode, drag_stop )
            && U_E( display->mode, drag )
            )
            {   if( !U_R( display->mode_ex, drag_stop_S_cancel ))
                {   
                    if( U_R( display->mode_ex, drag_S_copy ))
                    {   for_n( i, display->drag_S_object_src_n )
                        {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, display->drag_S_object_src[i].window_id );
                            U_F( window->req, draw );
                            struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, display->drag_S_object_src[i].object_id );
                            U_L( object->mode, drag_src );
                            
                        }
                    }else
                    {   for_n( i, display->drag_S_object_src_n )
                        {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, display->drag_S_object_src[i].window_id );
                            U_F( window->req, draw );
                            
                            if( E_x_Q_object_R_top( window, display->drag_S_object_src[i].object_id ))
                            {   struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, display->drag_S_object_src[i].object_id );
                                U_L( object->mode, drag_src );
                                if( !~E_x_Q_object_I_rem_descendants( window, display->drag_S_object_src[i].object_id ))
                                    U_F( display->req, restart );
                            }
                            else
                                if( !~E_x_Q_object_I_rem( window, display->drag_S_object_src[i].object_id ))
                                    U_F( display->req, restart );
                            E_x_Q_object_I_lay( display, window );
                        }
                    }
                }
                W( display->drag_S_object_src );
                struct E_x_Q_window_Z *dnd_window = &screen->dnd_window;
                E_mem_Q_tab_W( dnd_window->object );
                    #ifdef C_xcb_shape
                xcb_free_pixmap( display->x_display, screen->dnd_window_shape_pixmap );
                    #endif
                xcb_configure_window( display->x_display
                , dnd_window->x_window
                , XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
                , ( N32[] )
                  { E_x_Q_window_S_hidden_x
                  , E_x_Q_window_S_hidden_y
                  , 1
                  , 1
                  }
                );
                W( dnd_window->drawable );
                U_L( dnd_window->req, draw );
                if( U_R( display->req, pointer_S_ungrab ))
                {   if( !U_R( display->state, pointer_button_S_pressing ))
                    {   U_L( display->mode, drag_stop );
                        U_L( display->req, pointer_S_ungrab );
                        xcb_ungrab_pointer( display->x_display, display->pointer_button_S_grab_time );
                        display->pointer_button_S_seq_i = 0;
                    }
                }else
                    U_L( display->mode, drag_stop );
                U_F( display->req, draw );
                U_F( display->req, flush );
            }else if( !U_R( display->mode, drag_stop ) 
            && display->pointer_button_S_seq_i
            )
            {   struct E_x_Q_window_Z *window;
                if( U_R( display->mode, drag ))
                    window = &screen->dnd_window;
                else
                    window = E_mem_Q_tab_R( display->window, display->pointer_button_S_window_id );;
                unsigned event_mask = !U_R( display->mode, drag )
                  ? XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE
                  : XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION;
                xcb_cursor_t cursor = !U_R( display->mode, drag )
                  ? XCB_CURSOR_NONE
                  : !U_R( display->mode_ex, drag_S_copy ) ? display->drag_S_cursor : display->drag_S_copy_cursor;
                if( !U_R( display->mode, drag ))
                    display->pointer_button_S_grab_time = display->pointer_button_S_start_time;
                xcb_grab_pointer_cookie_t ret_id = xcb_grab_pointer_unchecked( display->x_display
                , yes
                , window->x_window
                , event_mask
                , XCB_GRAB_MODE_ASYNC
                , XCB_GRAB_MODE_ASYNC
                , XCB_NONE
                , cursor
                , display->pointer_button_S_grab_time
                );
                xcb_grab_pointer_reply_t *ret = xcb_grab_pointer_reply( display->x_display, ret_id, 0 );
                if( ret->status == XCB_GRAB_STATUS_SUCCESS ) 
                {   free(ret);
                    U_F( display->req, pointer_S_ungrab );
                    xcb_timestamp_t grab_time = display->pointer_button_S_time + ( display->pointer_button_S_seq_i & 1 ? display->pointer_button_C_release_timeout : display->pointer_button_C_seq_timeout );
                    ret_id = xcb_grab_pointer_unchecked( display->x_display
                    , yes
                    , window->x_window
                    , event_mask
                    , XCB_GRAB_MODE_ASYNC
                    , XCB_GRAB_MODE_ASYNC
                    , XCB_NONE
                    , cursor
                    , grab_time
                    );
                    xcb_grab_pointer_reply_t *ret = xcb_grab_pointer_reply( display->x_display, ret_id, 0 );
                    if( ret->status == XCB_GRAB_STATUS_SUCCESS ) 
                    {   free(ret);
                        display->pointer_button_S_grab_time = grab_time;
                        G(); Gs0_( "click" ); Gd( display->pointer_button ); Gd( display->pointer_button_S_seq_i );
                        if( !U_R( display->mode, drag ))
                        {   if( ~display->cursor_window ) 
                            {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, display->cursor_window );
                                struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, display->cursor_object );
                                struct E_x_Q_object_Z_data_Z_entry *object_data = object->data;
                                if( U_E( object_data->state, cursor_visible_ ))
                                    E_x_Q_object_I_draw(window);
                            }
                            I xbutton_object_id;
                            if( display->pointer_button_S_x >= 0
                            && display->pointer_button_S_x < window->width
                            && display->pointer_button_S_y >= 0
                            && display->pointer_button_S_y < window->height
                            )
                                xbutton_object_id = window->object_mask[ display->pointer_button_S_y * window->width + display->pointer_button_S_x ];
                            else
                                xbutton_object_id = ~0;
                            if( ~xbutton_object_id )
                            {   struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, xbutton_object_id );
                                if( U_R( object->mode, draggable )
                                && display->pointer_button_S_seq_i == 1
                                && display->pointer_button == 1
                                ){  if( ~display->cursor_window )
                                        display->cursor_window = ~0;
                                    Mt_( display->drag_S_object_src, 1 );
                                    if( display->drag_S_object_src )
                                    {   struct E_x_Q_window_Z *dnd_window = &screen->dnd_window;
                                        dnd_window->width_new = dnd_window->width = object->width;
                                        dnd_window->height_new = dnd_window->height = object->height;
                                        dnd_window->object = E_mem_Q_tab_M( sizeof( struct E_x_Q_object_Z ), 0 );
                                        if( !dnd_window->object )
                                            goto Drag_start_error;
                                        I dnd_window_object_id = E_x_Q_object_M( display, dnd_window, 0, 0, 0, object->width, object->height, 0, object->draw, 0 );
                                        struct E_x_Q_object_Z *dnd_window_object = E_mem_Q_tab_R( dnd_window->object, dnd_window_object_id );
                                        dnd_window_object->data = object->data;
                                        U_F( object->mode, drag_src );
                                        display->drag_S_object_src[0].window_id = display->pointer_button_S_window_id;
                                        display->drag_S_object_src[0].object_id = xbutton_object_id;
                                        display->drag_S_object_src_n = 1;
                                        N child_expanded_n = 0;
                                        struct E_x_Q_object_Z *parent_object = E_mem_Q_tab_R( window->object, display->drag_S_object_src[ child_expanded_n ].object_id );
                                        while( child_expanded_n != display->drag_S_object_src_n )
                                        {   struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, display->drag_S_object_src[ child_expanded_n ].object_id );
                                            child_expanded_n++;
                                            if( !object->child_n )
                                                continue;
                                            if( !E_mem_Q_blk_I_append( &display->drag_S_object_src, object->child_n ))
                                            {   W( display->drag_S_object_src );
                                                goto Drag_start_error;
                                            }
                                            I parent_id = dnd_window->object->index_n - 1;
                                            for_n( i, object->child_n )
                                            {   struct E_x_Q_object_Z *object_src = E_mem_Q_tab_R( window->object, object->child[i] );
                                                U_F( object_src->mode, drag_src );
                                                display->drag_S_object_src[ display->drag_S_object_src_n + i ].window_id = display->pointer_button_S_window_id;
                                                display->drag_S_object_src[ display->drag_S_object_src_n + i ].object_id = object->child[i];
                                                I dnd_window_object_id = E_x_Q_object_M( display, dnd_window, 0, object_src->x - parent_object->x, object_src->y - parent_object->y, object_src->width, object_src->height, 0, object_src->draw, 0 );
                                                if( !~dnd_window_object_id )
                                                {   W( display->drag_S_object_src );
                                                    for_each( object_id, dnd_window->object, E_mem_Q_tab )
                                                        E_x_Q_object_W( display, dnd_window, object_id );
                                                    goto Drag_start_error;
                                                }
                                                struct E_x_Q_object_Z *dnd_window_object = E_mem_Q_tab_R( dnd_window->object, dnd_window_object_id );
                                                dnd_window_object->data = object_src->data;
                                                G_(); Gd( display->drag_S_object_src[ child_expanded_n ].object_id ); Gd( dnd_window_object_id );
                                                E_x_Q_object_I_add( dnd_window, parent_id, dnd_window_object_id );
                                            }
                                            display->drag_S_object_src_n += object->child_n;
                                        }
                                        U_F( window->req, draw );
                                        screen = E_mem_Q_tab_R( display->screen, window->screen_id );
                                        display->drag_S_pointer_button = display->pointer_button;
                                        display->drag_S_dnd_window_screen_id = window->screen_id;
                                        display->drag_S_grab_x = display->pointer_button_S_x - object->x;
                                        display->drag_S_grab_y = display->pointer_button_S_y - object->y;
                                        xcb_grab_pointer_cookie_t ret_id = xcb_grab_pointer_unchecked( display->x_display
                                        , yes
                                        , dnd_window->x_window
                                        , XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION
                                        , XCB_GRAB_MODE_ASYNC
                                        , XCB_GRAB_MODE_ASYNC
                                        , XCB_NONE
                                        , display->drag_S_cursor
                                        , display->pointer_button_S_grab_time
                                        );
                                        xcb_grab_pointer_reply_t *ret = xcb_grab_pointer_reply( display->x_display, ret_id, 0 );
                                        free(ret);
                                        Mt_( dnd_window->drawable, dnd_window->width * dnd_window->height );
                                        if( !dnd_window->drawable )
                                        {   GV(NA); V();
                                        }
                                        xcb_configure_window( display->x_display
                                        , dnd_window->x_window
                                        , XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_STACK_MODE
                                        , ( N32[] )
                                          { display->pointer_button_S_root_x - display->drag_S_grab_x
                                          , display->pointer_button_S_root_y - display->drag_S_grab_y
                                          , dnd_window->width
                                          , dnd_window->height
                                          , XCB_STACK_MODE_ABOVE
                                          }
                                        );
                                            #ifdef C_xcb_shape
                                        screen->dnd_window_shape_pixmap = xcb_generate_id( display->x_display );
                                        xcb_create_pixmap( display->x_display
                                        , 1
                                        , screen->dnd_window_shape_pixmap
                                        , screen->x_root_window
                                        , dnd_window->width, dnd_window->height
                                        );
                                        
                                        
                                        
                                        
                                            #endif
                                        U_L( dnd_window->mode, resize );
                                        U_L( dnd_window->req, resize );
                                        U_F( dnd_window->req, draw );
                                        U_F( display->mode, drag );
                                        U_L( display->mode_ex, drag_S_copy );
                                        U_F( display->mode_ex, drag_stop_S_cancel );
                                        U_F( display->req, draw );
                                        U_F( display->req, flush );
                                    }else
Drag_start_error:                   {   GV_(NA);
                                    }
                                }else if( display->pointer_button_S_seq_i == 2
                                && display->pointer_button == 1
                                && object->draw == E_x_Q_object_Z_entry_I_draw
                                ){  I cursor_window = display->cursor_window;
                                    display->cursor_window = display->pointer_button_S_window_id;
                                    display->cursor_object = xbutton_object_id;
                                    struct E_x_Q_object_Z_data_Z_entry *object_data = object->data;
                                    S16 click_x = display->pointer_button_S_x - object->x;
                                    object_data->cursor_pos = 0;
                                    struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, object_data->font );
                                    S16 x = 0;
                                    Pc s = object_data->text + object_data->text_start;
                                    while( *s )
                                    {   U u = ~0;
                                        s = E_text_Z_su_R_u( s, &u );
                                        if( !~u )
                                        {   GV_(bad UTF-8 character); V();
                                        }
                                        for_n( i, font->bitmap_n )
                                            if( font->bitmap[i].u == u )
                                            {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                                                break;
                                            }
                                        if( i == font->bitmap_n )
                                            x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
                                        object_data->cursor_pos++;
                                        if( x > click_x )
                                            break;
                                    }
                                    if( !~cursor_window )
                                        U_F( object_data->state, cursor_visible_ );
                                }else
                                {   if( ~display->cursor_window )
                                        display->cursor_window = ~0;
                                    I object_id = xbutton_object_id;
                                    O{  if( object->click )
                                        {   object->click( window, object, display->pointer_button, display->pointer_button_S_seq_i );
                                            break;
                                        }
                                        object_id = E_x_Q_object_R_parent( window, object_id );
                                        if( !~object_id )
                                            break;
                                        object = E_mem_Q_tab_R( window->object, object_id );
                                    }
                                }
                            }else if( ~display->cursor_window )
                                display->cursor_window = ~0;
                        }else
                        {   if( display->pointer_button_S_seq_i == 2
                            && display->pointer_button == 3
                            )
                            {   xcb_change_active_pointer_grab( display->x_display
                                , ( U_R( display->mode_ex, drag_S_copy ) = !U_R( display->mode_ex, drag_S_copy )) ? display->drag_S_copy_cursor : display->drag_S_cursor
                                , display->pointer_button_S_grab_time
                                , event_mask
                                );
                                U_F( display->req, flush );
                            }
                        }
                        if( !U_R( display->mode, drag )
                        && !U_R( display->state, pointer_button_S_pressing )
                        )
                        {   U_L( display->req, pointer_S_ungrab );
                            U_F( display->req, flush );
                            xcb_ungrab_pointer( display->x_display, display->pointer_button_S_grab_time );
                        }
                        display->pointer_button_S_seq_i = 0;
                    }else
                    {   free(ret);
                            #ifdef E_flow_C_thread_system_unblock_reports
                        if( display->pointer_button_S_impulser_time != grab_time )
                        {   display->pointer_button_S_impulser_time = grab_time;
                            Yi_F( x_window, events_pointer_button_check, ( display->pointer_button_S_seq_i & 1 ? display->pointer_button_C_release_timeout : display->pointer_button_C_seq_timeout ) * 1000 );
                        }
                            #endif
                    }
                }else
                {   free(ret);
                        #ifdef E_flow_C_thread_system_unblock_reports
                    Yi_L( x_window, events_pointer_button_check );
                        #endif
                    if( U_R( display->mode, drag ))
                        U_F( display->mode, drag_stop );
                    display->pointer_button_S_seq_i = 0;
                }
            }else if( !U_R( display->mode, drag )
            && !U_R( display->state, pointer_button_S_pressing )
            && U_E( display->req, pointer_S_ungrab )
            )
            {   U_L( display->mode, drag_stop );
                U_F( display->req, flush );
                xcb_ungrab_pointer( display->x_display, display->pointer_button_S_grab_time ); 
            }
            if( U_R( display->mode, drag )
            && U_R( drag, motion )
            )
            {   
                if( !U_R( drag_S_motion, oth_screen )
                || drag_S_motion_x_root_window == screen->x_root_window
                )
                {   xcb_configure_window( display->x_display
                    , screen->dnd_window.x_window
                    , XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y
                    , ( N32[] )
                      { drag_S_motion_root_x - display->drag_S_grab_x
                      , drag_S_motion_root_y - display->drag_S_grab_y
                      }
                    );
                    U_F( display->req, flush );
                }else
                {   struct E_x_Q_screen_Z *screen_last = screen;
                    for_each( screen_id, display->screen, E_mem_Q_tab )
                    {   screen = E_mem_Q_tab_R( display->screen, screen_id );
                        if( drag_S_motion_x_root_window == screen->x_root_window )
                            break;
                    }
                    display->drag_S_dnd_window_screen_id = screen_id;
                    struct E_x_Q_window_Z *dnd_window = &screen_last->dnd_window;
                    
                    xcb_configure_window( display->x_display
                    , dnd_window->x_window
                    , XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
                    , ( N32[] )
                      { E_x_Q_window_S_hidden_x
                      , E_x_Q_window_S_hidden_y
                      , 1
                      , 1
                      }
                    );
                    W( dnd_window->drawable );
                    dnd_window = &screen->dnd_window;
                    Mt_( dnd_window->drawable, dnd_window->width * dnd_window->height );
                    if( !dnd_window->drawable )
                    {   GV(NA); V();
                    }
                    xcb_configure_window( display->x_display
                    , dnd_window->x_window
                    , XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
                    , ( N32[] )
                      { drag_S_motion_root_x - display->drag_S_grab_x
                      , drag_S_motion_root_y - display->drag_S_grab_y
                      , dnd_window->width
                      , dnd_window->height
                      }
                    );
                    xcb_grab_pointer_cookie_t ret_id = xcb_grab_pointer_unchecked( display->x_display
                    , yes
                    , dnd_window->x_window
                    , XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION
                    , XCB_GRAB_MODE_ASYNC
                    , XCB_GRAB_MODE_ASYNC
                    , XCB_NONE
                    , U_R( display->mode_ex, drag_S_copy ) ? display->drag_S_copy_cursor : display->drag_S_cursor
                    , display->pointer_button_S_grab_time
                    );
                    xcb_discard_reply( display->x_display, ret_id.sequence );
                    U_F( dnd_window->req, draw );
                    U_F( display->req, draw );
                    U_F( display->req, flush );
                }
            }
            if( U_R( window, postproc ))
            {   if( U_R( display->mode, drag ))
                {   struct E_x_Q_window_Z *window = &screen->dnd_window;
                    if( U_E( window->req, resize )
                    && ( window->width != window->width_new
                      || window->height != window->height_new
                    ))
                    {   window->width = window->width_new;
                        window->height = window->height_new;
                        W( window->drawable );
                        Mt_( window->drawable, window->width * window->height );
                        if( !window->drawable )
                        {   GV(NA); V();
                        }
                        U_F( window->req, draw );
                        U_F( display->req, draw );
                    }
                    if( window->user_activity_time > window->last_user_activity_time )
                    {   E_x_Z_property_P_v( display, window, _NET_WM_USER_TIME
                        , CARDINAL
                        , window->user_activity_time
                        );
                        window->last_user_activity_time = window->user_activity_time;
                        U_F( display->req, flush );
                    }
                }
                for_each( window_id, display->window, E_mem_Q_tab )
                {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
                    if( U_R( window->state, visible )
                    && U_E( window->req, resize )
                    )
                        if( window->width != window->width_new
                        || window->height != window->height_new
                        )
                        {   window->width = window->width_new;
                            window->height = window->height_new;
                            W( window->object_mask );
                            W( window->drawable );
                            Mt_( window->drawable, window->width * window->height );
                            if( !window->drawable )
                            {   GV(NA); V();
                            }
                            Mt_( window->object_mask, window->width * window->height );
                            if( !window->object_mask )
                            {   GV(NA); V();
                            }
                            for_n( i, window->width * window->height )
                                window->object_mask[i] = ~0;
                            U_F( window->req, draw );
                            U_F( display->req, draw );
                            E_x_Q_object_I_lay( display, window );
                        }else if( U_R( window->req, draw ))
                            U_F( display->req, draw );
                    if( window->user_activity_time > window->last_user_activity_time )
                    {   E_x_Z_property_P_v( display, window, _NET_WM_USER_TIME
                        , CARDINAL
                        , window->user_activity_time
                        );
                        window->last_user_activity_time = window->user_activity_time;
                        U_F( display->req, flush );
                    }
                }
            }
            if( U_R( display->req, draw ))
                U_F( x_window, draw );
            if( U_R( display->req, flush ))
                U_F( x_window, flush );
        }
        X_U( x_window, close_window );
        X_U( x_window, draw );
        X_U( x_window, flush );
            #ifndef E_flow_C_thread_system_unblock_reports
        Y_B( timer, 0 )
            break;
            #endif
    }
        #ifndef E_flow_C_thread_system_unblock_reports
    Y_W(timer);
        #else
    D_W( x_window, events_pointer_button_check );
#endif
}
_internal I D_id( x_window, draw ) = ~0; D( x_window, draw )
{   X_M( x_window, draw );
    X_A( x_window, flush );
    I_D
    {   X_B( x_window, draw, 0 )
            break;
        for_each( display_id, E_x_Q_display_S, E_mem_Q_tab )
        {   struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
            if( U_E( display->req, draw ))
            {   for_each( window_id, display->window, E_mem_Q_tab )
                {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
                    if( U_R( window->state, visible )
                    && !U_R( window->mode, resize )
                    && U_E( window->req, draw )
                    )
                    {   struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, window->screen_id );
                        for_n( i, window->width * window->height )
                            window->drawable[i] = E_x_Q_theme.window_bg;
                        for_n_( i, window->width * window->height )
                            window->object_mask[i] = ~0;
                        for_each( object_id, window->object, E_mem_Q_tab ) 
                        {   display->current_object = object_id;
                            struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
                            if( U_R( object->mode, drag_src ))
                                screen->draw_color = E_x_Q_theme.current_brace;
                            object->draw( display, screen, window, object ); 
                        }
                        xcb_put_image( display->x_display
                        , XCB_IMAGE_FORMAT_Z_PIXMAP
                        , window->x_window
                        , screen->drawable_gc
                        , window->width, window->height
                        , 0, 0
                        , 0
                        , 24
                        , window->width * window->height * sizeof(N32)
                        , (P)window->drawable
                        );
                        U_F( display->req, flush );
                    }
                }
            }
            if( U_R( display->mode, drag ))
            {   struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, display->drag_S_dnd_window_screen_id );
                struct E_x_Q_window_Z *window = &screen->dnd_window;
                if( !U_R( window->mode, resize )
                && U_E( window->req, draw )
                )
                {   for_n( i, window->width * window->height )
                        window->drawable[i] = E_x_Q_theme.window_bg;
                        #ifdef C_xcb_shape
                    xcb_poly_fill_rectangle( display->x_display
                    , screen->dnd_window_shape_pixmap
                    , screen->bitmask_0_gc
                    , 1
                    , ( xcb_rectangle_t [] )
                      { 0, 0
                      , window->width, window->height
                      }
                    );
                        #endif
                    U_F( screen->state, draw_object_drag_move );
                    for_each( object_id, window->object, E_mem_Q_tab )
                    {   struct E_x_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
                        object->draw( display, screen, window, object );
                    }
                    U_L( screen->state, draw_object_drag_move );
                        #ifdef C_xcb_shape
                    xcb_shape_mask( display->x_display
                    , XCB_SHAPE_SO_SET
                    , XCB_SHAPE_SK_BOUNDING
                    , window->x_window
                    , 0, 0
                    , screen->dnd_window_shape_pixmap
                    );
                        #endif
                    xcb_put_image( display->x_display
                    , XCB_IMAGE_FORMAT_Z_PIXMAP
                    , window->x_window
                    , screen->drawable_gc
                    , window->width, window->height
                    , 0, 0
                    , 0
                    , 24
                    , window->width * window->height * sizeof(N32)
                    , (P)window->drawable
                    );
                    U_F( display->req, flush );
                }
            }
            if( U_R( display->req, flush ))
                U_F( x_window, flush );
            U_L( display->mode, draw_simple );
        }
        X_U( x_window, flush );
    }
    X_W( x_window, draw );
}
_internal I D_id( x_window, flush ) = ~0; D( x_window, flush )
{   X_M( x_window, flush );
    I_D
    {   X_B( x_window, flush, 0 )
            break;
        for_each( display_id, E_x_Q_display_S, E_mem_Q_tab )
        {   struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
            if( U_E( display->req, flush ))
                xcb_flush( display->x_display );
        }
    }
    X_W( x_window, flush );
}


