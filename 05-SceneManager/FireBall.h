#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"

#define FIREBALL_ANI    2203
#define FIRE_BALL_BBOX_WIDTH 9
#define FIRE_BALL_BBOX_HEIGHT 7

#define FIRE_GRAVITY 0.0006f
#define FIRE_BALL_SPEED 0.15f

#define FIRE_FROM_MARIO 100
#define FIRE_FROM_ENEMY 200

class FireBall :
    public CGameObject
{
protected:
	float ax, ay;
	int mario_dir;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
public:
	FireBall(float x, float y);
	virtual void SetState(int state);
};

