#include "MarioStateBig.h"

#include "Mario.h"

MarioStateBig::MarioStateBig(CMario* mario) : BaseMarioState(mario)
{
}

void MarioStateBig::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	
	if (!mario->isOnPlatform)
	{
		//aniId = ID_ANI_MARIO_BRACE_RIGHT;
		switch (mario->jumpState)
		{
		case MarioJumpState::Fly:
			aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			break;
		case MarioJumpState::Float:
			aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			break;
		case MarioJumpState::Fall:
			aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			break;
		case MarioJumpState::Jump:
			aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			break;
		case MarioJumpState::HighJump:
			aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			break;
		default:
			break;
		}
	}


	else if (mario->isSliding && mario->GetVX() != 0) {
		aniId = ID_ANI_MARIO_BRACE_RIGHT;
	}
	else {

		if (mario->GetVX() == 0 && mario->walkState != MarioWalkState::Sit) {
			aniId = ID_ANI_MARIO_IDLE_RIGHT;
		}

		else {
			switch (mario->walkState)
			{
			case MarioWalkState::Run:
				aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				break;
			case MarioWalkState::Walk:
				aniId = ID_ANI_MARIO_WALKING_RIGHT;
				break;
			case MarioWalkState::Sit:
				aniId = ID_ANI_MARIO_SIT_RIGHT;
				break;
			default:
				aniId = ID_ANI_MARIO_IDLE_RIGHT;
				break;
			}
		}

	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;
	if (mario->direct < 0) aniId += 1;

	animations->Get(aniId)->Render(mario->GetX(), mario->GetY());
}
