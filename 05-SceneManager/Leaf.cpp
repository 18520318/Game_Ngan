#include "Leaf.h"

CLeaf::CLeaf(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = x + LEAF_BBOX_WIDTH;
	bottom = y + LEAF_BBOX_HEIGHT;
}

void CLeaf::Render()
{
	int aniId = -1;
	aniId = ID_ANI_LEAF_RIGHT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}
