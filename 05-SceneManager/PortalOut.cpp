#include "PortalOut.h"
#include "Mario.h"
#include "PlayScene.h"

PortalOut::PortalOut(float x, float y, float w, float h, int direction)
{
	this->x = x;
	this->y = y;

	this->width = w;
	this->height = h;

	this->portal_dir = direction;
}

void PortalOut::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();

	float sl, st, sr, sb, left, top, right, bottom;
	mario->GetBoundingBox(sl, st, sr, sb);

	GetBoundingBox(left, top, right, bottom);

	if (CCollision::IsOverlap(left, top, right, bottom, sl, st, sr, sb)) {
		mario->isDisable = true;
		float mx = mario->GetX();
		float my = mario->GetY();

		my += 0.7 * portal_dir;

		mario->SetPosition(mx, my);
		mario->SetVX(0);
		mario->SetVY(0);

		mario->GetBoundingBox(sl, st, sr, sb);

		if (!CCollision::IsOverlap(left, top, right, bottom, sl, st, sr, sb)) {
			mario->isDisable = false;
			mario->walkState = MarioWalkState::Idle;
			mario->direct = 1;
		}
	}
}

void PortalOut::Render()
{
	RenderBoundingBox();
}

void PortalOut::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}
