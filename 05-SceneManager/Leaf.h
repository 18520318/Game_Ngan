#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define ID_ANI_LEAF_RIGHT 110
#define ID_ANI_LEAF_LEFT 111

class CLeaf :
    public CGameObject
{
public:
    CLeaf(float x, float y);
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
};

