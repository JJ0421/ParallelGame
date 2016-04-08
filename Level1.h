#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "SDL/SDL_mixer.h"


extern int p1Health;
extern int p2Health;
extern int lvl;
class Level1 {
private:
	Mix_Chunk *pickup;
	Mix_Chunk *nextLevel;
	SDL_Rect camera;
	SDL_Renderer *renderTarget = nullptr;

	Player dude1;
	Player dude2;

	SDL_Rect pin;
	SDL_Rect road;
	SDL_Rect wall1;
	SDL_Rect wall2;
	SDL_Rect door;
	SDL_Rect key;
	SDL_Rect lava;


	Structure pinStructure;
	Structure roadStructure;
	Structure wall1Structure;
	Structure wall2Structure;
	Structure doorStructure;
	Structure keyStructure;
	Structure KeyOrNo;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	int playerNumber;
	bool hasKey;
public:
	Level1();
	~Level1();
	Structure example;
	void activateLevel(SDL_Renderer *renderer, SDL_Rect camera);
	void Draw();
	void DrawP1();
	void DrawP2();
	void go(int p);
	void checkDeath();

};