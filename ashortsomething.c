#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "game.h"
#include "sdlanim.c"

int main(){
    int j = 1;
    if(j==1){
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
        {
            printf("%s", Mix_GetError());
        }
        Zelda = Mix_LoadMUS("Zelda.mp3");
        Mix_PlayMusic(Zelda, -1); //Jouer infiniment la musique
        j = j +1;
    }
	rungame();
	return 0;
}

