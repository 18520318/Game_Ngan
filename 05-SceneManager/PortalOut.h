#pragma once
#include "GameObject.h"
class PortalOut :
    public CGameObject
{
    int portal_dir;

public:
    float width;
    float height;

    PortalOut(float x, float y, float w, float h, int direction);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

