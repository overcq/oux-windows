
























_internal
N32 *E_x_S_wm_icon;
_internal
N E_x_S_wm_icon_S_n;

_internal
struct E_x_Z_keysym_to_unicode *E_x_S_keysym_to_unicode;
_internal
N E_x_S_keysym_to_unicode_n;

_internal
S16 E_x_Q_window_S_hidden_x;
_internal
S16 E_x_Q_window_S_hidden_y;

struct E_x_Q_window_Z


















;
struct E_x_Q_screen_Z
















;

struct E_x_Z_drag_object_src


;
struct E_x_Z_keysym_to_unicode


;




struct E_x_Q_display_Z












































;
struct E_mem_Q_tab_Z *E_x_Q_display_S;

I
E_x_Q_display_M( void
){  I display_id = E_mem_Q_tab_I_add( E_x_Q_display_S );
    if( !~display_id )
        return ~0;
    struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
    
    int x_screen_id_default_;
    display->x_display = xcb_connect( 0, &x_screen_id_default_ );
    display->Z_screen_id_S_default = x_screen_id_default_;
    Mt_( display->atom, XCB_ATOM_AFTER_LAST - XCB_ATOM_FIRST_DEFINED );
    if( !display->atom )
    {   E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
        return ~0;
    }
#define _(atom) J_s(atom)
    Pc atom_name[ XCB_ATOM_AFTER_LAST - XCB_ATOM_FIRST_DEFINED ] =
    { _( XCB_ATOM_FIRST_DEFINED_ )
      E_x_Z_atom_J_atoms_
    };
#undef _
    xcb_intern_atom_cookie_t atom_req_id[ XCB_ATOM_AFTER_LAST - XCB_ATOM_FIRST_DEFINED ];
    for_n( i, XCB_ATOM_AFTER_LAST - XCB_ATOM_FIRST_DEFINED )
        atom_req_id[i] = xcb_intern_atom_unchecked( display->x_display
        , no
        , E_text_Z_s0_R_l( atom_name[i] )
        , atom_name[i]
        );
    for_n_( i, XCB_ATOM_AFTER_LAST - XCB_ATOM_FIRST_DEFINED )
    {   xcb_intern_atom_reply_t *ret = xcb_intern_atom_reply( display->x_display, atom_req_id[i], 0 );
        display->atom[i] = ret->atom;
        free(ret);
    }
    display->red_luminance_ratio = 0.2126; 
    display->green_luminance_ratio = 0.7152; 
    display->blue_luminance_ratio = 0.0722; 
    display->pointer_button_C_release_timeout = 183; 
    display->pointer_button_C_seq_timeout = 183; 
    display->pointer_button_C_restart_delay = 360; 
    display->pointer_button_S_time = 0;
        #ifdef E_flow_C_thread_system_unblock_reports
    display->pointer_button_S_impulser_time = 0;
        #endif
    display->pointer_button_S_seq_i = 0;
    display->drag_S_dnd_window_screen_id = 0;
    xcb_font_t font = xcb_generate_id( display->x_display );
    xcb_open_font( display->x_display
    , font
    , 7
    , "cursor"
    );
    display->drag_S_cursor = xcb_generate_id( display->x_display );
    xcb_create_glyph_cursor( display->x_display
    , display->drag_S_cursor
    , font
    , font
    , 102
    , 102
    , ~0, ~0, ~0
    , 0, 0, 0
    );
    display->drag_S_copy_cursor = xcb_generate_id( display->x_display );
    xcb_create_glyph_cursor( display->x_display
    , display->drag_S_copy_cursor
    , font
    , font
    , 90
    , 90
    , ~0, ~0, ~0
    , 0, 0, 0
    );
    xcb_close_font( display->x_display, font );
    display->class_name_l = E_text_Z_s0_R_0_l( E_base_S->E_flow_S_exe_name ) + E_text_Z_s0_R_0_l( E_base_S->E_flow_S_system_name );
    display->class_name = M( display->class_name_l );
    if( !display->class_name )
    {   W( display->atom );
        xcb_disconnect( display->x_display );
        E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
        return ~0;
    }
    E_text_Z_s_P_s0_copy_0( E_text_Z_s_P_s0_copy_0( display->class_name, E_base_S->E_flow_S_exe_name ), E_base_S->E_flow_S_system_name );
    display->setup = xcb_get_setup( display->x_display );
    xcb_get_keyboard_mapping_cookie_t keyboard_mapping_req_id = xcb_get_keyboard_mapping_unchecked( display->x_display, display->setup->min_keycode, 135 ); 
    display->keyboard_mapping = xcb_get_keyboard_mapping_reply( display->x_display, keyboard_mapping_req_id, 0 );
    xcb_xkb_use_extension_cookie_t xkb_use_extension_req_id = xcb_xkb_use_extension_unchecked( display->x_display, 1, 0 );
    xcb_xkb_use_extension_reply_t *ret = xcb_xkb_use_extension_reply( display->x_display, xkb_use_extension_req_id, 0 );
    free(ret);
    display->xkb_keyboard = xkb_x11_get_core_keyboard_device_id( display->x_display );
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator( display->setup );
    display->screen = E_mem_Q_tab_M( sizeof( struct E_x_Q_screen_Z ), screen_iter.rem );
    I screen_id = 0;
    do
    {   G(); Gd( screen_id );
        struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, screen_id );
        screen->dpi_x = 25.4 * screen_iter.data->width_in_pixels / screen_iter.data->width_in_millimeters;
        screen->dpi_y = 25.4 * screen_iter.data->height_in_pixels / screen_iter.data->height_in_millimeters;
        screen->pixel_width = (F)screen_iter.data->width_in_millimeters / screen_iter.data->width_in_pixels;
        screen->pixel_height = (F)screen_iter.data->height_in_millimeters / screen_iter.data->height_in_pixels;
        screen->draw_color = 0;
        screen->x_root_window = screen_iter.data->root;
        screen->depth = screen_iter.data->root_depth;
        screen->drawable_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->drawable_gc
        , screen_iter.data->root
        , XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { no
          }
        );
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        screen->drawable_background_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->drawable_background_gc
        , screen_iter.data->root
        , XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { E_x_Q_theme.window_bg
          , no
          }
        );
        
        xcb_copy_gc( display->x_display, screen->drawable_background_gc, screen->drawable_gc, XCB_GC_TILE );
        xcb_pixmap_t pixmap_obj_wa = xcb_generate_id( display->x_display );
        xcb_create_pixmap( display->x_display
        , E_x_Q_obj_C_id_bits
        , pixmap_obj_wa
        , screen_iter.data->root
        , 1, 1
        );
        screen->object_mask_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->object_mask_gc
        , pixmap_obj_wa
        , XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { no
          }
        );
        xcb_free_pixmap( display->x_display, pixmap_obj_wa );
        xcb_pixmap_t pixmap_1_wa = xcb_generate_id( display->x_display );
        xcb_create_pixmap( display->x_display
        , 1
        , pixmap_1_wa
        , screen_iter.data->root
        , 1, 1
        );
        screen->bitmask_1_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->bitmask_1_gc
        , pixmap_1_wa
        , XCB_GC_FUNCTION | XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { XCB_GX_SET
          , no
          }
        );
        screen->bitmask_0_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->bitmask_0_gc
        , pixmap_1_wa
        , XCB_GC_FUNCTION | XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { XCB_GX_CLEAR
          , no
          }
        );
        screen->bitmask_not_and_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->bitmask_not_and_gc
        , pixmap_1_wa
        , XCB_GC_FUNCTION | XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { XCB_GX_AND_INVERTED
          , no
          }
        );
        screen->bitmask_or_gc = xcb_generate_id( display->x_display );
        xcb_create_gc( display->x_display
        , screen->bitmask_or_gc
        , pixmap_1_wa
        , XCB_GC_FUNCTION | XCB_GC_GRAPHICS_EXPOSURES
        , ( N32[] )
          { XCB_GX_OR
          , no
          }
        );
        xcb_free_pixmap( display->x_display, pixmap_1_wa );
        
        
        struct E_x_Q_window_Z *dnd_window = &screen->dnd_window;
        dnd_window->x_window = xcb_generate_id( display->x_display );
        xcb_create_window( display->x_display
        , XCB_COPY_FROM_PARENT
        , dnd_window->x_window
        , screen_iter.data->root
        , E_x_Q_window_S_hidden_x
        , E_x_Q_window_S_hidden_y
        , 1
        , 1
        , 0
        , XCB_WINDOW_CLASS_INPUT_OUTPUT
        , XCB_COPY_FROM_PARENT
        , XCB_CW_BIT_GRAVITY | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_EVENT_MASK
        , ( N32[] )
          { XCB_GRAVITY_STATIC
          , yes
          , XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_RESIZE_REDIRECT
          }
        );
            #ifdef C_xcb_glx
        xcb_glx_get_fb_configs_cookie_t ret_id = xcb_glx_get_fb_configs_unchecked( display->x_display, screen_id );
        xcb_glx_get_fb_configs_reply_t *ret = xcb_glx_get_fb_configs_reply( display->x_display, ret_id, 0 );
        screen->glx_fbconfig = ; 
        free(ret);
        dnd_window->glx_window = xcb_generate_id( display->x_display );
        xcb_glx_create_window( display->x_display
        , screen_id
        , screen->glx_fbconfig
        , dnd_window->x_window
        , dnd_window->glx_window
        , 0
        , 0
        );
            #endif
        E_x_Z_property_P( display, dnd_window, WM_HINTS
        , WM_HINTS
        , (( xcb_icccm_wm_hints_t )
          { .flags = XCB_ICCCM_WM_HINT_INPUT | XCB_ICCCM_WM_HINT_STATE
          , .input = no
          , .initial_state = XCB_ICCCM_WM_STATE_NORMAL
          })
        );
        E_x_Z_property_P_text( display, dnd_window, WM_CLASS
        , STRING
        , display->class_name, display->class_name_l
        );
        E_x_Z_property_P( display, dnd_window, WM_PROTOCOLS
        , ATOM
        , (( xcb_atom_t[] )
          { E_x_Z_atom_R( display, WM_DELETE_WINDOW )
          , E_x_Z_atom_R( display, _NET_WM_PING )
          })
        );
        E_x_Z_property_P_atom( display, dnd_window, _NET_WM_WINDOW_TYPE
        , _NET_WM_WINDOW_TYPE_DND
        );
        E_x_Z_property_P_text( display, dnd_window, WM_CLIENT_MACHINE
        , STRING
        , E_base_S->E_flow_S_hostname, ~0
        );
        E_x_Z_property_P_v( display, dnd_window, _NET_WM_PID
        , CARDINAL
        , E_base_S->E_flow_S_exe_pid
        );
        E_x_Z_property_P_v( display, dnd_window, _NET_WM_BYPASS_COMPOSITOR
        , CARDINAL
        , yes
        );
        xcb_map_window( display->x_display, dnd_window->x_window );
        U_L( dnd_window->req, close );
        U_L( screen->state, draw_object_drag_move );
        U_L( screen->mode, animation );
    }while( screen_iter.rem != 1
    && ( xcb_screen_next( &screen_iter ), screen_id++, yes ));
    display->window = E_mem_Q_tab_M( sizeof( struct E_x_Q_window_Z ), 0 );
    if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
    {   D_M( x_window, flush )
        {   E_mem_Q_tab_W( display->window );
            E_mem_Q_tab_W( display->screen );
            W( display->class_name );
            W( display->atom );
            xcb_disconnect( display->x_display );
            E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
            return ~0;
        }
        D_M( x_window, draw )
        {   if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
                D_W( x_window, flush );
            E_mem_Q_tab_W( display->window );
            E_mem_Q_tab_W( display->screen );
            W( display->class_name );
            W( display->atom );
            xcb_disconnect( display->x_display );
            E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
            return ~0;
        }
            #ifndef E_flow_C_thread_system_unblock_reports
        D_M( x_window, events )
        {   if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
            {   D_W( x_window, draw );
                D_W( x_window, flush );
            }
            E_mem_Q_tab_W( display->window );
            E_mem_Q_tab_W( display->screen );
            W( display->class_name );
            W( display->atom );
            xcb_disconnect( display->x_display );
            E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
            return ~0;
        }
            #endif
    }
        #ifdef E_flow_C_thread_system_unblock_reports
    I *M_( thread_proc_arg );
    if( !thread_proc_arg )
    {   if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
        {   D_W( x_window, draw );
            D_W( x_window, flush );
        }
        E_mem_Q_tab_W( display->window );
        E_mem_Q_tab_W( display->screen );
        W( display->class_name );
        W( display->atom );
        xcb_disconnect( display->x_display );
        E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
        return ~0;
    }
    *thread_proc_arg = display_id;
    Dh_M( x_window, events, display_id, thread_proc_arg )
    {   W( thread_proc_arg );
        if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
        {   D_W( x_window, draw );
            D_W( x_window, flush );
        }
        E_mem_Q_tab_W( display->window );
        E_mem_Q_tab_W( display->screen );
        W( display->class_name );
        W( display->atom );
        xcb_disconnect( display->x_display );
        E_mem_Q_tab_I_remove( E_x_Q_display_S, display_id );
        return ~0;
    }
        #endif
    display->cursor_window = ~0;
    U_L( display->state, pointer_S_in_window );
    U_L( display->mode, drag );
    U_L( display->mode, drag_stop );
    U_L( display->mode, draw_simple );
    U_L( display->req, pointer_S_ungrab );
    U_L( display->req, draw );
    
    U_F( display->req, flush );
    U_L( display->req, restart );
    return display_id;
}
void
E_x_Q_display_W( I id
){  struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, id );
        #ifdef E_flow_C_thread_system_unblock_reports
    Dh_W( x_window, events, id );
        #endif
    if( E_mem_Q_tab_R_n( E_x_Q_display_S ) == 1 )
    {
            #ifndef E_flow_C_thread_system_unblock_reports
        D_W( x_window, events );
            #endif
        D_W( x_window, draw );
        D_W( x_window, flush );
    }
    xcb_disconnect( display->x_display );
    if( U_R( display->mode, drag ))
    {   W( display->drag_S_object_src );
        struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, display->drag_S_dnd_window_screen_id );
        E_mem_Q_tab_W( screen->dnd_window.object );
    }
    for_each_rev( window_id, display->window, E_mem_Q_tab )
    {   struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
        E_mem_Q_tab_W( window->object );
    }
    E_mem_Q_tab_W( display->window );
    E_mem_Q_tab_W( display->screen );
    free( display->keyboard_mapping );
    W( display->class_name );
    W( display->atom );
    E_mem_Q_tab_I_remove( E_x_Q_display_S, id );
}

