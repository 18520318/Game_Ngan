#include "Tail.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	right = left + width;
	top = y - height / 2;
	bottom = top + height;
}

void CTail::Render()
{
}
