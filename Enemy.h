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
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	int type;
	SDL_Scancode keys[3];
	int goingRight = 1;
	int goingLeft = 0;
	int startX;
	int goingDown = 1;
	int goingUp = 0;
	int startY;

public:
	Enemy();
	~Enemy();
	void activateEnemy(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int i);
	void Update(int end);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect camera);
	int GetOriginX();
	int GetOriginY();
	SDL_Rect positionRect;
	int moveSpeed;
};