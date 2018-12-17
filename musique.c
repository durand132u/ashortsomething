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

Mix_Music *Zelda;

void zeldaMusique(){
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
}
