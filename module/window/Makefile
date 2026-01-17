CC := clang
CFLAGS := -fwrapv -march=native -Os -pipe \
	-Wno-inconsistent-dllimport \
	-I'C:\Program Files\llvm-mingw-20251202-msvcrt-x86_64\include'
.PHONY: all build clean
all: build
build: liboux-window.dll
liboux-window.dll: $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) -pipe -s -shared -Wl,--out-implib=$@.a -L..\base -o $@ $^ -loux-base -lgdi32
%.o: %.c
	$(CC) -c $(CFLAGS) -DE_cplus_C_building_S_window -I..\..\compile -I.. -I..\base -I. -include E_cplus_S_to_libs.h -o $@ $<
clean:
	del liboux-window.dll liboux-window.dll.a
