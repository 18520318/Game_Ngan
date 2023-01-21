#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define ID_ANI_MUSHROOM 105
class CMushroom :
    public CGameObject
{
protected:
	float ax;
	float ay;

public:
	CMushroom(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

