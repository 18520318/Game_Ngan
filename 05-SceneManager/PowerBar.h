#pragma once
#include "GameObject.h"

#define POWER_ANI_ID 301
#define POWER_MAX_ANI_ID 302
#define POWER_WIDTH 8
#define SPACE_BETWEEN_POWER_AND_MAX 5

#define ARROW_POSITION_Y_LIST {0, 8, 16, 24, 32, 40}
#define LENGTH_ARROW    6

class PowerBar :
    public CGameObject
{
    float x, y;
    int stack;

    float posX[LENGTH_ARROW] = ARROW_POSITION_Y_LIST;
public:
    PowerBar(float x, float y, int stack);

    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};

