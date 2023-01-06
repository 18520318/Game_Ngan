#pragma once
#include "GameObject.h"

#define ID_ANI_QB_COIN 112

#define QBCOIN_BBOX_WIDTH 14
#define QBCOIN_BBOX_HEIGHT 14

class QBCoin :
    public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Render();
	QBCoin(float x, float y);
};

