#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level1.h"
#include "Level2.h";


#define NUM_THREADS 10


//-------------------------------------------------------------------------------------------------------------

SDL_Texture *texture = nullptr;
SDL_Window *window = nullptr;
SDL_Renderer *renderTarget = nullptr;
int frameWidth, frameHeight;
int textureWidth, textureHeight;

SDL_Event occur;


SDL_Rect camera;
SDL_Rect ai1;
SDL_Rect ai2;
SDL_Rect lives;

int p1Health = 3;
int p2Health = 3;
int lvl = 1;

Player player1;
Player player2;
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;

Structure p1Lives;
Structure p2Lives;

Level1 lv1;
Level2 lv2;

//-------------------------------------------------------------------------------------------------------------

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	return texture;
}


void LoadGame()
{
	texture = LoadTexture("background.png", renderTarget);
	camera.x = 0;
	camera.y = 0;
	camera.w = 640;
	camera.h = 480;
}

void *player1Actions(void *threadid)
{


	bool running = true;

	
	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}
		if(lvl == 1)
			lv1.go(1);
		if (lvl == 2)
			lv2.go(1);

	}

	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void *player2Actions(void *threadid)
{

	bool running = true;


	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
		}
		if (lvl == 1)
			lv1.go(2);
		if (lvl == 2)
			lv2.go(2);
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
		enemy1.Update();

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
		enemy2.Update();

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

	/*

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

	*/
}

void DrawScreen()
{

	SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 0);
	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, texture, &camera, NULL);
	p1Lives.DrawStill(renderTarget);
	p2Lives.DrawStill(renderTarget);
	if (lvl == 1) {
		lv1.Draw();
		lv1.DrawP1();
		lv1.DrawP2();
	}
	if (lvl == 2) {
		lv2.Draw();
		lv2.DrawP1();
		lv2.DrawP2();
	}
	SDL_RenderPresent(renderTarget);


}

void checkHealth()
{

	if (p1Health == 3)
		p1Lives.activateStructure(renderTarget, "threeLives.png", 0, 0, 150, 40);
	if (p1Health == 2)
		p1Lives.activateStructure(renderTarget, "twoLives.png", 0, 0, 150, 40);
	if (p1Health == 1)
		p1Lives.activateStructure(renderTarget, "oneLife.png", 0, 0, 150, 40);
	if (p1Health == 0)
		p1Lives.activateStructure(renderTarget, "dead.png", 0, 0, 150, 40);

	if (p2Health == 3)
		p2Lives.activateStructure(renderTarget, "threeLives.png", 880, 0, 150, 40);
	if (p2Health == 2)
		p2Lives.activateStructure(renderTarget, "twoLives.png", 880, 0, 150, 40);
	if (p2Health == 1)
		p2Lives.activateStructure(renderTarget, "oneLife.png", 880, 0, 150, 40);
	if (p2Health == 0)
		p2Lives.activateStructure(renderTarget, "dead.png", 880, 0, 150, 40);
}


void go()
{

	LoadGame();
	Logic();
	
	lv1.activateLevel(renderTarget, camera);
	lv2.activateLevel(renderTarget, camera);
	bool running = true;
	SDL_Event ev;

	while (running) {

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				running = false;
		}
 
		
		checkHealth();
		DrawScreen();
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderTarget);

	texture = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	IMG_Quit();
	SDL_Quit();
}

bool mainMenu()
{
	bool play = false;
	SDL_Event ev;
	while (!play)
	{
		while (SDL_PollEvent(&ev) != 0) {
			p1Lives.activateStructure(renderTarget, "start1.png", 410, 100, 200, 100);
			SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 0);
			SDL_RenderClear(renderTarget);
			p1Lives.DrawStill(renderTarget);
			SDL_RenderPresent(renderTarget);
			if (ev.type == SDL_MOUSEBUTTONUP) {
				play = true;
			}
		}

	}


	return play;
}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1040, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	go();



	return 0;

}


