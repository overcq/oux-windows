typedef C           *Pc; ///wskaźnik do obliczeń bajtowych i tekst techniczny języka ‟C”. zawsze będzie równoważny “char *” (przy uzgadnianiu ‘interfejsów’ procedur systemu operacyjnego).
typedef N           *Pn; ///wskaźnik do tablic liczb naturalnych.
typedef P           *Pp; ///wskaźnik do tablic adresów.
enum { false, true };
#define no                                  false
#define yes                                 true
///wyrażenie przypisania automatycznie nadające podanej wartości rozmiar zmiennej.
#define _v(a,v)                             (( (a) ^ (a) ) | (v) )
//------------------------------------------------------------------------------
#define _J_s(a)                             #a
#define J_s(a)                              _J_s(a)
#define _J_ab(a,b)                          a##b
#define J_ab(a,b)                           _J_ab(a,b)
#define J_a_b(a,b)                          J_ab(J_ab(a,_),b)
//------------------------------------------------------------------------------
#define J_n_10_max_digits(l)                ( l == 8 ? 20 : l == 4 ? 10 : l == 2 ? 5 : 3 )
#define J_swap(type,a,b)                    { type J_autogen(c) = a; a = b; b = J_autogen(c); }
#define J_min(a,b)                          ( (a) > (b) ? (b) : (a) )
#define J_max(a,b)                          ( (a) < (b) ? (b) : (a) )
#define J_abs(v)                            ( (S)(v) < 0 ? -(v) : (v) )
//------------------------------------------------------------------------------
#define J_autogen_S                         _autogen
#define J_autogen(a)                        J_a_b( a, J_autogen_S )
#define J_autogen_line(a)                   J_autogen( J_a_b( a, __LINE__ ))
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define O                                   while(yes)
#define for_n_(i_var,n)                     for( i_var = 0; i_var != (n); i_var++ )
#define for_n(i_var,n)                      N i_var; for_n_(i_var,(n))
#define for_n_rev_(i_var,n)                 i_var = (n); while( i_var-- )
#define for_n_rev(i_var,n)                  N for_n_rev_(i_var,(n))
#define for_i_(i_var,n)                     for_n_(i_var,(n))
#define for_i(i_var,n)                      I i_var; for_i_(i_var,(n))
#define for_i_rev_(i_var,n)                 for_n_rev_(i_var,(n))
#define for_i_rev(i_var,n)                  I for_i_rev_(i_var,(n))
//------------------------------------------------------------------------------
#define for_each_out_(out,id_var,p,q)       id_var = (out); while( ~( id_var = J_a_b(q,Z_iter_R_next)( (p), id_var, (out) )))
#define for_each_out(out,id_var,p,q)        I for_each_out_(out,id_var,(p),q)
#define for_each_(id_var,p,q)               for_each_out_(~0,id_var,(p),q)
#define for_each(id_var,p,q)                for_each_out(~0,id_var,(p),q)
//------------------------------------------------------------------------------
#define for_each_rev_out_(out,id_var,p,q)   id_var = (out); while( ~( id_var = J_a_b(q,Z_iter_R_prev)( (p), id_var, (out) )))
#define for_each_rev_out(out,id_var,p,q)    I for_each_rev_out_(out,id_var,(p),q)
#define for_each_rev_(id_var,p,q)           for_each_rev_out_(~0,id_var,(p),q)
#define for_each_rev(id_var,p,q)            for_each_rev_out(~0,id_var,(p),q)
//------------------------------------------------------------------------------
#define for_each_pop_out_(out,id_var,p,q) \
  for( \
  ; ~( id_var = J_a_b(q,Z_iter_R_prev)( (p), ~0, (out) )) \
  ; E_mem_Q_tab_I_rem( (p), id_var ) \
  )
#define for_each_pop_out(out,id_var,p,q)    I id_var; for_each_pop_out_((out),id_var,(p),q)
#define for_each_pop_(id_var,p,q)           for_each_pop_out_(~0,id_var,(p),q)
#define for_each_pop(id_var,p,q)            I id_var; for_each_pop_(id_var,(p),q)
//------------------------------------------------------------------------------
#define for_each_q_out(out,id_var,p,iter,q) \
  I id_var; \
  I J_autogen_line(id_var) = (out); \
  while(( id_var = J_a_b(q,Q_iter_R_next)( (p), (iter), ++J_autogen_line(id_var) )) != (out) )
