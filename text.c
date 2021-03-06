#include "0.h"
B
E_text_Z_c_T_alpha( C c
){  return ( c >= '0' && c <= '9' )
    || ( c >= 'A' && c <= 'Z' )
    || ( c >= 'a' && c <= 'z' );
}
B
E_text_Z_c_T_quote( C c
){  if( E_text_Z_c_T_alpha(c) )
        return no;
    return c < 43 || c > 122
    || c == ';'
    || c == '<'
    || c == '>'
    || c == '?'
    || c == '\\'
    || c == '`';
}
//==============================================================================
///szkic standardu:
///adres wynikowy procedur obiektów “s”:
///•na początku znalezionych albo
///•po wszystkich danych.
//------------------------------------------------------------------------------
B
E_text_Z_s0_T_eq( Pc s
, Pc t
){  while( *s
    && *t
    && *s == *t
    )
    {   s++;
        t++;
    }
    return !*s && !*t;
}
B
E_text_Z_s0_T_starts( Pc s
, Pc t
){  while( *s
    && *t
    && *s == *t
    )
    {   s++;
        t++;
    }
    return !*t;
}
B
E_text_Z_s_T_eq( Pc s
, Pc s_end
, Pc t
){  while( s != s_end
    && *s == *t
    )
    {   s++;
        t++;
    }
    return s == s_end;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pc
E_text_Z_s0_R_end( Pc s
){  while( *s )
        s++;
    return s;
}
N
E_text_Z_s0_R_l( Pc s
){  return E_text_Z_s0_R_end(s) - s;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s0_R_end_le( Pc s
, N l /// > 0
){  while( *s )
    {   if( !--l )
            break;
        s++;
    }
    return s;
}
B
E_text_Z_s0_T_l_le( Pc s
, N l /// > 0
){  while( *s )
    {   if( !--l )
            break;
        s++;
    }
    return *s == 0;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s0_R_0_end( Pc s
){  return E_text_Z_s0_R_end(s) + 1;
}
N
E_text_Z_s0_R_0_l( Pc s
){  return E_text_Z_s0_R_0_end(s) - s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pc
E_text_Z_s_R_search_0( Pc s
, Pc s_end
){  while( s != s_end )
    {   if( !*s )
            break;
        s++;
    }
    return s;
}
Pc
E_text_Z_s_R_search_c_( Pc s
, C c
){  while( *s != c )
        s++;
    return s;
}
Pc
E_text_Z_s0_R_search_c( Pc s
, C c
){  while( *s )
    {   if( *s == c )
            break;
        s++;
    }
    return s;
}
Pc
E_text_Z_s_R_search_last_c( Pc s
, Pc s_end
, C c
){  while( s_end != s )
    {   if( *--s_end == c )
            break;
    }
    return s_end;
}
Pc
E_text_Z_s0_R_search_last_c( Pc s
, C c
){  return E_text_Z_s_R_search_last_c( s, E_text_Z_s0_R_0_end(s), c );
}
Pc
E_text_Z_s0_R_search_last_c_( Pc s_end
, C c
){  while( *s_end != c )
        s_end--;
    return s_end;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s_R_search_s( Pc s
, Pc s_end
, Pc t
, Pc t_end
){  if( t == t_end )
        return s;
    if( t_end - t <= s_end - s )
    {   Pc r = s, t_ = t;
        while( s < s_end )
        {   if( *s == *t_ )
            {   if( t_ == t )
                    r = s;
                if( ++t_ == t_end )
                    return r;
            }else
            {   if( s >= s_end - ( t_end - t ))
                    break;
                if( t_ != t )
                    t_ = t;
            }
            s++;
        }
    }
    return s_end;
}
Pc
E_text_Z_s_R_search_s0( Pc s
, Pc s_end
, Pc t
){  if( !*t )
        return s;
    Pc r = s, t_ = t;
    while( s < s_end )
    {   if( *s == *t_ )
        {   if( t_ == t )
                r = s;
            if( !*++t_ )
                return r;
        }else if( t_ != t )
            t_ = t;
        s++;
    }
    return s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_text_Z_s_R_n( Pc s
, Pc s_end
, Pc *ret_s
, N base ///do 36; wynikającej z “( '9' - '0' + 1 ) + ( 'Z' - 'A' + 1 )”.
){  N n = 0;
    while( s < s_end )
    {   n *= base;
        if( *s >= '0' && *s <= '9' )
            n += *s - '0';
        else if( *s >= 'A' && *s < 'A' + base - 10 )
            n += 10 + *s - 'A';
        else if( *s >= 'a' && *s < 'a' + base - 10 )
            n += 10 + *s - 'a';
        else
            break;
        s++;
    }
    *ret_s = s;
    return n;
}
N
E_text_Z_s0_R_n( Pc s
, Pc *ret_s
, N base ///do 36; wynikającej z “( '9' - '0' + 1 ) + ( 'Z' - 'A' + 1 )”.
){  N n = 0;
    while( *s )
    {   n *= base;
        if( *s >= '0' && *s <= '9' )
            n += *s - '0';
        else if( *s >= 'A' && *s < 'A' + base - 10 )
            n += 10 + *s - 'A';
        else if( *s >= 'a' && *s < 'a' + base - 10 )
            n += 10 + *s - 'a';
        else
            break;
        s++;
    }
    *ret_s = s;
    return n;
}
//------------------------------------------------------------------------------
N
E_text_Z_s_R_n10( Pc s
, Pc s_end
, Pc *ret_s
){  N n = 0;
    while( s < s_end )
    {   n *= 10;
        if( *s >= '0' && *s <= '9' )
            n += *s - '0';
        else
            break;
        s++;
    }
    *ret_s = s;
    return n;
}
N
E_text_Z_s0_R_n10( Pc s
, Pc *ret_s
){  N n = 0;
    while( *s )
    {   n *= 10;
        if( *s >= '0' && *s <= '9' )
            n += *s - '0';
        else
            break;
        s++;
    }
    *ret_s = s;
    return n;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_n_N_s( Pc s_end
, N n
, N l
, N base
){  n = E_simple_Z_n_I_mod_i_2( n, l * 8 );
    do
    {   N k = n % base;
        *--s_end = k < 10
        ? '0' + k
        : 'A' + k - 10;
    }while( n /= base );
    return s_end;
}
N
E_text_Z_n_N_s_G( N n
, N l
, N base
){  N i = 0;
    n = E_simple_Z_n_I_mod_i_2( n, l * 8 );
    do
    {   i++;
    }while( n /= base );
    return i;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_i_N_s( Pc s_end
, S n
, N l
, N base
){  s_end = E_text_Z_n_N_s( s_end, J_abs(n), l, base );
    if( n < 0 )
        *--s_end = '-';
    return s_end;
}
N
E_text_Z_i_N_s_G( S n
, N l
, N base
){  return E_text_Z_n_N_s_G( J_abs(n), l, base ) + ( n < 0 ? 1 : 0 );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pc
E_text_Z_s_P_0( Pc s
){  *s++ = '\0';
    return s;
}
Pc
E_text_Z_s_P_fill_c( Pc s
, Pc s_end
, C c
){  while( s < s_end )
        *s++ = c;
    return s;
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s_P_copy( Pc s
, Pc s_end
, Pc t
, Pc t_end
){  while( s != s_end
    && t != t_end
    ){  *s = *t;
        s++;
        t++;
    }
    return s;
}
Pc
E_text_Z_s_P_copy_( Pc s
, Pc t
, Pc t_end
){  while( t != t_end )
    {   *s = *t;
        s++;
        t++;
    }
    return s;
}
Pc
E_text_Z_s_P_copy_0_( Pc s
, Pc t
, Pc t_end
){  return E_text_Z_s_P_0( E_text_Z_s_P_copy_( s, t, t_end ));
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s_P_copy_l( Pc s
, Pc t
, N l
){  while( l-- )
    {   *s = *t;
        s++;
        t++;
    }
    return s;
}
Pc
E_text_Z_s_P_copy_l_0( Pc s
, Pc t
, N l
){  return E_text_Z_s_P_0( E_text_Z_s_P_copy_l( s, t, l ));
}
//------------------------------------------------------------------------------
Pc
E_text_Z_s0_P_copy( Pc s
, Pc t
){  while( *t )
    {   *s = *t;
        s++;
        t++;
    }
    return s;
}
Pc
E_text_Z_s0_P_copy_0( Pc s
, Pc t
){  return E_text_Z_s_P_0( E_text_Z_s0_P_copy( s, t ));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_text_Z_s_P_rev( Pc s
, N l
){  N i = 0;
    N l_ = l / 2;
    while( l_-- )
    {   J_swap( C, s[i], s[ l - 1 - i ] );
        i++;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pc
E_text_Z_s_Z_cmdline_T_quote_n( Pc s
, Pc s_end
){  while( s < s_end )
        if( E_text_Z_c_T_quote( *s++ ))
            break;
    return s;
}
Pc
E_text_Z_s0_Z_cmdline_T_quote( Pc s
){  while( *s )
    {   if( E_text_Z_c_T_quote( *s ))
            break;
        s++;
    }
    return s;
}
//------------------------------------------------------------------------------
void
E_text_Z_s_Z_cmdline_Z_arg_I_mode( S *cmd_mode
, Pc arg
){  switch( *cmd_mode )
    { case 0:
          if( E_text_Z_s0_T_eq( arg, "gnome-terminal" ))
              *cmd_mode = 1;
          else if( E_text_Z_s0_T_eq( arg, "su" ))
              *cmd_mode = 2;
          else if( E_text_Z_s0_T_eq( arg, "sg" ))
              *cmd_mode = 3;
          else
              *cmd_mode = 0;
          break;
      case 1:
          if( E_text_Z_s0_T_eq( arg, "-e" ))
              *cmd_mode = -*cmd_mode;
          break;
      case 2:
          if( E_text_Z_s0_T_eq( arg, "-c" ))
              *cmd_mode = -*cmd_mode;
          break;
      case 3:
          if( !E_text_Z_s0_T_eq( arg, "-" ))
              *cmd_mode = -*cmd_mode;
          break;
    }
}
//------------------------------------------------------------------------------
void
E_text_Z_s_Z_cmdline_N_quote_I_open( Pc cmdline
, N *l
, B *inside
, N level
){  for_n_rev( i, level )
    {   E_mem_Q_blk_P_fill_c( cmdline + *l, ( 1 << i ) - 1, '\\' );
        *l += ( 1 << i ) - 1;
        *( cmdline + *l ) = '\'';
        ++*l;
    }
    *inside = yes;
}
void
E_text_Z_s_Z_cmdline_N_quote_I_close( Pc cmdline
, N *l
, B *inside
, N level
){  for_n( i, level )
    {   E_mem_Q_blk_P_fill_c( cmdline + *l, ( 1 << i ) - 1, '\\' );
        *l += ( 1 << i ) - 1;
        *( cmdline + *l ) = '\'';
        ++*l;
    }
    *inside = no;
}
N
E_text_Z_s_Z_cmdline_N_quote( Pc cmdline
, N level
, struct E_flow_Z_args *args
, N args_n
){  N l = 0;
    S cmd_mode = 0;
    B inside = no;
    for_n( args_i, args_n )
    {   for_n( i, args->argc )
        {   Pc arg = args->argv[i];
            if( !*arg )
                continue;
            if(l)
            {   if( !inside )
                    E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level );
                *( cmdline + l ) = ' ';
                l++;
            }
            if( cmd_mode < 0 )
            {   if(inside)
                    E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level );
                cmd_mode = 0;
                level++;
            }
            E_text_Z_s_Z_cmdline_Z_arg_I_mode( &cmd_mode, arg );
            Pc arg_;
            if( *( arg_ = E_text_Z_s0_R_search_c( arg, '\'' )))
            {   if( arg_ != arg )
                {   N arg_quote = 0;
                    if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ) != '\'' )
                    {   if(inside)
                            E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level );
                        arg_quote = 1;
                        E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level + arg_quote );
                    }else if( !inside )
                        E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level );
                    E_mem_Q_blk_I_copy( cmdline + l, arg, arg_ - arg );
                    l += arg_ - arg;
                    E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level + arg_quote );
                }else if( inside )
                    E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level );
                E_mem_Q_blk_P_fill_c( cmdline + l, ( 2 << level ) - 1, '\\' );
                l += ( 2 << level ) - 1;
                *( cmdline + l ) = '\'';
                l++;
                arg = arg_ + 1;
            }
            if( *arg_ )
                for( ; *( arg_ = E_text_Z_s0_R_search_c( arg, '\'' )); arg = arg_ + 1 )
                {   if( arg_ != arg )
                    {   N arg_quote = 0;
                        if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ) != '\'' )
                        {   arg_quote = 1;
                            E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level + arg_quote );
                        }
                        E_mem_Q_blk_I_copy( cmdline + l, arg, arg_ - arg );
                        l += arg_ - arg;
                        if( arg_quote )
                            E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level + arg_quote );
                    }
                    E_mem_Q_blk_P_fill_c( cmdline + l, ( 2 << level ) - 1, '\\' );
                    l += ( 2 << level ) - 1;
                    *( cmdline + l ) = '\'';
                    l++;
                }
            if( arg == args->argv[i] ) ///nie znalazł żadnego cudzysłowu.
            {   if( arg == args->argv[i] )
                    arg_ = E_text_Z_s0_R_end( args->argv[i] );
                N arg_quote = 0;
                if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ))
                {   if(inside)
                        E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level );
                    arg_quote = 1;
                    E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level + arg_quote );
                }else if( !inside )
                    E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level );
                E_mem_Q_blk_I_copy( cmdline + l, arg, arg_ - arg );
                l += arg_ - arg;
                if( arg_quote )
                    E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level + arg_quote );
            }else if( *arg ) ///znalazł i na końcu jest jeszcze coś oprócz zastąpionego cudzysłowu.
            {   if( arg == args->argv[i] )
                    arg_ = E_text_Z_s0_R_end( args->argv[i] );
                N arg_quote = 0;
                if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ))
                {   arg_quote = 1;
                    E_text_Z_s_Z_cmdline_N_quote_I_open( cmdline, &l, &inside, level + arg_quote );
                }
                E_mem_Q_blk_I_copy( cmdline + l, arg, arg_ - arg );
                l += arg_ - arg;
                if( arg_quote )
                    E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level + arg_quote );
            }
        }
        args++;
    }
    if(inside)
        E_text_Z_s_Z_cmdline_N_quote_I_close( cmdline, &l, &inside, level );
    return l;
}
//------------------------------------------------------------------------------
void
E_text_Z_s_Z_cmdline_N_quote_G_open(
  N *l
, B *inside
, N level
){  for_n_rev( i, level )
        *l += 1 << i;
    *inside = yes;
}
void
E_text_Z_s_Z_cmdline_N_quote_G_close(
  N *l
, B *inside
, N level
){  for_n( i, level )
        *l += 1 << i;
    *inside = no;
}
N
E_text_Z_s_Z_cmdline_N_quote_G(
  N level
, struct E_flow_Z_args *args
, N args_n
){  N l = 0;
    S cmd_mode = 0;
    B inside = no;
    for_n( args_i, args_n )
    {   for_n( i, args->argc )
        {   Pc arg = args->argv[i];
            if( !*arg )
                continue;
            if(l)
            {   if( !inside )
                    E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level );
                l++;
            }
            if( cmd_mode < 0 )
            {   if(inside)
                    E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level );
                cmd_mode = 0;
                level++;
            }
            E_text_Z_s_Z_cmdline_Z_arg_I_mode( &cmd_mode, arg );
            Pc arg_;
            if( *( arg_ = E_text_Z_s0_R_search_c( arg, '\'' )))
            {   if( arg_ != arg )
                {   N arg_quote = 0;
                    if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ) != '\'' )
                    {   if(inside)
                            E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level );
                        arg_quote = 1;
                        E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level + arg_quote );
                    }else if( !inside )
                        E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level );
                    l += arg_ - arg;
                    E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level + arg_quote );
                }else if( inside )
                    E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level );
                l += 2 << level;
                arg = arg_ + 1;
            }
            if( *arg_ )
                for( ; *( arg_ = E_text_Z_s0_R_search_c( arg, '\'' )); arg = arg_ + 1 )
                {   if( arg_ != arg )
                    {   N arg_quote = 0;
                        if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ) != '\'' )
                        {   arg_quote = 1;
                            E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level + arg_quote );
                        }
                        l += arg_ - arg;
                        if( arg_quote )
                            E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level + arg_quote );
                    }
                    l += 2 << level;
                }
            if( arg == args->argv[i] )
            {   if( arg == args->argv[i] )
                    arg_ = E_text_Z_s0_R_end( args->argv[i] );
                N arg_quote = 0;
                if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ))
                {   if(inside)
                        E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level );
                    arg_quote = 1;
                    E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level + arg_quote );
                }else if( !inside )
                    E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level );
                l += arg_ - arg;
                if( arg_quote )
                    E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level + arg_quote );
            }else if( *arg )
            {   if( arg == args->argv[i] )
                    arg_ = E_text_Z_s0_R_end( args->argv[i] );
                N arg_quote = 0;
                if( *E_text_Z_s_Z_cmdline_T_quote_n( arg, arg_ ))
                {   arg_quote = 1;
                    E_text_Z_s_Z_cmdline_N_quote_G_open( &l, &inside, level + arg_quote );
                }
                l += arg_ - arg;
                if( arg_quote )
                    E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level + arg_quote );
            }
        }
        args++;
    }
    if(inside)
        E_text_Z_s_Z_cmdline_N_quote_G_close( &l, &inside, level );
    return l;
}
//==============================================================================
N ///ile bajtów zapisano lub błąd.
E_text_Z_s_Z_u_R_utf8( U u
, Pc s
){  if( u <= 0x7f )
    {   s[0] = (C)u;
        return 1;
    }
    N first = 0x1f;
    N i = 0;
    while( u > first )
    {   s[i] = (C)(( u & 0x3f ) | 0x80 );
        first >>= 1;
        if( !first )
            return ~0;
        u >>= 6;
        i++;
    }
    s[i] = (C)(( ~first << 2 ) | u );
    E_text_Z_s_P_rev( s, i + 1 );
    return i + 1;
}
///TODO dodać sprawdzanie najkrótszego kodowania.
Pc
E_text_Z_s_Z_utf8_R_u( Pc s
, U *u
){  if( (S8)*s >= 0 )
    {   *u = *s;
        return s + 1;
    }
    U v = ~(S8)*s;
    N n = E_asm_I_bsr(v);
    if( n == ~0
    || n == 6
    )
        return s;
    v = *s & ( _v( v, 1 ) << n ) - 1;
    for_n( i, 6 - n )
    {   if(( *++s & 0xc0 ) != 0x80 )
            return s;
        v <<= 6;
        v |= *s & 0x3f;
    }
    *u = v;
    return s + 1;
}
Pc
E_text_Z_s_Z_utf8_R_rev_u( Pc s
, U *u
){  if( (S8)*( s - 1 ) >= 0 )
    {   *u = *( s - 1 );
        return s - 1;
    }
    U v = 0;
    for_n( i, 7 )
    {   if(( *--s & 0xc0 ) != 0x80 )
            break;
        v |= ( *s & 0x3f ) << ( i * 6 );
    }
    N n = E_asm_I_bsr( ~(S8)*s );
    if( n == ~0
    || n != 6 - i
    )
        return s + i;
    v |= ( *s & (( _v( v, 1 ) << n ) - 1 )) << (( i + 1 ) * 6 );
    *u = v;
    return s;
}
N
E_text_Z_s0_Z_utf8_R_l( Pc s
){  N i = 0;
    while( *s )
    {   U u = ~0;
        s = E_text_Z_s_Z_utf8_R_u( s, &u );
        if( !~u )
            return ~0;
        i++;
    }
    return i;
}
N ///ile bajtów przeczytano lub błąd.
E_text_Z_getter_Z_c_R_u( N (*getter)(void)
, U *u
){  N c = getter();
    if( !~c
    || c == E_mem_Q_file_S_eof
    )
        return c;
    if( (S8)c >= 0 )
    {   *u = c;
        return 1;
    }
    N n = E_asm_I_bsr( ~(S8)c );
    if( n == ~0
    || n == 6
    )
        return ~0;
    U v = c & ( _v( v, 1 ) << n ) - 1;
    for_n( i, 6 - n )
    {   c = getter();
        if( !~c
        || c == E_mem_Q_file_S_eof
        )
            return c;
        if(( c & 0xc0 ) != 0x80 )
            return ~0;
        v <<= 6;
        v |= c & 0x3f;
    }
    *u = v;
    return 7 - n;
}
N
E_text_Z_getter_Z_c_R_rev_u( N (*getter)(void)
, U *u
){  N c = getter();
    if( !~c
    || c == E_mem_Q_file_S_eof
    )
        return c;
    if( (S8)c >= 0 )
    {   *u = c;
        return 1;
    }
    U v = 0;
    for_n( i, 7 )
    {   if(( c & 0xc0 ) != 0x80 )
            break;
        v |= ( c & 0x3f ) << ( i * 6 );
        c = getter();
        if( !~c
        || c == E_mem_Q_file_S_eof
        )
            return c;
    }
    N n = E_asm_I_bsr( ~(S8)c );
    if( n == ~0
    || n != 6 - i
    )
        return ~0;
    v |= ( c & (( _v( v, 1 ) << n ) - 1 )) << ( i * 6 );
    *u = v;
    return i;
}
LPWSTR
E_text_Z_s_Z_ansi_R_u( Pc s
){  N l = MultiByteToWideChar( CP_ACP, 0
    , s, -1
    , 0, 0
    );
    LPWSTR Mt_( s_u, l );
    if( !s_u )
        return 0;
    if( MultiByteToWideChar( CP_ACP, 0
    , s, -1
    , s_u, l
    ) != l )
        V( "MultiByteToWideChar" );
    return s_u;
}
Pc
E_text_Z_s_Z_ansi_R_utf8( Pc s
){  LPWSTR s_u = E_text_Z_s_Z_ansi_R_u(s);
    if( !s_u )
        return 0;
    N l = 0;
    s = M(l);
    LPWSTR s_u_ = s_u;
    while( *s_u_ )
    {   C s_[6];
        N l_ = E_text_Z_s_Z_u_R_utf8( *s_u_, &s_[0] );
        if( !E_mem_Q_blk_I_append( &s, l_ ))
            V( "E_mem_Q_blk_I_append" );
        E_text_Z_s_P_copy_( s + l, s_, &s_[ l_ ] );
        l += l_;
        s_u_++;
    }
    if( !E_mem_Q_blk_I_append( &s, 1 ))
        V( "E_mem_Q_blk_I_append" );
    s[l] = '\0';
    W( s_u );
    return s;
}
