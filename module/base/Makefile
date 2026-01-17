CC := clang
CFLAGS := -fwrapv -march=native -Os -pipe \
	-Wno-inconsistent-dllimport \
	-I'C:\Program Files\llvm-mingw-20251202-msvcrt-x86_64\include'
.PHONY: all build clean
all: build
build: liboux-base.dll
liboux-base.dll: $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) -pipe -s -shared -Wl,--out-implib=$@.a -o $@ $^
%.o: %.c
	$(CC) -c $(CFLAGS) -DE_cplus_C_building_S_base -I..\..\compile -I.. -I..\window -I. -include E_cplus_S_to_libs.h -o $@ $<
clean:
	del liboux-base.dll liboux-base.dll.a