#pragma once
#include "GameObject.h"

#define ID_ANI_SCORE_EFFECT_100 910
#define ID_ANI_SCORE_EFFECT_200 911
#define ID_ANI_SCORE_EFFECT_400 912
#define ID_ANI_SCORE_EFFECT_800 913
#define ID_ANI_SCORE_EFFECT_1000 914
#define ID_ANI_SCORE_EFFECT_2000 915
#define ID_ANI_SCORE_EFFECT_4000 916
#define ID_ANI_SCORE_EFFECT_8000 917
#define ID_ANI_SCORE_EFFECT_1_UP 918

#define SCORE_EFFECT_MAX_HEIGHT 50
#define SCORE_EFFECT_SPEED 0.1f

#define SCORE_100 1
#define SCORE_200 2
#define SCORE_400 3
#define SCORE_800 4
#define SCORE_1000 5
#define SCORE_2000 6
#define SCORE_4000 7
#define SCORE_8000 8

#define SCORE_1_UP 9

class Score :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	BOOLEAN isFinish = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	virtual void Render();

public:
	Score(float x, float y, int model);
	virtual int SetScoreMario();
};

