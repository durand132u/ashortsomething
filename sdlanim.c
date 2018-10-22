#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "game.h"


/* Size of the window */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 320

#define GRASS_SIZE 32

/* Order of the different directions in the picture: */
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5

struct vector vit = {0,0};
struct sprite_t perso;
struct sprite_t fireball;
/* Handle events coming from the user:
   - quit the game?
   - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
*/
void HandleEvent(SDL_Event event,
		 int *gameover, int *currDirection, int *animFlip, struct sprite_t *perso, struct sprite_t *fireball)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *gameover = 1;
    break;

    /* handle the keyboard */
    
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:   
		case SDLK_q:
			*gameover = 0;
			break;
		  
		case SDLK_LEFT:
			perso->currDirection = DIR_LEFT;
			*animFlip = 1 - *animFlip;
			perso->pos.x -= SPRITE_STEP;
			break;
		  
		case SDLK_RIGHT:
			perso->currDirection = DIR_RIGHT;
			*animFlip = 1 - *animFlip;
			perso->pos.x += SPRITE_STEP;
			break;
		  
		case SDLK_UP:
			perso->currDirection = DIR_UP;
			*animFlip = 1 - *animFlip;
			perso->pos.y -= SPRITE_STEP;
			break;
			
		case SDLK_DOWN:
			perso->currDirection = DIR_DOWN;
			*animFlip = 1 - *animFlip;
			perso->pos.y += SPRITE_STEP;
			break;
		  
		case SDLK_SPACE:
		
			if (fireball->life ==0) {
				fireball->life = 80;
				fireball->pos.x = perso->pos.x;
				fireball->pos.y = perso->pos.y;
				double angle = (perso->currDirection * ((2*M_PI/4) + (M_PI/4)));
				fireball->v.x = 4*cos(angle);
				fireball->v.y = -4 * sin(angle);
				fireball->display = 1;
			}
		  break;
		  
		default:
			break;
    }
    
    break;
  }
}



int main(int argc, char* argv[]){

  int gameover =1                  ;
  SDL_Surface *screen, *temp, *sprite, *grass, *spritefire;
    int colorkey;

    /* Information about the current situation of the sprite: */
    int currentDirection = DIR_RIGHT;
    
    /* Walking in a direction is animated with 2 images; we use a boolean
     * that we flip after each movement to show them in turn and create
     * the illusion */
    int animationFlip = 0;

    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /* load sprite */
	{
		temp   = SDL_LoadBMP("sprite.bmp");
		sprite = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);

		temp = SDL_LoadBMP("fireball.bmp");
		spritefire = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
	}
	
	/*load background picture*/
	{
		temp = SDL_LoadBMP("grass.bmp");
		grass = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
	}

    /* setup sprite colorkey and turn on RLE */
	{
		colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

		colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
		SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	}
	
	/* initialise struct */
	perso.currDirection = 0;
	perso.display = 1;
	perso.size = 32;
	fireball.size = 8;
		
	/*initialisation*/
		{
			perso.pos.x = (SCREEN_WIDTH - perso.size)/2;
			perso.pos.y = (SCREEN_HEIGHT - perso.size)/2;
		}
		
	/* main loop: check events and re-draw the window until the end */
	while (gameover !=0)
	{
		SDL_Event event;

		/* look for an event; possibly update the position and the shape
		 * of the sprite. */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event, &gameover, &currentDirection,
			&animationFlip, &perso, &fireball);
		}
			
			
		/*position*/
		{
			if (fireball.display == 1){
				fireball.pos.x = fireball.pos.x + fireball.v.x;
				fireball.pos.y = fireball.pos.y + fireball.v.y;
			}
		}
			
		/*hyperspace*/
		{
			if (perso.pos.x < 0)  {
				perso.pos.x = SCREEN_WIDTH - perso.size;
			}
			if (perso.pos.x > SCREEN_WIDTH - perso.size) {
				perso.pos.x = perso.size ;
			}
			if (perso.pos.y < 0){
				perso.pos.y = SCREEN_HEIGHT - perso.size;
			}
			if (perso.pos.y > SCREEN_HEIGHT - perso.size) {
				perso.pos.y = perso.size;
			}
		}

		/*check and refresh fireball life */
		{
			if(fireball.life == 0){
				fireball.display=0;
			}
			else{
				fireball.life = fireball.life -1;
			}
		}
			
		/* draw the background */
		{			
			for(int x =0; x< SCREEN_WIDTH/GRASS_SIZE; x++){
				for(int y =0; y< SCREEN_HEIGHT/GRASS_SIZE; y++){				
					SDL_Rect position;
					position.x = x * GRASS_SIZE;
					position.y = y * GRASS_SIZE;
					SDL_BlitSurface(grass, NULL, screen, &position);
				}
			}
		}
	  
		/* draw sprite*/
		{
			if (perso.display != 0) {
				SDL_Rect spriteImage;
				SDL_Rect spritePos;
				spritePos.x = perso.pos.x;
				spritePos.y = perso.pos.y;
				spriteImage.y = 0;
				spriteImage.w = perso.size;
				spriteImage.h = perso.size;
				spriteImage.x = perso.size*(perso.currDirection*2);
				SDL_BlitSurface(sprite, &spriteImage, screen, &spritePos);
			}
				
			if (fireball.display != 0) {
				SDL_Rect fireballImage;
				SDL_Rect fireballPosition;
				fireballPosition.x = fireball.pos.x;
				fireballPosition.y = fireball.pos.y;
				fireballImage.y = 0;
				fireballImage.w = fireball.size;
				fireballImage.h = fireball.size;
				fireballImage.x = fireball.size;
				SDL_BlitSurface(sprite, &fireballImage, screen, &fireballPosition);
			}
		}
			
		

		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(12);
		
	}		
	/* clean up */
		SDL_FreeSurface(sprite);
		SDL_FreeSurface(grass);
		SDL_Quit();

		return 0;
}