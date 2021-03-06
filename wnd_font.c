#include "0.h"
struct E_mem_Q_tab_Z *E_wnd_Q_font_S;
//==============================================================================
N
E_wnd_Q_window_I_draw_Z_font(
  struct E_wnd_Q_window_Z *window
, S16 x
, S16 y
, N color
, I font_id
, U u
){  struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, font_id );
    for_n( i, font->bitmap_n )
        if( font->bitmap[i].u == u )
        {   N j = 0;
            C c;
            S16 x_, y_ = y;
            for_n( font_y, font->height )
            {   x_ = x;
                for_n( font_x, font->bitmap[i].width )
                {   if( j % 4 == 0 )
                        c = font->bitmap[i].bitmap[ j / 4 ];
                    if(( c >> ( j % 4 * 2 )) & 3 )
                    {   F brightness;
                        switch(( c >> ( j % 4 * 2 )) & 3 )
                        { case 1:
                              brightness = (F)( (N8)~0 >> 2 ) / (N8)~0;
                              break;
                          case 2:
                              brightness = (F)( (N8)~0 >> 1 ) / (N8)~0;
                              break;
                          case 3:
                              brightness = 1;
                              break;
                        }
                        E_wnd_Q_window_I_draw_aa_Z_pixel( window
                        , x_, y_
                        , color
                        , brightness
                        , 0
                        );
                    }
                    x_++;
                    j++;
                }
                y_++;
            }
            return 0;
        }
    return ~0;
}
N
E_wnd_Q_window_I_draw_Z_font_Z_s(
  struct E_wnd_Q_window_Z *window
, S16 x
, S16 y
, N color
, I font_id
, Pc s
){  struct E_wnd_Q_font_Z *font = E_mem_Q_tab_R( E_wnd_Q_font_S, font_id );
    U u;
    S16 x_ = x;
    while( *s )
    {   u = ~0;
        Pc s_ = E_text_Z_s_Z_utf8_R_u( s, &u );
        if( !~u )
            return ~0;
        s = s_;
        if( u == '\n' )
        {   x_ = x;
            y += font->height + 1;
            continue;
        }
        if( E_wnd_Q_window_I_draw_Z_font( window, x_, y, color, font_id, u ))
        {   u = font->bitmap[0].u;
            if( E_wnd_Q_window_I_draw_Z_font( window, x_, y, color, font_id, u ))
                return ~0;
        }
        for_n( i, font->bitmap_n )
            if( font->bitmap[i].u == u )
            {   x_ += font->bitmap[i].width + 1;
                break;
            }
    }
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N
E_wnd_Q_object_I_draw_Z_font(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, S16 x
, S16 y
, N color
, I font_id
, U u
){  return E_wnd_Q_window_I_draw_Z_font( window
    , object->x + x
    , object->y + y
    , !U_R( object->mode, drag_src ) ? color : E_wnd_Q_theme.inactive_text
    , font_id, u
    );
}
N
E_wnd_Q_object_I_draw_Z_font_Z_s(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, S16 x
, S16 y
, N color
, I font_id
, Pc s
){  return E_wnd_Q_window_I_draw_Z_font_Z_s( window
    , object->x + x
    , object->y + y
    , !U_R( object->mode, drag_src ) ? color : E_wnd_Q_theme.inactive_text
    , font_id, s
    );
}

