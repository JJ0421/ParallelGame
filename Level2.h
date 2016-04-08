#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"


extern int p1Health;
extern int p2Health;
extern int lvl;
class Level2 {
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
	SDL_Rect wall3;
	SDL_Rect wall4;
	SDL_Rect gate;
	SDL_Rect gateUp;
	SDL_Rect key;
	SDL_Rect door;
	SDL_Rect button;
	SDL_Rect oldButton;
	SDL_Rect lava;

	Structure pinStructure;
	Structure roadStructure;
	Structure wall1Structure;
	Structure wall2Structure;
	Structure wall3Structure;
	Structure wall4Structure;
	Structure doorStructure;
	Structure keyStructure;
	Structure KeyOrNo;
	Structure buttonStructure;
	Structure gateStructure;
	Structure gateStructure2;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	int playerNumber;
	bool hasKey;
	bool hasPressedButton;
public:
	Level2();
	~Level2();
	Structure example;
	void activateLevel(SDL_Renderer *renderer, SDL_Rect camera);
	void Draw();
	void DrawP1();
	void DrawP2();
	void go(int p);
	void checkDeath();

};