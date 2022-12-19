#include "FireBall.h"

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BALL_BBOX_WIDTH / 2;
	top = y - FIRE_BALL_BBOX_HEIGHT / 2;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void FireBall::Render()
{
	int aniId = FIREBALL_ANI;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void FireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void FireBall::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario_dir = mario->GetCurrentDirection();//Get Mario's current direction

	if (state == FIRE_FROM_MARIO) {
		vx = mario_dir * FIRE_BALL_SPEED;
	}
}

FireBall::FireBall(float x, float y):CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = FIRE_GRAVITY;
}
