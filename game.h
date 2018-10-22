#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdbool.h>

struct vector
{
  float x;
  float y;
};

struct sprite_t
{
	struct vector pos;
	struct vector v;
	int currDirection;
	int size;
	int life;
	SDL_Surface *sprite;
	int counter;
	int display;
};
#endif