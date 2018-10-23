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
struct sprite_t monster;
struct sprite_t fireball;
struct sprite_t poisonball;
struct sprite_t deathball;
/* Handle events coming from the user:
   - quit the game?
   - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
*/
void HandleEvent(SDL_Event event,
		 int *gameover, int *currDirection, int *animFlip, struct sprite_t *perso, struct sprite_t *fireball, struct sprite_t *deathball, struct sprite_t *poisonball)
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
				fireball->pos.x = perso->pos.x+(GRASS_SIZE/3);
				fireball->pos.y = perso->pos.y+(GRASS_SIZE/3);
				if(perso->currDirection == DIR_RIGHT){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = 2*cos(angle);
					fireball->v.y = -2 * sin(angle);
					fireball->display = 1;
				}
				if(perso->currDirection == DIR_LEFT){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = -2*cos(angle);
					fireball->v.y = 2 * sin(angle);
					fireball->display = 1;
				}
				if(perso->currDirection == DIR_UP){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = 2 * sin(angle);
					fireball->v.y = -2*cos(angle);
					fireball->display = 1;
				}
				if(perso->currDirection == DIR_DOWN){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = -2 * sin(angle);
					fireball->v.y = 2*cos(angle);
					fireball->display = 1;
				}

			}
		  break;


		case SDLK_F1:
		
			if (poisonball->life ==0) {
				poisonball->life = 80;
				poisonball->pos.x = perso->pos.x+(GRASS_SIZE/3);
				poisonball->pos.y = perso->pos.y+(GRASS_SIZE/3);
				if(perso->currDirection == DIR_RIGHT){
					double angle = (perso->currDirection * (2*M_PI));
					poisonball->v.x = 2*cos(angle);
					poisonball->v.y = -2 * sin(angle);
					poisonball->display = 1;
				}
				if(perso->currDirection == DIR_LEFT){
					double angle = (perso->currDirection * (2*M_PI));
					poisonball->v.x = -2*cos(angle);
					poisonball->v.y = 2 * sin(angle);
					poisonball->display = 1;
				}
				if(perso->currDirection == DIR_UP){
					double angle = (perso->currDirection * (2*M_PI));
					poisonball->v.x = 2 * sin(angle);
					poisonball->v.y = -2*cos(angle);
					poisonball->display = 1;
				}
				if(perso->currDirection == DIR_DOWN){
					double angle = (perso->currDirection * (2*M_PI));
					poisonball->v.x = -2 * sin(angle);
					poisonball->v.y = 2*cos(angle);
					poisonball->display = 1;
				}

			}
		  break;


		case SDLK_F2:
		
			if (deathball->life ==0) {
				deathball->life = 80;
				deathball->pos.x = perso->pos.x+(GRASS_SIZE/3);
				deathball->pos.y = perso->pos.y+(GRASS_SIZE/3);
				if(perso->currDirection == DIR_RIGHT){
					double angle = (perso->currDirection * (2*M_PI));
					deathball->v.x = 2*cos(angle);
					deathball->v.y = -2 * sin(angle);
					deathball->display = 1;
				}
				if(perso->currDirection == DIR_LEFT){
					double angle = (perso->currDirection * (2*M_PI));
					deathball->v.x = -2*cos(angle);
					deathball->v.y = 2 * sin(angle);
					deathball->display = 1;
				}
				if(perso->currDirection == DIR_UP){
					double angle = (perso->currDirection * (2*M_PI));
					deathball->v.x = 2 * sin(angle);
					deathball->v.y = -2*cos(angle);
					deathball->display = 1;
				}
				if(perso->currDirection == DIR_DOWN){
					double angle = (perso->currDirection * (2*M_PI));
					deathball->v.x = -2 * sin(angle);
					deathball->v.y = 2*cos(angle);
					deathball->display = 1;
				}

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
  SDL_Surface *screen, *temp, *sprite, *grass, *spritefire, *spritemonster, *spritedeath, *spritepoison;
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

		temp = SDL_LoadBMP("monster.bmp");
		spritemonster = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		
		temp = SDL_LoadBMP("fireball.bmp");
		spritefire = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		
		temp = SDL_LoadBMP("poisonball.bmp");
		spritepoison = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);

		temp = SDL_LoadBMP("deathball.bmp");
		spritedeath = SDL_DisplayFormat(temp);
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
		SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritemonster, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepoison, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritedeath, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	}
	
	/* initialise struct */
	perso.currDirection = 0;
	monster.currDirection =0;
	perso.display = 1;
	monster.display =1;
	perso.size = 32;
	monster.size =32;
	fireball.size = 16;
	poisonball.size = 16;
	deathball.size = 16;
		
	/*initialisation*/
		{
			perso.pos.x = (SCREEN_WIDTH - perso.size)/2;
			perso.pos.y = (SCREEN_HEIGHT - perso.size)/2;
			
			monster.pos.x =0;
			monster.pos.y =0;
		}
		
	/* main loop: check events and re-draw the window until the end */
	while (gameover !=0)
	{
		SDL_Event event;

		/* look for an event; possibly update the position and the shape
		 * of the sprite. */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event, &gameover, &currentDirection,
			&animationFlip, &perso, &fireball, &poisonball, &deathball);
		}
			
			
		/*position*/
		{
			if (fireball.display == 1){
				fireball.pos.x = fireball.pos.x + fireball.v.x;
				fireball.pos.y = fireball.pos.y + fireball.v.y;
			}
			
			if (poisonball.display == 1){
				poisonball.pos.x = poisonball.pos.x + poisonball.v.x;
				poisonball.pos.y = poisonball.pos.y + poisonball.v.y;
			}

			if (deathball.display == 1){
				deathball.pos.x = deathball.pos.x + deathball.v.x;
				deathball.pos.y = deathball.pos.y + deathball.v.y;
			}
			
		/* Déplacement du monstre */
				monster.pos.x = monster.pos.x + deathball.v.x; //Contrôle du monstre avec la deathball
				monster.pos.y = monster.pos.y + deathball.v.y;
			
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
		/* Monster hyperspace */
			if (monster.pos.x < 0)  {
				monster.pos.x = SCREEN_WIDTH - perso.size;
			}
			if (monster.pos.x > SCREEN_WIDTH - perso.size) {
				monster.pos.x = perso.size ;
			}
			if (monster.pos.y < 0){
				monster.pos.y = SCREEN_HEIGHT - perso.size;
			}
			if (monster.pos.y > SCREEN_HEIGHT - perso.size) {
				monster.pos.y = perso.size;
			}
		}

		/*check and refresh ball life */
		{
			if(fireball.life == 0){
				fireball.display=0;
			}
			else{
				fireball.life = fireball.life -1;
			}

			if(poisonball.life == 0){
				poisonball.display=0;
			}
			else{
				poisonball.life = poisonball.life -1;
			}

			if(deathball.life == 0){
				deathball.display=0;
			}
			else{
				deathball.life = deathball.life -5;
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
			
			if (monster.display != 0) {
				SDL_Rect monsterImage;
				SDL_Rect monsterPos;
				monsterPos.x = monster.pos.x;
				monsterPos.y = monster.pos.y;
				monsterImage.y = 0;
				monsterImage.w = monster.size;
				monsterImage.h = monster.size;
				monsterImage.x = monster.size*(monster.currDirection*2);
				SDL_BlitSurface(spritemonster, &monsterImage, screen, &monsterPos);
			}
				
			if (fireball.display != 0) {
				SDL_Rect fireballImage;
				SDL_Rect fireballPosition;
				fireballPosition.x = fireball.pos.x;
				fireballPosition.y = fireball.pos.y;
				fireballImage.y = 0;
				fireballImage.w = fireball.size;
				fireballImage.h = fireball.size;
				fireballImage.x = 0;
				SDL_BlitSurface(spritefire, &fireballImage, screen, &fireballPosition);
			}


			if (poisonball.display != 0) {
				SDL_Rect poisonballImage;
				SDL_Rect poisonballPosition;
				poisonballPosition.x = poisonball.pos.x;
				poisonballPosition.y = poisonball.pos.y;
				poisonballImage.y = 0;
				poisonballImage.w = poisonball.size;
				poisonballImage.h = poisonball.size;
				poisonballImage.x = 0;
				SDL_BlitSurface(spritepoison, &poisonballImage, screen, &poisonballPosition);
			}


			if (deathball.display != 0) {
				SDL_Rect deathballImage;
				SDL_Rect deathballPosition;
				deathballPosition.x = deathball.pos.x;
				deathballPosition.y = deathball.pos.y;
				deathballImage.y = 0;
				deathballImage.w = deathball.size;
				deathballImage.h = deathball.size;
				deathballImage.x = 0;
				SDL_BlitSurface(spritedeath, &deathballImage, screen, &deathballPosition);
			}

			


		}
			
		

		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(12);
		
	}		
	/* clean up */
		SDL_FreeSurface(sprite);
		SDL_FreeSurface(spritefire);
		SDL_FreeSurface(spritemonster);
		SDL_FreeSurface(spritepoison);
		SDL_FreeSurface(spritedeath);
		SDL_FreeSurface(grass);
		SDL_Quit();

		return 0;
}
