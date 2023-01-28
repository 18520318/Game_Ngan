#pragma once

#include "GameObject.h"

class CBGBlock :
    public CGameObject
{
public:
	float width;
	float height;

	CBGBlock(float x, float y, float width, float height);
	void Render() {};//RenderBoundingBox(); 
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetWidth() { return width; }

	virtual int IsBlocking(float nx, float ny, CGameObject* target);
};

