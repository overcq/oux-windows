//-*-C-*-
//******************************************************************************
#include <math.h>
//==============================================================================
    #ifdef C_id_small
#define E_window_Q_obj_C_id_bits         16
    #else
#define E_window_Q_obj_C_id_bits         32
    #endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define E_window_Q_window_I_draw_P_color_(color)             E_window_Q_window_I_draw_P_color( color )
#define E_window_Q_window_I_draw_Z_points_(points)           E_window_Q_window_I_draw_Z_points( window, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_window_I_draw_Z_segments_(points)         E_window_Q_window_I_draw_Z_segments( window, segments, sizeof(segments) / sizeof( struct E_window_Z_segment ))
#define E_window_Q_window_I_draw_Z_lines_(points)            E_window_Q_window_I_draw_Z_lines( window, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_window_I_draw_Z_rectangles_(points)       E_window_Q_window_I_draw_Z_rectangles( window, rectangles, sizeof(rectangles) / sizeof( RECT ))
#define E_window_Q_window_I_draw_Z_arcs_(arcs)               E_window_Q_window_I_draw_Z_arcs( window, rectangles, sizeof(arcs) / sizeof( struct E_window_Z_arc ))
#define E_window_Q_window_I_fill_Z_points_(points)           E_window_Q_window_I_fill_Z_points( window, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_window_I_fill_Z_rectangles_(rectangles)   E_window_Q_window_I_fill_Z_rectangles( window, rectangles, sizeof(rectangles) / sizeof( RECT ))
#define E_window_Q_window_I_fill_Z_arcs_(arcs)               E_window_Q_window_I_fill_Z_arcs( window, arcs, sizeof(arcs) / sizeof( RECT ))
//------------------------------------------------------------------------------
#define E_window_Q_object_I_draw_P_color_(color)             E_window_Q_object_I_draw_P_color( object, color )
#define E_window_Q_object_I_draw_Z_points_(points)           E_window_Q_object_I_draw_Z_points( window, object, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_object_I_draw_Z_segments_(segments)       E_window_Q_object_I_draw_Z_segments( window, object, segments, sizeof(segments) / sizeof( struct E_window_Z_segment ))
#define E_window_Q_object_I_draw_Z_lines_(points)            E_window_Q_object_I_draw_Z_lines( window, object, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_object_I_draw_Z_rectangles_(rectangles)   E_window_Q_object_I_draw_Z_rectangles( window, object, rectangles, sizeof(rectangles) / sizeof( RECT ))
#define E_window_Q_object_I_draw_Z_arcs_(arcs)               E_window_Q_object_I_draw_Z_arcs( window, object, arcs, sizeof(arcs) / sizeof( struct E_window_Z_arc ))
#define E_window_Q_object_I_fill_Z_points_(points)           E_window_Q_object_I_fill_Z_points( window, object, points, sizeof(points) / sizeof( POINT ))
#define E_window_Q_object_I_fill_Z_rectangles_(rectangles)   E_window_Q_object_I_fill_Z_rectangles( window, object, rectangles, sizeof(rectangles) / sizeof( RECT ))
#define E_window_Q_object_I_fill_Z_arcs_(arcs)               E_window_Q_object_I_fill_Z_arcs( window, object, arcs, sizeof(arcs) / sizeof( RECT ))
//------------------------------------------------------------------------------
#define E_window_Q_window_I_draw_aa_Z_pixel_( x, y, color, brightness, get_pixel )   E_window_Q_window_I_draw_aa_Z_pixel( window, x, y, color, brightness, get_pixel )
#define E_window_Q_window_I_draw_aa_Z_lines_( n, points, thickness, color )  E_window_Q_window_I_draw_aa_Z_lines( window, n, points, thickness, color )
//------------------------------------------------------------------------------
#define E_window_Q_window_I_draw_Z_font_( x, y, color, id, u )       E_window_Q_window_I_draw_Z_font( window, x, y, color, id, u )
#define E_window_Q_window_I_draw_Z_font_Z_s_( x, y, color, id, s )   E_window_Q_window_I_draw_Z_font_Z_s( window, x, y, color, id, s )
#define E_window_Q_object_I_draw_Z_font_( x, y, color, id, u )       E_window_Q_object_I_draw_Z_font( window, object, x, y, color, id, u )
#define E_window_Q_object_I_draw_Z_font_Z_s_( x, y, color, id, s )   E_window_Q_object_I_draw_Z_font_Z_s( window, object, x, y, color, id, s )
//******************************************************************************
