 //champs du programme
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "game.h"

#define GRASS_SIZE 32
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3
#define COLIDE		4/3
#define MAX_HP    	100
#define MAX_MANA    	1000
#define SPRITE_STEP     5
#define VITESSE_MOB 	2
#define BALL_SPEED		6

SDL_Surface *screen, *sprite, *grass, *spritefire, *spritemonster, *spritedeath, *spritepoison, *spriteludo, *spritepotion, *spritechampignon, *spritepnj, *spriteepee; //sprites ingame
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
int lastDir = DIR_RIGHT;
int animationFlip = 0;
int gameover;
int display;
int selection;
double ratio;
double angle;
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
int bdfdeplacements[4];
int continuer = 0;
int tete = 0;
int bdf;
int monstre = 0;
int tete_stickman = 0;
int z = 0;

struct vector vit = {0,0};
struct sprite_t perso;
struct sprite_t monster;
struct sprite_t ludo;
struct bdf_t fireball;
struct sprite_t poisonball;
struct sprite_t deathball;
struct sprite_t HP_potion;
struct sprite_t champignon;
struct sprite_t pnj;
struct sprite_t epee;

SDLKey haut_touche = SDLK_UP;
SDLKey bas_touche = SDLK_DOWN;
SDLKey gauche_touche = SDLK_LEFT;
SDLKey droite_touche = SDLK_RIGHT;
SDLKey bdf_touche = SDLK_SPACE;
SDLKey epee_touche = SDLK_e;
SDLKey Continuer_touche = SDLK_c;
SDLKey Oui_touche = SDLK_o;
SDLKey Non_touche = SDLK_n;
SDLKey bdp_touche = SDLK_F1;
SDLKey bdm_touche = SDLK_F2;
SDLKey quitter_touche = SDLK_q;
SDLKey pnj_touche = SDLK_F3;//NON UTILE AU JOUEUR
SDLKey IA_touche = SDLK_F4;
/*
//SDL_mixer
Mix_Music *music; //Création du pointeur de type Mix_Music
music = Mix_LoadMUS("Bruh.wav"); // Chargement de la musique

if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
{
   printf("%s", Mix_GetError());
}*/





void HandleEvent(SDL_Event event, int *gameover, int *currDirection, struct sprite_t *perso, struct sprite_t *ludo, struct sprite_t *epee,
 struct bdf_t *fireball, struct sprite_t *poisonball, struct sprite_t *deathball, struct sprite_t *HP_potion,struct sprite_t *champignon, struct sprite_t *pnj,
 int *display, int *posMouseX, int *posMouseY, int *selection)

