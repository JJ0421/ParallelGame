#include "Structure.h"
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"

Structure::Structure()
{

}


SDL_Rect Structure::activateStructure(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int w, int h)
{
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	positionRect.x = x;
	positionRect.y = y;
	positionRect.w = w;
	positionRect.h = h;
	frameWidth = positionRect.w;
	frameHeight = positionRect.h;
	return positionRect;
}




Structure::~Structure()
{
	SDL_DestroyTexture(texture);
}







void Structure::activateHealth(SDL_Renderer *renderTarget, int x, int y, int w, int h)
{
	SDL_Surface *surface = IMG_Load("threeLives.png");
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	positionRect.x = x;
	positionRect.y = y;
	positionRect.w = w;
	positionRect.h = h;
	frameWidth = positionRect.w;
	frameHeight = positionRect.h;
}


void Structure::DrawStill(SDL_Renderer *renderTarget)
{

	SDL_Rect drawingRect = { positionRect.x, positionRect.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, texture, NULL, &drawingRect);


}



void Structure::Draw(SDL_Renderer *renderTarget, SDL_Rect camera)
{
	SDL_Rect drawingRect = { positionRect.x - camera.x, positionRect.y - camera.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, texture, NULL, &drawingRect);


}



int Structure::GetOriginX() {
	return positionRect.x;
}

int Structure::GetOriginY() {
	return positionRect.y;
}


