#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 11
#define TAIL_BBOX_HEIGHT 6

class CTail :
    public CGameObject
{
public:
	float width = 0.0f;
	float height = 0.0f;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	CTail(float x, float y) {};
};

