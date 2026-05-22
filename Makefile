all: build-exe

build-exe: clean
	mkdir -p build
	x86_64-w64-mingw32-gcc src/*.c \
	-Iinclude \
	-Iglfw/include \
	-Lglfw/lib-mingw-w64 \
	-lglfw3 \
	-lgdi32 \
	-luser32 \
	-lkernel32 \
	-lshell32 \
	-lwinmm \
	-o build/game.exe

clean:
	rm -f build/game.exe