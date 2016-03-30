#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "Player.h"


#define NUM_THREADS 10

SDL_Surface *screen;
SDL_Window *window;
SDL_Event occur;


SDL_Rect player1;
SDL_Rect player2;
SDL_Rect ai1;
SDL_Rect ai2;
SDL_Rect wall;
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
	//Player player1 = Player(200, 350, 20, 20);

	player2.x = 785;
	player2.y = 350;
	player2.h = 20;
	player2.w = 20;
	//Player player2 = Player(785, 350, 20, 20);

	ai1.x = 200;
	ai1.y = 100;
	ai1.h = 20;
	ai1.w = 20;

	ai2.x = 500;
	ai2.y = 100;
	ai2.h = 20;
	ai2.w = 20;
	
	wall.x = 100;
	wall.y = 100;
	wall.h = 250;
	wall.w = 30;
}

void *player1Actions(void *threadid)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	bool running = true;

	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		} else if (keys[SDL_GetScancodeFromKey(SDLK_w)]) {
			if(player1.y != wall.y + wall.h || player1.x > wall.x + wall.w || player1.x + player1.w < wall.x){
				player1.y -= 1;
				SDL_Delay(1);
			}
		} else if (keys[SDL_GetScancodeFromKey(SDLK_a)]) {
			if(player1.x != wall.x + wall.w || player1.y > wall.y + wall.h || player1.y + player2.h < wall.y){
				player1.x -= 1;
				SDL_Delay(1);
			}
		} else if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
			if (player1.y + player1.h != wall.y || player1.x > wall.x + wall.w || player1.x + player1.w < wall.x) {
				player1.y += 1;
				SDL_Delay(1);
			}
		} else if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
			if (player1.x + player1.h != wall.x || player1.y > wall.y + wall.h || player1.y + player2.h < wall.y) {
				player1.x += 1;
				SDL_Delay(1);
			}
		} else {
			//player1.y += 1;
			//SDL_Delay(5);
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
			if (player2.y != wall.y + wall.h || player2.x > wall.x + wall.w || player2.x + player2.w < wall.x) {
				player2.y -= 1;
				SDL_Delay(1);
			}
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
			if (player2.x != wall.x + wall.w || player2.y > wall.y + wall.h || player2.y + player2.h < wall.y) {
				player2.x -= 1;
				SDL_Delay(1);
			}
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
			if (player2.y + player2.h != wall.y || player2.x > wall.x + wall.w || player2.x + player2.w < wall.x) {
				player2.y += 1;
				SDL_Delay(1);
			}
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
			if (player2.x + player2.h != wall.x || player2.y > wall.y + wall.h || player2.y + player2.h < wall.y) {
				player2.x += 1;
				SDL_Delay(1);
			}
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
		player1Actions, (void*)i);

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
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderFillRect(renderer, &wall);
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
