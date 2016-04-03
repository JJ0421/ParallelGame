#pragma once
#include <iostream>
#include <pthread.h>
#include "stdio.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Structure.h"
#include "Level2.h"
class Level2 {
public:
	Level2();
	~Level2();
	int playGame();
};