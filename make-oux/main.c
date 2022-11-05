/*******************************************************************************
*  ___   publicplace
* |OUX|  C
* |/C+|  make
*  ---   make oux
*        main
* (c)overcq                       on Windows XP                     2022-08-21 *
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define PCRE2_STATIC 1
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
//==============================================================================
HANDLE E_main_S_process_heap;
unsigned long E_main_S_xyi_array_a_n, E_main_S_xyi_array_b_n;
char **E_main_S_xyi_array_a, **E_main_S_xyi_array_b;
pcre2_code *E_main_S_x_regex, *E_main_S_yi_regex, *E_main_S_h_xyi_regex_b, *E_main_S_preproc_if_regex, *E_main_S_struct_union_regex, *E_main_S_d_regex, *E_main_S_e_regex, *E_main_S_enum_struct_union_regex_2, *E_main_S_enum_struct_union_regex_1, *E_main_S_def_name_regex, *E_main_S_def_name_asterisk_regex, *E_main_S_enum_struct_union_regex_3;
pcre2_match_data *E_main_S_3_match_data;
//==============================================================================
char *
strnstr( char *s
, char *t
, unsigned long l
){  char *s_ = s;
    char *t_ = t;
    for( unsigned long i = 0; i != l; i++ )
    {   if( *s_ == *t_ )
        {   if( t_ == t )
                s = s_;
            t_++;
            if( !*t_ )
                return s;
        }else
            t_ = t;
        s_++;
    }
    return 0;
}
//==============================================================================
int
E_main_Q_file_P_line( HANDLE file
, char *buf
){  unsigned long l = strlen(buf);
    unsigned long l_written;
    if( !WriteFile( file, buf, l, &l_written, 0 )
    || l_written != l
    )
    {   puts( "Unable to write to file." );
        return 1;
    }
    char s[1] = "\n";
    if( !WriteFile( file, s, sizeof(s), &l_written, 0 )
    || l_written != sizeof(s)
    )
    {   puts( "Unable to write to file." );
        return 1;
    }
    return 0;
}
int
E_main_Q_file_R_line( HANDLE file
, char **buf
){  unsigned long l = 1;
    *buf = HeapAlloc( E_main_S_process_heap, 0, l );
    if( !buf )
    {   puts( "Unable to allocate line buffer." );
        *buf = 0;
        return FALSE;
    }
    unsigned long l_read;
    int eof = FALSE;
    char s[1];
    do
    {   if( !ReadFile( file, &s[0], sizeof(s), &l_read, 0 ))
        {   puts( "Unable do read file." );
            HeapFree( E_main_S_process_heap, 0, *buf );
            *buf = 0;
            return eof;
        }
        if( l_read < sizeof(s) )
            eof = TRUE;
        if( !l_read
        || ( l_read == sizeof(s)
           && strncmp( s, "\n", sizeof(s) ) == 0
        ))
            break;
        char *buf_ = HeapReAlloc( E_main_S_process_heap, 0, *buf, l += l_read );
        if( !buf_ )
        {   puts( "Unable do realloc buffer." );
            HeapFree( E_main_S_process_heap, 0, *buf );
            *buf = 0;
            return eof;
        }
        *buf = buf_;
        strncpy( *buf + l - 1 - l_read, s, l_read );
    }while( l_read == sizeof(s) );
    (*buf)[ l - 1 ] = '\0';
    return eof;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char *
E_main_Q_filename_I_encode( char *filename
){  unsigned long size = strlen(filename) - 3 + 1;
    char *ret = HeapAlloc( E_main_S_process_heap, 0, size );
    if( !ret )
    {   puts( "Unable to allocate \"ret\"." );
        HeapFree( E_main_S_process_heap, 0, ret );
        return 0;
    }
    strncpy( ret, filename, size - 1 );
    ret[ size - 1 ] = '\0';
    for( char *p = ret; *p; p++ )
    {   if( isalnum( *p ))
            continue;
        unsigned long l_added = 2;
        char *s = HeapReAlloc( E_main_S_process_heap, 0, ret, size + l_added );
        if( !s )
        {   puts( "Unable to reallocate \"ret\"." );
            HeapFree( E_main_S_process_heap, 0, ret );
            return 0;
        }
        p = s + ( p - ret );
        ret = s;
        MoveMemory( p + 1 + l_added, p + 1, size - ( p + 1 - ret ));
        size += l_added;
        char c = p[ 1 + l_added ];
        sprintf( p, "_%.2x", *p );
        p[ 1 + l_added ] = c;
        p += l_added;
    }
    return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
E_main_I_cx_to_c( HANDLE h_file_cx
, HANDLE h_file
){  int eof;
    int inside_comment = FALSE, inside_braces = 0, inside_enum;
    char *last_line = 0;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
        {   if( last_line )
                HeapFree( E_main_S_process_heap, 0, last_line );
            return 1;
        }
Redo:   if( inside_comment )
        {   char *s = strstr( line, "*/" );
            if(s)
            {   MoveMemory( line, s + 2, strlen(s) - 2 + 1 );
                inside_comment = FALSE;
            }else
            {   if( last_line )
                {   if( E_main_Q_file_P_line( h_file, last_line ))
                    {   HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, last_line );
                }
                last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                if( !last_line )
                {   puts( "Unable to allocate \"last_line\"." );
                    return 1;
                }
                last_line[0] = '\0';
                goto Cont;
            }
        }
        char *s = strstr( line, "//" );
        if(s)
            *s = '\0';
        if( inside_braces == 1 )
        {   if( line[0] == '{' )
            {   if( last_line )
                {   if( E_main_Q_file_P_line( h_file, last_line ))
                    {   HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, last_line );
                }
                last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                if( !last_line )
                {   puts( "Unable to allocate \"last_line\"." );
                    return 1;
                }
                last_line[0] = '\0';
                inside_braces = 2;
                goto Cont;
            }
            inside_braces = 0;
        }
        if( inside_braces == 2 )
        {   if( line[0] == '}' )
            {   if( !inside_enum )
                {   inside_braces = strchr( line, ';' ) ? 0 : 3;
                    MoveMemory( line, line + 1, strlen( line + 1 ) + 1 );
                    if( last_line )
                    {   if( E_main_Q_file_P_line( h_file, last_line ))
                        {   HeapFree( E_main_S_process_heap, 0, last_line );
                            return 1;
                        }
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    }
                    last_line = line;
                }else
                {   inside_braces = 0;
                    if( last_line )
                    {   if( E_main_Q_file_P_line( h_file, last_line ))
                        {   HeapFree( E_main_S_process_heap, 0, last_line );
                            return 1;
                        }
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    }
                    last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                    if( !last_line )
                    {   puts( "Unable to allocate \"last_line\"." );
                        return 1;
                    }
                    last_line[0] = '\0';
                }
            }else
            {   if( last_line )
                {   if( E_main_Q_file_P_line( h_file, last_line ))
                    {   HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, last_line );
                }
                last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                if( !last_line )
                {   puts( "Unable to allocate \"last_line\"." );
                    CloseHandle( h_file );
                    return 1;
                }
                last_line[0] = '\0';
            }
            goto Cont;
        }
        if( inside_braces == 3 )
        {   if( last_line )
            {   if( E_main_Q_file_P_line( h_file, last_line ))
                {   HeapFree( E_main_S_process_heap, 0, last_line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, last_line );
            }
            last_line = line;
            if( line[0] == '}' )
                inside_braces = 0;
            goto Cont;
        }
        if( inside_braces == 4 )
        {   if( last_line )
            {   if( E_main_Q_file_P_line( h_file, last_line ))
                {   HeapFree( E_main_S_process_heap, 0, last_line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, last_line );
            }
            last_line = line;
            if( line[0] == ')' )
                inside_braces = 0;
            goto Cont;
        }
        int match_res = pcre2_match( E_main_S_enum_struct_union_regex_1, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for regex \"E_main_S_enum_struct_union_regex_1\"." );
                if( last_line )
                    HeapFree( E_main_S_process_heap, 0, last_line );
                return 1;
            }
            match_res = pcre2_match( E_main_S_enum_struct_union_regex_2, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   puts( "Match error for regex \"E_main_S_enum_struct_union_regex_2\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    return 1;
                }
                match_res = pcre2_match( E_main_S_e_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   puts( "Match error for regex \"E_main_S_e_regex\"." );
                        if( last_line )
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    match_res = pcre2_match( E_main_S_d_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                    if( match_res < 0 )
                    {   if( match_res != PCRE2_ERROR_NOMATCH )
                        {   puts( "Match error for regex \"E_main_S_d_regex\"." );
                            if( last_line )
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            return 1;
                        }
                        if( strncmp( line, "/*", 2 ))
                        {   if( last_line )
                            {   if( E_main_Q_file_P_line( h_file, last_line ))
                                {   HeapFree( E_main_S_process_heap, 0, last_line );
                                    return 1;
                                }
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            }
                            last_line = line;
                        }else
                        {   char *s = strstr( line, "*/" );
                            if(s)
                            {   MoveMemory( line, s + 2, strlen(s) - 2 + 1 );
                                goto Redo;
                            }
                            if( last_line )
                            {   if( E_main_Q_file_P_line( h_file, last_line ))
                                {   HeapFree( E_main_S_process_heap, 0, last_line );
                                    return 1;
                                }
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            }
                            last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                            if( !last_line )
                            {   puts( "Unable to allocate \"last_line\"." );
                                return 1;
                            }
                            last_line[0] = '\0';
                            inside_comment = TRUE;
                        }
                    }else
                    {   if( last_line )
                        {   if( E_main_Q_file_P_line( h_file, last_line ))
                            {   HeapFree( E_main_S_process_heap, 0, last_line );
                                return 1;
                            }
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        }
                        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                        last_line = HeapAlloc( E_main_S_process_heap, 0, 16 + ovector[3] - ovector[2] + 7 + strlen(line) + 1 );
                        if( !last_line )
                        {   puts( "Unable to allocate \"last_line\"." );
                            return 1;
                        }
                        strcpy( last_line, "_internal I D_id" );
                        strncpy( last_line + 16, line + ovector[2], ovector[3] - ovector[2] );
                        strcpy( last_line + 16 + ovector[3] - ovector[2], " = ~0; " );
                        strcpy( last_line + 16 + ovector[3] - ovector[2] + 7, line );
                    }
                }else
                {   if( last_line )
                    {   if( E_main_Q_file_P_line( h_file, last_line ))
                        {   HeapFree( E_main_S_process_heap, 0, last_line );
                            return 1;
                        }
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    }
                    last_line = line;
                    inside_braces = 4;
                }
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                if( last_line )
                {   if( E_main_Q_file_P_line( h_file, last_line ))
                    {   HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, last_line );
                }
                inside_enum = !strncmp( line, "enum", ovector[3] );
                if( !inside_enum )
                    last_line = line;
                else
                {   last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                    if( !last_line )
                    {   puts( "Unable to allocate \"last_line\"." );
                        return 1;
                    }
                    last_line[0] = '\0';
                }
                inside_braces = 1;
            }
        }else
        {   if( last_line )
            {   if( E_main_Q_file_P_line( h_file, last_line ))
                {   HeapFree( E_main_S_process_heap, 0, last_line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, last_line );
            }
            last_line = line;
        }
Cont:;
    }while( !eof );
    if( last_line )
    {   if( E_main_Q_file_P_line( h_file, last_line ))
        {   HeapFree( E_main_S_process_heap, 0, last_line );
            return 1;
        }
        HeapFree( E_main_S_process_heap, 0, last_line );
    }
    return 0;
}
int
E_main_I_cx_to_h_1( HANDLE h_file_cx
, HANDLE h_file
, char *file
, char *enc
){  unsigned long xyi_array_b_n = 0;
    char **xyi_array_b = HeapAlloc( E_main_S_process_heap, 0, xyi_array_b_n );
    int eof;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
        {   HeapFree( E_main_S_process_heap, 0, xyi_array_b );
            return 1;
        }
        int match_res = pcre2_match( E_main_S_h_xyi_regex_b, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for \"E_main_S_h_xyi_regex_b\"." );
                HeapFree( E_main_S_process_heap, 0, xyi_array_b );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) + 1 );
            if( !s )
            {   puts( "Unable to allocate \"xyi_array_b\" element." );
                HeapFree( E_main_S_process_heap, 0, xyi_array_b );
                return 1;
            }
            strncpy( s, line + ovector[2], ovector[3] - ovector[2] );
            strcpy( s + ( ovector[3] - ovector[2] ), ",X_" );
            strncpy( s + ( ovector[3] - ovector[2] ) + 3, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != xyi_array_b_n; i++ )
                if( !strcmp( xyi_array_b[i], s ))
                    break;
            if( i == xyi_array_b_n )
            {   for( i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    if( E_main_S_xyi_array_a[i]
                    && !strcmp( E_main_S_xyi_array_a[i], s )
                    )
                        break;
                if( i == E_main_S_xyi_array_a_n )
                {   void *p = HeapReAlloc( E_main_S_process_heap, 0, xyi_array_b, sizeof( char * ) * ( xyi_array_b_n + 1 ));
                    if( !p )
                    {   puts( "Unable to reallocate \"xyi_array_b\"." );
                        HeapFree( E_main_S_process_heap, 0, xyi_array_b );
                        return 1;
                    }
                    xyi_array_b = p;
                    xyi_array_b_n++;
                    xyi_array_b[ xyi_array_b_n - 1 ] = s;
                }
            }
        }
    }while( !eof );
    if( xyi_array_b_n )
    {   unsigned long l = strlen( xyi_array_b[0] );
        unsigned long l_enc = strlen(enc);
        unsigned long buffer_size = 17 + l + 17 + l_enc + 3 + 3;
        for( unsigned long i = 1; i != xyi_array_b_n; i++ )
        {   unsigned long l = strlen( xyi_array_b[0] );
            buffer_size += 12 + l + 17 + l_enc + 3;
        }
        char *buffer = HeapAlloc( E_main_S_process_heap, 0, buffer_size );
        if( !buffer )
        {   puts( "Unable to allocate \"buffer\"." );
            HeapFree( E_main_S_process_heap, 0, xyi_array_b );
            return 1;
        }
        strcpy( buffer, "enum\n{ _XhYi_uid(" );
        strcpy( buffer + 17, xyi_array_b[0] );
        strcpy( buffer + 17 + l, ") = _XhYi_F_uid( " );
        strcpy( buffer + 17 + l + 17, enc );
        strncpy( buffer + 17 + l + 17 + l_enc, " )\n", 3 );
        char *s = buffer + 17 + l + 17 + l_enc + 3;
        for( unsigned long i = 1; i != xyi_array_b_n; i++ )
        {   unsigned long l = strlen( xyi_array_b[0] );
            strcpy( s, ", _XhYi_uid(" );
            strcpy( s + 12, xyi_array_b[i] );
            strcpy( s + 12 + l, ") = _XhYi_F_uid( " );
            strcpy( s + 12 + l + 17, enc );
            strcpy( s + 12 + l + 17 + l_enc, " )\n" );
            s += 12 + l + 17 + l_enc + 3;
        }
        strncpy( s, "};\n", 3 );
        unsigned long wrote;
        WriteFile( h_file, buffer, buffer_size, &wrote, 0 );
        if( wrote != buffer_size )
        {   printf( "Unable to write file \"%s\": %lu.\n", file, GetLastError() );
            HeapFree( E_main_S_process_heap, 0, buffer );
            return 1;
        }
    }
    HeapFree( E_main_S_process_heap, 0, xyi_array_b );
    return 0;
}
int
E_main_I_cx_to_h_2( HANDLE h_file_cx
, HANDLE h_file
){  int eof;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
            return 1;
        char *s = strstr( line, "//" );
        if(s)
            *s = '\0';
        int match_res = pcre2_match( E_main_S_preproc_if_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for \"E_main_S_preproc_if_regex\"." );
                return 1;
            }
            match_res = pcre2_match( E_main_S_struct_union_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   puts( "Match error for \"E_main_S_preproc_if_regex\"." );
                    return 1;
                }
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                char *line_out = HeapAlloc( E_main_S_process_heap, 0, ovector[1] + 1 + 1 );
                if( !line_out )
                    return 1;
                strncpy( line_out, line, ovector[1] );
                strcpy( line_out + ovector[1], ";" );
                if( E_main_Q_file_P_line( h_file, line_out ))
                {   HeapFree( E_main_S_process_heap, 0, line_out );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, line_out );
            }
        }else
        {   if( E_main_Q_file_P_line( h_file, line ))
                return 1;
        }
        
    }while( !eof );
    return 0;
}
int
E_main_I_cx_to_h_3( HANDLE h_file_cx
, HANDLE h_file
){  int eof;
    int inside_braces = 0;
    char *last_line = 0;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
        {   if( last_line )
                HeapFree( E_main_S_process_heap, 0, last_line );
            return 1;
        }
        char *s = strstr( line, "//" );
        if(s)
            *s = '\0';
        if( inside_braces == 1 )
        {   if( line[0] == '{' )
            {   if( E_main_Q_file_P_line( h_file, last_line ))
                {   HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                if( E_main_Q_file_P_line( h_file, line ))
                {   HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                inside_braces = 2;
                HeapFree( E_main_S_process_heap, 0, line );
                goto Cont;
            }
            inside_braces = 0;
        }
        if( inside_braces == 2 )
        {   int match_res = pcre2_match( E_main_S_def_name_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   puts( "Match error for regex \"E_main_S_def_name_regex\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                if( E_main_Q_file_P_line( h_file, line ))
                {   if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                unsigned long l = ovector[3] - ovector[2];
                char *s = HeapAlloc( E_main_S_process_heap, 0, l + 1 );
                if( !s )
                {   puts( "Unable to reallocate \"s\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                strncpy( s, line + ovector[2], l );
                s[l] = '\0';
                match_res = pcre2_match( E_main_S_def_name_asterisk_regex, s, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   puts( "Match error for regex \"E_main_S_def_name_asterisk_regex\"." );
                        HeapFree( E_main_S_process_heap, 0, s );
                        if( last_line )
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        HeapFree( E_main_S_process_heap, 0, line );
                        return 1;
                    }
                }else
                {   char *s_ = HeapReAlloc( E_main_S_process_heap, 0, s, 7 + ( s[ ovector[2] ] ? 0 : 1 ) + l - 1 + 1 );
                    if( !s_ )
                    {   puts( "Unable to reallocate \"s\"." );
                        HeapFree( E_main_S_process_heap, 0, s );
                        if( last_line )
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        HeapFree( E_main_S_process_heap, 0, line );
                        return 1;
                    }
                    s = s_;
                    MoveMemory( s + 7 + ( s[ ovector[2] ] ? 0 : 1 ), s + 1, l - 1 + 1 );
                    strcpy( s, "extern" );
                    if( !s[ ovector[2] ] )
                        s[7] = ' ';
                    l = 7 + ( s[ ovector[2] ] ? 0 : 1 ) + l - 1;
                }
                char *s_ = HeapReAlloc( E_main_S_process_heap, 0, s, l + 1 + 1 );
                if( !s_ )
                {   puts( "Unable to reallocate \"s\"." );
                    HeapFree( E_main_S_process_heap, 0, s );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                s = s_;
                strcpy( s + l, ";" );
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, s );
            }
            HeapFree( E_main_S_process_heap, 0, line );
            goto Cont;
        }
        if( inside_braces == 3 )
        {   if( line[0] == '{' )
                inside_braces = 0;
            HeapFree( E_main_S_process_heap, 0, line );
            goto Cont;
        }
        if( inside_braces == 4 )
        {   if( line[0] == ')' )
            {   unsigned long l = strlen(line);
                char *s = HeapAlloc( E_main_S_process_heap, 0, 1 + 1 + 1 );
                if( !s )
                {   puts( "Unable to allocate \"s\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                s[0] = ')';
                strcpy( s + 1, ";" );
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, s );
                inside_braces = 0;
            }else if( E_main_Q_file_P_line( h_file, line ))
            {   if( last_line )
                    HeapFree( E_main_S_process_heap, 0, last_line );
                HeapFree( E_main_S_process_heap, 0, line );
                return 1;
            }
            HeapFree( E_main_S_process_heap, 0, line );
            goto Cont;
        }
        int match_res = pcre2_match( E_main_S_preproc_if_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for regex \"E_main_S_preproc_if_regex\"." );
                if( last_line )
                    HeapFree( E_main_S_process_heap, 0, last_line );
                HeapFree( E_main_S_process_heap, 0, line );
                return 1;
            }
            match_res = pcre2_match( E_main_S_enum_struct_union_regex_3, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   puts( "Match error for regex \"E_main_S_enum_struct_union_regex_3\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                match_res = pcre2_match( E_main_S_enum_struct_union_regex_2, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   puts( "Match error for regex \"E_main_S_enum_struct_union_regex_2\"." );
                        if( last_line )
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        HeapFree( E_main_S_process_heap, 0, line );
                        return 1;
                    }
                    match_res = pcre2_match( E_main_S_e_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                    if( match_res < 0 )
                    {   if( match_res != PCRE2_ERROR_NOMATCH )
                        {   puts( "Match error for regex \"E_main_S_e_regex\"." );
                            if( last_line )
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            HeapFree( E_main_S_process_heap, 0, line );
                            return 1;
                        }
                        match_res = pcre2_match( E_main_S_d_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
                        if( match_res < 0 )
                        {   if( match_res != PCRE2_ERROR_NOMATCH )
                            {   puts( "Match error for regex \"E_main_S_d_regex\"." );
                                if( last_line )
                                    HeapFree( E_main_S_process_heap, 0, last_line );
                                HeapFree( E_main_S_process_heap, 0, line );
                                return 1;
                            }
                            if( last_line )
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            last_line = line;
                        }else
                        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                            unsigned long l = strlen(line);
                            char *s = HeapAlloc( E_main_S_process_heap, 0, 13 + ( ovector[3] - ovector[2] ) + 2 + l + 1 + 1 );
                            if( !s )
                            {   puts( "Unable to allocate \"s\"." );
                                if( last_line )
                                    HeapFree( E_main_S_process_heap, 0, last_line );
                                HeapFree( E_main_S_process_heap, 0, line );
                                return 1;
                            }
                            strcpy( s, "extern I D_id" );
                            strncpy( s + 13, line + ovector[2], ovector[3] - ovector[2] );
                            strcpy( s + 13 + ( ovector[3] - ovector[2] ), "; " );
                            strcpy( s + 13 + ( ovector[3] - ovector[2] ) + 2, line );
                            strcpy( s + 13 + ( ovector[3] - ovector[2] ) + 2 + l, ";" );
                            if( E_main_Q_file_P_line( h_file, s ))
                            {   HeapFree( E_main_S_process_heap, 0, s );
                                if( last_line )
                                    HeapFree( E_main_S_process_heap, 0, last_line );
                                HeapFree( E_main_S_process_heap, 0, line );
                                return 1;
                            }
                            HeapFree( E_main_S_process_heap, 0, s );
                            HeapFree( E_main_S_process_heap, 0, line );
                        }
                    }else
                    {   if( E_main_Q_file_P_line( h_file, last_line ))
                        {   HeapFree( E_main_S_process_heap, 0, last_line );
                            HeapFree( E_main_S_process_heap, 0, line );
                            return 1;
                        }
                        if( E_main_Q_file_P_line( h_file, line ))
                        {   HeapFree( E_main_S_process_heap, 0, last_line );
                            HeapFree( E_main_S_process_heap, 0, line );
                            return 1;
                        }
                        inside_braces = 4;
                        HeapFree( E_main_S_process_heap, 0, line );
                    }
                }else
                {   inside_braces = 1;
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    last_line = line;
                }
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
                unsigned long l = ovector[3];
                char *s = HeapAlloc( E_main_S_process_heap, 0, 7 + l + 1 + 1 );
                if( !s )
                {   puts( "Unable to allocate \"s\"." );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                strcpy( s, "extern " );
                strncpy( s + 7, line, l );
                strcpy( s + 7 + l, ";" );
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    HeapFree( E_main_S_process_heap, 0, line );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, s );
                HeapFree( E_main_S_process_heap, 0, line );
            }
        }else
        {   if( E_main_Q_file_P_line( h_file, line ))
            {   if( last_line )
                    HeapFree( E_main_S_process_heap, 0, last_line );
                HeapFree( E_main_S_process_heap, 0, line );
                return 1;
            }
            HeapFree( E_main_S_process_heap, 0, line );
        }
Cont:;
    }while( !eof );
    if( last_line )
        HeapFree( E_main_S_process_heap, 0, last_line );
    return 0;
}
int
E_main_I_cx_to_xyi_array( HANDLE h_file_cx
){  int eof;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
            return 1;
        int match_res = pcre2_match( E_main_S_x_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for \"E_main_S_x_regex\"." );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) + 1 );
            if( !s )
            {   puts( "Unable to allocate \"E_main_S_xyi_array\" element." );
                return 1;
            }
            strncpy( s, line + ovector[2], ovector[3] - ovector[2] );
            strcpy( s + ( ovector[3] - ovector[2] ), ",X_" );
            strncpy( s + ( ovector[3] - ovector[2] ) + 3, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != E_main_S_xyi_array_a_n; i++ )
                if( E_main_S_xyi_array_a[i]
                && !strcmp( E_main_S_xyi_array_a[i], s )
                )
                    break;
            if( i == E_main_S_xyi_array_a_n )
            {   for( i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    if( !strcmp( E_main_S_xyi_array_b[i], s ))
                        break;
                if( i == E_main_S_xyi_array_b_n )
                    if( line[ ovector[0] + 2 + ( line[ ovector[0] ] == 'Y' ? 1 : 0 ) ] == 'A' )
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, E_main_S_xyi_array_a, sizeof( char * ) * ( E_main_S_xyi_array_a_n + 1 ));
                        if( !p )
                        {   puts( "Unable to reallocate \"E_main_S_xyi_array_a\"." );
                            return 1;
                        }
                        E_main_S_xyi_array_a = p;
                        E_main_S_xyi_array_a_n++;
                        E_main_S_xyi_array_a[ E_main_S_xyi_array_a_n - 1 ] = s;
                    }else
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, E_main_S_xyi_array_b, sizeof( char * ) * ( E_main_S_xyi_array_b_n + 1 ));
                        if( !p )
                        {   puts( "Unable to reallocate \"E_main_S_xyi_array_b\"." );
                            return 1;
                        }
                        E_main_S_xyi_array_b = p;
                        E_main_S_xyi_array_b_n++;
                        E_main_S_xyi_array_b[ E_main_S_xyi_array_b_n - 1 ] = s;
                    }
            }
        }
        match_res = pcre2_match( E_main_S_yi_regex, line, PCRE2_ZERO_TERMINATED, 0, 0, E_main_S_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   puts( "Match error for \"E_main_S_yi_regex\"." );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( E_main_S_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 4 + ( ovector[5] - ovector[4] ) + 1 );
            if( !s )
            {   puts( "Unable to allocate \"E_main_S_xyi_array\" element." );
                return 1;
            }
            strncpy( s, line + ovector[2], ovector[3] - ovector[2] );
            strcpy( s + ( ovector[3] - ovector[2] ), ",Yi_" );
            strncpy( s + ( ovector[3] - ovector[2] ) + 4, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 4 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != E_main_S_xyi_array_a_n; i++ )
                if( E_main_S_xyi_array_a[i]
                && !strcmp( E_main_S_xyi_array_a[i], s )
                )
                    break;
            if( i == E_main_S_xyi_array_a_n )
            {   for( i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    if( !strcmp( E_main_S_xyi_array_b[i], s ))
                        break;
                if( i == E_main_S_xyi_array_b_n )
                    if( line[ ovector[0] + 2 + ( line[ ovector[0] ] == 'Y' ? 1 : 0 ) ] == 'A' )
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, E_main_S_xyi_array_a, sizeof( char * ) * ( E_main_S_xyi_array_a_n + 1 ));
                        if( !p )
                        {   puts( "Unable to reallocate \"E_main_S_xyi_array_a\"." );
                            return 1;
                        }
                        E_main_S_xyi_array_a = p;
                        E_main_S_xyi_array_a_n++;
                        E_main_S_xyi_array_a[ E_main_S_xyi_array_a_n - 1 ] = s;
                    }else
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, E_main_S_xyi_array_b, sizeof( char * ) * ( E_main_S_xyi_array_b_n + 1 ));
                        if( !p )
                        {   puts( "Unable to reallocate \"E_main_S_xyi_array_b\"." );
                            return 1;
                        }
                        E_main_S_xyi_array_b = p;
                        E_main_S_xyi_array_b_n++;
                        E_main_S_xyi_array_b[ E_main_S_xyi_array_b_n - 1 ] = s;
                    }
            }
        }
    }while( !eof );
    return 0;
}
int
E_main_I_build_programs( char *file_mask
, char *file_h_to_libs_buffer
, unsigned long file_h_to_libs_buffer_size
){  WIN32_FIND_DATA found_file;
    HANDLE h_find_file = FindFirstFile( file_mask, &found_file );
    if( h_find_file == INVALID_HANDLE_VALUE )
    {   printf( "Not found directory for mask \"%s\".", file_mask );
        return 1;
    }
    unsigned long file_h_not_to_libs_buffer_size = file_h_to_libs_buffer_size;
    char *file_h_not_to_libs_buffer = HeapAlloc( E_main_S_process_heap, 0, file_h_not_to_libs_buffer_size );
    if( !file_h_not_to_libs_buffer )
    {   FindClose( h_find_file );
        return 1;
    }
    CopyMemory( file_h_not_to_libs_buffer, file_h_to_libs_buffer, file_h_to_libs_buffer_size );
    unsigned long l_file_mask = strlen( file_mask );
    do
    {   if( found_file.cFileName[0] != '.' )
        {   if( found_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            {   char *file_h_not_to_libs = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + 23 + 1 );
                if( !file_h_not_to_libs )
                {   puts( "Unable to allocate \"file_h_not_to_libs\"." );
                    FindClose( h_find_file );
                    HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                    return 1;
                }
                strncpy( file_h_not_to_libs, file_mask, l_file_mask - 1 );
                strcpy( file_h_not_to_libs + l_file_mask - 1, "E_cplus_S_not_to_libs.h" );
                DeleteFile( file_h_not_to_libs );
                HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
                unsigned long l_dir = strlen( found_file.cFileName );
                char *file_mask_ = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_dir + 2 + 1 );
                if( !file_mask_ )
                {   puts( "Unable to allocate \"file_mask_\"." );
                    FindClose( h_find_file );
                    HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                    return 1;
                }
                strncpy( file_mask_, file_mask, l_file_mask - 1 );
                strcpy( file_mask_ + l_file_mask - 1, found_file.cFileName );
                strcpy( file_mask_ + l_file_mask - 1 + l_dir, "\\*" );
                if( E_main_I_build_programs( file_mask_, file_h_to_libs_buffer, file_h_to_libs_buffer_size ))
                {   HeapFree( E_main_S_process_heap, 0, file_mask_ );
                    FindClose( h_find_file );
                    HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, file_mask_ );
            }else
            {   unsigned long l_file = strlen( found_file.cFileName );
                if( l_file > 3
                && !strcmp( found_file.cFileName + l_file - 3, ".cx" )
                )
                {   char *file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_file + 1 );
                    if( !file )
                    {   puts( "Unable to allocate \"file\"." );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    strncpy( file, file_mask, l_file_mask - 1 );
                    strcpy( file + l_file_mask - 1, found_file.cFileName );
                    HANDLE h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
                    if( h_file_cx == INVALID_HANDLE_VALUE )
                    {   printf( "Unable to open file \"%s\".\n", file );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    printf( "Processing file \"%s\"...\n", file );
                    file[ l_file_mask - 1 + l_file - 1 ] = '\0';
                    HANDLE h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   CloseHandle( h_file );
                            ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_1;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file, GetLastError() );
                            CloseHandle( h_file_cx );
                            HeapFree( E_main_S_process_heap, 0, file );
                            FindClose( h_find_file );
                            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                            return 1;
                        }
                    }
                    if( E_main_I_cx_to_c( h_file_cx, h_file ))
                    {   CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_1:             CloseHandle( h_file );
                    unsigned long l_added = 22 + l_file - 2 + 3;
                    char *file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size + l_added );
                    if( !file_h_not_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_not_to_libs_buffer\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                    MoveMemory( file_h_not_to_libs_buffer + l_added, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size );
                    file_h_not_to_libs_buffer_size += l_added;
                    strcpy( file_h_not_to_libs_buffer, "#include \"E_cplus_S_0_" );
                    strncpy( file_h_not_to_libs_buffer + 22, found_file.cFileName, l_file - 2 );
                    strncpy( file_h_not_to_libs_buffer + 22 + l_file - 2, "h\"\n", 3 );
                    char *enc = E_main_Q_filename_I_encode( found_file.cFileName );
                    unsigned long pos = strstr( file_h_not_to_libs_buffer, "#include \"E_cplus_S_language.h\"\n" ) + 32 - file_h_not_to_libs_buffer;
                    unsigned long l_enc = strlen(enc);
                    l_added = 10 + l_enc + 2 + 1;
                    file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size + l_added );
                    if( !file_h_not_to_libs_buffer_ )
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                    char *s = strchr( file_h_not_to_libs_buffer + pos + 15, '\n' ) + 1;
                    MoveMemory( s + l_added, s, file_h_not_to_libs_buffer_size - ( s - file_h_not_to_libs_buffer ));
                    strcpy( s, ", _F_uid( " );
                    strcpy( s + 10, enc );
                    strncpy( s + 10 + l_enc, " )\n", 3 );
                    s += 10 + l_enc + 3 - 1;
                    file_h_not_to_libs_buffer_size += l_added;
                    do
                    {   s = strchr( s, '\n' ) + 1;
                        if( s - file_h_not_to_libs_buffer == file_h_not_to_libs_buffer_size
                        || !strncmp( s, "#include \"E_cplus_S_1_", 22 )
                        )
                            break;
                    }while(TRUE);
                    l_added = 22 + l_file - 2 + 3;
                    file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size + l_added );
                    if( !file_h_not_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_not_to_libs_buffer\"." );
                        HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    s = file_h_not_to_libs_buffer_ + ( s - file_h_not_to_libs_buffer );
                    file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                    MoveMemory( s + l_added, s, file_h_not_to_libs_buffer_size - ( s - file_h_not_to_libs_buffer ));
                    file_h_not_to_libs_buffer_size += l_added;
                    strcpy( s, "#include \"E_cplus_S_1_" );
                    strncpy( s + 22, found_file.cFileName, l_file - 2 );
                    strncpy( s + 22 + l_file - 2, "h\"\n", 3 );
                    s += 22 + l_file - 2 + 3 - 1;
                    do
                    {   s = strchr( s, '\n' ) + 1;
                        if( s - file_h_not_to_libs_buffer == file_h_not_to_libs_buffer_size
                        || strncmp( s, "#include \"E_cplus_S_1_", 22 )
                        )
                            break;
                    }while(TRUE);
                    file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size + l_added );
                    if( !file_h_not_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_not_to_libs_buffer\"." );
                        HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    s = file_h_not_to_libs_buffer_ + ( s - file_h_not_to_libs_buffer );
                    file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                    MoveMemory( s + l_added, s, file_h_not_to_libs_buffer_size - ( s - file_h_not_to_libs_buffer ));
                    file_h_not_to_libs_buffer_size += l_added;
                    strcpy( s, "#include \"E_cplus_S_2_" );
                    strncpy( s + 22, found_file.cFileName, l_file - 2 );
                    strncpy( s + 22 + l_file - 2, "h\"\n", 3 );
                    char *file_ = HeapReAlloc( E_main_S_process_heap, 0, file, l_file_mask - 1 + 12 + l_file - 2 + 1 + 1 );
                    if( !file_ )
                    {   puts( "Unable to allocate \"file\"." );
                        HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    file = file_;
                    strcpy( file + l_file_mask - 1, "E_cplus_S_1_" );
                    strncpy( file + l_file_mask - 1 + 12, found_file.cFileName, l_file - 2 );
                    strcpy( file + l_file_mask - 1 + 12 + l_file - 2, "h" );
                    h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_2;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file, GetLastError() );
                            HeapFree( E_main_S_process_heap, 0, enc );
                            CloseHandle( h_file_cx );
                            HeapFree( E_main_S_process_heap, 0, file );
                            FindClose( h_find_file );
                            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                            return 1;
                        }
                    }
                    if( E_main_I_cx_to_h_1( h_file_cx, h_file, file, enc ))
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, enc );
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
                    if( E_main_I_cx_to_h_2( h_file_cx, h_file ))
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_2:             CloseHandle( h_file );
                    file[ l_file_mask - 1 + 10 ] = '2';
                    h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_3;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file, GetLastError() );
                            CloseHandle( h_file_cx );
                            HeapFree( E_main_S_process_heap, 0, file );
                            FindClose( h_find_file );
                            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                            return 1;
                        }
                    }
                    if( E_main_I_cx_to_h_3( h_file_cx, h_file ))
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
                        return 1;
                    }
