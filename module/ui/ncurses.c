








struct E_ncurses_Q_field_Z

;

int E_ncurses_I_getch_S_ret;
wint_t E_ncurses_I_getch_S_c;
B E_ncurses_I_getch_S_meta_key;
SCREEN *E_ncurses_S_screen;
int E_ncurses_S_scroll_x, E_ncurses_S_scroll_y;
int E_ncurses_S_scroll_max_x, E_ncurses_S_scroll_max_y;
struct E_mem_Q_tab_Z *E_ncurses_Q_layout_S;

void
E_ncurses_I_lay( void
){  erase();
    E_ncurses_S_scroll_max_x = E_ncurses_S_scroll_max_y = 0;
    int x = 0, y = 0;
    int cur_x = 0;
    int max_x, max_y;
    getmaxyx( stdscr, max_y, max_x );
    max_x -= 2;
    max_y -= 2;
    if( max_x > 1
    && max_y > 1
    && E_mem_Q_tab_R_n( E_data_Q_layout_S )
    )
    {   int focus_x_0 = ~0, focus_x, focus_y;
        move( y, x );
        B not_first = no, not_first_visible = no;;
        for_each( input_id, E_data_Q_layout_S, E_mem_Q_tab )
        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, input_id );
            S l = E_text_Z_su0_R_n( input->label );
            if( not_first )
            {   if( cur_x + 1 + l + 1 + ( input->select_n ? 1 : 0 ) + input->width > max_x )
                {   if( E_ncurses_S_scroll_max_x < x )
                        E_ncurses_S_scroll_max_x = x;
                    x = 0;
                    if( not_first_visible )
                    {   cur_x = 0;
                        move( getcury(stdscr) + 1, cur_x );
                    }
                }else
                {   y--; 
                    x++; 
                    if( y >= E_ncurses_S_scroll_y
                    && getcury(stdscr) <= max_y
                    )
                    {   if( x >= E_ncurses_S_scroll_x
                        && cur_x <= max_x
                        )
                            cur_x++;
                        move( getcury(stdscr), cur_x );
                    }
                }
            }
            struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, input_id );
            data->x = x;
            data->y = y;
            if( y >= E_ncurses_S_scroll_y
            && getcury(stdscr) <= max_y
            )
                not_first_visible = yes;
            not_first = yes;
            Pc s = input->label;
            while( *s )
            {   U u;
                s = E_text_Z_su_R_u( s, &u );
                if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   cchar_t cc;
                    wchar_t wc[2] = { u, L'\0' };
                    setcchar( &cc, &wc[0], A_NORMAL, 1, 0 );
                    add_wch( &cc );
                    cur_x++;
                }
                x++;
            }
            x++; 
            if( y >= E_ncurses_S_scroll_y
            && getcury(stdscr) <= max_y
            && x >= E_ncurses_S_scroll_x
            )
            {   if( cur_x <= max_x )
                    cur_x++;
                if( cur_x <= max_x )
                    move( getcury(stdscr), cur_x );
            }
            if( input->select_n )
            {   if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   add_wch( input_id == E_data_Q_layout_S_focus && ~E_data_Q_layout_S_focus_select ? WACS_DARROW : WACS_UARROW );
                    cur_x++;
                }
                x++;
            }
            B valid = E_data_Q_field_R_valid(input);
            s = input->s;
            l = E_text_Z_su0_R_n(s);
            N width = input->width;
            if( input_id == E_data_Q_layout_S_focus )
            {   focus_y = y;
                focus_x_0 = focus_x = x;
                if( E_data_Q_layout_S_focus_x < width )
                {   focus_x += E_data_Q_layout_S_focus_x;
                    if( l > width )
                        width--; 
                }else
                {   if( y >= E_ncurses_S_scroll_y
                    && getcury(stdscr) <= max_y
                    && x >= E_ncurses_S_scroll_x
                    && cur_x <= max_x
                    )
                    {   add_wch( WACS_LARROW );
                        cur_x++;
                    }
                    x++;
                    width--; 
                    if( l > width
                    && E_data_Q_layout_S_focus_x < l - width
                    )
                        width--; 
                    N after = l - E_data_Q_layout_S_focus_x;
                    if( after > width )
                        after = width;
                    focus_x += width - after;
                    if( focus_x < x )
                        focus_x = x;
                    s += input->s_i;
                    for( int i = x; i != focus_x; i++ )
                    {   U u;
                        s = E_text_Z_su_R_u_rev( s, &u );
                    }
                    width -= focus_x - x;
                    for( int i = x; i != focus_x; i++ )
                    {   U u;
                        s = E_text_Z_su_R_u( s, &u );
                        if( y >= E_ncurses_S_scroll_y
                        && getcury(stdscr) <= max_y
                        && x >= E_ncurses_S_scroll_x
                        && cur_x <= max_x
                        )
                        {   cchar_t cc;
                            wchar_t wc[2] = { u, L'\0' };
                            setcchar( &cc, &wc[0], A_NORMAL, valid ? 2 : 3, 0 );
                            add_wch( &cc );
                            cur_x++;
                        }
                        x++;
                    }
                }
            }else if( l > width )
            {   if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   add_wch( WACS_LARROW );
                    cur_x++;
                }
                x++;
                width--; 
                if( l > width )
                    width--; 
            }
            N i;
            for( i = 0; *s && i != width; i++ )
            {   U u;
                s = E_text_Z_su_R_u( s, &u );
                if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   cchar_t cc;
                    wchar_t wc[2] = { u, L'\0' };
                    setcchar( &cc, &wc[0], A_NORMAL, valid ? 2 : 3, 0 );
                    add_wch( &cc );
                    cur_x++;
                }
                x++;
            }
            for( ; i != width; i++ )
            {   if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   cchar_t cc;
                    wchar_t wc[2] = L" ";
                    setcchar( &cc, &wc[0], A_NORMAL, valid ? 2 : 3, 0 );
                    add_wch( &cc );
                    cur_x++;
                }
                x++;
            }
            if( l > width
            && E_data_Q_layout_S_focus_x < l - width
            )
            {   if( y >= E_ncurses_S_scroll_y
                && getcury(stdscr) <= max_y
                && x >= E_ncurses_S_scroll_x
                && cur_x <= max_x
                )
                {   add_wch( WACS_RARROW );
                    cur_x++;
                }
                x++;
            }
            y++;
        }
        if( E_ncurses_S_scroll_max_x < x )
            E_ncurses_S_scroll_max_x = x;
        E_ncurses_S_scroll_max_y = y;
        if( ~E_data_Q_layout_S_focus_select )
        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
            struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, E_data_Q_layout_S_focus );
            S label_l = E_text_Z_su0_R_n( input->label ) + 1;
            N x_l = 0;
            for_n( i, input->select_n )
            {   N l = E_text_Z_su0_R_n( input->select[i] );
                if( x_l < l )
                    x_l = l;
            }
            E_data_Q_layout_S_focus_select_width = x_l;
            int pos_y = data->y - E_ncurses_S_scroll_y;
            if( getmaxy(stdscr) - 1 - ( pos_y + 1 ) < input->select_n + 1
            && pos_y > getmaxy(stdscr) - 1 - ( pos_y + 1 )
            ) 
            {   N y_n = J_min( input->select_n, pos_y - 1 );
                int x = data->x - E_ncurses_S_scroll_x + label_l;
                if( x >= 0
                && x <= max_x
                )
                    mvadd_wch( pos_y + y_n + 1, x, WACS_ULCORNER );
                for( x++; x != data->x - E_ncurses_S_scroll_x + label_l + 1 + x_l; x++ )
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( pos_y + y_n + 1, x, WACS_HLINE );
                if( x >= 0
                && x <= max_x
                )
                    mvadd_wch( pos_y + y_n + 1, x, WACS_URCORNER );
                N select = 0;
                if( pos_y - 1 < input->select_n )
                {   if( E_data_Q_layout_S_focus_select > y_n / 2 )
                        select = E_data_Q_layout_S_focus_select - y_n / 2;
                    if( select + y_n > input->select_n )
                        select = input->select_n - y_n;
                }
                for( int y = pos_y - y_n; y != pos_y; y++ )
                {   int x = data->x - E_ncurses_S_scroll_x + label_l;
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( y, x, WACS_VLINE );
                    x++;
                    Pc s = input->select[select];
                    while( *s )
                    {   U u;
                        s = E_text_Z_su_R_u( s, &u );
                        if( x >= 0
                        && x <= max_x
                        )
                        {   cchar_t cc;
                            wchar_t wc[2] = { u, L'\0' };
                            setcchar( &cc, &wc[0], A_NORMAL, select == E_data_Q_layout_S_focus_select ? 2 : 1, 0 );
                            mvadd_wch( y, x, &cc );
                        }
                        x++;
                    }
                    for( ; x != data->x - E_ncurses_S_scroll_x + label_l + x_l + 1; x++ )
                    {   U u;
                        s = E_text_Z_su_R_u( s, &u );
                        if( x >= 0
                        && x <= max_x
                        )
                        {   cchar_t cc;
                            wchar_t wc[2] = L" ";
                            setcchar( &cc, &wc[0], A_NORMAL, select == E_data_Q_layout_S_focus_select ? 2 : 1, 0 );
                            mvadd_wch( y, x, &cc );
                        }
                    }
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( y, x, WACS_VLINE );
                    select++;
                }
            }else 
            {   N y_n = J_min( input->select_n, getmaxy(stdscr) - 1 - ( pos_y + 1 ) - 1 );
                int x = data->x - E_ncurses_S_scroll_x + label_l;
                if( x >= 0
                && x <= max_x
                )
                    mvadd_wch( pos_y + y_n + 1, x, WACS_LLCORNER );
                for( x++; x != data->x - E_ncurses_S_scroll_x + label_l + 1 + x_l; x++ )
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( pos_y + y_n + 1, x, WACS_HLINE );
                if( x >= 0
                && x <= max_x
                )
                    mvadd_wch( pos_y + y_n + 1, x, WACS_LRCORNER );
                N select = 0;
                if( getmaxy(stdscr) - 1 - ( pos_y + 1 ) - 1 < input->select_n )
                {   if( E_data_Q_layout_S_focus_select > y_n / 2 )
                        select = E_data_Q_layout_S_focus_select - y_n / 2;
                    if( select + y_n > input->select_n )
                        select = input->select_n - y_n;
                }
                for( int y = pos_y + 1; y != pos_y + 1 + y_n; y++ )
                {   int x = data->x - E_ncurses_S_scroll_x + label_l;
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( y, x, WACS_VLINE );
                    x++;
                    Pc s = input->select[select];
                    while( *s )
                    {   U u;
                        s = E_text_Z_su_R_u( s, &u );
                        if( x >= 0
                        && x <= max_x
                        )
                        {   cchar_t cc;
                            wchar_t wc[2] = { u, L'\0' };
                            setcchar( &cc, &wc[0], A_NORMAL, select == E_data_Q_layout_S_focus_select ? 2 : 1, 0 );
                            mvadd_wch( y, x, &cc );
                        }
                        x++;
                    }
                    for( ; x != data->x - E_ncurses_S_scroll_x + label_l + x_l + 1; x++ )
                    {   U u;
                        s = E_text_Z_su_R_u( s, &u );
                        if( x >= 0
                        && x <= max_x
                        )
                        {   cchar_t cc;
                            wchar_t wc[2] = L" ";
                            setcchar( &cc, &wc[0], A_NORMAL, select == E_data_Q_layout_S_focus_select ? 2 : 1, 0 );
                            mvadd_wch( y, x, &cc );
                        }
                    }
                    if( x >= 0
                    && x <= max_x
                    )
                        mvadd_wch( y, x, WACS_VLINE );
                    select++;
                }
            }
            x = data->x + label_l + 1 + x_l + 1;
            if( E_ncurses_S_scroll_max_x < x )
                E_ncurses_S_scroll_max_x = x;
        }
        max_x++;
        max_y++;
        if( E_ncurses_S_scroll_max_x < max_x )
            E_ncurses_S_scroll_max_x = max_x;
        if( E_ncurses_S_scroll_max_y < max_y )
            E_ncurses_S_scroll_max_y = max_y;
        int pos_x = round( (F)E_ncurses_S_scroll_x * max_x / E_ncurses_S_scroll_max_x );
        int pos_y = round( (F)E_ncurses_S_scroll_y * max_y / E_ncurses_S_scroll_max_y );
        int len_x = round( (F)max_x * max_x / E_ncurses_S_scroll_max_x );
        int len_y = round( (F)max_y * max_y / E_ncurses_S_scroll_max_y );
        move( max_y, 0 );
        for( int x = 0; x != max_x; x++ )
            add_wch( x < pos_x || x >= pos_x + len_x ? WACS_HLINE : WACS_BLOCK );
        if( ~focus_x_0 )
        {   cchar_t cc;
            wchar_t wc[2] = { E_data_Q_layout_S_overwrite ? L'O' : L'I', L'\0' };
            setcchar( &cc, &wc[0], A_NORMAL, 1, 0 );
            add_wch( &cc );
        }else
            add_wch( WACS_LRCORNER );
        for( int y = 0; y != max_y; y++ )
            mvadd_wch( y, max_x, y < pos_y || y >= pos_y + len_y ? WACS_VLINE : WACS_BLOCK );
        if( ~focus_x_0
        && focus_y >= E_ncurses_S_scroll_y
        && focus_y - E_ncurses_S_scroll_y < max_y
        && focus_x >= E_ncurses_S_scroll_x
        && focus_x - E_ncurses_S_scroll_x < max_x
        )
        {   curs_set(2) != ERR || curs_set(1);
            move( focus_y - E_ncurses_S_scroll_y, focus_x - E_ncurses_S_scroll_x );
        }else
            curs_set(0) != ERR || move( max_y, max_x );
    }
    refresh();
}

