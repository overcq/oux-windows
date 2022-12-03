/*******************************************************************************
*  ___   publicplace
* |OUX|  C
* |/C+|  make
*  ---   make oux
*        main
* (c)overcq                       on Windows XP                     2022-08-21 *
*******************************************************************************/
#include <stdio.h>
#include <windows.h>
#define PCRE2_STATIC 1
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
//==============================================================================
HANDLE E_main_S_process_heap;
//==============================================================================
int
E_main_Q_c_I_isupper( char c
){  return c >= 'A'
    && c <= 'Z';
}
int
E_main_Q_c_I_islower( char c
){  return c >= 'a'
    && c <= 'z';
}
int
E_main_Q_c_I_isalpha( char c
){  return E_main_Q_c_I_isupper(c)
    || E_main_Q_c_I_islower(c);
}
int
E_main_Q_c_I_isdigit( char c
){  return c >= '0'
    && c <= '9';
}
int
E_main_Q_c_I_isalnum( char c
){  return E_main_Q_c_I_isalpha(c)
    || E_main_Q_c_I_isdigit(c);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long
E_main_Q_s0_R_strlen( char *s
){  unsigned long ret = 0;
    while( *s )
    {   ret++;
        s++;
    }
    return ret;
}
int
E_main_Q_s0_s0_I_strcmp( char *s
, char *t
){  while( *s
    && *t
    && *s == *t
    )
    {  s++;
       t++;
    }
   return *s - *t;
}
int
E_main_Q_s0_s0_I_strncmp( char *s
, char *t
, unsigned long n
){  while( n
    && *s
    && *t
    && *s == *t
    )
    {  n--;
       s++;
       t++;
    }
   return !n ? 0 : *s - *t;
}
char *
E_main_Q_s0_I_strchr( char *s
, char c
){  while( *s
    && *s != c
    )
        s++;
    return *s ? s : 0;
}
char *
E_main_Q_s0_I_strstr( char *s
, char *t
){  char *s_, *t_ = t;
    while( *s
    && *t_
    )
    {   if( *s == *t_ )
        {   if( t_ == t )
                s_ = s;
            t_++;
        }else
            t_ = t;
        s++;
    }
    return !*t_ ? s_ : 0;
}
char *
E_main_Q_s_s0_I_strcpy( char *s
, char *t
){  char *s_ = s;
    do
    {   *s_ = *t;
        s_++;
    }while( *t++ );
    return s;
}
//==============================================================================
#define V(value,msg) if( (value) || ( E_main_I_check_winapi_error_internal( __LINE__, msg), FALSE )){}else
#define Vv(value,msg) if( (value) || ( E_main_I_check_winapi_error_v_internal( __LINE__, msg, #value, ( unsigned long )value ), FALSE )){}else
void
E_main_I_check_winapi_error_internal( int line
, char *msg
){  unsigned long e = GetLastError();
    fprintf( stderr, "In line %d: %s", line, msg );
    char *s;
    if( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, 0, e, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), ( LPTSTR )&s, 0, 0 ))
    {   fprintf( stderr, "\nUnable to format message: %lu.\n", GetLastError() );
        return;
    }
    fprintf( stderr, ": (%lu) %s", e, s );
    LocalFree(s);
}
void
E_main_I_check_winapi_error_v_internal( int line
, char *msg
, char *name
, unsigned long value
){  unsigned long e = GetLastError();
    fprintf( stderr, "In line %d: %s: %s = %lu", line, msg, name, value );
    char *s;
    if( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, 0, e, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), ( LPTSTR )&s, 0, 0 ))
    {   fprintf( stderr, "\nUnable to format message: %lu.\n", GetLastError() );
        return;
    }
    fprintf( stderr, ": (%lu) %s", e, s );
    LocalFree(s);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct E_main_Z_build_resources
{ unsigned long file_h_to_libs_buffer_size, file_h_not_to_libs_buffer_size;
  char *file_h_to_libs_buffer, *file_h_not_to_libs_buffer;
  unsigned long xyi_array_a_n, xyi_array_b_n;
  char **xyi_array_a, **xyi_array_b;
  pcre2_code *x_regex, *yi_regex, *enum_struct_union_regex_1, *enum_struct_union_regex_2, *enum_struct_union_regex_3, *e_regex, *d_regex, *def_name_regex, *def_name_asterisk_regex, *h_xyi_regex_b, *preproc_if_regex, *struct_union_regex;
  pcre2_match_data *_3_match_data;
  char *found_dir;
};
pcre2_code *
E_main_Q_pcre2_code_M( char *pattern
){  int error_code;
    PCRE2_SIZE error_offset;
    pcre2_code *ret = pcre2_compile(( PCRE2_SPTR8 )pattern, PCRE2_ZERO_TERMINATED, 0, &error_code, &error_offset, 0 );
    if( !ret )
    {   fputs( "pcre2 error:\n", stderr );
        int ret_e = pcre2_get_error_message( error_code, 0, 0 );
        if( ret_e != -PCRE2_ERROR_NOMEMORY )
        {   fputs( "Unable to get error message.\n", stderr );
            return ret;
        }
        char *s = HeapAlloc( E_main_S_process_heap, 0, ret_e );
        Vv( s, "Unable to allocate error message" )
            return ret;
        ret_e = pcre2_get_error_message( error_code, ( PCRE2_UCHAR8 * )s, ret_e );
        if( ret_e < 0 )
        {   fputs( "Unable to get error message.\n", stderr );
            HeapFree( E_main_S_process_heap, 0, s );
            return ret;
        }
        fprintf( stderr, "%s in pos %zd\n", s, error_offset );
        HeapFree( E_main_S_process_heap, 0, s );
    }
    return ret;
}
int
E_main_Q_build_resources_M( struct E_main_Z_build_resources *data
){  ZeroMemory( data, sizeof( *data ));
    data->file_h_to_libs_buffer_size = 147;
    data->file_h_to_libs_buffer = HeapAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer_size );
    Vv( data->file_h_to_libs_buffer, "Unable to allocate" )
        return 1;
    CopyMemory( data->file_h_to_libs_buffer, "#include <windows.h>\r\n#include \"E_cplus_S_machine.h\"\r\n#include \"E_cplus_S_language.h\"\r\n#include \"E_cplus_S_simple.h\"\r\n#include \"E_cplus_S_base.h\"\r\n", data->file_h_to_libs_buffer_size );
    data->xyi_array_a = HeapAlloc( E_main_S_process_heap, 0, 0 );
    Vv( data->xyi_array_a, "Unable to allocate" )
        return 1;
    data->xyi_array_b = HeapAlloc( E_main_S_process_heap, 0, 0 );
    Vv( data->xyi_array_b, "Unable to allocate" )
        return 1;
    data->x_regex = E_main_Q_pcre2_code_M( "\\bX_[AB]\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*[),]" );
    if( !data->x_regex )
        return 1;
    data->yi_regex = E_main_Q_pcre2_code_M( "\\bYi_[AB]\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*\\)" );
    if( !data->yi_regex )
        return 1;
    data->enum_struct_union_regex_1 = E_main_Q_pcre2_code_M( "^(?:(?:enum|struct|union)\\s+)?\\w+\\s+\\**E_.*;" );
    if( !data->enum_struct_union_regex_1 )
        return 1;
    data->enum_struct_union_regex_2 = E_main_Q_pcre2_code_M( "^(enum|struct|union)\\s+E_\\w" );
    if( !data->enum_struct_union_regex_2 )
        return 1;
    data->e_regex = E_main_Q_pcre2_code_M( "^E_\\w+\\(" );
    if( !data->e_regex )
        return 1;
    data->d_regex = E_main_Q_pcre2_code_M( "^D(\\([^)]*\\))" );
    if( !data->d_regex )
        return 1;
    data->def_name_regex = E_main_Q_pcre2_code_M( "^}[^=;]*" );
    if( !data->def_name_regex )
        return 1;
    data->def_name_asterisk_regex = E_main_Q_pcre2_code_M( "^}\\s*(\\*)*\\w" );
    if( !data->def_name_asterisk_regex )
        return 1;
    data->enum_struct_union_regex_3 = E_main_Q_pcre2_code_M( "^((?:(?:enum|struct|union)\\s+)?\\w+\\s+\\(?\\**E_[^=;]*)[=;]" );
    if( !data->enum_struct_union_regex_3 )
        return 1;
    data->h_xyi_regex_b = E_main_Q_pcre2_code_M( "\\b(?:X|Yi)_B\\(\\s*(\\w+)\\s*,\\s*(\\w+)\\s*[),]" );
    if( !data->h_xyi_regex_b )
        return 1;
    data->preproc_if_regex = E_main_Q_pcre2_code_M( "^\\s*#(?:if|(?:elif|else|endif)\\b)" );
    if( !data->preproc_if_regex )
        return 1;
    data->struct_union_regex = E_main_Q_pcre2_code_M( "^(?:struct|union)\\s+E_\\w+" );
    if( !data->struct_union_regex )
        return 1;
    data->_3_match_data = pcre2_match_data_create( 3, 0 );
    if( !data->_3_match_data )
    {   fputs( "Unable to allocate match data.\n", stderr );
        return 1;
    }
    return 0;
}
void
E_main_Q_build_resources_W( struct E_main_Z_build_resources *data
){  pcre2_match_data_free( data->_3_match_data );
    pcre2_code_free( data->struct_union_regex );
    pcre2_code_free( data->preproc_if_regex );
    pcre2_code_free( data->h_xyi_regex_b );
    pcre2_code_free( data->enum_struct_union_regex_3 );
    pcre2_code_free( data->def_name_asterisk_regex );
    pcre2_code_free( data->def_name_regex );
    pcre2_code_free( data->d_regex );
    pcre2_code_free( data->e_regex );
    pcre2_code_free( data->enum_struct_union_regex_2 );
    pcre2_code_free( data->enum_struct_union_regex_1 );
    pcre2_code_free( data->yi_regex );
    pcre2_code_free( data->x_regex );
    if( data->xyi_array_b )
    {   for( unsigned long i = 0; i != data->xyi_array_b_n; i++ )
            HeapFree( E_main_S_process_heap, 0, data->xyi_array_b[i] );
        HeapFree( E_main_S_process_heap, 0, data->xyi_array_b );
    }
    if( data->xyi_array_a )
    {   for( unsigned long i = 0; i != data->xyi_array_a_n; i++ )
            if( data->xyi_array_a[i] )
                HeapFree( E_main_S_process_heap, 0, data->xyi_array_a[i] );
        HeapFree( E_main_S_process_heap, 0, data->xyi_array_a );
    }
    if( data->file_h_to_libs_buffer )
        HeapFree( E_main_S_process_heap, 0, data->file_h_to_libs_buffer );
}
//==============================================================================
int
E_main_Q_file_R_line( HANDLE file
, char **buf
){  unsigned long l = 1;
    *buf = HeapAlloc( E_main_S_process_heap, 0, l );
    Vv( *buf, "Unable to allocate" )
    {   *buf = 0;
        return FALSE;
    }
    unsigned long l_read;
    int eof = FALSE;
    char s[1];
    do
    {   V( ReadFile( file, &s[0], sizeof(s), &l_read, 0 ), "Unable do read file" )
        {   HeapFree( E_main_S_process_heap, 0, *buf );
            *buf = 0;
            return eof;
        }
        if( l_read < sizeof(s) )
            eof = TRUE;
        if( !l_read )
            break;
        if( l_read == sizeof(s) )
        {   if( *s == '\r' )
                goto Cont;
            if( *s == '\n' )
                break;
        }
        char *buf_ = HeapReAlloc( E_main_S_process_heap, 0, *buf, l += l_read );
        Vv( buf_, "Unable to reallocate" )
        {   HeapFree( E_main_S_process_heap, 0, *buf );
            *buf = 0;
            return eof;
        }
        *buf = buf_;
        (*buf)[ l - 1 - l_read ] = *s;
Cont:;
    }while( !eof );
    (*buf)[ l - 1 ] = '\0';
    return eof;
}
int
E_main_Q_file_P_line( HANDLE file
, char *buf
){  unsigned long l = strlen(buf);
    unsigned long l_written;
    V( WriteFile( file, buf, l, &l_written, 0 )
    && l_written == l
    , "Unable to write to file"
    )
        return 1;
    char s[2] = "\r\n";
    V( WriteFile( file, s, sizeof(s), &l_written, 0 )
    && l_written == sizeof(s)
    , "Unable to write to file"
    )
        return 1;
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char *
E_main_Q_filename_I_encode( char *filename
){  unsigned long size = E_main_Q_s0_R_strlen(filename) - 3 + 1;
    char *ret = HeapAlloc( E_main_S_process_heap, 0, size );
    Vv( ret, "Unable to allocate" )
    {   HeapFree( E_main_S_process_heap, 0, ret );
        return 0;
    }
    CopyMemory( ret, filename, size - 1 );
    ret[ size - 1 ] = '\0';
    for( char *p = ret; *p; p++ )
    {   if( E_main_Q_c_I_isalnum( *p ))
            continue;
        unsigned long l_added = 2;
        char *ret_ = HeapReAlloc( E_main_S_process_heap, 0, ret, size + l_added );
        Vv( ret_, "Unable to reallocate" )
        {   HeapFree( E_main_S_process_heap, 0, ret );
            return 0;
        }
        p = ret_ + ( p - ret );
        ret = ret_;
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
, struct E_main_Z_build_resources *data
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
        {   char *s = E_main_Q_s0_I_strstr( line, "*/" );
            if(s)
            {   MoveMemory( line, s + 2, E_main_Q_s0_R_strlen(s) - 2 + 1 );
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
                Vv( last_line, "Unable to allocate" )
                    return 1;
                last_line[0] = '\0';
                goto Cont;
            }
        }
        char *s = E_main_Q_s0_I_strstr( line, "//" );
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
                Vv( last_line, "Unable to allocate" )
                    return 1;
                last_line[0] = '\0';
                inside_braces = 2;
                goto Cont;
            }
            inside_braces = 0;
        }
        if( inside_braces == 2 )
        {   if( line[0] == '}' )
            {   if( !inside_enum )
                {   inside_braces = E_main_Q_s0_I_strchr( line, ';' ) ? 0 : 3;
                    MoveMemory( line, line + 1, E_main_Q_s0_R_strlen( line + 1 ) + 1 );
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
                    Vv( last_line, "Unable to allocate" )
                        return 1;
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
                Vv( last_line, "Unable to allocate" )
                {   CloseHandle( h_file );
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
        int match_res = pcre2_match( data->enum_struct_union_regex_1, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for regex \"enum_struct_union_regex_1\".\n", stderr );
                if( last_line )
                    HeapFree( E_main_S_process_heap, 0, last_line );
                return 1;
            }
            match_res = pcre2_match( data->enum_struct_union_regex_2, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   fputs( "Match error for regex \"enum_struct_union_regex_2\".\n", stderr );
                    if( last_line )
                        HeapFree( E_main_S_process_heap, 0, last_line );
                    return 1;
                }
                match_res = pcre2_match( data->e_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   fputs( "Match error for regex \"e_regex\".\n", stderr );
                        if( last_line )
                            HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    match_res = pcre2_match( data->d_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                    if( match_res < 0 )
                    {   if( match_res != PCRE2_ERROR_NOMATCH )
                        {   fputs( "Match error for regex \"d_regex\".\n", stderr );
                            if( last_line )
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            return 1;
                        }
                        if( E_main_Q_s0_s0_I_strncmp( line, "/*", 2 ))
                        {   if( last_line )
                            {   if( E_main_Q_file_P_line( h_file, last_line ))
                                {   HeapFree( E_main_S_process_heap, 0, last_line );
                                    return 1;
                                }
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            }
                            last_line = line;
                        }else
                        {   char *s = E_main_Q_s0_I_strstr( line, "*/" );
                            if(s)
                            {   MoveMemory( line, s + 2, E_main_Q_s0_R_strlen(s) - 2 + 1 );
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
                            Vv( last_line, "Unable to allocate" )
                                return 1;
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
                        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                        last_line = HeapAlloc( E_main_S_process_heap, 0, 16 + ovector[3] - ovector[2] + 7 + E_main_Q_s0_R_strlen(line) + 1 );
                        Vv( last_line, "Unable to allocate" )
                            return 1;
                        E_main_Q_s_s0_I_strcpy( last_line, "_internal I D_id" );
                        CopyMemory( last_line + 16, line + ovector[2], ovector[3] - ovector[2] );
                        E_main_Q_s_s0_I_strcpy( last_line + 16 + ovector[3] - ovector[2], " = ~0; " );
                        E_main_Q_s_s0_I_strcpy( last_line + 16 + ovector[3] - ovector[2] + 7, line );
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
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                if( last_line )
                {   if( E_main_Q_file_P_line( h_file, last_line ))
                    {   HeapFree( E_main_S_process_heap, 0, last_line );
                        return 1;
                    }
                    HeapFree( E_main_S_process_heap, 0, last_line );
                }
                inside_enum = !E_main_Q_s0_s0_I_strncmp( line, "enum", ovector[3] );
                if( !inside_enum )
                    last_line = line;
                else
                {   last_line = HeapAlloc( E_main_S_process_heap, 0, 1 );
                    Vv( last_line, "Unable to allocate" )
                        return 1;
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
, char *enc
, struct E_main_Z_build_resources *data
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
        int match_res = pcre2_match( data->h_xyi_regex_b, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for \"h_xyi_regex_b\".\n", stderr );
                HeapFree( E_main_S_process_heap, 0, xyi_array_b );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) + 1 );
            Vv( s, "Unable to allocate" )
            {   HeapFree( E_main_S_process_heap, 0, xyi_array_b );
                return 1;
            }
            CopyMemory( s, line + ovector[2], ovector[3] - ovector[2] );
            E_main_Q_s_s0_I_strcpy( s + ( ovector[3] - ovector[2] ), ",X_" );
            CopyMemory( s + ( ovector[3] - ovector[2] ) + 3, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != xyi_array_b_n; i++ )
                if( !E_main_Q_s0_s0_I_strcmp( xyi_array_b[i], s ))
                    break;
            if( i == xyi_array_b_n )
            {   for( i = 0; i != data->xyi_array_a_n; i++ )
                    if( data->xyi_array_a[i]
                    && !E_main_Q_s0_s0_I_strcmp( data->xyi_array_a[i], s )
                    )
                        break;
                if( i == data->xyi_array_a_n )
                {   void *p = HeapReAlloc( E_main_S_process_heap, 0, xyi_array_b, sizeof( char * ) * ( xyi_array_b_n + 1 ));
                    Vv( p, "Unable to reallocate" )
                    {   HeapFree( E_main_S_process_heap, 0, xyi_array_b );
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
    {   unsigned long l = E_main_Q_s0_R_strlen( xyi_array_b[0] );
        unsigned long l_enc = E_main_Q_s0_R_strlen(enc);
        unsigned long buffer_size = 18 + l + 17 + l_enc + 3 + 4;
        for( unsigned long i = 1; i != xyi_array_b_n; i++ )
        {   unsigned long l = E_main_Q_s0_R_strlen( xyi_array_b[0] );
            buffer_size += 12 + l + 17 + l_enc + 4;
        }
        char *buffer = HeapAlloc( E_main_S_process_heap, 0, buffer_size );
        Vv( buffer, "Unable to allocate" )
        {   HeapFree( E_main_S_process_heap, 0, xyi_array_b );
            return 1;
        }
        E_main_Q_s_s0_I_strcpy( buffer, "enum\r\n{ _XhYi_uid(" );
        E_main_Q_s_s0_I_strcpy( buffer + 18, xyi_array_b[0] );
        E_main_Q_s_s0_I_strcpy( buffer + 18 + l, ") = _XhYi_F_uid( " );
        E_main_Q_s_s0_I_strcpy( buffer + 18 + l + 17, enc );
        CopyMemory( buffer + 18 + l + 17 + l_enc, " )\r\n", 4 );
        char *s = buffer + 18 + l + 17 + l_enc + 4;
        for( unsigned long i = 1; i != xyi_array_b_n; i++ )
        {   unsigned long l = E_main_Q_s0_R_strlen( xyi_array_b[0] );
            E_main_Q_s_s0_I_strcpy( s, ", _XhYi_uid(" );
            E_main_Q_s_s0_I_strcpy( s + 12, xyi_array_b[i] );
            E_main_Q_s_s0_I_strcpy( s + 12 + l, ") = _XhYi_F_uid( " );
            E_main_Q_s_s0_I_strcpy( s + 12 + l + 17, enc );
            E_main_Q_s_s0_I_strcpy( s + 12 + l + 17 + l_enc, " )\r\n" );
            s += 12 + l + 17 + l_enc + 4;
        }
        CopyMemory( s, "};\r\n", 4 );
        unsigned long wrote;
        V( WriteFile( h_file, buffer, buffer_size, &wrote, 0 )
        && wrote == buffer_size
        , "Unable to write file"
        )
        {   HeapFree( E_main_S_process_heap, 0, buffer );
            HeapFree( E_main_S_process_heap, 0, xyi_array_b );
            return 1;
        }
        HeapFree( E_main_S_process_heap, 0, buffer );
    }
    HeapFree( E_main_S_process_heap, 0, xyi_array_b );
    return 0;
}
int
E_main_I_cx_to_h_2( HANDLE h_file_cx
, HANDLE h_file
, struct E_main_Z_build_resources *data
){  int eof;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
            return 1;
        char *s = E_main_Q_s0_I_strstr( line, "//" );
        if(s)
            *s = '\0';
        int match_res = pcre2_match( data->preproc_if_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for \"preproc_if_regex\".\n", stderr );
                return 1;
            }
            match_res = pcre2_match( data->struct_union_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   fputs( "Match error for \"struct_union_regex\".\n", stderr );
                    return 1;
                }
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                char *line_out = HeapAlloc( E_main_S_process_heap, 0, ovector[1] + 1 + 1 );
                if( !line_out )
                    return 1;
                CopyMemory( line_out, line, ovector[1] );
                E_main_Q_s_s0_I_strcpy( line_out + ovector[1], ";" );
                if( E_main_Q_file_P_line( h_file, line_out ))
                {   HeapFree( E_main_S_process_heap, 0, line_out );
                    return 1;
                }
                HeapFree( E_main_S_process_heap, 0, line_out );
            }
        }else
            if( E_main_Q_file_P_line( h_file, line ))
                return 1;
    }while( !eof );
    return 0;
}
int
E_main_I_cx_to_h_3( HANDLE h_file_cx
, HANDLE h_file
, struct E_main_Z_build_resources *data
, int module
){  int eof;
    int inside_braces = 0;
    char *line, *last_line = 0;
    do
    {   eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
            goto Err_1;
        char *s = E_main_Q_s0_I_strstr( line, "//" );
        if(s)
            *s = '\0';
        if( inside_braces == 1 )
        {   if( line[0] == '{' )
            {   if( E_main_Q_file_P_line( h_file, last_line ))
                    goto Err_2;
                if( E_main_Q_file_P_line( h_file, line ))
                    goto Err_2;
                inside_braces = 2;
                HeapFree( E_main_S_process_heap, 0, line );
                goto Cont;
            }
            inside_braces = 0;
        }
        if( inside_braces == 2 )
        {   int match_res = pcre2_match( data->def_name_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   fputs( "Match error for regex \"def_name_regex\".\n", stderr );
                    goto Err_2;
                }
                if( E_main_Q_file_P_line( h_file, line ))
                    goto Err_2;
            }else
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                unsigned long l = ovector[1];
                char *s = HeapAlloc( E_main_S_process_heap, 0, l + 1 );
                Vv( s, "Unable to allocate" )
                    goto Err_2;
                CopyMemory( s, line, l );
                s[l] = '\0';
                match_res = pcre2_match( data->def_name_asterisk_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   fputs( "Match error for regex \"def_name_asterisk_regex\".\n", stderr );
                        HeapFree( E_main_S_process_heap, 0, s );
                        goto Err_2;
                    }
                    char *s_ = HeapReAlloc( E_main_S_process_heap, 0, s, l + 1 + 1 );
                    Vv( s_, "Unable to reallocate" )
                    {   HeapFree( E_main_S_process_heap, 0, s );
                        goto Err_2;
                    }
                    s = s_;
                    E_main_Q_s_s0_I_strcpy( s + l, ";" );
                }else
                {   char *s_ = HeapReAlloc( E_main_S_process_heap, 0, s, 1 + 16 + ( match_res == 1 ? 1 : 0 ) + l - 1 + 1 + 1 );
                    Vv( s_, "Unable to reallocate" )
                    {   HeapFree( E_main_S_process_heap, 0, s );
                        goto Err_2;
                    }
                    s = s_;
                    MoveMemory( s + 1 + 16 + ( match_res == 1 ? 1 : 0 ), s + 1, l - 1 );
                    CopyMemory( s + 1, "extern DLLIMPORT", 16 );
                    if( match_res == 1 )
                        s[ 1 + 16 ] = ' ';
                    E_main_Q_s_s0_I_strcpy( s + 1 + 16 + ( match_res == 1 ? 1 : 0 ) + l - 1, ";" );
                }
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    goto Err_2;
                }
                HeapFree( E_main_S_process_heap, 0, s );
                inside_braces =  E_main_Q_s0_I_strchr( line, ';' ) ? 0 : 3;
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
            {   char *s = HeapAlloc( E_main_S_process_heap, 0, 1 + 1 + 1 );
                Vv( s, "Unable to allocate" )
                    goto Err_2;
                E_main_Q_s_s0_I_strcpy( s, ");" );
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    goto Err_2;
                }
                HeapFree( E_main_S_process_heap, 0, s );
                inside_braces = 0;
            }else if( E_main_Q_file_P_line( h_file, line ))
                goto Err_2;
            HeapFree( E_main_S_process_heap, 0, line );
            goto Cont;
        }
        int match_res = pcre2_match( data->preproc_if_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for regex \"preproc_if_regex\".\n", stderr );
                goto Err_2;
            }
            match_res = pcre2_match( data->enum_struct_union_regex_3, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
            if( match_res < 0 )
            {   if( match_res != PCRE2_ERROR_NOMATCH )
                {   fputs( "Match error for regex \"enum_struct_union_regex_3\".\n", stderr );
                    goto Err_2;
                }
                match_res = pcre2_match( data->enum_struct_union_regex_2, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                if( match_res < 0 )
                {   if( match_res != PCRE2_ERROR_NOMATCH )
                    {   fputs( "Match error for regex \"enum_struct_union_regex_2\".\n", stderr );
                        goto Err_2;
                    }
                    match_res = pcre2_match( data->e_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                    if( match_res < 0 )
                    {   if( match_res != PCRE2_ERROR_NOMATCH )
                        {   fputs( "Match error for regex \"S_e_regex\".\n", stderr );
                            goto Err_2;
                        }
                        match_res = pcre2_match( data->d_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
                        if( match_res < 0 )
                        {   if( match_res != PCRE2_ERROR_NOMATCH )
                            {   fputs( "Match error for regex \"d_regex\".\n", stderr );
                                goto Err_2;
                            }
                            if( last_line )
                                HeapFree( E_main_S_process_heap, 0, last_line );
                            last_line = line;
                        }else
                        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                            unsigned long l = E_main_Q_s0_R_strlen(line);
                            char *s = HeapAlloc( E_main_S_process_heap, 0, 13 + ( ovector[3] - ovector[2] ) + 2 + l + 1 + 1 );
                            Vv( s, "Unable to allocate" )
                                goto Err_2;
                            E_main_Q_s_s0_I_strcpy( s, "extern I D_id" );
                            CopyMemory( s + 13, line + ovector[2], ovector[3] - ovector[2] );
                            E_main_Q_s_s0_I_strcpy( s + 13 + ( ovector[3] - ovector[2] ), "; " );
                            E_main_Q_s_s0_I_strcpy( s + 13 + ( ovector[3] - ovector[2] ) + 2, line );
                            E_main_Q_s_s0_I_strcpy( s + 13 + ( ovector[3] - ovector[2] ) + 2 + l, ";" );
                            if( E_main_Q_file_P_line( h_file, s ))
                            {   HeapFree( E_main_S_process_heap, 0, s );
                                goto Err_2;
                            }
                            HeapFree( E_main_S_process_heap, 0, s );
                            HeapFree( E_main_S_process_heap, 0, line );
                        }
                    }else
                    {   if(module)
                        {   unsigned long l = E_main_Q_s0_R_strlen( last_line );
                            char *s = HeapReAlloc( E_main_S_process_heap, 0, last_line, 10 + l + 1 );
                            Vv( s, "Unable to reallocate" )
                                goto Err_2;
                            last_line = s;
                            MoveMemory( last_line + 10, last_line, l + 1 );
                            CopyMemory( last_line, "DLLIMPORT ", 10 );
                        }
                        if( E_main_Q_file_P_line( h_file, last_line ))
                            goto Err_2;
                        if( E_main_Q_file_P_line( h_file, line ))
                            goto Err_2;
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
            {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
                unsigned long l = ovector[3];
                char *s = HeapAlloc( E_main_S_process_heap, 0, 17 + l + 1 + 1 );
                Vv( s, "Unable to allocate" )
                    goto Err_2;
                E_main_Q_s_s0_I_strcpy( s, "extern DLLIMPORT " );
                CopyMemory( s + 17, line, l );
                E_main_Q_s_s0_I_strcpy( s + 17 + l, ";" );
                if( E_main_Q_file_P_line( h_file, s ))
                {   HeapFree( E_main_S_process_heap, 0, s );
                    goto Err_2;
                }
                HeapFree( E_main_S_process_heap, 0, s );
                HeapFree( E_main_S_process_heap, 0, line );
            }
        }else
        {   if( E_main_Q_file_P_line( h_file, line ))
                goto Err_2;
            HeapFree( E_main_S_process_heap, 0, line );
        }
Cont:;
    }while( !eof );
    if( last_line )
        HeapFree( E_main_S_process_heap, 0, last_line );
    return 0;
Err_2:
    HeapFree( E_main_S_process_heap, 0, line );
Err_1:
    if( last_line )
        HeapFree( E_main_S_process_heap, 0, last_line );
    return 1;
}
int
E_main_I_cx_to_xyi_array( HANDLE h_file_cx
, struct E_main_Z_build_resources *data
){  int eof;
    do
    {   char *line;
        eof = E_main_Q_file_R_line( h_file_cx, &line );
        if( !line )
            return 1;
        int match_res = pcre2_match( data->x_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for \"x_regex\".\n", stderr );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) + 1 );
            Vv( s, "Unable to allocate" )
                return 1;
            CopyMemory( s, line + ovector[2], ovector[3] - ovector[2] );
            E_main_Q_s_s0_I_strcpy( s + ( ovector[3] - ovector[2] ), ",X_" );
            CopyMemory( s + ( ovector[3] - ovector[2] ) + 3, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 3 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != data->xyi_array_a_n; i++ )
                if( data->xyi_array_a[i]
                && !E_main_Q_s0_s0_I_strcmp( data->xyi_array_a[i], s )
                )
                    break;
            if( i == data->xyi_array_a_n )
            {   for( i = 0; i != data->xyi_array_b_n; i++ )
                    if( !E_main_Q_s0_s0_I_strcmp( data->xyi_array_b[i], s ))
                        break;
                if( i == data->xyi_array_b_n )
                    if( line[ ovector[0] + 2 + ( line[ ovector[0] ] == 'Y' ? 1 : 0 ) ] == 'A' )
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, data->xyi_array_a, sizeof( char * ) * ( data->xyi_array_a_n + 1 ));
                        Vv( p, "Unable to reallocate" )
                            return 1;
                        data->xyi_array_a = p;
                        data->xyi_array_a_n++;
                        data->xyi_array_a[ data->xyi_array_a_n - 1 ] = s;
                    }else
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, data->xyi_array_b, sizeof( char * ) * ( data->xyi_array_b_n + 1 ));
                        Vv( p, "Unable to reallocate" )
                            return 1;
                        data->xyi_array_b = p;
                        data->xyi_array_b_n++;
                        data->xyi_array_b[ data->xyi_array_b_n - 1 ] = s;
                    }
            }
        }
        match_res = pcre2_match( data->yi_regex, ( PCRE2_SPTR8 )line, PCRE2_ZERO_TERMINATED, 0, 0, data->_3_match_data, 0 );
        if( match_res < 0 )
        {   if( match_res != PCRE2_ERROR_NOMATCH )
            {   fputs( "Match error for \"yi_regex\".\n", stderr );
                return 1;
            }
        }else
        {   PCRE2_SIZE *ovector = pcre2_get_ovector_pointer( data->_3_match_data );
            char *s = HeapAlloc( E_main_S_process_heap, 0, ( ovector[3] - ovector[2] ) + 4 + ( ovector[5] - ovector[4] ) + 1 );
            Vv( s, "Unable to allocate" )
                return 1;
            CopyMemory( s, line + ovector[2], ovector[3] - ovector[2] );
            E_main_Q_s_s0_I_strcpy( s + ( ovector[3] - ovector[2] ), ",Yi_" );
            CopyMemory( s + ( ovector[3] - ovector[2] ) + 4, line + ovector[4], ovector[5] - ovector[4]);
            s[ ( ovector[3] - ovector[2] ) + 4 + ( ovector[5] - ovector[4] ) ] = '\0';
            unsigned long i;
            for( i = 0; i != data->xyi_array_a_n; i++ )
                if( data->xyi_array_a[i]
                && !E_main_Q_s0_s0_I_strcmp( data->xyi_array_a[i], s )
                )
                    break;
            if( i == data->xyi_array_a_n )
            {   for( i = 0; i != data->xyi_array_b_n; i++ )
                    if( !E_main_Q_s0_s0_I_strcmp( data->xyi_array_b[i], s ))
                        break;
                if( i == data->xyi_array_b_n )
                    if( line[ ovector[0] + 2 + ( line[ ovector[0] ] == 'Y' ? 1 : 0 ) ] == 'A' )
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, data->xyi_array_a, sizeof( char * ) * ( data->xyi_array_a_n + 1 ));
                        Vv( p, "Unable to reallocate" )
                            return 1;
                        data->xyi_array_a = p;
                        data->xyi_array_a_n++;
                        data->xyi_array_a[ data->xyi_array_a_n - 1 ] = s;
                    }else
                    {   void *p = HeapReAlloc( E_main_S_process_heap, 0, data->xyi_array_b, sizeof( char * ) * ( data->xyi_array_b_n + 1 ));
                        Vv( p, "Unable to reallocate" )
                            return 1;
                        data->xyi_array_b = p;
                        data->xyi_array_b_n++;
                        data->xyi_array_b[ data->xyi_array_b_n - 1 ] = s;
                    }
            }
        }
    }while( !eof );
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef int (*E_main_I_find_file_Z_proc)( WIN32_FIND_DATA *found_dir, void *context );
int
E_main_I_find_file( char *file_mask
, E_main_I_find_file_Z_proc proc
, void *context
){  int ret = 1;
    WIN32_FIND_DATA found_dir;
    HANDLE h_find_dir = FindFirstFile( file_mask, &found_dir );
    if( h_find_dir != INVALID_HANDLE_VALUE )
    {   do
        {   ret = proc( &found_dir, context );
            if(ret)
                break;
            if( !FindNextFile( h_find_dir, &found_dir ))
            {   if( GetLastError() != ERROR_NO_MORE_FILES )
                    ret = 1;
                break;
            }
        }while(TRUE);
        FindClose( h_find_dir );
    }else
        fprintf( stderr, "Not found file mask \"%s\".\n", file_mask );
    return ret;
}
//------------------------------------------------------------------------------
int
E_main_I_find_file_I_module_1( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  char *file;
    HANDLE h_file_cx, h_file;
    if( !( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( data->found_dir );
        unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
        file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + l_file + 1 );
        Vv( file, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file + 10, data->found_dir );
        file[ 10 + l_dir ] = '\\';
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1, found_file->cFileName );
        h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
        V( h_file_cx != INVALID_HANDLE_VALUE, "Unable to open file" )
            goto Err_1;
        fprintf( stderr, "Processing file \"%s\"...\n", file );
        file[ 10 + l_dir + 1 + l_file - 1 ] = '\0';
        h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
        if( h_file != INVALID_HANDLE_VALUE )
        {   FILETIME file_time;
            if( GetFileTime( h_file, 0, 0, &file_time ))
            {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                file_time_u.LowPart = file_time.dwLowDateTime;
                file_time_u.HighPart = file_time.dwHighDateTime;
                if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                    goto Cont_1;
                SetEndOfFile( h_file );
            }
        }else
        {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
            V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
                goto Err_2;
        }
        if( E_main_I_cx_to_c( h_file_cx, h_file, data ))
        {   CloseHandle( h_file );
            goto Err_2;
        }
        SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_1: CloseHandle( h_file );
/*        unsigned long l_added = 22 + l_dir + 2 + l_file - 2 + 4;
        char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
        Vv( file_h_to_libs_buffer_, "Unable to reallocate" )
            goto Err_2;
        data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
        MoveMemory( data->file_h_to_libs_buffer + l_added, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size );
        data->file_h_to_libs_buffer_size += l_added;
        E_main_Q_s_s0_I_strcpy( data->file_h_to_libs_buffer, "#include \"E_cplus_S_0_" );
        E_main_Q_s_s0_I_strcpy( data->file_h_to_libs_buffer + 22, data->found_dir );
        E_main_Q_s_s0_I_strcpy( data->file_h_to_libs_buffer + 22 + l_dir, "__" );
        CopyMemory( data->file_h_to_libs_buffer + 22 + l_dir + 2, found_file->cFileName, l_file - 2 );
        CopyMemory( data->file_h_to_libs_buffer + 22 + l_dir + 2 + l_file - 2, "h\"\r\n", 4 );*/
        char *path = HeapAlloc( E_main_S_process_heap, 0, l_dir + 1 + l_file + 1 );
        Vv( path, "Unable to allocate" )
            goto Err_2;
        E_main_Q_s_s0_I_strcpy( path, data->found_dir );
        path[ l_dir ] = '\\';
        E_main_Q_s_s0_I_strcpy( path + l_dir + 1, found_file->cFileName );
        char *enc = E_main_Q_filename_I_encode(path);
        if( !enc )
        {   HeapFree( E_main_S_process_heap, 0, path );
            goto Err_2;
        }
        HeapFree( E_main_S_process_heap, 0, path );
        unsigned long pos = E_main_Q_s0_I_strstr( data->file_h_to_libs_buffer, "#include \"E_cplus_S_language.h\"\r\n" ) + 33 - data->file_h_to_libs_buffer;
        char *s = data->file_h_to_libs_buffer + pos;
        do
        {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
            if( s - data->file_h_to_libs_buffer == data->file_h_to_libs_buffer_size
            || E_main_Q_s0_s0_I_strncmp( s, "#include \"", 10 )
            || s[10] == 'E'
            )
                break;
        }while(TRUE);
        unsigned long l_enc = E_main_Q_s0_R_strlen(enc);
        unsigned long l_added = 10 + l_enc + 4;
        if( E_main_Q_s0_s0_I_strncmp( s, "enum\r\n{ _F_uid( ", 16 ))
            l_added += 6 + 43;
        char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
        if( !file_h_to_libs_buffer_ )
        {   HeapFree( E_main_S_process_heap, 0, enc );
            goto Err_2;
        }
        s = file_h_to_libs_buffer_ + ( s - data->file_h_to_libs_buffer );
        data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
        if( !E_main_Q_s0_s0_I_strncmp( s, "enum\r\n{ _F_uid( ", 16 ))
        {   char *s_ = E_main_Q_s0_I_strstr( s + 16, "\r\n" ) + 2;
            MoveMemory( s_ + l_added, s_, data->file_h_to_libs_buffer_size - ( s_ - data->file_h_to_libs_buffer ));
            E_main_Q_s_s0_I_strcpy( s_, ", _F_uid( " );
            E_main_Q_s_s0_I_strcpy( s_ + 10, enc );
            CopyMemory( s_ + 10 + l_enc, " )\r\n", 4 );
            s = s_ + 10 + l_enc + 4 - 2;
        }else
        {   MoveMemory( s + l_added, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
            E_main_Q_s_s0_I_strcpy( s, "enum\r\n{ _F_uid( " );
            E_main_Q_s_s0_I_strcpy( s + 16, enc );
            CopyMemory( s + 16 + l_enc, " ) = ( ~0 << ( sizeof(int) * 8 / 2 - 1 )) | 1\r\n", 47 );
            s += 16 + l_enc + 47 - 2;
        }
        data->file_h_to_libs_buffer_size += l_added;
        HeapFree( E_main_S_process_heap, 0, enc );
        do
        {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
            if( *s != ',' )
                break;
        }while(TRUE);
        l_added = 22 + l_dir + 2 + l_file - 2 + 4;
        file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
        Vv( file_h_to_libs_buffer_, "Unable to reallocate" )
            goto Err_2;
        s = file_h_to_libs_buffer_ + ( s - data->file_h_to_libs_buffer );
        data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
        MoveMemory( s + l_added, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
        data->file_h_to_libs_buffer_size += l_added;
        E_main_Q_s_s0_I_strcpy( s, "#include \"E_cplus_S_1_" );
        E_main_Q_s_s0_I_strcpy( s + 22, data->found_dir );
        E_main_Q_s_s0_I_strcpy( s + 22 + l_dir, "__" );
        CopyMemory( s + 22 + l_dir + 2, found_file->cFileName, l_file - 2 );
        CopyMemory( s + 22 + l_dir + 2 + l_file - 2, "h\"\r\n", 4 );
        s += 22 + l_dir + 2 + l_file - 2 + 4 - 2;
        do
        {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
            if( s - data->file_h_to_libs_buffer + 22 > data->file_h_to_libs_buffer_size
            || E_main_Q_s0_s0_I_strncmp( s, "#include \"E_cplus_S_1_", 22 )
            )
                break;
        }while(TRUE);
        file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
        Vv( file_h_to_libs_buffer_, "Unable to reallocate" )
            goto Err_2;
        s = file_h_to_libs_buffer_ + ( s - data->file_h_to_libs_buffer );
        data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
        MoveMemory( s + l_added, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
        data->file_h_to_libs_buffer_size += l_added;
        E_main_Q_s_s0_I_strcpy( s, "#include \"E_cplus_S_2_" );
        E_main_Q_s_s0_I_strcpy( s + 22, data->found_dir );
        E_main_Q_s_s0_I_strcpy( s + 22 + l_dir, "__" );
        CopyMemory( s + 22 + l_dir + 2, found_file->cFileName, l_file - 2 );
        CopyMemory( s + 22 + l_dir + 2 + l_file - 2, "h\"\r\n", 4 );
        if( E_main_I_cx_to_xyi_array( h_file_cx, data ))
            goto Err_2;
        CloseHandle( h_file_cx );
        HeapFree( E_main_S_process_heap, 0, file );
    }
    return 0;
Err_2:
    CloseHandle( h_file_cx );
Err_1:
    HeapFree( E_main_S_process_heap, 0, file );
    return 1;
}
int
E_main_I_find_file_I_modules_1( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if(( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    && found_file->cFileName[0] != '.'
    )
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
        unsigned long l_added = 10 + l_dir + 3 + 2;
        char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
        Vv( file_h_to_libs_buffer_, "Unable to reallocate" )
            return 1;
        data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
        unsigned long pos = E_main_Q_s0_I_strstr( data->file_h_to_libs_buffer, "#include \"E_cplus_S_language.h\"\r\n" ) + 33 - data->file_h_to_libs_buffer;
        char *s = data->file_h_to_libs_buffer + pos;
        MoveMemory( s + l_added, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
        data->file_h_to_libs_buffer_size += l_added;
        E_main_Q_s_s0_I_strcpy( s, "#include \"" );
        E_main_Q_s_s0_I_strcpy( s + 10, found_file->cFileName );
        CopyMemory( s + 10 + l_dir, ".h\"\r\n", 5 );
        data->found_dir = found_file->cFileName;
        char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
        Vv( file_mask, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file_mask, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file_mask + 10, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file_mask + 10 + l_dir, "\\*.cx" );
        ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_module_1, data );
        HeapFree( E_main_S_process_heap, 0, file_mask );
    }
    return ret;
}
int
E_main_I_find_file_I_module_2( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  char *file, *file_h;
    HANDLE h_file_cx, h_file;
    if( !( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( data->found_dir );
        unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
        file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + l_file + 1 );
        Vv( file, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file + 10, data->found_dir );
        file[ 10 + l_dir ] = '\\';
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1, found_file->cFileName );
        h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
        V( h_file_cx != INVALID_HANDLE_VALUE, "Unable to open file" )
        {   HeapFree( E_main_S_process_heap, 0, file );
            return 1;
        }
        fprintf( stderr, "Processing file \"%s\"...\n", file );
        file_h = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2 + 1 + 1 );
        Vv( file_h, "Unable to allocate" )
            goto Err_1;
        CopyMemory( file_h, file, 10 + l_dir + 1 );
        E_main_Q_s_s0_I_strcpy( file_h + 10 + l_dir + 1, "E_cplus_S_1_" );
        E_main_Q_s_s0_I_strcpy( file_h + 10 + l_dir + 1 + 12, data->found_dir );
        E_main_Q_s_s0_I_strcpy( file_h + 10 + l_dir + 1 + 12 + l_dir, "__" );
        CopyMemory( file_h + 10 + l_dir + 1 + 12 + l_dir + 2, found_file->cFileName, l_file - 2 );
        E_main_Q_s_s0_I_strcpy( file_h + 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2, "h" );
        h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
        if( h_file != INVALID_HANDLE_VALUE )
        {   FILETIME file_time;
            if( GetFileTime( h_file, 0, 0, &file_time ))
            {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                file_time_u.LowPart = file_time.dwLowDateTime;
                file_time_u.HighPart = file_time.dwHighDateTime;
                if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                    goto Cont_1;
                SetEndOfFile( h_file );
            }
        }else
        {   h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
            V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
            {   HeapFree( E_main_S_process_heap, 0, file );
                goto Err_2;
            }
        }
        char *enc = E_main_Q_filename_I_encode( file + 10 );
        if( !enc )
        {   HeapFree( E_main_S_process_heap, 0, file );
            goto Err_3;
        }
        if( E_main_I_cx_to_h_1( h_file_cx, h_file, enc, data ))
        {   HeapFree( E_main_S_process_heap, 0, enc );
            goto Err_3;
        }
        HeapFree( E_main_S_process_heap, 0, enc );
        SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
        if( E_main_I_cx_to_h_2( h_file_cx, h_file, data ))
        {   HeapFree( E_main_S_process_heap, 0, file );
            goto Err_3;
        }
        SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_1: HeapFree( E_main_S_process_heap, 0, file );
        CloseHandle( h_file );
        file_h[ 10 + l_dir + 1 + 10 ] = '2';
        h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
        if( h_file != INVALID_HANDLE_VALUE )
        {   FILETIME file_time;
            if( GetFileTime( h_file, 0, 0, &file_time ))
            {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                file_time_u.LowPart = file_time.dwLowDateTime;
                file_time_u.HighPart = file_time.dwHighDateTime;
                if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                    goto Cont_2;
                SetEndOfFile( h_file );
            }
        }else
        {   h_file = CreateFile( file_h, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
            V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
                goto Err_2;
        }
        if( E_main_I_cx_to_h_3( h_file_cx, h_file, data, TRUE ))
            goto Err_3;
Cont_2: CloseHandle( h_file );
        HeapFree( E_main_S_process_heap, 0, file_h );
        CloseHandle( h_file_cx );
    }
    return 0;
Err_3:
    CloseHandle( h_file );
Err_2:
    HeapFree( E_main_S_process_heap, 0, file_h );
Err_1:
    CloseHandle( h_file_cx );
    return 1;
}
int
E_main_I_find_file_I_modules_2( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if(( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    && found_file->cFileName[0] != '.'
    )
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
        data->found_dir = HeapAlloc( E_main_S_process_heap, 0, l_dir + 1 );
        Vv( data->found_dir, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( data->found_dir, found_file->cFileName );
        char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
        Vv( file_mask, "Unable to allocate" )
        {   HeapFree( E_main_S_process_heap, 0, data->found_dir );
            return 1;
        }
        E_main_Q_s_s0_I_strcpy( file_mask, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file_mask + 10, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file_mask + 10 + l_dir, "\\*.cx" );
        ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_module_2, data );
        HeapFree( E_main_S_process_heap, 0, file_mask );
        HeapFree( E_main_S_process_heap, 0, data->found_dir );
    }
    return ret;
}
int
E_main_I_build_I_to_libs( struct E_main_Z_build_resources *data
){  unsigned long l_added = 4;
    if( data->xyi_array_a_n )
    {   for( unsigned long i = 0; i != data->xyi_array_a_n; i++ )
             for( unsigned long j = 0; j != data->xyi_array_b_n; j++ )
                  if( !E_main_Q_s0_s0_I_strcmp( data->xyi_array_a[i], data->xyi_array_b[j] ))
                  {   HeapFree( E_main_S_process_heap, 0, data->xyi_array_a[i] );
                      data->xyi_array_a[i] = 0;
                      break;
                  }
        unsigned long i;
        for( i = 0; i != data->xyi_array_a_n; i++ )
             if( data->xyi_array_a[i] )
                 break;
        if( i == data->xyi_array_a_n )
            data->xyi_array_a_n = 0;
        else
        {   unsigned long l = E_main_Q_s0_R_strlen( data->xyi_array_a[i] );
            l_added += 18 + l + 50 + 4;
            char *s = E_main_Q_s0_I_strstr( data->file_h_to_libs_buffer, "enum\r\n{ _F_uid( " ) + 6;
            do
            {   s = E_main_Q_s0_I_strstr( s + 10, "\r\n" ) + 2;
                if( s - data->file_h_to_libs_buffer == data->file_h_to_libs_buffer_size
                || *s != ','
                )
                    break;
            }while(TRUE);
            for( i++; i != data->xyi_array_a_n; i++ )
                if( data->xyi_array_a[i] )
                    l_added += 12 + E_main_Q_s0_R_strlen( data->xyi_array_a[i] ) + 3;
        }
    }
    char *s = E_main_Q_s0_I_strstr( data->file_h_to_libs_buffer, "enum\r\n{ _F_uid( " ) + 6;
    do
    {   s = E_main_Q_s0_I_strstr( s + 10, "\r\n" ) + 2;
        if( s - data->file_h_to_libs_buffer == data->file_h_to_libs_buffer_size
        || *s != ','
        )
            break;
    }while(TRUE);
    char *file_h_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size + l_added );
    Vv( file_h_to_libs_buffer_, "Unable to reallocate" )
        return 1;
    s = file_h_to_libs_buffer_ + ( s - data->file_h_to_libs_buffer );
    data->file_h_to_libs_buffer = file_h_to_libs_buffer_;
    MoveMemory( s + 4, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
    data->file_h_to_libs_buffer_size += 4;
    CopyMemory( s, "};\r\n", 4 );
    if( data->xyi_array_a_n )
    {   s += 4;
        l_added -= 4;
        unsigned long i;
        for( i = 0; i != data->xyi_array_a_n; i++ )
            if( data->xyi_array_a[i] )
                break;
        unsigned long l = E_main_Q_s0_R_strlen( data->xyi_array_a[i] );
        MoveMemory( s + l_added, s, data->file_h_to_libs_buffer_size - ( s - data->file_h_to_libs_buffer ));
        data->file_h_to_libs_buffer_size += l_added;
        E_main_Q_s_s0_I_strcpy( s, "enum\r\n{ _XhYi_uid(" );
        E_main_Q_s_s0_I_strcpy( s + 18, data->xyi_array_a[i] );
        CopyMemory( s + 18 + l, ") = _F_uid_v( ~0 << ( sizeof(int) * 8 / 2 - 1 ))\r\n", 50 );
        s += 18 + l + 50;
        for( i++; i != data->xyi_array_a_n; i++ )
        {   if( !data->xyi_array_a[i] )
                continue; 
            E_main_Q_s_s0_I_strcpy( s, ", _XhYi_uid(" );
            E_main_Q_s_s0_I_strcpy( s + 12, data->xyi_array_a[i] );
            unsigned long l = E_main_Q_s0_R_strlen( data->xyi_array_a[i] );
            E_main_Q_s_s0_I_strcpy( s + 12 + l, ")\r\n" );
            s += 12 + l + 3;
        }
        CopyMemory( s, "};\r\n", 4 );
    }
    char *file_h_to_libs = HeapAlloc( E_main_S_process_heap, 0, 29 + 1 );
    Vv( file_h_to_libs, "Unable to allocate" )
        return 1;
    E_main_Q_s_s0_I_strcpy( file_h_to_libs, "..\\module\\E_cplus_S_to_libs.h" );
    HANDLE h_file_h_to_libs = CreateFile( file_h_to_libs, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0 );
    V( h_file_h_to_libs != INVALID_HANDLE_VALUE, "Unable to create file" )
    {   HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
        return 1;
    }
    HeapFree( E_main_S_process_heap, 0, file_h_to_libs );
    unsigned long wrote;
    V( WriteFile( h_file_h_to_libs, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size, &wrote, 0 )
    && wrote == data->file_h_to_libs_buffer_size
    , "Unable to write file"
    )
    {   CloseHandle( h_file_h_to_libs );
        return 1;
    }
    CloseHandle( h_file_h_to_libs );
    return 0;
}
int
E_main_I_build_program_I_not_to_libs( struct E_main_Z_build_resources *data
){  if( data->file_h_not_to_libs_buffer_size != data->file_h_to_libs_buffer_size )
    {   unsigned long l_file_mask = E_main_Q_s0_R_strlen( data->found_dir );
        char *file_h_not_to_libs = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + 23 + 1 );
        Vv( file_h_not_to_libs, "Unable to allocate" )
            return 1;
        CopyMemory( file_h_not_to_libs, data->found_dir, l_file_mask - 1 );
        E_main_Q_s_s0_I_strcpy( file_h_not_to_libs + l_file_mask - 1, "E_cplus_S_not_to_libs.h" );
        HANDLE h_file_h_not_to_libs = CreateFile( file_h_not_to_libs, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0 );
        V( h_file_h_not_to_libs != INVALID_HANDLE_VALUE, "Unable to create file" )
        {   HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
            return 1;
        }
        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
        unsigned long wrote;
        V( WriteFile( h_file_h_not_to_libs, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size, &wrote, 0 )
        && wrote == data->file_h_not_to_libs_buffer_size
        , "Unable to write file"
        )
        {   CloseHandle( h_file_h_not_to_libs );
            return 1;
        }
        CloseHandle( h_file_h_not_to_libs );
    }
    return 0;
}
int
E_main_I_find_file_I_program( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    char *file, *enc;
    HANDLE h_file_cx, h_file;
    if( found_file->cFileName[0] != '.' )
    {   unsigned long l_file_mask = E_main_Q_s0_R_strlen( data->found_dir );
        if( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {   unsigned long file_h_not_to_libs_buffer_size = data->file_h_not_to_libs_buffer_size;
            char *file_h_not_to_libs_buffer = data->file_h_not_to_libs_buffer;
            data->file_h_not_to_libs_buffer_size = data->file_h_to_libs_buffer_size;
            data->file_h_not_to_libs_buffer = HeapAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer_size );
            Vv( data->file_h_not_to_libs_buffer, "Unable to allocate" )
                return 1;
            CopyMemory( data->file_h_not_to_libs_buffer, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size );
            unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
            char *file_mask = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_dir + 2 + 1 );
            Vv( file_mask, "Unable to allocate" )
                return 1;
            CopyMemory( file_mask, data->found_dir, l_file_mask - 1 );
            E_main_Q_s_s0_I_strcpy( file_mask + l_file_mask - 1, found_file->cFileName );
            E_main_Q_s_s0_I_strcpy( file_mask + l_file_mask - 1 + l_dir, "\\*" );
            char *found_dir = data->found_dir;
            data->found_dir = file_mask;
            !( ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_program, data ))
            && !( ret = E_main_I_build_program_I_not_to_libs(data) );
            data->found_dir = found_dir;
            HeapFree( E_main_S_process_heap, 0, file_mask );
            data->file_h_not_to_libs_buffer_size = file_h_not_to_libs_buffer_size;
            HeapFree( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer );
            data->file_h_not_to_libs_buffer = file_h_not_to_libs_buffer;
        }else
        {   unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
            if( l_file > 3
            && !E_main_Q_s0_s0_I_strcmp( found_file->cFileName + l_file - 3, ".cx" )
            )
            {   file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_file + 1 );
                Vv( file, "Unable to allocate" )
                    return 1;
                CopyMemory( file, data->found_dir, l_file_mask - 1 );
                E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1, found_file->cFileName );
                h_file_cx = CreateFile( file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0 );
                V( h_file_cx != INVALID_HANDLE_VALUE, "Unable to open file" )
                    goto Err_1;
                fprintf( stderr, "Processing file \"%s\"...\n", file );
                file[ l_file_mask - 1 + l_file - 1 ] = '\0';
                h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                if( h_file != INVALID_HANDLE_VALUE )
                {   FILETIME file_time;
                    if( GetFileTime( h_file, 0, 0, &file_time ))
                    {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                        file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                        file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                        file_time_u.LowPart = file_time.dwLowDateTime;
                        file_time_u.HighPart = file_time.dwHighDateTime;
                        if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                            goto Cont_1;
                        SetEndOfFile( h_file );
                    }
                }else
                {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                    V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
                        goto Err_2;
                }
                if( E_main_I_cx_to_c( h_file_cx, h_file, data ))
                {   CloseHandle( h_file );
                    goto Err_2;
                }
                SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_1:         CloseHandle( h_file );
