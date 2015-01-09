#ifndef __PIECE_H_DEFINED__
#define __PIECE_H_DEFINED__

#include <algorithm>

class Piece {
	public:
		Piece();
		Piece(int a, int b, bool virus);

		int getBlock(int rotation, int x, int y);

		char cPiece[4 /* Rotation */][2 /* Vertical */][2 /* Horizontal */];
		int x, y, rotation;
		bool virus;

	private:
		int a, b;
};

#endif // __PIECE_H_DEFINED__