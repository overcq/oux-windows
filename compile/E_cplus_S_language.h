/*******************************************************************************
*   ___   publicplace
*  �OUX�  "C+� into "C�
*  �/C+�  compile
*   ---   C+
*         base definitions
* �overcq                on "Gentoo Linux 13.0� �x86_64�              2015-1-6 *
*******************************************************************************/
// �Statement� i wyra�enia rozszerzonej sk�adni, kt�re musz� znajdowa� si� w nawiasach klamrowych bloku nadrz�dnego: �for_�[�], �V�[�], linie �G�[�].
// Og�lne standardy �interfejs�w� �procedur�:
// ? dodatkowe wyniki �procedur� s� przypisywane zmiennym wska�nikowym, je�li podany adres zmiennej nie jest zerowy.
// ? �mened�er� mog�cy zmieni� adres przechowywany w zmiennej uchwytu obiektu otrzymuje jako pierwszy �argument� wska�nik do zmiennej uchwytu, kt�r� uaktualnia, je�li potrzeba. Takimi �mened�erami� s� tylko wydaj�cy adres struktury danych: ?�mem_blk� musi tak robi�, ale ma zarejestrowane wszystkie wydane adresy, ?�mem_tab� nie musi tak robi�, lecz dla oszcz�dno�ci nie rejestruje wydanych tablic, a zawsze mo�na to zmieni� w przysz�o�ci. Poza �mened�erami� pami�ci raczej nic wi�cej nie potrzebuje wydawa� jako uchwyt obiektu� adresu struktury danych opisu, lecz �identyfikator� obiektu.
//==============================================================================
typedef C           *Pc; // Wska�nik do oblicze� bajtowych i tekst techniczny j�zyka "C� lub �UTF-8�. zawsze b�dzie r�wnowa�ny �char *� (przy uzgadnianiu �interfejs�w� procedur systemu operacyjnego).
typedef N           *Pn; // Wska�nik do tablic liczb naturalnych.
typedef P           *Pp; // Wska�nik do tablic adres�w.
//==============================================================================
#define false                               FALSE
#define true                                TRUE
#define no                                  FALSE
#define yes                                 TRUE
// Wyra�enie przypisania automatycznie nadaj�ce podanej warto�ci rozmiar zmiennej. Naprawia konieczno�� jawnego deklarowania przyrostk�w dla typ�w sta�ych; bo domy�lnie �int�.
#define _v(a,v)                             (( (a) ^ (a) ) | (v) )
//------------------------------------------------------------------------------
#define _J_s(a)                             #a
#define J_s(a)                              _J_s(a)
#define _J_ab(a,b)                          a##b
#define J_ab(a,b)                           _J_ab(a,b)
#define J_a_b(a,b)                          J_ab(J_ab(a,_),b)
//------------------------------------------------------------------------------
#define J_n_10_max_digits(l)                ( l == 8 ? 20 : l == 4 ? 10 : l == 2 ? 5 : 3 )
#define J_swap(type,a,b)                    { type J_autogen(_) = a; a = b; b = J_autogen(_); }
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
  ; E_mem_Q_tab_I_remove( (p), id_var ) \
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
#define _Yi_uid(module,impulser)            J_autogen(J_a_b(J_a_b(E,module),J_a_b(Yi,impulser)))
#define _Yi_var(module,impulser)            J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(Yi,impulser),S)))
#define _D_proc(module,task)                J_a_b(J_a_b(E,module),J_a_b(D,task))
#define D_id(module,task)                   J_autogen(J_a_b(J_a_b(E,module),J_a_b(J_a_b(D,task),S)))
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define Q_use(variable,object,...)    if( ~(( variable ) = J_a_b(object,D_M)( __VA_ARGS__ ))) {
//#define Q_use_0(variable,object,...)  if(( variable ) = J_a_b(object,D_M)( __VA_ARGS__ )) {
//#define Q_rel(object,...)         J_a_b(object,D_W)( __VA_ARGS__ ); }else { K( "Q_use" ); }
//------------------------------------------------------------------------------
#define _0(pointer_variable,l)              E_mem_Q_blk_P_fill_c( (pointer_variable), l, 0 )
#define _0_(pointer_variable)               _0( (pointer_variable), sizeof( *(pointer_variable) ))
//------------------------------------------------------------------------------
// Utworzenie i wyrzucenie zmiennej w pami�ci �alokowanej� w �mened�erze pami�ci�.
#define M(l)                                E_mem_Q_blk_M(l)
#define Mt(u,n)                             E_mem_Q_blk_M_tab((u),(n))
#define W(pointer_variable)                 E_mem_Q_blk_W( pointer_variable )
#define M_(pointer_variable)                pointer_variable = M( sizeof( *( pointer_variable )))
#define Mt_(pointer_variable,n)             pointer_variable = Mt( sizeof( *( pointer_variable )), (n) )
#define W_(pointer_variable)                ( W( pointer_variable ), pointer_variable = 0 )
#define W_tab_(pointer_variable)            ( E_mem_Q_tab_W( pointer_variable ), pointer_variable = 0 )
//------------------------------------------------------------------------------
// Instrukcja blokowa definicji �zadania�.
#define D(module,task)                      _internal void _D_proc(module,task)( P thread_proc_arg )
// Instrukcja blokowa p�tli g��wnej �zadania�.
#define I_D                                 if( E_flow_Q_task_I_begin() ){} else O
//------------------------------------------------------------------------------
// Utworzenie i wyrzucenie �zadania� lub �zadania� �w�tkowanego� czekaj�cego na �systemowy raport odblokowuj�cy�.
//TODO Rozdzieli� dla �Dh�� na �zadania� takie jak �D� (bez �subid�) oraz takie jak obecnie �Dh� (�Dhi�).
    #ifdef C_line_report
#define D_M(module,task)                    if( ~E_flow_Q_task_M( &(D_id(module,task)), &_D_proc(module,task), 0, no, J_s( _D_proc(module,task) ))){} else
#define Dh_M(module,task,subid,arg)         if( ~E_flow_Q_task_M_thread( &(D_id(module,task)), (subid), &_D_proc(module,task), (arg), J_s( _D_proc(module,task) ))){} else
    #else
#define D_M(module,task)                    if( ~E_flow_Q_task_M( &(D_id(module,task)), &_D_proc(module,task), 0, no )){} else
#define Dh_M(module,task,subid,arg)         if( ~E_flow_Q_task_M_thread( &(D_id(module,task)), (subid), &_D_proc(module,task), (arg) )){} else
    #endif
#define Dh_W(module,task,subid)             E_flow_Q_task_W_thread( &(D_id(module,task)), (subid) )
#define D_W(module,task)                    E_flow_Q_task_W( &(D_id(module,task)) )
//------------------------------------------------------------------------------
// Znacznik stanu �zwykle stanu pojedynczego obiektu sygnalizuj�cego p�niej kolekcj� umieszczony w strukturze tego �obiektu� dost�pnej przez wyra�enie.
#define U_R(start_expr,state_name)          J_a_b(start_expr,J_autogen(J_a_b(U,state_name)))
// Wzbudzenie stanu.
#define U_F(start_expr,state_name)          U_R(start_expr,state_name) = yes
// I liniowe obs�u�enie tego stanu.
#define U_L(start_expr,state_name)          U_R(start_expr,state_name) = no
// Albo blokowe.
#define U_E(start_expr,state_name)          ( U_R(start_expr,state_name) && ( U_L(start_expr,state_name), yes ))
//------------------------------------------------------------------------------
// Instrukcja blokowa definicji �zdarzenia�.
#define K(module,event)                     B _K_proc(module,event)( I object )
// Deklaracja emisji �zdarzenia�.
#define K_E(module,event,object)            if( !_K_proc(module,event)(object) ){} else
//------------------------------------------------------------------------------
// Instrukcje �X_M�/�X_A�, �Yi_M�/�Yi_A� musz� wyst�powa� w jednym z najwy�szych blok�w struktury programu �zadania�, w miejscu zapewniaj�cym tak� widoczno�� (do u�ycia �raportu� w tym �zadaniu�) jak deklaracja zmiennej lokalnej.
// Utworzenie i wyrzucenie �raportu�.
#define X_M_(module,report)                 _X_var(module,report) = E_flow_Q_report_M( _X_uid(module,report) )
#define X_M(module,report)                  I X_M_(module,report)
#define X_W(module,report)                  E_flow_Q_report_W( _X_var(module,report) )
// Deklaracja emisji �raportu� przez �zadanie�.
#define X_A(module,report)                  X_M(module,report); _unused B U_L(module,report)
// Sygnalizacja �zadania� obs�uguj�cego �raport� kolekcji.
#define X_F(module,report)                  E_flow_Q_report_I_signal( _X_var(module,report) )
// I warunkowa� gdy jest stan pojedynczego obiektu.
#define X_U(module,report)                  if( !U_E(module,report) ){} else X_F(module,report)
// Czekanie na �raport� kolekcji.
#define X_B(module,report,lost_count)       if( !E_flow_Q_report_I_wait( _X_var(module,report), (lost_count) )){} else
// Czyszczenie licznika raport�w.
#define X_L(module,report)                  E_flow_Q_report_I_clear( _X_var(module,report) )
//------------------------------------------------------------------------------
    #ifdef E_flow_C_thread_system_unblock_reports
// Deklaracja �procedury� generuj�cej �systemowy raport odblokowuj�cy� dla �zadania�; odblokowuj�cej to �zadanie�.
#define Xh_A( thread_unblock_proc_ ) \
  HANDLE J_autogen( thread_flow_mutex ); \
  volatile B *J_autogen( thread_switch_back ); \
  E_flow_Q_thread_system_unblock_report_M(( thread_unblock_proc_ ), &J_autogen( thread_flow_mutex ), &J_autogen( thread_switch_back ))
// Tu� przed wywo�aniem procedury blokuj�cej w oczekiwaniu na �systemowy raport odblokowuj�cy�.
#define Xh_B_() \
  *J_autogen( thread_switch_back ) = yes; \
  E_flow_Q_thread_system_unblock_report_I_before_block( J_autogen( thread_flow_mutex ))
// Czekanie na �systemowy raport odblokowuj�cy�; tu� po wywo�aniu procedury blokuj�cej.
#define Xh_B() \
  *J_autogen( thread_switch_back ) = no; \
  if( !E_flow_Q_thread_system_unblock_report_I_after_block( J_autogen( thread_flow_mutex ))){} else
    #else
#define Xh_A( thread_unblock_proc_ )
    #endif
//------------------------------------------------------------------------------
    #ifdef E_flow_C_itimer_system_unblock_report
// Utworzenie i wyrzucenie �systemowego raportu odblokowuj�cego� typu �itimer�, wyst�puj�cego najwy�ej jeden raz.
#define Xh1_M(sigsuspend,setitimer)         E_flow_Q_itimer_system_unblock_report_M( sigsuspend, setitimer )
#define Xh1_W()                             E_flow_Q_itimer_system_unblock_report_W()
// Czekanie na �systemowy raport odblokowuj�cy� typu �itimer�.
#define Xh1_B()                             if( !E_flow_Q_itimer_system_unblock_report_I_wait() ){} else
    #endif
//------------------------------------------------------------------------------
// Utworzenie i wyrzucenie �cyklera�.
#define Y_M(period)                         E_flow_Q_timer_M(period)
#define Y_W(timer)                          E_flow_Q_timer_W(timer)
// Czekanie na pe�ny okres �cyklera�.
#define Y_B(timer,lost_count)               if( !E_flow_Q_timer_I_wait( (timer), (lost_count) )){} else
//------------------------------------------------------------------------------
// Utworzenie i wyrzucenie �impulsatora�.
#define Yi_M(module,impulser)               I _Yi_var(module,impulser) = E_flow_Q_impulser_M( _Yi_uid(module,impulser) )
#define Yi_W(module,impulser)               E_flow_Q_timer_W( _Yi_var(module,impulser) )
// Deklaracja aktywacji �impulsatora� przez �zadanie�.
#define Yi_A(module,impulser)               I _Yi_var(module,impulser) = E_flow_Q_impulser_M_srv( _Yi_uid(module,impulser) )
// Aktywacja �impulsatora�.
#define Yi_F(module,impulser,time)          E_flow_Q_impulser_I_activate( _Yi_var(module,impulser), (time) )
// Dezaktywacja �impulsatora�.
#define Yi_L(module,impulser)               E_flow_Q_impulser_I_deactivate( _Yi_var(module,impulser) )
// Czekanie na wzbudzenie przez �impulsator�.
#define Yi_B(module,impulser)               if( !E_flow_Q_impulser_I_wait( _Yi_var(module,impulser) )){} else
//------------------------------------------------------------------------------
// Czekanie na wznowienie w nast�pnym obiegu czasu.
#define I_B()                               if( !E_flow_Q_task_I_schedule() ){} else
//------------------------------------------------------------------------------
// Wyj�cie z �zadania� po procedurze zawieraj�cej instrukcj� prze��czenia.
#define I_V()                               if( !E_flow_Q_task_R_exit() ){} else
//==============================================================================
#define _G_var      J_autogen_line(G)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #ifdef C_line_report
//TODO W przysz�o�ci zast�pi� niegwarantowane wypisywanie synchroniczne na wypisywanie do specjalnego wyj�cia danych, zawsze dost�pnego, a niekoniecznie o du�ej pojemno�ci.
// �Raport linii� nie wymagaj�cy integralno�ci programu. w miejscach, gdzie nie mo�na wykonywa� funkcji wypisywania integralnej tego programu. poniewa� nie mo�na wywo�ywa� �adnej funkcji obiektowo�ci zarz�dzanej albo takiej funkcji mo�e u�y� funkcja ��dania wypisania integralna tego programu.
#define G_()        _unused B _G_var = yes; E_flow_Z_line_report_Z_line_I_sync( &__FILE__[0], __LINE__, 0 )
// �Raport linii�.
#define G()         _unused B _G_var = no; E_flow_Z_line_report_Z_line_I( &__FILE__[0], __LINE__, 0 )
// �Niepowodzenie zaka�czaj�ce� (ewentualn� instrukcj� �V� umieszczon� na ko�cu linii). zaistnia�e przez wej�cie na t� lini� tekstu programu.
#define GV_(s)      _unused B _G_var = yes; E_flow_Z_line_report_Z_line_I_sync( &__FILE__[0], __LINE__, J_s(s) )
// �Niepowodzenie ostrzegaj�ce� (bez instrukcji �V�). ?
#define GV(s)       _unused B _G_var = no; E_flow_Z_line_report_Z_line_I( &__FILE__[0], __LINE__, J_s(s) )
//------------------------------------------------------------------------------
// Wypisywanie zmiennych programu; po �G�/�GV�/�G_�/�GV_� w linii.
#define Gc(c)       if( _G_var ) E_flow_Z_line_report_Z_text_c_I_sync( J_s(c), c ); else E_flow_Z_line_report_Z_text_c_I( J_s(c), c )
#define Gs(s,s_end) if( (s_end) - (s) ) Gs_l( s, s, (s_end) - (s) ); else Gs_l( s, "", 0 )
#define Gs_(s,s_end) if( (s_end) - (s) ) Gs_l_( s, (s_end) - (s) ); else Gs_l_( "", 0 )
#define Gs0(s)      Gs_l( s, s, 0 )
#define Gs0_(s)     Gs_l_( s, 0 )
#define Gsl(s,l)    if(l) Gs_l( s, s, (l) ); else Gs_l( s, "", 0 )
#define Gsl_(s,l)   if(l) Gs_l_( s, (l) ); else Gs_l_( "", 0 )
#define Gs_l(t,s,l) if( _G_var ) E_flow_Z_line_report_Z_text_s_I_sync( J_s(t), (s), (l) ); else E_flow_Z_line_report_Z_text_s_I( J_s(t), (s), (l) )
#define Gs_l_(s,l)  if( _G_var ) E_flow_Z_line_report_Z_s_I_sync( (s), (l) ); else E_flow_Z_line_report_Z_s_I( (s), (l) )
#define Gd(n)       if( _G_var ) E_flow_Z_line_report_Z_text_n_I_sync( J_s(n), (N)(n), sizeof(n), 10 ); else E_flow_Z_line_report_Z_text_n_I( J_s(n), (N)(n), sizeof(n), 10 )
#define Gh(n)       if( _G_var ) E_flow_Z_line_report_Z_text_n_I_sync( J_s(n), (N)(n), sizeof(n), 16 ); else E_flow_Z_line_report_Z_text_n_I( J_s(n), (N)(n), sizeof(n), 16 )
#define Gq(q)
    #else
#define G()
#define G_()
#define GV(s)
#define GV_(s)
#define Gc(c)
#define Gs(s,s_end)
#define Gs_(s,s_end)
#define Gs0(s)
#define Gs0_(s)
#define Gs_l(s)
#define Gs_l_(s)
#define Gd(n)
#define Gh(n)
#define Gq(q)
    #endif
//------------------------------------------------------------------------------
#define _V()        ExitProcess(1)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//NDFN Zintegrowa� koncepcje �V� razem z �K�. I wtedy zostanie do��czona koncepcja proces�w �restartowalnych� ze stanu zachowanego w momencie wyst�pienia takiego b��du (a nie zachowywanego ci�gle).
//NKN �V� s� drogami wyj�cia po nieudanym �K� wewn�trznym funkcji wo�anej.
// �Nierealizacje zaka�czaj�ce� (�V_�) powinny by� stosowane dla procedur systemu operacyjnego, kt�re musz� si� uda� dla kontynuacji jakiegokolwiek przep�ywu wykonania, oraz dla zwalniania oczywistych zasob�w.
#define V_(statement)                      V(statement) _V()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//NKN �Nierealizacje blokowe� (�V�), kt�re wyst�pi�y w �zadaniu� innym ni� �main�, musz� by� obs�ugiwane przez zablokowanie si� �zadania� na linii wyj�cia z �I_D� i sygnalizacj� b��du (p�-�zdarzenie�?), by �zadanie�, kt�re je uruchomi�o (co najmniej �main� usuwaj�ce po�rednio wszystkie �zadania� i ko�cz�ce program), mog�o normalnie je usun��. Wtedy nie b�dzie ju� nigdy krytycznego (przez zgubienie danych i byt�w sterowanych) przerywania programu z powodu b��du procedury systemu operacyjnego opr�cz sytuacji, gdy lepiej b�dzie natychmiast przerwa� program ni� jeszcze co� rozwali� z jego uszkodzonego wewn�trznego stanu.
    #ifdef C_line_report
#define V(statement) \
  if( (statement) || ( E_flow_Z_line_report_Z_line_I_error( &__FILE__[0], __LINE__ ), no )) \
  { \
  }else
    #else
#define V(statement) \
  if(statement) \
  { \
  }else
    #endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define J_assert(expr)                      if(expr){}else{ GV_(ASSERT); _V(); }
//==============================================================================
#define _forced_statement                   __asm__ volatile ( "" )
#define _internal                           __attribute__ ((__visibility__( "internal" )))
#define _packed                             __attribute__ ((__packed__))
#define _unreachable                        __builtin_unreachable()
#define _unused                             __attribute__ ((__unused__))
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef BUILDING_DLL
#define DLLIMPORT                           __declspec(dllexport)
#else
#define DLLIMPORT                           __declspec(dllimport)
#endif
//==============================================================================
#define E_mem_Q_file_S_eof                  ( ~1L )
/******************************************************************************/
