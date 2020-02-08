#include "0.h"
#define _single_thread_begin    E_base_S->E_mem_Q_blk_S_threads_sync_mutex = CreateMutex( 0, TRUE, "mem_blk_S_single_thread_begin" )
#define _single_thread_end      ReleaseMutex( E_base_S->E_mem_Q_blk_S_threads_sync_mutex )
//==============================================================================
B
E_mem_Q_blk_T_new_0( P p
){  SYSTEM_INFO si;
    GetSystemInfo( &si );
    return (Pc)p < (Pc)si.lpMinimumApplicationAddress;
}
#define E_mem_Q_blk_I_assert_on_return(line)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO do optymalizacji? po sprawdzeniu, czy procesory czasem wewnętrznie nie optymalizują kopiowania bajtowego.
P
E_mem_Q_blk_I_copy( P dst
, P src
, N l
){  Pc dst_c = dst, src_c = src;
    for_n( i, l )
    {   *dst_c = *src_c;
        dst_c++;
        src_c++;
    }
    return dst_c;
}
//TODO do optymalizacji? jw.
P
E_mem_Q_blk_I_copy_rev( P dst
, P src
, N l
){  Pc dst_end = (Pc)dst + l, src_end = (Pc)src + l;
    while( src_end != src )
    {   dst_end--;
        src_end--;
        *dst_end = *src_end;
    }
    return dst_end;
}
//TODO do optymalizacji?
P
E_mem_Q_blk_P_fill_c( P p
, N n
, C c
){  Pc s = p;
    for_n( i, n )
        *s++ = c;
    return s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
B
E_mem_Q_blk_Q_sys_table_mf_I_unite( N table_i
, N rel_addr_p
, N rel_addr_l
, P p
, N l
){  N i_found = ~0;
    for_n( i, E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ) ///szukanie bloku przyległego od dołu.
    {   Pc *p_ = (P)( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p );
        N *l_ = (P)( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l );
        if( *p_ + *l_ == p )
        {   p = *p_;
            l = *l_ += l;
            i_found = i;
            break;
        }
    }
    for_n_( i, E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ) ///szukanie bloku przyległego od góry.
    {   Pc *p_ = (P)( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p );
        N *l_ = (P)( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l );
        if( (Pc)p + l == *p_ )
        {   if( ~i_found ) ///był znaleziony blok przyległy od dołu.
            {   *( Pc * )( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + i_found * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) += *l_;
                *p_ = 0;
                *l_ = 0;
            }else
            {   *p_ = p;
                *l_ += l;
                i_found = i;
            }
            break;
        }
    }
    return !!~i_found;
}
N
E_mem_Q_blk_Q_sys_table_mf_P_put( N table_i
, N rel_addr_p
, N rel_addr_l
, P p
, N l
){  if( !E_mem_Q_blk_Q_sys_table_mf_I_unite( table_i, rel_addr_p, rel_addr_l, p, l ))
    {   if( table_i == E_mem_Q_blk_S_allocated_S_free_id
        && l >= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u
        ){  if( (Pc)p + l == E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p ) ///nowy blok jest przyległy od dołu do tablicy bloków.
            {   E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p -= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n++;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p;
                free_p[0].p = l != E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u ? p : 0;
                free_p[0].l = l - E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                return 0;
            }
            if( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p + E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u == p ) ///nowy blok jest przyległy od góry do tablicy bloków.
            {   struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p;
                free_p[ E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ].p = l != E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u
                  ? (Pc)p + E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u
                  : 0;
                free_p[ E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ].l = l - E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n++;
                return 0;
            }
        }
        N i = E_mem_Q_blk_Q_sys_table_R_new_id( table_i, rel_addr_p, rel_addr_l, p, l );
        if( !~i )
            return ~0;
    }
    return 0;
}
///dla tablic systemowych “mapped” i “free” ‘alokuje’ tyle “n”, ile żądane, lub więcej.
P
E_mem_Q_blk_Q_table_M_from_free_or_map_0( N allocated_2_table_i
, N u
, N n
, P p ///adres uprzedniej zawartości lub 0, gdy brak.
, N l ///i rozmiar. jeśli “p == 0”, to parametr ignorowany.
, N l_rel
){  N l_1 = n * u;
    Pc p_1;
    if(n)
    {   if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id
        && p ///uprzedni obszar tablicy staje się wolnym blokiem.
        ){  n++;
            l_1 += E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
        }
        N l_ = ~0;
        N i_found;
        struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
        for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku na całą tablicę.
            if( free_p[ free_i ].l >= l_1
            && free_p[ free_i ].l < l_
            ){  l_ = free_p[ free_i ].l;
                i_found = free_i;
                if( l_ == l_1 )
                    break;
            }
        if( !~l_ )
        {   ///jeśli żądanie ‘alokacji’ tablicy systemowej “mapped” lub “free” przyszło z rekurencji, to wtedy żądanie ‘alokacji’ takiej tablicy oznacza brak wolnych wpisów na poprzednią czekającą ‘alokację’ ogólną lub tablicy “allocated”, a za chwilę będą być może potrzebne jeszcze kolejne wpisy na bieżącą ‘alokację’. dlatego należy ‘alokować’ odrazu minimalną ilość rezerwowych wpisów (dla jednej tablicy, by nie wymuszać statycznie jednoczesnej ‘realokacji’ obu tablic), ponieważ w pesymistycznym przypadku ewentualne ‘doalokowanie’ jednej nadmiarowej strony pamięci na nie wykorzystane rezerwowe wpisy mniej kosztuje niż drugie kopiowanie tej samej tablicy dla ‘alokacji’ kolejnych wpisów w tej kolejnej rekurencji.
            Pc src_page, src_page_end;
            if(p) ///będzie kopiowanie, a teraz przygotowanie do ‘remapowania’ ‚środka’ zamiast kopiowania.
            {   src_page = E_simple_Z_p_I_align_up_to_v_2( (Pc)p, E_base_S->E_mem_S_page_size );
                src_page_end = E_simple_Z_p_I_align_down_to_v_2( (Pc)p + l, E_base_S->E_mem_S_page_size );
                ///zapewnienie liczby wpisów w tablicy systemowej właśnie ‘realokowanej’— potrzebnej dla pesymistycznego przypadku niescalenia z już obecnymi nowych bloków dodawanych w tym wywołaniu procedury do takiej tablicy— by nie mogło wystąpić rekurencyjne, zapętlające wywołanie tej procedury dla tej samej tablicy bez możliwości uzyskania nowych wpisów.
                if( src_page < src_page_end ) ///będzie ‘remapowanie’ wewnętrznych “stron” pamięci (bloków o adresach wyrównanych do rozmiaru “strony”).
                {   if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id ) ///zostaną one wzięte z obszaru dostępnych wolnych bloków (‘przemapowane’), a krańcowe pozostałości (od obszaru wyrównanego do “stron” pamięci) staną się wolnymi blokami.
                    {   n--; ///nie będzie potrzeba osobno wpisywać uprzedniego rozmiaru tablicy.
                        l_1 -= E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
                        if( src_page != p ) ///będzie wolny początkowy fragment w pierwszej “stronie” pamięci: w źródłowym bloku i nowym.
                        {   n += 2;
                            l_1 += 2 * E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
                        }
                        if( src_page_end != (Pc)p + l ) ///będzie wolny końcowy fragment w ostatniej “stronie” pamięci: w źródłowym bloku i nowym.
                        {   n += 2;
                            l_1 += 2 * E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
                        }
                    }else if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_mapped_id ) ///zostaną one wzięte z obszaru ‘zmapowanych’, a krańcowe “strony” staną się osobnymi ‘zmapowanymi’ blokami.
                    {   n += 2;
                        l_1 += 2 * E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
                    }
                }else if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_mapped_id ///nowy blok, ‘zmapowany’ na tablicę ‘zmapowanych’— musi być wpisany do tablicy.
                || allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id ///fragment pozostały do wyrównania do rozmiaru “stron” pamięci staje się wolnym blokiem.
                ){  n++;
                    l_1 += E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
                }
            }else if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id ) ///fragment pozostały do wyrównania do rozmiaru “stron” pamięci staje się wolnym blokiem.
            {   n++;
                l_1 += E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u;
            }
            N dst_rel = 0;
            if( p
            && src_page < src_page_end
            )
            {   l_ = E_simple_Z_n_I_align_up_to_v_2( l_1 - ( src_page - (Pc)p ), E_base_S->E_mem_S_page_size );
                l_ += dst_rel = E_simple_Z_n_I_align_up_to_v_2( l_rel + ( src_page - (Pc)p ), E_base_S->E_mem_S_page_size );
            }else
                l_ = E_simple_Z_n_I_align_up_to_v_2( l_1, E_base_S->E_mem_S_page_size );
            if( !( p_1 = VirtualAlloc( 0
            , l_
            , MEM_COMMIT
            , PAGE_READWRITE
            )))
                return 0;
            E_mem_Q_blk_P_fill_c( p_1, l_, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            Pc dst_page;
            Pc p_ = p_1;
            if(p)
            {   //TODO poniżej być może zastąpić (bez deintegracji) procedurą “move”, która powstanie.
                if( src_page < src_page_end )
                {   dst_page = p_1 + dst_rel;
                    p_ = dst_page - ( src_page - (Pc)p );
                    if( src_page != p )
                        E_mem_Q_blk_I_copy( p_, p, src_page - (Pc)p );
                    p_ -= l_rel;
                    E_mem_Q_blk_I_copy( dst_page, src_page, src_page_end - src_page );
                    if( !VirtualFree( src_page, src_page_end - src_page, MEM_DECOMMIT ))
                        V( "VirtualFree" );
                    E_mem_Q_blk_I_copy( dst_page + ( src_page_end - src_page ), src_page_end, (Pc)p + l - src_page_end );
                }else
                    E_mem_Q_blk_I_copy( p_1 + l_rel, p, l );
                if( allocated_2_table_i == E_base_S->E_mem_Q_blk_S_table_allocated_id )
                    E_base_S->E_mem_Q_blk_S_allocated = (P)p_;
            }else
                E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u = u;
            E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].p = p_;
            struct E_mem_Q_blk_Z_free free_p_;
            if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id )
            {   free_p = (P)p_;
                if( p
                && src_page < src_page_end
                )
                {   N i = 0;
                    if( src_page != p )
                    {   if( E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, src_page - (Pc)p ))
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = 0;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = 0;
                        }else
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = p;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = src_page - (Pc)p;
                        }
                        i++;
                        if( E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_1, p_ - p_1 ))
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = 0;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = 0;
                        }else
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = p_1;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = p_ - p_1;
                        }
                        i++;
                    }
                    if( src_page_end != (Pc)p + l )
                    {   if( E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, src_page_end, (Pc)p + l - src_page_end ))
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = 0;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = 0;
                        }else
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = src_page_end;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = (Pc)p + l - src_page_end;
                        }
                        i++;
                        if( E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_ + l_1, p_1 + l_ - ( p_ + l_1 )))
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = 0;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = 0;
                        }else
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].p = p_ + l_1;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + i ].l = p_1 + l_ - ( p_ + l_1 );
                        }
                    }
                }else
                {   if( l_ != l_1
                    && !E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_1 + l_1, l_ - l_1 )
                    )
                    {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = p_1 + l_1;
                        free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = l_ - l_1;
                    }else
                    {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = 0;
                        free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = 0;
                    }
                    if(p)
                        if( E_mem_Q_blk_Q_sys_table_mf_I_unite( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, l ))
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + 1 ].p = 0;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + 1 ].l = 0;
                        }else
                        {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + 1 ].p = p;
                            free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n + 1 ].l = l;
                        }
                }
            }else
            {   if( p
                && src_page < src_page_end
                )
                {   if( src_page != p )
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, src_page - (Pc)p ))
                            return 0;
                    if( p_ != p_1 )
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_1, p_ - p_1 ))
                            return 0;
                    if( src_page_end != (Pc)p + l )
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, src_page_end, (Pc)p + l - src_page_end ))
                            return 0;
                    if( p_1 + l_ != p_ + l_rel + l_1 )
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_ + l_rel + l_1, p_1 + l_ - ( p_ + l_rel + l_1 )))
                            return 0;
                }else
                {   if( l_ != l_1 )
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p_1 + l_1, l_ - l_1 ))
                            return 0;
                    if(p)
                        if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, l ))
                            return 0;
                }
            }
            struct E_mem_Q_blk_Z_mapped mapped_p_;
            if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_mapped_id )
            {   if( src_page < src_page_end )
                {   struct E_mem_Q_blk_Z_mapped *mapped_p = (P)p_;
                    for_i( i, E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n )
                    {   Pc p_end = mapped_p->p + mapped_p->l;
                        if( mapped_p->p <= (Pc)p
                        && (Pc)p < p_end
                        )
                        {   mapped_p->l = src_page - mapped_p->p;
                            if( mapped_p->p == p )
                                mapped_p->p = 0;
                            if( (Pc)p + l != p_end )
                            {   mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = src_page_end;
                                mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = p_end - src_page_end;
                            }else
                            {   mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = 0;
                                mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = 0;
                            }
                            break;
                        }
                        mapped_p++;
                    }
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n++;
                }
                struct E_mem_Q_blk_Z_mapped *mapped_p = (P)p_;
                if( E_mem_Q_blk_Q_sys_table_mf_I_unite( allocated_2_table_i, (Pc)&mapped_p_.p - (Pc)&mapped_p_, (Pc)&mapped_p_.l - (Pc)&mapped_p_, p_1, l_ ))
                {   mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = 0;
                    mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = 0;
                }else
                {   mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = p_1;
                    mapped_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = l_;
                }
            }else
            {   if( p
                && src_page < src_page_end
                ){  struct E_mem_Q_blk_Z_mapped *mapped_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].p;
                    for_i( i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_mapped_id ].n )
                    {   if( mapped_p->p <= (Pc)p
                        && mapped_p->p + mapped_p->l > (Pc)p
                        )
                        {   Pc p_end = mapped_p->p + mapped_p->l;
                            mapped_p->l = src_page - mapped_p->p;
                            if( mapped_p->p == p )
                                mapped_p->p = 0;
                            if( (Pc)p + l != p_end )
                                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_mapped_id, (Pc)&mapped_p_.p - (Pc)&mapped_p_, (Pc)&mapped_p_.l - (Pc)&mapped_p_, src_page_end, p_end - src_page_end ))
                                    return 0;
                            break;
                        }
                        mapped_p++;
                    }
                }
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_mapped_id, (Pc)&mapped_p_.p - (Pc)&mapped_p_, (Pc)&mapped_p_.l - (Pc)&mapped_p_, p_1, l_ ))
                    return 0;
            }
            E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n = n;
            return p_;
        }
        p_1 = free_p[ i_found ].p;
        if( l_ == l_1 )
            free_p[ i_found ].p = 0;
        else
            free_p[ i_found ].p += l_1;
        free_p[ i_found ].l -= l_1;
        if(p)
        {   E_mem_Q_blk_I_copy( p_1 + l_rel, p, l );
            if( allocated_2_table_i == E_base_S->E_mem_Q_blk_S_table_allocated_id )
                E_base_S->E_mem_Q_blk_S_allocated = (P)p_1;
        }
    }else if( !( p_1 = E_mem_Q_blk_R_new_0() ))
        return 0;
    if( !p ) //NDFN rozpoznanie niebezpośrednie, mimo że jednoznaczne w obecnej implementacji.
        E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].u = u;
    E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].p = p_1;
    if(p)
    {   struct E_mem_Q_blk_Z_free free_p_;
        if( allocated_2_table_i == E_mem_Q_blk_S_allocated_S_free_id )
        {   struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].p;
            if( E_mem_Q_blk_Q_sys_table_mf_I_unite( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, l ))
            {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = 0;
                free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = 0;
            }else
            {   free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].p = p;
                free_p[ E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n ].l = l;
            }
        }else
            if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, l ))
                return 0;
    }
    E_base_S->E_mem_Q_blk_S_allocated[ allocated_2_table_i ].n = n; ///końcowe wpisy i tak nie zawierałyby danych dla powyższego “unite”, a “E_mem_Q_blk_S_allocated_S_mapped_id” może wystąpić tylko w końcowym wywołaniu rekurencyjnym (pojedynczy poziom rekurencji), nie w odzewnętrznym, początkowym wywołaniu tej procedury, więc powiększenie tablicy dopiero tutaj.
    return p_1;
}
N
E_mem_Q_blk_Q_sys_table_R_new_id( N table_i
, N rel_addr_p
, N rel_addr_l
, P p ///adres do nowego wpisu.
, N l ///i rozmiar.
){  Pc p_0 = E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p;
    for_n( i, E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ) ///szukanie wolnego wpisu w tablicy.
        if( !*( P * )( p_0 + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ))
        {   if( table_i != E_base_S->E_mem_Q_blk_S_table_allocated_id )
                *( N * )( p_0 + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) = l;
            *( P * )( p_0 + i * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ) = p;
            return i;
        }
    struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
    for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
        if( free_p[ free_i ].p + free_p[ free_i ].l == p_0 )
        {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u )
            {   if( free_p[ free_i ].l == E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u )
                    free_p[ free_i ].p = 0;
                free_p[ free_i ].l -= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                if( table_i != E_base_S->E_mem_Q_blk_S_table_allocated_id )
                    *( N * )( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p - E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) = l;
                *( P * )( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p - E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ) = p;
                E_base_S->E_mem_Q_blk_S_allocated[ table_i ].p -= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n++;
                if( table_i == E_base_S->E_mem_Q_blk_S_table_allocated_id )
                    E_base_S->E_mem_Q_blk_S_allocated = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id++ ].p;
                return 0;
            }
            break;
        }
    N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
    for_n_( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
        if( p_0 + l_0 == free_p[ free_i ].p )
        {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u )
            {   if( free_p[ free_i ].l != E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u )
                    free_p[ free_i ].p += E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                else
                    free_p[ free_i ].p = 0;
                free_p[ free_i ].l -= E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u;
                if( table_i != E_base_S->E_mem_Q_blk_S_table_allocated_id )
                    *( N * )( p_0 + l_0 + rel_addr_l ) = l;
                *( P * )( p_0 + l_0 + rel_addr_p ) = p;
                return E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n++;
            }
            break;
        }
    Pc p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( table_i
    , E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u
    , E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n + 1
    , E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n ? p_0 : 0
    , l_0
    , 0
    );
    if( !p_1 )
        return ~0;
    if( table_i == E_mem_Q_blk_S_allocated_S_mapped_id
    || table_i == E_mem_Q_blk_S_allocated_S_free_id
    )
    {   *( P * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ) = 0;
        *( N * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) = 0;
        if( !E_mem_Q_blk_Q_sys_table_mf_I_unite( table_i, rel_addr_p, rel_addr_l, p, l ))
        {   *( P * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ) = p;
            *( N * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) = l;
        }
    }else
    {   *( P * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_p ) = p;
        if( table_i != E_base_S->E_mem_Q_blk_S_table_allocated_id )
            *( N * )( p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1 ) * E_base_S->E_mem_Q_blk_S_allocated[ table_i ].u + rel_addr_l ) = l;
    }
    return E_base_S->E_mem_Q_blk_S_allocated[ table_i ].n - 1;
}
__attribute__ ((__malloc__))
P
E_mem_Q_blk_R_new_0( void
){  SYSTEM_INFO si;
    GetSystemInfo( &si );
    Pc p_end = si.lpMinimumApplicationAddress;
    Pc p = (P)1;
    B exists;
    O{  exists = no;
        N allocated_i = E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n;
        while( allocated_i-- )
        {   if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == p )
            {   exists = yes;
                break;
            }
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p < p_end
            && E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p > p
            ){  p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                exists = yes;
                break;
            }
        }
        if( !exists )
            return p;
        if( ++p == p_end )
            break;
    }
    V( "out of empty block address space" );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
