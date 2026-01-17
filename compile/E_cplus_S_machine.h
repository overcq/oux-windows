/******************************************************************************/
// Włącza wypisywanie ‹raportów linii› umieszczonych instrukcjami “G”[…] lub z błędów w instrukcjach “V”[…]. Wyłączenie ‹raportów linii› nie wyłącza “strumienia” wypisywania dostępnego programowo.
#define C_line_report
// Przełącza na jeszcze mniejszy rozmiar identyfikatorów.
#define C_id_small
//==============================================================================
// Podejście ‘asemblerowe’ wysokiego poziomu.
// Nadzwyczajne typy danych:
typedef unsigned char       N8;
typedef signed char         S8;
typedef unsigned short      N16;
typedef short               S16;
typedef unsigned long       N32;
typedef long                S32;
typedef unsigned long long  N64;
typedef long long           S64;
typedef unsigned __int128   N128;
typedef __int128            S128;
//------------------------------------------------------------------------------
// Podstawowe typy danych:
typedef BOOL                B; // Musi być: “true == 1”.
typedef char                C; // Bajt lub znak bajtowy. Nieprzekraczalne reguły konwersji domyślnej w C z “char” do “int” wymuszają deklarację “char” bez podania “signed” lub “unsigned”, i następnie w pojedynczych przypadkach domyślnej zmiany z wielkości bajtowej – jawną konwersję typów, przez “unsigned char”. Sposób masowej realizacji takiej konwersji nie jest jeszcze ustalony.
typedef wchar_t             W;
typedef N64                 N; // Liczba naturalna do obliczeń arytmetycznych.
typedef S64                 S; // Ta sama liczba jak powyżej, ale ze znakiem. Ponieważ jest deklarowana jako maksymalna (“long”), to podlega zawsze domyślnej konwersji z nieistniejącym obcięciem wartości bitowej w obszarze maksymalnych wartości pojedynczych (nie tych scalanych w obliczeniach przez “carry flag”) liczb naturalnych maszyny.
    #ifdef C_id_small
typedef S16                 I; // ‹Identyfikator› tylko danych zarządzanych przez ‹menedżerów› ‟oux” (a nie przez zewnętrzne, dołączane podsystemy).
    #else
typedef S32                 I;
    #endif
typedef unsigned            In; // Służy do konwersji wartości “I” podczas porównywania.
typedef N32                 U; // Znak ‘unicode’.
typedef double              F; // Podstawowa liczba zmiennoprzecinkowa maszyny, ale do stosowania tylko w obliczeniach, w których wartość zbierająca niedokładność obliczeń jest urealniania w poszczególnych krokach programu.
typedef void                *P; // Tylko do deklaracji parametrów i konwersji pomiędzy typami wskaźnikowymi (nadawania przetwarzanej zawartości danych wskazywanych).
//==============================================================================
#define E_mem_Q_file_S_filename_separator   '\\'
#define E_mem_Q_file_S_filename_separator_s "\\"
#define E_mem_Q_file_S_filename_separator_w L"\\"
//==============================================================================
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
/******************************************************************************/
