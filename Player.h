#pragma once
#include "SDL/SDL.h"

using namespace std;
class Player
{
	int xPos;
	int yPos;
	int width;
	int height;

public:
	Player();
	Player(int x, int y, int w, int h);
	void Actions();
};

Player::Player() {

}

Player::Player(int x, int y, int w, int h) {
	xPos = x;
	yPos = y;
	width = w;
	height = h;
}

void Player::Actions()
{
	//const Uint8 *keys = SDL_GetKeyboardState(NULL);

	//bool running = true;

	//while (running) {

	//	SDL_PollEvent(&occur);
	//	if (occur.type == SDL_QUIT) {
	//		running = false;
	//	}
	//	else if (keys[SDL_GetScancodeFromKey(SDLK_w)]) {
	//		yPos -= 1;
	//		SDL_Delay(1);
	//	}
	//	else if (keys[SDL_GetScancodeFromKey(SDLK_a)]) {
	//		xPos -= 1;
	//		SDL_Delay(1);
	//	}
	//	else if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
	//		yPos += 1;
	//		SDL_Delay(1);
	//	}
	//	else if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
	//		xPos += 1;
	//		SDL_Delay(1);
	//	}
	//	else {
	//		yPos += 1;
	//		SDL_Delay(5);
	//	}

	//}
	//pthread_exit(NULL);
	//SDL_Quit();
}