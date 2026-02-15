CC := clang
CFLAGS := -fwrapv -march=native -Os -s -pipe
.PHONY: all build clean
all: build
build: make-oux.exe
make-oux.exe: main.c
	$(CC) $(CFLAGS) -o $@ $< -ID:\moje\programy\obce\pcre2\build\interface -LD:\moje\programy\obce\pcre2\build -lpcre2-8
clean:
	del make-oux.exe
