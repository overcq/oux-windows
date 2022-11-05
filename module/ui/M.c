








_internal
void
E_ui_M_ncurses( void
){  E_ncurses_Q_layout_S = E_mem_Q_tab_M( sizeof( struct E_ncurses_Q_field_Z ), 0 );
    E_ncurses_I_getch_S_meta_key = no;
    setupterm( 0, STDERR_FILENO, 0 );
    int max_x, max_y;
    max_x = tigetnum( "cols" );
    max_y = tigetnum( "lines" );
    del_curterm( cur_term );
    int tty_master, tty_slave;
    Pc tty_name = M(1024); 
    V1_( openpty( &tty_master, &tty_slave, tty_name, 0, 0 ));
    pid_t pid = E_flow_I_fork_I_begin();
    if( !pid )
    {   E_flow_I_fork_I_start();
        VO1_( close( tty_slave ));
        N l = E_text_Z_n_N_s_G( max_x, sizeof( max_x ), 10 ) + 1 + E_text_Z_n_N_s_G( max_y, sizeof( max_y ), 10 );
        Pc s_geometry = M( l + 1 );
        s_geometry[l] = '\0';
        s_geometry = E_text_Z_n_N_s( s_geometry + l, max_y, sizeof( max_y ), 10 );
        *--s_geometry = 'x';
        s_geometry = E_text_Z_n_N_s( s_geometry, max_x, sizeof( max_x ), 10 );
        l = E_text_Z_n_N_s_G( tty_master, sizeof( tty_master ), 10 );
        Pc s = M( l + 1 );
        s[l] = '\0';
        E_text_Z_n_N_s( s + l, tty_master, sizeof( tty_master ), 10 );
        struct E_flow_Z_args args[1];
        args[0].argc = 6;
        args[0].argv = ( Pc [] ){ "urxvt", "-geometry", s_geometry, "-pty-fd", s, "-resize-signal-parent" };
        E_flow_I_fork_I_exec( 0, args, 1 );
        W(s);
        l = 2 + E_text_Z_s0_R_l( tty_name ) + 1 + E_text_Z_n_N_s_G( tty_master, sizeof( tty_master ), 10 );
        s = M( l + 1 );
        s[l] = '\0';
        E_text_Z_n_N_s( s + l, tty_master, sizeof( tty_master ), 10 );
        E_text_Z_s_P_s0_copy( E_text_Z_s_P_s0_copy( E_text_Z_s_P_s0_copy( s, "-S" ), tty_name ), "/" );
        args[0].argc = 4;
        args[0].argv = ( Pc [] ){ "xterm", "-geometry", s_geometry, s };
        E_flow_I_fork_I_exec( 0, args, 1 );
    }
    E_flow_I_fork_I_end(pid);
    W( tty_name );
    VO1_( close( tty_master ));
    FILE *file;
    Vp_( file = fdopen( tty_slave, "r+" ));
    Vp_( E_ncurses_S_screen = newterm( 0, file, file ));
    start_color();
    init_pair( 1, COLOR_WHITE, COLOR_BLACK ); 
    init_pair( 2, COLOR_BLACK, COLOR_WHITE ); 
    init_pair( 3, COLOR_BLACK, COLOR_RED ); 
    attr_set( A_NORMAL, 1, 0 );
    noecho();
    intrflush( stdscr, FALSE );
    keypad( stdscr, TRUE );
    nonl();
    notimeout( stdscr, TRUE );
    raw();
    idlok( stdscr, FALSE );
    idcok( stdscr, TRUE );
    immedok( stdscr, FALSE );
    leaveok( stdscr, FALSE );
    scrollok( stdscr, FALSE );
    resizeterm( max_y, max_x );
    E_ncurses_S_scroll_y = E_ncurses_S_scroll_x = E_ncurses_S_scroll_max_x = E_ncurses_S_scroll_max_y = 0;
    mousemask( BUTTON1_CLICKED, 0 );
    D_M( ncurses, getch );
}
void
E_ui_M( void
){  E_data_Q_layout_S = E_mem_Q_tab_M( sizeof( struct E_data_Q_field_Z ), 0 );
    E_data_Q_layout_S_focus = ~0;
    E_data_Q_layout_S_focus_x = 0;
    E_data_Q_layout_S_focus_select = ~0;
    E_data_Q_layout_S_overwrite = no;
    E_ui_M_ncurses();
}


