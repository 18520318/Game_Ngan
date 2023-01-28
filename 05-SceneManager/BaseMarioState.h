#pragma once
#include "debug.h"
#include "Utils.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CMario;

class BaseMarioState
{
protected:
	CMario* mario;
public:
	BaseMarioState(CMario* mario);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void WalkUpdate(DWORD dt);

	virtual void JumpUpdate(DWORD dt);

	virtual void holdingShellUpdate(DWORD dt);

	virtual void warpUpdate(DWORD dt);

	virtual void Render() = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	float MARIO_MIN_JUMP_HEIGHT = 80 / 3;
	float MARIO_JUMP_HEIGHT = 97 / 3;
	float MARIO_PUSH_FORCE = 0.432f / 3;

	float MARIO_MIN_HIGH_JUMP_HEIGHT = 97 / 3;
	float MARIO_HIGH_JUMP_HEIGHT = 216 / 3;
	float MARIO_SUPER_JUMP_HEIGHT = 300 / 3;
	float MARIO_SUPER_PUSH_FORCE = 0.632f / 3;
};

