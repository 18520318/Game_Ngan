#include "Mushroom.h"
#include "Mario.h"
#include "PlayScene.h"

CMushroom::CMushroom(float x, float y) : CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;

	minY = y - MUSHROOM_BBOX_HEIGHT;
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
	vy += ay * dt;
	vx += ax * dt;
	if (y <= minY)
	{
		SetState(MUSHROOM_STATE_RUN);
	}

	float sl, st, sr, sb, left, top, right, bottom;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetBoundingBox(sl, st, sr, sb);

	GetBoundingBox(left, top, right, bottom);

	if (CCollision::IsOverlap(left, top, right, bottom, sl, st, sr, sb)) {
		LPCOLLISIONEVENT e = new CCollisionEvent(0.01f, 0, -1, 0, 0, mario, this);
		OnCollisionWith(e);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int aniId = -1;

	aniId = ID_ANI_MUSHROOM;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_SPEED_UP;
		break;
	case MUSHROOM_STATE_RUN:
		vx = MUSHROOM_RUN_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (e->obj == mario) {
		//TODO: Score
		isDeleted = true;
		if (mario->GetLevel() == MARIO_LEVEL_RACOON) {
			mario->SetLive(1);
		}
		else mario->SetLevel(MARIO_LEVEL_BIG);
	}
}
