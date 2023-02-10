#pragma once
#include "Mario.h"
#include "Utils.h"
#include "Timer.h"

class CBackUp
{
public:
	static CBackUp* __instance;
	
	int live = 0;
	int score = 0;
	int level = MARIO_LEVEL_SMALL;
	int scene = 0;
	int coin = 0;
	int gameTime = 0;

	static CBackUp* GetInstance();
	void BackUpMario(CMario* mario);
	void LoadBackUp(CMario* mario);
};

