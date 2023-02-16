#include "HelpBox.h"

void HelpBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HELP_WORLD_MAP)->Render(x, y);
}
