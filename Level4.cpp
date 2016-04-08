#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level4.h"

Level4::Level4()
{

}

Level4::~Level4()
{
	Mix_FreeChunk(pickup);
	Mix_FreeChunk(nextLevel);
	Mix_FreeChunk(buttonSound);
}

void Level4::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	dude2.activatePlayer(renderTarget, "player2.png", 0, 300, 3, 4, 2);
	lava.x = 0;
	lava.y = 700;
	lava.w = 5000;
	lava.h = 30;
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 550, 1850, 30);
	wall1 = wall1Structure.activateStructure(renderTarget, "wall.png", 2600, 350, 250, 30);
	wall2 = wall2Structure.activateStructure(renderTarget, "wall.png", 2000, 550, 250, 30);
	wall3 = wall3Structure.activateStructure(renderTarget, "wall.png", 1070, 430, 500, 30);
	wall4 = wall4Structure.activateStructure(renderTarget, "wallVert.png", 1320, 430, 30, 120);
	wall5 = wall5Structure.activateStructure(renderTarget, "wall.png", 2360, 465, 180, 30);
	door = doorStructure.activateStructure(renderTarget, "door.png", 2700, 270, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", 1400, 500, 30, 30);
	KeyOrNo.activateStructure(renderTarget, "keyMini.png", 505, 0, 30, 30);
	button = buttonStructure.activateStructure(renderTarget, "button.png", 900, 505, 40, 50);
	button2 = buttonStructure2.activateStructure(renderTarget, "button.png", 1200, 505, 40, 50);
	gate = gateStructure.activateStructure(renderTarget, "gate.png", 1070, 451, 100, 100);
	gateUp = gateStructure2.activateStructure(renderTarget, "gate.png", 1070, 360, 100, 100);
	gate2 = gate2Structure.activateStructure(renderTarget, "gate.png", 1475, 451, 100, 100);
	gate2Up = gate2Structure2.activateStructure(renderTarget, "gate.png", 1475, 360, 100, 100);
	pickup = Mix_LoadWAV("pickup.wav");
	nextLevel = Mix_LoadWAV("levelUp.wav");
	buttonSound = Mix_LoadWAV("gateOpen2.wav");
	makeEnemies();
}

void Level4::Draw()
{
	camera.x = dude1.GetOriginX() - 320;

	if (camera.x < 0)
		camera.x = 0;
	roadStructure.Draw(renderTarget, camera);
	wall1Structure.Draw(renderTarget, camera);
	wall2Structure.Draw(renderTarget, camera);
	wall3Structure.Draw(renderTarget, camera);
	wall4Structure.Draw(renderTarget, camera);
	wall5Structure.Draw(renderTarget, camera);
	doorStructure.Draw(renderTarget, camera);
	buttonStructure.Draw(renderTarget, camera);
	buttonStructure2.Draw(renderTarget, camera);
	if (!hasKey) {
		keyStructure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(doorStructure.texture, 255, 0, 0);
	}
	else {
		KeyOrNo.DrawStill(renderTarget);
	}
	if (!hasPressedButton) {
		gateStructure.Draw(renderTarget, camera);
		gateUp.y = 451;
		gate.y = 451;
		buttonKey1 = 0;

	}
	else {
		if (buttonKey1 == 0) {
			Mix_PlayChannel(1, buttonSound, 0);
			buttonKey1 = 1;
		}
		gateStructure2.Draw(renderTarget, camera);
		gateUp.y = 360;
		gate.y = 360;
	}

	if (!hasPressedButton2) {
		gate2Up.y = 451;
		gate2.y = 451;
		gate2Structure.Draw(renderTarget, camera);
		buttonKey2 = 0;

	}
	else {
		if (buttonKey2 == 0) {
			Mix_PlayChannel(1, buttonSound, 0);
			buttonKey2 = 1;
		}
		gate2Structure2.Draw(renderTarget, camera);
		gate2Up.y = 360;
		gate2.y = 360;
	}
}

void Level4::DrawP1()
{
	dude1.Draw(renderTarget, camera);
}

void Level4::DrawP2()
{
	dude2.Draw(renderTarget, camera);
}

void Level4::makeEnemies()
{
	enemy1.activateEnemy(renderTarget, "enemy.png", 1070, 405, 1);
	enemy1.moveSpeed = 3;

	enemy2.activateEnemy(renderTarget, "enemy.png", 2000, 525, 1);
	enemy2.moveSpeed = 2;

	enemy3.activateEnemy(renderTarget, "enemy.png", 2360, 440, 1);
	enemy3.moveSpeed = 1;
}
void Level4::updateEnemies()
{
	enemy1.Update(1570);
	enemy2.Update(2250);
	enemy3.Update(2540);
}

void Level4::DrawEnemies()
{
	enemy1.Draw(renderTarget, camera);
	enemy2.Draw(renderTarget, camera);
	enemy3.Draw(renderTarget, camera);
}

void Level4::checkDamage(int p)
{
	if (p == 1)
	{
		if (dude1.IntersectsWith(enemy1) || dude1.IntersectsWith(enemy2) || dude1.IntersectsWith(enemy3)) {
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
		if (dude2.IntersectsWith(enemy1) || dude2.IntersectsWith(enemy2) || dude2.IntersectsWith(enemy3)) {
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


void Level4::go(int p)
{

	if (p == 1) {
		dude1.IntersectsWith(road);
		dude1.IntersectsWith(wall1);
		dude1.IntersectsWith(wall2);
		dude1.IntersectsWith(wall3);
		dude1.IntersectsWith(wall4);
		dude1.IntersectsWith(pin);
		dude1.IntersectsWith(gate);
		dude1.IntersectsWith(gateUp);
		dude1.IntersectsWith(gate2);
		dude1.IntersectsWith(gate2Up);
		dude1.IntersectsWith(wall5);
		dude1.Update(keys);
	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(wall1);
		dude2.IntersectsWith(wall2);
		dude2.IntersectsWith(wall3);
		dude2.IntersectsWith(wall4);
		dude2.IntersectsWith(pin);
		dude2.IntersectsWith(gate);
		dude2.IntersectsWith(gateUp);
		dude2.IntersectsWith(gate2);
		dude2.IntersectsWith(gate2Up);
		dude2.IntersectsWith(wall5);
		dude2.Update(keys);

	}

	checkDamage(p);

	if (dude1.Passes(button) || dude2.Passes(button)) {
		hasPressedButton = true;
	}
	else {
		hasPressedButton = false;
	}

	if (dude1.Passes(button2) || dude2.Passes(button2)) {
		hasPressedButton2 = true;
	}
	else {
		hasPressedButton2 = false;
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
			lvl = 3;
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

void Level4::checkDeath()
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