#include "Leaf.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Score.h"

CLeaf::CLeaf(float x, float y)
{
	this->x = x;
	this->y = y;

	this->ay = 0;
	this->ax = 0;

	minY = y - LEAF_MAX_HEIGHT;
	limitLeft = x;
	limitRight = x + LEAF_MAX_RIGHT;
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
	if (vx > 0) {
		aniId = ID_ANI_LEAF_RIGHT;
	}
	else {
		aniId = ID_ANI_LEAF_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		y = minY;
		isFall = true;
	}
	if (isFall) {
		vy = LEAF_GRAVITY;
		if (x <= limitLeft)
		{
			x = limitLeft;
			vx = LEAF_SPEED_X;
		}
		if (x >= limitRight)
		{
			x = limitRight;
			vx = -LEAF_SPEED_X;
		}
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

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//if (e->obj == mario) {
	//	//TODO: Score
	//	mario->obj = new Score(this->x, this->y, SCORE_1000);
	//	mario->SetLevel(MARIO_LEVEL_RACOON);
	//	mario->ListEffect.push_back(mario->obj);
	//	isDeleted = true;
	//	
	//}
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_UP:
		vy = -LEAF_SPEED_UP;
		break;
	}
}
