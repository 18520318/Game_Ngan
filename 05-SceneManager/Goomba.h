#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.03f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_RED_WING_BBOX_HEIGHT 16
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define LIMIT_TIME_WING_WALKING 1000

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_RED_GOOMBA_WING_WALKING 5005
#define ID_RED_GOOMBA_WALKING 5003
#define ID_RED_GOOMBA_DIE 5004
#define ID_RED_GOOMBA_WING_JUMP 5006

#define GOOMBA_RED_WING_STATE_WALKING 201
#define GOOMBA_RED_WING_STATE_JUMP_LOW 202
#define GOOMBA_RED_WING_STATE_JUMP_HIGH 203

#define LIMIT_JUMP_STACK 3
#define LIMIT_LOW_JUMP 0.25f
#define LIMIT_HIGH_JUMP 0.4f

#define JUMP_LOW_SPEED 0.25f
#define JUMP_HIGH_SPEED 0.4f

#define NORMAL_GOOMBA 1
#define RED_GOOMBA	2

#define ID_ANI_GOOMBA_IS_ATTACKED 30008

#define IS_ATTACKED 900

#define GOOMBA_IS_ATTACK_SPEED_Y 0.3f
#define GOOMBA_IS_ATTACK_SPEED_X 0.05f

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;
	ULONGLONG wing_walk_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);

	BOOLEAN isOnPlatform;
	BOOLEAN isWalking = false;
	BOOLEAN isOnAir = false;

	int jumpStack = 0;
};