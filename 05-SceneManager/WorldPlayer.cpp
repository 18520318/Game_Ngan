#include "WorldPlayer.h"
#include "Backup.h"
#include "Door.h"
#include "Blocker.h"


WorldPlayer::WorldPlayer(float x, float y) : CGameObject()
{
	SetState(MARIO_WORLD_MAP_STATE_IDLE);
	this->x = x;
	this->y = y;
	this->ay = 0;
	this->ax = 0;
	this->level = CBackUp::GetInstance()->level;
}

void WorldPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_S)) {
		if (sceneSwitch != -1 && sceneSwitch != 0) {
			CGame::GetInstance()->InitiateSwitchScene(MAIN_SCENE_ID);
			sceneSwitch = -1;
		}
	}

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (allowRight) {
			SetState(MARIO_WORLD_MAP_STATE_WALK_RIGHT);
			allowLeft = false;
			allowRight = false;
			allowTop = false;
			allowBottom = false;
		}
	}
	if (game->IsKeyDown(DIK_LEFT)) {
		if (allowLeft) {
			SetState(MARIO_WORLD_MAP_STATE_WALK_LEFT);
			allowLeft = false;
			allowRight = false;
			allowTop = false;
			allowBottom = false;
		}
	}
	if (game->IsKeyDown(DIK_UP)) {
		if (allowTop) {
			SetState(MARIO_WORLD_MAP_STATE_WALK_TOP);
			allowLeft = false;
			allowRight = false;
			allowTop = false;
			allowBottom = false;
		}
	}
	if (game->IsKeyDown(DIK_DOWN)) {
		if (allowBottom) {
			SetState(MARIO_WORLD_MAP_STATE_WALK_BOTTOM);
			allowLeft = false;
			allowRight = false;
			allowTop = false;
			allowBottom = false;
		}
	}

	if (game->IsKeyDown(DIK_1)) {
		SetLevel(MARIO_LEVEL_SMALL);
	}
	if (game->IsKeyDown(DIK_2)) {
		SetLevel(MARIO_LEVEL_BIG);
	}
	if (game->IsKeyDown(DIK_3)) {
		SetLevel(MARIO_LEVEL_RACOON);
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void WorldPlayer::Render()
{
	int ani = ID_ANI_MARIO_SMALL_IN_WORLD_MAP;

	switch (level) {
		case MARIO_LEVEL_SMALL: {
			ani = ID_ANI_MARIO_SMALL_IN_WORLD_MAP;
			break;
		}
		case MARIO_LEVEL_BIG:
		{
			ani = ID_ANI_MARIO_IN_WORLD_MAP;
			break;
		}
		case MARIO_LEVEL_RACOON:
		{
			ani = ID_ANI_MARIO_RACCOON_IN_WORLD_MAP;
			break;
		}
	}

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void WorldPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_WORLD_MAP_BBOX_WIDTH / 2; top = y - MARIO_WORLD_MAP_BBOX_WIDTH / 2; right = left + MARIO_WORLD_MAP_BBOX_HEIGHT; bottom = top + MARIO_WORLD_MAP_BBOX_HEIGHT;
}

void WorldPlayer::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void WorldPlayer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<Blocker*>(e->obj))
		OnCollisionWithBlocker(e);
	if (dynamic_cast<Door*>(e->obj))
		OnCollisionWithDoor(e);
}

void WorldPlayer::OnCollisionWithDoor(LPCOLLISIONEVENT e)
{
	Door* door = dynamic_cast<Door*>(e->obj);
	sceneSwitch = door->GetScene();
}

void WorldPlayer::OnCollisionWithBlocker(LPCOLLISIONEVENT e)
{

	Blocker* block = dynamic_cast<Blocker*>(e->obj);
	vx = 0;
	vy = 0;
	allowLeft = block->allowLeft;
	allowRight = block->allowRight;
	allowBottom = block->allowBottom;
	allowTop = block->allowTop;
	if (e->nx != 0) {
		x = x - e->nx * MARIO_WORLD_MAP_BBOX_WIDTH;
	}
	if (e->ny != 0) {
		y = y - e->ny * MARIO_WORLD_MAP_BBOX_WIDTH;
	}
}

void WorldPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MARIO_WORLD_MAP_STATE_IDLE:
		{
			vx = vy = 0;
			break;
		}
		case MARIO_WORLD_MAP_STATE_WALK_RIGHT:
		{
			vx = MARIO_WORLD_MAP_SPEED;
			vy = 0;
			break;
		}
		case MARIO_WORLD_MAP_STATE_WALK_LEFT:
		{
			vx = -MARIO_WORLD_MAP_SPEED;
			vy = 0;
			break;
		}
		case MARIO_WORLD_MAP_STATE_WALK_TOP:
		{
			vx = 0;
			vy = -MARIO_WORLD_MAP_SPEED;
			break;
		}
		case MARIO_WORLD_MAP_STATE_WALK_BOTTOM:
		{
			vx = 0;
			vy = MARIO_WORLD_MAP_SPEED;
			break;
		}
	}
}