/*                unsigned long l_added = 22 + l_file - 2 + 4;
                char *file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size + l_added );
                Vv( file_h_not_to_libs_buffer_, "Unable to reallocate" )
                    goto Err_2;
                data->file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                MoveMemory( data->file_h_not_to_libs_buffer + l_added, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size );
                data->file_h_not_to_libs_buffer_size += l_added;
                E_main_Q_s_s0_I_strcpy( data->file_h_not_to_libs_buffer, "#include \"E_cplus_S_0_" );
                CopyMemory( data->file_h_not_to_libs_buffer + 22, found_file->cFileName, l_file - 2 );
                CopyMemory( data->file_h_not_to_libs_buffer + 22 + l_file - 2, "h\"\r\n", 4 );*/
                enc = E_main_Q_filename_I_encode( found_file->cFileName );
                if( !enc )
                    goto Err_2;
                unsigned long pos = E_main_Q_s0_I_strstr( data->file_h_not_to_libs_buffer, "#include \"E_cplus_S_language.h\"\r\n" ) + 33 - data->file_h_not_to_libs_buffer;
                char *s = data->file_h_not_to_libs_buffer + pos;
                do
                {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
                    if( s - data->file_h_not_to_libs_buffer == data->file_h_not_to_libs_buffer_size
                    || E_main_Q_s0_s0_I_strncmp( s, "#include \"", 10 )
                    || s[10] == 'E'
                    )
                        break;
                }while(TRUE);
                unsigned long l_enc = E_main_Q_s0_R_strlen(enc);
                unsigned long l_added = 10 + l_enc + 4;
                char *file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size + l_added );
                Vv( file_h_not_to_libs_buffer_, "Unable to reallocate" )
                    goto Err_3;
                s = file_h_not_to_libs_buffer_ + ( s - data->file_h_not_to_libs_buffer );
                data->file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                s = E_main_Q_s0_I_strstr( s + 15, "\r\n" ) + 2;
                MoveMemory( s + l_added, s, data->file_h_not_to_libs_buffer_size - ( s - data->file_h_not_to_libs_buffer ));
                E_main_Q_s_s0_I_strcpy( s, ", _F_uid( " );
                E_main_Q_s_s0_I_strcpy( s + 10, enc );
                CopyMemory( s + 10 + l_enc, " )\r\n", 4 );
                s += 10 + l_enc + 4 - 2;
                data->file_h_not_to_libs_buffer_size += l_added;
                do
                {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
                    if( s - data->file_h_not_to_libs_buffer + 22 > data->file_h_not_to_libs_buffer_size
                    || !E_main_Q_s0_s0_I_strncmp( s, "#include \"E_cplus_S_1_", 22 )
                    )
                        break;
                }while(TRUE);
                l_added = 22 + l_file - 2 + 4;
                file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size + l_added );
                Vv( file_h_not_to_libs_buffer_, "Unable to reallocate" )
                    goto Err_3;
                s = file_h_not_to_libs_buffer_ + ( s - data->file_h_not_to_libs_buffer );
                data->file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                MoveMemory( s + l_added, s, data->file_h_not_to_libs_buffer_size - ( s - data->file_h_not_to_libs_buffer ));
                data->file_h_not_to_libs_buffer_size += l_added;
                E_main_Q_s_s0_I_strcpy( s, "#include \"E_cplus_S_1_" );
                CopyMemory( s + 22, found_file->cFileName, l_file - 2 );
                CopyMemory( s + 22 + l_file - 2, "h\"\r\n", 4 );
                s += 22 + l_file - 2 + 4 - 1;
                do
                {   s = E_main_Q_s0_I_strstr( s, "\r\n" ) + 2;
                    if( s - data->file_h_not_to_libs_buffer + 22 > data->file_h_not_to_libs_buffer_size
                    || E_main_Q_s0_s0_I_strncmp( s, "#include \"E_cplus_S_1_", 22 )
                    )
                       break;
                }while(TRUE);
                file_h_not_to_libs_buffer_ = HeapReAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer, data->file_h_not_to_libs_buffer_size + l_added );
                Vv( file_h_not_to_libs_buffer_, "Unable to reallocate" )
                    goto Err_3;
                s = file_h_not_to_libs_buffer_ + ( s - data->file_h_not_to_libs_buffer );
                data->file_h_not_to_libs_buffer = file_h_not_to_libs_buffer_;
                MoveMemory( s + l_added, s, data->file_h_not_to_libs_buffer_size - ( s - data->file_h_not_to_libs_buffer ));
                data->file_h_not_to_libs_buffer_size += l_added;
                E_main_Q_s_s0_I_strcpy( s, "#include \"E_cplus_S_2_" );
                CopyMemory( s + 22, found_file->cFileName, l_file - 2 );
                CopyMemory( s + 22 + l_file - 2, "h\"\r\n", 4 );
                char *file_ = HeapReAlloc( E_main_S_process_heap, 0, file, l_file_mask - 1 + 12 + l_file - 2 + 1 + 1 );
                Vv( file_, "Unable to reallocate" )
                    goto Err_3;
                file = file_;
                E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1, "E_cplus_S_1_" );
                CopyMemory( file + l_file_mask - 1 + 12, found_file->cFileName, l_file - 2 );
                E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1 + 12 + l_file - 2, "h" );
                h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                if( h_file != INVALID_HANDLE_VALUE )
                {   FILETIME file_time;
                    if( GetFileTime( h_file, 0, 0, &file_time ))
                    {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                        file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                        file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                        file_time_u.LowPart = file_time.dwLowDateTime;
                        file_time_u.HighPart = file_time.dwHighDateTime;
                        if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                            goto Cont_2;
                        SetEndOfFile( h_file );
                    }
                }else
                {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                    V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
                        goto Err_3;
                }
                if( E_main_I_cx_to_h_1( h_file_cx, h_file, enc, data ))
                    goto Err_4;
                SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
                if( E_main_I_cx_to_h_2( h_file_cx, h_file, data ))
                    goto Err_4;
                SetFilePointer( h_file_cx, 0, 0, FILE_BEGIN );
