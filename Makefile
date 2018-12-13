SRC=sdlanim.c
BIN=sdlanim

$(BIN): $(SRC) game.h
	gcc -Wall -g3 -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -lSDL_ttf -lSDL_mixer -L./usr/lib -I./usr/include  -o $(BIN)

clean:
	rm -f $(BIN)
