#ifndef __BOARD_H_DEFINED__
#define __BOARD_H_DEFINED__

#include "Window.h"
#include "Piece.h"
#include "Texture.h"
#include "Sprite.h"

#define BLOCK_SIZE 8		// Block WIDTH and HEIGHT in pixels!

#define BOARD_WIDTH 12		// Board WIDTH in BLOCKS!
#define BOARD_HEIGHT 20		// Board HEIGHT in BLOCKS!
#define BOARD_X ((256 - (BOARD_WIDTH * BLOCK_SIZE)) / 2)	// Board X position in PIXELS
#define BOARD_Y ((240 - (BOARD_HEIGHT * BLOCK_SIZE)))		// Board Y position in PIXELS

#define PIECE_SIZE 2		
#define BLOCK_COUNT 3

class Board
{
	public:
		Board(Window *window);

		int getXPos(int position);	// Returns 'cell' X location in PIXELS
		int getYPos(int position);  // Returns 'cell' Y location in PIXELS

		void setCurrentPiece(Piece* piece);
		void storePiece();
		bool isFreeBlock(int x, int y);
		bool isPossibleMovement(int x, int y, int rotation);
		bool isGameOver();
		int  getBlock(int x, int y);
		void init();
		void renderExplosion(int x, int y);

		void deletePossibleLines();

		int board[BOARD_HEIGHT][BOARD_WIDTH];

	private:
		
		void deleteHorizontal(int x, int y);
		void deleteVertical(int x, int y);

		enum { POS_FREE, POS_FILLED };
		
		Piece *currentPiece;
		Window *mWindow;
};

#endif //__BOARD_H_DEFINED__ 