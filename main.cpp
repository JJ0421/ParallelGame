#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
using namespace std;

#define NUM_THREADS 3


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


Structure p1H3;
Structure p1H2;
Structure p1H1;
Structure p1H0;

Structure p2H3;
Structure p2H2;
Structure p2H1;
Structure p2H0;

Structure startStructure;

Level1 lv1;
Level2 lv2;
Level3 lv3;
Level4 lv4;
Mix_Music *bgm;
Mix_Chunk *hover;
Mix_Chunk *select;


bool playing = true;
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

	p1H3.activateStructure(renderTarget, "threeLives.png", 0, 0, 150, 40);
	p1H2.activateStructure(renderTarget, "twoLives.png", 0, 0, 150, 40);
	p1H1.activateStructure(renderTarget, "oneLife.png", 0, 0, 150, 40);
	p1H0.activateStructure(renderTarget, "dead.png", 0, 0, 150, 40);
	p2H3.activateStructure(renderTarget, "threeLives.png", 1000, 0, 150, 40);
	p2H2.activateStructure(renderTarget, "twoLives.png", 1000, 0, 150, 40);
	p2H1.activateStructure(renderTarget, "oneLife.png", 1000, 0, 150, 40);
	p2H0.activateStructure(renderTarget, "dead.png", 1000, 0, 150, 40);
	bgm = Mix_LoadMUS("bgm.wav");

}

void *player1Actions(void *threadid)
{


	bool running = true;

	
	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
			playing = false;
		}
		if(lvl == 1)
			lv1.go(1);
		if (lvl == 2)
			lv2.go(1);
		if (lvl == 3)
			lv3.go(1);
		if (lvl == 4)
			lv4.go(1);

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
			playing = false;
		}
		if (lvl == 1)
			lv1.go(2);
		if (lvl == 2)
			lv2.go(2);
		if (lvl == 3)
			lv3.go(2);
		if (lvl == 4)
			lv4.go(2);
	}

	pthread_exit(NULL);
	SDL_Quit();
	return 0;
}

void *enemyActions(void *threadid)
{

	bool running = true;
	while (running) {

		SDL_PollEvent(&occur);
		if (occur.type == SDL_QUIT) {
			running = false;
			playing = false;
		}
		if (lvl == 3)
			lv3.updateEnemies();
		if (lvl == 4)
			lv4.updateEnemies();

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
	enemyActions, (void *)i);
	if (rc) {
		exit(-1);
	}


}

void DrawHealth()
{
	if (p1Health == 3)
		p1H3.DrawStill(renderTarget);
	if (p1Health == 2)
		p1H2.DrawStill(renderTarget);
	if (p1Health == 1)
		p1H1.DrawStill(renderTarget);
	if (p1Health <= 0) {
		p1H0.DrawStill(renderTarget);
		SDL_Delay(100);
	}

	if (p2Health == 3)
		p2H3.DrawStill(renderTarget);
	if (p2Health == 2)
		p2H2.DrawStill(renderTarget);
	if (p2Health == 1)
		p2H1.DrawStill(renderTarget);
	if (p2Health <= 0) {
		p2H0.DrawStill(renderTarget);
		SDL_Delay(100);
	}
}

void DrawScreen()
{

	SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 0);
	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, texture, &camera, NULL);
	DrawHealth();
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
	if (lvl == 3) {
		lv3.Draw();
		lv3.DrawP1();
		lv3.DrawP2();
		lv3.DrawEnemies();
	}
	if (lvl == 4) {
		lv4.Draw();
		lv4.DrawP1();
		lv4.DrawP2();
		lv4.DrawEnemies();
	}
	SDL_RenderPresent(renderTarget);


}




void go()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	LoadGame();
	Logic();
	
	lv1.activateLevel(renderTarget, camera);
	lv2.activateLevel(renderTarget, camera);
	lv3.activateLevel(renderTarget, camera);
	lv4.activateLevel(renderTarget, camera);
	bool running = true;
	SDL_Event ev;

	while (playing) {

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT) {
				running = false;
				playing = false;
			}
		}
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(bgm, -1);

		DrawScreen();
		if (keyState[SDL_SCANCODE_ESCAPE])
			playing = false;
	}
}

bool mainMenu()
{
	bool play = false;
	SDL_Event ev;
	startStructure.activateStructure(renderTarget, "start1.png", 480, 100, 200, 100);
	hover = Mix_LoadWAV("hover.wav");
	select = Mix_LoadWAV("select.wav");
	int hovering = 0;
	while (play == false)
	{
		while (SDL_PollEvent(&ev) != 0) {

			SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 0);
			SDL_RenderClear(renderTarget);
			startStructure.DrawStill(renderTarget);
			SDL_RenderPresent(renderTarget);

			if (ev.type) {
				SDL_SetTextureColorMod(startStructure.texture, 255, 255, 255);
				if (ev.type == SDL_QUIT) {
					SDL_DestroyWindow(window);
					SDL_DestroyTexture(texture);
					SDL_DestroyRenderer(renderTarget);

					return false;
				}

				if (ev.type == SDL_MOUSEMOTION) {
					if (ev.button.x >= 480 && ev.button.x <= 680 && ev.button.y >= 100 && ev.button.y <= 200) {
						SDL_SetTextureColorMod(startStructure.texture, 255, 0, 0);
						if(hovering == 0)
							Mix_PlayChannel(1, hover, 0);
						hovering = 1;
					}
					else {
						hovering = 0;
					}
				}
				if (ev.button.x >= 480 && ev.button.x <= 680 && ev.button.y >= 100 && ev.button.y <= 200 && ev.type == SDL_MOUSEBUTTONUP) {
					SDL_SetTextureColorMod(startStructure.texture, 255, 0, 0);
					play = true;
				}
			}
		}

	}
	Mix_PlayChannel(1, select, 0);
	return play;
}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1150, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	if (mainMenu() == true) {
		go();
	}

	texture = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	bgm = nullptr;
	hover = nullptr;
	select = nullptr;
	Mix_FreeMusic(bgm);
	Mix_FreeChunk(hover);
	Mix_FreeChunk(select);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderTarget);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;

}


