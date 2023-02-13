#include "HUD.h"
#include "Animation.h"
#include "Animations.h"

HUD::HUD(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HUD::Render(CMario* mario, int remainingTime)
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUD)->Render(x, y);

	_char.Draw(x - ADJUST_X_WORLD, y - ADJUST_Y_WORLD, FillNumber(std::to_string(1), NUMBER_WORLD));
	_char.Draw(x + ADJUST_X_COIN, y - ADJUST_Y_COIN, FillNumber(std::to_string(mario->GetCoin()), NUMBER_COIN));
	_char.Draw(x + ADJUST_X_TIME, y + ADJUST_Y_TIME, FillNumber(std::to_string(remainingTime), NUMBER_TIME));

	power = new PowerBar(x - ADJUST_X_POWER, y - ADJUST_Y_POWER, mario->powerMeter);
	power->Render();
	//score
	//time
	//live
}

string HUD::FillNumber(string s, UINT fillNumber)
{
	while (s.size() < fillNumber) {
		s = "0" + s;
	}
	return s;
}
