#include "0.h"
B
E_mem_Q_file_Q_cache_T_pos_in( struct E_mem_Q_file_Z *file
, N pos
){  if( !file->blk_n )
        return no;
    if( U_E( file->current_blk, valid_sob ))
        return yes;
    if( U_E( file->current_blk, valid_eob ))
        return no;
    for( struct E_mem_Q_rel_map_blk_Z *blk = file->blk; blk != file->blk + file->blk_n; blk++ )
    {   if( pos < blk->pos )
            break;
        if( pos < blk->pos + blk->l )
        {   file->current_blk = blk - file->blk;
            file->current_blk_pos = pos - blk->pos;
            return yes;
        }
    }
    return no;
}
N
E_mem_Q_file_Q_cache_I_put( struct E_mem_Q_file_Z *file
, N data_pos
, N l
){  if( !file->blk_n )
    {   struct E_mem_Q_rel_map_blk_Z *new_blk = E_mem_Q_blk_I_append( &file->blk, file->blk_n = 1 );
        if( !new_blk )
            return ~0;
        new_blk->pos = data_pos;
        new_blk->data = M( new_blk->l = l );
        E_mem_Q_blk_I_copy( new_blk->data, E_base_S->E_mem_Q_file_S_buffer, l );
        file->current_blk = 0;
        file->current_blk_pos = file->pos - data_pos;
        return 0;
    }
    ///scalenie bloków danych wczytanych zawartych w bloku odczytanym z pliku.
    struct E_mem_Q_rel_map_blk_Z *blk, *blk_begin, *blk_end;
    for( blk = file->blk; blk != file->blk + file->blk_n; blk++ )
        if( data_pos < blk->pos )
            break;
    if(( blk == file->blk
      && data_pos + l < blk->pos
    ) || ( blk == file->blk + file->blk_n
      && data_pos >= ( blk - 1 )->pos + ( blk - 1 )->l )
    )
    {   struct E_mem_Q_rel_map_blk_Z *new_blk = E_mem_Q_blk_I_insert( &file->blk, blk - file->blk, 1 );
        if( !new_blk )
            return ~0;
        file->blk_n++;
        new_blk->pos = data_pos;
        new_blk->data = M( new_blk->l = l );
        E_mem_Q_blk_I_copy( new_blk->data, E_base_S->E_mem_Q_file_S_buffer, l );
        file->current_blk = blk - file->blk;
        file->current_blk_pos = file->pos - data_pos;
        return 0;
    }
    if( blk != file->blk )
        blk--;
    blk_begin = blk;
    for( ; blk != file->blk + file->blk_n; blk++ )
        if( data_pos + l >= blk->pos + blk->l )
            break;
    blk_end = blk - 1;
    struct E_mem_Q_rel_map_blk_Z new_blk;
    N pos_begin = blk_begin->pos;
    if( data_pos < pos_begin )
        pos_begin = data_pos;
    N pos_end = blk_end->pos + blk_end->l;
    if( data_pos + l > pos_end )
        pos_end = data_pos + l;
    new_blk.pos = pos_begin;
    new_blk.data = M( new_blk.l = pos_end - pos_begin );
    E_mem_Q_blk_I_copy( new_blk.data + ( data_pos - blk_begin->pos ), E_base_S->E_mem_Q_file_S_buffer, l );
    blk = blk_begin;
    O{  E_mem_Q_blk_I_copy( new_blk.data + ( blk->pos - new_blk.pos ), blk->data, blk->l );
        if( blk == blk_end )
            break;
        blk++;
    }
    N i = blk_begin - file->blk;
    N n = blk_end - blk_begin;
    if(n)
        if( !E_mem_Q_blk_I_rem( &file->blk, i + 1, n ))
            return ~0;
    file->blk[i] = new_blk;
    file->current_blk = i;
    file->current_blk_pos = file->pos - pos_begin;
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
I
E_mem_Q_file_M( Pc path
){  HANDLE fd;
    if(( fd = CreateFile( path
    , GENERIC_READ | GENERIC_WRITE
    , FILE_SHARE_READ
    , 0
    , OPEN_EXISTING
    , FILE_ATTRIBUTE_NORMAL
    , 0 )) == INVALID_HANDLE_VALUE )
        return ~0;
    I id = E_mem_Q_tab_I_add( E_base_S->E_mem_Q_file_S );
    if( !~id )
    {   CloseHandle(fd);
        return id;
    }
    struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    Mt_( file->blk, file->blk_n = 0 );
    Mt_( file->unsaved, file->unsaved_n = 0 );
    file->pos = 0;
    file->fd = fd;
    file->l = GetFileSize( fd, 0 );
    U_L( file->current_blk, valid );
    U_L( file->current_blk, valid_sob );
    U_L( file->current_blk, valid_eob );
    return id;
}
N
E_mem_Q_file_W( I id
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    struct E_mem_Z_range *range = file->unsaved;
    SetFilePointer( file->fd, file->l, 0, FILE_BEGIN );
    SetEndOfFile( file->fd );
    for_n( unsaved_i, file->unsaved_n )
    {   for_n( blk_i, file->blk_n )
            if( range->pos >= file->blk[ blk_i ].pos )
                break;
            N l = E_mem_Q_file_I_write_pos( file->fd
            , range->pos
            , file->blk[ blk_i ].data + range->pos - file->blk[ blk_i ].pos
            , range->pos_end - range->pos
            );
            if( !~l )
                return l;
            range++;
    }
    W( file->unsaved );
    for_n( blk_i, file->blk_n )
        W( file->blk[ blk_i ].data );
    W( file->blk );
    if( !CloseHandle( file->fd ))
        return ~0;
    if( E_mem_Q_tab_I_rem( E_base_S->E_mem_Q_file_S, id ))
        return ~0;
    return 0;
}
//------------------------------------------------------------------------------
N
E_mem_Q_file_I_save( I id
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    if( !file->unsaved_n )
        return 0;
    SetFilePointer( file->fd, file->l, 0, FILE_BEGIN );
    SetEndOfFile( file->fd );
    struct E_mem_Z_range *range = file->unsaved;
    for_n( unsaved_i, file->unsaved_n )
    {   for_n( blk_i, file->blk_n )
            if( range->pos >= file->blk[ blk_i ].pos )
                break;
            N l = E_mem_Q_file_I_write_pos( file->fd
            , range->pos
            , file->blk[ blk_i ].data + range->pos - file->blk[ blk_i ].pos
            , range->pos_end - range->pos
            );
            if( !~l )
                return l;
            range++;
    }
    if( !E_mem_Q_blk_I_rem( &file->unsaved, 0, file->unsaved_n ))
        return ~0;
    file->unsaved_n = 0;
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_mem_Q_file_I_write_pos( HANDLE fd
, N pos
, Pc data
, N data_l
){  if( SetFilePointer( fd, pos, 0, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
        return ~0;
    N l = 0;
    N l_;
    O{  if( !WriteFile( fd, data + l, data_l - l, &l_, 0 ))
            break;
        if( !l_ )
            break;
        l += l_;
        if( l == data_l )
            break;
    }
    return l;
}
N
E_mem_Q_file_I_read_pos( HANDLE fd
, N pos
){  if( SetFilePointer( fd, pos, 0, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
        return ~0;
    N l = 0;
    N l_;
    O{  if( !ReadFile( fd, E_base_S->E_mem_Q_file_S_buffer, E_base_S->E_mem_Q_file_S_buffer_l, &l_, 0 ))
            break;
        if( !l_ )
            break;
        l += l_;
        if( l == E_base_S->E_mem_Q_file_S_buffer_l )
            break;
    }
    return l;
}
N
E_mem_Q_file_R_current_blk( struct E_mem_Q_file_Z *file
){  if( U_R( file->current_blk, valid ))
        return 0;
    if( E_mem_Q_file_Q_cache_T_pos_in( file, file->pos ))
    {   U_F( file->current_blk, valid );
        return 0;
    }
    N data_pos = E_simple_Z_n_I_align_down_to_v_2( file->pos, E_base_S->E_mem_Q_file_S_buffer_l );
    N l = E_mem_Q_file_I_read_pos( file->fd, data_pos );
    if( !~l )
        return l;
    if( l
    && data_pos + l > file->l )
        l = file->l - data_pos;
    if( l <= file->pos - data_pos )
        return E_mem_Q_file_S_eof;
    if( !~E_mem_Q_file_Q_cache_I_put( file, data_pos, l ))
        return ~0;
    U_F( file->current_blk, valid );
    return l;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_mem_Q_file_R_pos( I id
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    return file->pos;
}
N
E_mem_Q_file_P_pos( I id
, N pos
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    if( pos > file->l )
        return ~0;
    file->pos = pos;
    U_L( file->current_blk, valid );
    U_L( file->current_blk, valid_sob );
    U_L( file->current_blk, valid_eob );
    return 0;
}
N
E_mem_Q_file_R_c( I id
, C *c
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    N ret = E_mem_Q_file_R_current_blk(file);
    if( !~ret
    || ret == E_mem_Q_file_S_eof
    )
        return ret;
    *c = file->blk[ file->current_blk ].data[ file->current_blk_pos++ ];
    file->pos++;
    if( file->current_blk_pos == file->blk[ file->current_blk ].l )
    {   U_L( file->current_blk, valid );
        U_F( file->current_blk, valid_eob );
    }
    return 0;
}
N
E_mem_Q_file_R_rev_c( I id
, C *c
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    N ret = E_mem_Q_file_R_current_blk(file);
    if( !~ret
    || ret == E_mem_Q_file_S_eof
    )
        return ret;
    *c = file->blk[ file->current_blk ].data[ file->current_blk_pos-- ];
    file->pos--;
    if( file->current_blk_pos == -1 )
    {   U_L( file->current_blk, valid );
        U_F( file->current_blk, valid_sob );
    }
    return 0;
}
N
E_mem_Q_file_R_s( I id
, Pc s
, N n
){  for_n( i, n )
    {   C c;
        N ret = E_mem_Q_file_R_c( id, &c );
        if(ret)
            return ret;
        s[i] = c;
    }
    return 0;
}
N
E_mem_Q_file_R_N( I id
, N *v
, N n
){  *v = 0;
    for_n( i, n )
    {   C c;
        N ret = E_mem_Q_file_R_c( id, &c );
        if(ret)
            return ret;
        *v |= (N)c << ( i * 8 );
    }
    return 0;
}
N
E_mem_Q_file_R_16( I id
, N *v
){  return E_mem_Q_file_R_N( id, v, 2 );
}
N
E_mem_Q_file_R_32( I id
, N *v
){  return E_mem_Q_file_R_N( id, v, 2 );
}
N
E_mem_Q_file_R_64( I id
, N *v
){  return E_mem_Q_file_R_N( id, v, 2 );
}
N
E_mem_Q_file_P_c( I id
, C c
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    N ret = E_mem_Q_file_R_current_blk(file);
    if( !~ret
    || ret == E_mem_Q_file_S_eof
    )
        return ret;
    ///czy da się skleić zakresy danych nie zapisanych.
    B blk_exists = no;
    for_n( unsaved_i, file->unsaved_n )
    {   if( file->pos < file->unsaved[ unsaved_i ].pos
        && file->pos + 1 >= file->unsaved[ unsaved_i ].pos
        ) ///przed blokiem
        {   blk_exists = yes;
            if( unsaved_i
            && file->unsaved[ unsaved_i - 1 ].pos_end + 1 >= file->unsaved[ unsaved_i ].pos
            )
            {   file->unsaved[ unsaved_i - 1 ].pos_end = file->unsaved[ unsaved_i ].pos_end;
                if( !E_mem_Q_blk_I_rem( &file->unsaved, unsaved_i, 1 ))
                    return ~0;
                file->unsaved_n--;
            }else
                file->unsaved[ unsaved_i ].pos = file->pos;
            break;
        }
        if( file->pos >= file->unsaved[ unsaved_i ].pos
        && file->pos < file->unsaved[ unsaved_i ].pos_end
        )
        {   blk_exists = yes;
            break;
        }
        if( file->pos == file->unsaved[ unsaved_i ].pos_end ) ///po bloku
        {   blk_exists = yes;
            if( unsaved_i + 1 != file->unsaved_n
            && file->unsaved[ unsaved_i + 1 ].pos <= file->unsaved[ unsaved_i ].pos_end + 1
            )
            {   file->unsaved[ unsaved_i ].pos_end = file->unsaved[ unsaved_i + 1 ].pos_end;
                if( !E_mem_Q_blk_I_rem( &file->unsaved, unsaved_i + 1, 1 ))
                    return ~0;
                file->unsaved_n--;
            }else
                file->unsaved[ unsaved_i ].pos_end++;
            break;
        }
        if( file->pos > file->unsaved[ unsaved_i ].pos_end )
            break;
    }
    if( !blk_exists )
    {   for_n( unsaved_i, file->unsaved_n )
            if( file->unsaved[ unsaved_i ].pos > file->pos )
                break;
        if( unsaved_i != file->unsaved_n )
        {   P new_blk = E_mem_Q_blk_I_insert( &file->unsaved, unsaved_i, 1 );
            if( !new_blk )
                return ~0;
        }else
        {   P new_blk = E_mem_Q_blk_I_append( &file->unsaved, 1 );
            if( !new_blk )
                return ~0;
        }
        file->unsaved_n++;
        file->unsaved[ unsaved_i ].pos = file->pos;
        file->unsaved[ unsaved_i ].pos_end = file->pos + 1;
    }
    ///ustawienie nowej pozycji w pliku.
    if( U_R( file->current_blk, valid ))
    {   if( file->current_blk_pos + 1 == file->blk[ file->current_blk ].l )
        {   U_L( file->current_blk, valid );
            U_F( file->current_blk, valid_eob );
        }
    }else if( U_R( file->current_blk, valid_eob ))
    {   if( file->current_blk != file->blk_n
        && file->blk[ file->current_blk + 1 ].pos - ( file->blk[ file->current_blk ].pos + file->blk[ file->current_blk ].l ) <= 1
        )
        {   N l = file->blk[ file->current_blk + 1 ].pos - ( file->blk[ file->current_blk ].pos + file->blk[ file->current_blk ].l );
            Pc pos = E_mem_Q_blk_I_append( &file->blk[ file->current_blk ].data, l + file->blk[ file->current_blk + 1 ].l );
            if( !pos )
                return ~0;
            file->blk[ file->current_blk ].l += l + file->blk[ file->current_blk + 1 ].l;
            E_mem_Q_blk_I_copy( pos + l, file->blk[ file->current_blk + 1 ].data, file->blk[ file->current_blk + 1 ].l );
            W( file->blk[ file->current_blk + 1 ].data );
            if( !E_mem_Q_blk_I_rem( &file->blk, file->current_blk + 1, 1 ))
                return ~0;
            file->blk_n--;
            U_F( file->current_blk, valid );
            U_L( file->current_blk, valid_eob );
        }else
        {   if( !E_mem_Q_blk_I_append( &file->blk[ file->current_blk ].data, 1 ))
                return ~0;
            file->blk[ file->current_blk ].l++;
        }
    }else if( U_R( file->current_blk, valid_sob ))
    {   if( file->current_blk
        && file->blk[ file->current_blk ].pos - ( file->blk[ file->current_blk - 1 ].pos + file->blk[ file->current_blk - 1 ].l ) <= 1
        )
        {   N l = file->blk[ file->current_blk ].pos - ( file->blk[ file->current_blk - 1 ].pos + file->blk[ file->current_blk - 1 ].l );
            file->current_blk--;
            file->current_blk_pos = file->blk[ file->current_blk ].l;
            file->blk[ file->current_blk ].l += l + file->blk[ file->current_blk + 1 ].l;
            Pc pos = E_mem_Q_blk_I_append( &file->blk[ file->current_blk ].data, l + file->blk[ file->current_blk + 1 ].l );
            if( !pos )
                return ~0;
            E_mem_Q_blk_I_copy( pos + l, file->blk[ file->current_blk + 1 ].data, file->blk[ file->current_blk + 1 ].l );
            W( file->blk[ file->current_blk + 1 ].data );
            if( !E_mem_Q_blk_I_rem( &file->blk, file->current_blk + 1, 1 ))
                return ~0;
            file->blk_n--;
            U_F( file->current_blk, valid );
        }else
        {   E_mem_Q_blk_I_prepend( &file->blk[ file->current_blk ].data, 1 );
            file->blk[ file->current_blk ].l++;
            if( file->current_blk_pos + 1 == file->blk[ file->current_blk ].l )
                U_F( file->current_blk, valid_eob );
            else
                U_F( file->current_blk, valid );
        }
        U_L( file->current_blk, valid_sob );
    }else
    {   for_n( blk_i, file->blk_n )
            if( file->pos >= file->blk[ blk_i ].pos )
                break;
        P p;
        if( blk_i != file->blk_n )
            p = E_mem_Q_blk_I_insert( &file->blk, blk_i, 1 );
        else
            p = E_mem_Q_blk_I_append( &file->blk, 1 );
        if( !p )
            return ~0;
        file->blk_n++;
        file->current_blk = blk_i;
        file->current_blk_pos = 0;
        file->blk[ file->current_blk ].data = M( file->blk[ file->current_blk ].l = 1 );
        file->blk[ file->current_blk ].pos = file->pos;
        U_F( file->current_blk, valid_eob );
    }
    file->pos++;
    *( file->blk[ file->current_blk ].data + file->current_blk_pos ) = c;
    file->current_blk_pos++;
    return 0;
}
N
E_mem_Q_file_P_s( I id
, Pc s
, N n
){  for( N i = 0; i != n; i++ )
    {   N ret;
        if( ret = E_mem_Q_file_P_c( id, s[i] ))
            return ret;
    }
    return 0;
}
N
E_mem_Q_file_P_N( I id
, N v
, N n
){  C s[n];
    for_n( i, n )
        s[i] = ( v >> ( i * 8 )) & 0xff;
    return E_mem_Q_file_P_s( id, &s[0], n );
}
N
E_mem_Q_file_P_16( I id
, N v
){  return E_mem_Q_file_P_N( id, v, 2 );
}
N
E_mem_Q_file_P_32( I id
, N v
){  return E_mem_Q_file_P_N( id, v, 4 );
}
N
E_mem_Q_file_P_64( I id
, N v
){  return E_mem_Q_file_P_N( id, v, 8 );
}
N
E_mem_Q_file_P_insert_c( I id
, C c
){  return E_mem_Q_file_P_insert_s( id, &(( C[] ){ c })[0], 1 );
}
N
E_mem_Q_file_P_insert_s( I id
, Pc s
, N n
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    U_L( file->current_blk, valid );
    U_L( file->current_blk, valid_sob );
    U_L( file->current_blk, valid_eob );
    N ret = E_mem_Q_file_R_current_blk(file);
    if( !~ret )
        return ret;
    if( ret == E_mem_Q_file_S_eof )
    {   file->current_blk = 0;
        file->current_blk_pos = 0;
        struct E_mem_Q_rel_map_blk_Z *new_blk = E_mem_Q_blk_I_append( &file->blk, file->blk_n = 1 );
        if( !new_blk )
            return ~0;
        new_blk->pos = file->l;
        new_blk->data = M( new_blk->l = 0 );
    }else if( file->blk[ file->blk_n - 1 ].pos > file->pos
    || file->blk[ file->blk_n - 1 ].pos + file->blk[ file->blk_n - 1 ].l != file->l
    )
    {   N pos = file->pos;
        while(( file->pos += E_base_S->E_mem_Q_file_S_buffer_l ) < file->l )
        {   U_L( file->current_blk, valid );
            U_L( file->current_blk, valid_sob );
            U_L( file->current_blk, valid_eob );
            E_mem_Q_file_R_current_blk(file);
        }
        U_L( file->current_blk, valid );
        U_L( file->current_blk, valid_sob );
        U_L( file->current_blk, valid_eob );
        file->pos = pos;
        E_mem_Q_file_R_current_blk(file);
    }
    if( !E_mem_Q_blk_I_append( &file->blk[ file->current_blk ].data, n ))
        return ~0;
    E_mem_Q_blk_I_copy_rev( file->blk[ file->current_blk ].data + file->current_blk_pos + n, file->blk[ file->current_blk ].data + file->current_blk_pos, file->blk[ file->current_blk ].l - file->current_blk_pos );
    file->blk[ file->current_blk ].l += n;
    file->l += n;
    E_mem_Q_blk_I_copy( file->blk[ file->current_blk ].data + file->current_blk_pos, s, n );
    B blk_exists = no;
    N unsaved_i = file->unsaved_n;
    while( ~--unsaved_i )
        if( file->pos >= file->unsaved[ unsaved_i ].pos )
        {   if( file->pos < file->unsaved[ unsaved_i ].pos_end )
            {   blk_exists = yes;
                if( file->unsaved[ unsaved_i ].pos_end < file->pos + n )
                    file->unsaved[ unsaved_i ].pos_end = file->pos + n;
            }else
            {   if( !E_mem_Q_blk_I_rem( &file->unsaved, unsaved_i, 1 ))
                    return ~0;
                file->unsaved_n--;
            }
        }else
            break;
    if( !blk_exists )
    {   struct E_mem_Z_range *unsaved = E_mem_Q_blk_I_append( &file->unsaved, 1 );
        if( !unsaved )
            return ~0;
        file->unsaved_n++;
        unsaved->pos = file->pos;
        unsaved->pos_end = file->pos + file->blk[ file->current_blk ].l;
    }
    file->current_blk_pos += n;
    return 0;
}
N
E_mem_Q_file_P_insert_N( I id
, N v
, N n
){  C s[n];
    for_n( i, n )
        s[i] = ( v >> ( i * 8 )) & 0xff;
    return E_mem_Q_file_P_insert_s( id, &s[0], n );
}
N
E_mem_Q_file_P_insert_16( I id
, N v
){  return E_mem_Q_file_P_insert_N( id, v, 2 );
}
N
E_mem_Q_file_P_insert_32( I id
, N v
){  return E_mem_Q_file_P_insert_N( id, v, 4 );
}
N
E_mem_Q_file_P_insert_64( I id
, N v
){  return E_mem_Q_file_P_insert_N( id, v, 8 );
}
N
E_mem_Q_file_P_rem_s( I id
, N n
){  struct E_mem_Q_file_Z *file = E_mem_Q_tab_R( E_base_S->E_mem_Q_file_S, id );
    U_L( file->current_blk, valid );
    U_L( file->current_blk, valid_sob );
    U_L( file->current_blk, valid_eob );
    N ret = E_mem_Q_file_R_current_blk(file);
    if( !~ret
    || ret == E_mem_Q_file_S_eof
    )
        return ret;
    if( !file->blk_n
    || file->blk[ file->blk_n - 1 ].pos > file->pos
    || file->blk[ file->blk_n - 1 ].pos + file->blk[ file->blk_n - 1 ].l != file->l
    )
    {   N pos = file->pos;
        while(( file->pos += E_base_S->E_mem_Q_file_S_buffer_l ) < file->l )
        {   U_L( file->current_blk, valid );
            U_L( file->current_blk, valid_sob );
            U_L( file->current_blk, valid_eob );
            E_mem_Q_file_R_current_blk(file);
        }
        U_L( file->current_blk, valid );
        U_L( file->current_blk, valid_sob );
        U_L( file->current_blk, valid_eob );
        file->pos = pos;
        E_mem_Q_file_R_current_blk(file);
    }
    N blk_l = file->blk[ file->current_blk ].l - n;
    if( blk_l )
    {   E_mem_Q_blk_I_copy( file->blk[ file->current_blk ].data + file->current_blk_pos, file->blk[ file->current_blk ].data + file->current_blk_pos + n, file->blk[ file->current_blk ].l - file->current_blk_pos - n );
        if( !E_mem_Q_blk_I_rem( &file->blk[ file->current_blk ].data, file->blk[ file->current_blk ].l - n, n ))
            return ~0;
        file->blk[ file->current_blk ].l = blk_l;
    }else
    {   W( file->blk[ file->current_blk ].data );
        if( !E_mem_Q_blk_I_rem( &file->blk, file->current_blk, 1 ))
            return ~0;
        file->blk_n--;
    }
    file->l -= n;
    B blk_exists = no;
    N unsaved_i = file->unsaved_n;
    while( ~--unsaved_i )
        if( file->pos >= file->unsaved[ unsaved_i ].pos )
        {   if( file->pos < file->unsaved[ unsaved_i ].pos_end )
            {   blk_exists = yes;
                if( blk_l - file->current_blk_pos )
                    file->unsaved[ unsaved_i ].pos_end = file->pos + blk_l - file->current_blk_pos;
                else
                {   if( !E_mem_Q_blk_I_rem( &file->unsaved, unsaved_i, 1 ))
                        return ~0;
                    file->unsaved_n--;
                }
            }else
            {   if( !E_mem_Q_blk_I_rem( &file->unsaved, unsaved_i, 1 ))
                    return ~0;
                file->unsaved_n--;
            }
        }else
            break;
    if( !blk_exists
    && blk_l - file->current_blk_pos
    )
    {   struct E_mem_Z_range *unsaved = E_mem_Q_blk_I_append( &file->unsaved, 1 );
        if( !unsaved )
            return ~0;
        file->unsaved_n++;
        unsaved->pos = file->pos;
        unsaved->pos_end = file->pos + blk_l - file->current_blk_pos;
    }
    return 0;
}

