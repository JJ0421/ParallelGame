#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level5.h"
using namespace std;
Level5::Level5()
{

}

Level5::~Level5()
{
	Mix_FreeChunk(pickup);
	Mix_FreeChunk(nextLevel);
}

void Level5::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	dude2.activatePlayer(renderTarget, "player2.png", 10, 300, 3, 4, 2);
	lava.x = 0;
	lava.y = 700;
	lava.w = 5000;
	lava.h = 30;
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 550, 150, 30);
	road2 = roadStructure2.activateStructure(renderTarget, "road.png", 1000, 550, 150, 30);
	door = doorStructure.activateStructure(renderTarget, "door.png", 1100, 470, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", -100, 400, 30, 30);
	key2 = key2Structure.activateStructure(renderTarget, "key.png", -100, 400, 30, 30);
	KeyOrNo.activateStructure(renderTarget, "keyMini.png", 505, 0, 30, 30);
	KeyOrNo2.activateStructure(renderTarget, "keyMini.png", 515, 0, 30, 30);
	pickup = Mix_LoadWAV("pickup.wav");
	pickup2 = Mix_LoadWAV("pickup.wav");
	nextLevel = Mix_LoadWAV("levelUp.wav");

	platforms[0] = platform1.activateStructure(renderTarget, "platform.png", 250, 500, 75, 30);
	platforms[1] = platform2.activateStructure(renderTarget, "platform.png", 400, 400, 75, 30);
	platforms[2] = platform3.activateStructure(renderTarget, "platform.png", 550, 300, 75, 30);
	platforms[3] = platform4.activateStructure(renderTarget, "platform.png", 700, 200, 75, 30);
	platforms[4] = platform5.activateStructure(renderTarget, "platform.png", 850, 100, 75, 30);

	platforms[5] = platform6.activateStructure(renderTarget, "platform.png", 250, 100, 75, 30);
	platforms[6] = platform7.activateStructure(renderTarget, "platform.png", 400, 200, 75, 30);
	platforms[7] = platform8.activateStructure(renderTarget, "platform.png", 700, 400, 75, 30);
	platforms[8] = platform9.activateStructure(renderTarget, "platform.png", 850, 500, 75, 30);

	SDL_SetTextureColorMod(key2Structure.texture, 125, 125, 125);
	SDL_SetTextureColorMod(KeyOrNo2.texture, 125, 125, 125);

	makeEnemies();

}

void Level5::Draw()
{
	if (keys[SDL_SCANCODE_SPACE]) {
		cam = 2;
	}

	if (keys[SDL_SCANCODE_DELETE]) {
		cam = 1;
	}

	if(cam % 2 == 0)
		camera.x = dude1.GetOriginX() - 620;
	else {
		camera.x = dude2.GetOriginX() - 620;
	}
	if (camera.x < 0)
		camera.x = 0;
	
	roadStructure.Draw(renderTarget, camera);
	roadStructure2.Draw(renderTarget, camera);
	doorStructure.Draw(renderTarget, camera);
	platform1.Draw(renderTarget, camera);
	platform2.Draw(renderTarget, camera);
	platform3.Draw(renderTarget, camera);
	platform4.Draw(renderTarget, camera);
	platform5.Draw(renderTarget, camera);
	platform6.Draw(renderTarget, camera);
	platform7.Draw(renderTarget, camera);
	platform8.Draw(renderTarget, camera);
	platform9.Draw(renderTarget, camera);

	if (!hasKey) {
		keyStructure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(doorStructure.texture, 255, 0, 0);
	}
	else {
		KeyOrNo.DrawStill(renderTarget);
	}

	if (!hasKey2) {
		key2Structure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(doorStructure.texture, 255, 0, 0);
	}
	else {
		KeyOrNo2.DrawStill(renderTarget);
	}


}

void Level5::DrawP1()
{
	dude1.Draw(renderTarget, camera);
}

void Level5::DrawP2()
{
	dude2.Draw(renderTarget, camera);
}



void Level5::makeEnemies()
{
	enemy1.moveSpeed = 3;
	enemy3.moveSpeed = 3;
	enemy4.moveSpeed = 3;
	enemy5.moveSpeed = 3;
	enemy6.moveSpeed = 3;
	enemy1.activateEnemy(renderTarget, "enemy.png", 100, 370, 1);
	enemy3.activateEnemy(renderTarget, "enemy.png", 100, 170, 1);
	enemy4.activateEnemy(renderTarget, "enemy.png", 355, 50, 2);
	enemy5.activateEnemy(renderTarget, "enemy.png", 570, 50, 2);
	enemy6.activateEnemy(renderTarget, "enemy.png", 790, 50, 2);
	
}

void Level5::updateEnemies()
{

	enemy1.Update(1100);
	enemy3.Update(1100);
	enemy4.Update(800);
	enemy5.Update(800);
	enemy6.Update(800);
}

void Level5::DrawEnemies()
{
	enemy1.Draw(renderTarget, camera);
	enemy3.Draw(renderTarget, camera);
	enemy4.Draw(renderTarget, camera);
	enemy5.Draw(renderTarget, camera);
	enemy6.Draw(renderTarget, camera);

}

