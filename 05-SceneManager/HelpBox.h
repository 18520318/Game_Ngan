#pragma once
#include "GameObject.h"

#define ID_ANI_HELP_WORLD_MAP 111

class HelpBox :
    public CGameObject
{
public:
	HelpBox(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; }
};

