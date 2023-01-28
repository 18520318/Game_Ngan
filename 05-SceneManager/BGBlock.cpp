#include "BGBlock.h"

CBGBlock::CBGBlock(float x, float y, float width, float height) :CGameObject(x, y)
{
	this->width = width;
	this->height = height;
}

void CBGBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	r = l + width;
	t = y - height / 2;
	b = t + height;
}

int CBGBlock::IsBlocking(float nx, float ny, CGameObject* target)
{
	if (ny < 0) {
		return 1;
	}
	return 0;
}
