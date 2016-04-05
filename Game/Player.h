#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Enemy.h"
#include "Structure.h"

class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	SDL_Texture *texture2;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];

public:
	Player();
	~Player();
	void activatePlayer(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY, int playerNumber);

	void Update(const Uint8 *keyState);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect camera);
	bool IntersectsWith(Enemy &e);
	bool IntersectsWith(SDL_Rect &wall);
	int GetOriginX();
	int GetOriginY();
	void gravity();
	int damaged = 0;
	int lives;
	int grav;
	int playerJump;
	SDL_Rect positionRect;
	SDL_Rect healthRect;
	int upState = 0;
	int leftState = 0;
	int rightState = 0;
	int isPressed = 0;
	int oldPosition;
	int peak;
	int collide;
	int collideUp;

};