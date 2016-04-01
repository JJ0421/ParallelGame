#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Enemy
{
private:
	SDL_Texture *texture;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	int type;
	SDL_Scancode keys[3];

public:
	Enemy();
	~Enemy();
	void activateEnemy(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int i);
	void Update();
	void Draw(SDL_Renderer *renderTarget, SDL_Rect camera);
	//bool IntersectsWith(Player &p);
	int GetOriginX();
	int GetOriginY();
	SDL_Rect positionRect;
};