 //champs du programme
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include "game.h"

#define GRASS_SIZE 32
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3
#define COLIDE			4/3
#define MAX_HP    		100
#define MAX_MANA    	100
#define SPRITE_STEP     5
#define VITESSE_MOB 	2
#define BALL_SPEED		6

SDL_Surface *screen, *sprite, *grass, *spritefire, *spritemonster, *spritedeath, *spritepoison, *spriteludo, *spritepotion, *spritechampignon; //sprites ingame
SDL_Surface *barreDeVie_Ludo, *barreDeVie_monstre, *barreDeVie_perso, *barreDeMana_perso; //barres
SDL_Surface *background, *message, *fleche; //menu
SDL_Surface *messageQ1; //quetes
SDL_Rect posMes;
SDL_Rect posFleche;
SDL_Rect posMesQ1;
SDL_Color textColor = { 255, 255, 255 };
TTF_Font *font50;
TTF_Font *font36;
TTF_Font *fontCTRL;
TTF_Font *fontQ1;

int currentDirection = DIR_RIGHT;
int animationFlip = 0;
int gameover;
int display;
int selection;
double ratio;
int posMouseX;
int posMouseY;
int choice = 0;
int choiceTEST = 0;
int SCREEN_WIDTH=1024;
int SCREEN_HEIGHT=768;
int resolutions[4][2];
int actualRes=2;
int resChange=0;
int quest = 0;
int questTEST = 0;
int quest1[5][2][2];
int QTchampignon = 0;
int deplacements[4];

struct vector vit = {0,0};
struct sprite_t perso;
struct sprite_t monster;
struct sprite_t ludo;
struct bdf_t fireball;
struct sprite_t poisonball;
struct sprite_t deathball;
struct sprite_t HP_potion;
struct sprite_t champignon;

SDLKey bdf_touche = SDLK_SPACE;
SDLKey haut_touche = SDLK_UP;
SDLKey bas_touche = SDLK_DOWN;
SDLKey gauche_touche = SDLK_LEFT;
SDLKey droite_touche = SDLK_RIGHT;
SDLKey quitter_touche = SDLK_q;
SDLKey bdp_touche = SDLK_F1;
SDLKey bdm_touche = SDLK_F2;
SDLKey pnj_touche = SDLK_F3;
SDLKey IA_touche = SDLK_F4;
SDLKey Oui_touche = SDLK_o;
SDLKey Non_touche = SDLK_n;

void HandleEvent(SDL_Event event, int *gameover, int *currDirection, struct sprite_t *perso, struct sprite_t *ludo,
 struct bdf_t *fireball, struct sprite_t *poisonball, struct sprite_t *deathball, struct sprite_t *HP_potion,struct sprite_t *champignon, int *display, int *posMouseX, int *posMouseY, int *selection)
{
	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			*gameover = 1;
			break;

		/* handle the keyboard */
		