{
	switch (event.type){
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
				currentDirection= DIR_LEFT;
			}
			if(event.key.keysym.sym==droite_touche){
				perso->currDirection = DIR_RIGHT;
				deplacements[1]=1;
				currentDirection= DIR_RIGHT;
			}
			if(event.key.keysym.sym==haut_touche){
				perso->currDirection = DIR_UP;
				deplacements[2]=1;
				currentDirection= DIR_UP;
			}
			if(event.key.keysym.sym==bas_touche){
				perso->currDirection = DIR_DOWN;
				deplacements[3]=1;
				currentDirection= DIR_DOWN;
			}				
			if(event.key.keysym.sym==bdf_touche&&bdf&&perso->mana>100){
				if (fireball->display==0) {
				      	perso->mana = perso->mana-100;
					fireball->display=1;
					fireball->range=7*BALL_SPEED;
					fireball->pos.x = perso->pos.x+(GRASS_SIZE/3);
					fireball->pos.y = perso->pos.y+(GRASS_SIZE/3);
					bdfdeplacements[0]=deplacements[0];
					bdfdeplacements[1]=deplacements[1];
					bdfdeplacements[2]=deplacements[2];
					bdfdeplacements[3]=deplacements[3];
					 if((bdfdeplacements[0]==1)&&(bdfdeplacements[2]==1)){ //gauche + haut
					    angle = 3*M_PI/4;
					    fireball->v.x = BALL_SPEED*cos(angle);
					    fireball->v.y = -BALL_SPEED * sin(angle);
		    
					}else if((bdfdeplacements[0]==1)&&(bdfdeplacements[3]==1)){ //gauche + bas
					    angle = 5*M_PI/4;
					    fireball->v.x = 2*BALL_SPEED*cos(angle);
					    fireball->v.y = -2*BALL_SPEED * sin(angle);
		    
					}else if((bdfdeplacements[1]==1)&&(bdfdeplacements[2]==1)){ //droite + haut
					    angle = M_PI/4;
					    fireball->v.x = 2*BALL_SPEED*cos(angle);
					    fireball->v.y = -2*BALL_SPEED * sin(angle);
		    
					}else if((bdfdeplacements[1]==1)&&(bdfdeplacements[3]==1)){ //droite + bas
					    angle = 7*M_PI/4;
					    fireball->v.x = 2*BALL_SPEED*cos(angle);
					    fireball->v.y = -2*BALL_SPEED * sin(angle);
					}else if((bdfdeplacements[0]==1)&&(bdfdeplacements[1]!=1)){ //gauche
						angle = (currentDirection * (2*M_PI));
						fireball->v.x = -2*BALL_SPEED*cos(angle);
						fireball->v.y = 2*BALL_SPEED * sin(angle);
					}else if((bdfdeplacements[1]==1)&&(bdfdeplacements[0]!=1)){ //droite
						angle = (currentDirection * (2*M_PI));
						fireball->v.x = 2*BALL_SPEED*cos(angle);
						fireball->v.y = -2*BALL_SPEED * sin(angle);
					}else if((bdfdeplacements[2]==1)&&(bdfdeplacements[3]!=1)){ //haut
						angle = (currentDirection * (2*M_PI));
						fireball->v.x = 2*BALL_SPEED * sin(angle);
						fireball->v.y = -2*BALL_SPEED*cos(angle);
					}else if((bdfdeplacements[3]==1)&&(bdfdeplacements[2]!=1)){ //bas
						angle = (currentDirection * (2*M_PI));
						fireball->v.x = -2*BALL_SPEED * sin(angle);
						fireball->v.y = 2*BALL_SPEED*cos(angle);
					}else if((bdfdeplacements[0]==0)&&(bdfdeplacements[1]==0)&&(bdfdeplacements[2]==0)&&(bdfdeplacements[3]==0)){
						switch(currentDirection){
							case 0 :
								angle = (currentDirection * (2*M_PI));
								fireball->v.x = BALL_SPEED * sin(angle);
								fireball->v.y = -BALL_SPEED*cos(angle);
								break;
							case 1 :
								angle = (currentDirection * (2*M_PI));
								fireball->v.x = BALL_SPEED*cos(angle);
								fireball->v.y = -BALL_SPEED * sin(angle);
								break;
							case 2 :
								angle = (currentDirection * (2*M_PI));
								fireball->v.x = -BALL_SPEED * sin(angle);
								fireball->v.y = BALL_SPEED*cos(angle);
								break;
							case 3 :
								angle = (currentDirection * (2*M_PI));
								fireball->v.x = -BALL_SPEED*cos(angle);
								fireball->v.y = BALL_SPEED * sin(angle);
								break;
							break;
						}
						break;
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
			if(event.key.keysym.sym==Oui_touche){
				quest1[0][0][0] += 1;
			}
			if(event.key.keysym.sym==Non_touche){
				quest1[0][1][0] += 1;
			}
			if(event.key.keysym.sym==Continuer_touche){
			  //CONDITIONS POUR LES QUETES
			  if(continuer==0&&QTchampignon>5){
			    continuer=1;
			  } else {
			    if(continuer==1){
			      continuer = 2;
			    } else {
			      if(continuer==2&&bdf==1){
				continuer=3;
			      } else {
				if(continuer==3&&tete==1){
				  continuer=4;
				} else {
				  if(continuer==4&&perso->life>=100){
				    continuer =5; 
				  } else {
				    if(continuer==5&&tete_stickman==1){
				      continuer = 6; 
				    } else {
				    if(continuer==6&&monstre==1){
				      continuer = 7;
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
			
		if(event.key.keysym.sym==epee_touche){
		  if(z==0){
		    z = 1;
		  } else {
		    z = 0;
		  }
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
					//controles
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
				if((*posMouseX>=60*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*display=1; //retour menu
					*selection=-1; //reset
				}
				if((*posMouseX>=10*SCREEN_WIDTH/100)&&(*posMouseX<=20*SCREEN_WIDTH/100)&&(*posMouseY>=45*SCREEN_HEIGHT/100)&&(*posMouseY<=50*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					haut_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=25*SCREEN_WIDTH/100)&&(*posMouseX<=35*SCREEN_WIDTH/100)&&(*posMouseY>=45*SCREEN_HEIGHT/100)&&(*posMouseY<=50*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					bas_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=40*SCREEN_WIDTH/100)&&(*posMouseX<=50*SCREEN_WIDTH/100)&&(*posMouseY>=45*SCREEN_HEIGHT/100)&&(*posMouseY<=50*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					gauche_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=55*SCREEN_WIDTH/100)&&(*posMouseX<=65*SCREEN_WIDTH/100)&&(*posMouseY>=45*SCREEN_HEIGHT/100)&&(*posMouseY<=50*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					droite_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=70*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=45*SCREEN_HEIGHT/100)&&(*posMouseY<=50*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					bdf_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=10*SCREEN_WIDTH/100)&&(*posMouseX<=20*SCREEN_WIDTH/100)&&(*posMouseY>=65*SCREEN_HEIGHT/100)&&(*posMouseY<=70*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					epee_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=25*SCREEN_WIDTH/100)&&(*posMouseX<=35*SCREEN_WIDTH/100)&&(*posMouseY>=65*SCREEN_HEIGHT/100)&&(*posMouseY<=70*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					quitter_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=40*SCREEN_WIDTH/100)&&(*posMouseX<=50*SCREEN_WIDTH/100)&&(*posMouseY>=65*SCREEN_HEIGHT/100)&&(*posMouseY<=70*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					bdp_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=55*SCREEN_WIDTH/100)&&(*posMouseX<=65*SCREEN_WIDTH/100)&&(*posMouseY>=65*SCREEN_HEIGHT/100)&&(*posMouseY<=70*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					bdm_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=10*SCREEN_WIDTH/100)&&(*posMouseX<=20*SCREEN_WIDTH/100)&&(*posMouseY>=85*SCREEN_HEIGHT/100)&&(*posMouseY<=90*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					Continuer_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=25*SCREEN_WIDTH/100)&&(*posMouseX<=35*SCREEN_WIDTH/100)&&(*posMouseY>=85*SCREEN_HEIGHT/100)&&(*posMouseY<=90*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					Oui_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=40*SCREEN_WIDTH/100)&&(*posMouseX<=50*SCREEN_WIDTH/100)&&(*posMouseY>=85*SCREEN_HEIGHT/100)&&(*posMouseY<=90*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					Non_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=70*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=65*SCREEN_HEIGHT/100)&&(*posMouseY<=70*SCREEN_HEIGHT/100)){
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					IA_touche=keychange.key.keysym.sym;
				}
				if((*posMouseX>=55*SCREEN_WIDTH/100)&&(*posMouseX<=65*SCREEN_WIDTH/100)&&(*posMouseY>=80*SCREEN_HEIGHT/100)&&(*posMouseY<=85*SCREEN_HEIGHT/100)){//SAUVEGARDE des touches
					FILE* ctrls=fopen("CONTROLS.txt", "w+");
					int lecture;
					if(ctrls!=NULL){
						lecture=0;
					}else{
						lecture=1;
						printf("IMPOSSIBLE DE LIRE DANS LE FICHIER");
					}
					if(lecture==0){
						fputs(SDL_GetKeyName(haut_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(bas_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(gauche_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(droite_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(bdf_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(epee_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(quitter_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(bdp_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(bdm_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(Continuer_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(Oui_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(Non_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(IA_touche),ctrls);
						lecture=1;
					}
					fclose(ctrls);
				}
				
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
				if((*posMouseX>=60*SCREEN_WIDTH/100)&&(*posMouseX<=80*SCREEN_WIDTH/100)&&(*posMouseY>=20*SCREEN_HEIGHT/100)&&(*posMouseY<=25*SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
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
	  return 0;
}

void aleaspawn(struct sprite_t* a){
	int nbalea1 = rand()%500;	
	int nbalea2 = rand()%500;
	a->display = 1;
	a->pos.x = nbalea2;
	a->pos.y = nbalea1;
	
}

SDLKey GetKeyFromName(char* name){
	SDLKey res=SDLK_UP;
	if(strcmp(name,"up")==0){
		res=SDLK_UP;
	}
	if(strcmp(name,"down")==0){
		res=SDLK_DOWN;
	}
	if(strcmp(name,"left")==0){
		res=SDLK_LEFT;
	}
	if(strcmp(name,"right")==0){
		res=SDLK_RIGHT;
	}
	if(strcmp(name,"f1")==0){
		res=SDLK_F1;
	}
	if(strcmp(name,"f2")==0){
		res=SDLK_F2;
	}
	if(strcmp(name,"f3")==0){
		res=SDLK_F3;
	}
	if(strcmp(name,"f4")==0){
		res=SDLK_F4;
	}
	if(strcmp(name,"f5")==0){
		res=SDLK_F5;
	}
	if(strcmp(name,"f6")==0){
		res=SDLK_F6;
	}
	if(strcmp(name,"f7")==0){
		res=SDLK_F7;
	}
	if(strcmp(name,"f8")==0){
		res=SDLK_F8;
	}
	if(strcmp(name,"f9")==0){
		res=SDLK_F9;
	}
	if(strcmp(name,"f10")==0){
		res=SDLK_F10;
	}
	if(strcmp(name,"f11")==0){
		res=SDLK_F11;
	}
	if(strcmp(name,"f12")==0){
		res=SDLK_F12;
	}
	if(strcmp(name,"0")==0){
		res=SDLK_0;
	}
	if(strcmp(name,"1")==0){
		res=SDLK_1;
	}
	if(strcmp(name,"2")==0){
		res=SDLK_2;
	}
	if(strcmp(name,"3")==0){
		res=SDLK_3;
	}
	if(strcmp(name,"4")==0){
		res=SDLK_4;
	}
	if(strcmp(name,"5")==0){
		res=SDLK_5;
	}
	if(strcmp(name,"6")==0){
		res=SDLK_6;
	}
	if(strcmp(name,"7")==0){
		res=SDLK_7;
	}
	if(strcmp(name,"8")==0){
		res=SDLK_8;
	}
	if(strcmp(name,"9")==0){
		res=SDLK_9;
	}
	if(strcmp(name,"insert")==0){
		res=SDLK_INSERT;
	}
	if(strcmp(name,"home")==0){
		res=SDLK_HOME;
	}
	if(strcmp(name,"end")==0){
		res=SDLK_END;
	}
	if(strcmp(name,"pageup")==0){
		res=SDLK_PAGEUP;
	}
	if(strcmp(name,"pagedown")==0){
		res=SDLK_PAGEDOWN;
	}
	if(strcmp(name,"delete")==0){
		res=SDLK_DELETE;
	}
	if(strcmp(name,"space")==0){
		res=SDLK_SPACE;
	}
	if(strcmp(name,"backspace")==0){
		res=SDLK_BACKSPACE;
	}
	if(strcmp(name,"tab")==0){
		res=SDLK_TAB;
	}
	if(strcmp(name,"clear")==0){
		res=SDLK_CLEAR;
	}
	if(strcmp(name,"return")==0){
		res=SDLK_RETURN;
	}
	if(strcmp(name,"pause")==0){
		res=SDLK_PAUSE;
	}
	if(strcmp(name,"a")==0){
		res=SDLK_a;
	}
	if(strcmp(name,"b")==0){
		res=SDLK_b;
	}
	if(strcmp(name,"c")==0){
		res=SDLK_c;
	}
	if(strcmp(name,"d")==0){
		res=SDLK_d;
	}
	if(strcmp(name,"e")==0){
		res=SDLK_e;
	}
	if(strcmp(name,"f")==0){
		res=SDLK_f;
	}
	if(strcmp(name,"g")==0){
		res=SDLK_g;
	}
	if(strcmp(name,"h")==0){
		res=SDLK_h;
	}
	if(strcmp(name,"i")==0){
		res=SDLK_i;
	}
	if(strcmp(name,"j")==0){
		res=SDLK_j;
	}
	if(strcmp(name,"k")==0){
		res=SDLK_k;
	}
	if(strcmp(name,"l")==0){
		res=SDLK_l;
	}
	if(strcmp(name,"m")==0){
		res=SDLK_m;
	}
	if(strcmp(name,"n")==0){
		res=SDLK_n;
	}
	if(strcmp(name,"o")==0){
		res=SDLK_o;
	}
	if(strcmp(name,"p")==0){
		res=SDLK_p;
	}
	if(strcmp(name,"q")==0){
		res=SDLK_q;
	}
	if(strcmp(name,"r")==0){
		res=SDLK_r;
	}
	if(strcmp(name,"s")==0){
		res=SDLK_s;
	}
	if(strcmp(name,"t")==0){
		res=SDLK_t;
	}
	if(strcmp(name,"u")==0){
		res=SDLK_u;
	}
	if(strcmp(name,"v")==0){
		res=SDLK_v;
	}
	if(strcmp(name,"w")==0){
		res=SDLK_w;
	}
	if(strcmp(name,"x")==0){
		res=SDLK_x;
	}
	if(strcmp(name,"y")==0){
		res=SDLK_y;
	}
	if(strcmp(name,"z")==0){
		res=SDLK_z;
	}
	return res;
}

void chargerTouches(){
	FILE* ctrls=NULL;
	ctrls=fopen("CONTROLS.txt", "r+"); //lecture seule pour charger les touches
	int lecture;
	if(ctrls!=NULL){
		lecture=0;
	}else{
		lecture=1;
		printf("IMPOSSIBLE DE LIRE DANS LE FICHIER");
	}
	if(lecture==0){
		char touche1[10];char touche2[10];char touche3[10];char touche4[10];char touche5[10];char touche6[10];char touche7[10];char touche8[10];char touche9[10];char touche10[10];char touche11[10];char touche12[10];char touche13[10];
		fscanf(ctrls,"%s %s %s %s %s %s %s %s %s %s %s %s %s",touche1,touche2,touche3,touche4,touche5,touche6,touche7,touche8,touche9,touche10,touche11,touche12,touche13);
		haut_touche=GetKeyFromName(touche1);
		bas_touche=GetKeyFromName(touche2);
		gauche_touche=GetKeyFromName(touche3);
		droite_touche=GetKeyFromName(touche4);
		bdf_touche=GetKeyFromName(touche5);
		epee_touche=GetKeyFromName(touche6);
		quitter_touche=GetKeyFromName(touche7);
		bdp_touche=GetKeyFromName(touche8);
		bdm_touche=GetKeyFromName(touche9);
		Continuer_touche=GetKeyFromName(touche10);
		Oui_touche=GetKeyFromName(touche11);
		Non_touche=GetKeyFromName(touche12);
		IA_touche=GetKeyFromName(touche13);
		lecture=1;
	}
	fclose(ctrls);
}

void initAll(){
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		SDL_WM_SetCaption("Ashortsomething", "Ashortsomething");
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
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
		fontQ1 = TTF_OpenFont( "ALoveOfThunder.ttf", 26/ratio);
		/* load sprite */
		SDL_Surface *temp = SDL_LoadBMP("sprite.bmp");
		sprite = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		temp = SDL_LoadBMP("epee.bmp");
		spriteepee = SDL_DisplayFormat(temp);
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
		temp = SDL_LoadBMP("pnj.bmp");
		spritepnj = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		
		
		int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spriteepee, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spriteludo, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritefire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritemonster, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepoison, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritedeath, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepotion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritechampignon, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		SDL_SetColorKey(spritepnj, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);


		/* initialise struct */
		monster.currDirection =0;
		perso.display = 1;
		perso.size = 32;
		perso.life = MAX_HP;
		perso.mana = MAX_MANA;
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
		pnj.display = 1;
		pnj.size = 32;
		pnj.pos.x = 500;
		pnj.pos.y = 500;
		
		//Position champignon
		champignon.display = 1;
		champignon.size = 32;
		champignon.pos.x = 400;
		champignon.pos.y = 400;
		
		perso.pos.x = (SCREEN_WIDTH - perso.size)/2;
		perso.pos.y = (SCREEN_HEIGHT - perso.size)/2;
		monster.pos.x =0;
		monster.pos.y =0;
		HP_potion.pos.x=550;
		HP_potion.pos.y=450;
		
		
		epee.display = 1;
		epee.size=32;
		epee.pos.x=perso.pos.x+10;
		epee.pos.y=perso.pos.y;
		
		
		//Initialisation barre de vie
		barreDeVie_Ludo = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeVie_monstre = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeVie_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);
		barreDeMana_perso = SDL_CreateRGBSurface(SDL_HWSURFACE, 31, 3, 32, 0, 0, 0, 0);

		chargerTouches();
}

void resetAll(){
		SDL_FreeSurface(screen);
		SDL_FreeSurface(sprite);
		SDL_FreeSurface(spriteepee);
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
		SDL_FreeSurface(spritepnj);
		//Mix_FreeMusic(effect1); //Libération de la musique
		//Mix_CloseAudio();
		TTF_CloseFont(font50); 
		TTF_CloseFont(font36); 
		TTF_CloseFont(fontCTRL); 
		TTF_CloseFont(fontQ1); 
		TTF_Quit();
		SDL_Quit();
	}

void rungame(){
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
			HandleEvent(event, &gameover, &currentDirection, &perso, &epee, &ludo, &fireball, &poisonball, &deathball, &HP_potion, &champignon, &pnj, &display,&posMouseX,&posMouseY,&selection);
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
            MANA_perso.w = perso.mana*perso.size/MAX_MANA;
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
			if(monstre==0){
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
				
				if(monstre==1){
					monster.pos.x = monster.pos.x + deathball.v.x; //Contrôle du monstre avec la deathball
					monster.pos.y = monster.pos.y + deathball.v.y;
				}
				
				//Mix_PlayMusic(music, -1); // Jouer infiniment la musique;

				
				
				
				
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
				tete_stickman +=1;
				aleaspawn(&monster);
				monster.life=100;


			}
			if(ludo.life <= 0){
				ludo.display = 0;
				ludo.life=100;
				aleaspawn(&ludo);
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
				aleaspawn(&champignon);
			}	
			
			//Collisions si le jeu tourne
			if(Collision(&ludo, &perso)&&((ludo.display!=0)||(ludo.life!=0))){ 
				ludo.life -=1;
			}
			
			if(CollisionBdf(&ludo, &fireball)&&fireball.display!=0){
				fireball.display = 0;
				ludo.life -=10;
				if(ludo.life<=0){ //SI LUDO MEURT, ON GAGNE SA TETE
					tete+=1; //Pour quete 2
				}
			}
			
			if(CollisionBdf(&monster, &fireball)&&fireball.display!=0){
				fireball.display=0;
				monster.life -=10;
				if(monster.life<=0){
					tete_stickman+=1;
				}
			}
			
			if(Collision(&monster, &perso)){ 
				monster.life -=1;
			}
			
			if(Collision(&HP_potion,&perso)&&(HP_potion.display!=0)&&(perso.life<MAX_HP)){
				HP_potion.display=0;
				aleaspawn(&HP_potion);
				if(perso.life+50<MAX_HP){ //Debug des pvs superieur au max en cas de potion ramassee
					perso.life +=50;
				}else{
					perso.life=MAX_HP;
				}
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
			if(Collision(&ludo,&monster)){
				monster.life--;
				ludo.life--;
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
			if(perso.mana<=0){
			  perso.mana = 0; 
			}
			if(perso.mana<1000){ 
			  perso.mana+=1;
			}

		
					
		      if (epee.display != 0) { //affiche perso
			SDL_Rect epeeImage;
			SDL_Rect epeePos;
			if(perso.currDirection==1){
			    epeePos.x=perso.pos.x+20;
			    epeePos.y=perso.pos.y;
			}
			if(perso.currDirection==0){
			    epeePos.x=perso.pos.x;
			    epeePos.y=perso.pos.y-20;
			}
			if(perso.currDirection==2){
			    epeePos.x=perso.pos.x;
			    epeePos.y=perso.pos.y+20;
			}
			if(perso.currDirection==3){
			    epeePos.x=perso.pos.x-25;
			    epeePos.y=perso.pos.y;
			    
			}
			epeeImage.y = 0;
			epeeImage.w = epee.size;
			epeeImage.h = epee.size;
			epeeImage.x = epee.size*(perso.currDirection*2);
			if(z){
			 epeeImage.x +=32;
			}
			SDL_BlitSurface(spriteepee, &epeeImage, screen, &epeePos);
			SDL_BlitSurface(barreDeVie_perso, NULL, screen, &manaPos); // BlitSurface épée AVANT vie/mana -> pour que l'épée ne soit pas AU DESSSUS de vie/mana
			SDL_BlitSurface(barreDeMana_perso, NULL, screen, &spritePos);
		      }

		}
		
		
			
			
			//Message quest
			posMesQ1.x = 2*SCREEN_WIDTH/100;
			posMesQ1.y = 90*SCREEN_HEIGHT/100;
				
			if(DistanceXY(&pnj,&perso)<50){ //affichage d'une quete
				if(quest1[0][0][0]==0){
					messageQ1 = TTF_RenderText_Solid(fontQ1, "Va me chercher 5 champignons O:Accepter la quete N:Quitter",textColor); //O pour accepter, N pour refuser
				}
				if(quest1[0][0][0]>0){
					messageQ1 = TTF_RenderText_Solid(fontQ1, "Merci d'avoir accepter la quete... J'attends mes champignons", textColor); //Si acceptation quête
					if(QTchampignon>5){ //Si on a été cueillir le champignon
						messageQ1 = TTF_RenderText_Solid(fontQ1, "Quete termine. Veuillez appuyer sur c pour la suite", textColor); 
						//RECOMPENSE DE QUETE ICI
						perso.argent = perso.argent + 5;
						if((continuer==1)&&(bdf!=1)){
							messageQ1 = TTF_RenderText_Solid(fontQ1, "Vous avez gagne 5 shortmoney, et vous avez acquis un nouveau pouvoir...", textColor); 

						}
						if(continuer==2&&perso.argent>=5){
							messageQ1 = TTF_RenderText_Solid(fontQ1,"Il te suis. Appuies sur espace pour tester tes nouvelles capacites, et tues le.", textColor); 
							bdf = 1;
						}
						if(continuer==3&&tete==1){
							messageQ1 = TTF_RenderText_Solid(fontQ1, "C'est tres bien! Tu peux te soigner en prenant cette potion", textColor); 
						}
						if(continuer==4&&tete_stickman!=1&&monstre!=1){
							messageQ1 = TTF_RenderText_Solid(fontQ1, "Tu le vois ce stickman? Ramenes moi sa tete et je te donnerai de quoi te battre", textColor); 
						}
						if(continuer==5&&tete_stickman==1){
							messageQ1 = TTF_RenderText_Solid(fontQ1, "Desormais tu peux controler ce monstre en appuyant sur F3! Bien joue! ", textColor);
							monstre=1;
						}
						if(continuer>5&&monstre==1){
						   	messageQ1 = TTF_RenderText_Solid(fontQ1, "Tiens! Ce pnj bizarre est revenue. Tests tes nouveaux pouvoirs!", textColor); 
						}
					}
					if(quest1[0][1][0]>0){
						messageQ1 = TTF_RenderText_Solid(fontQ1, "Tu veux pas ma quete? :(", textColor); //Si refus de la quête(press n)
						quest1[0][1][0]=0;
					}	
				}
					
			} else {
				messageQ1 = TTF_RenderText_Solid(fontQ1, "",textColor); //Message vide
			}
			if(continuer>=4){
			    monster.display=1;  
			} else {
			    monster.display=0;
			}
			if(continuer==2||continuer==6){
			    ludo.display=1;
			} else {
			    ludo.display=0;
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
			
			if(pnj.display != 0){ //affichage champi
				SDL_Rect pnjImage;
				SDL_Rect pnjPos;
				pnjPos.x = pnj.pos.x;
				pnjPos.y = pnj.pos.y;		
				pnjImage.y = 0;
				pnjImage.w = champignon.size;
				pnjImage.h = champignon.size;
				pnjImage.x = ludo.size*(ludo.currDirection*2);
				SDL_BlitSurface(spritepnj, &pnjImage, screen, &pnjPos);
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
			posMes.x=50*SCREEN_WIDTH/100-(100/ratio);
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
			/*
			FILE* ctrls=fopen("CONTROLS.txt", "r+");
			int lecture;
			if(ctrls!=NULL){
				lecture=0;
			}else{
				lecture=1;
				printf("IMPOSSIBLE DE LIRE DANS LE FICHIER");
			}
			while(lecture==0){
				char c = fgetc(ctrls);
				if( feof(ctrls) ) {
					lecture=1;
				}else{
					printf("%c", c);
				}
			}
			fclose(ctrls);
			display=1;
			*/
			char buffer[20]; //char temporaire pour les touches actuelles
			message = TTF_RenderText_Solid(font50,"Controles :",textColor);
			posMes.x=50*SCREEN_WIDTH/100-(100/ratio);
			posMes.y=0.0;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(font36,"Retour",textColor);
			posMes.x=60*SCREEN_WIDTH/100;
			posMes.y=20*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Haut",textColor); //Touche haut
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(haut_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=45*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Bas",textColor);  //Touche bas
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(bas_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=45*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Gauche",textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(gauche_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=45*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Droite",textColor);
			posMes.x=55*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(droite_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=55*SCREEN_WIDTH/100;
			posMes.y=45*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Boule de feu",textColor);
			posMes.x=70*SCREEN_WIDTH/100;
			posMes.y=40*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(bdf_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=70*SCREEN_WIDTH/100;
			posMes.y=45*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Coup d'epee",textColor);
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(epee_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=65*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Pause",textColor);
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(quitter_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=65*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Boule Poison",textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(bdp_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=65*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Controle mob",textColor);
			posMes.x=55*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(bdm_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=55*SCREEN_WIDTH/100;
			posMes.y=65*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Continuer",textColor);
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=80*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(Continuer_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=10*SCREEN_WIDTH/100;
			posMes.y=85*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Accepter",textColor);
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=80*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(Oui_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=25*SCREEN_WIDTH/100;
			posMes.y=85*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"Refuser",textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=80*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(Non_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=40*SCREEN_WIDTH/100;
			posMes.y=85*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"IA ennemis",textColor);
			posMes.x=70*SCREEN_WIDTH/100;
			posMes.y=60*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			sprintf(buffer, "(%s)", SDL_GetKeyName(IA_touche));
			message = TTF_RenderText_Solid(fontCTRL,buffer,textColor);
			posMes.x=70*SCREEN_WIDTH/100;
			posMes.y=65*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(fontCTRL,"SAVE",textColor);
			posMes.x=55*SCREEN_WIDTH/100;
			posMes.y=80*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			message = TTF_RenderText_Solid(fontCTRL,"ACTION",textColor);
			posMes.x=20*SCREEN_WIDTH/100;
			posMes.y=20*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(fontCTRL,"(TOUCHE ASSOCIEE)",textColor);
			posMes.x=20*SCREEN_WIDTH/100;
			posMes.y=25*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			message = TTF_RenderText_Solid(fontCTRL,"<- Cliquez pour changer",textColor);
			posMes.x=35*SCREEN_WIDTH/100;
			posMes.y=25*SCREEN_HEIGHT/100;
			SDL_BlitSurface(message,NULL,screen,&posMes);
			
			if(selection==0){
				posFleche.x=80*SCREEN_WIDTH/100;
				posFleche.y=18*SCREEN_HEIGHT/100;
				SDL_BlitSurface(fleche,NULL,screen,&posFleche);
			}
		}
        SDL_UpdateRect(screen,0,0,0,0);
		SDL_Delay(12);
	}
	resetAll(); //casse tout avant de finir le programme
}
