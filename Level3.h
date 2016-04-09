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
class Level3 {
private:
	Mix_Chunk *pickup;
	Mix_Chunk *nextLevel;
	SDL_Rect camera;
	SDL_Renderer *renderTarget = nullptr;

	Player dude1;
	Player dude2;

	SDL_Rect pin;
	SDL_Rect road;
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
	int p1Damaged;
	int p1BeingHit;
	int p2Damaged;
	int p2BeingHit;
	int cam;
	
public:
	Level3();
	~Level3();
	Structure example;
	void activateLevel(SDL_Renderer *renderer, SDL_Rect camera);
	void checkDamage(int p);
	void Draw();
	void DrawP1();
	void DrawP2();
	void DrawEnemies();
	void go(int p);
	void makeEnemies();
	void updateEnemies();
	Enemy enemies[6];
	void checkDeath();


};