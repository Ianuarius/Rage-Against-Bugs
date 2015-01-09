#ifndef __SDL_H_INCLUDED__
#define __SDL_H_INCLUDED__

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/*
	High-level wrapper for SDL2 calls.
	Simply initializes and finishes SDL2.
*/

namespace SDL
{
	// Initializes SDL2, MUST be called before everything else
	bool init();

	// Destroys SDL2, MUST be called when program closes
	void exit();
}

#endif // __SDL_H_INCLUDED__