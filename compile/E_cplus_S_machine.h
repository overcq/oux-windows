/*******************************************************************************
*   ___   publicplace
*  ¦OUX¦  "C+” into "C”
*  ¦/C+¦  compile
*   ---   C+
*         platform definitions
* ©overcq                on "Gentoo Linux 13.0” “x86_64”              2015-1-6 *
*******************************************************************************/
// W³¹cza wypisywanie ‹raportów linii› umieszczonych instrukcjami “G”[…] lub z b³êdów w instrukcjach “V”[…]. Wy³¹czenie ‹raportów linii› nie wy³¹cza “strumienia” wypisywania dostêpnego programowo.
#define C_line_report
// Prze³¹cza na jeszcze mniejszy rozmiar identyfikatorów.
#define C_id_small
// W³¹cza kontrolê poprawnoœci pamiêci 'alokatora' bloków.
#define E_mem_Q_blk_C_debug
//==============================================================================
// Podejœcie ‘asemblerowe’ wysokiego poziomu.
// Nadzwyczajne typy danych:
typedef unsigned char       N8;
typedef signed char         S8;
typedef unsigned short      N16;
typedef short               S16;
    #if defined( __i386__ )
typedef unsigned long       N32;
typedef long                S32;
typedef unsigned long long  N64;
typedef long long           S64;
    #elif defined( __x86_64__ )
typedef unsigned            N32;
typedef int                 S32;
typedef unsigned long       N64;
typedef long                S64;
    #endif
//------------------------------------------------------------------------------
// Podstawowe typy danych:
typedef BOOL                B; // Musi byæ: “true == 1”.
typedef char                C; // Bajt lub znak bajtowy. Nieprzekraczalne regu³y konwersji domyœlnej w "C” z “char” do “int” wymuszaj¹ deklaracjê “char” bez podania “signed” lub “unsigned”, i nastêpnie w pojedynczych przypadkach domyœlnej zmiany z wielkoœci bajtowej– jawn¹ konwersjê typów, przez “unsigned char”. Sposób masowej realizacji takiej konwersji nie jest jeszcze ustalony.
     #if defined( __i386__ )
typedef N32                 N;
typedef S32                 S;
typedef S16                 I;
    #elif defined( __x86_64__ )
typedef N64                 N; // Liczba naturalna do obliczeñ arytmetycznych.
typedef S64                 S; // Ta sama liczba jak powy¿ej, ale ze znakiem. Poniewa¿ jest deklarowana jako maksymalna (“long”), to podlega zawsze domyœlnej konwersji z nieistniej¹cym obciêciem wartoœci bitowej w obszarze maksymalnych wartoœci pojedynczych (nie tych scalanych w obliczeniach przez “carry flag”) liczb naturalnych maszyny.
        #ifdef C_id_small
typedef S16                 I; // ‹Identyfikator› tylko danych zarz¹dzanych przez ‹mened¿erów› "oux” (a nie przez zewnêtrzne, do³¹czane podsystemy).
        #else
typedef N32                 I;
        #endif
    #endif
typedef unsigned            In; // S³u¿y do konwersji wartoœci “I” podczas porównywania.
typedef N32                 U; // Znak ‘unicode’.
typedef double              F; // Podstawowa liczba zmiennoprzecinkowa maszyny, ale do stosowania tylko w obliczeniach, w których wartoœæ zbieraj¹ca niedok³adnoœæ obliczeñ jest urealniania w poszczególnych krokach programu.
typedef void                *P; // Tylko do deklaracji parametrów i konwersji pomiêdzy typami wskaŸnikowymi (nadawania przetwarzanej zawartoœci danych wskazywanych).
//==============================================================================
#define E_mem_Q_file_S_filename_separator   '\\'
#define E_mem_Q_file_S_filename_separator_s "\\"
/******************************************************************************/
