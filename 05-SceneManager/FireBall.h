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

#define FIRE_BALL_STATE_FPP_SHOOT_NEAR 400
#define FIRE_BALL_STATE_FPP_SHOOT_FAR 500
#define FIRE_BALL_DISAPPEAR 300

#define	FIRE_BALL_FPP_SHOOT_SPEED_Y 0.03f
#define FIRE_BALL_FPP_SHOOT_SPEED_X_NEAR 0.03f
#define FIRE_BALL_FPP_SHOOT_SPEED_X_FAR 0.08f

#define ADJUST_FPP_SHOOT_FIRE_BALL_HEIGHT 10

#define FIRE_BALL_BOUNCE_SPEED 0.16f

#define FIRE_BALL_DISAPPEAR_EFFECT_TIME_OUT 200

class FireBall :
    public CGameObject
{
protected:
	float ax, ay;
	int mario_dir;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
public:
	FireBall(float x, float y);
	virtual void SetState(int state);

	virtual int IsCollidable();
	virtual int IsBlocking() { return 1; }

	BOOLEAN isEnemyShoot;
	BOOLEAN isDisappear = false;
	ULONGLONG start_disappear = -1;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

