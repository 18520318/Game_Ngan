#include "Grass.h"

void Grass::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GRASS)->Render(x, y);
}
