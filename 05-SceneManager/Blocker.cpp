#include "Blocker.h"

Blocker::Blocker(float x, float y, int allowLeft, int allowRight, int allowBottom, int allowTop) : CGameObject(x, y) {
	this->allowLeft = allowLeft;
	this->allowRight = allowRight;
	this->allowBottom = allowBottom;
	this->allowTop = allowTop;
}

void Blocker::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLOCK_OBJ_BBOX_WIDTH / 2;
	r = l + BLOCK_OBJ_BBOX_WIDTH;
	t = y - BLOCK_OBJ_BBOX_HEIGHT / 2;
	b = t + BLOCK_OBJ_BBOX_HEIGHT;
}
