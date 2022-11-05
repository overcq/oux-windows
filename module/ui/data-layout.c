








struct E_mem_Q_tab_Z *E_data_Q_layout_S;
I E_data_Q_layout_S_focus;
N E_data_Q_layout_S_focus_x;
N E_data_Q_layout_S_focus_select;
S E_data_Q_layout_S_focus_select_width;
B E_data_Q_layout_S_overwrite;

I
E_data_Q_layout_I_add( enum E_data_Q_field_Z_type type
, Pc label
, N width
){  I id = E_mem_Q_tab_I_add( E_ncurses_Q_layout_S );
    struct E_ncurses_Q_field_Z *data = E_mem_Q_tab_R( E_ncurses_Q_layout_S, id );
    data->x = data->y = ~0;
    E_mem_Q_tab_I_add( E_data_Q_layout_S );
    struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, id );
    E_data_Q_field_M( input, type, label, width );
    return id;
}
N
E_data_Q_layout_Q_fields_I_store( Pc path
){  I file_id = E_mem_Q_file_M( path, no, S_IRUSR | S_IWUSR );
    if( !~E_mem_Q_file_I_truncate( file_id ))
    {   E_mem_Q_file_W( file_id );
        return ~0;
    }
    struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, file_id );
    for_each( input_id, E_data_Q_layout_S, E_mem_Q_tab )
    {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, input_id );
        if( E_mem_Q_file_P_insert_s( file_id, input->s, E_text_Z_s0_R_0_l( input->s )))
        {   E_mem_Q_file_W( file_id );
            return ~0;
        }
        E_mem_Q_file_P_pos( file_id, file->l );
    }
    E_mem_Q_file_W( file_id );
    return 0;
}
N
E_data_Q_layout_Q_fields_I_restore( Pc path
){  I file_id = E_mem_Q_file_M( path, no, 0 );
    for_each( input_id, E_data_Q_layout_S, E_mem_Q_tab )
    {   struct E_data_Q_field_Z *input = E_mem_Q_tab_R( E_data_Q_layout_S, input_id );
        if( E_mem_Q_file_R_u_upto_0( file_id, &input->s ))
        {   E_mem_Q_file_W( file_id );
            return ~0;
        }
    }
    C c;
    N ret = E_mem_Q_file_R_c( file_id, &c );
    E_mem_Q_file_W( file_id );
    return ret == E_mem_Q_file_S_eof ? 0 : ~0;
}


