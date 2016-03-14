#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"


#define NUM_THREADS 10

SDL_Surface *screen;
SDL_Window *window;
SDL_Event occur;


SDL_Rect player1;
SDL_Rect player2;
SDL_Rect ai1;
SDL_Rect ai2;
SDL_Renderer* renderer = NULL;
void LoadGame() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1040, 680,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	player1.x = 200;
	player1.y = 350;
	player1.h = 20;
	player1.w = 20;

	player2.x = 785;
	player2.y = 350;
	player2.h = 20;
	player2.w = 20;

	ai1.x = 200;
	ai1.y = 100;
	ai1.h = 20;
	ai1.w = 20;

	ai2.x = 500;
	ai2.y = 100;
	ai2.h = 20;
	ai2.w = 20;
	
}

void *player1Actions(void *threadid)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	bool running = true;

	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}

		if (keys[SDL_GetScancodeFromKey(SDLK_w)]) {
			player1.y -= 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_a)]) {
			player1.x -= 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
			player1.y += 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
			player1.x += 1;
			SDL_Delay(1);
		}
	}
	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void *player2Actions(void *threadid)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	bool running = true;

	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}

		if (keys[SDL_GetScancodeFromKey(SDLK_UP)]) {
			player2.y -= 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
			player2.x -= 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
			player2.y += 1;
			SDL_Delay(1);
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
			player2.x += 1;
			SDL_Delay(1);
		}
	}

	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void *aiMove1(void *threadid)
{

	bool running = true;

	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}
		for (int i = 0; i < 750; i++) {
			ai1.x++;
			SDL_Delay(1);
		}
		for (int i = 750; i > 0; i--) {
			ai1.x--;
			SDL_Delay(1);
		}
		
	}

	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void *aiMove2(void *threadid)
{

	bool running = true;

	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}
		for (int i = 0; i < 450; i++) {
			ai2.y++;
			SDL_Delay(1);
		}
		for (int i = 450; i > 0; i--) {
			ai2.y--;
			SDL_Delay(1);
		}

	}

	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void Logic()
{
	
	pthread_t threads[NUM_THREADS];
	int rc;
	int i;	
	
	i = 0;
	rc = pthread_create(&threads[i], NULL,
		player1Actions, (void *)i);

	if (rc) {
		exit(-1);
	}

	i = 1;
	rc = pthread_create(&threads[i], NULL,
		player2Actions, (void *)i);
	if (rc) {
		exit(-1);
	}

	i = 2;
	rc = pthread_create(&threads[i], NULL,
		aiMove1, (void *)i);
	if (rc) {
		exit(-1);
	}


	i = 3;
	rc = pthread_create(&threads[i], NULL,
		aiMove2, (void *)i);
	if (rc) {
		exit(-1);
	}

}

void DrawScreen()
{
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &player1);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &player2);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &ai1);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &ai2);
	SDL_RenderPresent(renderer);

	
}



int main(int argc, char** argv) {

	LoadGame();
	Logic();
	bool running = true;

	while (running) {
		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}		
		DrawScreen();
	}
	
	SDL_Quit();
	return 0;
}