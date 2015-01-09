#include "Sprite.h"

Sprite::Sprite(Window *window, Texture *sourceTexture, int width, int height, int frames, int framerate = 0) {
	mWindow = window;
	gSpriteSheet = sourceTexture;

	for (int i = 0; i <= frames-1; i++) {
		SDL_Rect tmpSpriteClip;
		tmpSpriteClip.w = width;
		tmpSpriteClip.h = height;

		tmpSpriteClip.x = i * width;
		tmpSpriteClip.y = 0;

		gSpriteClips.push_back(tmpSpriteClip);
	}

	frameCount = gSpriteClips.size();
	currentFrame = 0;
	frameRate = framerate;
	currentFrameTime = 0;

	animCount = 0;
	infinitePlay = true;
}

Sprite::~Sprite() {
	gSpriteSheet->free();
}

void Sprite::addFrame(int x, int y, int width, int height) {
	SDL_Rect tmpSpriteClip;

	tmpSpriteClip.w = width;
	tmpSpriteClip.h = height;
	tmpSpriteClip.x = x;
	tmpSpriteClip.y = y;

	gSpriteClips.push_back(tmpSpriteClip);

	frameCount = gSpriteClips.size();
}

void Sprite::setFramerate(int fps) {
	frameRate = fps;
}

void Sprite::render(int xPos, int yPos)  {	
	SDL_Rect* currentClip = &gSpriteClips[currentFrame];
	mWindow->render(gSpriteSheet, currentClip, xPos, yPos);
	//gSpriteSheet->render(xPos, yPos, currentClip);

	if (spriteTimer.getTicks() >= 1.0f / frameRate * 1000) {
		++currentFrame;
		currentFrameTime = 0;

		if (currentFrame >= frameCount) {
			animCount--;
			currentFrame = 0;
		}

		if (!infinitePlay && animCount <= 0) {
			animCount = 0;
			spriteTimer.stop();
		} else {
			spriteTimer.start();
		}
	}
}

void Sprite::play(bool infinite, int loopCount) {
	infinitePlay = infinite;

	if (!infinite) {
		animCount = loopCount;
	}

	spriteTimer.start();
}

void Sprite::stop() {
	spriteTimer.stop();
}

bool Sprite::playing() {
	if (spriteTimer.isStarted()) {
		return true;
	} else {
		return false;
	}
}