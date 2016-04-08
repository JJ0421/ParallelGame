#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level1.h"

Level1::Level1()
{

}

Level1::~Level1()
{
	Mix_FreeChunk(pickup);
	Mix_FreeChunk(nextLevel);
}

void Level1::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	dude2.activatePlayer(renderTarget, "player2.png", 10, 300, 3, 4, 2);
	lava.x = 0;
	lava.y = 700;
	lava.w = 5000;
	lava.h = 30;
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 550, 1500, 30);
	wall1 = wall1Structure.activateStructure(renderTarget, "wall.png", 400, 450, 250, 30);
	wall2 = wall2Structure.activateStructure(renderTarget, "wall.png", 750, 400, 250, 30);
	door = doorStructure.activateStructure(renderTarget, "door.png", 870, 323, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", 500, 400, 30, 30);
	KeyOrNo.activateStructure(renderTarget, "keyMini.png", 505, 0, 30, 30);
	pickup = Mix_LoadWAV("pickup.wav");
	nextLevel = Mix_LoadWAV("levelUp.wav");
}

void Level1::Draw()
{
	camera.x = dude1.GetOriginX() - 620;
	if (camera.x < 0)
		camera.x = 0;

	
	roadStructure.Draw(renderTarget, camera);
	wall1Structure.Draw(renderTarget, camera);
	wall2Structure.Draw(renderTarget, camera);
	doorStructure.Draw(renderTarget, camera);
	if (!hasKey) {
		keyStructure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(doorStructure.texture, 255, 0, 0);
	}
	else {
		KeyOrNo.DrawStill(renderTarget);
	}
}

void Level1::DrawP1()
{
	dude1.Draw(renderTarget, camera);
}

void Level1::DrawP2()
{
	dude2.Draw(renderTarget, camera);
}


void Level1::go(int p)
{

	if (p == 1) {
		dude1.IntersectsWith(road);
		dude1.IntersectsWith(wall1);
		dude1.IntersectsWith(wall2);
		dude1.IntersectsWith(pin);
		dude1.Update(keys);
	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(wall1);
		dude2.IntersectsWith(wall2);
		dude2.IntersectsWith(pin);
		dude2.Update(keys);
	}

	if (dude1.Passes(key) || dude2.Passes(key)) {
		hasKey = true;
		Mix_PlayChannel(1, pickup, 0);
		pickup = nullptr;
		SDL_SetTextureColorMod(doorStructure.texture, 255, 255, 255);
	}
	if (hasKey) {
		if (dude1.Passes(door) && dude2.Passes(door)) {
			Mix_PlayChannel(1, nextLevel, 0);
			lvl = 2;
		}
	}

	if (dude1.Passes(lava)) {
		p1Health = 0;
	}

	if (dude2.Passes(lava)) {
		p2Health = 0;
	}

	checkDeath();
}

void Level1::checkDeath()
{
	if (p1Health == 0 || p2Health == 0)
	{
		dude1.positionRect.x = 40;
		dude1.positionRect.y = 0;
		dude2.positionRect.x = 20;
		dude2.positionRect.y = 0;
		hasKey = false;
		pickup = Mix_LoadWAV("pickup.wav");
		p1Health = 3;
		p2Health = 3;

	}
}