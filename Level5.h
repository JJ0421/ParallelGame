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
class Level5 {
private:
	Mix_Chunk *pickup;
	Mix_Chunk *pickup2;
	Mix_Chunk *nextLevel;
	SDL_Rect camera;
	SDL_Renderer *renderTarget = nullptr;

	Player dude1;
	Player dude2;

	Enemy enemy1;
	Enemy enemy3;
	Enemy enemy4;
	Enemy enemy5;
	Enemy enemy6;

	SDL_Rect pin;
	SDL_Rect road;
	SDL_Rect road2;
	SDL_Rect platforms[9];
	SDL_Rect door;
	SDL_Rect key;
	SDL_Rect key2;
	SDL_Rect lava;


	Structure pinStructure;
	Structure roadStructure;
	Structure roadStructure2;
	Structure doorStructure;
	Structure keyStructure;
	Structure key2Structure;
	Structure KeyOrNo;
	Structure KeyOrNo2;
	Structure platform1;
	Structure platform2;
	Structure platform3;
	Structure platform4;
	Structure platform5;
	Structure platform6;
	Structure platform7;
	Structure platform8;
	Structure platform9;
	Structure platform10;
	Structure platform11;
	Structure platform12;
	Structure platform13;
	

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	int playerNumber;
	bool hasKey;
	bool hasKey2;
	int cam;
	int isPressed = 0;
	int timer = 0;
	int p1Damaged;
	int p1BeingHit;
	int p2Damaged;
	int p2BeingHit;
	SDL_Event ev;
public:
	Level5();
	~Level5();
	Structure example;
	void activateLevel(SDL_Renderer *renderer, SDL_Rect camera);
	void Draw();
	void DrawP1();
	void DrawP2();
	void go(int p);
	void checkDeath();
	void makeEnemies();
	void updateEnemies();
	void DrawEnemies();
	void checkDamage(int p);

};