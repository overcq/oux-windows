



















N32
E_x_Z_color_M(
  N8 red
, N8 green
, N8 blue
){  return ( red << 16 ) | ( green << 8 ) | blue;
}
N8
E_x_Z_color_R_red( N32 color
){  J_assert( !( color & ~0xffffff ));
    return ( color >> 16 ) & 0xff;
}
N8
E_x_Z_color_R_green( N32 color
){  J_assert( !( color & ~0xffffff ));
    return ( color >> 8 ) & 0xff;
}
N8
E_x_Z_color_R_blue( N32 color
){  J_assert( !( color & ~0xffffff ));
    return color & 0xff;
}
N32
E_x_Z_color_M_gray( N8 luminance
){  return E_x_Z_color_M( luminance, luminance, luminance );
}
N32
E_x_Z_color_P_luminance( struct E_x_Q_display_Z *display
, N32 color
, F luminance
){  J_assert( !( color & ~0xffffff ));
    J_assert( luminance >= 0 && luminance <= 1 );
    N8 red = E_x_Z_color_R_red(color);
    N8 green = E_x_Z_color_R_green(color);
    N8 blue = E_x_Z_color_R_blue(color);
    F color_luminance = E_x_Z_color_R_luminance( display, color );
    if( luminance < color_luminance )
    {   red = lround( red * luminance / color_luminance );
        green = lround( green * luminance / color_luminance );
        blue = lround( blue * luminance / color_luminance );
    }else if( luminance > color_luminance )
    {   red += lround(( 0xff - red ) * ( luminance - color_luminance ) / ( 1 - color_luminance ));
        green += lround(( 0xff - green ) * ( luminance - color_luminance ) / ( 1 - color_luminance ));
        blue += lround(( 0xff - blue ) * ( luminance - color_luminance ) / ( 1 - color_luminance ));
    }else
        return color;
    return E_x_Z_color_M( red, green, blue );
}
F
E_x_Z_color_R_luminance( struct E_x_Q_display_Z *display
, N32 color
){  return ( display->red_luminance_ratio * E_x_Z_color_R_red(color) + display->green_luminance_ratio * E_x_Z_color_R_green(color) + display->blue_luminance_ratio * E_x_Z_color_R_blue(color) ) / 255;
}

void
E_x_Q_window_I_draw_P_color(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, N32 color
){  J_assert( !( color & ~0xffffff ));
    if( screen->draw_color != color )
        xcb_change_gc( display->x_display
        , screen->drawable_gc
        , XCB_GC_FOREGROUND
        , ( N32[] )
          { screen->draw_color = color
          }
        );
}

