
















struct E_data_Q_field_Z








































;

_internal
void
E_data_Q_field_M_( struct E_data_Q_field_Z *input
, Pc label
, N width
){  J_assert( width > 2 );
    J_assert( E_text_Z_su0_R_n(label) <= ~0 >> 1 );
    input->label = M( E_text_Z_s0_R_0_l(label) );
    input->width = width;
    E_text_Z_s_P_s0_copy_0( input->label, label );
    input->s = M(1);
    *input->s = '\0';
    input->s_i = 0;
    input->select = 0;
    input->select_n = 0;
}
void
E_data_Q_field_M( struct E_data_Q_field_Z *input
, enum E_data_Q_field_Z_type type
, Pc label
, N width
){  E_data_Q_field_M_( input, label, width );
    input->type = type;
    switch(type)
    { case E_data_Q_field_S_text:
            input->conf.text.regex = 0;
            break;
      case E_data_Q_field_S_number:
            input->conf.number.slider = 0;
            input->conf.number.signed_ = 0;
            input->conf.number.floating_point = 0;
            input->conf.number.base = 10;
            break;
      case E_data_Q_field_S_bignum:
            input->conf.bignum.slider = 0;
            input->conf.bignum.min_prec = 0;
            break;
    }
}
void
E_data_Q_field_W( struct E_data_Q_field_Z *input
){  W( input->label );
    if( input->type == E_data_Q_field_S_text
    && input->conf.text.regex
    )
        regfree( &input->conf.text.regex_comp );
    if( input->type == E_data_Q_field_S_bignum
    && input->conf.bignum.slider
    )
    {   E_math_Q_bignum_W(input->conf.bignum.min);
        E_math_Q_bignum_W(input->conf.bignum.max);
    }
    W(input->s);
}

B
E_data_Q_field_R_valid( struct E_data_Q_field_Z *input
){  switch(input->type)
    { case E_data_Q_field_S_text:
            if( input->conf.text.regex
            && regexec( &input->conf.text.regex_comp, input->s, 0, 0, 0 )
            )
                return no;
            break;
      case E_data_Q_field_S_number:
            if( input->conf.number.slider )
                if( input->conf.number.floating_point )
                {   Pc ret_s;
                    F v = E_text_Z_s0_N_f( input->s, &ret_s, input->conf.number.base );
                    if( *ret_s
                    || v < input->conf.number.value.floating_point.min
                    || v > input->conf.number.value.floating_point.max
                    )
                        return no;
                }else if( input->conf.number.signed_ )
                {   Pc ret_s;
                    S v = E_text_Z_s0_N_sn( input->s, &ret_s, input->conf.number.base );
                    if( *ret_s
                    || v < input->conf.number.value.signed_.min
                    || v > input->conf.number.value.signed_.max
                    )
                        return no;
                }else
                {   Pc ret_s;
                    N v = E_text_Z_s0_N_n( input->s, &ret_s, input->conf.number.base );
                    if( *ret_s
                    || v < input->conf.number.value.unsigned_.min
                    || v > input->conf.number.value.unsigned_.max
                    )
                        return no;
                }
            break;
      case E_data_Q_field_S_bignum:
            if( input->conf.bignum.slider )
            {   Pc ret_s;
                struct E_math_Z_bignum *v = E_text_Z_s0_N_bignum( input->s, &ret_s, input->conf.bignum.base, input->conf.bignum.min_prec );
                if( *ret_s
                || E_math_Q_bignum_I_compare( v, input->conf.bignum.min ) == -2
                || E_math_Q_bignum_I_compare( v, input->conf.bignum.max ) == 2
                )
                    return no;
            }
            break;
      case E_data_Q_field_S_datetime:
            if( input->conf.datetime.slider )
            {   Pc ret_s;
                struct E_datetime_Z v = E_text_Z_s0_N_datetime( input->s, &ret_s );
                if( *ret_s
                || E_datetime_I_compare( v, input->conf.datetime.min ) < 0
                || E_datetime_I_compare( v, input->conf.datetime.max ) > 0
                )
                    return no;
            }
            break;
    }
    return yes;
}

