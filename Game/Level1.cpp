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

}

void Level1::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	dude2.activatePlayer(renderTarget, "player2.png", 0, 300, 3, 4, 2);
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 450, 1500, 30);
	wall1 = wall1Structure.activateStructure(renderTarget, "wall.png", 400, 350, 250, 30);
	wall2 = wall2Structure.activateStructure(renderTarget, "wall.png", 750, 300, 250, 30);
	gate = gateStructure.activateStructure(renderTarget, "door.png", 870, 223, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", 500, 300, 30, 30);
}

void Level1::Draw()
{
	camera.x = dude1.GetOriginX() - 320;

	if (camera.x < 0)
		camera.x = 0;
	roadStructure.Draw(renderTarget, camera);
	wall1Structure.Draw(renderTarget, camera);
	wall2Structure.Draw(renderTarget, camera);
	gateStructure.Draw(renderTarget, camera);
	if (!hasKey) {
		keyStructure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(gateStructure.texture, 255, 0, 0);
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
		dude1.IntersectsWith(gate);
		dude1.IntersectsWith(pin);
		dude1.Update(keys);
		p1Health = dude1.lives;
	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(wall1);
		dude2.IntersectsWith(wall2);
		dude2.IntersectsWith(gate);
		dude2.Update(keys);
		dude2.IntersectsWith(pin);
		p2Health = dude2.lives;
	}

	if (dude1.IntersectsWith(key)) {
		hasKey = true;
		SDL_SetTextureColorMod(gateStructure.texture, 255, 255, 255);
	}
	if (hasKey) {
		key.x = -100;
		if (dude1.IntersectsWith(gate)) {
			dude1.positionRect.y = 0;
		}
	}

	if (dude2.IntersectsWith(key)) {
		hasKey = true;
		SDL_SetTextureColorMod(gateStructure.texture, 255, 255, 255);
	}
	if (hasKey) {
		key.x = -100;
		if (dude2.IntersectsWith(gate)) {
			dude2.positionRect.y = 0;
		}
	}

}