I
E_x_Q_window_M( I display_id
, I screen_id
, N width
, N height
){  struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
    I window_id = E_mem_Q_tab_I_add( display->window );
    if( !~window_id )
        return ~0;
    struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
    window->screen_id = ~screen_id ? screen_id : display->Z_screen_id_S_default;
    struct E_x_Q_screen_Z *screen = E_mem_Q_tab_R( display->screen, window->screen_id );
    window->x = 0;
    window->y = 0;
    window->width_new = window->width = width;
    window->height_new = window->height = height;
    window->object = E_mem_Q_tab_M( sizeof( struct E_x_Q_object_Z ), 0 );
    window->drawable = xcb_generate_id( display->x_display );
    xcb_create_pixmap( display->x_display
    , screen->depth
    , window->drawable
    , screen->x_root_window
    , window->width, window->height
    );
    window->drawable_mask = xcb_generate_id( display->x_display );
    xcb_create_pixmap( display->x_display
    , 1
    , window->drawable_mask
    , screen->x_root_window
    , window->width, window->height
    );
    window->drawable_mask_2 = xcb_generate_id( display->x_display );
    xcb_create_pixmap( display->x_display
    , 1
    , window->drawable_mask_2
    , screen->x_root_window
    , window->width, window->height
    );
    xcb_poly_fill_rectangle( display->x_display
    , window->drawable_mask_2
    , screen->bitmask_1_gc
    , 1
    , ( xcb_rectangle_t[] )
      { 0
      , 0
      , window->width
      , window->height
      }
    );
    window->object_mask = xcb_generate_id( display->x_display );
    xcb_create_pixmap( display->x_display
    , E_x_Q_obj_C_id_bits
    , window->object_mask
    , screen->x_root_window
    , window->width, window->height
    );
    window->user_activity_time = window->last_user_activity_time = 0;
    window->x_window = xcb_generate_id( display->x_display );
    xcb_create_window( display->x_display
    , XCB_COPY_FROM_PARENT
    , window->x_window
    , screen->x_root_window
    , window->x, window->y, window->width, window->height, 0
    , XCB_WINDOW_CLASS_INPUT_OUTPUT
    , XCB_COPY_FROM_PARENT 
    , XCB_CW_BIT_GRAVITY | XCB_CW_EVENT_MASK
    , ( N32[] )
      { XCB_GRAVITY_STATIC
      , XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW | XCB_EVENT_MASK_VISIBILITY_CHANGE | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_RESIZE_REDIRECT | XCB_EVENT_MASK_FOCUS_CHANGE
      }
    );
        #ifdef C_xcb_glx
    window->glx_window = xcb_generate_id( display->x_display );
    xcb_glx_create_window( display->x_display
    , window->screen_id
    , screen->glx_fbconfig
    , window->x_window
    , window->glx_window
    , 0
    , 0
    );
        #endif
    E_x_Z_property_P_text( display, window, WM_NAME
    , C_STRING 
    , E_base_S->E_flow_S_exe_name, ~0
    );
    E_x_Z_property_P_text( display, window, _NET_WM_NAME
    , UTF8_STRING
    , E_base_S->E_flow_S_exe_name, ~0
    );
    E_x_Z_property_P_text( display, window, WM_ICON_NAME
    , C_STRING 
    , E_base_S->E_flow_S_exe_name, ~0
    );
    E_x_Z_property_P_text( display, window, _NET_WM_ICON_NAME
    , UTF8_STRING
    , E_base_S->E_flow_S_exe_name, ~0
    );
    E_x_Z_property_P( display, window, WM_NORMAL_HINTS
    , WM_SIZE_HINTS
    , (( xcb_size_hints_t )
      { .flags = XCB_ICCCM_SIZE_HINT_P_MIN_SIZE
      , .min_width = 140
      , .min_height = 80
      })
    );
    E_x_Z_property_P( display, window, WM_HINTS
    , WM_HINTS
    , (( xcb_icccm_wm_hints_t )
      { .flags = XCB_ICCCM_WM_HINT_INPUT | XCB_ICCCM_WM_HINT_STATE
      , .input = yes
      , .initial_state = XCB_ICCCM_WM_STATE_NORMAL
      })
    );
    E_x_Z_property_P_text( display, window, WM_CLASS
    , STRING
    , display->class_name, display->class_name_l 
    );
    
    E_x_Z_property_P( display, window, WM_PROTOCOLS
    , ATOM
    , (( xcb_atom_t[] )
      { E_x_Z_atom_R( display, WM_DELETE_WINDOW )
      , E_x_Z_atom_R( display, _NET_WM_PING )
      })
    );
    E_x_Z_property_P_atom( display, window, _NET_WM_WINDOW_TYPE
    , _NET_WM_WINDOW_TYPE_NORMAL
    );
    E_x_Z_property_P_( display, window, _NET_WM_ICON
    , CARDINAL
    , 32
    , E_x_S_wm_icon_S_n
    , E_x_S_wm_icon
    );
    E_x_Z_property_P_text( display, window, WM_CLIENT_MACHINE
    , STRING
    , E_base_S->E_flow_S_hostname, ~0
    );
    E_x_Z_property_P_v( display, window, _NET_WM_PID
    , CARDINAL
    , E_base_S->E_flow_S_exe_pid
    );
    E_x_Z_property_P_v( display, window, _NET_WM_BYPASS_COMPOSITOR
    , CARDINAL
    , yes
    );
    xcb_map_window( display->x_display, window->x_window );
    U_L( window->state, visible );
    U_L( window->mode, resize );
    U_L( window->req, resize );
    U_F( window->req, draw );
    U_F( window->req_ex, draw_S_set_background_pixmap );
    U_L( window->req, close );
    U_F( display->req, draw );
    U_L( display->req, flush );
    return window_id;
}
void
E_x_Q_window_W( I display_id
, I window_id
){  struct E_x_Q_display_Z *display = E_mem_Q_tab_R( E_x_Q_display_S, display_id );
    struct E_x_Q_window_Z *window = E_mem_Q_tab_R( display->window, window_id );
        #ifdef C_xcb_glx
    xcb_glx_delete_window( display->x_display, window->glx_window );
        #endif
    xcb_destroy_window( display->x_display, window->x_window );
    xcb_free_pixmap( display->x_display, window->object_mask );
    xcb_free_pixmap( display->x_display, window->drawable_mask_2 );
    xcb_free_pixmap( display->x_display, window->drawable_mask );
    xcb_free_pixmap( display->x_display, window->drawable );
    E_mem_Q_tab_W( window->object );
    E_mem_Q_tab_I_remove( display->window, window_id );
    if( U_R( display->mode, drag ))
    {   for_n( i, display->drag_S_object_src_n )
            if( display->drag_S_object_src[i].window_id == window_id )
            {   U_F( display->mode, drag_stop );
                    #ifdef E_flow_C_thread_system_unblock_reports
                E_flow_Q_thread_system_unblock_report_I_unblock( D_id(x_window,events), display_id );
                    #endif
                break;
            }
    }
    U_F( display->req, flush );
}

