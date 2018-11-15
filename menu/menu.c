#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main(int argc, char* argv[])
{
    SDL_Surface *screen,*temp;
    int gameover;

    /* initialize video system */
    SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

    /* set the title bar */
    SDL_WM_SetCaption("Menu Test", "Menu Test");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    gameover = 0;
	
	//Les surfaces 
	SDL_Surface *background; 
	SDL_Surface *message; 
	SDL_Surface *message2; 
	SDL_Surface *message3; 
	SDL_Surface *message4; 
	//La structure d'événement 
	SDL_Event event; 

	//Le Font qu'on va utiliser
	TTF_Font *font50; 
	TTF_Font *font36;

	//La couleur du Font 
	SDL_Color textColor = { 255, 255, 255 };
	
	//Mise en place de la barre caption 
	SDL_WM_SetCaption( "Menu Test", NULL ); 
	
	temp = SDL_LoadBMP("background.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
	
	font50 = TTF_OpenFont( "A_Love_Of_Thunder.ttf", 50);
	font36 = TTF_OpenFont( "A_Love_Of_Thunder.ttf", 36);
	
	message = TTF_RenderText_Solid(font50,"Welcome to AShortSomething !",textColor);
	SDL_Rect posMes1={50*SCREEN_WIDTH/100-400,0.0};
	message2 = TTF_RenderText_Solid(font36,"Play",textColor);
	SDL_Rect posMes2={80*SCREEN_WIDTH/100,20*SCREEN_HEIGHT/100};
	message3 = TTF_RenderText_Solid(font36,"Options",textColor);
	SDL_Rect posMes3={80*SCREEN_WIDTH/100,40*SCREEN_HEIGHT/100};
	message4 = TTF_RenderText_Solid(font36,"Quit",textColor);
	SDL_Rect posMes4={80*SCREEN_WIDTH/100,60*SCREEN_HEIGHT/100};
	int *posMouseX=0;
	int *posMouseY=0;
    /* main loop: check events and re-draw the window until the end */
    while (!gameover)
    {
        SDL_Event event;

        /* look for an event */
        if (SDL_PollEvent(&event)) {
            /* an event was found */
            switch (event.type) {
                /* close button clicked */
                case SDL_QUIT:
                    gameover = 1;
                    break;

                /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            gameover = 1;
                            break;
                        default:
                            break;
                    }
                    break;
				case SDL_MOUSEBUTTONDOWN:
					posMouse=SDL_GetMouseState(event.button.x,event.button.y);
					printf("POS MOUSE X %d POS MOUSE Y %d\n",posMouse.x,posMouse.y);
					break;
            }
        }

        /* update the screen */
		
		SDL_BlitSurface(message,NULL,screen,&posMes1);
		SDL_BlitSurface(message2,NULL,screen,&posMes2);
		SDL_BlitSurface(message3,NULL,screen,&posMes3);
		SDL_BlitSurface(message4,NULL,screen,&posMes4);
        SDL_UpdateRect(screen,0,0,0,0);
    }

    /* clean up */
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(message);
	SDL_FreeSurface(message2);
	SDL_FreeSurface(message3);
	SDL_FreeSurface(message4);
    SDL_Quit();

    return 0;
}