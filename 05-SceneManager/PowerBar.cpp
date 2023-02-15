#include "PowerBar.h"
#include "Mario.h"

PowerBar::PowerBar(float x, float y, int stack)
{
	this->x = x;
	this->y = y;
	this->stack = stack;
}

void PowerBar::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	for (int i = 0; i < stack; i++) {
		if (i == MARIO_POWER_FULL - 1) {
			animations->Get(POWER_MAX_ANI_ID)->Render(x + i * POWER_WIDTH + SPACE_BETWEEN_POWER_AND_MAX, y);
		}
		else {
			//animations->Get(POWER_ANI_ID)->Render(x + i * POWER_WIDTH, y);
			animations->Get(POWER_ANI_ID)->Render(x + posX[i], y);
		}
	}
}
