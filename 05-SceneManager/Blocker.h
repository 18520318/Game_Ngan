#pragma once
#include "GameObject.h"

#define BLOCK_OBJ_BBOX_WIDTH 7
#define BLOCK_OBJ_BBOX_HEIGHT 8

class Blocker :
    public CGameObject
{
public:
	int allowLeft = 0, allowRight = 0, allowBottom = 0, allowTop = 0;

	Blocker(float x, float y, int allowLeft, int allowRight, int allowBottom, int allowTop);
	virtual void Render() { }
	void Update(DWORD dt) {};
	virtual int IsBlocking() { return 0; }

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

