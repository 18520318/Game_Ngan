#pragma once
#include "BaseMarioState.h"

class CMario;

class MarioStateRacoon :
    public BaseMarioState
{
public:
    MarioStateRacoon(CMario* mario);

    virtual void Render();
};

