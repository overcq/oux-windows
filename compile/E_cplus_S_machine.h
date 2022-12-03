/*******************************************************************************
*   ___   publicplace
*  �OUX�  "C+� into "C�
*  �/C+�  compile
*   ---   C+
*         platform definitions
* �overcq                on "Gentoo Linux 13.0� �x86_64�              2015-1-6 *
*******************************************************************************/
// W��cza wypisywanie �raport�w linii� umieszczonych instrukcjami �G�[�] lub z b��d�w w instrukcjach �V�[�]. Wy��czenie �raport�w linii� nie wy��cza �strumienia� wypisywania dost�pnego programowo.
#define C_line_report
// Prze��cza na jeszcze mniejszy rozmiar identyfikator�w.
#define C_id_small
// W��cza kontrol� poprawno�ci pami�ci 'alokatora' blok�w.
#define E_mem_Q_blk_C_debug
//==============================================================================
// Podej�cie �asemblerowe� wysokiego poziomu.
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
typedef BOOL                B; // Musi by�: �true == 1�.
typedef char                C; // Bajt lub znak bajtowy. Nieprzekraczalne regu�y konwersji domy�lnej w "C� z �char� do �int� wymuszaj� deklaracj� �char� bez podania �signed� lub �unsigned�, i nast�pnie w pojedynczych przypadkach domy�lnej zmiany z wielko�ci bajtowej� jawn� konwersj� typ�w, przez �unsigned char�. Spos�b masowej realizacji takiej konwersji nie jest jeszcze ustalony.
     #if defined( __i386__ )
typedef N32                 N;
typedef S32                 S;
typedef S16                 I;
    #elif defined( __x86_64__ )
typedef N64                 N; // Liczba naturalna do oblicze� arytmetycznych.
typedef S64                 S; // Ta sama liczba jak powy�ej, ale ze znakiem. Poniewa� jest deklarowana jako maksymalna (�long�), to podlega zawsze domy�lnej konwersji z nieistniej�cym obci�ciem warto�ci bitowej w obszarze maksymalnych warto�ci pojedynczych (nie tych scalanych w obliczeniach przez �carry flag�) liczb naturalnych maszyny.
        #ifdef C_id_small
typedef S16                 I; // �Identyfikator� tylko danych zarz�dzanych przez �mened�er�w� "oux� (a nie przez zewn�trzne, do��czane podsystemy).
        #else
typedef N32                 I;
        #endif
    #endif
typedef unsigned            In; // S�u�y do konwersji warto�ci �I� podczas por�wnywania.
typedef N32                 U; // Znak �unicode�.
typedef double              F; // Podstawowa liczba zmiennoprzecinkowa maszyny, ale do stosowania tylko w obliczeniach, w kt�rych warto�� zbieraj�ca niedok�adno�� oblicze� jest urealniania w poszczeg�lnych krokach programu.
typedef void                *P; // Tylko do deklaracji parametr�w i konwersji pomi�dzy typami wska�nikowymi (nadawania przetwarzanej zawarto�ci danych wskazywanych).
//==============================================================================
#define E_mem_Q_file_S_filename_separator   '\\'
#define E_mem_Q_file_S_filename_separator_s "\\"
/******************************************************************************/
