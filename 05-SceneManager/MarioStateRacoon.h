#pragma once
#include "BaseMarioState.h"

#define ID_ANI_RACOON_MARIO_IDLE_RIGHT 3400
#define ID_ANI_RACOON_MARIO_IDLE_LEFT 3401

#define ID_ANI_RACOON_MARIO_WALKING_RIGHT 3500
#define ID_ANI_RACOON_MARIO_WALKING_LEFT 3501

#define ID_ANI_RACOON_MARIO_RUNNING_RIGHT 3600
#define ID_ANI_RACOON_MARIO_RUNNING_LEFT 3601

#define ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT 3700
#define ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT 3701

#define ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT 3800
#define ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT 3801

#define ID_ANI_RACOON_MARIO_SIT_RIGHT 3900
#define ID_ANI_RACOON_MARIO_SIT_LEFT 3901

#define ID_ANI_RACOON_MARIO_BRACE_RIGHT 3100
#define ID_ANI_RACOON_MARIO_BRACE_LEFT 3101


#define ID_ANI_RACOON_MARIO_ATTACK_FROM_LEFT 3200
#define ID_ANI_RACOON_MARIO_ATTACK_FROM_RIGHT 3201

class CMario;

class MarioStateRacoon :
    public BaseMarioState
{
public:
    MarioStateRacoon(CMario* mario);

    virtual void JumpUpdate(DWORD dt);
    //virtual void PowerMeterUpdate(DWORD dt);
    //virtual void AttackUpdate(DWORD dt);

    virtual void Render();
};

