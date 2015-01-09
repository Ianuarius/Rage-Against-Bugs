#ifndef __FONT_H_DEFINED__
#define __FONT_H_DEFINED__

#include <string>
#include <SDL_ttf.h>

class Font {
	public:
		// Constructor overloading
		Font();
		Font(std::string fontName, int fontSize);

		~Font();

		bool loadFromFile(std::string fontName, int fontSize);
		TTF_Font *getFont();

	private:
		TTF_Font *font;
};

#endif __FONT_H_DEFINED__