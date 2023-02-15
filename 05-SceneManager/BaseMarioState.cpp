#include "BaseMarioState.h"
#include "GameObject.h"
#include "Mario.h"
#include "Koopas.h"

BaseMarioState::BaseMarioState(CMario* mario)
{
	this->mario = mario;
}

void BaseMarioState::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	WalkUpdate(dt);
	PowerMeterUpdate(dt);
	JumpUpdate(dt);
	AttackUpdate(dt);
	holdingShellUpdate(dt);
	warpUpdate(dt);

	CCollision::GetInstance()->Process(mario, dt, coObjects);
	//DebugOut(L"vy: %f\n", mario->GetVY());
}

void BaseMarioState::WalkUpdate(DWORD dt)
{
	if (mario->isDisable) return; 

	CGame* game = CGame::GetInstance();
	float vx_check = mario->GetVX();
	if (game->IsKeyDown(DIK_DOWN)) {
		if (mario->jumpState == MarioJumpState::Idle) {
			mario->walkState = MarioWalkState::Sit;
			mario->drag = MARIO_CROUCH_DRAG_FORCE;
		}
	}
	if (game->IsKeyReleased(DIK_DOWN) && mario->walkState == MarioWalkState::Sit) {
		mario->walkState = MarioWalkState::Idle;
	}
	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
	{
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
		if (mario->jumpState != MarioJumpState::Idle) {
			maxSpeed = (maxSpeed > fly_sp) ? fly_sp : maxSpeed;//min(maxSpeed, MAX_FLY_SPEED);
		}

		if (abs(vx_check) > maxSpeed) {
			int sign = mario->GetVX() < 0 ? -1 : 1;
			if (abs(mario->GetVX()) - maxSpeed > MARIO_ACCEL_WALK_X * dt) {
				vx_check -= MARIO_ACCEL_WALK_X * dt * sign;
			}
			else {
				vx_check = maxSpeed * sign;
			}
		}
		mario->direct = vx_check < 0 ? -1 : 1;
		if (mario->GetVX() * keySign >= 0) {
			mario->isSliding = 0;
		}
	}
	else {
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
	if (mario->isDisable) return;
	float vy_temp = mario->GetVY();
	
	CGame* game = CGame::GetInstance();
	float x, y;
	mario->GetPosition(x, y);

	if (mario->isOnPlatform) {
		mario->jumpState = MarioJumpState::Idle;

		if (game->IsKeyPressed(DIK_S)) {
			mario->jumpState = MarioJumpState::Jump;
			mario->isOnPlatform = false;
			mario->_jumpStartHeight = y;

			if (mario->powerMeter >= PMETER_MAX) {
				mario->jumpState = MarioJumpState::Fly;
			}
		}
	}

	float jumpHeight = MARIO_JUMP_HEIGHT;
	float minJumpHeight = MARIO_MIN_JUMP_HEIGHT;
	float height = 0;

	switch (mario->jumpState)
	{
	case MarioJumpState::Fly:
		height = abs(mario->_jumpStartHeight - y - vy_temp * dt);
		minJumpHeight = MARIO_MIN_HIGH_JUMP_HEIGHT;

		if (height < minJumpHeight || (height < MARIO_SUPER_JUMP_HEIGHT && game->IsKeyDown(DIK_S))) {
			vy_temp = -MARIO_SUPER_PUSH_FORCE - MARIO_GRAVITY * dt;
		}
		else {
			mario->jumpState = MarioJumpState::Float;
			vy_temp = -MARIO_SUPER_PUSH_FORCE / 2;
		}
		break;
	case MarioJumpState::HighJump:
		jumpHeight = MARIO_HIGH_JUMP_HEIGHT;
		minJumpHeight = MARIO_MIN_HIGH_JUMP_HEIGHT;
	case MarioJumpState::Jump:
		height = abs(mario->_jumpStartHeight - y - vy_temp * dt);

		if (height < minJumpHeight || (height < jumpHeight && game->IsKeyDown(DIK_S))) {
			vy_temp = -MARIO_PUSH_FORCE - MARIO_GRAVITY * dt;
		}
		else {
			if (game->IsKeyDown(DIK_S) && mario->jumpState == MarioJumpState::Jump) {
				mario->jumpState = MarioJumpState::HighJump;
			}
			else {
				mario->jumpState = MarioJumpState::Fall;
				vy_temp = -MARIO_PUSH_FORCE / 2;
			}
		}
		break;
	case MarioJumpState::Float:
	case MarioJumpState::Fall:
		break;
	}
	mario->SetVY(vy_temp);
}

void BaseMarioState::holdingShellUpdate(DWORD dt)
{
	if (mario->isDisable) return;

	CGame* game = CGame::GetInstance();
	if (mario->hand != NULL) {
		if (mario->direct > 0) {
			mario->hand->SetPosition(mario->GetX() + 10, mario->GetY());
		}
		else mario->hand->SetPosition(mario->GetX() - 10, mario->GetY());
		if (game->IsKeyReleased(DIK_A)) {
			dynamic_cast<Koopas*>(mario->hand)->isHeld = false;
			mario->hand->SetPosition(mario->hand->GetX() + 5 * mario->direct, mario->hand->GetY() - 5);
			mario->hand->SetState(KOOPAS_STATE_IS_KICKED);
			mario->hand = NULL;
		}
	}

}

void BaseMarioState::warpUpdate(DWORD dt)
{
}

void BaseMarioState::PowerMeterUpdate(DWORD dt)
{
	if (mario->isDisable) return;
	float vx = mario->GetVX();

	float maxRun = abs(vx) > MARIO_RUNNING_SPEED * 0.85f;

	if (maxRun && mario->isOnPlatform)
		mario->powerMeter = max(0.0f, min(mario->powerMeter + PMETER_UP_STEP * dt, PMETER_MAX + 1));
	else if (mario->powerMeter > 0)
		mario->powerMeter = max(0.0f, min(mario->powerMeter - PMETER_DOWN_STEP * dt, PMETER_MAX));
}

void BaseMarioState::AttackUpdate(DWORD dt)
{
}

void BaseMarioState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (mario->walkState == MarioWalkState::Sit)
	{
		left = mario->GetX() - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
		top = mario->GetY() - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
		bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
	}
	else
	{
		left = mario->GetX() - MARIO_BIG_BBOX_WIDTH / 2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		top = mario->GetY() - MARIO_BIG_BBOX_HEIGHT / 2;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
}
