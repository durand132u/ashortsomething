#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "game.h"


/* Size of the window */
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768

#define GRASS_SIZE 32

/* Order of the different directions in the picture: */
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3
#define COLIDE			4/3
#define MAX_HP    		100
/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5

struct vector vit = {0,0};
struct sprite_t perso;
struct sprite_t monster;
struct sprite_t ludo;
struct bdf_t fireball;
struct sprite_t poisonball;
struct sprite_t deathball;
struct sprite_t HP_potion;
SDL_Surface* barreDeVie_Ludo;
SDL_Surface* barreDeVie_monstre;
SDL_Surface* barreDeVie_perso;

/* Handle events coming from the user:
   - quit the game?
   - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
*/
void HandleEvent(SDL_Event event,
		 int *gameover, int *currDirection, int *animFlip, struct sprite_t *perso, struct sprite_t *ludo, struct bdf_t *fireball, struct sprite_t *deathball, struct sprite_t *poisonball, struct sprite_t *HP_potion)
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
		
			if (fireball->display==0) {
				fireball->display=1;
				fireball->range=100;
				fireball->pos.x = perso->pos.x+(GRASS_SIZE/3);
				fireball->pos.y = perso->pos.y+(GRASS_SIZE/3);
				if(perso->currDirection == DIR_RIGHT){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = 2*cos(angle);
					fireball->v.y = -2 * sin(angle);
				}
				if(perso->currDirection == DIR_LEFT){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = -2*cos(angle);
					fireball->v.y = 2 * sin(angle);
				}
				if(perso->currDirection == DIR_UP){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = 2 * sin(angle);
					fireball->v.y = -2*cos(angle);
				}
				if(perso->currDirection == DIR_DOWN){
					double angle = (perso->currDirection * (2*M_PI));
					fireball->v.x = -2 * sin(angle);
					fireball->v.y = 2*cos(angle);
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
					poisonball->v.y = 2 * sin(angle);
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
			
		case SDLK_F3:
			/* Apparition PNJ Ludo */
			ludo->life= 100;
			ludo->display = 1;
			ludo->pos.x = 200;
			ludo->pos.y = 200;
		
			
		break;
	
			
		  
		default:
			break;
    }
    
    break;
  }
}


/*Working Collision Ludo -> Perso*/ 	

	int CollisionBdf(struct sprite_t* a, struct bdf_t* b){
		if((a->display==1)&&(b->display==1)){
			float diffX, diffY;
			diffX = fabs((b->pos.x+b->size)-(a->pos.x+a->size/2));
			diffY = fabs((b->pos.y+b->size)-(a->pos.y+a->size/2));
			if((diffX<b->size)&&(diffY<b->size)&&(b->display!=0)){
				return 1;
			}
			return 0;
		}
		return 0;
		
	}
	int Collision(struct sprite_t* a, struct sprite_t* b){
		if((a->display==1)&&(b->display==1)){
			float diffX, diffY;
			diffX = fabs((b->pos.x+b->size)-(a->pos.x+a->size));
			diffY = fabs((b->pos.y+b->size)-(a->pos.y+a->size));
			if((diffX<b->size)&&(diffY<b->size)&&(b->display!=0)){
				return 1;
			}
			return 0;
		}
		return 0;
	}

	int CollisionDistance(struct sprite_t* a, struct sprite_t* b, int Dx){
		if((a->display==1)&&(b->display==1)){
			float diffX, diffY;
			diffX = fabs((b->pos.x+b->size)-(a->pos.x+a->size));
			diffY = fabs((b->pos.y+b->size)-(a->pos.y+a->size));
			if((diffX<Dx)&&(diffY<Dx)&&(b->display!=0)){
				return 1;
			}
			return 0;
		}
		return 0;
	}

	/*int IAFUYARDE(struct sprite_t* a, struct sprite_t* b){
			if((a->display==1)&&(b->display==1)){
			diffX = fabs((b->pos.x+b->size)-(a->pos.x+a->size));
			diffY = fabs((b->pos.y+b->size)-(a->pos.y+a->size));
			if((diffX<200&&(a->display==1)&&(b->display==1))*/
			   
			   








