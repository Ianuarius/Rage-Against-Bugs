#include "Game.h"

const char Game::blocks[6] = {1, 4, 16, 2, 8, 32};

Game::Game(Window* window, Board* board) {

	// Seed random
	srand((unsigned int)time(NULL));
	
	this->mWindow = window;
	this->mBoard = board;

	// Taustakuva
	background.setRenderer(mWindow->renderer);
	background.loadFromFile("taustakuva.png");
	backgroundRect.w = 256;
	backgroundRect.h = 240;
	backgroundRect.x = 0;
	backgroundRect.y = 0;

	// Ruukku
	pot.setRenderer(mWindow->renderer);
	pot.loadFromFile("ruukku.png");
	potRect.w = 164;
	potRect.h = 166;
	potRect.x = 0;
	potRect.y = 0;

	//Create initial piece
	currentPiece = Piece(blocks[randomNumber(1,3)], blocks[randomNumber(1,3)], false);
	currentPiece.x = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	currentPiece.y = 0;
	currentPiece.rotation = 0;

	//Create next piece
	nextPiece = Piece(blocks[randomNumber(1,3)], blocks[randomNumber(1,3)], false);
	nextPiece.x = BOARD_WIDTH + 5;
	nextPiece.y = 0;
	nextPiece.rotation = 0;
}

void Game::drawScene() {
	// Draw background
	mWindow->render(&background, &backgroundRect, 0, 0);

	// Draw the pot
	mWindow->render(&pot, &potRect, (BOARD_X / 2 + BLOCK_SIZE), BOARD_Y);

	// Draws board
	drawBoard();

	// Draws current piece
	drawPiece(&currentPiece);

	// Draws next piece
	drawPiece(&nextPiece);
}

void Game::drawBoard() {
	Texture deadBlock;
	deadBlock.setRenderer(mWindow->renderer);

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
				switch(mBoard->getBlock(j, i)) {
				case 1: 
					deadBlock.loadFromFile("siemen_vihr_d.png");
					break;

				case 4:
					deadBlock.loadFromFile("siemen_sin_d.png");
					break;

				case 16: 
					deadBlock.loadFromFile("siemen_kelt_d.png");
					break;

				case 2:
					deadBlock.loadFromFile("virus_vihr.png");
					break;

				case 8:
					deadBlock.loadFromFile("virus_sin.png");
					break;

				case 32:
					deadBlock.loadFromFile("virus_kelt.png");
					break;

				default:
					//drawColor = Color("white");
					break;
				}

				if (!mBoard->isFreeBlock(j, i)) {
					SDL_Rect box = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

					mWindow->render(&deadBlock, &box, BOARD_X + j * BLOCK_SIZE, BOARD_Y + i * BLOCK_SIZE);
				}
		}
	}
}

void Game::createNewPiece() {
	//Set next piece to current piece
	currentPiece = nextPiece;
	currentPiece.x = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	currentPiece.y = 0;
	currentPiece.rotation = 0;

	//Create new next piece
	nextPiece = Piece(blocks[randomNumber(0,3)], blocks[randomNumber(0,3)], false);
	nextPiece.x = BOARD_WIDTH + 5;
	nextPiece.y = 0;
}

void Game::drawPiece(Piece *piece) {
	Texture siemenTekstuuri;
	siemenTekstuuri.setRenderer(mWindow->renderer);

	int x = piece->x;
	int y = piece->y;
	int rotation = piece->rotation;

	int xPos = mBoard->getXPos(x);
	int yPos = mBoard->getYPos(y);

	for (int i = 0; i < PIECE_SIZE; i++) {
		for(int j = 0; j < PIECE_SIZE; j++) {

			switch(piece->getBlock(rotation, i, j)) {
			case 1: 
				siemenTekstuuri.loadFromFile("siemen_vihr_h.png");
				break;

			case 4:
				siemenTekstuuri.loadFromFile("siemen_sin_h.png");
				break;

			case 16: 
				siemenTekstuuri.loadFromFile("siemen_kelt_h.png");
				break;

			case 2:
				siemenTekstuuri.loadFromFile("virus_vihr.png");
				break;

			case 8:
				siemenTekstuuri.loadFromFile("virus_sin.png");
				break;

			case 32:
				siemenTekstuuri.loadFromFile("virus_kelt.png");
				break;

			default:
				//drawColor = Color("white");
				break;
			}

			if (piece->getBlock(rotation, i, j) != 0) {
				SDL_Rect box = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

				//mWindow->drawRect(xPos + (BLOCK_SIZE * j), yPos + (BLOCK_SIZE * i), BLOCK_SIZE, BLOCK_SIZE, Color("white"));
				mWindow->render(&siemenTekstuuri, &box, xPos + (BLOCK_SIZE * j), yPos + (BLOCK_SIZE * i));
			}
		}
	}
}

void Game::spawnVirus(int count, int level) {
	int maxLevel = BOARD_HEIGHT - level;
	
	for (int i = 0; i < count; i++) {
		int x = randomNumber(0, BOARD_WIDTH);
		int y = randomNumber(maxLevel, BOARD_HEIGHT);

		mBoard->board[y][x] = blocks[randomNumber(3,6)];
	}
}

bool Game::virusExists() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if( mBoard->getBlock(j, i) == 2 ||
				mBoard->getBlock(j, i) == 8 ||
				mBoard->getBlock(j, i) == 32)
			{
				return true;
			}
		}
	}

	return false;
}

Piece* Game::getCurrentPiece() {
	return &currentPiece;
}

int Game::randomNumber(int min, int max) {
	return rand() % (max-min) + min;
}