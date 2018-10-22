#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL_ttf.h>
#include "game.h"




/* Size of the window */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 320
/* Size of the grass texture picture */
#define GRASS_SIZE    32

/* In the sprite, we have 8 images of a 32x32 picture,
 * 2 images for each direction. */
/* Size of one image: */
#define SPRITE_SIZE     32
/* Taille de la boule de feu: */
#define FIREBALL_SIZE 32

/* Order of the different directions in the picture: */
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5*



struct sprite_t perso;
struct sprite_t fireball;
int gameover = 1;
int life =1;


/* Handle events coming from the user:
   - quit the game?
   - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
*/
void HandleEvent(SDL_Event event,
		 int *quit, int *currDirection, int *animFlip, SDL_Rect *position, SDL_Rect *fireballPosition, struct sprite_t *perso, struct sprite_t *fireball)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;

    /* handle the keyboard */
    
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:   
    case SDLK_q:
		*quit = 1;
		break;
      
    case SDLK_LEFT:
		move_left(currDirection, animFlip, position);
		break;
      
    case SDLK_RIGHT:
		move_right(currDirection, animFlip, position);
		break;
      
    case SDLK_UP:
		move_up(currDirection, animFlip, position);
		break;
		
    case SDLK_DOWN:
		move_down(currDirection, animFlip, position);
		break;
      
    case SDLK_SPACE:
		init_fireball(perso, fireball);
      break;
      
    default:
      break;
    }
    
    break;
  }
}



int main(int argc, char* argv[]){
  
  SDL_Surface *screen, *temp, *sprite, *grass, *spritefire;
    int colorkey;

    /* Information about the current situation of the sprite: */
    int currentDirection = DIR_RIGHT;
    
    /* Walking in a direction is animated with 2 images; we use a boolean
     * that we flip after each movement to show them in turn and create
     * the illusion */
    int animationFlip = 0;

    /* Rectangle to store the position of the sprite in the window.
     * Only the x and y coordinates are used. */
    SDL_Rect spritePosition;
	SDL_Rect fireballPosition;

    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /* load sprite */
    temp   = SDL_LoadBMP("sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp = SDL_LoadBMP("fireball.bmp");
    spritefire = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* setup sprite colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
	
	if (gameover !=0){
	
	
		perso.currDirection = 0;
		perso.display = 1;
		perso.life =life;
		perso.size = 32;
		fireball.size = 8;
		
		/*initialisation*/
		init(&perso);
		
		/*load grass picture*/
		temp = SDL_LoadBMP("grass.bmp");
		grass = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		
		
	
		/* main loop: check events and re-draw the window until the end */
		while (!gameover)
		{
			SDL_Event event;

			/* look for an event; possibly update the position and the shape
			 * of the sprite. */
			if (SDL_PollEvent(&event)) {
				HandleEvent(event, &gameover, &currentDirection,
				&animationFlip, &spritePosition, &fireballPosition, &perso, &fireball);
			}
			
			
			/*position*/
			fireball_move(&fireball);
			
			/*hyperspace*/
			
			hyperspace(&perso);

			/*check and refresh fireball life */
			if(fireball.life == 0){
				fireball.display=0;
			}
			else{
				fireball.life = fireball.life -1;
			}
			
			/* draw the background */
			draw_background(screen);
	  
			/* draw sprite*/

			if (perso.display != 0) {
				hitbox( &perso, sprite, screen);
			}
			
			if (fireball.display != 0) {
				hitboxFireball( &fireball, spritefire, screen);
			}
			
			
		

			/* update the screen */
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(12);
		}
	}		
	/* clean up */
		SDL_FreeSurface(sprite);
		SDL_FreeSurface(grass);
		SDL_Quit();

		return 0;
}