/*
 *		Rage against bugs
 */

//Using SDL and standard IO
#include <stdio.h>
#include "SDL.h"
#include "Window.h"
#include "Piece.h"
#include "Board.h"
#include "Game.h"
#include "Timer.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"

int main(int argc, char* args[])
{
	// SDL init
	if (!SDL::init()) {
		printf("SDL initialization failed!");
		return -1;
	}

	// Hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	// Window related
	Window window(800, 600, "Rage Against Bugs");
	SDL_Event event;
	bool quit = false;
	Timer gameTimer;
	gameTimer.start();

	Texture levelText, levelTextShadow;
	SDL_Color white = {255, 255, 255};
	SDL_Color black = {0, 0, 0};

	levelText.setRenderer(window.renderer);
	levelTextShadow.setRenderer(window.renderer);

	levelText.printText("Level 1", 16, white);
	levelTextShadow.printText("Level 1", 16, black);

	// Game related
	Board board(&window);
	Game game(&window, &board);
	Piece* currentPiece = game.getCurrentPiece();
	board.setCurrentPiece(currentPiece);

	int virusCount = 10;
	int virusLevel = 10;
	int level = 1;

	// Pate!
	Texture pate;
	window.loadTexture(&pate, "pate.png");
	Sprite throwAnimation(&window, &pate, pate.getWidth()/3, pate.getHeight(), 3, 6);

	game.spawnVirus(virusCount, virusLevel);

	Music ost("ost001.wav");
	ost.play();

	while(!quit) {
		Piece* currentPiece = game.getCurrentPiece();
		int rotation = currentPiece->rotation;
		int x = 0;
		Uint32 waitTicks = 750;

		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_LEFT:
						x--;
						break;

					case SDLK_RIGHT:
						x++;
						break;

					case SDLK_DOWN:
						waitTicks = 5;
						break;

					case SDLK_SPACE:
						rotation = (rotation + 1) % 4;
						break;

					case SDLK_ESCAPE:
						exit(0);
						break;

					default:
						break;
				}
			}
		}

		if (board.isPossibleMovement(currentPiece->x + x, currentPiece->y, rotation)) {
			currentPiece->x += x;
			currentPiece->rotation = rotation;
		}

		if (gameTimer.getTicks() > waitTicks) {
			if (board.isPossibleMovement(currentPiece->x, currentPiece->y+1, currentPiece->rotation)) {
				currentPiece->y++;
			} else {
				board.storePiece();

				if (board.isGameOver()) {
					exit(0);
				}

				board.deletePossibleLines();

				if (!game.virusExists()) {
					board.init();
					virusCount++;
					virusLevel++;
					level++;

					levelText.printText("Level " + std::to_string(level), 18, white);
					levelTextShadow.printText("Level " + std::to_string(level), 18, black);

					game.spawnVirus(virusCount, virusLevel/2);
				}

				throwAnimation.play(false, 1);

				game.createNewPiece();
				board.setCurrentPiece(game.getCurrentPiece());
			}
			
			gameTimer.start();
		}

		// Clear screen
		window.clear();

		game.drawScene();

		// Print level text
		levelTextShadow.render(75, 40);
		levelText.render(74, 39);

		throwAnimation.render(222, 81);

		// Refresh screen and cap framerate
		window.refresh();
		window.capFramerate(120);
	}

	levelTextShadow.free();
	levelText.free();

	SDL::exit();

	return 0;
}