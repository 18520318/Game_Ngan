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
};

