SRC=menu.c
BIN=menu

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lSDL_ttf -o $(BIN)

clean:
	rm -f $(BIN)
