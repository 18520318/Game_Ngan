#include "FireBall.h"

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BALL_BBOX_WIDTH / 2;
	top = y - FIRE_BALL_BBOX_HEIGHT / 2;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (!checkObjectInCamera(this)) {
		isDeleted = true;
	}

	if (isDisappear && GetTickCount64() - start_disappear > FIRE_BALL_DISAPPEAR_EFFECT_TIME_OUT) { // effect disappear
		start_disappear = -1;
		isDisappear = false;
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBall::Render()
{
	int aniId = FIREBALL_ANI;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void FireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void FireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0 && state == FIRE_FROM_MARIO)
	{
		vy = -FIRE_BALL_BOUNCE_SPEED;

	}
	else if (e->ny > 0) {
		ay = FIRE_GRAVITY;
	}
	else if (e->nx != 0)
	{
		SetState(FIRE_BALL_DISAPPEAR);
	}

	if (e->obj->GetType() == ENEMY) {
		e->obj->SetState(ENEMY_STATE_IS_FIRE_ATTACKED);
		SetState(FIRE_BALL_DISAPPEAR);
	}
}

int FireBall::IsCollidable()
{
	if (state == FIRE_FROM_MARIO) {
		return 1;
	}
	else
		return 0;
}

FireBall::FireBall(float x, float y):CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = FIRE_GRAVITY;
}

void FireBall::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario_dir = mario->GetCurrentDirection();//Get Mario's current direction

	switch (state)
	{
	case FIRE_FROM_MARIO:
		vx = mario_dir * FIRE_BALL_SPEED;
		break;
	case FIRE_BALL_STATE_FPP_SHOOT_NEAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_NEAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_STATE_FPP_SHOOT_FAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_FAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_DISAPPEAR:
		vx = 0;
		vy = 0;
		ay = 0;
		start_disappear = GetTickCount64();
		isDisappear = true;
		break;
	}
}