__attribute__ ((__malloc__))
P
E_mem_Q_blk_M_tab(
  N u ///!= 0
, N n
){  _single_thread_begin;
    struct E_mem_Q_blk_Z_allocated allocated_p;
    N allocated_i = E_mem_Q_blk_Q_sys_table_R_new_id( E_base_S->E_mem_Q_blk_S_table_allocated_id, (Pc)&allocated_p.p - (Pc)&allocated_p, (Pc)&allocated_p.n - (Pc)&allocated_p, 0, 0 );
    if( !~allocated_i )
    {   E_mem_Q_blk_I_assert_on_return( __LINE__ );
        _single_thread_end;
        return 0;
    }
    if( !E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i, u, n, 0, 0, 0 ))
    {   E_mem_Q_blk_I_assert_on_return( __LINE__ );
        _single_thread_end;
        return 0;
    }
    E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
    P p_ = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    return p_;
}
P
E_mem_Q_blk_M( N l
){  return E_mem_Q_blk_M_tab( 1, l );
}
__attribute__ ((__malloc__))
P
E_mem_Q_blk_M_replace_tab( P p
, N u ///!= 0
, N n
){  if(!p)
        V( "E_mem_Q_blk_M_replace_tab" );
    _single_thread_begin;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == p )
        {   if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u ))
                    return 0;
            }
            if( !E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i, u, n, 0, 0, 0 ))
                E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p = E_mem_Q_blk_R_new_0();
            else
                E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            P p_ = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
            E_mem_Q_blk_I_assert_on_return( __LINE__ );
            _single_thread_end;
            return p_;
        }
    _single_thread_end;
    V( "E_mem_Q_blk_M_replace_tab" );
}
P
E_mem_Q_blk_M_replace( P p
, N l
){  return E_mem_Q_blk_M_replace_tab( p, 1, l );
}
__attribute__ ((__malloc__))
P
E_mem_Q_blk_M_split( P p
, N i
){  if( !p )
        V( "E_mem_Q_blk_M_split" );
    _single_thread_begin;
    struct E_mem_Q_blk_Z_allocated allocated_p;
    N allocated_i = E_mem_Q_blk_Q_sys_table_R_new_id( E_base_S->E_mem_Q_blk_S_table_allocated_id, (Pc)&allocated_p.p - (Pc)&allocated_p, (Pc)&allocated_p.n - (Pc)&allocated_p, 0, 0 );
    if( !~allocated_i )
    {   E_mem_Q_blk_I_assert_on_return( __LINE__ );
        _single_thread_end;
        return 0;
    }
    for_n( allocated_j, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_j ].p == p )
        {   E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n = E_base_S->E_mem_Q_blk_S_allocated[ allocated_j ].n - i;
            E_base_S->E_mem_Q_blk_S_allocated[ allocated_j ].n = i;
            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u = E_base_S->E_mem_Q_blk_S_allocated[ allocated_j ].u;
            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p = (Pc)p + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_j ].u;
            P p_ = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
            E_mem_Q_blk_I_assert_on_return( __LINE__ );
            _single_thread_end;
            return p_;
        }
    _single_thread_end;
    V( "E_mem_Q_blk_M_split" );
}
N
E_mem_Q_blk_W( P p
){  if( U_R( E_base_S->E_flow_S_signal, exit_all )) //NDFN to sprawdzenie raczej umieszczać tylko w funkcjach wysokopoziomowych.
        return 0;
    if( !p )
        return ~0;
    _single_thread_begin;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == p )
        {   E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p = 0;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_, p, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u ))
                {   _single_thread_end;
                    return ~0;
                }
            }
            E_mem_Q_blk_I_assert_on_return( __LINE__ );
            _single_thread_end;
            return 0;
        }
    _single_thread_end;
    V( "E_mem_Q_blk_W" );
}
//------------------------------------------------------------------------------
P
E_mem_Q_blk_I_add_( P p
, N n
, N *n_prepended
, N *n_appended
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   Pc p_0 = 0;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   N l = n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                N l_1 = 0;
                p_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
                for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
                    if( free_p[ free_i ].p + free_p[ free_i ].l == p_0 )
                    {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u )
                        {   l_1 = free_p[ free_i ].l;
                            if( l_1 > l )
                                l_1 = l;
                            else if( l_1 < l )
                                l_1 = E_simple_Z_n_I_align_down_to_v( l_1, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u );
                            l -= l_1;
                        }
                        break;
                    }
                if( !l )
                {   if( free_p[ free_i ].l == l_1 )
                        free_p[ free_i ].p = 0;
                    free_p[ free_i ].l -= l_1;
                    *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                    E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                    if( n_prepended )
                        *n_prepended = n;
                    if( n_appended )
                        *n_appended = 0;
                    return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1;
                }
                for_n( free_j, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
                    if( p_0 + l_0 == free_p[ free_j ].p )
                    {   if( free_p[ free_j ].l >= l )
                        {   if( free_p[ free_j ].l != l )
                                free_p[ free_j ].p += l;
                            else
                                free_p[ free_j ].p = 0;
                            free_p[ free_j ].l -= l;
                            if( l_1 )
                            {   if( free_p[ free_i ].l == l_1 )
                                    free_p[ free_i ].p = 0;
                                free_p[ free_i ].l -= l_1;
                                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                            }
                            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                            if( n_prepended )
                            {   *n_prepended = l_1 / E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                                E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, *n_prepended * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                            }
                            if( n_appended )
                            {   *n_appended = l / E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                                E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + ( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n - *n_appended ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, *n_appended * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                            }
                            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1 + l_0;
                        }
                        break;
                    }
                l += l_1; ///przywraca oryginalną wartość sprzed scalenia od dołu, skoro był blok przyległy od dołu, zabrakło do pełnej liczby od góry.
            }
            P p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n + n
            , p_0
            , l_0
            , 0
            );
            if( !p_1 )
                return p_1;
            *( P * )p = p_1;
            E_mem_Q_blk_P_fill_c( (Pc)p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n - n ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            if( n_prepended )
                *n_prepended = 0;
            if( n_appended )
                *n_appended = n;
            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_0;
        }
    return (P)~0;
}
P
E_mem_Q_blk_I_prepend_append_( P p
, N n_prepend
, N n_append
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   Pc p_0 = 0;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   N l = ( n_prepend + n_append ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                N l_1 = 0;
                p_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
                for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
                    if( free_p[ free_i ].p + free_p[ free_i ].l == p_0 )
                    {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u )
                        {   l_1 = free_p[ free_i ].l;
                            if( l_1 > l )
                                l_1 = l;
                            else if( l_1 < l )
                                l_1 = E_simple_Z_n_I_align_down_to_v( l_1, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u );
                            l -= l_1;
                        }
                        break;
                    }
                if( !n_append
                && !l
                ){  if( free_p[ free_i ].l == l_1 )
                        free_p[ free_i ].p = 0;
                    free_p[ free_i ].l -= l_1;
                    *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n_prepend;
                    return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1;
                }
                //kontynuacja od tej linii: trzeba wybrać optymalne przesunięcie pomiędzy blokiem poprzedzającym a następującym, by ewentualnie nie kopiować.
                for_n( free_j, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
                    if( p_0 + l_0 == free_p[ free_j ].p )
                    {   if( free_p[ free_j ].l >= l )
                        {   if( free_p[ free_j ].l != l )
                                free_p[ free_j ].p += l;
                            else
                                free_p[ free_j ].p = 0;
                            free_p[ free_j ].l -= l;
                            if( l_1 )
                            {   if( free_p[ free_i ].l == l_1 )
                                    free_p[ free_i ].p = 0;
                                free_p[ free_i ].l -= l_1;
                                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                            }
                            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n_prepend + n_append;

                            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1 + l_0;
                        }
                        break;
                    }
                l += l_1; ///przywraca oryginalną wartość sprzed scalenia od dołu, skoro był blok przyległy od dołu, zabrakło do pełnej liczby od góry.
            }
            P p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n + n_prepend + n_append
            , p_0
            , l_0
            , n_prepend * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            );
            if( !p_1 )
                return p_1;
            *( P * )p = p_1;
            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
        }
    return (P)~0;
}
P
E_mem_Q_blk_I_append_( P p
, N n
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   N l = n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            Pc p_0 = 0;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   N l_1 = 0;
                p_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
                for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
                    if( p_0 + l_0 == free_p[ free_i ].p )
                    {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u )
                        {   l_1 = free_p[ free_i ].l;
                            if( l_1 > l )
                                l_1 = l;
                            else if( l_1 < l )
                                l_1 = E_simple_Z_n_I_align_down_to_v( l_1, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u );
                            l -= l_1;
                        }
                        break;
                    }
                if( !l )
                {   if( free_p[ free_i ].l != l_1 )
                        free_p[ free_i ].p += l_1;
                    else
                        free_p[ free_i ].p = 0;
                    free_p[ free_i ].l -= l_1;
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                    E_mem_Q_blk_P_fill_c( p_0 + ( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n - n ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                    return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_0;
                }
                for_n( free_j, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
                    if( free_p[ free_j ].p + free_p[ free_j ].l == p_0 )
                    {   if( free_p[ free_j ].l >= l )
                        {   if( free_p[ free_j ].l == l )
                                free_p[ free_j ].p = 0;
                            free_p[ free_j ].l -= l;
                            if( l_1 )
                            {   if( free_p[ free_i ].l != l_1 )
                                    free_p[ free_i ].p += l_1;
                                else
                                    free_p[ free_i ].p = 0;
                                free_p[ free_i ].l -= l_1;
                            }
                            Pc p_1 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p - l;
                            E_mem_Q_blk_I_copy( p_1, p_0, l_0 );
                            *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p = p_1;
                            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                            E_mem_Q_blk_P_fill_c( p_1 + l_0, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_0;
                        }
                        break;
                    }
                l += l_1; ///przywraca oryginalną wartość sprzed scalenia od dołu, skoro był blok przyległy od dołu, a zabrakło do pełnej liczby od góry.
            }
            P p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n + n
            , p_0
            , l_0
            , 0
            );
            if( !p_1 )
                return p_1;
            *( P * )p = p_1;
            E_mem_Q_blk_P_fill_c( (Pc)p_1 + ( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n - n ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            return (Pc)p_1 + l_0;
        }
    return (P)~0;
}
P
E_mem_Q_blk_I_prepend_( P p
, N n
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   N l = n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            Pc p_0 = 0;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   N l_1 = 0;
                p_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
                for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
                    if( free_p[ free_i ].p + free_p[ free_i ].l == p_0 )
                    {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u )
                        {   l_1 = free_p[ free_i ].l;
                            if( l_1 > l )
                                l_1 = l;
                            else if( l_1 < l )
                                l_1 = E_simple_Z_n_I_align_down_to_v( l_1, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u );
                            l -= l_1;
                        }
                        break;
                    }
                if( !l )
                {   if( free_p[ free_i ].l == l_1 )
                        free_p[ free_i ].p = 0;
                    free_p[ free_i ].l -= l_1;
                    *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                    E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                    return p_0;
                }
                for_n( free_j, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
                    if( p_0 + l_0 == free_p[ free_j ].p )
                    {   if( free_p[ free_j ].l >= l )
                        {   if( free_p[ free_j ].l != l )
                                free_p[ free_j ].p += l;
                            else
                                free_p[ free_j ].p = 0;
                            free_p[ free_j ].l -= l;
                            if( l_1 )
                            {   if( free_p[ free_i ].l == l_1 )
                                    free_p[ free_i ].p = 0;
                                free_p[ free_i ].l -= l_1;
                            }
                            E_mem_Q_blk_I_copy_rev( p_0 + l, p_0, l_0 );
                            if( l_1 )
                                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                            E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                            return p_0 + l;
                        }
                        break;
                    }
                l += l_1; ///przywraca oryginalną wartość sprzed scalenia od dołu, skoro był blok przyległy od dołu, a zabrakło do pełnej liczby od góry.
            }
            P p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n + n
            , p_0
            , l_0
            , l
            );
            if( !p_1 )
                return p_1;
            E_mem_Q_blk_P_fill_c( p_1, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            *( P * )p = p_1;
            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l;
        }
    return (P)~0;
}
P
E_mem_Q_blk_I_insert_( P p
, N i
, N n
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   Pc p_0 = 0;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
            {   N l = n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                N l_1 = 0;
                p_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
                struct E_mem_Q_blk_Z_free *free_p = (P)E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].p;
                for_n( free_i, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od dołu.
                    if( free_p[ free_i ].p + free_p[ free_i ].l == p_0 )
                    {   if( free_p[ free_i ].l >= E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u )
                        {   l_1 = free_p[ free_i ].l;
                            if( l_1 > l )
                                l_1 = l;
                            else if( l_1 < l )
                                l_1 = E_simple_Z_n_I_align_down_to_v( l_1, E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u );
                            l -= l_1;
                        }
                        break;
                    }
                if( !l )
                {   if( free_p[ free_i ].l == l_1 )
                        free_p[ free_i ].p = 0;
                    free_p[ free_i ].l -= l_1;
                    *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                    E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                    E_mem_Q_blk_I_copy( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p
                    , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1
                    , i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                    );
                    E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, l_1, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                    return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                }
                for_n( free_j, E_base_S->E_mem_Q_blk_S_allocated[ E_mem_Q_blk_S_allocated_S_free_id ].n ) ///szukanie wolnego bloku przyległego od góry.
                    if( p_0 + l_0 == free_p[ free_j ].p )
                    {   if( free_p[ free_j ].l >= l )
                        {   if( free_p[ free_j ].l != l )
                                free_p[ free_j ].p += l;
                            else
                                free_p[ free_j ].p = 0;
                            free_p[ free_j ].l -= l;
                            if( l_1 )
                            {   if( free_p[ free_i ].l == l_1 )
                                    free_p[ free_i ].p = 0;
                                free_p[ free_i ].l -= l_1;
                                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p -= l_1;
                            }
                            E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n += n;
                            E_mem_Q_blk_I_copy( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p
                            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1
                            , i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                            );
                            E_mem_Q_blk_I_copy_rev( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1 + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u + l
                            ,  E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + l_1 + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                            , l_0 - i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                            );
                            E_mem_Q_blk_P_fill_c( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, l_1, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
                            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                        }
                        break;
                    }
                l += l_1; ///przywraca oryginalną wartość sprzed scalenia od dołu, skoro był blok przyległy od dołu, zabrakło do pełnej liczby od góry.
            }
            P p_1 = E_mem_Q_blk_Q_table_M_from_free_or_map_0( allocated_i
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
            , E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n + n
            , p_0
            , l_0
            , 0
            );
            if( !p_1 )
                return p_1;
            //TODO zrobić w “E_mem_Q_blk_Q_table_M_from_free_or_map” parametr przesuniecia dla ‘split’ i kopiowania tam odrazu?
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n )
                E_mem_Q_blk_I_copy_rev( (Pc)p_1 + ( i + n ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                , (Pc)p_1 + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                , l_0 - i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u
                ); ///“E_flow_Q_task_I_touch_stack” było wykonane w “E_mem_Q_blk_Q_table_M_from_free_or_map”.
            E_mem_Q_blk_P_fill_c( (Pc)p_1 + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u, 0xa5 ); ///TODO procedura usuwająca zerowanie nowej pamięci na czas usuwania zmiennych globalnych i testów.
            *( P * )p = p_1;
            return (Pc)p_1 + i * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
        }
    return (P)~0;
}
P
E_mem_Q_blk_I_rem_( P p
, N i
, N n
){  if( !*( P * )p )
        return (P)~0;
    for_n( allocated_i, E_base_S->E_mem_Q_blk_S_allocated[ E_base_S->E_mem_Q_blk_S_table_allocated_id ].n )
        if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p == *( P * )p )
        {   N l = n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            N l_0 = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
            if( E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n == n ) ///usuwany cały blok.
            {   E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n = 0;
                P p_ = *( P * )p;
                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p = E_mem_Q_blk_R_new_0();
                struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_
                , p_
                , l
                ))
                    return 0;
            }else if( i == E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n - n ) ///usuwane na końcu bloku.
            {   E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n -= n;
                struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_
                , *( Pc * )p + l_0 - l
                , l
                ))
                    return 0;
            }else if( !i ) ///usuwane na początku bloku.
            {   E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n -= n;
                P p_ = *( P * )p;
                *( P * )p = E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p += l;
                struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_
                , p_
                , l
                ))
                    return 0;
            }else ///usuwane w środku bloku.
            {   Pc p_0 = *( Pc * )p + ( i + n ) * E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].u;
                E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].n -= n;
                E_mem_Q_blk_I_copy( p_0 - l
                , p_0
                , *( Pc * )p + l_0 - p_0
                );
                struct E_mem_Q_blk_Z_free free_p_;
                if( !~E_mem_Q_blk_Q_sys_table_mf_P_put( E_mem_Q_blk_S_allocated_S_free_id, (Pc)&free_p_.p - (Pc)&free_p_, (Pc)&free_p_.l - (Pc)&free_p_
                , *( Pc * )p + l_0 - l
                , l
                ))
                    return 0;
            }
            return E_base_S->E_mem_Q_blk_S_allocated[ allocated_i ].p;
        }
    return (P)~0;
}
//------------------------------------------------------------------------------
///resize useing a boundary without memory move if possible.
///gdy wynik jest niezerowy, to:
///•jeżeli “*n_appended”, to w wyniku jest adres nowego bloku przyległego od góry.
///•jeżeli “!*n_appended”, 〃 adres podanego bloku (przed którym dołączono blok przyległy od dołu).
///te wartości nie są używane i mogą zostać zmienione.
P
E_mem_Q_blk_I_add( P p
, N n
, N *n_prepended
, N *n_appended
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_add_( p, n, n_prepended, n_appended );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p_ )
        V( "E_mem_Q_blk_I_add" );
    return p_;
}
///resize useing boundaries without memory move if possible.
//NDFN funkcja nie dokończona.
P
E_mem_Q_blk_I_prepend_append( P p
, N n_prepend
, N n_append
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_prepend_append_( p, n_prepend, n_append );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p_ )
        V( "E_mem_Q_blk_I_prepend_append" );
    return p_;
}
///resize useing high boundary without memory move if possible.
///w wyniku podaje adres dołączonego bloku.
P
E_mem_Q_blk_I_append( P p
, N n
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_append_( p, n );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p_ )
        V( "E_mem_Q_blk_I_append" );
    return p_;
}
///resize useing low boundary without memory move if possible.
///w wyniku podaje adres danych pierwotnego bloku.
P
E_mem_Q_blk_I_prepend( P p
, N n
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_prepend_( p, n );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p_ )
        V( "E_mem_Q_blk_I_prepend" );
    return p_;
}
///insert without memory move if possible.
///w wyniku podaje adres wstawionego bloku.
//NDFN funkcja nie sprawdzona.
P
E_mem_Q_blk_I_insert( P p
, N i
, N n
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_insert_( p, i, n );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p_ )
        V( "E_mem_Q_blk_I_insert" );
    return p_;
}
///remove without memory move.
///w wyniku podaje nowy adres bloku (jak w “*( P * )p”).
P
E_mem_Q_blk_I_rem( P p
, N i
, N n
){  _single_thread_begin;
    P p_ = E_mem_Q_blk_I_rem_( p, i, n );
    E_mem_Q_blk_I_assert_on_return( __LINE__ );
    _single_thread_end;
    if( !~(N)p )
        V( "E_mem_Q_blk_I_rem" );
    return p_;
}

