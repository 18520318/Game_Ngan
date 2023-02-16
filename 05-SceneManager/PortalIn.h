#pragma once
#include "GameObject.h"


class PortalIn :
    public CGameObject
{

	float cx;
	float cy;

	bool isActive;

public:
	float width;
	float height;

	int sceneNo;

	PortalIn(float x, float y, float w, float h, int direction, float cx, float cy, int scene);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking(LPCOLLISIONEVENT e) { return 0; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetScene() { return sceneNo; }

	float GetCX() { return cx; }
	float GetCY() { return cy; }

	int portal_dir; // down -> 1, up -> -1
};

