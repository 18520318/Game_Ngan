#include "Score.h"
#include "Mario.h"
#include "PlayScene.h"

Score::Score(float x, float y, int model) : CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	this->objType = model;
	minY = y - SCORE_EFFECT_MAX_HEIGHT;
	this->vy = -SCORE_EFFECT_SPEED;

	SetScoreMario();
}

void Score::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		isDeleted = true;
	}
	//if (isDeleted) {
		//SetScoreMario();
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Score::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Score::Render()
{
	int aniId = ID_ANI_SCORE_EFFECT_100;
	switch (objType) {
	case SCORE_100:
		aniId = ID_ANI_SCORE_EFFECT_100;
		break;
	case SCORE_200:
		aniId = ID_ANI_SCORE_EFFECT_200;
		break;
	case SCORE_400:
		aniId = ID_ANI_SCORE_EFFECT_400;
		break;
	case SCORE_800:
		aniId = ID_ANI_SCORE_EFFECT_800;
		break;
	case SCORE_1000:
		aniId = ID_ANI_SCORE_EFFECT_1000;
		break;
	case SCORE_2000:
		aniId = ID_ANI_SCORE_EFFECT_2000;
		break;
	case SCORE_4000:
		aniId = ID_ANI_SCORE_EFFECT_4000;
		break;
	case SCORE_8000:
		aniId = ID_ANI_SCORE_EFFECT_8000;
		break;
	case SCORE_1_UP:
		aniId = ID_ANI_SCORE_EFFECT_1_UP;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

int Score::SetScoreMario()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (model) {
	case SCORE_100:
		//mario->SetScore(100);
		return 100;
		break;
	case SCORE_200:
		//mario->SetScore(200);
		return 200;
		break;
	case SCORE_400:
		//mario->SetScore(400);
		return 400;
		break;
	case SCORE_800:
		//mario->SetScore(800);
		return 800;
		break;
	case SCORE_1000:
		//mario->SetScore(1000);
		return 1000;
		break;
	case SCORE_2000:
		//mario->SetScore(2000);
		return 2000;
		break;
	case SCORE_4000:
		//mario->SetScore(4000);
		return 4000;
		break;
	case SCORE_8000:
		//mario->SetScore(8000);
		return 8000;
		break;
	case SCORE_1_UP:
		//live + 1
	default:
		return 0;
		break;
	}
}
