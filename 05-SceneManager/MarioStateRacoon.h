#pragma once
#include "BaseMarioState.h"
#include "Timer.h"


class CMario;
class CTail;

class MarioStateRacoon :
    public BaseMarioState
{
public:
    CTail* tail;

    MarioStateRacoon(CMario* mario);
    ~MarioStateRacoon();

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

    virtual void JumpUpdate(DWORD dt);
    virtual void PowerMeterUpdate(DWORD dt);
    virtual void AttackUpdate(DWORD dt);

    virtual void Render();

    Timer flyTimer{ true, 250L };
    Timer pmeterTimer{ true, 4000L };
    Timer attackTimer{ true, 400L };

    float MAX_FLY_HEIGHT = 315;
};

