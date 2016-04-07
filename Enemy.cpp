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
	startY = positionRect.y;
	startX = positionRect.x;
	positionRect.w = 25;
	positionRect.h = 25;
	frameWidth = positionRect.w;
	frameHeight = positionRect.h;



	isActive = true;

}

Enemy::~Enemy()
{
	SDL_DestroyTexture(texture);
}




void Enemy::Update(int end)
{
	if (type == 1) {
		if (goingRight == 1) {
			if (positionRect.x < end) {
				positionRect.x += moveSpeed;
				SDL_Delay(1);
			}
			else {
				goingLeft = 1;
				goingRight = 0;
			}
		}

		if (goingLeft == 1) {
			if (positionRect.x + positionRect.w > startX) {
				positionRect.x -= moveSpeed;
				SDL_Delay(1);
			}
			else {
				goingRight = 1;
				goingLeft = 0;
			}
		}
	}
	if (type == 2) {
		if (goingDown == 1) {
			if (positionRect.y +positionRect.h < end) {
				positionRect.y += moveSpeed;
				SDL_Delay(1);
			}
			else {
				goingUp = 1;
				goingDown = 0;
			}
		}

		if (goingUp == 1) {
			if (positionRect.y + positionRect.h > startY) {
				positionRect.y -= moveSpeed;
				SDL_Delay(1);
			}
			else {
				goingDown = 1;
				goingUp = 0;
			}
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