#define for_each_q(id_var,p,iter,q)         for_each_q_out(~0,id_var,(p),(iter),q)
//==============================================================================
#define _F_uid_v(v)                         ( (v) << ( sizeof(int) * 8 / 2 ))
#define _F_uid(file_identifier)             J_autogen(J_a_b(F,file_identifier))
#define _K_proc(module,event)               J_a_b(J_a_b(E,module),J_a_b(K,event))
#define _XhYi_F_uid(file_identifier)        _F_uid_v( _F_uid(file_identifier) )
#define _XhYi_uid(module,report_impulser)   J_autogen(J_a_b(J_a_b(E,module),report_impulser))
#define _X_uid(module,report)               J_autogen(J_a_b(J_a_b(E,module),J_a_b(X,report)))
#define _X_var(module,report)               J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(X,report),S)))
#define _Y_uid(module,timer)                J_autogen(J_a_b(J_a_b(E,module),J_a_b(Y,timer)))
#define _Y_var(module,timer)                J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(Y,timer),S)))
#define _Yi_uid(module,impulser)            J_autogen(J_a_b(J_a_b(E,module),J_a_b(Yi,impulser)))
#define _Yi_var(module,impulser)            J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(Yi,impulser),S)))
#define _D_proc(module,task)                J_a_b(J_a_b(E,module),J_a_b(D,task))
#define D_id(module,task)                   J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(D,task),S)))
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///instrukcje “X_M”/“X_A”, “Yi_M”/“Yi_A” muszą występować w jednym z najwyższych bloków struktury programu ‹zadania›, w miejscu zapewniającym taką widoczność (do użycia ‹raportu› w tym ‹zadaniu›) jak deklaracja zmiennej lokalnej.
//#define Q_use(variable,object,...)    if( ~(( variable ) = J_a_b(object,D_M)( __VA_ARGS__ ))) {
//#define Q_use_0(variable,object,...)  if(( variable ) = J_a_b(object,D_M)( __VA_ARGS__ )) {
//#define Q_rel(object,...)         J_a_b(object,D_W)( __VA_ARGS__ ); }else { K( "Q_use" ); }
//------------------------------------------------------------------------------
#define _0(pointer_variable,l)              E_mem_Q_blk_P_fill_c( (pointer_variable), l, 0 )
#define _0_(pointer_variable)               _0( (pointer_variable), sizeof( *(pointer_variable) ))
//------------------------------------------------------------------------------
///utworzenie i wyrzucenie zmiennej w pamięci ‘alokowanej’ w “menedżerze pamięci”.
#define M(l)                                E_mem_Q_blk_M(l)
#define Mt(u,n)                             E_mem_Q_blk_M_tab( (u), (n) )
#define W(pointer_variable)                 E_mem_Q_blk_W( pointer_variable )
#define M_(pointer_variable)                pointer_variable = M( sizeof( *( pointer_variable )))
#define Mt_(pointer_variable,n)             pointer_variable = Mt( sizeof( *( pointer_variable )), (n) )
#define W_(pointer_variable)                ( W( pointer_variable ), pointer_variable = 0 )
#define W_tab_(pointer_variable)            ( E_mem_Q_tab_W( pointer_variable ), pointer_variable = 0 )
//------------------------------------------------------------------------------
///instrukcja blokowa definicji ‹zadania›.
#define D(module,task)                      void _D_proc(module,task)( P thread_proc_arg )
///instrukcja blokowa pętli głównej ‹zadania›.
#define I_D                                 O
//------------------------------------------------------------------------------
///utworzenie i wyrzucenie ‹zadania› lub ‹zadania› “wątkowanego” czekającego na ‹systemowy raport odblokowujący›.
#define D_M(module,task)                    CreateThread( 0, 0, _D_proc(module,task), 0, 0, &D_id(module,task) )
//------------------------------------------------------------------------------
///znacznik stanu —zwykle stanu pojedynczego obiektu sygnalizującego później kolekcję— umieszczony w strukturze tego ‹obiektu› dostępnej przez wyrażenie.
#define U_R(start_expr,state_name)          J_a_b(start_expr,J_autogen(J_a_b(U,state_name)))
///wzbudzenie stanu.
#define U_F(start_expr,state_name)          U_R(start_expr,state_name) = yes
///i liniowe obsłużenie tego stanu.
#define U_L(start_expr,state_name)          U_R(start_expr,state_name) = no
///albo blokowe.
#define U_E(start_expr,state_name)          ( U_R(start_expr,state_name) && ( U_L(start_expr,state_name), yes ))
//------------------------------------------------------------------------------
///instrukcja blokowa definicji ‹zdarzenia›.
#define K(module,event)                     B _K_proc(module,event)( I object )
///deklaracja emisji ‹zdarzenia›.
#define K_E(module,event,object)            if( !_K_proc(module,event)(object) ){} else
//------------------------------------------------------------------------------
///utworzenie i wyrzucenie ‹raportu›.
#define X_M_(module,report)                 _X_var(module,report) = CreateEvent( 0, FALSE, FALSE, J_s( _X_uid(module,report) ))
#define X_M(module,report)                  HANDLE X_M_(module,report)
#define X_W(module,report)                  CloseHandle( _X_var(module,report) )
///deklaracja emisji ‹raportu› przez ‹zadanie›.
#define X_A(module,report)                  X_M(module,report); _unused B U_L(module,report)
///sygnalizacja ‹zadania› obsługującego ‹raport› kolekcji.
#define X_F(module,report)                  SetEvent( _X_var(module,report) )
///i warunkowa– gdy jest stan pojedynczego obiektu.
#define X_U(module,report)                  if( !U_E(module,report) ){} else X_F(module,report)
///czekanie na ‹raport› kolekcji.
#define X_B(module,report)                  WaitForSingleObject( _X_var(module,report), INFINITE )
//------------------------------------------------------------------------------
///utworzenie i wyrzucenie ‹cyklera›.
#define Y_M(module,timer,period)            HANDLE _Y_var(module,timer) = CreateWaitableTimer( 0, FALSE, J_s( _Y_uid(module,timer) )); LARGE_INTEGER li; li.QuadPart = -period * 10000; SetWaitableTimer( _Y_var(module,timer), &li, period, 0, 0, FALSE )
#define Y_W(module,timer)                   CancelWaitableTimer( _Y_var(module,timer) )
///czekanie na pełny okres ‹cyklera›.
#define Y_B(module,timer)                   WaitForSingleObject( _Y_var(module,timer), INFINITE )
//==============================================================================
#define V(s) \
    {   MessageBox( 0, (s), "Failure exit", MB_OK ); \
        ExitProcess(1); \
    }
