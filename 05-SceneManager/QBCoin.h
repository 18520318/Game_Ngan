#pragma once
#include "GameObject.h"

#define ID_ANI_QB_COIN 112

#define QBCOIN_BBOX_WIDTH 14
#define QBCOIN_BBOX_HEIGHT 14

#define QB_COIN_MAX_HEIGHT 50
#define QB_COIN_SPEED 0.1f
#define HEIGHT_FINISH 30

#define QB_COIN_STATE_UP 100
#define QB_COIN_STATE_DOWN 200

class QBCoin :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float heightFinish;

	BOOLEAN isFall = false;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Render();
	QBCoin(float x, float y);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);

	virtual void SetState(int state);
};

