#pragma once
#include "Character.h"
#include "Mario.h"
#include "PowerBar.h"

#define ID_ANI_HUD 30012
#define HUD_HEIGHT 32
#define HUD_WIDTH 272

#define NUMBER_SCORE 7
#define NUMBER_TIME 3
#define NUMBER_WORLD 1
#define NUMBER_COIN 1
#define NUMBER_HEALTH 1

#define ADJUST_X_POWER 62
#define ADJUST_Y_POWER 3

#define ADJUST_X_COIN 20
#define ADJUST_Y_COIN 4

#define ADJUST_X_HEALTH 86
#define ADJUST_Y_HEALTH 5

#define ADJUST_X_WORLD 76
#define ADJUST_Y_WORLD 4

#define ADJUST_X_TIME 12
#define ADJUST_Y_TIME 5

#define ADJUST_X_SCORE 62
#define ADJUST_Y_SCORE 5

class HUD
{
	float x, y;
	Character _char;
	PowerBar* power;
public:
	HUD(float x, float y);
	void Render(CMario* mario, int remainingTime);

	string FillNumber(string s, UINT fillNumber);
};