Cont_2:         CloseHandle( h_file );
                file[ l_file_mask - 1 + 10 ] = '2';
                h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
                if( h_file != INVALID_HANDLE_VALUE )
                {   FILETIME file_time;
                    if( GetFileTime( h_file, 0, 0, &file_time ))
                    {   ULARGE_INTEGER file_cx_time_u, file_time_u;
                        file_cx_time_u.LowPart = found_file->ftLastWriteTime.dwLowDateTime;
                        file_cx_time_u.HighPart = found_file->ftLastWriteTime.dwHighDateTime;
                        file_time_u.LowPart = file_time.dwLowDateTime;
                        file_time_u.HighPart = file_time.dwHighDateTime;
                        if( file_cx_time_u.QuadPart <= file_time_u.QuadPart )
                            goto Cont_3;
                        SetEndOfFile( h_file );
                    }
                }else
                {   h_file = CreateFile( file, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
                    V( h_file != INVALID_HANDLE_VALUE, "Unable to create file" )
                        goto Err_3;
                }
                if( E_main_I_cx_to_h_3( h_file_cx, h_file, data, FALSE ))
                {   CloseHandle( h_file );
                    goto Err_4;
                }
Cont_3:         CloseHandle( h_file );
                HeapFree( E_main_S_process_heap, 0, enc );
                CloseHandle( h_file_cx );
                HeapFree( E_main_S_process_heap, 0, file );
            }
        }
    }
    return ret;
