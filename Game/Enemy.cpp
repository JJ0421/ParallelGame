#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

Enemy::Enemy()
{

}


void Enemy::activateEnemy(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int o)
{
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	positionRect.x = x;
	positionRect.y = y;
	type = o;

	positionRect.w = 25;
	positionRect.h = 25;
	frameWidth = positionRect.w;
	frameHeight = positionRect.h;



	isActive = true;

	
	moveSpeed = 1;
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(texture);
}




void Enemy::Update()
{
	if (type == 1) {
		for (int i = 0; i < 750; i++) {
			positionRect.x++;
			SDL_Delay(1);
		}
		for (int i = 750; i > 0; i--) {
			positionRect.x--;
			SDL_Delay(1);
		}
	}
	if (type == 2) {
		for (int i = 0; i < 450; i++) {
			positionRect.y++;
			SDL_Delay(1);
		}
		for (int i = 450; i > 0; i--) {
			positionRect.y--;
			SDL_Delay(1);
		}
	}
}

void Enemy::Draw(SDL_Renderer *renderTarget, SDL_Rect camera)
{
	SDL_Rect drawingRect = { positionRect.x - camera.x, positionRect.y - camera.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, texture, NULL, &drawingRect);


}



int Enemy::GetOriginX() {
	return positionRect.x;
}

int Enemy::GetOriginY() {
	return positionRect.y;
}



