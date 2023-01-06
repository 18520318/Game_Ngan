#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_ITEM 2
#define QUESTION_BRICK_COIN 1

class CQuestionBrick :
    public CGameObject
{
public:
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
    CQuestionBrick(float x, float y, int type);
};

