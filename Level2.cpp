#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level2.h"

Level2::Level2()
{

}

Level2::~Level2()
{

}

void Level2::activateLevel(SDL_Renderer *renderer, SDL_Rect cameraRect) {
	renderTarget = renderer;
	camera = cameraRect;
	dude1.activatePlayer(renderTarget, "player1.png", 50, 300, 3, 4, 1);
	p1Health = dude1.lives;
	dude2.activatePlayer(renderTarget, "player2.png", 0, 300, 3, 4, 2);
	p2Health = dude2.lives;
	pin = pinStructure.activateStructure(renderTarget, "", 0, 0, 1, 5000);
	road = roadStructure.activateStructure(renderTarget, "road.png", 0, 450, 1500, 30);
	wall1 = wall1Structure.activateStructure(renderTarget, "wall.png", 200, 250, 250, 30);
	wall2 = wall2Structure.activateStructure(renderTarget, "wall.png", 550, 350, 250, 30);
	wall3 = wall3Structure.activateStructure(renderTarget, "wall.png", 1070, 330, 250, 30);
	wall4 = wall4Structure.activateStructure(renderTarget, "wall.png", 1320, 330, 30, 120);
	door = doorStructure.activateStructure(renderTarget, "door.png", 250, 170, 40, 80);
	key = keyStructure.activateStructure(renderTarget, "key.png", 1200, 400, 30, 30);
	KeyOrNo.activateStructure(renderTarget, "keyMini.png", 505, 0, 30, 30);
	button = buttonStructure.activateStructure(renderTarget, "button.png", 900, 405, 40, 50);
	//p1Health = dude1.lives;
	//p2Health = dude2.lives;
}

void Level2::Draw()
{
	camera.x = dude1.GetOriginX() - 320;

	if (camera.x < 0)
		camera.x = 0;
	roadStructure.Draw(renderTarget, camera);
	wall1Structure.Draw(renderTarget, camera);
	wall2Structure.Draw(renderTarget, camera);
	wall3Structure.Draw(renderTarget, camera);
	wall4Structure.Draw(renderTarget, camera);
	doorStructure.Draw(renderTarget, camera);
	if (!hasKey) {
		keyStructure.Draw(renderTarget, camera);
		SDL_SetTextureColorMod(doorStructure.texture, 255, 0, 0);
	}
	else {
		KeyOrNo.DrawStill(renderTarget);
	}
	if (!hasPressedButton) {
		buttonStructure.Draw(renderTarget, camera);
		gate = gateStructure.activateStructure(renderTarget, "gate.png", 1070, 352, 100, 100);
		gateStructure.Draw(renderTarget, camera);

	}
	else {
		buttonStructure.Draw(renderTarget, camera);
		gate = gateStructure2.activateStructure(renderTarget, "gate.png", 1070, 260, 100, 100);
		gateStructure2.Draw(renderTarget, camera);
	}
}

void Level2::DrawP1()
{
	dude1.Draw(renderTarget, camera);
}

void Level2::DrawP2()
{
	dude2.Draw(renderTarget, camera);
}


void Level2::go(int p)
{

	if (p == 1) {
		dude1.IntersectsWith(road);
		dude1.IntersectsWith(wall1);
		dude1.IntersectsWith(wall2);
		dude1.IntersectsWith(wall3);
		dude1.IntersectsWith(wall4);
		dude1.IntersectsWith(pin);
		dude1.IntersectsWith(gate);
		dude1.Update(keys);
	}
	else {
		dude2.IntersectsWith(road);
		dude2.IntersectsWith(wall1);
		dude2.IntersectsWith(wall2);
		dude1.IntersectsWith(wall3);
		dude1.IntersectsWith(wall4);
		dude2.IntersectsWith(pin);
		dude2.IntersectsWith(gate);
		dude2.Update(keys);

	}

	if (dude1.Passes(button) || dude2.Passes(button)) {
		hasPressedButton = true;
	}
	else {
		hasPressedButton = false;
	}

	if (dude1.IntersectsWith(key)) {
		hasKey = true;
		SDL_SetTextureColorMod(doorStructure.texture, 255, 255, 255);
		
	}

	if (dude2.IntersectsWith(key)) {
		hasKey = true;
		SDL_SetTextureColorMod(doorStructure.texture, 255, 255, 255);
	}

	if (hasKey) {
		key.x = -100;
		if (dude1.Passes(door) && dude2.Passes(door)) {
			dude1.positionRect.y = 0;
		}
	}





}