_internal
void
E_ncurses_I_tab_focus( void
){  struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
    struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, E_data_Q_layout_S_focus );
    if( data->x < E_ncurses_S_scroll_x
    || data->x >= E_ncurses_S_scroll_x + getmaxx(stdscr) - 1
    )
        E_ncurses_S_scroll_x = data->x + E_text_Z_su0_R_n( input->label ) + 1 + ( input->select_n ? 1 : 0 ) + input->width < getmaxx(stdscr)
        ? 0
        : data->x < E_ncurses_S_scroll_max_x - ( getmaxx(stdscr) - 1 )
          ? data->x
          : E_ncurses_S_scroll_max_x - ( getmaxx(stdscr) - 1 );
    if( data->y < E_ncurses_S_scroll_y
    || data->y >= E_ncurses_S_scroll_y + getmaxy(stdscr) - 1
    )
        E_ncurses_S_scroll_y = data->y < E_ncurses_S_scroll_max_y - ( getmaxy(stdscr) - 1 )
        ? data->y
        : E_ncurses_S_scroll_max_y - ( getmaxy(stdscr) - 1 );
    E_data_Q_layout_S_focus_x = E_data_Q_field_R_u_i(input);
    E_data_Q_layout_S_focus_select = ~0;
    E_data_Q_layout_S_overwrite = no;
}
B
E_ncurses_I_sigsuspend( sigset_t *sigset
){  sigset_t old_sigset;
    _sigprocmask( SIG_SETMASK, sigset, &old_sigset ); 
    E_ncurses_I_getch_S_ret = get_wch( &E_ncurses_I_getch_S_c );
    _sigprocmask( SIG_SETMASK, &old_sigset, 0 );
    return E_ncurses_I_getch_S_ret != ERR; 
}
void
E_ncurses_I_setitimer( Z_clock_time *tv
){
#ifndef E_flow_drv_C_clock_monotonic
    timeout( tv->tv_sec * 1000 + ( tv->Z_clock_time_minor_field + 999 ) / 1000 );
#else
    timeout( tv->tv_sec * 1000 + ( tv->Z_clock_time_minor_field + 999999 ) / 1000000 );
#endif
}
_internal I D_id( ncurses, getch ) = ~0; D( ncurses, getch )
{   Xh1_M( &E_ncurses_I_sigsuspend, &E_ncurses_I_setitimer );
    I_D
    {   Xh1_B()
            break;
        switch( E_ncurses_I_getch_S_ret )
        { case KEY_CODE_YES:
                if( E_ncurses_I_getch_S_meta_key )
                {   switch( E_ncurses_I_getch_S_c )
                    { case KEY_DC:
                            break;
                      case KEY_RIGHT:
                            break;
                      case KEY_LEFT:
                            break;
                      case KEY_DOWN:
                            if( !~E_data_Q_layout_S_focus_select )
                            {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                                if( input->select_n )
                                {   E_data_Q_layout_S_focus_select = 0;
                                    E_ncurses_I_lay();
                                }
                            }
                            break;
                      case KEY_UP:
                            if( ~E_data_Q_layout_S_focus_select )
                            {   E_data_Q_layout_S_focus_select = ~0;
                                E_ncurses_I_lay();
                            }
                            break;
                      case KEY_A1: 
                            if( E_ncurses_S_scroll_max_x )
                            {   E_ncurses_S_scroll_x = 0;
                                E_ncurses_I_lay();
                            }
                            break;
                      case KEY_C1: 
                            if( E_ncurses_S_scroll_max_x )
                            {   E_ncurses_S_scroll_x = E_ncurses_S_scroll_max_x - ( getmaxx(stdscr) - 1 );
                                E_ncurses_I_lay();
                            }
                            break;
                      case KEY_NPAGE:
                      case KEY_C3: 
                            if( E_ncurses_S_scroll_max_x )
                            {   if( E_ncurses_S_scroll_max_x - E_ncurses_S_scroll_x > 2 * ( getmaxx(stdscr) - 1 ))
                                    E_ncurses_S_scroll_x += getmaxx(stdscr) - 1;
                                else
                                    E_ncurses_S_scroll_x = E_ncurses_S_scroll_max_x - ( getmaxx(stdscr) - 1 );
                                E_ncurses_I_lay();
                            }
                            break;
                      case KEY_PPAGE:
                      case KEY_A3: 
                            if( E_ncurses_S_scroll_max_x )
                            {   if( E_ncurses_S_scroll_x > getmaxx(stdscr) - 1 )
                                    E_ncurses_S_scroll_x -= getmaxx(stdscr) - 1;
                                else
                                    E_ncurses_S_scroll_x = 0;
                                E_ncurses_I_lay();
                            }
                            break;
                      default:
                        {   beep();
                            G_(); Gd( E_ncurses_I_getch_S_c ); 
                            break;
                        }
                    }
                    E_ncurses_I_getch_S_meta_key = no;
                    break;
                }
                switch( E_ncurses_I_getch_S_c )
                { case KEY_RESIZE:
                        if( ~E_data_Q_layout_S_focus )
                            E_data_Q_layout_S_focus = E_data_Q_layout_S_focus_select = ~0;
                        E_ncurses_I_lay();
                        break;
                  case KEY_MOUSE:
                        if( E_ncurses_S_scroll_max_x )
                        {   MEVENT ev;
                            getmouse( &ev );
                            if( ev.bstate & BUTTON1_CLICKED )
                            {   if( ev.y == getmaxy(stdscr) - 1
                                && ev.x != getmaxx(stdscr) - 1
                                )
                                {   int max_x = getmaxx(stdscr) - 1;
                                    int len_x = round( (F)max_x * max_x / E_ncurses_S_scroll_max_x );
                                    int E_ncurses_S_scroll_x_ = round(( (F)ev.x - 0.5 * len_x ) * E_ncurses_S_scroll_max_x / max_x );
                                    if( E_ncurses_S_scroll_x_ < 0 )
                                        E_ncurses_S_scroll_x_ = 0;
                                    else if( E_ncurses_S_scroll_x_ > E_ncurses_S_scroll_max_x - max_x )
                                        E_ncurses_S_scroll_x_ = E_ncurses_S_scroll_max_x - max_x;
                                    if( E_ncurses_S_scroll_x != E_ncurses_S_scroll_x_ )
                                    {   E_ncurses_S_scroll_x = E_ncurses_S_scroll_x_;
                                        E_ncurses_I_lay();
                                    }
                                    break;
                                }
                                if( ev.x == getmaxx(stdscr) - 1
                                && ev.y != getmaxy(stdscr) - 1
                                )
                                {   int max_y = getmaxy(stdscr) - 1;
                                    int len_y = round( (F)max_y * max_y / E_ncurses_S_scroll_max_y );
                                    int E_ncurses_S_scroll_y_ = round(( (F)ev.y - 0.5 * len_y ) * E_ncurses_S_scroll_max_y / max_y );
                                    if( E_ncurses_S_scroll_y_ < 0 )
                                        E_ncurses_S_scroll_y_ = 0;
                                    else if( E_ncurses_S_scroll_y_ > E_ncurses_S_scroll_max_y - max_y )
                                        E_ncurses_S_scroll_y_ = E_ncurses_S_scroll_max_y - max_y;
                                    if( E_ncurses_S_scroll_y != E_ncurses_S_scroll_y_ )
                                    {   E_ncurses_S_scroll_y = E_ncurses_S_scroll_y_;
                                        E_ncurses_I_lay();
                                    }
                                    break;
                                }
                                if( ~E_data_Q_layout_S_focus_select )
                                {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                                    struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, E_data_Q_layout_S_focus );
                                    S l = E_text_Z_su0_R_n( input->label ) + 1;
                                    int pos_x = data->x - E_ncurses_S_scroll_x;
                                    if( ev.x >= pos_x + l
                                    && ev.x <= pos_x + l + 1 + E_data_Q_layout_S_focus_select_width
                                    )
                                    {   int pos_y = data->y - E_ncurses_S_scroll_y;
                                        if( getmaxy(stdscr) - 1 - ( pos_y + 1 ) < input->select_n + 1
                                        && pos_y > getmaxy(stdscr) - 1 - ( pos_y + 1 )
                                        ) 
                                        {   N y_n = J_min( input->select_n, pos_y - 1 );
                                            if( ev.y >= pos_y - ( y_n + 1 )
                                            && ev.y < pos_y
                                            )
                                            {   if( ev.x > pos_x + l
                                                && ev.x < pos_x + l + 1 + E_data_Q_layout_S_focus_select_width
                                                && ev.y > pos_y - ( y_n + 1 )
                                                )
                                                {   N select = 0;
                                                    if( pos_y - 1 < input->select_n )
                                                    {   if( E_data_Q_layout_S_focus_select > y_n / 2 )
                                                            select = E_data_Q_layout_S_focus_select - y_n / 2;
                                                        if( select + y_n > input->select_n )
                                                            select = input->select_n - y_n;
                                                    }
                                                    select += ev.y - ( pos_y - y_n );
                                                    if( E_data_Q_field_P_select( input, select ))
                                                    {   E_data_Q_layout_S_focus_x = 0;
                                                        E_data_Q_layout_S_focus_select = ~0;
                                                        E_ncurses_I_lay();
                                                    }
                                                }
                                                break;
                                            }
                                        }else 
                                        {   N y_n = J_min( input->select_n, getmaxy(stdscr) - 1 - ( pos_y + 1 ) - 1 );
                                            if( ev.y > pos_y
                                            && ev.y <= pos_y + y_n + 1
                                            )
                                            {   if( ev.x > pos_x + l
                                                && ev.x < pos_x + l + 1 + E_data_Q_layout_S_focus_select_width
                                                && ev.y < pos_y + y_n + 1
                                                )
                                                {   N select = 0;
                                                    if( getmaxy(stdscr) - 1 - ( pos_y + 1 ) - 1 < input->select_n )
                                                    {   if( E_data_Q_layout_S_focus_select > y_n / 2 )
                                                            select = E_data_Q_layout_S_focus_select - y_n / 2;
                                                        if( select + y_n > input->select_n )
                                                            select = input->select_n - y_n;
                                                    }
                                                    select += ev.y - ( pos_y + 1 );
                                                    if( E_data_Q_field_P_select( input, select ))
                                                    {   E_data_Q_layout_S_focus_x = 0;
                                                        E_data_Q_layout_S_focus_select = ~0;
                                                        E_ncurses_I_lay();
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                    }
                                    if( ev.x == getmaxx(stdscr) - 1
                                    && ev.y == getmaxy(stdscr) - 1
                                    )
                                    {   E_data_Q_layout_S_overwrite = !E_data_Q_layout_S_overwrite;
                                        E_ncurses_I_lay();
                                        break;
                                    }
                                }
                                if( ev.x != getmaxx(stdscr) - 1
                                && ev.y != getmaxy(stdscr) - 1
                                )
                                {   for_each( input_id, E_ncurses_Q_layout_S, E_mem_Q_tab )
                                    {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, input_id );
                                        struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, input_id );
                                        if( ev.y == data->y - E_ncurses_S_scroll_y )
                                        {   if(( ev.x >= data->x - E_ncurses_S_scroll_x
                                                && ev.x < data->x - E_ncurses_S_scroll_x + E_text_Z_su0_R_n( input->label ) + 1
                                              )
                                              || ( ev.x >= data->x - E_ncurses_S_scroll_x + E_text_Z_su0_R_n( input->label ) + 1 + ( input->select_n ? 1 : 0 )
                                                && ev.x < data->x - E_ncurses_S_scroll_x + E_text_Z_su0_R_n( input->label ) + 1 + ( input->select_n ? 1 : 0 ) + input->width
                                            ))
                                            {   E_data_Q_layout_S_focus = input_id;
                                                E_data_Q_layout_S_focus_x = E_data_Q_field_R_u_i(input);
                                                E_data_Q_layout_S_focus_select = ~0;
                                                E_data_Q_layout_S_overwrite = no;
                                                E_ncurses_I_lay();
                                                break;
                                            }
                                            if( ev.x == data->x - E_ncurses_S_scroll_x + E_text_Z_su0_R_n( input->label ) + 1 )
                                            {   if( E_data_Q_layout_S_focus != input_id )
                                                {   E_data_Q_layout_S_focus = input_id;
                                                    E_data_Q_layout_S_focus_x = E_data_Q_field_R_u_i(input);
                                                    E_data_Q_layout_S_focus_select = 0;
                                                    E_data_Q_layout_S_overwrite = no;
                                                    E_ncurses_I_lay();
                                                }else
                                                {   E_data_Q_layout_S_focus_select = !~E_data_Q_layout_S_focus_select ? 0 : ~0;
                                                    E_ncurses_I_lay();
                                                }
                                                break;
                                            }
                                        }
                                    }
                                    if( ~input_id )
                                        break;
                                }
                                E_data_Q_layout_S_focus = E_data_Q_layout_S_focus_select = ~0;
                                E_ncurses_I_lay();
                            }
                            break;
                        }
                  case KEY_IC:
                        if( ~E_data_Q_layout_S_focus )
                        {   E_data_Q_layout_S_overwrite = !E_data_Q_layout_S_overwrite;
                            E_ncurses_I_lay();
                        }
                        break;
                  case KEY_DC:
                        if( ~E_data_Q_layout_S_focus )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( !~E_data_Q_layout_S_focus_select )
                            {   if( E_data_Q_field_P_remove_on(input) )
                                    E_ncurses_I_lay();
                                else
                                    beep();
                            }else
                            {
                            }
                        }
                        break;
                  case KEY_BACKSPACE:
                        if( ~E_data_Q_layout_S_focus )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( !~E_data_Q_layout_S_focus_select )
                            {   if( E_data_Q_field_P_remove_back(input) )
                                {   E_data_Q_layout_S_focus_x--;
                                    E_ncurses_I_lay();
                                }else
                                    beep();
                            }else
                            {
                            }
                        }
                        break;
                  case KEY_ENTER: 
                        E_ncurses_I_getch_S_c = '\r';
                        goto Enter;
                  case KEY_RIGHT:
                        if( ~E_data_Q_layout_S_focus )
                            if( !~E_data_Q_layout_S_focus_select )
                            {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                                if( E_data_Q_field_P_right(input) )
                                {   E_data_Q_layout_S_focus_x++;
                                    E_ncurses_I_lay();
                                }else
                                    beep();
                            }
                        break;
                  case KEY_LEFT:
                        if( ~E_data_Q_layout_S_focus )
                            if( !~E_data_Q_layout_S_focus_select )
                            {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                                if( E_data_Q_field_P_left(input) )
                                {   E_data_Q_layout_S_focus_x--;
                                    E_ncurses_I_lay();
                                }else
                                    beep();
                            }
                        break;
                  case KEY_DOWN:
                        if( ~E_data_Q_layout_S_focus_select )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( E_data_Q_layout_S_focus_select + 1 != input->select_n )
                            {   E_data_Q_layout_S_focus_select++;
                                E_ncurses_I_lay();
                            }
                        }
                        break;
                  case KEY_UP:
                        if( ~E_data_Q_layout_S_focus_select )
                            if( E_data_Q_layout_S_focus_select )
                            {   E_data_Q_layout_S_focus_select--;
                                E_ncurses_I_lay();
                            }
                        break;
                  case KEY_BTAB:
                        if( E_ncurses_S_scroll_max_x )
                        {   if( ~E_data_Q_layout_S_focus
                            && E_data_Q_layout_S_focus
                            )
                                E_data_Q_layout_S_focus--;
                            else
                                E_data_Q_layout_S_focus = E_mem_Q_tab_R_n( E_data_Q_layout_S ) - 1;
                            E_ncurses_I_tab_focus();
                            E_ncurses_I_lay();
                        }
                        break;
                  case KEY_HOME:
                        if( ~E_data_Q_layout_S_focus )
                        {   if( !~E_data_Q_layout_S_focus_select )
                            {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                                if( E_data_Q_field_P_left(input) )
                                {   do
                                    {   E_data_Q_layout_S_focus_x--;
                                    }while( E_data_Q_field_P_left(input) );
                                    E_ncurses_I_lay();
                                }
                            }else if( E_data_Q_layout_S_focus_select )
                            {   E_data_Q_layout_S_focus_select = 0;
                                E_ncurses_I_lay();
                            }
                        }
                        break;
                  case KEY_A1: 
                        if( E_ncurses_S_scroll_max_y )
                        {   E_ncurses_S_scroll_y = 0;
                            E_ncurses_I_lay();
                        }
                        break;
                  case KEY_END:
                        if( ~E_data_Q_layout_S_focus )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( !~E_data_Q_layout_S_focus_select )
                            {   if( E_data_Q_field_P_right(input) )
                                {   do
                                    {   E_data_Q_layout_S_focus_x++;
                                    }while( E_data_Q_field_P_right(input) );
                                    E_ncurses_I_lay();
                                }
                            }else if( E_data_Q_layout_S_focus_select != input->select_n - 1 )
                            {   E_data_Q_layout_S_focus_select = input->select_n - 1;
                                E_ncurses_I_lay();
                            }
                        }
                        break;
                  case KEY_C1: 
                        if( E_ncurses_S_scroll_max_y )
                        {   E_ncurses_S_scroll_y = E_ncurses_S_scroll_max_y - ( getmaxy(stdscr) - 1 );
                            E_ncurses_I_lay();
                        }
                        break;
                  case KEY_NPAGE:
                  case KEY_C3: 
                        if( E_ncurses_S_scroll_max_y )
                        {   if( E_ncurses_S_scroll_max_y - E_ncurses_S_scroll_y > 2 * ( getmaxy(stdscr) - 1 ))
                                E_ncurses_S_scroll_y += getmaxy(stdscr) - 1;
                            else
                                E_ncurses_S_scroll_y = E_ncurses_S_scroll_max_y - ( getmaxy(stdscr) - 1 );
                            E_ncurses_I_lay();
                        }
                        break;
                  case KEY_PPAGE:
                  case KEY_A3: 
                        if( E_ncurses_S_scroll_max_y )
                        {   if( E_ncurses_S_scroll_y > getmaxy(stdscr) - 1 )
                                E_ncurses_S_scroll_y -= getmaxy(stdscr) - 1;
                            else
                                E_ncurses_S_scroll_y = 0;
                            E_ncurses_I_lay();
                        }
                        break;
                  default:
                    {   beep();
                        G_(); Gd( E_ncurses_I_getch_S_c ); 
                        break;
                    }
                }
                break;
          case OK:
                if( E_ncurses_I_getch_S_meta_key )
                {   switch( E_ncurses_I_getch_S_c )
                    { case 's':
                            break;
                    }
                    E_ncurses_I_getch_S_meta_key = no;
                    break;
                }
                switch( E_ncurses_I_getch_S_c )
                { case 3: 
                        break;
                  case '\t':
                        if( E_ncurses_S_scroll_max_x )
                        {   if( ~E_data_Q_layout_S_focus
                            && E_data_Q_layout_S_focus + 1 != E_mem_Q_tab_R_n( E_data_Q_layout_S )
                            )
                                E_data_Q_layout_S_focus++;
                            else
                                E_data_Q_layout_S_focus = 0;
                            E_ncurses_I_tab_focus();
                            E_ncurses_I_lay();
                        }
                        break;
                  case '\r':
Enter:                  if( ~E_data_Q_layout_S_focus_select )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( E_data_Q_field_P_select( input, E_data_Q_layout_S_focus_select ))
                            {   E_data_Q_layout_S_focus_x = 0;
                                E_data_Q_layout_S_focus_select = ~0;
                                E_ncurses_I_lay();
                            }
                        }
                        break;
                  case 17: 
                        U_F( E_base_S->E_flow_S_signal, exit );
                        break;
                  case 19: 
                        break;
                  case 27: 
                        E_ncurses_I_getch_S_meta_key = yes;
                        break;
                  default:
                        if( !iswprint( E_ncurses_I_getch_S_c ))
                        {   beep();
                            G_(); Gd( E_ncurses_I_getch_S_c ); 
                            break;
                        }
                        if( ~E_data_Q_layout_S_focus )
                        {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, E_data_Q_layout_S_focus );
                            if( !~E_data_Q_layout_S_focus_select )
                            {   if( !E_data_Q_layout_S_overwrite )
                                    if( E_data_Q_field_P_insert( input, E_ncurses_I_getch_S_c ))
                                    {   E_data_Q_layout_S_focus_x++;
                                        E_ncurses_I_lay();
                                    }else
                                        beep();
                                else
                                    if( E_data_Q_field_P_overwrite( input, E_ncurses_I_getch_S_c ))
                                    {   E_data_Q_layout_S_focus_x++;
                                        E_ncurses_I_lay();
                                    }else
                                        beep();
                            }else
                            {
                            }
                        }
                        break;
                }
                break;
        }
    }
    Xh1_W();
}


