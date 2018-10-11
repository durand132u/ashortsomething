SRC=sdlanim.c game.c
BIN=sdlanim

$(BIN): $(SRC) game.h
	gcc -Wall -g -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -l SDL_ttf -o $(BIN)

clean:
	rm -f $(BIN)
