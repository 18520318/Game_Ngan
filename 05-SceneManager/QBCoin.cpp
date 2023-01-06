#include "QBCoin.h"

void QBCoin::Render()
{
	int aniId = ID_ANI_QB_COIN;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

QBCoin::QBCoin(float x, float y)
{
	this->x = x;
	this->y = y;
}
