SRC=sdlanim.c
BIN=sdlanim

$(BIN): $(SRC) game.h
	gcc -Wall -g -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -lSDL_ttf -o $(BIN)

clean:
	rm -f $(BIN)