void
E_x_Q_window_I_draw_Z_points(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_point_t *points
){  J_assert(n);
    xcb_poly_point( display->x_display
    , XCB_COORD_MODE_ORIGIN
    , window->drawable
    , screen->drawable_gc
    , n
    , points
    );
    xcb_poly_point( display->x_display
    , XCB_COORD_MODE_ORIGIN
    , window->drawable_mask
    , screen->bitmask_1_gc
    , n
    , points
    );
    xcb_poly_point( display->x_display
    , XCB_COORD_MODE_ORIGIN
    , window->object_mask
    , screen->object_mask_gc
    , n
    , points
    );
}
void
E_x_Q_window_I_draw_Z_segments(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_segment_t *segments
){  J_assert(n);
    xcb_poly_segment( display->x_display
    , window->drawable
    , screen->drawable_gc
    , n
    , segments
    );
    xcb_poly_segment( display->x_display
    , window->drawable_mask
    , screen->bitmask_1_gc
    , n
    , segments
    );
    xcb_poly_segment( display->x_display
    , window->object_mask
    , screen->object_mask_gc
    , n
    , segments
    );
}
N
E_x_Q_window_I_draw_Z_lines(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_point_t *points
){  J_assert( n > 1 );
    xcb_segment_t *Mt_( segments, n - 1 );
    if( !segments )
        return ~0;
    for_n( i, n - 1 )
        segments[i] = ( xcb_segment_t )
        { .x1 = points[i].x
        , .y1 = points[i].y
        , .x2 = points[ i + 1 ].x
        , .y2 = points[ i + 1 ].y
        };
    E_x_Q_window_I_draw_Z_segments( display, screen, window
    , n - 1
    , segments
    );
    W(segments);
    return 0;
}
N
E_x_Q_window_I_draw_Z_rectangles(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_rectangle_t *rectangles
){  J_assert(n);
    xcb_segment_t *Mt_( segments, n * 4 );
    if( !segments )
        return ~0;
    for_n( i, n )
    {   segments[ 4 * i ] = ( xcb_segment_t )
        { .x1 = rectangles[i].x
        , .y1 = rectangles[i].y
        , .x2 = rectangles[i].x + rectangles[i].width - 1 - ( rectangles[i].width ? 1 : 0 )
        , .y2 = rectangles[i].y
        };
        segments[ 4 * i + 1 ] = ( xcb_segment_t )
        { .x1 = rectangles[i].x + rectangles[i].width - 1
        , .y1 = rectangles[i].y
        , .x2 = rectangles[i].x + rectangles[i].width - 1
        , .y2 = rectangles[i].y + rectangles[i].height - 1 - ( rectangles[i].height ? 1 : 0 )
        };
        segments[ 4 * i + 2 ] = ( xcb_segment_t )
        { .x1 = rectangles[i].x + ( rectangles[i].width ? 1 : 0 )
        , .y1 = rectangles[i].y + rectangles[i].height - 1
        , .x2 = rectangles[i].x + rectangles[i].width - 1
        , .y2 = rectangles[i].y + rectangles[i].height - 1
        };
        segments[ 4 * i + 3 ] = ( xcb_segment_t )
        { .x1 = rectangles[i].x
        , .y1 = rectangles[i].y + ( rectangles[i].height ? 1 : 0 )
        , .x2 = rectangles[i].x
        , .y2 = rectangles[i].y + rectangles[i].height - 1
        };
    }
    E_x_Q_window_I_draw_Z_segments( display, screen, window
    , n * 4
    , segments
    );
    W(segments);
    return 0;
}
void
E_x_Q_window_I_draw_Z_arcs(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_arc_t *arcs
){  J_assert(n);
    xcb_poly_arc( display->x_display
    , window->drawable
    , screen->drawable_gc
    , n
    , arcs
    );
    xcb_poly_arc( display->x_display
    , window->drawable_mask
    , screen->bitmask_1_gc
    , n
    , arcs
    );
    xcb_poly_arc( display->x_display
    , window->object_mask
    , screen->object_mask_gc
    , n
    , arcs
    );
}
void
E_x_Q_window_I_fill_Z_points(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_point_t *points
){  J_assert( n > 2 );
    xcb_fill_poly( display->x_display
    , window->drawable
    , screen->drawable_gc
    , XCB_POLY_SHAPE_COMPLEX
    , XCB_COORD_MODE_ORIGIN
    , n
    , points
    );
    xcb_fill_poly( display->x_display
    , window->drawable_mask
    , screen->bitmask_1_gc
    , XCB_POLY_SHAPE_COMPLEX
    , XCB_COORD_MODE_ORIGIN
    , n
    , points
    );
    xcb_fill_poly( display->x_display
    , window->object_mask
    , screen->object_mask_gc
    , XCB_POLY_SHAPE_COMPLEX
    , XCB_COORD_MODE_ORIGIN
    , n
    , points
    );
}
void
E_x_Q_window_I_fill_Z_rectangles(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_rectangle_t *rectangles
){  J_assert(n);
    xcb_poly_fill_rectangle( display->x_display
    , window->drawable
    , screen->drawable_gc
    , n
    , rectangles
    );
    xcb_poly_fill_rectangle( display->x_display
    , window->drawable_mask
    , screen->bitmask_1_gc
    , n
    , rectangles
    );
    xcb_poly_fill_rectangle( display->x_display
    , window->object_mask
    , screen->object_mask_gc
    , n
    , rectangles
    );
}
void
E_x_Q_window_I_fill_Z_arcs(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N32 n
, xcb_arc_t *arcs
){  J_assert(n);
    xcb_poly_fill_arc( display->x_display
    , window->drawable
    , screen->drawable_gc
    , n
    , arcs
    );
    xcb_poly_fill_arc( display->x_display
    , window->drawable_mask
    , screen->bitmask_1_gc
    , n
    , arcs
    );
    xcb_poly_fill_arc( display->x_display
    , window->object_mask
    , screen->object_mask_gc
    , n
    , arcs
    );
}

