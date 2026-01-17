CC := clang
CFLAGS := -fwrapv -march=native -Os -pipe \
	-I'C:\Program Files\llvm-mingw-20251202-msvcrt-x86_64\include'
.PHONY: all build clean
all: build
build: ui.exe
ui.exe: $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) -pipe -s -L..\..\module\base -L..\..\module\window -o $@ $^ -loux-base -loux-window
%.o: %.c
	$(CC) -c $(CFLAGS) -I..\..\compile -I..\..\module\base -I..\..\module\window -I. -include E_cplus_S_not_to_libs.h -o $@ $<
clean:
	del ui.exe