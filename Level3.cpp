#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level3.h"
using namespace std;

Level3::Level3()
{

}

Level3::~Level3()
{

}

void Level3::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	dude2.activatePlayer(renderTarget, "player2.png", 10, 300, 3, 4, 2);
	lava.x = 0;
	lava.y = 700;
	lava.w = 5000;
	lava.h = 30;
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 550, 1800, 30);
	door = doorStructure.activateStructure(renderTarget, "door.png", 1600, 470, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", 1400, 515, 30, 30);
	KeyOrNo.activateStructure(renderTarget, "keyMini.png", 505, 0, 30, 30);
	makeEnemies();
}

void Level3::makeEnemies()
{
	int j = 700;
	for (int i = 0; i < 6; i++) {
		enemies[i].activateEnemy(renderTarget, "enemy.png", j, 75, 2);
		j += 150;
	}
}

void Level3::updateEnemies()
{
	enemies[0].moveSpeed = 7;
	enemies[0].Update(road.y);
	for (int i = 1; i < 6; i++) {
		if(enemies[i-1].positionRect.y >= enemies[i].positionRect.y + 100)
		enemies[i].moveSpeed = 7;
		enemies[i].Update(road.y);
	}
}

void Level3::DrawEnemies()
{

	for (int i = 0; i < 6; i++) {
		enemies[i].Draw(renderTarget, camera);
	}
}

void Level3::Draw()
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

void Level3::DrawP1()
{
	dude1.Draw(renderTarget, camera);
}

void Level3::DrawP2()
{
	dude2.Draw(renderTarget, camera);
}

void Level3::checkDamage(int p)
{
	if (p == 1)
	{
		if (dude1.IntersectsWith(enemies[0]) || dude1.IntersectsWith(enemies[1]) || dude1.IntersectsWith(enemies[2]) ||
			dude1.IntersectsWith(enemies[3]) || dude1.IntersectsWith(enemies[4]) || dude1.IntersectsWith(enemies[5])) {
			p1Damaged = 1;
		}
		else {
			p1BeingHit = 0;
			p1Damaged = 0;
		}
		if (p1Damaged == 1 && p1BeingHit == 0)
		{
			p1Health--;
			p1BeingHit = 1;
		}
	}
	else
	{
		if (dude2.IntersectsWith(enemies[0]) || dude2.IntersectsWith(enemies[1]) || dude2.IntersectsWith(enemies[2]) ||
			dude2.IntersectsWith(enemies[3]) || dude2.IntersectsWith(enemies[4]) || dude2.IntersectsWith(enemies[5])) {
			p2Damaged = 1;
		}
		else {
			p2BeingHit = 0;
			p2Damaged = 0;
		}
		if (p2Damaged == 1 && p2BeingHit == 0)
		{
			p2Health--;
			p2BeingHit = 1;
		}
	}
}

void Level3::go(int p)
{

	if (p == 1) {
		dude1.IntersectsWith(road);
		dude1.IntersectsWith(pin);
		dude1.Update(keys);




	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(pin);
		dude2.Update(keys);
	}


	checkDamage(p);

	if (dude1.Passes(key) || dude2.Passes(key)) {
		hasKey = true;
		SDL_SetTextureColorMod(doorStructure.texture, 255, 255, 255);
	}
	if (hasKey) {
		if (dude1.Passes(door) && dude2.Passes(door)) {
			lvl = 4;
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

void Level3::checkDeath()
{
	if (p1Health == 0 || p2Health == 0)
	{
		dude1.positionRect.x = 40;
		dude1.positionRect.y = 0;
		dude2.positionRect.x = 20;
		dude2.positionRect.y = 0;
		hasKey = false;
		p1Health = 3;
		p2Health = 3;
	}
}