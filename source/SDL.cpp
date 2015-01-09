#include "SDL.h"

bool SDL::init() {
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	/*
	Initialize AUDIO and TFF
	*/
	if (TTF_Init() == -1) {
		printf("SDL TTF could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	 //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }

	return success;
}

void SDL::exit() {
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}