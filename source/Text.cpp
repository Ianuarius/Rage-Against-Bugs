#include "Text.h"

Text::Text() {
	mColor = &Color("white");
}

void Text::setFont(Font *font) {
	mFont = font;
}

void Text::setColor(Color color) {
	mColor = &color;
}

void Text::print(std::string text) {
	// Get rid of pre-existing texture
	texture.free();

	// Get current font settings
	TTF_Font *font = mFont->getFont();

	// Get color in SDL_Color
	//SDL_Color color = mColor->getSDLColor();

	SDL_Color color = {254, 254, 254, 254};

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (textSurface) {
		//texture = SDL_CreateTextureFromSurface();
	}
}