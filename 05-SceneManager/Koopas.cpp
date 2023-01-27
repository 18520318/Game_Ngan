#include "Koopas.h"

#include "Utils.h"

Koopas::Koopas(float x, float y, int model) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = model;

	SetType(EType::ENEMY);
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;

	if (objType == KOOPAS_GREEN_WING) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_GREEN_WING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_GREEN_WING_LEFT;
		}
	}
	

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

int Koopas::IsCollidable()
{
	if (state == ENEMY_STATE_IS_FIRE_ATTACKED || state == ENEMY_STATE_IS_KOOPAS_ATTACKED) {
		return 0;
	}
	else {
		return 1;
	}
}

void Koopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
