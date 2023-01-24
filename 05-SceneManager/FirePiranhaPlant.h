#pragma once
#include "GameObject.h"

#define FPP_BBOX_WIDTH 16
#define FPP_BIG_BBOX_HEIGHT 33
#define FPP_SMALL_BBOX_HEIGHT 25

// BIG PIRANHA
#define ID_ANI_FPP_LEFT_TOP 50002
#define ID_ANI_FPP_LEFT_BOTTOM 50003
#define ID_ANI_FPP_LEFT_TOP_SHOOT 50004
#define ID_ANI_FPP_LEFT_BOTTOM_SHOOT 50005
#define ID_ANI_FPP_RIGHT_TOP 50006
#define ID_ANI_FPP_RIGHT_BOTTOM 50007
#define ID_ANI_FPP_RIGHT_TOP_SHOOT 50008
#define ID_ANI_FPP_RIGHT_BOTTOM_SHOOT 50009

// SMALL PIRANHA
#define ID_ANI_FPP_SMALL_LEFT_TOP 50010
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM 50011
#define ID_ANI_FPP_SMALL_LEFT_TOP_SHOOT 50012
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM_SHOOT 50013
#define ID_ANI_FPP_SMALL_RIGHT_TOP 50014
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM 50015
#define ID_ANI_FPP_SMALL_RIGHT_TOP_SHOOT 50016
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM_SHOOT 50017

// MODEL
#define FPP_BIG 1
#define FPP_SMALL 2

class FirePiranhaPlant :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
public:
	FirePiranhaPlant(float x, float y, int type);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