Err_4:
    CloseHandle( h_file );
Err_3:
    HeapFree( E_main_S_process_heap, 0, enc );
Err_2:
    CloseHandle( h_file_cx );
Err_1:
    HeapFree( E_main_S_process_heap, 0, file );
    return 1;
}
int
E_main_I_find_file_I_programs( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if(( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    && found_file->cFileName[0] != '.'
    )
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
        char *file_h_not_to_libs = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 24 + 1 );
        Vv( file_h_not_to_libs, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file_h_not_to_libs, "..\\program\\" );
        E_main_Q_s_s0_I_strcpy( file_h_not_to_libs + 11, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file_h_not_to_libs + 11 + l_dir, "\\E_cplus_S_not_to_libs.h" );
        DeleteFile( file_h_not_to_libs );
        HeapFree( E_main_S_process_heap, 0, file_h_not_to_libs );
        data->file_h_not_to_libs_buffer_size = data->file_h_to_libs_buffer_size;
        data->file_h_not_to_libs_buffer = HeapAlloc( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer_size );
        Vv( data->file_h_not_to_libs_buffer, "Unable to allocate" )
            return 1;
        CopyMemory( data->file_h_not_to_libs_buffer, data->file_h_to_libs_buffer, data->file_h_to_libs_buffer_size );
        char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 2 + 1 );
        E_main_Q_s_s0_I_strcpy( file_mask, "..\\program\\" );
        E_main_Q_s_s0_I_strcpy( file_mask + 11, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file_mask + 11 + l_dir, "\\*" );
        data->found_dir = file_mask;
        !( ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_program, data ))
        && !( ret = E_main_I_build_program_I_not_to_libs(data) );
        HeapFree( E_main_S_process_heap, 0, file_mask );
        HeapFree( E_main_S_process_heap, 0, data->file_h_not_to_libs_buffer );
    }
    return ret;
}
int
E_main_I_build( void
){  struct E_main_Z_build_resources data;
    int ret = E_main_Q_build_resources_M( &data );
    if(ret)
        return 1;
    !( ret = E_main_I_find_file( "..\\module\\*", ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_modules_1, &data ))
    && !( ret = E_main_I_find_file( "..\\module\\*", ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_modules_2, &data ))
    && !( ret = E_main_I_build_I_to_libs( &data ))
    && !( ret = E_main_I_find_file( "..\\program\\*", ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_programs, &data ));
    E_main_Q_build_resources_W( &data );
    return ret;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
E_main_I_find_file_I_clean_module( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  if( !( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( data->found_dir );
        unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
        char *file = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 1 + l_file - 1 + 1 );
        Vv( file, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file + 10, data->found_dir );
        file[ 10 + l_dir ] = '\\';
        CopyMemory( file + 10 + l_dir + 1, found_file->cFileName, l_file - 1 );
        file[ 10 + l_dir + 1 + l_file - 1 ] = '\0';
        fprintf( stderr, "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        file[ 10 + l_dir + 1 + l_file - 2 ] = 'o';
        fprintf( stderr, "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        char *file_ = HeapReAlloc( E_main_S_process_heap, 0, file, 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2 + 1 + 1 );
        Vv( file_, "Unable to reallocate" )
        {   HeapFree( E_main_S_process_heap, 0, file );
            return 1;
        }
        file = file_;
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1, "E_cplus_S_0_" );
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1 + 12, data->found_dir );
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1 + 12 + l_dir, "__" );
        CopyMemory( file + 10 + l_dir + 1 + 12 + l_dir + 2, found_file->cFileName, l_file - 2 );
        E_main_Q_s_s0_I_strcpy( file + 10 + l_dir + 1 + 12 + l_dir + 2 + l_file - 2, "h" );
        fprintf( stderr, "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        file[ 10 + l_dir + 1 + 10 ] = '1';
        fprintf( stderr, "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        file[ 10 + l_dir + 1 + 10 ] = '2';
        fprintf( stderr, "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        HeapFree( E_main_S_process_heap, 0, file );
    }
    return 0;
}
int
E_main_I_find_file_I_clean_modules( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if(( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    && found_file->cFileName[0] != '.'
    )
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
        char *file_mask = HeapAlloc( E_main_S_process_heap, 0, 10 + l_dir + 5 + 1 );
        E_main_Q_s_s0_I_strcpy( file_mask, "..\\module\\" );
        E_main_Q_s_s0_I_strcpy( file_mask + 10, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file_mask + 10 + l_dir, "\\*.cx" );
        data->found_dir = found_file->cFileName;
        ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_clean_module, data );
    }
    return ret;
}
int
E_main_I_find_file_I_clean_program( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if( found_file->cFileName[0] != '.' )
    {   unsigned long l_file_mask = E_main_Q_s0_R_strlen( data->found_dir );
        if( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {   char *file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + 23 + 1 );
            Vv( file, "Unable to allocate" )
                return 1;
            CopyMemory( file, data->found_dir, l_file_mask - 1 );
            E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1, "E_cplus_S_not_to_libs.h" );
            printf( "Removing file \"%s\"...\n", file );
            DeleteFile(file);
            HeapFree( E_main_S_process_heap, 0, file );
            unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
            char *file_mask = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_dir + 2 + 1 );
            CopyMemory( file_mask, data->found_dir, l_file_mask - 1 );
            E_main_Q_s_s0_I_strcpy( file_mask + l_file_mask - 1, found_file->cFileName );
            E_main_Q_s_s0_I_strcpy( file_mask + l_file_mask - 1 + l_dir, "\\*" );
            char *found_dir = data->found_dir;
            data->found_dir = file_mask;
            ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_clean_program, data );
            data->found_dir = found_dir;
            HeapFree( E_main_S_process_heap, 0, file_mask );
        }else
        {   unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
            if( l_file > 3
            && !E_main_Q_s0_s0_I_strcmp( found_file->cFileName + l_file - 3, ".cx" )
            )
            {   unsigned long l_file = E_main_Q_s0_R_strlen( found_file->cFileName );
                char *file = HeapAlloc( E_main_S_process_heap, 0, l_file_mask - 1 + l_file + 1 );
                Vv( file, "Unable to allocate" )
                    return 1;
                CopyMemory( file, data->found_dir, l_file_mask - 1 );
                CopyMemory( file + l_file_mask - 1, found_file->cFileName, l_file - 1 );
                file[ l_file_mask - 1 + l_file - 1 ] = '\0';
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                file[ l_file_mask - 1 + l_file - 2 ] = 'o';
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                char *file_ = HeapReAlloc( E_main_S_process_heap, 0, file, l_file_mask - 1 + 12 + l_file - 2 + 1 + 1 );
                Vv( file_, "Unable to reallocate" )
                {   HeapFree( E_main_S_process_heap, 0, file );
                    return 1;
                }
                file = file_;
                E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1 , "E_cplus_S_0_" );
                CopyMemory( file + l_file_mask - 1 + 12, found_file->cFileName, l_file - 2 );
                E_main_Q_s_s0_I_strcpy( file + l_file_mask - 1 + 12 + l_file - 2, "h" );
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                file[ l_file_mask - 1 + 10 ] = '1';
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                file[ l_file_mask - 1 + 10 ] = '2';
                printf( "Removing file \"%s\"...\n", file );
                DeleteFile(file);
                HeapFree( E_main_S_process_heap, 0, file );
            }
        }
    }
    return ret;
}
int
E_main_I_find_file_I_clean_programs( WIN32_FIND_DATA *found_file
, struct E_main_Z_build_resources *data
){  int ret = 0;
    if(( found_file->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    && found_file->cFileName[0] != '.'
    )
    {   unsigned long l_dir = E_main_Q_s0_R_strlen( found_file->cFileName );
        char *file = HeapAlloc( E_main_S_process_heap, 0, 11 + l_dir + 24 + 1 );
        Vv( file, "Unable to allocate" )
            return 1;
        E_main_Q_s_s0_I_strcpy( file, "..\\program\\" );
        E_main_Q_s_s0_I_strcpy( file + 11, found_file->cFileName );
        E_main_Q_s_s0_I_strcpy( file + 11 + l_dir, "\\E_cplus_S_not_to_libs.h" );
        printf( "Removing file \"%s\"...\n", file );
        DeleteFile(file);
        char *file_mask = HeapReAlloc( E_main_S_process_heap, 0, file, 11 + l_dir + 1 + 1 + 1 );
        Vv( file_mask, "Unable to reallocate" )
        {   HeapFree( E_main_S_process_heap, 0, file );
            return 1;
        }
        data->found_dir = file_mask;
        E_main_Q_s_s0_I_strcpy( file_mask + 11 + l_dir + 1, "*" );
        ret = E_main_I_find_file( file_mask, ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_clean_program, data );
        HeapFree( E_main_S_process_heap, 0, file_mask );
    }
    return ret;
}
int
E_main_I_clean( void
){  fputs( "Removing file \"..\\module\\E_cplus_S_to_libs.h\"...\n", stderr );
    DeleteFile( "..\\module\\E_cplus_S_to_libs.h" );
    struct E_main_Z_build_resources data;
    int ret = 0;
    !( ret = E_main_I_find_file( "..\\module\\*", ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_clean_modules, &data ))
    && !( ret = E_main_I_find_file( "..\\program\\*", ( E_main_I_find_file_Z_proc )E_main_I_find_file_I_clean_programs, &data ));
    return ret;
}
//==============================================================================
enum E_main_Z_func                                                                                                                        
{ E_main_Z_func_S_build
, E_main_Z_func_S_clean
};
int
main( int argc
, char *argv[]
){  if( argc > 2 )
        return 1;
    enum E_main_Z_func func;
    if( argc == 1 )
        func = E_main_Z_func_S_build;
    else if( E_main_Q_s0_s0_I_strcmp( argv[1], "all" ) == 0
    || E_main_Q_s0_s0_I_strcmp( argv[1], "build" ) == 0
    )
        func = E_main_Z_func_S_build;
    else if( E_main_Q_s0_s0_I_strcmp( argv[1], "clean" ) == 0 )
        func = E_main_Z_func_S_clean;
    else
    {   fputs( "Invalid command.\n", stderr );
        return 1;
    }
    E_main_S_process_heap = GetProcessHeap();
    int ret;
    if( func == E_main_Z_func_S_build )
        ret = E_main_I_build();
    else
        ret = E_main_I_clean();
    return ret;
}
//******************************************************************************