//==============================================================================
#define Gs(s,l) if( !E_base_S_log_file ){}else \
    {   N written; \
        if( !WriteFile( E_base_S_log_file, (s), (l), &written, 0 ) \
        || (l) != written \
        ) \
            V( "WriteFile" ); \
        if( !WriteFile( E_base_S_log_file, "\r\n", 2, &written, 0 ) \
        || 2 != written \
        ) \
            V( "WriteFile" ); \
    }
#define Gs_(s) Gs( (s), E_text_Z_s0_R_l(s) )
#define Gd(v) if( !E_base_S_log_file ){}else \
    {   N l = E_text_Z_n_N_s_G( (v), sizeof(v), 10 ); \
        HLOCAL s_ = LocalAlloc( LMEM_FIXED, l ); \
        Pc s = LocalLock( s_ ); \
        E_text_Z_n_N_s( s + l, (v), sizeof(v), 10 ); \
        Gs( s, l ); \
        LocalUnlock( s_ ); \
        LocalFree( s_ ); \
    }
#define Gh(v) if( !E_base_S_log_file ){}else \
    {   N l = E_text_Z_n_N_s_G( (v), sizeof(v), 16 ) + 2; \
        HLOCAL s_ = LocalAlloc( LMEM_FIXED, l ); \
        Pc s = LocalLock( s_ ); \
        E_text_Z_n_N_s( s + l, (v), sizeof(v), 16 ); \
        s[1] = 'x'; \
        s[0] = '0'; \
        Gs( s, l ); \
        LocalUnlock( s_ ); \
        LocalFree( s_ ); \
    }
#define Ge \
    {   N error = GetLastError(); \
        Pc s; \
        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM \
        , 0 \
        , error \
        , 0 \
        , &s, 0 \
        , 0 \
        ); \
        MessageBox( 0, s, "error", MB_OK ); \
        LocalFree(s); \
    }
//==============================================================================
#define _forced_statement                   __asm__ volatile ( "" )
    #ifndef _unreachable
#define _unreachable                        __builtin_unreachable()
    #endif
#define _unused                             __attribute__ ((__unused__))
#define E_mem_Q_file_S_eof                  ~1L
