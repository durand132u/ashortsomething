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


void move_left(int *currDirection, int *animFlip, SDL_Rect *position);
void move_right(int *currDirection, int *animFlip, SDL_Rect *position);
void move_up(int *currDirection, int *animFlip, SDL_Rect *position);
void move_down(int *currDirection, int *animFlip, SDL_Rect *position);

void init(struct sprite_t *perso);
void init_fireball(struct sprite_t *perso, struct sprite_t *fireball);
//void init_explode(struct sprite_t *boom, struct sprite_t *monster);

void hyperspace(struct sprite_t *perso);

//void boom_move(struct sprite_t *boom);
void fireball_move(struct sprite_t *fireball);

void convert_int (struct sprite_t *perso, SDL_Rect *spritePosition);

void draw_background(SDL_Surface *screen);

void hitbox (struct sprite_t *perso, SDL_Surface *sprite, SDL_Surface *screen);
void hitboxFireball (struct sprite_t *perso, SDL_Surface *sprite, SDL_Surface *screen);

bool collide_test (struct sprite_t sprite1, struct sprite_t sprite2, SDL_PixelFormat *format, int *cu, int *cv);

void testlife(struct sprite_t *ship);

#endif