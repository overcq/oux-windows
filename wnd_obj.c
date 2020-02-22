#include "0.h"
S16 E_wnd_Q_object_S_layout_dx = 4;
S16 E_wnd_Q_object_S_layout_dy = 4;
B U_R( E_wnd_S_mode, draw_simple ) = no;
//==============================================================================
I
E_wnd_Q_object_M(
  struct E_wnd_Q_window_Z *window
, N child_n
, S16 x
, S16 y
, N16 width
, N16 height
, void
  (*clear_data)(P)
, draw_object_proc draw
, click_object_proc click
){  I object_id = E_mem_Q_tab_I_add( window->object );
    if( !~object_id )
        return ~0;
    struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
    object->draw = draw;
    object->click = click;
    object->clear_data = clear_data;
    object->child_n = child_n;
    Mt_( object->child, child_n );
    if( !object->child )
    {   E_mem_Q_tab_I_rem( window->object, object_id );
        return ~0;
    }
    object->data = 0;
    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    U_L( object->mode, lay_height );
    U_L( object->mode, draggable );
    U_L( object->mode, drag_src );
    return object_id;
}
void
E_wnd_Q_object_W(
  struct E_wnd_Q_window_Z *window
, I object_id
){  struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
    if( object->data )
    {   if( object->clear_data )
            object->clear_data( object->data );
        W( object->data );
    }
    W( object->child );
    E_mem_Q_tab_I_rem( window->object, object_id );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
I
E_wnd_Q_object_R_parent( struct E_wnd_Q_window_Z *window
, I id
){  for_each( object_id, window->object, E_mem_Q_tab )
    {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
        for_n( child_i, object->child_n )
        {   if( object->child[ child_i ] == id )
                return object_id;
        }
    }
    return ~0;
}
B
E_wnd_Q_object_R_top( struct E_wnd_Q_window_Z *window
, I id
){  return !~E_wnd_Q_object_R_parent( window, id );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_wnd_Q_object_I_add( struct E_wnd_Q_window_Z *window
, I id
, I child_id
){  struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, id );
    if( !E_mem_Q_blk_I_append( &object->child, 1 ))
        return ~0;
    object->child[ object->child_n ] = child_id;
    object->child_n++;
    return 0;
}
//------------------------------------------------------------------------------
N
E_wnd_Q_object_I_rem( struct E_wnd_Q_window_Z *window
, I id
){  for_each( object_id, window->object, E_mem_Q_tab )
    {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
        for_n( child_i, object->child_n )
        {   if( object->child[ child_i ] == id )
            {   E_mem_Q_blk_I_rem( &object->child, child_i, 1 );
                object->child_n--;
                struct E_wnd_Q_object_Z *object_rem = E_mem_Q_tab_R( window->object, id );
                if( object_rem->child_n )
                {   if( !E_mem_Q_blk_I_append( &object->child, object_rem->child_n ))
                        return ~0;
                    E_mem_Q_blk_I_copy_rev( &object->child[ child_i ] + object_rem->child_n, &object->child[ child_i ], ( object->child_n - child_i ) * sizeof( object->child[0] ));
                    for_n( i, object_rem->child_n )
                        object->child[ child_i + i ] = object_rem->child[i];
                    object->child_n += object_rem->child_n;
                }
                goto End;
            }
        }
    }
End:E_mem_Q_tab_I_rem( window->object, id );
    return 0;
}
N
E_wnd_Q_object_I_rem_descendants( struct E_wnd_Q_window_Z *window
, I id
){  struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, id );
    N ids_n = object->child_n;
    I * Mt_( ids, ids_n );
    if( !ids )
        return ~0;
    for_n( child_i, object->child_n )
        ids[ child_i ] = object->child[ child_i ];
    E_mem_Q_blk_I_rem( &object->child, 0, object->child_n );
    object->child_n = 0;
    for_n( ids_i, ids_n )
    {   object = E_mem_Q_tab_R( window->object, ids[ ids_i ] );
        if( !E_mem_Q_blk_I_append( &ids, object->child_n ))
            return ~0;
        for_n( child_i, object->child_n )
            ids[ ids_n + child_i ] = object->child[ child_i ];
        ids_n += object->child_n;
    }
    for_n_( ids_i, ids_n )
        E_mem_Q_tab_I_rem( window->object, ids[ ids_i ] );
    W(ids);
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
I
E_wnd_Q_object_Z_button_M(
  struct E_wnd_Q_window_Z *window
){  return E_wnd_Q_object_M( window
    , 0
    , 0
    , 0
    , 20
    , 10
    , 0
    , &E_wnd_Q_object_Z_button_I_draw
    , 0
    );
}
void
E_wnd_Q_object_Z_button_I_draw(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
){  E_wnd_Q_object_I_draw_P_color( object, E_wnd_Q_theme.line );
    E_wnd_Q_object_I_fill_Z_rectangles( window, object
    , 1
    , ( RECT [] )
      { { 0, 0
        , object->width, object->height
        }
      }
    );
    E_wnd_Q_object_I_draw_P_color( object, E_wnd_Q_theme.object_bg );
    E_wnd_Q_object_I_fill_Z_points( window, object
    , 4
    , ( POINT[] )
      { { 1, 1 }
      , { object->width - 1, 1 }
      , { object->width - 1, object->height - 1 }
      , { 1, object->height - 1 }
      }
    );
}
//------------------------------------------------------------------------------
void
E_wnd_Q_object_Z_entry_I_clear_data( P data
){  struct E_wnd_Q_object_Z_data_Z_entry *object_data = data;
    W( object_data->text );
}
I
E_wnd_Q_object_Z_entry_M(
  struct E_wnd_Q_window_Z *window
, I font_id
, Pc text
){  I object_id = E_wnd_Q_object_M( window
    , 0
    , 0
    , 0
    , 16
    , 8
    , &E_wnd_Q_object_Z_font_I_clear_data
    , &E_wnd_Q_object_Z_entry_I_draw
    , 0
    );
    struct E_wnd_Q_object_Z_data_Z_entry *M_( object_data );
    if( !object_data )
    {   E_wnd_Q_object_W( window, object_id );
        return ~0;
    }
    object_data->font = font_id;
    object_data->text = M( E_text_Z_s0_R_0_l(text) );
    object_data->text_start = 0;
    if( !object_data->text )
    {   E_wnd_Q_object_W( window, object_id );
        return ~0;
    }
    E_text_Z_s0_P_copy_0( object_data->text, text );
    U_L( object_data->state, visible );
    struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
    object->data = object_data;
    return object_id;
}
void
E_wnd_Q_object_Z_entry_I_draw(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
){  E_wnd_Q_object_I_draw_P_color( object, E_wnd_Q_theme.window_bg );
    E_wnd_Q_object_I_fill_Z_rectangles( window, object
    , 1
    , ( RECT[] )
      { { 0, 0
        , object->width, object->height
        }
      }
    );
    struct E_wnd_Q_object_Z_data_Z_entry *object_data = object->data;
    struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, object_data->font );
    S16 x = 0;
    Pc s = object_data->text;
    for_n( i, object_data->text_start )
    {   U u = ~0;
        s = E_text_Z_s_Z_utf8_R_u( s, &u );
        if( !~u )
            V( "E_text_Z_s_Z_utf8_R_u" );
    }
    Pc s_ = s;
    while( *s )
    {   U u = ~0;
        s = E_text_Z_s_Z_utf8_R_u( s, &u );
        if( !~u )
            V( "E_text_Z_s_Z_utf8_R_u" );
        for_n( i, font->bitmap_n )
            if( font->bitmap[i].u == u )
            {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                break;
            }
        if( i == font->bitmap_n )
            x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
        if( x > object->width )
            break;
    }
    C c = *s;
    *s = '\0';
    E_wnd_Q_object_I_draw_Z_font_Z_s( window, object, 0, 0, E_wnd_Q_theme.text, object_data->font, s_ );
    *s = c;
    if( U_R( object_data->state, visible ))
    {   struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, object_data->font );
        S16 x = 0;
        Pc s = object_data->text;
        for_n( i, object_data->text_start )
        {   U u = ~0;
            s = E_text_Z_s_Z_utf8_R_u( s, &u );
            if( !~u )
                V( "E_text_Z_s_Z_utf8_R_u" );
        }
        N l = object_data->cursor_pos - object_data->text_start;
        while( l && *s )
        {   U u = ~0;
            s = E_text_Z_s_Z_utf8_R_u( s, &u );
            if( !~u )
                V( "E_text_Z_s_Z_utf8_R_u" );
            for_n( i, font->bitmap_n )
                if( font->bitmap[i].u == u )
                {   x += ( x != 0 ? 1 : 0 ) + font->bitmap[i].width;
                    break;
                }
            if( i == font->bitmap_n )
                x += ( x != 0 ? 1 : 0 ) + font->bitmap[0].width;
            l--;
        }
        E_wnd_Q_object_I_draw_P_color( object, E_wnd_Q_theme.cursor );
        RECT segments[1] =
        { x, 0
        , x, object->height - 1
        };
        E_wnd_Q_object_I_draw_Z_segments( window, object, 1, segments );
    }
}
//------------------------------------------------------------------------------
void
E_wnd_Q_object_Z_font_I_clear_data( P data
){  struct E_wnd_Q_object_Z_data_Z_font *object_data = data;
    W( object_data->label );
}
I
E_wnd_Q_object_Z_font_M(
  struct E_wnd_Q_window_Z *window
, I font_id
, Pc label
){  struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, font_id );
    N16 width = 2, width_ = 0;
    N16 height = font->height;
    Pc s = label;
    while( *s )
    {   if( *s == '\n' )
        {   if( width_ > width )
                width = width_;
            width_ = 0;
            height += 1 + font->height;
            s++;
        }else
        {   U u = ~0;
            s = E_text_Z_s_Z_utf8_R_u( s, &u );
            if( !~u )
                return ~0;
            for_n( i, font->bitmap_n )
                if( font->bitmap[i].u == u )
                {   width_ += ( width_ != 0 ? 1 : 0 ) + font->bitmap[i].width;
                    break;
                }
            if( i == font->bitmap_n )
                return ~0;
        }
    }
    if( width_ > width )
        width = width_;
    I object_id = E_wnd_Q_object_M( window
    , 0
    , 0
    , 0
    , width
    , height
    , &E_wnd_Q_object_Z_font_I_clear_data
    , &E_wnd_Q_object_Z_font_I_draw
    , 0
    );
    struct E_wnd_Q_object_Z_data_Z_font *M_( object_data );
    if( !object_data )
    {   E_wnd_Q_object_W( window, object_id );
        return ~0;
    }
    object_data->font = font_id;
    object_data->label = M( E_text_Z_s0_R_0_l(label) );
    if( !object_data->label )
    {   E_wnd_Q_object_W( window, object_id );
        return ~0;
    }
    E_text_Z_s0_P_copy_0( object_data->label, label );
    struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
    object->data = object_data;
    return object_id;
}
void
E_wnd_Q_object_Z_font_I_draw(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
){  struct E_wnd_Q_object_Z_data_Z_font *object_data = object->data;
    E_wnd_Q_object_I_draw_Z_font_Z_s( window, object, 0, 0, E_wnd_Q_theme.text, object_data->font, object_data->label );
}
//------------------------------------------------------------------------------
I
E_wnd_Q_object_Z_frame_M(
  struct E_wnd_Q_window_Z *window
){  return E_wnd_Q_object_M( window
    , 0
    , 0
    , 0
    , 16
    , 8
    , 0
    , &E_wnd_Q_object_Z_frame_I_draw
    , 0
    );
}
void
E_wnd_Q_object_Z_frame_I_draw(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
){  E_wnd_Q_object_I_draw_P_color( object, E_wnd_Q_theme.line );
    E_wnd_Q_object_I_draw_Z_rectangles( window, object
    , 1
    , ( RECT[] )
      { { 0, 0
        , object->width, object->height
        }
      }
    );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_wnd_Q_object_I_lay(
  struct E_wnd_Q_window_Z *window
){  if( !E_mem_Q_tab_R_n( window->object ))
        return 0;
    struct Z_stack
    { struct E_wnd_Q_object_Z *object;
      N i;
    };
    struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, 0 );
    if( object->child_n )
    {   for_each( id, window->object, E_mem_Q_tab )
        {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, id );
            U_L( object->mode, lay_height );
        }
Restart:;
        struct Z_stack *stack = Mt( sizeof( struct Z_stack ), 0 );
        if( !stack )
            return ~0;
        N stack_i = ~0;
        S16 next_x = E_wnd_Q_object_S_layout_dx;
        S16 next_y = E_wnd_Q_object_S_layout_dy;
        S16 after_x = E_wnd_Q_object_S_layout_dx;
        S16 after_y = E_wnd_Q_object_S_layout_dy;
        O{  if( object->child_n )
            {   if( ~stack_i )
                    if( U_R( object->mode, lay_height ))
                    {   next_x = stack[ stack_i ].object->x + E_wnd_Q_object_S_layout_dx;
                        after_x = next_x + E_wnd_Q_object_S_layout_dx;
                        next_y = after_y;
                        after_y += E_wnd_Q_object_S_layout_dy;
                    }else
                        after_y = next_y + E_wnd_Q_object_S_layout_dy;
                struct Z_stack *stack_top = E_mem_Q_blk_I_append( &stack, 1 );
                if( !stack_top )
                {   W(stack);
                    return ~0;
                }
                stack_i++;
                stack_top->object = object;
                stack_top->i = 0;
                object->x = next_x;
                object->y = next_y;
                object->width = E_wnd_Q_object_S_layout_dx;
                object->height = E_wnd_Q_object_S_layout_dy;
                next_x += E_wnd_Q_object_S_layout_dx;
                if( next_x > window->width
                && !U_R( object->mode, lay_height )
                ){  U_F( object->mode, lay_height );
                    do
                    {   object = stack[ stack_i ].object;
                    }while( ~--stack_i
                    && !stack[ stack_i ].i
                    );
                    U_F( object->mode, lay_height );
                    W(stack);
                    object = E_mem_Q_tab_R( window->object, 0 );
                    goto Restart;
                }
                next_y += E_wnd_Q_object_S_layout_dy;
                object = E_mem_Q_tab_R( window->object, object->child[0] );
                continue;
            }
            if( stack[ stack_i ].i != stack[ stack_i ].object->child_n )
            {   stack[ stack_i ].i++;
                if( U_R( object->mode, lay_height )
                && stack[ stack_i ].i != 1
                ){  next_x = stack[ stack_i ].object->x + E_wnd_Q_object_S_layout_dx;
                    next_y = after_y;
                }
                object->x = next_x;
                object->y = next_y;
                if( after_x < next_x + object->width + E_wnd_Q_object_S_layout_dx )
                    after_x = next_x + object->width + E_wnd_Q_object_S_layout_dx;
                if( after_y < next_y + object->height + E_wnd_Q_object_S_layout_dy )
                    after_y = next_y + object->height + E_wnd_Q_object_S_layout_dy;
                struct E_wnd_Q_object_Z *object_ = object;
                N stack_i_ = stack_i;
                N16 after_x_ = after_x;
                N16 after_y_ = after_y;
                do
                {   object_ = stack[ stack_i_ ].object;
                    if( object_->width < after_x_ - object_->x )
                        object_->width = after_x_ - object_->x;
                    if( object_->height < after_y_ - object_->y )
                        object_->height = after_y_ - object_->y;
                    after_x_ += E_wnd_Q_object_S_layout_dx;
                    after_y_ += E_wnd_Q_object_S_layout_dy;
                }while( ~--stack_i_ );
                next_x += object->width + E_wnd_Q_object_S_layout_dx;
                if( next_x > window->width
                && !U_R( object->mode, lay_height )
                ){  U_F( object->mode, lay_height );
                    if( stack[ stack_i ].i == 1 )
                    {   do
                        {   object = stack[ stack_i ].object;
                        }while( ~--stack_i
                        && !stack[ stack_i ].i
                        );
                        U_F( object->mode, lay_height );
                    }
                    W(stack);
                    object = E_mem_Q_tab_R( window->object, 0 );
                    goto Restart;
                }
                if( stack[ stack_i ].i != stack[ stack_i ].object->child_n )
                {   object = E_mem_Q_tab_R( window->object, stack[ stack_i ].object->child[ stack[ stack_i ].i ] );
                    continue;
                }
            }
            N stack_i_1 = stack_i;
            do
            {   next_x = stack[ stack_i ].object->x + stack[ stack_i ].object->width + E_wnd_Q_object_S_layout_dx;
                if( next_x > window->width
                && !U_R( stack[ stack_i ].object->mode, lay_height )
                ){  U_F( stack[ stack_i ].object->mode, lay_height );
                    N stack_i_ = stack_i;
                    O{  if( object->child_n )
                        {   struct Z_stack *stack_top = E_mem_Q_blk_I_append( &stack, 1 );
                            if( !stack_top )
                            {   W(stack);
                                return ~0;
                            }
                            stack_i_++;
                            stack_top->object = object;
                            stack_top->i = object->child_n;
                            object = E_mem_Q_tab_R( window->object, object->child[ stack_top->i - 1 ] );
                            continue;
                        }
                        if( ~stack[ stack_i_ ].i )
                        {   stack[ stack_i_ ].i--;
                            U_L( object->mode, lay_height );
                            if( ~stack[ stack_i_ ].i )
                            {   object = E_mem_Q_tab_R( window->object, stack[ stack_i_ ].object->child[ stack[ stack_i_ ].i ] );
                                continue;
                            }
                        }
                        N stack_i_1 = stack_i_;
                        do
                        {   if( stack_i_ == stack_i )
                                goto Cont;
                            U_L( stack[ stack_i_ ].object->mode, lay_height );
                            stack_i_--;
                            if( ~stack[ stack_i_ ].i )
                                stack[ stack_i_ ].i--;
                        }while( !~stack[ stack_i_ ].i );
                        E_mem_Q_blk_I_rem( &stack, stack_i_ + 1, stack_i_1 - stack_i_ );
                        object = E_mem_Q_tab_R( window->object, stack[ stack_i_ ].object->child[ stack[ stack_i_ ].i ] );
                    }
Cont:               do
                    {   object = stack[ stack_i ].object;
                    }while( ~--stack_i
                    && !stack[ stack_i ].i
                    );
                    U_F( object->mode, lay_height );
                    W(stack);
                    object = E_mem_Q_tab_R( window->object, 0 );
                    goto Restart;
                }
                next_y -= E_wnd_Q_object_S_layout_dy;
                if( after_y < stack[ stack_i ].object->y + stack[ stack_i ].object->height + E_wnd_Q_object_S_layout_dy )
                    after_y = stack[ stack_i ].object->y + stack[ stack_i ].object->height + E_wnd_Q_object_S_layout_dy;
            }while( ~--stack_i
            && ++stack[ stack_i ].i == stack[ stack_i ].object->child_n
            );
            if( !~stack_i )
                break;
            E_mem_Q_blk_I_rem( &stack, stack_i + 1, stack_i_1 - stack_i );
            object = E_mem_Q_tab_R( window->object, stack[ stack_i ].object->child[ stack[ stack_i ].i ] );
        }
        W(stack);
    }
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_wnd_Q_object_I_draw_Z_draw_proc( draw_object_proc draw_object_proc
){  for_each( window_id, E_wnd_Q_window_S, E_mem_Q_tab )
    {   struct E_wnd_Q_window_Z *window = E_mem_Q_tab_R( E_wnd_Q_window_S, window_id );
        for_each( object_id, window->object, E_mem_Q_tab )
        {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( window->object, object_id );
            if( object->draw == draw_object_proc )
            {   RECT rectangle =
                { object->x, object->y
                , object->x + object->width, object->y + object->height
                };
                InvalidateRect( window->h, &rectangle, TRUE );
            }
        }
    }
    if( U_R( E_wnd_S_mode, drag ))
    {   for_each( object_id, E_wnd_Q_dnd_window_S.object, E_mem_Q_tab )
        {   struct E_wnd_Q_object_Z *object = E_mem_Q_tab_R( E_wnd_Q_dnd_window_S.object, object_id );
            if( object->draw == draw_object_proc )
            {   RECT rectangle =
                { object->x, object->y
                , object->x + object->width, object->y + object->height
                };
                InvalidateRect( E_wnd_Q_dnd_window_S.h, &rectangle, TRUE );
                break;
            }
        }
    }
}

