#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

Player::Player()
{
}


void Player::activatePlayer(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY,int playerNumber)
{
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	lives = 3;

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;
	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	positionRect.w = 30;
	positionRect.h = 30;

	isActive = false;

	if (playerNumber == 1)
	{
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_A;
		keys[2] = SDL_SCANCODE_D;
	}
	else {
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_LEFT;
		keys[2] = SDL_SCANCODE_RIGHT;
	}

	playerJump = 150;
	grav = 1;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}


void Player::gravity()
{
	positionRect.y++;
	SDL_Delay(1);

}


void Player::Update(float delta, const Uint8 *keyState)
{
	int speed = 1;
	isActive = true;
	if (keyState[keys[0]] && isPressed == 0)
	{
		isPressed = 1;
		oldPosition = positionRect.y;
		cropRect.y = frameHeight * 3;
		positionRect.y -= 3;
		peak = oldPosition - 150;
		upState = 1;
		
	}
	else {
		upState = 0;
	}
	
	if (isPressed == 1) {
		if (positionRect.y > peak && collideUp != 1) {
			positionRect.y -= 3;
			collide = 0;
		}
		else
			isPressed = 2;
	}



	if (positionRect.y == oldPosition && collide == 1)
		isPressed = 0;
	



	if (keyState[keys[1]])
	{
		positionRect.x -= speed;
		cropRect.y = frameHeight;
		SDL_Delay(1);
		leftState = 1;
	}
	else {
		leftState = 0;
	}
	if (keyState[keys[2]])
	{
		positionRect.x += speed;
		cropRect.y = frameHeight * 2;
		SDL_Delay(1);
		rightState = 1;
	}
	else {
		rightState = 0;
	}
	if (keyState[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
		positionRect.y += speed;
		cropRect.y = 0;
		SDL_Delay(1);
	}

	else {
		isActive = false;
		gravity();
	}

	
	
	if (isActive)
	{
		frameCounter += delta;
	
		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
		}
	}
	else {
		frameCounter = 0;
		cropRect.x = frameWidth;

	}

}

void Player::Draw(SDL_Renderer *renderTarget, SDL_Rect camera)
{
	SDL_Rect drawingRect = { positionRect.x - camera.x, positionRect.y - camera.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect);

	
}


bool Player::IntersectsWith(Enemy &e)
{
	if (positionRect.x + positionRect.w < e.positionRect.x || positionRect.x > e.positionRect.x + e.positionRect.w
		|| positionRect.y + positionRect.h < e.positionRect.y || positionRect.y > e.positionRect.y + e.positionRect.h)
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	}


	if ((positionRect.x + positionRect.w) == e.positionRect.x) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		SDL_Delay(3);
		damaged = 1;
		return true;
	}
	if (positionRect.x == e.positionRect.x + e.positionRect.w) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		SDL_Delay(3);
		damaged = 1;
		return true;
	}
	if (positionRect.y + positionRect.h == e.positionRect.y) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		SDL_Delay(3);
		damaged = 1;
		return true;
	}
	if (positionRect.y == e.positionRect.y + e.positionRect.h) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		SDL_Delay(3);
		damaged = 1;
		return true;
	}
	if (damaged == 1) {
		lives--;
		if (lives == 0)
			positionRect.x = 0;
		damaged = 0;
	}

}

bool Player::IntersectsWith(SDL_Rect &wall)
{
	pWall = wall;
	if (positionRect.x + positionRect.w < wall.x || positionRect.x > wall.x + wall.w
		|| positionRect.y + positionRect.h < wall.y || positionRect.y > wall.y + wall.h)
	{		
		return false;
	}

	if ((positionRect.x + positionRect.w) == wall.x) {
		positionRect.x--;
		collide = 1;
		return true;
	}
	if (positionRect.x == wall.x + wall.w) {
		positionRect.x++;
		collide = 1;
		return true;
	}

	if (isPressed == 1) {
		if (positionRect.y < wall.y + wall.h) {
			positionRect.y = wall.y + wall.h + 1;
			collideUp = 1;
			return true;
		}
	}


		if (positionRect.y + positionRect.h == wall.y) {
			positionRect.y--;
			collide = 1;
			collideUp = 0;
			oldPosition = positionRect.y;
			return true;
		}
	


}

int Player::GetOriginX() {
	return positionRect.x;
}

int Player::GetOriginY() {
	return positionRect.y;
}







