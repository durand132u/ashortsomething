SRC=sdlanim.c game.c
BIN=sdlanim

$(BIN): $(SRC) game.h
	gcc -Wall -g -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)

clean:
	rm -f $(BIN)