struct E_x_Z_points

;
F
E_x_I_pole_wielokata(
  N n
, struct E_x_Z_points *points
){  J_assert( n > 2 );
    F pole = 0;
    for_n( i, n - 1 )
        pole += points[i].x * points[ i + 1 ].y - points[ i + 1 ].x * points[i].y;
    pole += points[ n - 1 ].x * points[0].y - points[0].x * points[ n - 1 ].y;
    return 0.5 * fabs(pole);
}
void
E_x_Q_window_I_draw_aa_Z_pixel(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, S16 x
, S16 y
, N32 color
, F brightness
, N get_pixel
){  J_assert( !( color & ~0xffffff ));
    J_assert( brightness >= 0 && brightness <= 1 );
    N background_red, background_green, background_blue;
    N n = 0;
    if( !U_R( screen->state, draw_object_drag_move ))
    {   N p[8];
        p[0] = ( get_pixel & E_x_Z_aa_pixel_S_e ) && x + 1 < window->width ? E_x_Q_image_R_pixel( display, window->drawable, x + 1, y ) : color;
        p[1] = ( get_pixel & E_x_Z_aa_pixel_S_se ) && x + 1 < window->width && y + 1 < window->height ? E_x_Q_image_R_pixel( display, window->drawable, x + 1, y + 1 ) : color;
        p[2] = ( get_pixel & E_x_Z_aa_pixel_S_s ) && y + 1 < window->height ? E_x_Q_image_R_pixel( display, window->drawable, x, y + 1 ) : color;
        p[3] = ( get_pixel & E_x_Z_aa_pixel_S_sw ) && x > 0 && y + 1 < window->height ? E_x_Q_image_R_pixel( display, window->drawable, x - 1, y + 1 ) : color;
        p[4] = ( get_pixel & E_x_Z_aa_pixel_S_w ) && x > 0 ? E_x_Q_image_R_pixel( display, window->drawable, x - 1, y ) : color;
        p[5] = ( get_pixel & E_x_Z_aa_pixel_S_nw ) && x > 0 && y > 0 ? E_x_Q_image_R_pixel( display, window->drawable, x - 1, y - 1 ) : color;
        p[6] = ( get_pixel & E_x_Z_aa_pixel_S_n ) && y > 0 ? E_x_Q_image_R_pixel( display, window->drawable, x, y - 1 ) : color;
        p[7] = ( get_pixel & E_x_Z_aa_pixel_S_ne ) && x + 1 < window->width && y > 0 ? E_x_Q_image_R_pixel( display, window->drawable, x + 1, y - 1 ) : color;
        background_red = background_green = background_blue = 0;
        for_n( i, 8 )
            if( p[i] != color )
            {   background_red += E_x_Z_color_R_red( p[i] );
                background_green += E_x_Z_color_R_green( p[i] );
                background_blue += E_x_Z_color_R_blue( p[i] );
                n++;
            }
    }
    if(n)
    {   background_red /= n;
        background_green /= n;
        background_blue /= n;
    }else
    {   background_red = E_x_Z_color_R_red( E_x_Q_theme.window_bg );
        background_green = E_x_Z_color_R_green( E_x_Q_theme.window_bg );
        background_blue = E_x_Z_color_R_blue( E_x_Q_theme.window_bg );
    }
    N red = E_x_Z_color_R_red(color);
    N green = E_x_Z_color_R_green(color);
    N blue = E_x_Z_color_R_blue(color);
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
    E_x_Q_window_I_draw_P_color_( E_x_Z_color_M( red, green, blue ));
    E_x_Q_window_I_draw_Z_points_(
      (( xcb_point_t[] )
      { x, y
      })
    );
}
N
E_x_Q_window_I_draw_aa_Z_lines(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, N n
, xcb_point_t *points
, F thickness
, N32 color
){  J_assert( n > 1 );
    J_assert( !( color & ~0xffffff ));
    F a = screen->pixel_width;
    F b = screen->pixel_height;
    F pole_pixela = a * b;
    for_n( i, n - 1 )
    {   F alfa = atan( (F)( points[ i + 1 ].y - points[i].y ) / ( points[ i + 1 ].x - points[i].x ));
        if( points[ i + 1 ].x > points[i].x )
        {   if( points[ i + 1 ].y < points[i].y )
                alfa += M_PI_2;
            else if( points[i].y == points[ i + 1 ].y )
            {   xcb_rectangle_t rectangle[1];
                rectangle[0].x = points[i].x;
                rectangle[0].y = points[i].y - (S16)( 0.5 * thickness / b );
                rectangle[0].width = points[ i + 1 ].x - points[i].x + 1;
                rectangle[0].height = (N16)( thickness / b );
                F pole = fmod( 0.5 * thickness, b );
                if(pole)
                {   pole *= a;
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x, rectangle[0].y - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_n
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width - 1, rectangle[0].y - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_n | E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_e
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x, rectangle[0].y + rectangle[0].height
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_s
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width - 1, rectangle[0].y + rectangle[0].height
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_s | E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_e
                    );
                    if( points[i].x + 1 < points[ i + 1 ].x )
                        for( S16 x = points[i].x + 1; x != points[ i + 1 ].x; x++ )
                        {   E_x_Q_window_I_draw_aa_Z_pixel_(
                              x, rectangle[0].y - 1
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_n
                            );
                            E_x_Q_window_I_draw_aa_Z_pixel_(
                              x, rectangle[0].y + rectangle[0].height
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_s
                            );
                        }
                }
                if( rectangle[0].height )
                {   E_x_Q_window_I_draw_P_color_(color);
                    E_x_Q_window_I_fill_Z_rectangles_(rectangle);
                    if(i)
                    {   xcb_arc_t arcs[2] =
                        { { points[i].x - rectangle[0].height / 2, points[i].y - rectangle[0].height / 2
                          , rectangle[0].height, rectangle[0].height
                          , 0, 24000
                          }
                        , { points[ i + 1 ].x - rectangle[0].height / 2, points[ i + 1 ].y - rectangle[0].height / 2
                          , rectangle[0].height, rectangle[0].height
                          , 0, 24000
                          }
                        };
                        E_x_Q_window_I_fill_Z_arcs_(arcs);
                    }
                }
                continue;
            }
        }else if( points[ i + 1 ].x < points[i].x )
        {   if( points[ i + 1 ].y > points[i].y )
                alfa += M_PI_2;
            else if( points[i].y == points[ i + 1 ].y )
            {   xcb_rectangle_t rectangle[1];
                rectangle[0].x = points[ i + 1 ].x;
                rectangle[0].y = points[i].y - (S16)( 0.5 * thickness / b );
                rectangle[0].width = points[i].x - points[ i + 1 ].x + 1;
                rectangle[0].height = (N16)( thickness / b );
                F pole = fmod( 0.5 * thickness, b );
                if(pole)
                {   pole *= a;
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x, rectangle[0].y - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_n
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width - 1, rectangle[0].y - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_n | E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_e
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x, rectangle[0].y + rectangle[0].height
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_sw | E_x_Z_aa_pixel_S_s
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width - 1, rectangle[0].y + rectangle[0].height
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_s | E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_e
                    );
                    if( points[ i + 1 ].x + 1 < points[i].x )
                        for( S16 x = points[ i + 1 ].x + 1; x != points[i].x; x++ )
                        {   E_x_Q_window_I_draw_aa_Z_pixel_(
                              x, rectangle[0].y - 1
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_n
                            );
                            E_x_Q_window_I_draw_aa_Z_pixel_(
                             x, rectangle[0].y + rectangle[0].height
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_s
                            );
                        }
                }
                if( rectangle[0].height )
                {   E_x_Q_window_I_draw_P_color_(color);
                    E_x_Q_window_I_fill_Z_rectangles_(rectangle);
                    if(i)
                    {   xcb_arc_t arcs[2] =
                        { { points[i].x - rectangle[0].height / 2, points[i].y - rectangle[0].height / 2
                          , rectangle[0].height, rectangle[0].height
                          , 0, 24000
                          }
                        , { points[ i + 1 ].x - rectangle[0].height / 2, points[ i + 1 ].y - rectangle[0].height / 2
                          , rectangle[0].height, rectangle[0].height
                          , 0, 24000
                          }
                        };
                        E_x_Q_window_I_fill_Z_arcs_(arcs);
                    }
                }
                continue;
            }
        }else
        {   if( points[ i + 1 ].y > points[i].y )
            {   xcb_rectangle_t rectangle[1];
                rectangle[0].x = points[i].x - (S16)( 0.5 * thickness / a );
                rectangle[0].y = points[i].y;
                rectangle[0].width = (N16)( thickness / a );
                rectangle[0].height = points[ i + 1 ].y - points[i].y + 1;
                F pole = fmod( 0.5 * thickness, a );
                if(pole)
                {   pole *= b;
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x - 1, rectangle[0].y
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_n
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width, rectangle[0].y
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_n | E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_e
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x - 1, rectangle[0].y + rectangle[0].height - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_sw | E_x_Z_aa_pixel_S_s
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width, rectangle[0].y + rectangle[0].height - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_s | E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_e
                    );
                    if( points[i].y + 1 < points[ i + 1 ].y )
                        for( S16 y = points[i].y + 1; y != points[ i + 1 ].y; y++ )
                        {   E_x_Q_window_I_draw_aa_Z_pixel_(
                              rectangle[0].x - 1, y
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_w
                            );
                            E_x_Q_window_I_draw_aa_Z_pixel_(
                              rectangle[0].x + rectangle[0].width, y
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_e
                            );
                        }
                }
                if( rectangle[0].width )
                {   E_x_Q_window_I_draw_P_color_(color);
                    E_x_Q_window_I_fill_Z_rectangles_(rectangle);
                    if(i)
                    {   xcb_arc_t arcs[2] =
                        { { points[i].x - rectangle[0].width / 2, points[i].y - rectangle[0].width / 2
                          , rectangle[0].width, rectangle[0].width
                          , 0, 24000
                          }
                        , { points[ i + 1 ].x - rectangle[0].width / 2, points[ i + 1 ].y - rectangle[0].width / 2
                          , rectangle[0].width, rectangle[0].width
                          , 0, 24000
                          }
                        };
                        E_x_Q_window_I_fill_Z_arcs_(arcs);
                    }
                }
            }else if( points[ i + 1 ].y < points[i].y )
            {   xcb_rectangle_t rectangle[1];
                rectangle[0].x = points[i].x - (S16)( 0.5 * thickness / a );
                rectangle[0].y = points[ i + 1 ].y;
                rectangle[0].width = (N16)( thickness / a );
                rectangle[0].height = points[i].y - points[ i + 1 ].y + 1;
                F pole = fmod( 0.5 * thickness, a );
                if(pole)
                {   pole *= b;
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x - 1, rectangle[0].y
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_n
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width, rectangle[0].y
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_n | E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_e
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x - 1, rectangle[0].y + rectangle[0].height - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_w | E_x_Z_aa_pixel_S_sw | E_x_Z_aa_pixel_S_s
                    );
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      rectangle[0].x + rectangle[0].width, rectangle[0].y + rectangle[0].height - 1
                    , color
                    , pole / pole_pixela
                    , E_x_Z_aa_pixel_S_s | E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_e
                    );
                    if( points[ i + 1 ].y + 1 < points[i].y )
                        for( S16 y = points[ i + 1 ].y + 1; y != points[i].y; y++ )
                        {   E_x_Q_window_I_draw_aa_Z_pixel_(
                              rectangle[0].x - 1, y
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_w
                            );
                            E_x_Q_window_I_draw_aa_Z_pixel_(
                              rectangle[0].x + rectangle[0].width, y
                            , color
                            , pole / pole_pixela
                            , E_x_Z_aa_pixel_S_e
                            );
                        }
                }
                if( rectangle[0].width )
                {   E_x_Q_window_I_draw_P_color_(color);
                    E_x_Q_window_I_fill_Z_rectangles_(rectangle);
                    if(i)
                    {   xcb_arc_t arcs[2] =
                        { { points[i].x - rectangle[0].width / 2, points[i].y - rectangle[0].width / 2
                          , rectangle[0].width, rectangle[0].width
                          , 0, 24000
                          }
                        , { points[ i + 1 ].x - rectangle[0].width / 2, points[ i + 1 ].y - rectangle[0].width / 2
                          , rectangle[0].width, rectangle[0].width
                          , 0, 24000
                          }
                        };
                        E_x_Q_window_I_fill_Z_arcs_(arcs);
                    }
                }
            }else
            {   GV( "point instead of line" );
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
                struct E_x_Z_points *pixel_points;
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
                pole += E_x_I_pole_wielokata( pixel_points_n, pixel_points );
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
                    ){  E_x_Q_window_I_draw_P_color_(color);
                        S16 x_ = x, y_ = y;
                        for_n_rev( i, dx_dy_n )
                        {   x_ -= dx_dy[i].dx;
                            y_ -= dx_dy[i].dy;
                            if( i == dx_dy_n - 1
                            && (( dx_dy[i].dx && prev_dx  )
                              || ( dx_dy[i].dy && prev_dy )
                            ))
                                continue;
                            xcb_point_t point = { x_, y_ };
                            E_x_Q_window_I_draw_Z_points( display, screen, window, 1, &point );
                        }
                    }
                }else if( j == 2 )
                    if( dx_dy_n )
                    {   E_mem_Q_blk_I_remove( &dx_dy, 0, dx_dy_n );
                        dx_dy_n = 0;
                    }
                if( !U_R( first_pixel, overdrawn ))
                {   N get_pixel;
                    if( U_R( screen->mode, animation ))
                        if( dx_direction > 0 && dy_direction > 0 )
                        {   get_pixel = prawoskretny ? E_x_Z_aa_pixel_S_sw : E_x_Z_aa_pixel_S_ne;
                            if( prawoskretny && prev_dy )
                                get_pixel |= E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_w;
                            if( !prawoskretny && prev_dx )
                                get_pixel |= E_x_Z_aa_pixel_S_nw | E_x_Z_aa_pixel_S_n;
                            if( prawoskretny && !dy )
                                get_pixel |= E_x_Z_aa_pixel_S_s;
                            if( !prawoskretny && !dx )
                                get_pixel |= E_x_Z_aa_pixel_S_e;
                        }else if( dx_direction > 0 && dy_direction < 0 )
                        {   get_pixel = prawoskretny ? E_x_Z_aa_pixel_S_se : E_x_Z_aa_pixel_S_nw;
                            if( prawoskretny && prev_dx )
                                get_pixel |= E_x_Z_aa_pixel_S_sw | E_x_Z_aa_pixel_S_s;
                            if( !prawoskretny && prev_dy )
                                get_pixel |= E_x_Z_aa_pixel_S_sw | E_x_Z_aa_pixel_S_w;
                            if( prawoskretny && !dx )
                                get_pixel |= E_x_Z_aa_pixel_S_s;
                            if( !prawoskretny && !dy )
                                get_pixel |= E_x_Z_aa_pixel_S_w;
                        }else if( dx_direction < 0 && dy_direction > 0 )
                        {   get_pixel = prawoskretny ? E_x_Z_aa_pixel_S_nw : E_x_Z_aa_pixel_S_se;
                            if( prawoskretny && prev_dx )
                                get_pixel |= E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_n;
                            if( !prawoskretny && prev_dy )
                                get_pixel |= E_x_Z_aa_pixel_S_ne | E_x_Z_aa_pixel_S_e;
                            if( prawoskretny && !dx )
                                get_pixel |= E_x_Z_aa_pixel_S_e;
                            if( !prawoskretny && !dy )
                                get_pixel |= E_x_Z_aa_pixel_S_s;
                        }else 
                        {   get_pixel = prawoskretny ? E_x_Z_aa_pixel_S_ne : E_x_Z_aa_pixel_S_sw;
                            if( prawoskretny && prev_dy )
                                get_pixel |= E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_e;
                            if( !prawoskretny && prev_dx )
                                get_pixel |= E_x_Z_aa_pixel_S_se | E_x_Z_aa_pixel_S_s;
                            if( prawoskretny && !dy )
                                get_pixel |= E_x_Z_aa_pixel_S_n;
                            if( !prawoskretny && !dx )
                                get_pixel |= E_x_Z_aa_pixel_S_w;
                        }
                    else
                        get_pixel = 0;
                    E_x_Q_window_I_draw_aa_Z_pixel_(
                      x, y
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
        if( i && dx_dy_n )
        {   xcb_arc_t arcs[1] =
            { points[i].x - dx_dy_n, points[i].y - dx_dy_n
            , dx_dy_n * 2, dx_dy_n * 2
            , 0, 24000
            };
            E_x_Q_window_I_draw_P_color_(color);
            E_x_Q_window_I_fill_Z_arcs_(arcs);
        }
    }
    return 0;
}

