#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "game.h"

#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3

#define SPRITE_STEP     5

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024


struct vector vit = {0,0}; /* vector for speed */

SDL_Surface *temp, *sprite, *grass;

int colorkey;

double angle =0;

void move_left(int *currDirection, int *animFlip, SDL_Rect *position) 
{
	*currDirection = DIR_LEFT;
	*animFlip = 1 - *animFlip;
	position->x -= SPRITE_STEP;
}

void move_right(int *currDirection, int *animFlip, SDL_Rect *position) 
{
	*currDirection = DIR_RIGHT;
	*animFlip = 1 - *animFlip;
	position->x += SPRITE_STEP;
}

void move_up(int *currDirection, int *animFlip, SDL_Rect *position) 
{
	*currDirection = DIR_UP;
	*animFlip = 1 - *animFlip;
	position->y -= SPRITE_STEP;
}

void move_down(int *currDirection, int *animFlip, SDL_Rect *position) 
{
	*currDirection = DIR_DOWN;
	*animFlip = 1 - *animFlip;
	position->y += SPRITE_STEP;
}

void init(struct sprite_t *perso)
{
	perso->pos.x = (SCREEN_WIDTH - perso->size)/2;
	perso->pos.y = (SCREEN_HEIGHT - perso->size)/2;
	perso->v.x = 0;
	perso->v.y = 0;
}

void init_fireball(struct sprite_t *perso, struct sprite_t *fireball)
{
	if (fireball->life ==0) 
	{
		fireball->life = 80;
		fireball->pos.x = perso->pos.x;
		fireball->pos.y = perso->pos.y;
		angle = (perso->currDirection * (2*M_PI/4));
		fireball->v.x = 4*cos(angle);
		fireball->v.y = -4 * sin(angle);
		fireball->display = 1;
	}
	else{
		return;
	}
}

/* void init_boom (struct sprite_t *boom, struct sprite_t *monster)
{
	boom->pos.x = monster->pos.x;
	boom->pos.y = monster->pos.y;
}
*/

void hyperspace(struct sprite_t *sprite)  /* Management of hyperspace */
{
  if (sprite->pos.x < 0)
    sprite->pos.x = SCREEN_WIDTH - sprite->size;
  if (sprite->pos.x > SCREEN_WIDTH - sprite->size) 
    sprite->pos.x = sprite->size ;
  if (sprite->pos.y < 0)
    sprite->pos.y = SCREEN_HEIGHT - sprite->size;
  if (sprite->pos.y > SCREEN_HEIGHT - sprite->size) 
    sprite->pos.y = sprite->size;
}


void fireball_move(struct sprite_t *fireball)
{
	fireball->pos.x = fireball->pos.x + fireball->v.x;
	fireball->pos.y = fireball->pos.y + fireball->v.y;
}

void convert_int (struct sprite_t *perso, SDL_Rect *spritePosition)
{
	spritePosition->x = (int) perso->pos.x;
	spritePosition->y = (int) perso->pos.y;
}


void draw_background(SDL_Surface *screen)
{
	SDL_Rect position;
	position.x = 0;
	position.y =0;
	SDL_BlitSurface(grass, NULL, screen, &position);
}


void hitbox (struct sprite_t *perso, SDL_Surface *sprite, SDL_Surface *screen)
{  
  SDL_Rect spriteImage;
  SDL_Rect spritePos;
  spritePos.x = perso->pos.x;
  spritePos.y = perso->pos.y;
  spriteImage.y = 0;
  spriteImage.w = perso->size;
  spriteImage.h = perso->size;
  spriteImage.x = perso->size*(perso->currDirection);
  SDL_BlitSurface(sprite, &spriteImage, screen, &spritePos);
}


void hitboxFireball( struct sprite_t *fireball, SDL_Surface *sprite, SDL_Surface *screen)
{
		  SDL_Rect fireballImage;
		  SDL_Rect fireballPosition;
		  fireballPosition.x = fireball->pos.x;
		  fireballPosition.y = fireball->pos.y;
		  fireballImage.y = 0;
		  fireballImage.w = fireball->size;
		  fireballImage.h = fireball->size;
		  fireballImage.x = fireball->size;

		  SDL_BlitSurface(sprite, &fireballImage, screen, &fireballPosition);
}	

bool collide_test (struct sprite_t sprite1, struct sprite_t sprite2, SDL_PixelFormat *format, int *cu, int *cv)
{
  /* rough test using the bounding boxes (bb) only */
  bool test = !(sprite2.pos.x > sprite1.pos.x + sprite1.size ||
		sprite2.pos.x + sprite2.size < sprite1.pos.x ||
		sprite2.pos.y > sprite1.pos.y + sprite1.sprite->h ||
		sprite2.pos.y + sprite2.sprite->h < sprite1.pos.y);
		return test;
}

void testlife(struct sprite_t *perso)
{
  if (perso->counter == 1) {
    perso->life = perso->life -1;
  }
}
