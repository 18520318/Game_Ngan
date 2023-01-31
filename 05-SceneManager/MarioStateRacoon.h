#pragma once
#include "BaseMarioState.h"
#include "Timer.h"


class CMario;

class MarioStateRacoon :
    public BaseMarioState
{
public:
    MarioStateRacoon(CMario* mario);

    virtual void JumpUpdate(DWORD dt);
    virtual void PowerMeterUpdate(DWORD dt);
    virtual void AttackUpdate(DWORD dt);

    virtual void Render();

    Timer flyTimer{ true, 250L };
    Timer pmeterTimer{ true, 4000L };
    Timer attackTimer{ true, 400 };
};

