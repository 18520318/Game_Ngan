#include "Tail.h"
#include "QuestionBrick.h"
#include "Mario.h"
#include "PlayScene.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x-8;
	right = x + 24;
	top = y;
	bottom = y + 5;
}

void CTail::Render()
{
	//RenderBoundingBox();
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->x = this->mario->GetX();
	this->y = this->mario->GetY() + 6;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i))) {
			if (dynamic_cast<CQuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQuestionBrick(coObjects->at(i));
		}
		
	}
}

void CTail::OnCollisionWithQuestionBrick(LPGAMEOBJECT& e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e);
	if (!questionBrick->isEmpty) {
		questionBrick->Bounce();
	}
}

CTail::CTail(CMario* mario)
{
	this->mario = mario;
}
