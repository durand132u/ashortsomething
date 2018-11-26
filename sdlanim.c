#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
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
#define MAX_MANA    	100
/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5
#define VITESSE_MOB 	2
#define fps 60

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
SDL_Surface* barreDeMana_perso;

int choice = 0;
int choiceTEST = 0;



/* Handle events coming from the user:
   - quit the game?
   - use of arrows to move the sprite
   In the second case, we modify the current direction and the
   position of the sprite in the window.
   We also change the animation bit used for creating the "walk" effect.
*/
void HandleEvent(SDL_Event event, int *gameover, int *currDirection, int *animFlip, struct sprite_t *perso, struct sprite_t *ludo,
 struct bdf_t *fireball, struct sprite_t *poisonball, struct sprite_t *deathball, struct sprite_t *HP_potion,int *display, int *posMouseX, int *posMouseY, int *selection)
{
	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			*gameover = 1;
			break;

		/* handle the keyboard */
		
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:   // retour au menu
				case SDLK_q:
					*display =1 ;
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
				
				case SDLK_F4:
					if(choiceTEST){
						choice = 1;
						choiceTEST= 0;
					} else {
						choice = 0;
						choiceTEST = 1;
					}
				break;
				default:
					break;
				}
				break;
		case SDL_MOUSEBUTTONDOWN:
			if((*display==1)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					//Lancement du jeu
					*display=2;
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=96*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					//Lancement des options
					*display=3;
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					//fermeture du jeu
					*gameover=0;
				}
			}
			if((*display==3)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					printf("ECRAN A AGRANDIR EN 16/9e"); //agrandir ecran
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					printf("ECRAN A REDUIRE EN 16/9e"); //reduire ecran
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=80*SCREEN_HEIGHT/100)&&(*posMouseY<=85*SCREEN_HEIGHT/100)){
					printf("AJOUTER GESTION DES CONTROLES"); //controles
					*display=4; //menu de controles
				}
				if((*posMouseX>=60*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*display=1; //retour menu
				}
			}
			
			if((*display==4)){
				SDL_GetMouseState(posMouseX,posMouseY); // A GERER : INTERFACE DE REDEFINITION DES CONTROLES
			}
			break;
			
		case SDL_MOUSEMOTION:
			*selection=-1; //reset
			if((*display==1)){
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1; //reset
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*selection=1; //play
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=96*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					*selection=2; //options
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					*selection=3; //quit
				}
			}
			if((*display==3)){
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1; //reset
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					*selection=1; //agrandir ecran
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					*selection=2; //reduire ecran
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=80*SCREEN_HEIGHT/100)&&(*posMouseY<=85*SCREEN_HEIGHT/100)){
					*selection=3; //controles
				}
				if((*posMouseX>=60*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
			}
			if((*display==4)){
				SDL_GetMouseState(posMouseX,posMouseY);
				//Gestion des controles poussée
			}
			break;
				
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

	float puissance(float x, int n)
	{
	  if(n==0)
	  {
	    return 1;
	  }
	  else
	  {
	    return x*puissance(x,n-1);
	  }
	}
	
	/*int Distance(struct sprite_t* a, struct sprite_t* b, int Dx){
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
	}*/
	
	int DistanceXY(struct sprite_t* a, struct sprite_t* b){
	  if((a->display==1)&&(b->display==1)){ 
	    float diffX, diffY, res;
	    diffX = fabs((b->pos.x+b->size)-(a->pos.x+a->size));
	    diffY = fabs((b->pos.y+b->size)-(a->pos.y+a->size));
	    res = sqrt(puissance(diffX,2)+puissance(diffY,2));
	    return res;
	  }
	  return 10;
	}
	
	//Limiter fps
	void cap_fps (Uint32 starting_tick){
		if ( (1000/fps) > SDL_GetTicks() - starting_tick ) {
			SDL_Delay ( 1000 / fps - ( SDL_GetTicks() - starting_tick ) );
		}
	}

int main(int argc, char* argv[]){

	
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
	TTF_Init();

    /* set the title bar */
    SDL_WM_SetCaption("Ashortsomething", "Ashortsomething");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);
	
	int gameover =1;
	int display=1; // 1 menu 2 jeu 3 config 4 controles 5 menu de pause
	
	//Les surfaces du menu
	SDL_Surface *background; 
	SDL_Surface *message;
	SDL_Surface *fleche;
	int selection=-1;
	SDL_Rect posMes;
	SDL_Rect posFleche;

	//Les Fonts qu'on va utiliser pour le menu
	TTF_Font *font50; 
	TTF_Font *font36;
	TTF_Font *fontCTRL;
	
	//La couleur du Font 
	SDL_Color textColor = { 255, 255, 255 };
	
	font50 = TTF_OpenFont( "ALoveOfThunder.ttf", 50); //Taille Gros titres
	if(!font50){
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return 2;
		}
	font36 = TTF_OpenFont( "ALoveOfThunder.ttf", 36); //Taille de toutes les lignes de menu hors gros titres
	if(!font36){
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	return 2;
	}
	fontCTRL = TTF_OpenFont( "ALoveOfThunder.ttf", 16); //taille du menu de controle uniquement
	if(!fontCTRL){
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	return 2;
	}
	
    /* load sprite */
	{
		temp = SDL_LoadBMP("sprite.bmp");
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
		
		temp = SDL_LoadBMP("background.bmp");
		background = SDL_DisplayFormat(temp);
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


	//Positions souris
	int posMouseX=0;
	int posMouseY=0;
	
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

	/*Initialise framerate */
	Uint32 starting_tick;
	


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
			barreDeMana_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);


		}
		
	/* main loop: check events and re-draw the window until the end */
	while (gameover)
	{
		printf("");
		int disp=display;
		SDL_Event event;
		/* look for an event; possibly update the position and the shape
		 * of the sprite. */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event, &gameover, &currentDirection, &animationFlip, &perso, &ludo, &fireball, &poisonball, &deathball, &HP_potion,&display,&posMouseX,&posMouseY,&selection);
		}
		
		//fps
		starting_tick = SDL_GetTicks();
		
		//Barre de vie ludo
		
		//FillRect d'un SDLRect avec règle de trois basique
		if(disp==2){
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
			
			//Bare de mana personnage
			SDL_FillRect(barreDeMana_perso, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //fond noir
			SDL_Rect MANA_perso;
			MANA_perso.x = 0;
			MANA_perso.y = 0;
			MANA_perso.w = perso.life*perso.size/MAX_MANA;
			MANA_perso.h = 3;
			SDL_FillRect(barreDeMana_perso, &MANA_perso, SDL_MapRGB(barreDeMana_perso->format, 148, 0, 211));
		}
		
		/*position*/
		if(disp==2){
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
		}
		/* Déplacement du monstre */


		/*Gestion aléatoire entre -2 et 4 */
		if(disp==2){
			srand(time(NULL));
			int a = rand()%5;		
			switch(a){
				case(0):
					break;
				case(1):
					monster.pos.x = monster.pos.x + VITESSE_MOB;
					break;
				case(2):
					monster.pos.x = monster.pos.x -VITESSE_MOB;
					break;
				case(3):
					monster.pos.y = monster.pos.y +VITESSE_MOB;
					break;
				case(4):
					monster.pos.y = monster.pos.y -VITESSE_MOB;
					break;
				default :
					break;
			}
		}
			

				//monster.pos.x = monster.pos.x + deathball.v.x; //Contrôle du monstre avec la deathball
				//monster.pos.y = monster.pos.y + deathball.v.y;
				/* // Le monstre tourne en rond
				double angle2 = (rand()%90);
				ludo.display = 1;
				ludo.pos.x += 2 * cos(angle2);
				ludo.pos.y += 2*sin(angle2);*/
				
				
			//IA Aggressive
		if(disp==2){
			if (choice ==1){
				if(perso.pos.x>ludo.pos.x){
					ludo.pos.x+=2;
				} 
				if(perso.pos.x<ludo.pos.x){
					ludo.pos.x-=2;
				} 
				if(perso.pos.y > ludo.pos.y){
					ludo.pos.y+=2;	
				}
				if(perso.pos.y < ludo.pos.y){
					ludo.pos.y-=2;	
				}
			}
			
				//IA Fuyarde 
			if(choice == 0){
			    if(DistanceXY(&perso,&ludo)<=100){
				if(perso.pos.x<ludo.pos.x){
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
				}
			    } else if(DistanceXY(&perso,&ludo)>180){
			      	if(perso.pos.x>ludo.pos.x){
					ludo.pos.x+=2;
				} 
				if(perso.pos.x<ludo.pos.x){
					ludo.pos.x-=2;
				} 
				if(perso.pos.y > ludo.pos.y){
					ludo.pos.y+=2;	
				}
				if(perso.pos.y < ludo.pos.y){
					ludo.pos.y-=2;	
				}
			      
			    }
			}
		}


		/*hyperspace*/
		if(disp==2){
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
				ludo.pos.x = SCREEN_WIDTH ;
			}
			if (ludo.pos.x > SCREEN_WIDTH + perso.size) {
				ludo.pos.x = perso.size ;
			}
			if (ludo.pos.y < 0){
				ludo.pos.y = SCREEN_HEIGHT ;
			}
			if (ludo.pos.y > SCREEN_HEIGHT) {
				ludo.pos.y = perso.size;
			}
		}

		/*check and refresh ball life */
		if(disp==2){
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
		if((disp==1)||(disp==3)){
			SDL_BlitSurface(background,NULL,screen,NULL);
		}
		if(disp==2){
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
		if(disp==2){ // si le jeu est en route
			if (perso.display != 0) {
				SDL_Rect spriteImage;
				SDL_Rect spritePos;
				SDL_Rect manaPos;
				manaPos.x = perso.pos.x;
				manaPos.y = perso.pos.y - 3;
				spritePos.x = perso.pos.x;
				spritePos.y = perso.pos.y;
				spriteImage.y = 0;
				spriteImage.w = perso.size;
				spriteImage.h = perso.size;
				spriteImage.x = perso.size*(perso.currDirection*2);
				SDL_BlitSurface(sprite, &spriteImage, screen, &spritePos);
				SDL_BlitSurface(barreDeVie_perso, NULL, screen, &manaPos);
				SDL_BlitSurface(barreDeMana_perso, NULL, screen, &spritePos);



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
			//Collisions si le jeu tourne
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
			
			if(Collision(&HP_potion,&ludo)&&HP_potion.display!=0&&ludo.life<MAX_HP){
				HP_potion.display=0;
				if(ludo.life+50<MAX_HP){ //Debug des pvs superieur au max en cas de potion ramassee
					ludo.life +=50;
				}else{
					ludo.life=MAX_HP;
				}
				printf("Vie de ludo : %d \n", ludo.life);
			}
		}
		/* update the screen */
		if(disp==1){
			message = TTF_RenderText_Solid(font50,"Welcome to AShortSomething !",textColor);
			posMes.x=50*SCREEN_WIDTH/100-400;
			posMes.y=0.0;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Play",textColor);
			posMes.x=80*SCREEN_WIDTH/100;
			posMes.y=20*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Options",textColor);
			posMes.x=80*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Quit",textColor);
			posMes.x=80*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			if(selection!=-1){
				fleche = TTF_RenderText_Solid(font50,">>>",textColor);
				posFleche.x=65*SCREEN_WIDTH/100;
				posFleche.y=((20*SCREEN_HEIGHT/100)*selection)-(2*SCREEN_HEIGHT/100);
				SDL_BlitSurface(fleche,NULL,screen,&posFleche);
			}
		}
		if(disp==3){
			message = TTF_RenderText_Solid(font50,"OPTIONS :",textColor);
			posMes.x=50*SCREEN_WIDTH/100-100;
			posMes.y=0.0;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Agrandir la taille de l'ecran",textColor);
			posMes.x=5*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Reduire la taille de l'ecran",textColor);
			posMes.x=5*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Changer les controles",textColor);
			posMes.x=5*SCREEN_WIDTH/100;
			posMes.y=80*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Retour",textColor);
			posMes.x=60*SCREEN_WIDTH/100;
			posMes.y=20*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			if(selection!=-1){
				fleche = TTF_RenderText_Solid(font50,"<<<",textColor);
				posFleche.x=65*SCREEN_WIDTH/100;
				posFleche.y=((20*SCREEN_HEIGHT/100)*(selection+1))-(2*SCREEN_HEIGHT/100);
				if(selection==0){
					posFleche.x=80*SCREEN_WIDTH/100;
				}
				SDL_BlitSurface(fleche,NULL,screen,&posFleche);
			}
		}
		if(disp==4){
			//Creation des boutons du menu de controles
		}
        SDL_UpdateRect(screen,0,0,0,0);
		
		cap_fps(starting_tick);
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
		SDL_FreeSurface(background);
		SDL_FreeSurface(screen);
		SDL_FreeSurface(message);
		SDL_FreeSurface(fleche);
		SDL_Quit();

		return 0;
}
