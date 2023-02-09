#include "Goomba.h"
#include "Mario.h"
#include "PlayScene.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	this->objType = type;
	nx = -1;
	if(type == NORMAL_GOOMBA) SetState(GOOMBA_STATE_WALKING);
	else SetState(GOOMBA_RED_WING_STATE_WALKING);

	SetType(EType::ENEMY);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		if (objType == RED_GOOMBA && state != GOOMBA_STATE_WALKING) {
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_RED_WING_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_RED_WING_BBOX_HEIGHT;
		}
		else {
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny, this)) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
		isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!checkObjectInCamera(this)) return;
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	if (objType == RED_GOOMBA && state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_WALKING) {
		if (state == GOOMBA_RED_WING_STATE_WALKING && GetTickCount64() - wing_walk_start > LIMIT_TIME_WING_WALKING && isWalking) { 
			//Low jump
			jumpStack = 0;
			wing_walk_start = -1;
			isWalking = false;
			SetState(GOOMBA_RED_WING_STATE_JUMP_LOW);
		}
		else if (!isWalking) {

			if (jumpStack == LIMIT_JUMP_STACK) { 
				//High jump
				SetState(GOOMBA_RED_WING_STATE_JUMP_HIGH);
				jumpStack = -1;
			}
			else {
				if (jumpStack == -1 && isOnPlatform) 
					//Walking
				{
					SetState(GOOMBA_RED_WING_STATE_WALKING);
				}
				else
					if (isOnPlatform && isOnAir) {
						jumpStack++;
						isOnAir = false;
						SetState(GOOMBA_RED_WING_STATE_JUMP_LOW);
					}
			}
		}
	}

	if (vy <= -LIMIT_LOW_JUMP && state == GOOMBA_RED_WING_STATE_JUMP_LOW)
	{
		vy = -LIMIT_LOW_JUMP;
		ay = GOOMBA_GRAVITY;
	}
	if (vy <= -LIMIT_HIGH_JUMP && state == GOOMBA_RED_WING_STATE_JUMP_HIGH)
	{
		vy = -LIMIT_HIGH_JUMP;
		ay = GOOMBA_GRAVITY;

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;
	if (objType == NORMAL_GOOMBA) {
		aniId = ID_ANI_GOOMBA_WALKING;
		if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED)
		{
			aniId = ID_ANI_GOOMBA_IS_ATTACKED;
		}
		if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_ANI_GOOMBA_DIE;
		}
	}
	else
	{
		aniId = ID_RED_GOOMBA_WING_WALKING;
		if (state == IS_ATTACKED)
		{
			aniId = ID_ANI_GOOMBA_IS_ATTACKED;
		}
		if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_RED_GOOMBA_DIE;
		}
		if (state == GOOMBA_STATE_WALKING) {
			aniId = ID_RED_GOOMBA_WALKING;
		}
		else if (state == GOOMBA_RED_WING_STATE_WALKING) {
			aniId = ID_RED_GOOMBA_WING_WALKING;
		}
		else if (state == GOOMBA_RED_WING_STATE_JUMP_HIGH || state == GOOMBA_RED_WING_STATE_JUMP_LOW) {
			aniId = ID_RED_GOOMBA_WING_JUMP;
		}
		else if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
			aniId = ID_ANI_GOOMBA_IS_ATTACKED;
		}
	}
	

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_RED_WING_STATE_WALKING:
			vx = nx * GOOMBA_WALKING_SPEED;
			wing_walk_start = GetTickCount64();
			isWalking = true;
			break;
		case GOOMBA_RED_WING_STATE_JUMP_LOW:
			vy = -JUMP_LOW_SPEED;
			isOnPlatform = false;
			isOnAir = true;
			break;
		case GOOMBA_RED_WING_STATE_JUMP_HIGH:
			vy = -JUMP_HIGH_SPEED;
			isOnPlatform = false;
			isOnAir = true;
			break;
		case ENEMY_STATE_IS_TAIL_ATTACKED:
		case IS_ATTACKED:
			vy = -GOOMBA_IS_ATTACK_SPEED_Y;
			vx = mario->GetDirection() * GOOMBA_IS_ATTACK_SPEED_X;
			break;
	}
}

int CGoomba::IsCollidable() {
	if (state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
		return 0;
	}
	else {
		return 1;
	}
}