		case SDL_KEYDOWN:
			if((event.key.keysym.sym==SDLK_ESCAPE)||(event.key.keysym.sym==quitter_touche)){   // retour au menu
				*display =1 ;
			}
			if(event.key.keysym.sym==gauche_touche){
				perso->currDirection = DIR_LEFT;
				deplacements[0]=1;
			}
			if(event.key.keysym.sym==droite_touche){
				perso->currDirection = DIR_RIGHT;
				deplacements[1]=1;
			}
			if(event.key.keysym.sym==haut_touche){
				perso->currDirection = DIR_UP;
				deplacements[2]=1;
			}
			if(event.key.keysym.sym==bas_touche){
				perso->currDirection = DIR_DOWN;
				deplacements[3]=1;
			}				
			if(event.key.keysym.sym==bdf_touche){
				if (fireball->display==0) {
					fireball->display=1;
					fireball->range=7*BALL_SPEED;
					fireball->pos.x = perso->pos.x+(GRASS_SIZE/3);
					fireball->pos.y = perso->pos.y+(GRASS_SIZE/3);
					if(perso->currDirection == DIR_RIGHT){
						double angle = (perso->currDirection * (2*M_PI));
						fireball->v.x = BALL_SPEED*cos(angle);
						fireball->v.y = -BALL_SPEED * sin(angle);
					}
					if(perso->currDirection == DIR_LEFT){
						double angle = (perso->currDirection * (2*M_PI));
						fireball->v.x = -BALL_SPEED*cos(angle);
						fireball->v.y = BALL_SPEED * sin(angle);
					}
					if(perso->currDirection == DIR_UP){
						double angle = (perso->currDirection * (2*M_PI));
						fireball->v.x = BALL_SPEED * sin(angle);
						fireball->v.y = -BALL_SPEED*cos(angle);
					}
					if(perso->currDirection == DIR_DOWN){
						double angle = (perso->currDirection * (2*M_PI));
						fireball->v.x = -BALL_SPEED * sin(angle);
						fireball->v.y = BALL_SPEED*cos(angle);
					}
				}
			}
			if(event.key.keysym.sym==bdp_touche){
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
			}
			if(event.key.keysym.sym==bdm_touche){
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
			}
			if(event.key.keysym.sym==pnj_touche){
				/* Apparition PNJ Ludo */
				ludo->life= 100;
				ludo->display = 1;
				ludo->pos.x = 200;
				ludo->pos.y = 200;
			}	
			if(event.key.keysym.sym==IA_touche){
				if(choiceTEST){
					choice = 1;
					choiceTEST= 0;
				} else {
					choice = 0;
					choiceTEST = 1;
				}
			}
			if(event.key.keysym.sym==Oui_touche){
				quest1[0][0][0] += 1;
			}
			if(event.key.keysym.sym==Non_touche){
				quest1[0][1][0] += 1;
			}
			break;
		case SDL_KEYUP:
			if(event.key.keysym.sym==gauche_touche){
				deplacements[0]=0;
			}
			if(event.key.keysym.sym==droite_touche){
				deplacements[1]=0;
			}
			if(event.key.keysym.sym==haut_touche){
				deplacements[2]=0;
			}
			if(event.key.keysym.sym==bas_touche){
				deplacements[3]=0;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if((*display==1)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					//Lancement du jeu
					*display=2;
					*selection=-1; //reset
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=96*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					//Lancement des options
					*display=3;
					*selection=-1; //reset
				}
				if((*posMouseX>=78*SCREEN_WIDTH/100)&&(*posMouseX<=90*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					//fermeture du jeu
					*gameover=0;
					*selection=-1; //reset
				}
			}
			if((*display==3)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=40*SCREEN_HEIGHT/100)&&(*posMouseY<=45*SCREEN_HEIGHT/100)){
					if(actualRes<3){
						actualRes++;	//agrandir ecran
						SCREEN_HEIGHT=resolutions[actualRes][0];
						SCREEN_WIDTH=resolutions[actualRes][1];
						resChange=1;
					}else{
						//POP UP ECRAN AGRANDI AU MAX
					}
					*selection=-1; //reset
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=60*SCREEN_HEIGHT/100)&&(*posMouseY<=65*SCREEN_HEIGHT/100)){
					if(actualRes>0){
						actualRes--; //reduire ecran
						SCREEN_HEIGHT=resolutions[actualRes][0];
						SCREEN_WIDTH=resolutions[actualRes][1];
						resChange=1;
					}
					else{
						//POP UP ECRAN REDUIT AU MAX
					}
					*selection=-1; //reset
				}
				if((*posMouseX>=5*SCREEN_WIDTH/100)&&(*posMouseX<=60*SCREEN_WIDTH/100)&&(*posMouseY>=80*SCREEN_HEIGHT/100)&&(*posMouseY<=85*SCREEN_HEIGHT/100)){
					printf("AJOUTER GESTION DES CONTROLES"); //controles
					*display=4; //menu de controles
					*selection=-1; //reset
				}
				if((*posMouseX>=60*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*display=1; //retour menu
					*selection=-1; //reset
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
				*selection=-1; //reset
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

float puissance(float x, int n){
	  if(n==0)
	  {
	    return 1;
	  }
	  else
	  {
	    return x*puissance(x,n-1);
	  }
	}
	
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
	
void initAll(){
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		SDL_WM_SetCaption("Ashortsomething", "Ashortsomething");
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
		currentDirection = DIR_RIGHT;
		/* set keyboard repeat */
		SDL_EnableKeyRepeat(10, 10);
		gameover =1;
		display=1; // 1 menu 2 jeu 3 config 4 controles 5 menu de pause
		//Les surfaces du menu
		selection=-1;
		resolutions[0][1]=640;
		resolutions[0][0]=480;
		resolutions[1][1]=800;
		resolutions[1][0]=600;
		resolutions[2][1]=1024;
		resolutions[2][0]=768;
		resolutions[3][1]=1280;
		resolutions[3][0]=960;
		//La couleur du Font 
		ratio = 1024.0/SCREEN_HEIGHT;
		font50 = TTF_OpenFont( "ALoveOfThunder.ttf", 50/ratio); //Taille Gros titres 50 = 1024 768  800 600   1024/800    768/600
		font36 = TTF_OpenFont( "ALoveOfThunder.ttf", 36/ratio); //Taille de toutes les lignes de menu hors gros titres 36 = 1024 768
		fontCTRL = TTF_OpenFont( "ALoveOfThunder.ttf", 16/ratio); //taille du menu de controle uniquement 16 = 1024 768
		fontQ1 = TTF_OpenFont( "ALoveOfThunder.ttf", 20/ratio);
		/* load sprite */
		SDL_Surface *temp = SDL_LoadBMP("sprite.bmp");
		sprite = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		temp = SDL_LoadBMP("monster.bmp");
		spritemonster = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);	
		temp = SDL_LoadBMP("champignon.bmp");
		spritechampignon = SDL_DisplayFormat(temp);
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
		temp = SDL_LoadBMP("grass.bmp");
		grass = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spriteludo, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritemonster, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepoison, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritedeath, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepotion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritechampignon, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
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
		//Position champignon
		champignon.display = 1;
		champignon.size = 32;
		champignon.pos.x = 400;
		champignon.pos.y = 400;
		
		perso.pos.x = (SCREEN_WIDTH - perso.size)/2;
		perso.pos.y = (SCREEN_HEIGHT - perso.size)/2;
		monster.pos.x =0;
		monster.pos.y =0;
		HP_potion.pos.x=500;
		HP_potion.pos.y=400;
		//Initialisation barre de vie
		barreDeVie_Ludo = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeVie_monstre = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeVie_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeMana_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
}

void resetAll(){
		SDL_FreeSurface(screen);
		SDL_FreeSurface(sprite);
		SDL_FreeSurface(grass);
		SDL_FreeSurface(spritefire);
		SDL_FreeSurface(spritemonster);
		SDL_FreeSurface(spritedeath);
		SDL_FreeSurface(spritepoison);
		SDL_FreeSurface(spriteludo);
		SDL_FreeSurface(spritepotion);
		SDL_FreeSurface(spritechampignon);
		SDL_FreeSurface(barreDeVie_Ludo);
		SDL_FreeSurface(barreDeVie_monstre);
		SDL_FreeSurface(barreDeVie_perso);
		SDL_FreeSurface(barreDeMana_perso);
		SDL_FreeSurface(background);
		SDL_FreeSurface(message);
		SDL_FreeSurface(fleche);
		SDL_FreeSurface(messageQ1);
		TTF_CloseFont(font50); 
		TTF_CloseFont(font36); 
		TTF_CloseFont(fontCTRL); 
		TTF_CloseFont(fontQ1); 
		TTF_Quit();
		SDL_Quit();
	}

int main(int argc, char* argv[]){
	initAll(); //initialise tout
	while (gameover) // Boucle principale dexecution
	{
		if(resChange==1){ //si agrandissement / reduction ecran reboot laffichage
			resetAll();
			initAll();
			resChange=0;
			SDL_UpdateRect(screen,0,0,0,0);
		}
		int disp=display;
		SDL_Event event;
		if (SDL_PollEvent(&event)) { //Si entrée clavier ou souris il lance la fonction reliée
			HandleEvent(event, &gameover, &currentDirection, &perso, &ludo, &fireball, &poisonball, &deathball, &HP_potion, &champignon, &display,&posMouseX,&posMouseY,&selection);
		}
		//gestion du deplacement
		if(deplacements[0]==1){
			perso.pos.x -= SPRITE_STEP;
		}
		if(deplacements[1]==1){
			perso.pos.x += SPRITE_STEP;
		}
		if(deplacements[2]==1){
			perso.pos.y -= SPRITE_STEP;
		}
		if(deplacements[3]==1){
			perso.pos.y += SPRITE_STEP;
		}
		
		if(disp==2||disp==5){
			//Barre de vie Ludo
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
		if(disp==2){ //Gestion des evenements dus aux deplacements collisions actualisations etc
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

				//monster.pos.x = monster.pos.x + deathball.v.x; //Contrôle du monstre avec la deathball
				//monster.pos.y = monster.pos.y + deathball.v.y;
				/* // Le monstre tourne en rond
				double angle2 = (rand()%90);
				ludo.display = 1;
				ludo.pos.x += 2 * cos(angle2);
				ludo.pos.y += 2*sin(angle2);*/
				
				
			//IA Aggressive
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
		/*hyperspace*/
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
		/*check and refresh ball life */
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
			//Gestion du champignon
			if(Collision(&champignon, &perso)&&((champignon.display!=0)||(champignon.life!=0))){ 
				champignon.display = 0;
				QTchampignon +=1;
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
			}
		}
		if((disp==1)||(disp==3)||(disp==4)){ //Affiche un ecran noir pour cacher le jeu (et donc ne pas le cacher dans les autres display)
			SDL_BlitSurface(background,NULL,screen,NULL);
		}
		if(disp==1){ // si on est dans le menu
			message = TTF_RenderText_Solid(font50,"Welcome to AShortSomething !",textColor);
			posMes.x=50*SCREEN_WIDTH/100-(400/ratio);
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
		if(disp==2 ||disp==5){ // si le jeu est en route
			for(int x =0; x< SCREEN_WIDTH/GRASS_SIZE; x++){  //dessine le fond du jeu
				for(int y =0; y< SCREEN_HEIGHT/GRASS_SIZE; y++){				
					SDL_Rect position;
					position.x = x * GRASS_SIZE;
					position.y = y * GRASS_SIZE;
					SDL_BlitSurface(grass, NULL, screen, &position);
				}
			}
			if (perso.display != 0) { //affiche perso
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
				//Message quest
				//Compteur de temps pour les quêtes
				posMesQ1.x = 10*SCREEN_WIDTH/100;
				posMesQ1.y = 90*SCREEN_HEIGHT/100;
			}
			if(DistanceXY(&HP_potion,&perso)<50){ //affichage d'une quete
				if(quest1[0][0][0]==0){
					messageQ1 = TTF_RenderText_Solid(fontQ1, "Va me chercher des champignons O:Accepter la quete N:Quitter",textColor); //O pour accepter, N pour refuser
				}
				if(quest1[0][0][0]>0){
					messageQ1 = TTF_RenderText_Solid(fontQ1, "Merci d'avoir accepter la quete... J'attends mes champignons", textColor); //Si acceptation quête
					if(QTchampignon==1){ //Si on a été cueillir le champignon
						messageQ1 = TTF_RenderText_Solid(fontQ1, "Quete termine", textColor); //Ecriture quête terminé
						//RECOMPENSE DE QUETE ICI
						perso.argent = perso.argent + 5;
						Uint32 compteurA = SDL_GetTicks();
						Uint32 compteurB = SDL_GetTicks() + 2000;
						if(compteurA-compteurB<=0){
							quest1[0][0][0] = 0;
						}
					}
				}
				if(quest1[0][1][0]>0){
					messageQ1 = TTF_RenderText_Solid(fontQ1, "Tu veux pas ma quete? :(", textColor); //Si refus de la quête(press n)
					quest1[0][1][0]=0;
				}
			} else {
				messageQ1 = TTF_RenderText_Solid(fontQ1, "",textColor); //Message vide
			}
			SDL_BlitSurface(messageQ1, NULL, screen, &posMesQ1); //Affichage message
			if (monster.display != 0) { //affichage monstre
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
			
			if (ludo.display != 0) { //affichage ludo
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
			
			if(champignon.display != 0){ //affichage champi
				SDL_Rect champignonImage;
				SDL_Rect champignonPos;
				champignonPos.x = champignon.pos.x;
				champignonPos.y = champignon.pos.y;
								
				champignonImage.y = 0;
				champignonImage.w = champignon.size;
				champignonImage.h = champignon.size;
				champignonImage.x = ludo.size*(ludo.currDirection*2);
				SDL_BlitSurface(spritechampignon, &champignonImage, screen, &champignonPos);
			}

			if (fireball.display != 0) { //affichage bdf
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

			if (poisonball.display != 0) { //afficahge bdp
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

			if (deathball.display != 0) { //affichage bdm
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
				
			if (HP_potion.display != 0) { //affichage popo
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
			
		}
		if(disp==3){ // si on est dans les options
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
		if(disp==4){ // si on est dans les controles
			FILE* ctrls=fopen("CONTROLS.txt", "r+");
			
			//Creation des boutons du menu de controles
			
			//touches directionnelles
			//boule de feu
			//attaque
			//pause
			//boule de poison
			//boule de mort
			
		}
        SDL_UpdateRect(screen,0,0,0,0);
		SDL_Delay(12);
	}
	resetAll(); //casse tout avant de finir le programme
	return 0;
}
