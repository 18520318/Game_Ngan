#pragma once
#include "BaseMarioState.h"

class CMario;

class MarioStateBig :
    public BaseMarioState
{
public:
    MarioStateBig(CMario* mario);

    virtual void Render();
};

