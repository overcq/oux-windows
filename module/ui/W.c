








_internal
void
E_ui_W_ncurses( void
){  D_W( ncurses, getch );
    endwin();
    delscreen( E_ncurses_S_screen );
}
void
E_ui_W( void
){  E_ui_W_ncurses();
    E_mem_Q_tab_W( E_data_Q_layout_S );
}


