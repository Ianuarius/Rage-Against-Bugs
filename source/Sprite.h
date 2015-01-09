#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include <vector>
#include "Texture.h"
#include "Window.h"
#include "Timer.h"

class Sprite {
	public:
		// Constructor
		Sprite(Window *window, Texture *sourceTexture, int width, int height, int frames, int framerate);

		// Destructor
		~Sprite();

		// Creates sprite from file. Assumes each frame to be same size.
		//void create(Texture *sourceTexture, int width, int height, int frames);

		// Used for manually adding frames.
		void addFrame(int x, int y, int width, int height);

		// Gets texture object
		//void setRenderer(SDL_Renderer* Renderer);

		// Set sprite framerate
		void setFramerate(int fps);

		// Plays animation
		// Infinite = true - plays animation forever
		// loopCount = how many times to loop
		void play(bool infinite, int loopCount);

		// Stops playing
		void stop();

		// Is animation still playing?
		bool playing();

		// Render sprite
		void render(int xPos, int yPos);


	private:
		Window *mWindow;
		Texture *gSpriteSheet;
		Timer spriteTimer;

		std::vector<SDL_Rect> gSpriteClips;

		int frameRate, frameCount, currentFrame, width, height;
		float currentFrameTime;

		bool infinitePlay;
		int animCount;
};

#endif __SPRITE_H_INCLUDED__