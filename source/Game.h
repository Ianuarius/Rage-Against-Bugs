#ifndef __GAME_H_DEFINED__
#define __GAME_H_DEFINED__

#include "Window.h"
#include "Board.h"
#include "Piece.h"
#include "Color.h"
#include "Texture.h"
#include <time.h>
#include <math.h>

class Game {
	public:
		Game(Window* window, Board* board);

		void drawScene();
		void createNewPiece();
		void spawnVirus(int count, int level);
		bool virusExists();
		Piece* getCurrentPiece();

		static const char blocks[6];

	private:
		void drawBoard();
		void drawPiece(Piece *piece);

		int randomNumber(int min, int max);

		Window* mWindow;
		Board* mBoard;
		Piece currentPiece, nextPiece;

		Texture background;
		SDL_Rect backgroundRect;

		Texture pot;
		SDL_Rect potRect;
};

#endif //__GAME_H_DEFINED__