#ifndef __TEXT_H_DEFINED__
#define __TEXT_H_DEFINED__

#include "Texture.h"
#include "Font.h"
#include "Color.h"

class Text {
	public:
		Text();

		void setFont(Font *font);
		void setColor(Color color);
		void print(std::string text);

	private:
		Texture texture;
		Font *mFont;
		Color *mColor;

};

#endif __TEXT_H_DEFINED__