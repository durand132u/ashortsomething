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
	int argent;
	SDL_Surface *sprite;
	int display;
    int mana;
};

struct bdf_t
{
	struct vector pos;
	struct vector v;
	int currDirection;
	int size;
	int display;
	int range;
	SDL_Surface *sprite;
};

struct inventaire
{
	int champignon;
};
#endif