Cont_3:             CloseHandle( h_file );
                    CloseHandle( h_file_cx );
                    HeapFree( E_main_S_process_heap, 0, file );
                }
            }
        }
    }while( FindNextFile( h_find_file, &found_file ));
    FindClose( h_find_file );
    if( file_h_not_to_libs_buffer_size != file_h_to_libs_buffer_size )
    {   char *file_h_not_to_libs = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + 23 + 1 );
        if( !file_h_not_to_libs )
        {   puts( "Unable to allocate \"file_h_not_to_libs\"." );
            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
            return 1;
        }
        strncpy( file_h_not_to_libs, file_mask, l_file_mask - 1 );
        strcpy( file_h_not_to_libs + l_file_mask - 1, "E_cplus_S_not_to_libs.h" );
        HANDLE h_file_h_not_to_libs = CreateFile( file_h_not_to_libs, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0 );
        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
        if( h_file_h_not_to_libs == INVALID_HANDLE_VALUE )
        {   printf( "Unable to create file \"%s\": %lu.\n", file_h_not_to_libs, GetLastError() );
            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
            return 1;
        }
        unsigned long wrote;
        WriteFile( h_file_h_not_to_libs, file_h_not_to_libs_buffer, file_h_not_to_libs_buffer_size, &wrote, 0 );
        if( wrote != file_h_not_to_libs_buffer_size )
        {   printf( "Unable to write file \"%s\": %lu.\n", file_h_not_to_libs, GetLastError() );
            CloseHandle( h_file_h_not_to_libs );
            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
            return 1;
        }
        CloseHandle( h_file_h_not_to_libs );
    }
    HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs_buffer );
    return 0;
}
int
E_main_I_build( void
){  WIN32_FIND_DATA found_dir;
    HANDLE h_find_dir = FindFirstFile( "..\\module\\*", &found_dir );
    if( h_find_dir == INVALID_HANDLE_VALUE )
    {   puts( "Not found directory \"module\"." );
        return 1;
    }
    char *file_h_to_libs = HeapAlloc( E_main_S_process_heap, 0, 29 + 1 );
    if( !file_h_to_libs )
    {   puts( "Unable to allocate \"file_h_to_libs\"." );
        FindClose( h_find_dir );
        return 1;
    }
    strcpy( file_h_to_libs, "..\\module\\E_cplus_S_to_libs.h" );
    unsigned long file_h_to_libs_buffer_size = 63;
    char *file_h_to_libs_buffer = HeapAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer_size );
    if( !file_h_to_libs_buffer )
    {   HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    strncpy( file_h_to_libs_buffer, "#include \"E_cplus_S_machine.h\"\n#include \"E_cplus_S_language.h\"\n", file_h_to_libs_buffer_size );
    E_main_S_xyi_array_a_n = 0;
    E_main_S_xyi_array_a = HeapAlloc( E_main_S_process_heap, 0, sizeof( char * ) * E_main_S_xyi_array_a_n );
    if( !E_main_S_xyi_array_a )
    {   puts( "Unable to allocate \"E_main_S_xyi_array_a\"" );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    E_main_S_xyi_array_b_n = 0;
    E_main_S_xyi_array_b = HeapAlloc( E_main_S_process_heap, 0, sizeof( char * ) * E_main_S_xyi_array_b_n );
    if( !E_main_S_xyi_array_b )
    {   puts( "Unable to allocate \"E_main_S_xyi_array_b\"" );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    char *pattern = "\\bX_[AB]\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*[),]";
    int error_code;
    PCRE2_SIZE error_offset;
    E_main_S_x_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_x_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "\\bYi_[AB]\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*\\)";
    E_main_S_yi_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_yi_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^(?:(?:enum|struct|union)\\s+)?\\w+\\s+\\**E_.*;";
    E_main_S_enum_struct_union_regex_1 = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_enum_struct_union_regex_1 )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^(enum|struct|union)\\s+E_\\w";
    E_main_S_enum_struct_union_regex_2 = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_enum_struct_union_regex_2 )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^E_\\w+\\(";
    E_main_S_e_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_e_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^D(\\([^)]*\\))";
    E_main_S_d_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_d_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^}[^=;]*";
    E_main_S_def_name_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_def_name_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^}\\s*(\\*)*\\w";
    E_main_S_def_name_asterisk_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_def_name_asterisk_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^((?:(?:enum|struct|union)\\s+)?\\w+\\s+\\(?:\\**E_[^=;]*)[=;]";
    E_main_S_enum_struct_union_regex_3 = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_enum_struct_union_regex_3 )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    E_main_S_3_match_data = pcre2_match_data_create( 3, 0 );
    if( !E_main_S_3_match_data )
    {   puts( "Unable to allocate match data." );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    do
    {   if(( found_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        && found_dir.cFileName[0] != '.'
        )
        {   unsigned long l_dir = strlen( found_dir.cFileName );
            char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
            if( !file_mask )
            {   puts( "Unable to allocate \"file_mask\"." );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                pcre2_code_free( E_main_S_yi_regex );
                pcre2_code_free( E_main_S_x_regex );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                FindClose( h_find_dir );
                return 1;
            }
            strcpy( file_mask, "..\\module\\" );
            strcpy( file_mask + 10, found_dir.cFileName );
            strcpy( file_mask + 10 + l_dir, "\\*.cx" );
            WIN32_FIND_DATA found_file;
            HANDLE h_find_file = FindFirstFile( file_mask, &found_file );
            if( h_find_file == INVALID_HANDLE_VALUE )
            {   printf( "Not found any file with mask \"%s\".\n", file_mask );
                HeapFree( E_main_S_process_heap, 0, file_mask );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                pcre2_code_free( E_main_S_yi_regex );
                pcre2_code_free( E_main_S_x_regex );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                FindClose( h_find_dir );
                return 1;
            }
            HeapFree( E_main_S_process_heap, 0, file_mask );
            do
            {   if( !( found_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
                {   unsigned long l_file = strlen( found_file.cFileName );
                    char *file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + l_file + 1 );
                    if( !file )
                    {   puts( "Unable to allocate \"file\"." );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    strcpy( file, "..\\module\\" );
                    strcpy( file + 10, found_dir.cFileName );
                    file[ 10 + l_dir ] = '\\';
                    strcpy( file + 10 + l_dir + 1, found_file.cFileName );
                    HANDLE h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
                    if( h_file_cx == INVALID_HANDLE_VALUE )
                    {   printf( "Unable to open file \"%s\".\n", file );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    printf( "Processing file \"%s\"...\n", file );
                    file[ 10 + l_dir + 1 + l_file - 1 ] = '\0';
                    HANDLE h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_1;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file, GetLastError() );
                            CloseHandle( h_file_cx );
                            HeapFree( E_main_S_process_heap, 0, file );
                            FindClose( h_find_file );
                            pcre2_match_data_free( E_main_S_3_match_data );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                            pcre2_code_free( E_main_S_def_name_asterisk_regex );
                            pcre2_code_free( E_main_S_def_name_regex );
                            pcre2_code_free( E_main_S_d_regex );
                            pcre2_code_free( E_main_S_e_regex );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                            pcre2_code_free( E_main_S_yi_regex );
                            pcre2_code_free( E_main_S_x_regex );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                            FindClose( h_find_dir );
                            return 1;
                        }
                    }
                    if( E_main_I_cx_to_c( h_file_cx, h_file ))
                    {   CloseHandle( h_file );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_1:             CloseHandle( h_file );
                    unsigned long l_added = 22 + l_dir + 2 + l_file - 2 + 3;
                    char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer, file_h_to_libs_buffer_size + l_added );
                    if( !file_h_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_to_libs_buffer\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    file_h_to_libs_buffer = file_h_to_libs_buffer_;
                    MoveMemory( file_h_to_libs_buffer + l_added, file_h_to_libs_buffer, file_h_to_libs_buffer_size );
                    file_h_to_libs_buffer_size += l_added;
                    strcpy( file_h_to_libs_buffer, "#include \"E_cplus_S_0_" );
                    strcpy( file_h_to_libs_buffer + 22, found_dir.cFileName );
                    strcpy( file_h_to_libs_buffer + 22 + l_dir, "__" );
                    strncpy( file_h_to_libs_buffer + 22 + l_dir + 2, found_file.cFileName, l_file - 2 );
                    strncpy( file_h_to_libs_buffer + 22 + l_dir + 2 + l_file - 2, "h\"\n", 3 );
                    char *path = HeapAlloc( E_main_S_process_heap, 0, l_dir + 1 + l_file + 1 );
                    if( !path )
                    {   puts( "Unable to allocate \"path\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    strcpy( path, found_dir.cFileName );
                    path[ l_dir ] = '\\';
                    strcpy( path + l_dir + 1, found_file.cFileName );
                    char *enc = E_main_Q_filename_I_encode(path);
                    HeapFree( E_main_S_process_heap, 0, path );
                    unsigned long pos = strstr( file_h_to_libs_buffer, "#include \"E_cplus_S_language.h\"\n" ) + 32 - file_h_to_libs_buffer;
                    unsigned long l_enc = strlen(enc);
                    l_added = 10 + l_enc + 2 + 1;
                    if( strncmp( file_h_to_libs_buffer + pos, "enum\n{ _F_uid( ", 15 ))
                        l_added += 4 + 1 + 43;
                    file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer, file_h_to_libs_buffer_size + l_added );
                    if( !file_h_to_libs_buffer_ )
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    file_h_to_libs_buffer = file_h_to_libs_buffer_;
                    if( !strncmp( file_h_to_libs_buffer + pos, "enum\n{ _F_uid( ", 15 ))
                    {   char *s = strchr( file_h_to_libs_buffer + pos + 15, '\n' ) + 1;
                        MoveMemory( s + l_added, s, file_h_to_libs_buffer_size - ( s - file_h_to_libs_buffer ));
                        strcpy( s, ", _F_uid( " );
                        strcpy( s + 10, enc );
                        strncpy( s + 10 + l_enc, " )\n", 3 );
                        pos = s + 10 + l_enc + 3 - file_h_to_libs_buffer - 1;
                    }else
                    {   MoveMemory( file_h_to_libs_buffer + pos + l_added, file_h_to_libs_buffer + pos, file_h_to_libs_buffer_size - pos );
                        strcpy( file_h_to_libs_buffer + pos, "enum\n{ _F_uid( " );
                        strcpy( file_h_to_libs_buffer + pos + 15, enc );
                        strncpy( file_h_to_libs_buffer + pos + 15 + l_enc, " ) = ( ~0 << ( sizeof(int) * 8 / 2 - 1 )) | 1\n", 46 );
                        pos += 15 + l_enc + 46 - 1;
                    }
                    file_h_to_libs_buffer_size += l_added;
                    HeapFree( E_main_S_process_heap, 0, enc );
                    char *s = file_h_to_libs_buffer + pos;
                    do
                    {   s = strchr( s, '\n' ) + 1;
                        if( s - file_h_to_libs_buffer == file_h_to_libs_buffer_size
                        || *s != ','
                        )
                            break;
                    }while(TRUE);
                    l_added = 22 + l_dir + 2 + l_file - 2 + 3;
                    file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer, file_h_to_libs_buffer_size + l_added );
                    if( !file_h_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_to_libs_buffer\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    s = file_h_to_libs_buffer_ + ( s - file_h_to_libs_buffer );
                    file_h_to_libs_buffer = file_h_to_libs_buffer_;
                    MoveMemory( s + l_added, s, file_h_to_libs_buffer_size - ( s - file_h_to_libs_buffer ));
                    file_h_to_libs_buffer_size += l_added;
                    strcpy( s, "#include \"E_cplus_S_1_" );
                    strcpy( s + 22, found_dir.cFileName );
                    strcpy( s + 22 + l_dir, "__" );
                    strncpy( s + 22 + l_dir + 2, found_file.cFileName, l_file - 2 );
                    strncpy( s + 22 + l_dir + 2 + l_file - 2, "h\"\n", 3 );
                    s += 22 + l_dir + 2 + l_file - 2 + 3 - 1;
                    do
                    {   s = strchr( s, '\n' ) + 1;
                        if( s - file_h_to_libs_buffer == file_h_to_libs_buffer_size
                        || strncmp( s, "#include \"E_cplus_S_1_", 22 )
                        )
                            break;
                    }while(TRUE);
                    file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer, file_h_to_libs_buffer_size + l_added );
                    if( !file_h_to_libs_buffer_ )
                    {   puts( "Unable to reallocate \"file_h_to_libs_buffer\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    s = file_h_to_libs_buffer_ + ( s - file_h_to_libs_buffer );
                    file_h_to_libs_buffer = file_h_to_libs_buffer_;
                    MoveMemory( s + l_added, s, file_h_to_libs_buffer_size - ( s - file_h_to_libs_buffer ));
                    file_h_to_libs_buffer_size += l_added;
                    strcpy( s, "#include \"E_cplus_S_2_" );
                    strcpy( s + 22, found_dir.cFileName );
                    strcpy( s + 22 + l_dir, "__" );
                    strncpy( s + 22 + l_dir + 2, found_file.cFileName, l_file - 2 );
                    strncpy( s + 22 + l_dir + 2 + l_file - 2, "h\"\n", 3 );
                    if( E_main_I_cx_to_xyi_array( h_file_cx ))
                    {   CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );

                    CloseHandle( h_file_cx );
                    HeapFree( E_main_S_process_heap, 0, file );
                }
            }while( FindNextFile( h_find_file, &found_file ));
            FindClose( h_find_file );
        }
    }while( FindNextFile( h_find_dir, &found_dir ));
    FindClose( h_find_dir );
    pattern = "\\b(?:X|Yi)_B\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*[),]";
    E_main_S_h_xyi_regex_b = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_h_xyi_regex_b )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^\\s*#(?:if|(?:elif|else|endif)\\b)";
    E_main_S_preproc_if_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_preproc_if_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    pattern = "^(?:struct|union)\\s+E_\\w+";
    E_main_S_struct_union_regex = pcre2_compile( pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !E_main_S_struct_union_regex )
    {   printf( "Unable to compile regex \"%s\".\n", pattern );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        FindClose( h_find_dir );
        return 1;
    }
    h_find_dir = FindFirstFile( "..\\module\\*", &found_dir );
    if( h_find_dir == INVALID_HANDLE_VALUE )
    {   puts( "Not found directory \"module\"." );
        pcre2_code_free( E_main_S_struct_union_regex );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        pcre2_code_free( E_main_S_yi_regex );
        pcre2_code_free( E_main_S_x_regex );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        return 1;
    }
    do
    {   if(( found_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        && found_dir.cFileName[0] != '.'
        )
        {   unsigned long l_dir = strlen( found_dir.cFileName );
            char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
            if( !file_mask )
            {   puts( "Unable to allocate \"file_mask\"." );
                pcre2_code_free( E_main_S_struct_union_regex );
                pcre2_code_free( E_main_S_preproc_if_regex );
                pcre2_code_free( E_main_S_h_xyi_regex_b );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                pcre2_code_free( E_main_S_yi_regex );
                pcre2_code_free( E_main_S_x_regex );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                FindClose( h_find_dir );
                return 1;
            }
            strcpy( file_mask, "..\\module\\" );
            strcpy( file_mask + 10, found_dir.cFileName );
            strcpy( file_mask + 10 + l_dir, "\\*.cx" );
            WIN32_FIND_DATA found_file;
            HANDLE h_find_file = FindFirstFile( file_mask, &found_file );
            if( h_find_file == INVALID_HANDLE_VALUE )
            {   printf( "Not found any file with mask \"%s\".\n", file_mask );
                HeapFree( E_main_S_process_heap, 0, file_mask );
                pcre2_code_free( E_main_S_struct_union_regex );
                pcre2_code_free( E_main_S_preproc_if_regex );
                pcre2_code_free( E_main_S_h_xyi_regex_b );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                pcre2_code_free( E_main_S_yi_regex );
                pcre2_code_free( E_main_S_x_regex );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                FindClose( h_find_dir );
                return 1;
            }
            HeapFree( E_main_S_process_heap, 0, file_mask );
            do
            {   if( !( found_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
                {   unsigned long l_file = strlen( found_file.cFileName );
                    char *file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + l_file + 1 );
                    if( !file )
                    {   puts( "Unable to allocate \"file\"." );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    strcpy( file, "..\\module\\" );
                    strcpy( file + 10, found_dir.cFileName );
                    file[ 10 + l_dir ] = '\\';
                    strcpy( file + 10 + l_dir + 1, found_file.cFileName );
                    HANDLE h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
                    if( h_file_cx == INVALID_HANDLE_VALUE )
                    {   printf( "Unable to open file \"%s\".\n", file );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    printf( "Processing file \"%s\"...\n", file );
                    char *file_h = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2 + 1 + 1 );
                    if( !file_h )
                    {   puts( "Unable to allocate \"file_h_1\"." );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    strncpy( file_h, file, 10 + l_dir + 1 );
                    strcpy( file_h + 10 + l_dir + 1, "E_cplus_S_1_" );
                    strcpy( file_h + 10 + l_dir + 1 + 12, found_dir.cFileName );
                    strcpy( file_h + 10 + l_dir + 1 + 12 + l_dir, "__" );
                    strncpy( file_h + 10 + l_dir + 1 + 12 + l_dir + 2, found_file.cFileName, l_file - 2 );
                    strcpy( file_h + 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2, "h" );
                    HANDLE h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_2;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file_h, GetLastError() );
                            HeapFree( E_main_S_process_heap, 0, file_h );
                            CloseHandle( h_file_cx );
                            HeapFree( E_main_S_process_heap, 0, file );
                            FindClose( h_find_file );
                            pcre2_code_free( E_main_S_struct_union_regex );
                            pcre2_code_free( E_main_S_preproc_if_regex );
                            pcre2_code_free( E_main_S_h_xyi_regex_b );
                            pcre2_match_data_free( E_main_S_3_match_data );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                            pcre2_code_free( E_main_S_def_name_asterisk_regex );
                            pcre2_code_free( E_main_S_def_name_regex );
                            pcre2_code_free( E_main_S_d_regex );
                            pcre2_code_free( E_main_S_e_regex );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                            pcre2_code_free( E_main_S_yi_regex );
                            pcre2_code_free( E_main_S_x_regex );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                            FindClose( h_find_dir );
                            return 1;
                        }
                    }
                    char *enc = E_main_Q_filename_I_encode( file + 10 );
                    if( E_main_I_cx_to_h_1( h_file_cx, h_file, file, enc ))
                    {   HeapFree( E_main_S_process_heap, 0, enc );
                        CloseHandle( h_file );
                        HeapFree( E_main_S_process_heap, 0, file_h );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, enc );
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
                    if( E_main_I_cx_to_h_2( h_file_cx, h_file ))
                    {   CloseHandle( h_file );
                        HeapFree( E_main_S_process_heap, 0, file_h );
                        CloseHandle( h_file_cx );
                        HeapFree( E_main_S_process_heap, 0, file );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
                    SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_2:             HeapFree( E_main_S_process_heap, 0, file );
                    CloseHandle( h_file );
                    file_h[ 10 + l_dir + 1 + 10 ] = '2';
                    h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                    if( h_file != INVALID_HANDLE_VALUE )
                    {   FILETIME file_time;
                        if( GetFileTime( h_file, 0, 0, &file_time ))
                        {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                            file_cx_time_u.LowPart = found_file.ftLastWriteTime.dwLowDateTime;
                            file_cx_time_u.HighPart = found_file.ftLastWriteTime.dwHighDateTime;
                            file_time_u.LowPart = file_time.dwLowDateTime;
                            file_time_u.HighPart = file_time.dwHighDateTime;
                            if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                                goto Cont_3;
                            SetEndOfFile( h_file );
                        }
                    }else
                    {   h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                        if( h_file == INVALID_HANDLE_VALUE )
                        {   printf( "Unable to create file \"%s\": %lu.\n", file_h, GetLastError() );
                            HeapFree( E_main_S_process_heap, 0, file_h );
                            CloseHandle( h_file_cx );
                            FindClose( h_find_file );
                            pcre2_code_free( E_main_S_struct_union_regex );
                            pcre2_code_free( E_main_S_preproc_if_regex );
                            pcre2_code_free( E_main_S_h_xyi_regex_b );
                            pcre2_match_data_free( E_main_S_3_match_data );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                            pcre2_code_free( E_main_S_def_name_asterisk_regex );
                            pcre2_code_free( E_main_S_def_name_regex );
                            pcre2_code_free( E_main_S_d_regex );
                            pcre2_code_free( E_main_S_e_regex );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                            pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                            pcre2_code_free( E_main_S_yi_regex );
                            pcre2_code_free( E_main_S_x_regex );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                            for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                            HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                            FindClose( h_find_dir );
                            return 1;
                        }
                    }
                    if( E_main_I_cx_to_h_3( h_file_cx, h_file ))
                    {   CloseHandle( h_file );
                        HeapFree( E_main_S_process_heap, 0, file_h );
                        CloseHandle( h_file_cx );
                        FindClose( h_find_file );
                        pcre2_code_free( E_main_S_struct_union_regex );
                        pcre2_code_free( E_main_S_preproc_if_regex );
                        pcre2_code_free( E_main_S_h_xyi_regex_b );
                        pcre2_match_data_free( E_main_S_3_match_data );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                        pcre2_code_free( E_main_S_def_name_asterisk_regex );
                        pcre2_code_free( E_main_S_def_name_regex );
                        pcre2_code_free( E_main_S_d_regex );
                        pcre2_code_free( E_main_S_e_regex );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                        pcre2_code_free( E_main_S_yi_regex );
                        pcre2_code_free( E_main_S_x_regex );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
                        FindClose( h_find_dir );
                        return 1;
                    }
Cont_3:             CloseHandle( h_file );
                    HeapFree( E_main_S_process_heap, 0, file_h );
                    CloseHandle( h_file_cx );
                }
            }while( FindNextFile( h_find_file, &found_file ));
            FindClose( h_find_file );
        }
    }while( FindNextFile( h_find_dir, &found_dir ));
    FindClose( h_find_dir );
    pcre2_code_free( E_main_S_yi_regex );
    pcre2_code_free( E_main_S_x_regex );
    unsigned long l_added = 3;
    if( E_main_S_xyi_array_a_n )
    {   for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
             for( unsigned long j = 0; j != E_main_S_xyi_array_b_n; j++ )
                  if( !strcmp( E_main_S_xyi_array_a[i], E_main_S_xyi_array_b[j] ))
                  {   HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                      E_main_S_xyi_array_a[i] = 0;
                      break;
                  }
        unsigned long i;
        for( i = 0; i != E_main_S_xyi_array_a_n; i++ )
             if( E_main_S_xyi_array_a[i] )
                 break;
        if( i == E_main_S_xyi_array_a_n )
            E_main_S_xyi_array_a_n = 0;
        else
        {   unsigned long l = strlen( E_main_S_xyi_array_a[i] );
            l_added += 17 + l + 49 + 3;
            char *s = strstr( file_h_to_libs_buffer, "enum\n{ _F_uid( " ) + 5;
            do
            {   s = strchr( s + 10, '\n' ) + 1;
                if( s - file_h_to_libs_buffer == file_h_to_libs_buffer_size
                || *s != ','
                )
                    break;
            }while(TRUE);
            for( i++; i != E_main_S_xyi_array_a_n; i++ )
                if( E_main_S_xyi_array_a[i] )
                    l_added += 12 + strlen( E_main_S_xyi_array_a[i] ) + 2;
        }
    }
    char *s = strstr( file_h_to_libs_buffer, "enum\n{ _F_uid( " ) + 5;
    do
    {   s = strchr( s + 10, '\n' ) + 1;
        if( s - file_h_to_libs_buffer == file_h_to_libs_buffer_size
        || *s != ','
        )
            break;
    }while(TRUE);
    char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, file_h_to_libs_buffer, file_h_to_libs_buffer_size + l_added );
    if( !file_h_to_libs_buffer_ )
    {   puts( "Unable to reallocate \"file_h_to_libs_buffer\"." );
        pcre2_code_free( E_main_S_struct_union_regex );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            if( E_main_S_xyi_array_a[i] )
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        return 1;
    }
    s = file_h_to_libs_buffer_ + ( s - file_h_to_libs_buffer );
    file_h_to_libs_buffer = file_h_to_libs_buffer_;
    MoveMemory( s + 3, s, file_h_to_libs_buffer_size - ( s - file_h_to_libs_buffer ));
    file_h_to_libs_buffer_size += 3;
    strncpy( s, "};\n", 3 );
    if( E_main_S_xyi_array_a_n )
    {   s += 3;
        l_added -= 3;
        unsigned long i;
        for( i = 0; i != E_main_S_xyi_array_a_n; i++ )
            if( E_main_S_xyi_array_a[i] )
                break;
        unsigned long l = strlen( E_main_S_xyi_array_a[i] );
        MoveMemory( s + l_added, s, file_h_to_libs_buffer_size - ( s - file_h_to_libs_buffer ));
        file_h_to_libs_buffer_size += l_added;
        strcpy( s, "enum\n{ _XhYi_uid(" );
        strcpy( s + 17, E_main_S_xyi_array_a[i] );
        strncpy( s + 17 + l, ") = _F_uid_v( ~0 << ( sizeof(int) * 8 / 2 - 1 ))\n", 49 );
        s += 17 + l + 49;
        for( i++; i != E_main_S_xyi_array_a_n; i++ )
        {   if( !E_main_S_xyi_array_a[i] )
                continue; 
            strcpy( s, ", _XhYi_uid(" );
            strcpy( s + 12, E_main_S_xyi_array_a[i] );
            unsigned long l = strlen( E_main_S_xyi_array_a[i] );
            strcpy( s + 12 + l, ")\n" );
            s += 12 + l + 2;
        }
        strncpy( s, "};\n", 3 );
    }
    HANDLE h_file_h_to_libs = CreateFile( file_h_to_libs, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0 );
    if( h_file_h_to_libs == INVALID_HANDLE_VALUE )
    {   printf( "Unable to create file \"%s\": %lu.\n", file_h_to_libs, GetLastError() );
        pcre2_code_free( E_main_S_struct_union_regex );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            if( E_main_S_xyi_array_a[i] )
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        return 1;
    }
    unsigned long wrote;
    WriteFile( h_file_h_to_libs, file_h_to_libs_buffer, file_h_to_libs_buffer_size, &wrote, 0 );
    if( wrote != file_h_to_libs_buffer_size )
    {   printf( "Unable to write file \"%s\": %lu.\n", file_h_to_libs, GetLastError() );
        pcre2_code_free( E_main_S_struct_union_regex );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        CloseHandle( h_file_h_to_libs );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            if( E_main_S_xyi_array_a[i] )
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        return 1;
    }
    CloseHandle( h_file_h_to_libs );
    HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
    h_find_dir = FindFirstFile( "..\\program\\*", &found_dir );
    if( h_find_dir == INVALID_HANDLE_VALUE )
    {   puts( "Not found directory \"program\"." );
        pcre2_code_free( E_main_S_struct_union_regex );
        pcre2_code_free( E_main_S_preproc_if_regex );
        pcre2_code_free( E_main_S_h_xyi_regex_b );
        pcre2_match_data_free( E_main_S_3_match_data );
        pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
        pcre2_code_free( E_main_S_def_name_asterisk_regex );
        pcre2_code_free( E_main_S_def_name_regex );
        pcre2_code_free( E_main_S_d_regex );
        pcre2_code_free( E_main_S_e_regex );
        pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
        pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
        for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
        for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
            if( E_main_S_xyi_array_a[i] )
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
        HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
        return 1;
    }
    do
    {   if(( found_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        && found_dir.cFileName[0] != '.'
        )
        {   unsigned long l_dir = strlen( found_dir.cFileName );
            char *file_h_not_to_libs = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 24 + 1 );
            if( !file_h_not_to_libs )
            {   puts( "Unable to allocate \"file_h_not_to_libs\"." );
                FindClose( h_find_dir );
                pcre2_code_free( E_main_S_struct_union_regex );
                pcre2_code_free( E_main_S_preproc_if_regex );
                pcre2_code_free( E_main_S_h_xyi_regex_b );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    if( E_main_S_xyi_array_a[i] )
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                return 1;
            }
            strcpy( file_h_not_to_libs, "..\\program\\" );
            strcpy( file_h_not_to_libs + 11, found_dir.cFileName );
            strcpy( file_h_not_to_libs + 11 + l_dir, "\\E_cplus_S_not_to_libs.h" );
            DeleteFile( file_h_not_to_libs );
            HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
            char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 2 + 1 );
            strcpy( file_mask, "..\\program\\" );
            strcpy( file_mask + 11, found_dir.cFileName );
            strcpy( file_mask + 11 + l_dir, "\\*" );
            if( E_main_I_build_programs( file_mask, file_h_to_libs_buffer, file_h_to_libs_buffer_size ))
            {   HeapFree( E_main_S_process_heap, 0, file_mask );
                FindClose( h_find_dir );
                pcre2_code_free( E_main_S_struct_union_regex );
                pcre2_code_free( E_main_S_preproc_if_regex );
                pcre2_code_free( E_main_S_h_xyi_regex_b );
                pcre2_match_data_free( E_main_S_3_match_data );
                pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
                pcre2_code_free( E_main_S_def_name_asterisk_regex );
                pcre2_code_free( E_main_S_def_name_regex );
                pcre2_code_free( E_main_S_d_regex );
                pcre2_code_free( E_main_S_e_regex );
                pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
                pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
                for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
                    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
                for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
                    if( E_main_S_xyi_array_a[i] )
                        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
                HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
                HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
                return 1;
            }
            HeapFree( E_main_S_process_heap, 0, file_mask );
        }
    }while( FindNextFile( h_find_dir, &found_dir ));
    FindClose( h_find_dir );
    pcre2_code_free( E_main_S_struct_union_regex );
    pcre2_code_free( E_main_S_preproc_if_regex );
    pcre2_code_free( E_main_S_h_xyi_regex_b );
    pcre2_match_data_free( E_main_S_3_match_data );
    pcre2_code_free( E_main_S_enum_struct_union_regex_3 );
    pcre2_code_free( E_main_S_def_name_asterisk_regex );
    pcre2_code_free( E_main_S_def_name_regex );
    pcre2_code_free( E_main_S_d_regex );
    pcre2_code_free( E_main_S_e_regex );
    pcre2_code_free( E_main_S_enum_struct_union_regex_2 );
    pcre2_code_free( E_main_S_enum_struct_union_regex_1 );
    for( unsigned long i = 0; i != E_main_S_xyi_array_b_n; i++ )
        HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b[i] );
    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_b );
    for( unsigned long i = 0; i != E_main_S_xyi_array_a_n; i++ )
        if( E_main_S_xyi_array_a[i] )
            HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a[i] );
    HeapFree( E_main_S_process_heap, 0, E_main_S_xyi_array_a );
    HeapFree( E_main_S_process_heap, 0, file_h_to_libs_buffer );
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
E_main_I_clean_programs( char *file_mask
){  WIN32_FIND_DATA found_file;
    HANDLE h_find_file = FindFirstFile( file_mask, &found_file );
    if( h_find_file == INVALID_HANDLE_VALUE )
    {   printf( "Not found directory for mask \"%s\".", file_mask );
        return 1;
    }
    do
    {   if( found_file.cFileName[0] != '.' )
        {   if( found_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            {   unsigned long l_file_mask = strlen( file_mask );
                char *file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + 23 + 1 );
                strncpy( file, file_mask, l_file_mask - 1 );
                strcpy( file + l_file_mask - 1, "E_cplus_S_not_to_libs.h" );
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                HeapFree( E_main_S_process_heap, 0, file );
                unsigned long l_dir = strlen( found_file.cFileName );
                char *file_mask_ = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_dir + 2 + 1 );
                strncpy( file_mask_, file_mask, l_file_mask - 1 );
                strcpy( file_mask_ + l_file_mask - 1, found_file.cFileName );
                strcpy( file_mask_ + l_file_mask - 1 + l_dir, "\\*" );
                if( E_main_I_clean_programs( file_mask_ ))
                {   HeapFree( E_main_S_process_heap, 0, file_mask_ );
                    FindClose( h_find_file );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, file_mask_ );
            }else
            {   unsigned long l_file = strlen( found_file.cFileName );
                if( l_file > 3
                && !strcmp( found_file.cFileName + l_file - 3, ".cx" )
                )
                {   unsigned long l_file_mask = strlen( file_mask );
                    unsigned long l_file = strlen( found_file.cFileName );
                    char *file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_file + 1 );
                    if( !file )
                    {   puts( "Unable to allocate \"file\"." );
                        FindClose( h_find_file );
                        return 1;
                    }
                    strncpy( file, file_mask, l_file_mask - 1 );
                    strncpy( file + l_file_mask - 1, found_file.cFileName, l_file - 1 );
                    file[ l_file_mask - 1 + l_file - 1 ] = '\0';
                    printf( "Removing file \"%s\"...\n", file );
                    DeleteFile(file);
                    HeapFree( E_main_S_process_heap, 0, file );
                    char *file_h = HeapAlloc( E_main_S_process_heap, 0, 12 + l_file - 1 + 1 );
                    if( !file_h )
                    {   puts( "Unable to allocate \"file_h\"." );
                        FindClose( h_find_file );
                        return 1;
                    }
                    strcpy( file_h, "E_cplus_S_0_" );
                    strncpy( file_h + 12, found_file.cFileName, l_file - 2 );
                    strcpy( file_h + 12 + l_file - 2, "h" );
                    printf( "Removing file \"%s\"...\n", file_h );
                    DeleteFile( file_h );
                    file_h[10] = '1';
                    printf( "Removing file \"%s\"...\n", file_h );
                    DeleteFile( file_h );
                    file_h[10] = '2';
                    printf( "Removing file \"%s\"...\n", file_h );
                    DeleteFile( file_h );
                    HeapFree( E_main_S_process_heap, 0, file_h );
                    puts( "1" );
                }
            }
        }
    }while( FindNextFile( h_find_file, &found_file ));
    FindClose( h_find_file );
    return 0;
}
int
E_main_I_clean( void
){  WIN32_FIND_DATA found_dir;
    HANDLE h_find_dir = FindFirstFile( "..\\module\\*", &found_dir );
    if( h_find_dir == INVALID_HANDLE_VALUE )
        puts( "Not found directory \"module\"." );
    else
    {   puts( "Removing file \"..\\module\\E_cplus_S_to_libs.h\"..." );
        DeleteFile( "..\\module\\E_cplus_S_to_libs.h" );
        do
        {   if(( found_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            && found_dir.cFileName[0] != '.'
            )
            {   unsigned long l_dir = strlen( found_dir.cFileName );
                char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
                strcpy( file_mask, "..\\module\\" );
                strcpy( file_mask + 10, found_dir.cFileName );
                strcpy( file_mask + 10 + l_dir, "\\*.cx" );
                WIN32_FIND_DATA found_file;
                HANDLE h_find_file = FindFirstFile( file_mask, &found_file );
                if( h_find_file == INVALID_HANDLE_VALUE )
                {   printf( "Not found any file with mask \"%s\".\n", file_mask );
                    HeapFree( E_main_S_process_heap, 0, file_mask );
                    FindClose( h_find_dir );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, file_mask );
                do
                {   if( !( found_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
                    {   unsigned long l_file = strlen( found_file.cFileName );
                        char *file = HeapAlloc( E_main_S_process_heap, 0, 7 + l_dir + 1 + l_file - 1 + 1 );
                        if( !file )
                        {   puts( "Unable to allocate \"file\"." );
                            FindClose( h_find_file );
                            FindClose( h_find_dir );
                            return 1;
                        }
                        strcpy( file, "..\\module\\" );
                        strcpy( file + 10, found_dir.cFileName );
                        file[ 10 + l_dir ] = '\\';
                        strncpy( file + 10 + l_dir + 1, found_file.cFileName, l_file - 1 );
                        file[ 10 + l_dir + 1 + l_file - 1 ] = '\0';
                        printf( "Removing file \"%s\"...\n", file );
                        DeleteFile(file);
                        HeapFree( E_main_S_process_heap, 0, file );
                        file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2 + 1 + 1 );
                        if( !file )
                        {   puts( "Unable to allocate \"file\"." );
                            FindClose( h_find_file );
                            FindClose( h_find_dir );
                            return 1;
                        }
                        strcpy( file, "..\\module\\" );
                        strcpy( file + 10, found_dir.cFileName );
                        file[ 10 + l_dir ] = '\\';
                        strcpy( file + 10 + l_dir + 1, "E_cplus_S_0_" );
                        strcpy( file + 10 + l_dir + 1 + 12, found_dir.cFileName );
                        strcpy( file + 10 + l_dir + 1 + 12 + l_dir, "__" );
                        strncpy( file + 10 + l_dir + 1 + 12 + l_dir + 2, found_file.cFileName, l_file - 2 );
                        strcpy( file + 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2, "h" );
                        printf( "Removing file \"%s\"...\n", file );
                        DeleteFile( file );
                        file[ 10 + l_dir + 1 + 10 ] = '1';
                        printf( "Removing file \"%s\"...\n", file );
                        DeleteFile( file );
                        file[ 10 + l_dir + 1 + 10 ] = '2';
                        printf( "Removing file \"%s\"...\n", file );
                        DeleteFile( file );
                        HeapFree( E_main_S_process_heap, 0, file );
                    }
                }while( FindNextFile( h_find_file, &found_file ));
                FindClose( h_find_file );
            }
        }while( FindNextFile( h_find_dir, &found_dir ));
        FindClose( h_find_dir );
    }
    h_find_dir = FindFirstFile( "..\\program\\*", &found_dir );
    if( h_find_dir == INVALID_HANDLE_VALUE )
        puts( "Not found directory \"program\"." );
    else
    {   do
        {   if(( found_dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            && found_dir.cFileName[0] != '.'
            )
            {   unsigned long l_dir = strlen( found_dir.cFileName );
                char *file = HeapAlloc( E_main_S_process_heap, 0, 11 + 23 + 1 );
                strcpy( file, "..\\program\\" );
                strcpy( file + 11, found_dir.cFileName );
                strcpy( file + 11 + l_dir, "\\E_cplus_S_not_to_libs.h" );
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                HeapFree( E_main_S_process_heap, 0, file );
                char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 2 + 1 );
                strcpy( file_mask, "..\\program\\" );
                strcpy( file_mask + 11, found_dir.cFileName );
                strcpy( file_mask + 11 + l_dir, "\\*" );
                if( E_main_I_clean_programs( file_mask ))
                {   HeapFree( E_main_S_process_heap, 0, file_mask );
                    FindClose( h_find_dir );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, file_mask );
            }
        }while( FindNextFile( h_find_dir, &found_dir ));
        FindClose( h_find_dir );
    }
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
E_main_I_run( void
){
    return 0;
}
//==============================================================================
enum E_main_Z_func                                                                                                                        
{ E_main_Z_func_S_build
, E_main_Z_func_S_clean
, E_main_Z_func_S_run
};
int
main( int argc
, char *argv[]
){  if( argc > 2 )
        return 1;
    enum E_main_Z_func func;
    if( argc == 1 )
        func = E_main_Z_func_S_build;
    else if( strcmp( argv[1], "all" ) == 0
    || strcmp( argv[1], "build" ) == 0
    )
        func = E_main_Z_func_S_build;
    else if( strcmp( argv[1], "clean" ) == 0 )
        func = E_main_Z_func_S_clean;
    else if( strcmp( argv[1], "run" ) == 0 )
        func = E_main_Z_func_S_run;
    else
        return 1;
    E_main_S_process_heap = GetProcessHeap();
    int ret;
    if( func == E_main_Z_func_S_build )
        ret = E_main_I_build();
    else if( func == E_main_Z_func_S_clean )
        ret = E_main_I_clean();
    else
        ret = E_main_I_run();
    return ret;
}
//******************************************************************************

