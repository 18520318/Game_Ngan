#include "QuestionBrick.h"
#include "Brick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Leaf.h"
#include "QBCoin.h"
#include "Mushroom.h"

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Render()
{
	int aniId = ID_ANI_QUESTION_BRICK;

	if (isEmpty) {
		aniId = ID_ANI_QUESTION_BRICK_EMPTY;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

CQuestionBrick::CQuestionBrick(float x, float y, int type)
{
	this->objType = type;

	this->ay = 0;
	this->ax = 0;
	this->minY = y - QUESTION_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		vy = QUESTION_BRICK_SPEED_DOWN;

	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		isEmpty = true;
		isOpened = true;
	}

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (isOpened) {
		if (objType == QUESTION_BRICK_ITEM) {
			if (mario->GetLevel() == MARIO_LEVEL_BIG) {
				CLeaf* leaf = new CLeaf(x, y);
				leaf->SetState(LEAF_STATE_UP);
				scene->objects.push_back(leaf);//insert(scene->objects.begin() + 1, leaf);
			}
			if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
				CMushroom* mushroom = new CMushroom(x, y);
				mushroom->SetState(MUSHROOM_STATE_UP);
				scene->objects.insert(scene->objects.begin() + 1, mushroom);//push_back(mushroom);
			}
		}
		else {
			QBCoin* coin = new QBCoin(x, y);
			coin->SetState(QB_COIN_STATE_UP);
			scene->objects.insert(scene->objects.begin() + 1, coin);
			mario->SetCoin(mario->GetCoin() + 1);
		}
		isOpened = false;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_UP:
		vy = -QUESTION_BRICK_SPEED_UP;
		break;
	}
}

void CQuestionBrick::Bounce()
{
	if (this->isBounced) {
		return;
	}
	this->isBounced = true;
	this->SetState(QUESTION_BRICK_STATE_UP);
}
