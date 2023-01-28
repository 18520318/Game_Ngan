#pragma once
#include "GameObject.h"

#define FPP_BBOX_WIDTH 16
#define FPP_BIG_BBOX_HEIGHT 33
#define FPP_SMALL_BBOX_HEIGHT 25

// BIG PIRANHA
#define ID_ANI_FPP_LEFT_TOP 500002
#define ID_ANI_FPP_LEFT_BOTTOM 500003
#define ID_ANI_FPP_LEFT_TOP_SHOOT 500004
#define ID_ANI_FPP_LEFT_BOTTOM_SHOOT 500005
#define ID_ANI_FPP_RIGHT_TOP 500006
#define ID_ANI_FPP_RIGHT_BOTTOM 500007
#define ID_ANI_FPP_RIGHT_TOP_SHOOT 500008
#define ID_ANI_FPP_RIGHT_BOTTOM_SHOOT 500009

// SMALL PIRANHA
#define ID_ANI_FPP_SMALL_LEFT_TOP 500010
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM 500011
#define ID_ANI_FPP_SMALL_LEFT_TOP_SHOOT 500012
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM_SHOOT 500013
#define ID_ANI_FPP_SMALL_RIGHT_TOP 500014
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM 500015
#define ID_ANI_FPP_SMALL_RIGHT_TOP_SHOOT 500016
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM_SHOOT 500017

// MODEL
#define FPP_BIG 1
#define FPP_SMALL 2

//DISTANCE
#define DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO 75
#define DISTANCE_SAFE_ZONE 25

// SPEED
#define FPP_SPEED 0.02f

//  POSITION OF MARIO
#define LEFT_TOP_SIDE_NEAR  1
#define LEFT_TOP_SIDE_FAR  2
#define LEFT_BOTTOM_SIDE_NEAR  3
#define LEFT_BOTTOM_SIDE_FAR  4
#define RIGHT_TOP_SIDE_NEAR  5
#define RIGHT_TOP_SIDE_FAR  6
#define RIGHT_BOTTOM_SIDE_NEAR  7
#define RIGHT_BOTTOM_SIDE_FAR 8

// TIME
#define FPP_UP_TIME_OUT 4000
#define FPP_DOWN_TIME_OUT 3000

class FirePiranhaPlant :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	float startY;
	int marioRange = 0;

public:
	FirePiranhaPlant(float x, float y, int type);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);

	bool GetSafeZone();
	void ShootFire();

	ULONGLONG down_start = -1;
	ULONGLONG up_start = -1;
	BOOLEAN isMarioSafeZone = false;
	BOOLEAN startShoot = false, startDown = false;
	BOOLEAN isBottom = false, isFar = false;

	void GetMarioRangeCurrent();

	virtual int IsBlocking(float nx, float ny, CGameObject* target);
};

