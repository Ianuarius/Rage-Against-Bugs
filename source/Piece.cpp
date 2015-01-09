#include "Piece.h"

Piece::Piece() {
	a = 0;
	b = 0;
	x = 0;
	y = 0;
	rotation = 0;
	virus = false;
}

Piece::Piece(int blockA, int blockB, bool virus) {
	a = blockA;
	b = blockB;
	x = 0;
	y = 0;
	rotation = 0;
	this->virus = virus;

	char piece[4 /* Rotation */][2 /* Vertical */][2 /* Horizontal */] = {
		{ 
			{0, 0},
			{a, b}
		},
		{ 
			{a, 0},
			{b, 0}
		},
		{ 
			{0, 0},
			{b, a}
		},
		{ 
			{b, 0},
			{a, 0}
		},
	};

	std::copy(&piece[0][0][0], &piece[0][0][0]+4*2*2, &cPiece[0][0][0]);

}

int Piece::getBlock(int rotation, int x, int y) {
	return cPiece[rotation][x][y];
}