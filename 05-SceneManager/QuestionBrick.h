#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_ITEM 2
#define QUESTION_BRICK_COIN 1

#define ID_ANI_QUESTION_BRICK 102
#define ID_ANI_QUESTION_BRICK_EMPTY 103

class CQuestionBrick :
    public CGameObject
{
    BOOLEAN isEmpty = false;
public:
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
    CQuestionBrick(float x, float y, int type);
};

