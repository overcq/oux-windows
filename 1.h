#define C_id_small
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
typedef _Bool               B; ///musi być: “true == 1”.
typedef char                C; ///bajt lub znak bajtowy. nieprzekraczalne reguły konwersji domyślnej w ‟C” z “char” do “int” wymuszają deklarację “char” bez podania “signed” lub “unsigned”, i następnie w pojedynczych przypadkach domyślnej zmiany z wielkości bajtowej– jawną konwersję typów, przez “unsigned char”. sposób masowej realizacji takiej konwersji nie jest jeszcze ustalony.
     #if defined( __i386__ )
typedef N32                 N;
typedef S32                 S;
typedef S16                 I;
    #elif defined( __x86_64__ )
typedef N64                 N; ///liczba naturalna do obliczeń arytmetycznych.
typedef S64                 S; ///ta sama liczba jak powyżej, ale ze znakiem. ponieważ jest deklarowana jako maksymalna (“long”), to podlega zawsze domyślnej konwersji z nieistniejącym obcięciem wartości bitowej w obszarze maksymalnych wartości pojedynczych (nie tych scalanych w obliczeniach przez “carry flag”) liczb naturalnych maszyny.
        #ifdef C_id_small
typedef S16                 I; ///‹identyfikator› tylko danych zarządzanych przez ‹menedżerów› ‟oux” (a nie przez zewnętrzne, dołączane podsystemy).
        #else
typedef N32                 I;
        #endif
    #endif
typedef unsigned            In; ///służy do konwersji wartości “I” podczas porównywania.
typedef N32                 U; ///znak ‘unicode’.
typedef double              F; ///podstawowa liczba zmiennoprzecinkowa maszyny, ale do stosowania tylko w obliczeniach, w których wartość zbierająca niedokładność obliczeń jest urealniania w poszczególnych krokach programu.
typedef void                *P; ///tylko do deklaracji parametrów i konwersji pomiędzy typami wskaźnikowymi (nadawania przetwarzanej zawartości danych wskazywanych).
#define E_mem_Q_file_S_filename_separator   '\\'
#define E_mem_Q_file_S_filename_separator_s "\\"