xcb_keysym_t
E_x_Q_display_R_keysym( struct E_x_Q_display_Z *display
, xcb_keycode_t keycode
, N keysym_pos
){  J_assert( keycode >= display->setup->min_keycode );
    J_assert( keysym_pos < display->keyboard_mapping->keysyms_per_keycode );
    xcb_keysym_t *keysyms = (P)( display->keyboard_mapping + 1 );
    return keysyms[ ( keycode - display->setup->min_keycode ) * display->keyboard_mapping->keysyms_per_keycode + keysym_pos ];
}
U
E_x_Q_display_I_keysym_to_unicode( struct E_x_Q_display_Z *display
, xcb_keysym_t keysym
){  if(( keysym >= 0x20 && keysym <= 0x7e )
    || ( keysym >= 0xa0 && keysym <= 0xff )
    )
        return keysym;
    if(( keysym & 0xff000000 ) == 0x1000000 )
        return keysym & 0xffffff;
    S first = 0, last = E_x_S_keysym_to_unicode_n;
    S i;
    do
    {   i = first + ( last - first ) / 2;
        if( keysym == E_x_S_keysym_to_unicode[i].keysym )
            return E_x_S_keysym_to_unicode[i].u;
        if( keysym < E_x_S_keysym_to_unicode[i].keysym )
            last = i - 1;
        else
            first = i + 1;
    }while( first <= last );
    return ~0;
}

N32
E_x_Q_image_R_pixel( struct E_x_Q_display_Z *display
, xcb_pixmap_t pixmap
, S16 x
, S16 y
){  J_assert( x >= 0 );
    J_assert( y >= 0 );
    xcb_get_image_cookie_t ret_id = xcb_get_image_unchecked( display->x_display
    , XCB_IMAGE_FORMAT_Z_PIXMAP
    , pixmap
    , x, y, 1, 1
    , ~0 
    );
    xcb_get_image_reply_t *ret = xcb_get_image_reply( display->x_display, ret_id, 0 ); 
    N32 pixel = *( N32 * )xcb_get_image_data(ret) & 0xffffff;
    free(ret);
    return pixel;
}


