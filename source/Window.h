#ifndef __WINDOW_H_DEFINED__
#define __WINDOW_H_DEFINED__

#include <string>
#include "SDL.h"
#include "Timer.h"
#include "Color.h"
#include "Texture.h"
#include "Font.h"

class Window {
	public:
		Window(int width, int height, std::string title="");

		virtual ~Window();

		// Destroys everything on the window and itself
		void destroy();

		// Destroys the program's window and recreates it with new width/height (and title)
		void resize(int width, int height, std::string title="");

		// Returns window width
		int getWidth();

		// Returns window height
		int getHeight();

		// Effectively draws everything that's onscreen
		void refresh();

		// Clears whole window to the background color
		void clear();

		// Toggles fullscreen mode of the program's window.
		bool toggleFullscreen();

		// Sets window title
		void setTitle(std::string title);

		// Returns average framerate (overall average method)
		int getFramerate();

		// Caps 
		void capFramerate(Uint32 framerate);

		// Returns how many milliseconds have passed since the last frame and the current
		int getDelta();

 		// SDL's internal data structure that represents window
		SDL_Window* window;

		SDL_Renderer* renderer;

		SDL_Surface* surface;

		bool isFullscreen;

		// Temp
		void drawRect(int X, int Y, int W, int H, Color color);

		// Loads texture from file
		void loadTexture(Texture *sourceTexture, std::string path);

		// Texture rendering
		void render(Texture *sourceTexture, SDL_Rect *destRect, int x, int y);

		// Prints text
		void printText(Font *font, std::string text);

	private:
		// Window caption
		std::string title;

		// Timer to see how many milliseconds has passed
		// between last frame and the current.
		Timer framerateTimer, frameTicks;

		// Framerate related variables
		int framerateCap, frameCount;

		// Deltatime
		int delta;

		// Current width and height
		int width, height;

		// Original width and height
		int originalWidth, originalHeight;
};

#endif //__WINDOW_H_DEFINED__