B
E_data_Q_field_Z_text_P_regex( struct E_data_Q_field_Z *input
, Pc regex
){  if( input->conf.text.regex )
        regfree( &input->conf.text.regex_comp );
    if(regex)
    {   input->conf.text.regex = M( 2 + E_text_Z_s0_R_l(regex) + 2 + 1 );
        E_text_Z_s_P_s0_copy_0( E_text_Z_s_P_s0_copy( E_text_Z_s_P_s0_copy( input->conf.text.regex, "^(" ), regex ), ")$" );
        if( regcomp( &input->conf.text.regex_comp, input->conf.text.regex, REG_EXTENDED | REG_NOSUB ))
        {   W_( input->conf.text.regex );
            return no;
        }
    }else
        input->conf.text.regex = 0;
    return yes;
}
B
E_data_Q_field_P_left( struct E_data_Q_field_Z *input
){  if( input->s_i )
    {   U u;
        N l = input->s + input->s_i - E_text_Z_su_R_u_rev( input->s + input->s_i, &u );
        input->s_i -= l;
        return yes;
    }
    return no;
}
B
E_data_Q_field_P_right( struct E_data_Q_field_Z *input
){  if( *( input->s + input->s_i ))
    {   U u;
        N l = E_text_Z_su_R_u( input->s + input->s_i, &u ) - ( input->s + input->s_i );
        input->s_i += l;
        return yes;
    }
    return no;
}
B
E_data_Q_field_P_insert( struct E_data_Q_field_Z *input
, U u
){  N l = E_text_Z_u_R_su_G(u);
    if( !~l
    || !E_mem_Q_blk_I_insert( &input->s, input->s_i, l )
    )
        return no;
    E_text_Z_u_R_su( u, input->s + input->s_i );
    input->s_i += l;
    return yes;
}
B
E_data_Q_field_P_overwrite( struct E_data_Q_field_Z *input
, U u
){  N l_1, l_2 = E_text_Z_u_R_su_G(u);
    if( *( input->s + input->s_i ))
    {   U u;
        l_1 = E_text_Z_su_R_u( input->s + input->s_i, &u ) - ( input->s + input->s_i );
        if( !~l_2 )
            return no;
        if( l_1 > l_2 )
            E_mem_Q_blk_I_remove( &input->s, input->s_i, l_1 - l_2 );
        else if( l_1 < l_2
        && !E_mem_Q_blk_I_insert( &input->s, input->s_i, l_2 - l_1 )
        )
            return no;
    }else if( !E_mem_Q_blk_I_insert( &input->s, input->s_i, l_2 ))
        return no;
    E_text_Z_u_R_su( u, input->s + input->s_i );
    input->s_i += l_2;
    return yes;
}
B
E_data_Q_field_P_remove_back( struct E_data_Q_field_Z *input
){  if( input->s_i )
    {   U u;
        N l = input->s + input->s_i - E_text_Z_su_R_u_rev( input->s + input->s_i, &u );
        input->s_i -= l;
        E_mem_Q_blk_I_remove( &input->s, input->s_i, l );
        return yes;
    }
    return no;
}
B
E_data_Q_field_P_remove_on( struct E_data_Q_field_Z *input
){  if( *( input->s + input->s_i ))
    {   U u;
        N l = E_text_Z_su_R_u( input->s + input->s_i, &u ) - ( input->s + input->s_i );
        E_mem_Q_blk_I_remove( &input->s, input->s_i, l );
        return yes;
    }
    return no;
}
B
E_data_Q_field_P_select( struct E_data_Q_field_Z *input
, N i
){  J_assert( i < input->select_n );
    if( !E_mem_Q_blk_M_replace( &input->s, E_text_Z_s0_R_0_l( input->select[i] )))
        return no;
    E_text_Z_s_P_s0_copy_0( input->s, input->select[i] );
    input->s_i = 0;
    return yes;
}
N
E_data_Q_field_R_u_i( struct E_data_Q_field_Z *input
){  U u;
    N i = 0;
    for( Pc s = input->s; s != input->s + input->s_i; s = E_text_Z_su_R_u( s, &u ))
        i++;
    return i;
}


