#pragma once
#include "GameObject.h"

#define GOLD_BRICK_BBOX_WIDTH 16
#define GOLD_BRICK_BBOX_HEIGHT 16

#define ID_ANI_GOLD_BRICK 1004
#define ID_ANI_GOLD_BRICK_EMPTY 103
#define ID_ANI_COIN_IDLE 113

#define GOLD_BRICK_MAX_HEIGHT 10 
#define GOLD_BRICK_SPEED_UP 0.1f
#define GOLD_BRICK_SPEED_DOWN 0.1f

#define GOLD_BRICK_MUSHROOM 1
#define GOLD_BRICK_P_BUTTON 2
#define GOLD_BRICK_COIN 3

#define GOLD_BRICK_STATE_UP 100
#define GOLD_BRICK_STATE_TRANSFORM_COIN 200
#define GOLD_BRICK_STATE_NORMAL 300

#define GOLD_BRICK_COIN_TIME_OUT 5000
class GoldBrick :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	float startY;
	float startX;
	BOOLEAN isTransform = false;

	BOOLEAN isBreak = false;
	// model = 1: ra nấm xanh
	// model = 2: ra P button
	// model = 3: có thể biến ra tiền
	ULONGLONG transform_start = -1;

	vector<LPGAMEOBJECT> objects;
public:
	GoldBrick(float x, float y, int model);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking(float nx, float ny, CGameObject* target) {
		return 1;
	};
	virtual int IsCollidable() { return 0; };
	virtual void OnNoCollision(DWORD dt);

	virtual void SetState(int state);
	void SetBreak(int isBreak) { this->isBreak = isBreak; }
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;
};

