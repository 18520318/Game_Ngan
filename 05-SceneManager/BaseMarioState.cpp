#include "BaseMarioState.h"
#include "GameObject.h"
#include "Mario.h"

BaseMarioState::BaseMarioState(CMario* mario)
{
	this->mario = mario;
}

void BaseMarioState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	WalkUpdate(dt);
	JumpUpdate(dt);
	holdingShellUpdate(dt);
	warpUpdate(dt);
}

void BaseMarioState::WalkUpdate(DWORD dt)
{
	CGame* game = CGame::GetInstance();
	float vx_check = mario->GetVX();
	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
	{
		//direct = game->IsKeyDown(DIK_RIGHT) ? 1 : -1;
		int keySign = game->IsKeyDown(DIK_LEFT) ? -1 : 1;
		//DebugOut(L"Directtt %d \n", keySign);

		if (mario->isOnPlatform) mario->walkState = MarioWalkState::Walk;
		mario->SetAX(MARIO_ACCEL_WALK_X * keySign);
		float maxSpeed = MARIO_WALK_MAX_SPEED;

		if (game->IsKeyDown(DIK_A)) {
			if (mario->isOnPlatform) {
				mario->walkState = MarioWalkState::Run;
			}
			mario->SetAX(MARIO_ACCEL_RUN_X * keySign);
			maxSpeed = MARIO_RUNNING_MAX_SPEED;
		}
		//DebugOut(L"Directtt %f \n", (float)mario->GetVX() * keySign);
		if (mario->GetVX() * keySign < 0) {
			mario->isSliding = true;
			mario->SetAX((FLOAT)((game->IsKeyDown(DIK_A) ? MARIO_SKID_ACCELERATION : MARIO_SKID_ACCELERATION * 0.5) * keySign));

			if (!mario->isOnPlatform) {
				mario->SetAX(MARIO_SKID_ACCELERATION * keySign * 2);
			}
		}
		//DebugOut(L"[INFO] Current accelerate: %d \n", ax);
		vx_check += mario->GetAX() * dt;
		//DebugOut(L"Directtt %f \n", vx_check);
		float fly_sp = MAX_FLY_SPEED;
		if (mario->jumpState != MarioJumpState::Idle)
			maxSpeed = (maxSpeed > fly_sp) ? fly_sp : maxSpeed;//min(maxSpeed, MAX_FLY_SPEED);

		if (abs(mario->GetVX()) > maxSpeed) {
			int sign = mario->GetVX() < 0 ? -1 : 1;
			if (abs(mario->GetVX()) - maxSpeed > MARIO_ACCEL_WALK_X * dt) {
				vx_check -= MARIO_ACCEL_WALK_X * dt * sign;
			}
			else {
				vx_check = maxSpeed * sign;
			}
		}
		if (mario->GetVX() * mario->direct >= 0) {
			mario->isSliding = 0;
		}
		mario->direct = vx_check < 0 ? -1 : 1;
	}
	else {
		//else			isSliding = 0;
			//walkState = MarioWalkState::Idle;	
		if (abs(vx_check) > mario->drag * dt) {
			int sign = vx_check < 0 ? -1 : 1;
			vx_check -= mario->drag * dt * sign;
		}
		else {
			vx_check = 0.0f;
			if (mario->walkState != MarioWalkState::Sit) {
				mario->walkState = MarioWalkState::Idle;
			}
		}
	}
	//DebugOut(L"Directtt %d \n", isSliding);
	if (mario->walkState != MarioWalkState::Sit) {
		mario->drag = mario->walkState == MarioWalkState::Run ? MARIO_RUN_DRAG_FORCE : MARIO_WALK_DRAG_FORCE;
	}
	mario->drag *= mario->isOnPlatform;

	//SetSpeed(vx_check, vy );
	mario->SetVX(vx_check);
}

void BaseMarioState::JumpUpdate(DWORD dt)
{
	
}

void BaseMarioState::holdingShellUpdate(DWORD dt)
{
}

void BaseMarioState::warpUpdate(DWORD dt)
{
}
