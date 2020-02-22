#include "0.h"
N32 E_wnd_S_draw_color = ~0;
N32
E_wnd_Z_color_M(
  N8 red
, N8 green
, N8 blue
){  return RGB( red, green, blue );
}
N8
E_wnd_Z_color_R_blue( N32 color
){  return GetBValue(color);
}
N8
E_wnd_Z_color_R_green( N32 color
){  return GetGValue(color);
}
N8
E_wnd_Z_color_R_red( N32 color
){  return GetRValue(color);
}
N32
E_wnd_Z_color_M_gray(
  N8 luminance
){  return E_wnd_Z_color_M( luminance, luminance, luminance );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_wnd_Q_window_I_draw_P_color(
  N32 color
){  E_wnd_S_draw_color = color;
}
//------------------------------------------------------------------------------
void
E_wnd_Q_window_I_draw_Z_points(
  struct E_wnd_Q_window_Z *window
, N32 n
, POINT *points
){  for_n( i, n )
        if( points[i].x < window->width && points[i].y < window->height )
        {   SetPixel( window->drawable_dc, points[i].x, points[i].y, E_wnd_S_draw_color );
            if( !U_R( E_wnd_S_state, draw_object_drag_move ))
                window->object_mask[ points[i].x + window->width * points[i].y ] = E_wnd_S_current_object;
            else
            {   OffsetRgn( E_wnd_S_drag_region_pixel, points[i].x, points[i].y );
                CombineRgn( E_wnd_S_drag_region, E_wnd_S_drag_region, E_wnd_S_drag_region_pixel, RGN_OR );
                OffsetRgn( E_wnd_S_drag_region_pixel, -points[i].x, -points[i].y );
            }
        }
}
N
E_wnd_Q_window_I_draw_Z_segments_Z_low(
  struct E_wnd_Q_window_Z *window
, RECT segment
){  S16 dx = segment.right - segment.left;
    S16 dy = segment.bottom - segment.top;
    S16 yi = 1;
    if( dy < 0 )
    {   yi = -yi;
        dy = -dy;
    }
    S16 D = 2 * dy - dx;
    S16 y = segment.top;
    POINT *Mt_( points, dx + 1 );
    if( !points )
        return ~0;
    for_n( j, dx + 1 )
    {   points[j].x = segment.left + j;
        points[j].y = y;
        if( D > 0 )
        {   y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
    E_wnd_Q_window_I_draw_Z_points( window, dx + 1, points );
    W(points);
    return 0;
}
N
E_wnd_Q_window_I_draw_Z_segments_Z_high(
  struct E_wnd_Q_window_Z *window
, RECT segment
){  S16 dx = segment.right - segment.left;
    S16 dy = segment.bottom - segment.top;
    S16 xi = 1;
    if( dx < 0 )
    {   xi = -xi;
        dx = -dx;
    }
    S16 D = 2 * dx - dy;
    S16 x = segment.left;
    POINT *Mt_( points, dy + 1 );
    if( !points )
        return ~0;
    for_n( j, dy + 1 )
    {   points[j].x = x;
        points[j].y = segment.top + j;
        if( D > 0 )
        {   x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
    E_wnd_Q_window_I_draw_Z_points( window, dy + 1, points );
    W(points);
    return 0;
}
N
E_wnd_Q_window_I_draw_Z_segments(
  struct E_wnd_Q_window_Z *window
, N32 n
, RECT *segments
){  for_n( i, n )
        if( segments[i].left == segments[i].right )
        {   POINT *Mt_( points, abs( segments[i].bottom - segments[i].top ) + 1 );
            if( !points )
                return ~0;
            for_n( j, abs( segments[i].bottom - segments[i].top ) + 1 )
            {   points[j].x = segments[i].left;
                points[j].y = segments[i].top + j;
            }
            E_wnd_Q_window_I_draw_Z_points( window, abs( segments[i].bottom - segments[i].top ) + 1, points );
            W(points);
        }else if( segments[i].top == segments[i].bottom )
        {   POINT *Mt_( points, abs( segments[i].right - segments[i].left ) + 1 );
            if( !points )
                return ~0;
            for_n( j, abs( segments[i].right - segments[i].left ) + 1 )
            {   points[j].x = segments[i].left + j;
                points[j].y = segments[i].top;
            }
            E_wnd_Q_window_I_draw_Z_points( window, abs( segments[i].right - segments[i].left ) + 1, points );
            W(points);
        }else
            if( abs( segments[i].bottom - segments[i].top ) < abs( segments[i].right - segments[i].left ))
                if( segments[i].left > segments[i].right )
                {   if( !~E_wnd_Q_window_I_draw_Z_segments_Z_low( window
                    , (RECT){ segments[i].right, segments[i].bottom, segments[i].left, segments[i].top }))
                        return ~0;
                }else
                {   if( !~E_wnd_Q_window_I_draw_Z_segments_Z_low( window
                    , (RECT){ segments[i].left, segments[i].top, segments[i].right, segments[i].bottom }))
                        return ~0;
                }
            else
                if( segments[i].top > segments[i].bottom )
                {   if( !~E_wnd_Q_window_I_draw_Z_segments_Z_high( window
                    , (RECT){ segments[i].right, segments[i].bottom, segments[i].left, segments[i].top }))
                        return ~0;
                }else
                {   if( !~E_wnd_Q_window_I_draw_Z_segments_Z_high( window
                    , (RECT){ segments[i].left, segments[i].top, segments[i].right, segments[i].bottom }))
                        return ~0;
                }
    return 0;
}
N
E_wnd_Q_window_I_draw_Z_lines(
  struct E_wnd_Q_window_Z *window
, N32 n
, POINT *points
){  RECT *Mt_( segments, n - 1 );
    if( !segments )
        return ~0;
    for_n( i, n - 1 )
        segments[i] = (RECT)
        { points[i].x
        , points[i].y
        , points[ i + 1 ].x
        , points[ i + 1 ].y
        };
    if( !~E_wnd_Q_window_I_draw_Z_segments( window
    , n - 1
    , segments
    ))
    {   W(segments);
        return ~0;
    }
    W(segments);
    return 0;
}
N
E_wnd_Q_window_I_draw_Z_rectangles(
  struct E_wnd_Q_window_Z *window
, N32 n
, RECT *rectangles
){  RECT *Mt_( segments, n * 4 );
    if( !segments )
        return ~0;
    for_n( i, n )
    {   segments[ 4 * i ] = (RECT)
        { rectangles[i].left
        , rectangles[i].top
        , rectangles[i].left + rectangles[i].right - 1 - ( rectangles[i].right ? 1 : 0 )
        , rectangles[i].top
        };
        segments[ 4 * i + 1 ] = (RECT)
        { rectangles[i].left + rectangles[i].right - 1
        , rectangles[i].top
        , rectangles[i].left + rectangles[i].right - 1
        , rectangles[i].top + rectangles[i].bottom - 1 - ( rectangles[i].bottom ? 1 : 0 )
        };
        segments[ 4 * i + 2 ] = (RECT)
        { rectangles[i].left + ( rectangles[i].right ? 1 : 0 )
        , rectangles[i].top + rectangles[i].bottom - 1
        , rectangles[i].left + rectangles[i].right - 1
        , rectangles[i].top + rectangles[i].bottom - 1
        };
        segments[ 4 * i + 3 ] = (RECT)
        { rectangles[i].left
        , rectangles[i].top + ( rectangles[i].bottom ? 1 : 0 )
        , rectangles[i].left
        , rectangles[i].top + rectangles[i].bottom - 1
        };
    }
    if( !~E_wnd_Q_window_I_draw_Z_segments( window
    , n * 4
    , segments
    ))
    {   W(segments);
        return ~0;
    }
    W(segments);
    return 0;
}
//void
//E_wnd_Q_window_I_draw_Z_arcs(
//  struct E_wnd_Q_window_Z *window
//, N32 n
//, xcb_arc_t *arcs
//){  //TODO
//
//}
void
E_wnd_Q_window_I_fill_Z_points(
  struct E_wnd_Q_window_Z *window
, N32 n
, POINT *points
){  //TODO

}
N
E_wnd_Q_window_I_fill_Z_rectangles(
  struct E_wnd_Q_window_Z *window
, N32 n
, RECT *rectangles
){  for_n( i, n )
    {   RECT *Mt_( segments, rectangles[i].bottom );
        for_n( j, rectangles[i].bottom )
            segments[j] = (RECT)
            { rectangles[i].left
            , rectangles[i].top + j
            , rectangles[i].left + rectangles[i].right - 1
            , rectangles[i].top + j
            };
        if( !~E_wnd_Q_window_I_draw_Z_segments( window, rectangles[i].bottom, segments ))
        {   W(segments);
            return ~0;
        }
        W(segments);
    }
    return 0;
}
//void
//E_wnd_Q_window_I_fill_Z_arcs(
//  struct E_wnd_Q_window_Z *window
//, N32 n
//, xcb_arc_t *arcs
//){  //TODO
//
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
F
E_wnd_I_pole_wielokata(
  N n
, struct E_wnd_Z_points *points
){  F pole = 0;
    for_n( i, n - 1 )
        pole += points[i].x * points[ i + 1 ].y - points[ i + 1 ].x * points[i].y;
    pole += points[ n - 1 ].x * points[0].y - points[0].x * points[ n - 1 ].y;
    return 0.5 * fabs(pole);
}
void
E_wnd_Q_window_I_draw_aa_Z_pixel(
  struct E_wnd_Q_window_Z *window
, S16 x
, S16 y
, N32 color
, F brightness
, N get_pixel
){  N background_red, background_green, background_blue;
    N n = 0;
    if( !U_R( E_wnd_S_state, draw_object_drag_move ))
    {   N p[8];
        p[0] = ( get_pixel & Z_aa_pixel_S_e ) && x + 1 < window->width ? GetPixel( window->drawable_dc, x + 1, y ) : color;
        p[1] = ( get_pixel & Z_aa_pixel_S_se ) && x + 1 < window->width && y + 1 < window->height ? GetPixel( window->drawable_dc, x + 1, y + 1 ) : color;
        p[2] = ( get_pixel & Z_aa_pixel_S_s ) && y + 1 < window->height ? GetPixel( window->drawable_dc, x, y + 1 ) : color;
        p[3] = ( get_pixel & Z_aa_pixel_S_sw ) && x > 0 && y + 1 < window->height ? GetPixel( window->drawable_dc, x - 1, y + 1 ) : color;
        p[4] = ( get_pixel & Z_aa_pixel_S_w ) && x > 0 ? GetPixel( window->drawable_dc, x - 1, y ) : color;
        p[5] = ( get_pixel & Z_aa_pixel_S_nw ) && x > 0 && y > 0 ? GetPixel( window->drawable_dc, x - 1, y - 1 ) : color;
        p[6] = ( get_pixel & Z_aa_pixel_S_n ) && y > 0 ? GetPixel( window->drawable_dc, x, y - 1 ) : color;
        p[7] = ( get_pixel & Z_aa_pixel_S_ne ) && x + 1 < window->width && y > 0 ? GetPixel( window->drawable_dc, x + 1, y - 1 ) : color;
        background_red = background_green = background_blue = 0;
        for_n( i, 8 )
            if( p[i] != color )
            {   background_red += E_wnd_Z_color_R_red( p[i] );
                background_green += E_wnd_Z_color_R_green( p[i] );
                background_blue += E_wnd_Z_color_R_red( p[i] );
                n++;
            }
    }
    if(n)
    {   background_red /= n;
        background_green /= n;
        background_blue /= n;
    }else
    {   background_red = E_wnd_Z_color_R_red( E_wnd_Q_theme.window_bg );
        background_green = E_wnd_Z_color_R_green( E_wnd_Q_theme.window_bg );
        background_blue = E_wnd_Z_color_R_blue( E_wnd_Q_theme.window_bg );
    }
    N red = E_wnd_Z_color_R_red(color);
    N green = E_wnd_Z_color_R_green(color);
    N blue = E_wnd_Z_color_R_blue(color);
    if( red > background_red )
        red = background_red + ( red - background_red ) * brightness;
    else
        red = background_red - ( background_red - red ) * brightness;
    if( green > background_green )
        green = background_green + ( green - background_green ) * brightness;
    else
        green = background_green - ( background_green - green ) * brightness;
    if( blue > background_blue )
        blue = background_blue + ( blue - background_blue ) * brightness;
    else
        blue = background_blue - ( background_blue - blue ) * brightness;
    E_wnd_Q_window_I_draw_P_color( E_wnd_Z_color_M( red, green, blue ));
    E_wnd_Q_window_I_draw_Z_points( window
    , 1
    , ( POINT[] )
      { x, y
      }
    );
}
N
E_wnd_Q_window_I_draw_aa_Z_lines(
  struct E_wnd_Q_window_Z *window
, N n
, POINT *points
, F thickness
, N32 color
){  if( n < 2 )
        return ~0;
    F a = window->pixel_width;
    F b = window->pixel_height;
    F pole_pixela = a * b;
    for_n( i, n - 1 )
    {   F alfa = atan( (F)( points[ i + 1 ].y - points[i].y ) / ( points[ i + 1 ].x - points[i].x ));
        if( points[ i + 1 ].x > points[i].x )
        {   if( points[ i + 1 ].y < points[i].y )
                alfa += M_PI_2;
            else if( points[i].y == points[ i + 1 ].y )
            {   RECT rectangle[1];
                rectangle[0].left = points[i].x;
                rectangle[0].top = points[i].y - (S16)( 0.5 * thickness / b );
                rectangle[0].right = points[ i + 1 ].x - points[i].x + 1;
                rectangle[0].bottom = (N16)( thickness / b );
                F pole = fmod( 0.5 * thickness, b );
                if(pole)
                {   pole *= a;
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left, rectangle[0].top - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_nw | Z_aa_pixel_S_n
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right - 1, rectangle[0].top - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_n | Z_aa_pixel_S_ne | Z_aa_pixel_S_e
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left, rectangle[0].top + rectangle[0].bottom
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_se | Z_aa_pixel_S_s
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right - 1, rectangle[0].top + rectangle[0].bottom
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_s | Z_aa_pixel_S_se | Z_aa_pixel_S_e
                    );
                    if( points[i].x + 1 < points[ i + 1 ].x )
                        for( S16 x = points[i].x + 1; x != points[ i + 1 ].x; x++ )
                        {   E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , x, rectangle[0].top - 1
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_n
                            );
                            E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , x, rectangle[0].top + rectangle[0].bottom
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_s
                            );
                        }
                }
                if( rectangle[0].bottom )
                {   E_wnd_Q_window_I_draw_P_color(color);
                    E_wnd_Q_window_I_fill_Z_rectangles( window, 1, rectangle );
//                    if(i)
//                    {   xcb_arc_t arcs[2] =
//                        { { points[i].x - rectangle[0].height / 2, points[i].y - rectangle[0].height / 2
//                          , rectangle[0].height, rectangle[0].height
//                          , 0, 24000
//                          }
//                        , { points[ i + 1 ].x - rectangle[0].height / 2, points[ i + 1 ].y - rectangle[0].height / 2
//                          , rectangle[0].height, rectangle[0].height
//                          , 0, 24000
//                          }
//                        };
//                        E_wnd_Q_window_I_fill_Z_arcs_(arcs);
//                    }
                }
                continue;
            }
        }else if( points[ i + 1 ].x < points[i].x )
        {   if( points[ i + 1 ].y > points[i].y )
                alfa += M_PI_2;
            else if( points[i].y == points[ i + 1 ].y )
            {   RECT rectangle[1];
                rectangle[0].left = points[ i + 1 ].x;
                rectangle[0].top = points[i].y - (S16)( 0.5 * thickness / b );
                rectangle[0].right = points[i].x - points[ i + 1 ].x + 1;
                rectangle[0].bottom = (N16)( thickness / b );
                F pole = fmod( 0.5 * thickness, b );
                if(pole)
                {   pole *= a;
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left, rectangle[0].top - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_nw | Z_aa_pixel_S_n
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right - 1, rectangle[0].top - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_n | Z_aa_pixel_S_ne | Z_aa_pixel_S_e
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left, rectangle[0].top + rectangle[0].bottom
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_sw | Z_aa_pixel_S_s
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right - 1, rectangle[0].top + rectangle[0].bottom
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_s | Z_aa_pixel_S_se | Z_aa_pixel_S_e
                    );
                    if( points[ i + 1 ].x + 1 < points[i].x )
                        for( S16 x = points[ i + 1 ].x + 1; x != points[i].x; x++ )
                        {   E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , x, rectangle[0].top - 1
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_n
                            );
                            E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , x, rectangle[0].top + rectangle[0].bottom
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_s
                            );
                        }
                }
                if( rectangle[0].bottom )
                {   E_wnd_Q_window_I_draw_P_color(color);
                    E_wnd_Q_window_I_fill_Z_rectangles( window, 1, rectangle );
//                    if(i)
//                    {   xcb_arc_t arcs[2] =
//                        { { points[i].x - rectangle[0].height / 2, points[i].y - rectangle[0].height / 2
//                          , rectangle[0].height, rectangle[0].height
//                          , 0, 24000
//                          }
//                        , { points[ i + 1 ].x - rectangle[0].height / 2, points[ i + 1 ].y - rectangle[0].height / 2
//                          , rectangle[0].height, rectangle[0].height
//                          , 0, 24000
//                          }
//                        };
//                        E_wnd_Q_window_I_fill_Z_arcs_(arcs);
//                    }
                }
                continue;
            }
        }else
        {   if( points[ i + 1 ].y > points[i].y )
            {   RECT rectangle[1];
                rectangle[0].left = points[i].x - (S16)( 0.5 * thickness / a );
                rectangle[0].top = points[i].y;
                rectangle[0].right = (N16)( thickness / a );
                rectangle[0].bottom = points[ i + 1 ].y - points[i].y + 1;
                F pole = fmod( 0.5 * thickness, a );
                if(pole)
                {   pole *= b;
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left - 1, rectangle[0].top
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_nw | Z_aa_pixel_S_n
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right, rectangle[0].top
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_n | Z_aa_pixel_S_ne | Z_aa_pixel_S_e
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left - 1, rectangle[0].top + rectangle[0].bottom - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_sw | Z_aa_pixel_S_s
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right, rectangle[0].top + rectangle[0].bottom - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_s | Z_aa_pixel_S_se | Z_aa_pixel_S_e
                    );
                    if( points[i].y + 1 < points[ i + 1 ].y )
                        for( S16 y = points[i].y + 1; y != points[ i + 1 ].y; y++ )
                        {   E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , rectangle[0].left - 1, y
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_w
                            );
                            E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , rectangle[0].left + rectangle[0].right, y
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_e
                            );
                        }
                }
                if( rectangle[0].right )
                {   E_wnd_Q_window_I_draw_P_color(color);
                    E_wnd_Q_window_I_fill_Z_rectangles( window, 1, rectangle );
//                    if(i)
//                    {   xcb_arc_t arcs[2] =
//                        { { points[i].x - rectangle[0].width / 2, points[i].y - rectangle[0].width / 2
//                          , rectangle[0].width, rectangle[0].width
//                          , 0, 24000
//                          }
//                        , { points[ i + 1 ].x - rectangle[0].width / 2, points[ i + 1 ].y - rectangle[0].width / 2
//                          , rectangle[0].width, rectangle[0].width
//                          , 0, 24000
//                          }
//                        };
//                        E_wnd_Q_window_I_fill_Z_arcs_(arcs);
//                    }
                }
            }else if( points[ i + 1 ].y < points[i].y )
            {   RECT rectangle[1];
                rectangle[0].left = points[i].x - (S16)( 0.5 * thickness / a );
                rectangle[0].top = points[ i + 1 ].y;
                rectangle[0].right = (N16)( thickness / a );
                rectangle[0].bottom = points[i].y - points[ i + 1 ].y + 1;
                F pole = fmod( 0.5 * thickness, a );
                if(pole)
                {   pole *= b;
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left - 1, rectangle[0].top
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_nw | Z_aa_pixel_S_n
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right, rectangle[0].top
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_n | Z_aa_pixel_S_ne | Z_aa_pixel_S_e
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left - 1, rectangle[0].top + rectangle[0].bottom - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_w | Z_aa_pixel_S_sw | Z_aa_pixel_S_s
                    );
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , rectangle[0].left + rectangle[0].right, rectangle[0].top + rectangle[0].bottom - 1
                    , color
                    , pole / pole_pixela
                    , Z_aa_pixel_S_s | Z_aa_pixel_S_se | Z_aa_pixel_S_e
                    );
                    if( points[ i + 1 ].y + 1 < points[i].y )
                        for( S16 y = points[ i + 1 ].y + 1; y != points[i].y; y++ )
                        {   E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , rectangle[0].left - 1, y
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_w
                            );
                            E_wnd_Q_window_I_draw_aa_Z_pixel( window
                            , rectangle[0].left + rectangle[0].right, y
                            , color
                            , pole / pole_pixela
                            , Z_aa_pixel_S_e
                            );
                        }
                }
                if( rectangle[0].right )
                {   E_wnd_Q_window_I_draw_P_color(color);
                    E_wnd_Q_window_I_fill_Z_rectangles( window, 1, rectangle );
//                    if(i)
//                    {   xcb_arc_t arcs[2] =
//                        { { points[i].x - rectangle[0].width / 2, points[i].y - rectangle[0].width / 2
//                          , rectangle[0].width, rectangle[0].width
//                          , 0, 24000
//                          }
//                        , { points[ i + 1 ].x - rectangle[0].width / 2, points[ i + 1 ].y - rectangle[0].width / 2
//                          , rectangle[0].width, rectangle[0].width
//                          , 0, 24000
//                          }
//                        };
//                        E_wnd_Q_window_I_fill_Z_arcs_(arcs);
//                    }
                }
            }
            continue;
        }
        F sin_alfa, cos_alfa, tan_alfa;
        S16 dx_direction, dy_direction;
        F pixel_dx, pixel_dy;
        B prawoskretny;
        struct
        { S16 dx, dy;
        } *Mt_( dx_dy, 0 );
        if( !dx_dy )
            return ~0;
        N dx_dy_n = 0;
        for_n( j, 6 )
        {   F length;
            S16 x, y;
            B U_R( first_pixel, overdrawn );
            switch(j)
            { case 0:
                  U_F( first_pixel, overdrawn );
                  prawoskretny = no;
                  alfa = M_PI_2 - alfa;
                  sin_alfa = sin(alfa);
                  cos_alfa = cos(alfa);
                  tan_alfa = tan(alfa);
                  length = 0.5 * thickness;
                  x = points[i].x;
                  y = points[i].y;
                  if( points[ i + 1 ].x > points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = -1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = -1;
                      }
                  else if( points[ i + 1 ].x < points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = 1;
                      }
                  pixel_dx = 0.5 * a;
                  pixel_dy = 0.5 * b;
                  break;
              case 1:
                  U_F( first_pixel, overdrawn );
                  length = hypot(( points[ i + 1 ].x - points[i].x + 1 ) * a, ( points[ i + 1 ].y - points[i].y + 1 ) * b );
                  if( points[ i + 1 ].x > points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = 1;
                          dy_direction = -1;
                      }
                  else if( points[ i + 1 ].x < points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = -1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = -1;
                      }
                  break;
              case 2:
                  U_F( first_pixel, overdrawn );
                  prawoskretny = yes;
                  alfa = M_PI_2 - alfa;
                  sin_alfa = sin(alfa);
                  cos_alfa = cos(alfa);
                  tan_alfa = tan(alfa);
                  length = 0.5 * thickness;
                  x = points[ i + 1 ].x;
                  y = points[ i + 1 ].y;
                  if( points[ i + 1 ].x > points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = -1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = -1;
                      }
                  else if( points[ i + 1 ].x < points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = 1;
                      }
                  pixel_dx = 0.5 * a;
                  pixel_dy = 0.5 * b;
                  break;
              case 3:
                  U_L( first_pixel, overdrawn );
                  prawoskretny = no;
                  alfa = M_PI_2 - alfa;
                  sin_alfa = sin(alfa);
                  cos_alfa = cos(alfa);
                  tan_alfa = tan(alfa);
                  length = 0.5 * thickness;
                  x = points[ i + 1 ].x;
                  y = points[ i + 1 ].y;
                  dx_direction = -dx_direction;
                  dy_direction = -dy_direction;
                  pixel_dx = 0.5 * a;
                  pixel_dy = 0.5 * b;
                  break;
              case 4:
                  U_L( first_pixel, overdrawn );
                  prawoskretny = yes;
                  alfa = M_PI_2 - alfa;
                  sin_alfa = sin(alfa);
                  cos_alfa = cos(alfa);
                  tan_alfa = tan(alfa);
                  length = 0.5 * thickness;
                  x = points[i].x;
                  y = points[i].y;
                  pixel_dx = 0.5 * a;
                  pixel_dy = 0.5 * b;
                  break;
              case 5:
                  U_F( first_pixel, overdrawn );
                  length = hypot(( points[ i + 1 ].x - points[i].x + 1 ) * a, ( points[ i + 1 ].y - points[i].y + 1 ) * b );
                  if( points[ i + 1 ].x > points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = 1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = 1;
                          dy_direction = -1;
                      }
                  else if( points[ i + 1 ].x < points[i].x )
                      if( points[ i + 1 ].y > points[i].y )
                      {   dx_direction = -1;
                          dy_direction = 1;
                      }else
                      {   dx_direction = -1;
                          dy_direction = -1;
                      }
                  break;
            }
            B wariant_0 = ( prawoskretny && (( dx_direction > 0 && dy_direction > 0 ) || ( dx_direction < 0 && dy_direction < 0 )))
                || ( !prawoskretny && (( dx_direction > 0 && dy_direction < 0 ) || ( dx_direction < 0 && dy_direction > 0 )));
            if( !wariant_0 )
            {   J_swap( F, a, b );
                J_swap( F, pixel_dx, pixel_dy );
            }
            S16 dx, dy;
            B U_F( first_pixel, computed );
            while( length > 0 )
            {   F alfa_przekatnej = atan(( b - pixel_dy ) / ( a - pixel_dx ));
                S16 prev_dx, prev_dy;
                if( !U_R( first_pixel, computed ))
                {   prev_dx = dx;
                    prev_dy = dy;
                }else
                {   prev_dx = 0;
                    prev_dy = 0;
                }
                struct E_wnd_Z_points *pixel_points;
                N pixel_points_n;
                if( alfa <= alfa_przekatnej )
                {   if( length >= ( a - pixel_dx ) / cos_alfa )
                    {   Mt_( pixel_points, pixel_points_n = 3 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = a;
                        pixel_points[1].y = pixel_dy + ( a - pixel_dx ) * tan_alfa;
                        pixel_points[2].x = a;
                        pixel_points[2].y = pixel_dy;
                    }else if( length <= ( a - pixel_dx ) * cos_alfa )
                    {   Mt_( pixel_points, pixel_points_n = 3 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + length * cos_alfa;
                        pixel_points[1].y = pixel_dy + length * sin_alfa;
                        pixel_points[2].x = pixel_dx + length / cos_alfa;
                        pixel_points[2].y = pixel_dy;
                    }else
                    {   Mt_( pixel_points, pixel_points_n = 4 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + length * cos_alfa;
                        pixel_points[1].y = pixel_dy + length * sin_alfa;
                        pixel_points[2].x = a;
                        pixel_points[2].y = pixel_dy + ( length / cos_alfa - ( a - pixel_dx )) / tan_alfa;
                        pixel_points[3].x = a;
                        pixel_points[3].y = pixel_dy;
                    }
                    length -= ( a - pixel_dx ) / cos_alfa;
                    if( wariant_0 )
                    {   dx = dx_direction;
                        dy = alfa == alfa_przekatnej ? dy_direction : 0;
                    }else
                    {   dx = alfa == alfa_przekatnej ? dx_direction : 0;
                        dy = dy_direction;
                    }
                }else
                {   if( length >= ( b - pixel_dy ) / sin_alfa + ( a - pixel_dx - ( b - pixel_dy ) / tan_alfa ) * cos_alfa )
                    {   Mt_( pixel_points, pixel_points_n = 4 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + ( b - pixel_dy ) / tan_alfa;
                        pixel_points[1].y = b;
                        pixel_points[2].x = a;
                        pixel_points[2].y = b;
                        pixel_points[3].x = a;
                        pixel_points[3].y = pixel_dy;
                    }else if( length > ( b - pixel_dy ) / sin_alfa )
                    {   Mt_( pixel_points, pixel_points_n = 5 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + ( b - pixel_dy ) / tan_alfa;
                        pixel_points[1].y = b;
                        pixel_points[2].x = pixel_dx + ( b - pixel_dy ) / tan_alfa + ( length - ( b - pixel_dy ) / sin_alfa ) / cos_alfa;
                        pixel_points[2].y = b;
                        pixel_points[3].x = a;
                        pixel_points[3].y = b - ( a - ( pixel_dx + ( b - pixel_dy ) / tan_alfa + ( length - ( b - pixel_dy ) / sin_alfa ) / cos_alfa )) / tan_alfa;
                        if( pixel_points[3].y <= pixel_dy )
                        {   pixel_points[3].x = a;
                            if( pixel_points[3].y < pixel_dy )
                                pixel_points[3].x -= ( pixel_dy - pixel_points[3].y ) * tan_alfa;
                            pixel_points[3].y = pixel_dy;
                            pixel_points_n--;
                        }else
                        {   pixel_points[4].x = a;
                            pixel_points[4].y = pixel_dy;
                        }
                    }else if( length <= ( a - pixel_dx ) * cos_alfa )
                    {   Mt_( pixel_points, pixel_points_n = 3 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + length * cos_alfa;
                        pixel_points[1].y = pixel_dy + length * sin_alfa;
                        pixel_points[2].x = pixel_dx + length / cos_alfa;
                        pixel_points[2].y = pixel_dy;
                    }else
                    {   Mt_( pixel_points, pixel_points_n = 4 );
                        if( !pixel_points )
                        {   W( dx_dy );
                            return ~0;
                        }
                        pixel_points[1].x = pixel_dx + length * cos_alfa;
                        pixel_points[1].y = pixel_dy + length * sin_alfa;
                        pixel_points[2].x = a;
                        pixel_points[2].y = pixel_dy + ( pixel_dx + length / cos_alfa - a ) / tan_alfa;
                        pixel_points[3].x = a;
                        pixel_points[3].y = pixel_dy;
                    }
                    length -= ( b - pixel_dy ) / sin_alfa;
                    if( wariant_0 )
                    {   dx = 0;
                        dy = dy_direction;
                    }else
                    {   dx = dx_direction;
                        dy = 0;
                    }
                }
                pixel_points[0].x = pixel_dx;
                pixel_points[0].y = pixel_dy;
                F pole = 0;
                if( !pixel_dx && pixel_dy )
                    pole = pixel_dy * a;
                if( alfa <= alfa_przekatnej )
                {   pixel_dy = alfa == alfa_przekatnej ? 0 : pixel_dy + ( a - pixel_dx ) * tan_alfa;
                    if( pixel_dy >= b )
                        pixel_dy = 0;
                    pixel_dx = 0;
                }else
                {   pixel_dx += ( b - pixel_dy ) / tan_alfa;
                    if( pixel_dx >= a )
                        pixel_dx = 0;
                    pixel_dy = 0;
                }
                if( !wariant_0 )
                {   for_n( i, pixel_points_n )
                        J_swap( F, pixel_points[i].x, pixel_points[i].y );
                }
                pole += E_wnd_I_pole_wielokata( pixel_points_n, pixel_points );
                W( pixel_points );
                if( U_R( first_pixel, computed )
                && ( j == 3 || j == 4 )
                )
                    pole *= 2;
                if( j == 0 )
                {   if( !E_mem_Q_blk_I_append( &dx_dy, 1 ))
                        return ~0;
                    dx_dy[ dx_dy_n ].dx = dx;
                    dx_dy[ dx_dy_n ].dy = dy;
                    dx_dy_n++;
                }else if( j == 4 )
                {   if( !U_R( first_pixel, computed ))
                    {   if( !E_mem_Q_blk_I_append( &dx_dy, 1 ))
                            return ~0;
                        dx_dy[ dx_dy_n ].dx = dx;
                        dx_dy[ dx_dy_n ].dy = dy;
                        dx_dy_n++;
                    }
                }else if( j == 1 || j == 5 )
                {   if( !U_R( first_pixel, computed )
                    && length > 0
                    ){  E_wnd_Q_window_I_draw_P_color(color);
                        S16 x_ = x, y_ = y;
                        for_n_rev( i, dx_dy_n )
                        {   x_ -= dx_dy[i].dx;
                            y_ -= dx_dy[i].dy;
                            if( i == dx_dy_n - 1
                            && (( dx_dy[i].dx && prev_dx  )
                              || ( dx_dy[i].dy && prev_dy )
                            ))
                                continue;
                            POINT point = { x_, y_ };
                            E_wnd_Q_window_I_draw_Z_points( window, 1, &point );
                        }
                    }
                }else if( j == 2 )
                {   E_mem_Q_blk_I_rem( &dx_dy, 0, dx_dy_n );
                    dx_dy_n = 0;
                }
                if( !U_R( first_pixel, overdrawn ))
                {   N get_pixel;
//                    if( U_R( screen->mode, animation ))
                        if( dx_direction > 0 && dy_direction > 0 )
                        {   get_pixel = prawoskretny ? Z_aa_pixel_S_sw : Z_aa_pixel_S_ne;
                            if( prawoskretny && prev_dy )
                                get_pixel |= Z_aa_pixel_S_nw | Z_aa_pixel_S_w;
                            if( !prawoskretny && prev_dx )
                                get_pixel |= Z_aa_pixel_S_nw | Z_aa_pixel_S_n;
                            if( prawoskretny && !dy )
                                get_pixel |= Z_aa_pixel_S_s;
                            if( !prawoskretny && !dx )
                                get_pixel |= Z_aa_pixel_S_e;
                        }else if( dx_direction > 0 && dy_direction < 0 )
                        {   get_pixel = prawoskretny ? Z_aa_pixel_S_se : Z_aa_pixel_S_nw;
                            if( prawoskretny && prev_dx )
                                get_pixel |= Z_aa_pixel_S_sw | Z_aa_pixel_S_s;
                            if( !prawoskretny && prev_dy )
                                get_pixel |= Z_aa_pixel_S_sw | Z_aa_pixel_S_w;
                            if( prawoskretny && !dx )
                                get_pixel |= Z_aa_pixel_S_s;
                            if( !prawoskretny && !dy )
                                get_pixel |= Z_aa_pixel_S_w;
                        }else if( dx_direction < 0 && dy_direction > 0 )
                        {   get_pixel = prawoskretny ? Z_aa_pixel_S_nw : Z_aa_pixel_S_se;
                            if( prawoskretny && prev_dx )
                                get_pixel |= Z_aa_pixel_S_ne | Z_aa_pixel_S_n;
                            if( !prawoskretny && prev_dy )
                                get_pixel |= Z_aa_pixel_S_ne | Z_aa_pixel_S_e;
                            if( prawoskretny && !dx )
                                get_pixel |= Z_aa_pixel_S_e;
                            if( !prawoskretny && !dy )
                                get_pixel |= Z_aa_pixel_S_s;
                        }else /// if( dx_direction < 0 && dy_direction < 0 )
                        {   get_pixel = prawoskretny ? Z_aa_pixel_S_ne : Z_aa_pixel_S_sw;
                            if( prawoskretny && prev_dy )
                                get_pixel |= Z_aa_pixel_S_se | Z_aa_pixel_S_e;
                            if( !prawoskretny && prev_dx )
                                get_pixel |= Z_aa_pixel_S_se | Z_aa_pixel_S_s;
                            if( prawoskretny && !dy )
                                get_pixel |= Z_aa_pixel_S_n;
                            if( !prawoskretny && !dx )
                                get_pixel |= Z_aa_pixel_S_w;
                        }
//                    else
//                        get_pixel = 0;
                    E_wnd_Q_window_I_draw_aa_Z_pixel( window
                    , x, y
                    , color
                    , pole / pole_pixela
                    , get_pixel
                    );
                }
                U_L( first_pixel, overdrawn );
                U_L( first_pixel, computed );
                x += dx;
                y += dy;
            }
            if( j != 5 && !wariant_0 )
            {   J_swap( F, a, b );
                J_swap( F, pixel_dx, pixel_dy );
            }
        }
        W( dx_dy );
//        if( i && dx_dy_n )
//        {   xcb_arc_t arcs[1] =
//            { points[i].x - dx_dy_n, points[i].y - dx_dy_n
//            , dx_dy_n * 2, dx_dy_n * 2
//            , 0, 24000
//            };
//            E_wnd_Q_window_I_draw_P_color(color);
//            E_wnd_Q_window_I_fill_Z_arcs_(arcs);
//        }
    }
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_wnd_Q_object_I_draw_P_color(
  struct E_wnd_Q_object_Z *object
, N32 color
){  if( !U_R( object->mode, drag_src ))
        E_wnd_Q_window_I_draw_P_color(color);
}
//------------------------------------------------------------------------------
void
E_wnd_Q_object_I_draw_Z_points(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, POINT *points
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_wnd_Q_window_I_draw_Z_points( window, n, points );
}
void
E_wnd_Q_object_I_draw_Z_segments(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, RECT *segments
){  for_n( i, n )
    {   segments[i].left += object->x;
        segments[i].top += object->y;
        segments[i].right += object->x;
        segments[i].bottom += object->y;
    }
    E_wnd_Q_window_I_draw_Z_segments( window, n, segments );
}
void
E_wnd_Q_object_I_draw_Z_lines(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, POINT *points
){  for_n( i, n )
        points[i].y += object->y;
    {   points[i].x += object->x;
    }
    E_wnd_Q_window_I_draw_Z_lines( window, n, points );
}
void
E_wnd_Q_object_I_draw_Z_rectangles(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, RECT *rectangles
){  for_n( i, n )
    {   rectangles[i].left += object->x;
        rectangles[i].top += object->y;
    }
    E_wnd_Q_window_I_draw_Z_rectangles( window, n, rectangles );
}
//void
//E_wnd_Q_object_I_draw_Z_arcs(
//  struct E_wnd_Q_window_Z *window
//, struct E_wnd_Q_object_Z *object
//, N32 n
//, xcb_arc_t *arcs
//){  for_n( i, n )
//    {   arcs[i].x += object->x;
//        arcs[i].y += object->y;
//    }
//    E_wnd_Q_window_I_draw_Z_arcs( window, n, arcs );
//}
void
E_wnd_Q_object_I_fill_Z_points(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, POINT *points
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_wnd_Q_window_I_fill_Z_points( window, n, points );
}
void
E_wnd_Q_object_I_fill_Z_rectangles(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N32 n
, RECT *rectangles
){  for_n( i, n )
    {   rectangles[i].left += object->x;
        rectangles[i].top += object->y;
    }
    E_wnd_Q_window_I_fill_Z_rectangles( window, n, rectangles );
}
//void
//E_wnd_Q_object_I_fill_Z_arcs(
//  struct E_wnd_Q_window_Z *window
//, struct E_wnd_Q_object_Z *object
//, N32 n
//, xcb_arc_t *arcs
//){  for_n( i, n )
//    {   arcs[i].x += object->x;
//        arcs[i].y += object->y;
//    }
//    E_wnd_Q_window_I_fill_Z_arcs( window, n, arcs );
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_wnd_Q_object_I_draw_aa_Z_pixel(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, S16 x
, S16 y
, N32 color
, F brightness
, N get_pixel
){  E_wnd_Q_window_I_draw_aa_Z_pixel( window
    , object->x + x
    , object->y + y
    , !U_R( object->mode, drag_src ) ? color : E_wnd_Q_theme.current_brace
    , brightness
    , get_pixel
    );
}
void
E_wnd_Q_object_I_draw_aa_Z_lines(
  struct E_wnd_Q_window_Z *window
, struct E_wnd_Q_object_Z *object
, N n
, POINT *points
, N32 color
, F thickness
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_wnd_Q_window_I_draw_aa_Z_lines( window
    , n
    , points
    , thickness
    , !U_R( object->mode, drag_src ) ? color : E_wnd_Q_theme.current_brace
    );
}