void Level5::checkDamage(int p)
{
	if (p == 1)
	{
		if (dude1.IntersectsWith(enemy1) || dude1.IntersectsWith(enemy3) ||
			dude1.IntersectsWith(enemy4) || dude1.IntersectsWith(enemy5) || dude1.IntersectsWith(enemy6)) {
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
		if (dude2.IntersectsWith(enemy1) || dude2.IntersectsWith(enemy3) ||
			dude2.IntersectsWith(enemy4) || dude2.IntersectsWith(enemy5) || dude2.IntersectsWith(enemy6)) {
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

void Level5::go(int p)
{



	if (p == 1) {

		dude1.IntersectsWith(road);
		dude1.IntersectsWith(road2);
		dude1.IntersectsWith(pin);

		dude1.IntersectsWith(platforms[0]);
		if (dude1.IntersectsWith(platforms[1])) {
			key.x = 875;
			key.y = 70;
			keyStructure.positionRect.x = 875;
			keyStructure.positionRect.y = 70;
		}
		if (dude1.IntersectsWith(platforms[2])) {
			key.x = -100;
			keyStructure.positionRect.x = -100;
		}
		if (dude1.IntersectsWith(platforms[3])) {
			key.x = 425;
			key.y = 170;
			keyStructure.positionRect.x = 425;
			keyStructure.positionRect.y = 170;
		}
		if (dude1.IntersectsWith(platforms[4])) {
			key.x = 275;
			key.y = 70;
			keyStructure.positionRect.x = 275;
			keyStructure.positionRect.y = 70;
		}
		if (dude1.IntersectsWith(platforms[5])) {
			key.x = 725;
			key.y = 170;
			keyStructure.positionRect.x = 725;
			keyStructure.positionRect.y = 170;
		}
		if (dude1.IntersectsWith(platforms[6])) {
			key.x = 875;
			key.y = 470;
			keyStructure.positionRect.x = 875;
			keyStructure.positionRect.y = 470;
		}
		if (dude1.IntersectsWith(platforms[7])) {
			key.x = 875;
			key.y = 70;
			keyStructure.positionRect.x = 875;
			keyStructure.positionRect.y = 70;
		}
		dude1.IntersectsWith(platforms[8]);

		dude1.Update(keys);
	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(road2);
		dude2.IntersectsWith(pin);

		if (dude2.IntersectsWith(platforms[0])) {
			key2.x = 875;
			key2.y = 470;
			key2Structure.positionRect.x = 875;
			key2Structure.positionRect.y = 470;
		}
		dude2.IntersectsWith(platforms[1]);
		if (dude2.IntersectsWith(platforms[2])) {
			key2.x = -100;
			key2Structure.positionRect.x = -100;
		}
		dude2.IntersectsWith(platforms[3]);
		if (dude2.IntersectsWith(platforms[4])) {
			key2.x = 425;
			key2.y = 370;
			key2Structure.positionRect.x = 425;
			key2Structure.positionRect.y = 370;
		}
		dude2.IntersectsWith(platforms[5]);

		if (dude2.IntersectsWith(platforms[6])) {
			key2.x = 725;
			key2.y = 370;
			key2Structure.positionRect.x = 725;
			key2Structure.positionRect.y = 370;
		}
		if (dude2.IntersectsWith(platforms[7])) {
			key2.x = 725;
			key2.y = 170;
			key2Structure.positionRect.x = 725;
			key2Structure.positionRect.y = 170;
		}
		if (dude2.IntersectsWith(platforms[8])) {
			key2.x = 275;
			key2.y = 70;
			key2Structure.positionRect.x = 275;
			key2Structure.positionRect.y = 70;
		}
		dude2.Update(keys);
	}

	checkDamage(p);

	if (dude1.Passes(key) || dude2.Passes(key)) {
		hasKey = true;
		Mix_PlayChannel(1, pickup, 0);
		pickup = nullptr;
	}
	if (dude1.Passes(key2) || dude2.Passes(key2)) {
		hasKey2 = true;
		Mix_PlayChannel(1, pickup2, 0);
		pickup2 = nullptr;
	}

	if (hasKey && hasKey2) {

		SDL_SetTextureColorMod(doorStructure.texture, 255, 255, 255);
		if (dude1.Passes(door) && dude2.Passes(door)) {
			Mix_PlayChannel(1, nextLevel, 0);
			lvl = 0;
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

void Level5::checkDeath()
{
	if (p1Health == 0 || p2Health == 0)
	{
		dude1.positionRect.x = 40;
		dude1.positionRect.y = 0;
		dude2.positionRect.x = 20;
		dude2.positionRect.y = 0;
		key.x = -100;
		key2.x = -100;
		keyStructure.positionRect.x = -100;
		key2Structure.positionRect.x = -100;
		hasKey = false;
		hasKey2 = false;
		pickup = Mix_LoadWAV("pickup.wav");
		pickup2 = Mix_LoadWAV("pickup.wav");
		p1Health = 3;
		p2Health = 3;

	}
}