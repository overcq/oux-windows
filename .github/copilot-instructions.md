# Copilot / AI Agent Instructions for OUX/C+ (Windows)

Repozytorium zawiera projekt **OUX/C+ v3** — system kompilacji `.cx` → `.c` z runtime modułów (DLL). Projekt rozwija się równolegle do [oryginalnego OUX/C+](https://github.com/overcq/oux) na Linux. Instrukcje są krótkie i praktyczne.

## Architektura projektu

```
make-oux/           = Kompilator .cx → .c (C PCRE2)
compile/            = Nagłówki runtime (typy, makra)
module/base/        = Moduł podstawowy (DLL) - alokacja, timer, flow, I/O
module/window/      = Moduł okien (DLL) - GDI32
program/ui/         = Program testowy UI
program/test/       = Testy
suspended/          = Kod wznowiony (net, fork, page, syntax...)
```

## Typy danych (E_cplus_S_machine.h)

```c
N       = unsigned long long (64-bit)     // Liczba naturalna (arytmetyka)
S       = long long (64-bit)              // Liczba ze znakiem
I       = signed short lub int (ID)       // Identyfikator - manager tylko
B       = BOOL                            // Wartość logiczna (true/false)
C       = char (bajt)                     // Bajt/tekst UTF-8
W       = wchar_t                         // Szeroki znak (Windows API)
F       = double                          // Zmiennoprzecinkowa
P       = void*                           // Wskaźnik (konwersje między typami)
N8, N16, N32, N64, N128                   // Typy o stałej szerokości
```

## System makr i idiomy (E_cplus_S_language.h)

### Alokacja pamięci
- **M(l)** — alokuj l bajtów; zwraca wskaźnik lub ~0 (błąd)
- **Mt(u, n)** — alokuj tablicę n elementów rozmiaru u
- **W(ptr)** — dealokuj ptr; zawsze używaj zamiast free()
- **_0_(ptr)** — wyzeruj strukturę; _0(ptr, len) — wyzeruj len bajtów

### Zadania i raporty (flow control)

```c
D(module, task) { ... }              // Definicja zadania (makro blokowe)
D_M(module, task, stack_size)         // Utwórz zadanie; zwraca I (ID)
D_W(module, task)                     // Zakończ zadanie
X_M(module, report)                   // Utwórz raport; zwraca I
X_W(module, report)                   // Dealokuj raport
X_F(module, report)                   // Sygnalizuj raport (obudź oczekujących)
X_B(module, report, lost_count)       // Czekaj na raport
```

### Cyklery i impulsatory (timery)
- **Y_M(period)** — utwórz cykler (timer); period w ms
- **Y_W(timer)** — dealokuj timer
- **Y_B(timer, lost_count)** — czekaj na pełny okres
- **Yi_M(module, impulser)** — utwórz impulsator
- **Yi_F(module, impulser, time)** — aktywuj impulsator na time ms
- **Yi_L(module, impulser)** — dezaktywuj

### Stany bitowe
- **U_R(expr, state_name)** — odczytaj stan (zwraca bit)
- **U_F(expr, state_name)** — ustaw stan
- **U_L(expr, state_name)** — wyzeruj stan
- **U_E(expr, state_name)** — warunkowa obsługa (if-like)

### Harmonogram i przełączenie
- **I_B()** — czekaj do następnego obiegu (schedule)
- **I_V()** — wyjście z zadania z przełączeniem

### Zdarzenia
```c
K(module, event) { ... }              // Definicja handlera zdarzenia
K_E(module, event, object)             // Emisja zdarzenia (if-like)
```

## Konwencje nazewnicze

- **E_module_...** — symbole publiczne modułu (nagłówki lub wygenerowane)
- **E_module_Q_...** — funkcje/dane "private" (internal)
- **_export** — (makro puste) marker eksportu w .cx
- **_internal** — marker prywatny/statyczny
- **_import** — (rzadko) marker importu

Wszystkie zadania, raporty, timery i impulsatory mają **globalnie unikalny ID** generowany na podstawie nazwy (`_F_uid(module_task)`).

## Build & workflow

### Setup PCRE2 (Windows, wymagane raz)
```bash
cd D:\moje\zasoby\programy\pcre2  # (lub inna ścieżka)
cmake -G 'MinGW Makefiles' -B build .
cmake --build build
# Tworzy: pcre2-8.lib (static)
```
Ścieżka do PCRE2 jest zakodowana w `make-oux/Makefile`.

### Kompilacja make-oux
```bash
cd make-oux
mingw32-make              # lub: make (jeśli MSYS2)
# Tworzy: make-oux.exe
```

### Generowanie .c z .cx
```bash
cd make-oux
make-oux.exe              # Przetwarza WSZYSTKIE .cx w module/* i program/*
```
Pliki wygenerowane: `E_cplus_S_*.c` (jeden per moduł/program)

### Kompilacja modułów DLL
```bash
cd module/base
mingw32-make              # Tworzy: liboux-base.dll + liboux-base.dll.a
cd ../window
mingw32-make              # Tworzy: liboux-window.dll + liboux-window.dll.a
```

Flagi kompilatora w każdym module (z Makefile):
```makefile
-include E_cplus_S_to_libs.h  # Konieczne: definiuje uid, enum dla raportów
-fwrapv                       # Arytmetyka na przepełnieniach
-DE_cplus_C_building_S_base   # Marker budowania konkretnego modułu
-I../../compile              # Nagłówki runtime
-I..                          # Inne moduły (base.h, window.h)
```

### Kompilacja programów
```bash
cd program/ui
mingw32-make              # Tworzy: ui.exe
# Linkuje: liboux-base.dll liboux-window.dll
```

Program musi linkować moduły w kolejności zależności (base przed window).

### Uruchomienie
```bash
program\ui\ui.exe         # W Command Prompt lub PowerShell
```

## Edycja kodu i dodawanie cech

### Główna reguła
**Zawsze edytuj `.cx`, nigdy bezpośrednio `.c`**. Pliki `.c` są generowane i nadpiszą się.

### Workflow dodawania funkcjonalności
1. Edytuj `.cx` (np. `module/base/M.cx`)
2. Uruchom `make-oux.exe` z katalogu `make-oux/`
3. Zbuduj moduł: `mingw32-make` w katalogu modułu
4. Linkuj programy zależne (automatycznie przez Makefile)

### Eksport z modułu
- Deklaruj w `.cx` z `_export` (marker)
- Wygenerowane: `E_cplus_S_1_module__submodule.h` (forward decl) i `E_cplus_S_2_*.h` (full def)
- Importuj w innych modułach: `-I../module_name` w Makefile
- Dołącz: `-include E_cplus_S_to_libs.h` (definiuje uid dla raportów)

### Typ zwrotu funkcji/zadania
- Zwróć `~0` (czyli wszystkie bity ustawione) dla błędu
- Zwróć `0` lub wartość >= 0 dla sukcesu
- Makra `M()`, `D_M()` itp. testują z `if(~(...))` — to inweruje, więc `~0` = fałsz = błąd

### Obsługa Unicode / Windows API
- `wchar_t *` dla ścieżek, nazw (L"...")
- `char *` (UTF-8) dla logiki aplikacji
- `E_main_Q_w0_I_to_s0()` (jeśli istnieje) lub ręczna konwersja WideCharToMultiByte
- Moduł window używa GDI32 — patrz `module/window/...` dla GDI wzorców

## Ważne pliki do edycji

### compile/E_cplus_S_language.h
- Makra D, X, Y, M, W, U, K, I itp.
- Zmiana tutaj wpływa na WSZYSTKIE moduły i programy
- Edytuj ostrożnie, testuj kompilację całego projektu

### compile/E_cplus_S_machine.h
- Definicje typów (N, S, I, B, C, W, F)
- Separatory ścieżek (`E_mem_Q_file_S_filename_separator`)
- GET_X_LPARAM, GET_Y_LPARAM itp.

### compile/E_cplus_S_base.h, E_cplus_S_simple.h
- Proste typy i helpery bazowe
- Stosunkowo stabilne

### module/E_cplus_S_to_libs.h
- Enum uid dla raportów/taskow wszystkich modułów
- Musi być spójny z wygenerowanymi nagłówkami
- Regeneruj po dodaniu nowego raportu

### make-oux/main.c
- Rdzeń kodu generatora .cx → .c (PCRE2)
- 2300+ linii C z regexami do parsowania makr blokowych
- Szukaj: `E_main_I_cx_to_c` (główna funkcja), `E_main_Q_pcre2_code_M` (regex database)
- **Zmieniaj ostrożnie i testuj na małych .cx plikach**

## Testowanie i debugowanie

### Brak zautomatyzowanego test frameworka
- Aby przetestować zmianę codegenu: utwórz mały `.cx` trigger, uruchom `make-oux.exe`, skompiluj wynik, przetestuj ręcznie
- Np. dla nowego makra: `program/test/test_newfeature.cx` → generuj → kompiluj → uruchom

### Debugowanie na Windows
- Historycznie: Orwell Dev-C++ (32-bit), starsze clang
- Współcześnie: VS Code + MinGW, VS Community + clang-cl
- Pewne brakuje symboli debugowania w DLL — kompiluj z `-g` jeśli potrzebujesz

### Weryfikacja wygenerowanego kodu
```bash
# Po make-oux.exe:
cat module/base/E_cplus_S_M.c         # Sprawdzić, czy makra się rozwinęły
cat program/ui/E_cplus_S_main.c       # Sprawdzić główny plik programu
```

## Specjalne notatki

1. **Identyfikatory uint** (`I`) są **16-bit** (C_id_small) lub 32-bit. ID są przydzielane przez menedżerów (flow, memory), nie ręcznie.
2. **Wszystkie operacje na liczbach** (`N`, `S`) mogą przepełniać się i zawijać — projekt assumes `__int128` na x64.
3. **Task scheduling** nie jest preemptywne — każde zadanie musi dobrowolnie oddać kontrolę (`I_B()`, `I_V()`).
4. **Windows-only**: Projekt nie wspiera Linux/Unix; ścieżki, API, wątkowanie są Windows (HANDLE, DWORD itp.).
5. **Moduł window** zależy od base (linkowanie: `-loux-base -lgdi32`).
6. **Suspended code** (`suspended/`) zawiera niedokończone cechy (net, fork, page, syntax) — mogą być eksperymenty lub robocze WiP.

## Kontakty i zasoby

- **Producent**: overcq
- **Email**: overcq@int.pl
- **GitHub**: https://github.com/overcq/oux-windows
- **Wsparcie**: https://overcq.ct8.pl/oux-c-plus.html
- **Issues**: https://github.com/overcq/oux-windows/issues
