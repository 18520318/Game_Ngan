#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_ITEM 2
#define QUESTION_BRICK_COIN 1

#define ID_ANI_QUESTION_BRICK 102
#define ID_ANI_QUESTION_BRICK_EMPTY 103

#define QUESTION_BRICK_STATE_UP 100

#define QUESTION_BRICK_MAX_HEIGHT 10 
#define QUESTION_BRICK_SPEED_UP 0.1f
#define QUESTION_BRICK_SPEED_DOWN 0.1f

class CQuestionBrick :
    public CGameObject
{
    float ax;
    float ay;

    float minY;
    float startY;
    float startX;
public:
    BOOLEAN isEmpty = false;
    BOOLEAN isOpened = false;
    BOOLEAN isBounced = false;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
    CQuestionBrick(float x, float y, int type);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 1; }
    virtual void OnNoCollision(DWORD dt);

    virtual void SetState(int state);
    
    void Bounce();

    virtual int IsBlocking(float nx, float ny, CGameObject* target) { return 1; };
};

