#include "0.h"
struct E_mem_Q_tab_Z *
E_mem_Q_tab_M(
  N u
, I n
){  struct E_mem_Q_tab_Z *tab = E_mem_Q_blk_M( sizeof( struct E_mem_Q_tab_Z ));
    if( !tab )
        return 0;
    Mt_( tab->index, n );
    if( !tab->index )
    {   W(tab);
        return 0;
    }
    tab->data = Mt( u, n );
    if( !tab->data )
    {   W( tab->index );
        W(tab);
        return 0;
    }
    tab->index_n = n;
    tab->data_n = n;
    tab->u = u;
    for_i( i, n )
        tab->index[i] = tab->data + i * tab->u;
    tab->iterator = 0;
    return tab;
}
void
E_mem_Q_tab_W( struct E_mem_Q_tab_Z *tab
){  if( U_R( E_base_S->E_flow_S_signal, exit_all ))
        return;
    if( tab->iterator )
    {   for_each( i, tab->iterator, E_mem_Q_tab )
        {   struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[i];
            W( iterator->index );
        }
        W( tab->iterator->data );
        W( tab->iterator->index );
        W( tab->iterator );
    }
    W( tab->data );
    W( tab->index );
    W(tab);
}
//------------------------------------------------------------------------------
B
E_mem_Q_tab_T( struct E_mem_Q_tab_Z *tab
, I id
){  return (In)tab->data_n > (In)id
    && tab->index[id];
}
I
E_mem_Q_tab_R_n( struct E_mem_Q_tab_Z *tab
){  return tab->data_n;
}
P
E_mem_Q_tab_R( struct E_mem_Q_tab_Z *tab
, I id
){  return tab->index[id];
}
I
E_mem_Q_tab_I_add( struct E_mem_Q_tab_Z *tab
){  for_i( id, tab->index_n )
        if( !tab->index[id] )
            break;
    Pc data = tab->data;
    N n_prepended;
    if( !E_mem_Q_blk_I_add( &tab->data, 1, &n_prepended, 0 ))
        return ~0;
    if( tab->data != data )
    {   for_i( i, id )
            tab->index[i] += tab->data + ( n_prepended ? tab->u : 0 ) - data;
        if( i != tab->index_n )
            while( ++i != tab->index_n )
                if( tab->index[i] )
                    tab->index[i] += tab->data + ( n_prepended ? tab->u : 0 ) - data;
    }
    if( id == tab->index_n )
    {   if( !E_mem_Q_blk_I_append( &tab->index, 1 ))
        {   if( !E_mem_Q_blk_I_rem( &tab->data, n_prepended ? 0 : tab->data_n, 1 ))
                V( "E_mem_Q_blk_I_rem" );
            return ~0;
        }
        tab->index_n++;
    }
    tab->index[id] = tab->data + ( n_prepended ? 0 : id * tab->u );
    tab->data_n++;
    if( tab->iterator )
    {   for_i( i, tab->iterator->index_n )
        {   struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[i];
            if(iterator)
            {   I *p = E_mem_Q_blk_I_append( &iterator->index, 1 );
                if( !p )
                    V( "E_mem_Q_blk_I_append" );
                *p = id;
                iterator->n++;
            }
        }
    }
    return id;
}
I
E_mem_Q_tab_I_add_i( struct E_mem_Q_tab_Z *tab
, I id
){  Pc data = tab->data;
    N n_prepended;
    if( !E_mem_Q_blk_I_add( &tab->data, 1, &n_prepended, 0 ))
        return ~0;
    if( tab->data != data )
    {   if( id < tab->index_n )
        {   for_i( i, id )
                tab->index[i] += tab->data + ( n_prepended ? tab->u : 0 ) - data;
            if( i != tab->index_n )
                while( ++i != tab->index_n )
                    if( tab->index[i] )
                        tab->index[i] += tab->data + ( n_prepended ? tab->u : 0 ) - data;
        }else
        {   for_i( i, tab->index_n )
                tab->index[i] += tab->data + ( n_prepended ? tab->u : 0 ) - data;
        }
    }
    if( id >= tab->index_n )
    {   if( !E_mem_Q_blk_I_append( &tab->index, id + 1 - tab->index_n ))
        {   if( !E_mem_Q_blk_I_rem( &tab->data, n_prepended ? 0 : tab->data_n, id + 1 - tab->index_n ))
            {   V( "E_mem_Q_blk_I_rem" );
            }
            return ~0;
        }
        for( I i = tab->index_n; (In)i < (In)id; i++ )
            tab->index[i] = 0;
        tab->index_n = id + 1;
    }
    tab->index[id] = tab->data + ( n_prepended ? 0 : id * tab->u );
    tab->data_n++;
    if( tab->iterator )
    {   for_i( i, tab->iterator->index_n )
        {   struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[i];
            if(iterator)
            {   I *p = E_mem_Q_blk_I_append( &iterator->index, 1 );
                if( !p )
                    V( "E_mem_Q_blk_I_append" );
                *p = id;
                iterator->n++;
            }
        }
    }
    return id;
}
N
E_mem_Q_tab_I_rem( struct E_mem_Q_tab_Z *tab
, I id
){  if( tab->iterator )
    {   for_i( i, tab->iterator->index_n )
            if( tab->iterator->index[i] )
            {   struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[i];
                for_i( j, iterator->n )
                    if( iterator->index[j] == id )
                    {   iterator->n--;
                        if( !E_mem_Q_blk_I_rem( &iterator->index, j, 1 ))
                            return ~0;
                        break;
                    }
            }
    }
    Pc p = tab->index[id];
    if( id == tab->index_n - 1 )
    {   I i = id;
        while(i)
            if( tab->index[ --i ])
            {   i++;
                break;
            }
        tab->index_n = i;
        if( !E_mem_Q_blk_I_rem( &tab->index, i, id - i + 1 ))
            tab->index[id] = 0;
    }else
        tab->index[id] = 0;
    Pc data = tab->data;
    tab->data_n--;
    if( !E_mem_Q_blk_I_rem( &tab->data, ( p - tab->data ) / tab->u, 1 ))
        return ~0;
    if( tab->data != data )
    {   for_i( i, tab->index_n )
            if( tab->index[i] )
            {   if( tab->index[i] > p )
                    tab->index[i] -= tab->u;
                tab->index[i] += tab->data - data;
            }
    }else
    {   for_i( i, tab->index_n )
            if( tab->index[i] > p )
                tab->index[i] -= tab->u;
    }
    return 0;
}
#if 0
N
E_mem_Q_tab_I_copy( //NDFN kolejność do odwrócenia.
  struct E_mem_Q_tab_Z *tab_src
, I src_id
, struct E_mem_Q_tab_Z *tab_dest
){  I dest_id = E_mem_Q_tab_I_add( tab_dest );
    E_mem_Q_blk_P_copy( tab_dest->index[ dest_id ], tab_src->index[ src_id ], tab_src->u );
    return dest_id;
}
N
E_mem_Q_tab_I_move(
  struct E_mem_Q_tab_Z *tab_src
, I src_id
, struct E_mem_Q_tab_Z *tab_dest
){  I dest_id = E_mem_Q_tab_I_copy( tab_src, src_id, tab_dest );
    E_mem_Q_tab_I_rem( tab_src, src_id );
    return dest_id;
}
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///iteratory statyczne. gdy wiadomo, że nie nastąpi przełączenie ‹zadania›, ponieważ wyliczenie wartości musi być wykonane w jednym ‹atomie›, i nie nastąpi zmiana kolekcji.
I
E_mem_Q_tab_Z_iter_R_next( struct E_mem_Q_tab_Z *tab
, I id
, I out_id ///pomijany— i od następnego do poprzedniego elementu.
){  if( (In)id + 1 > (In)out_id )
    {   while( ++id != tab->index_n )
            if( tab->index[id] )
                return id;
        id = ~0;
    }
    if( !~out_id )
        out_id = tab->index_n;
    while( ++id != out_id )
        if( tab->index[id] )
            return id;
    return ~0;
}
I
E_mem_Q_tab_Z_iter_R_prev( struct E_mem_Q_tab_Z *tab
, I id
, I out_id
){  if( !~id )
        id = tab->index_n;
    if( (In)id - 1 < (In)out_id )
    {   while( ~--id )
            if( tab->index[id] )
                return id;
        if( !~out_id )
            return ~0;
        id = tab->index_n;
    }
    while( --id != out_id )
        if( tab->index[id] )
            return id;
    return ~0;
}
//------------------------------------------------------------------------------
I
E_mem_Q_tab_Q_iter_M( struct E_mem_Q_tab_Z *tab
, I out_id
){  I n = tab->data_n;
    if( ~out_id
    && n
    )
        n--;
    I iterator_id;
    if( tab->iterator )
    {   iterator_id = E_mem_Q_tab_I_add( tab->iterator );
        if( !~iterator_id )
            return ~0;
    }else
    {   tab->iterator = E_mem_Q_tab_M( sizeof( struct E_mem_Q_tab_S_iterator_Z ), 1 );
        if( !tab->iterator )
            return ~0;
        iterator_id = 0;
    }
    struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[ iterator_id ];
    Mt_( iterator->index, n );
    if( !iterator->index )
    {   if( iterator_id )
            E_mem_Q_tab_I_rem( tab->iterator, iterator_id );
        else
            W_tab_( tab->iterator );
        return ~0;
    }
    iterator->n = n;
    I i = 0;
    I id;
    for( id = out_id + 1; id != tab->index_n; id++ )
        if( tab->index[id] )
            iterator->index[ i++ ] = id;
    if( ~out_id )
    {   for_i_( id, out_id )
            if( tab->index[id] )
                iterator->index[ i++ ] = id;
    }
    return iterator_id;
}
///OLET do zwalniania ‘iteratora’ tylko wtedy, gdy nie zakończy się wartością “empty” (czyli gdy pętla zostanie przerwana).
void
E_mem_Q_tab_Q_iter_W( struct E_mem_Q_tab_Z *tab
, I iterator_id
){  struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[ iterator_id ];
    W( iterator->index );
    if( tab->iterator->data_n != 1 )
        E_mem_Q_tab_I_rem( tab->iterator, iterator_id );
    else
        W_tab_( tab->iterator );
}
I
E_mem_Q_tab_Q_iter_R_next( struct E_mem_Q_tab_Z *tab
, I iterator_id
, I id
){  struct E_mem_Q_tab_S_iterator_Z *iterator = (P)tab->iterator->index[ iterator_id ];
    return (In)id < (In)iterator->n ? iterator->index[id] : ~0;
}

