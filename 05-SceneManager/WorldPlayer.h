#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MARIO_WORLD_MAP_BBOX_WIDTH 8
#define MARIO_WORLD_MAP_BBOX_HEIGHT 8

class WorldPlayer :
    public CGameObject
{
    int level;
    float ax;
    float ay;

public:
    int allowLeft = 0, allowRight = 1, allowBottom = 0, allowTop = 0;
    WorldPlayer(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
	void OnCollisionWithBlocker(LPCOLLISIONEVENT e);

	void SetState(int state);
	void SetLevel(int l) { level = l; };

	BOOLEAN isReadySwitchScene = false;

	int sceneSwitch = -1;
};

