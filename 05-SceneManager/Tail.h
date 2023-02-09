#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 11
#define TAIL_BBOX_HEIGHT 6

class CMario;

class CTail :
    public CGameObject
{
private:
	CMario* mario;
public:
	float width = 0.0f;
	float height = 0.0f;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	void SetWidth(float width) { this->width = width; }
	void SetHeight(float height) { this->height = height; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnCollisionWithQuestionBrick(LPGAMEOBJECT& e);
	void OnCollisionWithGoldBrick(LPGAMEOBJECT& e);
	void OnCollisionWithEnemy(LPGAMEOBJECT& e);

	CTail(CMario* mario);
};