int main(int argc, char* argv[]){

  int gameover =1                  ;
  SDL_Surface *screen, *temp, *sprite, *grass, *spritefire, *spritemonster, *spritedeath, *spritepoison, *spriteludo, *spritepotion;
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
		
		temp = SDL_LoadBMP("ludo.bmp");
		spriteludo = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp); 
		
		temp = SDL_LoadBMP("moyenne_potion_rouge.bmp");
		spritepotion = SDL_DisplayFormat(temp);
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
		SDL_SetColorKey(spriteludo, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritemonster, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepoison, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritedeath, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepotion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);


	}
	
	/* initialise struct */
	perso.currDirection = 0;
	monster.currDirection =0;
	perso.display = 1;
	perso.size = 32;
	perso.life = MAX_HP;
	ludo.display = 1;
	ludo.size = 32;
	ludo.life = MAX_HP;
	monster.display = 1;
	monster.life=MAX_HP;
	monster.size =32;
	fireball.size = 16;
	poisonball.size = 16;
	deathball.size = 16;
	HP_potion.size = 32;
	HP_potion.life=1;
	HP_potion.display = 1;

	
	
	//printf(" fX %lf\n fY %lf",fireball.pos.x, fireball.pos.y); printf 
		
	/*initialisation*/
		{
			perso.pos.x = (SCREEN_WIDTH - perso.size)/2;
			perso.pos.y = (SCREEN_HEIGHT - perso.size)/2;
			
			monster.pos.x =0;
			monster.pos.y =0;
			
			HP_potion.pos.x=400;
			HP_potion.pos.y=400;
			
			//Initialisation barre de vie
			barreDeVie_Ludo = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
			barreDeVie_monstre = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
			barreDeVie_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);


		}
		
	/* main loop: check events and re-draw the window until the end */
	while (gameover !=0)
	{
		SDL_Event event;
		

		/* look for an event; possibly update the position and the shape
		 * of the sprite. */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event, &gameover, &currentDirection,
			&animationFlip, &perso, &ludo, &fireball, &poisonball, &deathball, &HP_potion);
		}
			
		
		//Barre de vie ludo
		
		//FillRect d'un SDLRect avec règle de trois basique
		SDL_FillRect(barreDeVie_Ludo, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //fond noir
		SDL_Rect HP_ludo;
		HP_ludo.x = 0;
		HP_ludo.y = 0;
		HP_ludo.w = ludo.life*ludo.size/MAX_HP;
		HP_ludo.h = 3;
			if(ludo.life>(80*MAX_HP/100)){
				SDL_FillRect(barreDeVie_Ludo, &HP_ludo, SDL_MapRGB(barreDeVie_Ludo->format, 0, 255, 0));
			}
			if(ludo.life>(60*MAX_HP/100)&&ludo.life<=(80*MAX_HP/100)){
				SDL_FillRect(barreDeVie_Ludo, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_Ludo, &HP_ludo, SDL_MapRGB(barreDeVie_Ludo->format, 255, 255, 0)); //jaune
			}
			if(ludo.life>40&&ludo.life<=(60*MAX_HP/100)){
				SDL_FillRect(barreDeVie_Ludo, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_Ludo, &HP_ludo, SDL_MapRGB(barreDeVie_Ludo->format, 255, 112, 0)); //orange
			}
			if(ludo.life>0&&ludo.life<=(40*MAX_HP/100)){
				SDL_FillRect(barreDeVie_Ludo, &HP_ludo, SDL_MapRGB(barreDeVie_Ludo->format, 255, 0, 0)); // rouge
			}
		
		//Barre de vie monstre
		SDL_FillRect(barreDeVie_monstre, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //fond noir
		SDL_Rect HP_monstre;
		HP_monstre.x = 0;
		HP_monstre.y = 0;
		HP_monstre.w = monster.life*monster.size/MAX_HP;
		HP_monstre.h = 3;
		if(monster.life>(80*MAX_HP/100)){
			SDL_FillRect(barreDeVie_monstre, &HP_monstre, SDL_MapRGB(barreDeVie_monstre->format, 0, 255, 0));
		}
		if(monster.life>(60*MAX_HP/100)&&monster.life<=(80*MAX_HP/100)){
				SDL_FillRect(barreDeVie_monstre, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_monstre, &HP_monstre, SDL_MapRGB(barreDeVie_monstre->format, 255, 255, 0)); //jaune
			}
		if(monster.life>(40*MAX_HP/100)&&monster.life<=(60*MAX_HP/100)){
				SDL_FillRect(barreDeVie_monstre, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_monstre, &HP_monstre, SDL_MapRGB(barreDeVie_monstre->format, 255, 112, 0)); //orange
		}
		if(monster.life>0&&monster.life<=(40*MAX_HP/100)){
				SDL_FillRect(barreDeVie_monstre, &HP_monstre, SDL_MapRGB(barreDeVie_monstre->format, 255, 0, 0)); // rouge
		}
		
		//Barre de vie personnage
		SDL_FillRect(barreDeVie_perso, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //fond noir
		SDL_Rect HP_perso;
		HP_perso.x = 0;
		HP_perso.y = 0;
		HP_perso.w = perso.life*perso.size/MAX_HP;
		HP_perso.h = 3;
		SDL_FillRect(barreDeVie_perso, &HP_perso, SDL_MapRGB(barreDeVie_perso->format, 0, 255, 0));
		if(perso.life>(80*MAX_HP/100)){
			SDL_FillRect(barreDeVie_perso, &HP_monstre, SDL_MapRGB(barreDeVie_perso->format, 0, 255, 0));
		}
		if(perso.life>(60*MAX_HP/100)&&perso.life<=(80*MAX_HP/100)){
				SDL_FillRect(barreDeVie_perso, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_perso, &HP_monstre, SDL_MapRGB(barreDeVie_perso->format, 255, 255, 0)); //jaune
			}
		if(perso.life>(40*MAX_HP/100)&&perso.life<=(60*MAX_HP/100)){
				SDL_FillRect(barreDeVie_perso, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_FillRect(barreDeVie_perso, &HP_monstre, SDL_MapRGB(barreDeVie_perso->format, 255, 112, 0)); //orange
		}
		if(perso.life>0&&perso.life<=(40*MAX_HP/100)){
				SDL_FillRect(barreDeVie_perso, &HP_monstre, SDL_MapRGB(barreDeVie_perso->format, 255, 0, 0)); // rouge
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


		/*Gestion aléatoire entre -2 et 4 */
		srand(time(NULL));
		int a = rand()%5;		
		switch(a){
			case(0):
				break;
			case(1):
				monster.pos.x = monster.pos.x +5;
				break;
			case(2):
				monster.pos.x = monster.pos.x -5;
				break;
			case(3):
				monster.pos.y = monster.pos.y +5;
				break;
			case(4):
				monster.pos.y = monster.pos.y -5;
				break;
			default :
				break;
		}
			

				//monster.pos.x = monster.pos.x + deathball.v.x; //Contrôle du monstre avec la deathball
				//monster.pos.y = monster.pos.y + deathball.v.y;
			/* // Le monstre tourne en rond
			double angle2 = (rand()%90);
				ludo.display = 1;
				ludo.pos.x += 2 * cos(angle2);
				ludo.pos.y += 2*sin(angle2);
				
				*/
			//IA Aggressive
			if(perso.pos.x>ludo.pos.x){
				ludo.pos.x+=5;
			} 
			if(perso.pos.x<ludo.pos.x){
				ludo.pos.x-=5;
			} 
			if(perso.pos.y > ludo.pos.y){
				ludo.pos.y+=5;	
			}
			if(perso.pos.y < ludo.pos.y){
				ludo.pos.y-=5;	
			}
			
			//IA Fuyarde 
			/*if(perso.pos.x<ludo.pos.x){
				ludo.pos.x+=3;
			} 
			if(perso.pos.x>ludo.pos.x){
				ludo.pos.x-=3;
			} 
			if(perso.pos.y <ludo.pos.y){
				ludo.pos.y+=3;	
			}
			if(perso.pos.y > ludo.pos.y){
				ludo.pos.y-=3;	
			}*/
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
			
			/* Ludo Hyperspace*/
				if (ludo.pos.x < 0)  {
				ludo.pos.x = SCREEN_WIDTH - perso.size;
			}
			if (ludo.pos.x > SCREEN_WIDTH - perso.size) {
				ludo.pos.x = perso.size ;
			}
			if (ludo.pos.y < 0){
				ludo.pos.y = SCREEN_HEIGHT - perso.size;
			}
			if (ludo.pos.y > SCREEN_HEIGHT - perso.size) {
				ludo.pos.y = perso.size;
			}
		}

		/*check and refresh ball life */
		{
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
				deathball.life = deathball.life -10;
			}
			if(monster.life <= 0){
				monster.display = 0;
			}
			if(ludo.life <= 0){
				ludo.display = 0;
			}
			if(fireball.display!=0&&fireball.range!=0){
			    fireball.range--;
			}
			if(fireball.display!=0&&fireball.range==0){
				fireball.display=0;
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
				SDL_BlitSurface(barreDeVie_perso, NULL, screen, &spritePos);


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
				SDL_BlitSurface(barreDeVie_monstre, NULL, screen, &monsterPos);


				
			}
			
			if (ludo.display != 0) {
				SDL_Rect ludoImage;
				SDL_Rect ludoPos;
				ludoPos.x = ludo.pos.x;
				ludoPos.y = ludo.pos.y;
				ludoImage.y = 0;
				ludoImage.w = ludo.size;
				ludoImage.h = ludo.size;
				ludoImage.x = ludo.size*(ludo.currDirection*2);
				SDL_BlitSurface(spriteludo, &ludoImage, screen, &ludoPos);
				SDL_BlitSurface(barreDeVie_Ludo, NULL, screen, &ludoPos);



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
				
			if (HP_potion.display != 0) {
				SDL_Rect HP_potionImage;
				SDL_Rect HP_potionPosition;
				HP_potionPosition.x = HP_potion.pos.x;
				HP_potionPosition.y = HP_potion.pos.y;
				HP_potionImage.y = 0;
				HP_potionImage.w = HP_potion.size;
				HP_potionImage.h = HP_potion.size;
				HP_potionImage.x = 0;
				SDL_BlitSurface(spritepotion, &HP_potionImage, screen, &HP_potionPosition);
				
				
	
			}
			
			



			//1//100% Working Collision Perso -> Ludo	
			/*float diffX, diffY;
			diffX = fabs(((perso.pos.x+perso.size/2)-(ludo.pos.x)+ludo.size/2));
			diffY = fabs(((perso.pos.y+perso.size/2)-(ludo.pos.y)+ludo.size/2));
			if(diffX<40&&diffY<40){
				printf("Collision");
				ludo.life -=1;
			}
			printf("Difference de x %lf\n\n Diffference de y %lf\n\n", diffX,diffY);
			printf("Vie de ludo %d", ludo.life);*/

			
			
			//2//100% Working Collision Boule de feu -> Ludo
			/*float diffX, diffY;
			diffX = fabs(((fireball.pos.x+fireball.size)-(ludo.pos.x)+ludo.size/2-32));
			diffY = fabs(((fireball.pos.y+fireball.size)-(ludo.pos.y)+ludo.size/2-32));
			if(diffX<16&&diffY<16&&fireball.display!=0){
				double i;
				i++;
				printf("%lf Collision\n", i);
				
				fireball.display = 0;
				ludo.life -=25;
			}
			printf("Difference de x %lf\n\n Diffference de y %lf\n\n", diffX,diffY);
			printf("Vie de ludo %d", ludo.life);*/




			//Working Test utilisation fonction Collision
			
			if(Collision(&ludo, &perso)&&((ludo.display!=0)||(ludo.life!=0))){ 
				ludo.life -=1;
			}
			
			if(CollisionBdf(&ludo, &fireball)&&fireball.display!=0){ // Présence de quelques bugs en utilisant cette fonction avec la fireball, pour être plus précis voire //2//
				fireball.display = 0;
				ludo.life -=10;
				if(ludo.life<=0){
					
				}
			}
			
			if(CollisionBdf(&monster, &fireball)&&fireball.display!=0){
				fireball.display=0;
				monster.life -=10;

			}
			
			if(Collision(&monster, &perso)){ 
				monster.life -=1;
			}
			
			if(Collision(&HP_potion,&perso)&&HP_potion.display!=0&&perso.life<MAX_HP){
				HP_potion.display=0;
				perso.life +=30;
			}
			
			if(Collision(&HP_potion,&monster)&&HP_potion.display!=0&&monster.life<MAX_HP){
				HP_potion.display=0;
				monster.life +=50;
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
		SDL_FreeSurface(spriteludo);
		SDL_FreeSurface(barreDeVie_Ludo);
		SDL_FreeSurface(barreDeVie_perso);
		SDL_FreeSurface(barreDeVie_monstre);
		SDL_FreeSurface(spritepoison);
		SDL_FreeSurface(spritedeath);
		SDL_FreeSurface(grass);
		SDL_Quit();

		return 0;
}
