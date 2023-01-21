#include "Mushroom.h"

Mushroom::MushRoom(float x, float y)
{
}

CMushroom::CMushroom(float x, float y) : CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CMushroom::Render()
{
	int aniId = -1;

	aniId = ID_ANI_MUSHROOM;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
