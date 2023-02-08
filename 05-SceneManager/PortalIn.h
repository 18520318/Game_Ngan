#pragma once
#include "GameObject.h"


class PortalIn :
    public CGameObject
{
	int portal_dir; // down -> 1, up -> -1

	float cx;
	float cy;

	bool isActive;

public:
	float width;
	float height;

	PortalIn(float x, float y, float w, float h, int direction, float cx, float cy);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking(LPCOLLISIONEVENT e) { return 0; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

