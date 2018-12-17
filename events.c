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

double angle;
int actualRes=2;
int bdfdeplacements[4];
int changertouche=0;

void HandleEvent(SDL_Event event, int *gameover, int *currDirection, struct sprite_t *perso, struct sprite_t *ludo, struct sprite_t *epee,
 struct bdf_t *fireball, struct sprite_t *poisonball, struct sprite_t *deathball, struct sprite_t *HP_potion,struct sprite_t *champignon, struct sprite_t *pnj,
 int *display, int *posMouseX, int *posMouseY, int *selection,SDLKey *haut_touche,SDLKey *bas_touche,SDLKey *gauche_touche,SDLKey *droite_touche,SDLKey *bdf_touche,
 SDLKey *epee_touche,SDLKey *Continuer_touche,SDLKey *Oui_touche,SDLKey *Non_touche,SDLKey *bdp_touche,SDLKey *bdm_touche,SDLKey *quitter_touche,SDLKey *pnj_touche,
 SDLKey *IA_touche,int bdf,int *SCREEN_HEIGHT,int *SCREEN_WIDTH,int *z,int *resChange,int resolutions[4][2],int tete,int tete_stickman,int monstre,int QTchampignon, int questInteract,int *continuer,int (*quest1)[5][2][2],int *choice,int *choiceTEST,int (*deplacements)[4],int *frappe){
	switch (event.type){
		case SDL_QUIT:
			*gameover = 1;
			break;
		case SDL_KEYDOWN:
			if((event.key.keysym.sym==*gauche_touche)&&(*display==2)){
				perso->currDirection = DIR_LEFT;
				(*deplacements)[0]=1;
				*currDirection= DIR_LEFT;
			}
			if((event.key.keysym.sym==*droite_touche)&&(*display==2)){
				perso->currDirection = DIR_RIGHT;
				(*deplacements)[1]=1;
				*currDirection= DIR_RIGHT;
			}
			if((event.key.keysym.sym==*haut_touche)&&(*display==2)){
				perso->currDirection = DIR_UP;
				(*deplacements)[2]=1;
				*currDirection= DIR_UP;
			}
			if((event.key.keysym.sym==*bas_touche)&&(*display==2)){
				perso->currDirection = DIR_DOWN;
				(*deplacements)[3]=1;
				*currDirection= DIR_DOWN;
			}				
			if((event.key.keysym.sym==*bdf_touche)&&(bdf)&&(perso->mana>100)&&(*display==2)){
				if (fireball->display==0) {
				    perso->mana = perso->mana-100;
					fireball->display=1;
					fireball->range=7*BALL_SPEED;
					fireball->pos.x = perso->pos.x+(GRASS_SIZE/3);
					fireball->pos.y = perso->pos.y+(GRASS_SIZE/3);
					bdfdeplacements[0]=(*deplacements)[0];
					bdfdeplacements[1]=(*deplacements)[1];
					bdfdeplacements[2]=(*deplacements)[2];
					bdfdeplacements[3]=(*deplacements)[3];
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
						angle = (*currDirection * (2*M_PI));
						fireball->v.x = -2*BALL_SPEED*cos(angle);
						fireball->v.y = 2*BALL_SPEED * sin(angle);
					}else if((bdfdeplacements[1]==1)&&(bdfdeplacements[0]!=1)){ //droite
						angle = (*currDirection * (2*M_PI));
						fireball->v.x = 2*BALL_SPEED*cos(angle);
						fireball->v.y = -2*BALL_SPEED * sin(angle);
					}else if((bdfdeplacements[2]==1)&&(bdfdeplacements[3]!=1)){ //haut
						angle = (*currDirection * (2*M_PI));
						fireball->v.x = 2*BALL_SPEED * sin(angle);
						fireball->v.y = -2*BALL_SPEED*cos(angle);
					}else if((bdfdeplacements[3]==1)&&(bdfdeplacements[2]!=1)){ //bas
						angle = (*currDirection * (2*M_PI));
						fireball->v.x = -2*BALL_SPEED * sin(angle);
						fireball->v.y = 2*BALL_SPEED*cos(angle);
					}else if((bdfdeplacements[0]==0)&&(bdfdeplacements[1]==0)&&(bdfdeplacements[2]==0)&&(bdfdeplacements[3]==0)){
						switch(*currDirection){
							case 0 :
								angle = (*currDirection * (2*M_PI));
								fireball->v.x = BALL_SPEED * sin(angle);
								fireball->v.y = -BALL_SPEED*cos(angle);
								break;
							case 1 :
								angle = (*currDirection * (2*M_PI));
								fireball->v.x = BALL_SPEED*cos(angle);
								fireball->v.y = -BALL_SPEED * sin(angle);
								break;
							case 2 :
								angle = (*currDirection * (2*M_PI));
								fireball->v.x = -BALL_SPEED * sin(angle);
								fireball->v.y = BALL_SPEED*cos(angle);
								break;
							case 3 :
								angle = (*currDirection * (2*M_PI));
								fireball->v.x = -BALL_SPEED*cos(angle);
								fireball->v.y = BALL_SPEED * sin(angle);
								break;
							break;
						}
						break;
					}
				}
			}
			if((event.key.keysym.sym==*bdp_touche)&&(*display==2)){
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
			if((event.key.keysym.sym==*bdm_touche)&&(*display==2)){
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
			if((event.key.keysym.sym==*pnj_touche)&&(*display==2)){
				/* Apparition PNJ Ludo */
				ludo->life= 100;
				ludo->display = 1;
				ludo->pos.x = 200;
				ludo->pos.y = 200;
			}	
			if((event.key.keysym.sym==*IA_touche)&&(*display==2)){
				if(*choiceTEST){
					*choice = 1;
					*choiceTEST= 0;
				} else {
					*choice = 0;
					*choiceTEST = 1;
				}
			}
			break;
		case SDL_KEYUP: //touche relachee
			if((event.key.keysym.sym==*quitter_touche)&&(changertouche==0)){   // ouverture menu pause si jeu en cours / retour au jeu si dans menu pause
				if(*display==2){
					*display=5;
				}else if(*display==5){
					*display=2;
				}
			}
			/*if(event.key.keysym.sym==SDLK_ESCAPE){
				*display=1;
			}*/
			if(event.key.keysym.sym==*gauche_touche){
				(*deplacements)[0]=0;
			}
			if(event.key.keysym.sym==*droite_touche){
				(*deplacements)[1]=0;
			}
			if(event.key.keysym.sym==*haut_touche){
				(*deplacements)[2]=0;
			}
			if(event.key.keysym.sym==*bas_touche){
				(*deplacements)[3]=0;
			}
			if(event.key.keysym.sym==*Oui_touche){
                if(questInteract){
                    *quest1[0][0][0] += 1;
                }
			}
			if(event.key.keysym.sym==*Non_touche){
                if(questInteract){
                    *quest1[0][1][0] += 1;
                }
			}
			if(event.key.keysym.sym==*Continuer_touche){
			  //CONDITIONS POUR LES QUETES
              if(questInteract)
              {
                if(*continuer==0&&QTchampignon>5){
                    *continuer=1;
                }else{
                    if(*continuer==1){
                    *continuer = 2;
                    }else{
                        if(*continuer==2&&tete>=1){
							*continuer=3;
                        }else{
                            if(*continuer==3&&perso->life>=100){
                                *continuer=4;
                            }else{
                                if(*continuer==4&&tete_stickman>=1){
                                    *continuer =5; 
                                }else{
                                    if(*continuer==5&&monstre==1){
                                        *continuer = 6; 
                                    }else{
                                        if(*continuer==6&&tete_stickman>=2){
                                            *continuer = 7;
                                        } else {
                                            if(*continuer==7){
                                             *continuer = 8;   
                                            } else {
                                                if(*continuer==8){
                                                 *continuer +=1;   
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }	
        }
            if(event.key.keysym.sym==*epee_touche){
				if(*z==0){
					*z = 1;
				}else{
					*z = 0;
				}
				if(*frappe==0){
				  *frappe=1;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if((*display==1)){ //clic souris dans menu
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=90**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					//Lancement du jeu
					*display=2;
					perso->life=100;
					*selection=-1; //reset
				}
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=96**SCREEN_WIDTH/100)&&(*posMouseY>=40**SCREEN_HEIGHT/100)&&(*posMouseY<=45**SCREEN_HEIGHT/100)){
					//Lancement des options
					*display=3;
					*selection=-1; //reset
				}
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=90**SCREEN_WIDTH/100)&&(*posMouseY>=60**SCREEN_HEIGHT/100)&&(*posMouseY<=65**SCREEN_HEIGHT/100)){
					//fermeture du jeu
					*gameover=0;
					*selection=-1; //reset
				}
			}
			if((*display==3)){ //clic souris dans options
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=40**SCREEN_HEIGHT/100)&&(*posMouseY<=45**SCREEN_HEIGHT/100)){
					if(actualRes<3){
						actualRes++;	//agrandir ecran
						*SCREEN_HEIGHT=resolutions[actualRes][0];
						*SCREEN_WIDTH=resolutions[actualRes][1];
						*resChange=1;
					}else{
						//POP UP ECRAN AGRANDI AU MAX
					}
					*selection=-1; //reset
				}
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=60**SCREEN_HEIGHT/100)&&(*posMouseY<=65**SCREEN_HEIGHT/100)){
					if(actualRes>0){
						actualRes--; //reduire ecran
						*SCREEN_HEIGHT=resolutions[actualRes][0];
						*SCREEN_WIDTH=resolutions[actualRes][1];
						*resChange=1;
					}
					else{
						//POP UP ECRAN REDUIT AU MAX
					}
					*selection=-1; //reset
				}
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=80**SCREEN_HEIGHT/100)&&(*posMouseY<=85**SCREEN_HEIGHT/100)){
					//controles
					*display=4; //menu de controles
					*selection=-1; //reset
				}
				if((*posMouseX>=60**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					*display=1; //retour menu
					*selection=-1; //reset
				}
			}
			if((*display==4)){ //clic souris dans controles
				SDL_GetMouseState(posMouseX,posMouseY); 
				if((*posMouseX>=60**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					*display=1; //retour menu
					*selection=-1; //reset
				}
				if((*posMouseX>=10**SCREEN_WIDTH/100)&&(*posMouseX<=20**SCREEN_WIDTH/100)&&(*posMouseY>=45**SCREEN_HEIGHT/100)&&(*posMouseY<=50**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*haut_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=25**SCREEN_WIDTH/100)&&(*posMouseX<=35**SCREEN_WIDTH/100)&&(*posMouseY>=45**SCREEN_HEIGHT/100)&&(*posMouseY<=50**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*bas_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=40**SCREEN_WIDTH/100)&&(*posMouseX<=50**SCREEN_WIDTH/100)&&(*posMouseY>=45**SCREEN_HEIGHT/100)&&(*posMouseY<=50**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*gauche_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=55**SCREEN_WIDTH/100)&&(*posMouseX<=65**SCREEN_WIDTH/100)&&(*posMouseY>=45**SCREEN_HEIGHT/100)&&(*posMouseY<=50**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*droite_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=70**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=45**SCREEN_HEIGHT/100)&&(*posMouseY<=50**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*bdf_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=10**SCREEN_WIDTH/100)&&(*posMouseX<=20**SCREEN_WIDTH/100)&&(*posMouseY>=65**SCREEN_HEIGHT/100)&&(*posMouseY<=70**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*epee_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=25**SCREEN_WIDTH/100)&&(*posMouseX<=35**SCREEN_WIDTH/100)&&(*posMouseY>=65**SCREEN_HEIGHT/100)&&(*posMouseY<=70**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*quitter_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=40**SCREEN_WIDTH/100)&&(*posMouseX<=50**SCREEN_WIDTH/100)&&(*posMouseY>=65**SCREEN_HEIGHT/100)&&(*posMouseY<=70**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*bdp_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=55**SCREEN_WIDTH/100)&&(*posMouseX<=65**SCREEN_WIDTH/100)&&(*posMouseY>=65**SCREEN_HEIGHT/100)&&(*posMouseY<=70**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*bdm_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=10**SCREEN_WIDTH/100)&&(*posMouseX<=20**SCREEN_WIDTH/100)&&(*posMouseY>=85**SCREEN_HEIGHT/100)&&(*posMouseY<=90**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*Continuer_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=25**SCREEN_WIDTH/100)&&(*posMouseX<=35**SCREEN_WIDTH/100)&&(*posMouseY>=85**SCREEN_HEIGHT/100)&&(*posMouseY<=90**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*Oui_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=40**SCREEN_WIDTH/100)&&(*posMouseX<=50**SCREEN_WIDTH/100)&&(*posMouseY>=85**SCREEN_HEIGHT/100)&&(*posMouseY<=90**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*Non_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=70**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=65**SCREEN_HEIGHT/100)&&(*posMouseY<=70**SCREEN_HEIGHT/100)){
					changertouche=1;
					SDL_Event keychange;
					int change = 0;
					while(change==0){
						SDL_PollEvent(&keychange);
						if(keychange.type==SDL_KEYDOWN){
							change = 1;
						}
					}
					*IA_touche=keychange.key.keysym.sym;
					changertouche=0;
				}
				if((*posMouseX>=55**SCREEN_WIDTH/100)&&(*posMouseX<=65**SCREEN_WIDTH/100)&&(*posMouseY>=80**SCREEN_HEIGHT/100)&&(*posMouseY<=85**SCREEN_HEIGHT/100)){//SAUVEGARDE des touches
					FILE* ctrls=fopen("CONTROLS.txt", "w+");
					int lecture;
					if(ctrls!=NULL){
						lecture=0;
					}else{
						lecture=1;
						printf("IMPOSSIBLE DE LIRE DANS LE FICHIER");
					}
					if(lecture==0){
						fputs(SDL_GetKeyName(*haut_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*bas_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*gauche_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*droite_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*bdf_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*epee_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*quitter_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*bdp_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*bdm_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*Continuer_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*Oui_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*Non_touche),ctrls);
						fputs(" ",ctrls);
						fputs(SDL_GetKeyName(*IA_touche),ctrls);
						lecture=1;
					}
					fclose(ctrls);
				}
				
			}
			if((*display==5)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=85**SCREEN_WIDTH/100)&&(*posMouseX<=95**SCREEN_WIDTH/100)&&(*posMouseY>=80**SCREEN_HEIGHT/100)&&(*posMouseY<=85**SCREEN_HEIGHT/100)){
					*display=3;
					*selection=-1;
				}
				if((*posMouseX>=85**SCREEN_WIDTH/100)&&(*posMouseX<=95**SCREEN_WIDTH/100)&&(*posMouseY>=90**SCREEN_HEIGHT/100)&&(*posMouseY<=95**SCREEN_HEIGHT/100)){
					*display=1; //retour menu
					*selection=-1; //reset
				}
			}
			if((*display==6)){
				SDL_GetMouseState(posMouseX,posMouseY);
				if((*posMouseX>=50**SCREEN_WIDTH/100)&&(*posMouseX<=70**SCREEN_WIDTH/100)&&(*posMouseY>=70**SCREEN_HEIGHT/100)&&(*posMouseY<=80**SCREEN_HEIGHT/100)){
					*display=1;
					*selection=-1;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			*selection=-1; //reset
			if((*display==1)){ //deplacement souris dans menu
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1; //reset
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=90**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					*selection=1; //play
				}
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=96**SCREEN_WIDTH/100)&&(*posMouseY>=40**SCREEN_HEIGHT/100)&&(*posMouseY<=45**SCREEN_HEIGHT/100)){
					*selection=2; //options
				}
				if((*posMouseX>=78**SCREEN_WIDTH/100)&&(*posMouseX<=90**SCREEN_WIDTH/100)&&(*posMouseY>=60**SCREEN_HEIGHT/100)&&(*posMouseY<=65**SCREEN_HEIGHT/100)){
					*selection=3; //quit
				}
			}
			if((*display==3)){ //deplacement souris dans options
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1; //reset
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=40**SCREEN_HEIGHT/100)&&(*posMouseY<=45**SCREEN_HEIGHT/100)){
					*selection=1; //agrandir ecran
				}
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=60**SCREEN_HEIGHT/100)&&(*posMouseY<=65**SCREEN_HEIGHT/100)){
					*selection=2; //reduire ecran
				}
				if((*posMouseX>=5**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=80**SCREEN_HEIGHT/100)&&(*posMouseY<=85**SCREEN_HEIGHT/100)){
					*selection=3; //controles
				}
				if((*posMouseX>=60**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
			}
			if((*display==4)){ //deplacement souris dans controles
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1; //reset
				if((*posMouseX>=60**SCREEN_WIDTH/100)&&(*posMouseX<=80**SCREEN_WIDTH/100)&&(*posMouseY>=20**SCREEN_HEIGHT/100)&&(*posMouseY<=25**SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
			}
			if((*display==5)){
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1;
				if((*posMouseX>=85**SCREEN_WIDTH/100)&&(*posMouseX<=95**SCREEN_WIDTH/100)&&(*posMouseY>=80**SCREEN_HEIGHT/100)&&(*posMouseY<=85**SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
				if((*posMouseX>=85**SCREEN_WIDTH/100)&&(*posMouseX<=95**SCREEN_WIDTH/100)&&(*posMouseY>=90**SCREEN_HEIGHT/100)&&(*posMouseY<=95**SCREEN_HEIGHT/100)){
					*selection=1; //retour menu
				}
			}
			if((*display==6)){
				SDL_GetMouseState(posMouseX,posMouseY);
				*selection=-1;
				if((*posMouseX>=50**SCREEN_WIDTH/100)&&(*posMouseX<=60**SCREEN_WIDTH/100)&&(*posMouseY>=70**SCREEN_HEIGHT/100)&&(*posMouseY<=75**SCREEN_HEIGHT/100)){
					*selection=0; //retour menu
				}
			}
			break;
				
		break;
	}
}