void
E_x_Q_object_I_draw_P_color(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_object_Z *object
, N32 color
){  if( !U_R( object->mode, drag_src ))
        E_x_Q_window_I_draw_P_color_(color);
}

void
E_x_Q_object_I_draw_Z_points(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_point_t *points
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_x_Q_window_I_draw_Z_points( display, screen, window, n, points );
}
void
E_x_Q_object_I_draw_Z_segments(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_segment_t *segments
){  for_n( i, n )
    {   segments[i].x1 += object->x;
        segments[i].y1 += object->y;
        segments[i].x2 += object->x;
        segments[i].y2 += object->y;
    }
    E_x_Q_window_I_draw_Z_segments( display, screen, window, n, segments );
}
void
E_x_Q_object_I_draw_Z_lines(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_point_t *points
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_x_Q_window_I_draw_Z_lines( display, screen, window, n, points );
}
void
E_x_Q_object_I_draw_Z_rectangles(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_rectangle_t *rectangles
){  for_n( i, n )
    {   rectangles[i].x += object->x;
        rectangles[i].y += object->y;
    }
    E_x_Q_window_I_draw_Z_rectangles( display, screen, window, n, rectangles );
}
void
E_x_Q_object_I_draw_Z_arcs(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_arc_t *arcs
){  for_n( i, n )
    {   arcs[i].x += object->x;
        arcs[i].y += object->y;
    }
    E_x_Q_window_I_draw_Z_arcs( display, screen, window, n, arcs );
}
void
E_x_Q_object_I_fill_Z_points(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_point_t *points
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_x_Q_window_I_fill_Z_points( display, screen, window, n, points );
}
void
E_x_Q_object_I_fill_Z_rectangles(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_rectangle_t *rectangles
){  for_n( i, n )
    {   rectangles[i].x += object->x;
        rectangles[i].y += object->y;
    }
    E_x_Q_window_I_fill_Z_rectangles( display, screen, window, n, rectangles );
}
void
E_x_Q_object_I_fill_Z_arcs(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N32 n
, xcb_arc_t *arcs
){  for_n( i, n )
    {   arcs[i].x += object->x;
        arcs[i].y += object->y;
    }
    E_x_Q_window_I_fill_Z_arcs( display, screen, window, n, arcs );
}

void
E_x_Q_object_I_draw_aa_Z_pixel(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, S16 x
, S16 y
, N32 color
, F brightness
, N get_pixel
){  E_x_Q_window_I_draw_aa_Z_pixel_(
      object->x + x
    , object->y + y
    , !U_R( object->mode, drag_src ) ? color : E_x_Q_theme.current_brace
    , brightness
    , get_pixel
    );
}
void
E_x_Q_object_I_draw_aa_Z_lines(
  struct E_x_Q_display_Z *display
, struct E_x_Q_screen_Z *screen
, struct E_x_Q_window_Z *window
, struct E_x_Q_object_Z *object
, N n
, xcb_point_t *points
, N32 color
, F thickness
){  for_n( i, n )
    {   points[i].x += object->x;
        points[i].y += object->y;
    }
    E_x_Q_window_I_draw_aa_Z_lines_(
      n
    , points
    , thickness
    , !U_R( object->mode, drag_src ) ? color : E_x_Q_theme.current_brace
    );
}


