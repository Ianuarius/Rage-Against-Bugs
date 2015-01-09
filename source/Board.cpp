#include "Board.h"

Board::Board(Window *window) {
	mWindow = window;

	init();
}

void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			board[i][j] = POS_FREE;
		}
	}
}

int Board::getXPos(int position) {
	return BOARD_X + (BLOCK_SIZE * position);
}

int Board::getYPos(int position) {
	return BOARD_Y + (BLOCK_SIZE * position);
}

bool Board::isFreeBlock(int x, int y) {
	if (board[y][x] == POS_FREE) {
		return true;
	} else {
		return false;
	}
}

int Board::getBlock(int x, int y) {
	return board[y][x];
}

bool Board::isGameOver() {
	for (int x = 0; x < BOARD_WIDTH; x++) {
		if (board[1][x] != POS_FREE) {
			return true;
		}
	}

	return false;
}

bool Board::isPossibleMovement(int x, int y, int rotation) {
	for (int i1 = x, i2 = 0; i1 < x + PIECE_SIZE; i1++, i2++) {
		for (int j1 = y, j2 = 0; j1 < y + PIECE_SIZE; j1++, j2++) {

			// Check if the piece is outside the limits of the board
			if (i1 < 0 					|| 
				i1 > BOARD_WIDTH  - 1	||
				j1 > BOARD_HEIGHT - 1)
			{
				if (currentPiece->getBlock(rotation, j2, i2) != 0) { 
 					return false;
				}
			}

			if (j1 >= 0) {
				if (currentPiece->getBlock(rotation, j2, i2) !=0 
					&& !isFreeBlock(i1, j1)) {
						return false;
				}
			}

		}
	}

	return true;
}

void Board::storePiece() {
	int x = currentPiece->x;
	int y = currentPiece->y;
	int rotation = currentPiece->rotation;

	for (int i1 = x, i2 = 0; i1 < x + PIECE_SIZE; i1++, i2++) {
		for (int j1 = y, j2 = 0; j1 < y + PIECE_SIZE; j1++, j2++) {
			if (currentPiece->getBlock(rotation, j2, i2) != 0) {
				board[j1][i1] = currentPiece->getBlock(rotation, j2, i2);
			}
		}
	}
}

void Board::deletePossibleLines() {
	int piece = POS_FREE;
 	int count = 0;

	for (int x = 0; x < BOARD_WIDTH; x++) {
		for (int y = 0; y < BOARD_HEIGHT; y++) {
			int currentBlock = getBlock(x, y);

			if (currentBlock != POS_FREE) {
				if (currentBlock == piece || currentBlock == piece*2) {
					count++;
				} else {
					piece = currentBlock;
					count = 1;
				}

				if (count > BLOCK_COUNT) {
					deleteVertical(x, y);
				}

			} else {
				piece = POS_FREE;
				count = 0;
			}
		}
    }

    for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			int currentBlock = getBlock(x, y);

			if (currentBlock != POS_FREE) {
				if (currentBlock == piece || currentBlock == piece*2) {
					count++;
				} else {
					piece = currentBlock;
					count = 1;
				}

				if (count > BLOCK_COUNT) {
					deleteHorizontal(x, y);
				}

			} else {
				piece = POS_FREE;
				count = 0;
			}
		}
    }
}

void Board::deleteHorizontal(int x, int y) {
	int i = 0;
	int piece = getBlock(x, y);

	while (true) {
		int currentBlock = getBlock(x + i, y);
		int mathBlock = 0;
		
		if (currentBlock == 1 ||
			currentBlock == 4 ||
			currentBlock == 16) {
				mathBlock = currentBlock * 2;
		} else {
			mathBlock = currentBlock / 2;
		}

		if (currentBlock == piece || mathBlock == piece) {
			board[y][x + i] = POS_FREE;
			i--;
		} else {
			break;
		}
	}
}

void Board::deleteVertical(int x, int y) {
	int i = 0;
	int piece = getBlock(x, y);

	while (true) {
		int currentBlock = getBlock(x, y + i);
		int mathBlock = 0;
		
		if (currentBlock == 1 ||
			currentBlock == 4 ||
			currentBlock == 16) {
				mathBlock = currentBlock * 2;
		} else {
			mathBlock = currentBlock / 2;
		}

		if (currentBlock == piece || mathBlock == piece) {
			board[y + i][x] = POS_FREE;
			i--;
		} else {
			break;
		}
	}
}

void Board::setCurrentPiece(Piece* piece) {
	currentPiece = piece;
}