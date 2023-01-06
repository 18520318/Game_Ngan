#include "Tail.h"
#include "QuestionBrick.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	right = left + width;
	top = y - height / 2;
	bottom = top + height;
}

void CTail::Render()
{
	RenderBoundingBox();
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}
