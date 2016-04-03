#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"

class Structure
{
private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;

public:
	Structure();
	~Structure();
	SDL_Rect activateStructure(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int w, int h);
	void activateHealth(SDL_Renderer *renderTarget, int x, int y, int w, int h);
	void DrawStill(SDL_Renderer *renderTarget);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect camera);
	int GetOriginX();
	int GetOriginY();
	SDL_Rect positionRect;
};
