#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "FireBall.h"
#include "BGBlock.h"
#include "QuestionBrick.h"
#include "Leaf.h"
#include "FirePiranhaPlant.h"

#include "BaseMarioState.h"
#include "MarioStateSmall.h"
#include "MarioStateBig.h"
#include "MarioStateRacoon.h"

#include "Collision.h"

CMario::CMario(float x, float y) : CGameObject(x, y) {
	this->stateHandler = new MarioStateSmall(this);
	isSitting = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = MARIO_GRAVITY;

	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	untouchable_start = -1;
	isOnPlatform = false;
	coin = 0;
	isShootingFire = false;
	this->x = x;
	this->y = y;
	tail = new CTail(x, y);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{	
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	//if (abs(vx) > abs(maxVx)) vx = maxVx;
	//if (x <= MARIO_BIG_BBOX_WIDTH) {
	//	x = MARIO_BIG_BBOX_WIDTH;
	//}
	//if (x + MARIO_BIG_BBOX_WIDTH >= scene->map->GetMapWidth()) {
	//	x = (float)(scene->map->GetMapWidth() - MARIO_BIG_BBOX_WIDTH);
	//}
	LPGAME game = CGame::GetInstance();
	if (game->IsKeyPressed(DIK_1)) {
//		SetLevel(MARIO_LEVEL_SMALL);
		this->stateHandler = new MarioStateSmall(this);
	}
	if (game->IsKeyPressed(DIK_2)) {
//		SetLevel(MARIO_LEVEL_BIG);
		this->stateHandler = new MarioStateBig(this);
	}
	if (game->IsKeyPressed(DIK_3)) {
//		SetLevel(MARIO_LEVEL_RACOON);
		this->stateHandler = new MarioStateRacoon(this);
	}

	stateHandler->Update(dt, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);

	float finall, finalt, finalr, finalb;
	this->GetBoundingBox(finall, finalt, finalr, finalb);

	if (b - t != finalb - finalt) {
		this->y += b - finalb;
	}

	isOnPlatform = true;
}

void CMario::SetTail()
{
	if (!tail) {
		tail = new CTail(x, y);
	}
	if (nx > 0)
	{
		tail->SetPosition(x - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
	}
	else {
		tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
	}
	tail->SetWidth(TAIL_BBOX_WIDTH);
	tail->SetHeight(TAIL_BBOX_HEIGHT);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBGBlock*>(e->obj))
		OnCollisionWithBackgroundBlock(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<FirePiranhaPlant*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<FireBall*>(e->obj))
		OnCollisionWithFireball(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (goomba->GetType() == NORMAL_GOOMBA) {
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else
			{
				if (goomba->GetState() == GOOMBA_STATE_WALKING) {
					goomba->SetState(GOOMBA_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else
				{
					goomba->SetState(GOOMBA_STATE_WALKING);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
			}
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			SetHurt();
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e)
{
	CBGBlock* block = dynamic_cast<CBGBlock*>(e->obj);
	if (e->ny > 0) {
		isGoThroughBlock = true;
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0 && !questionBrick->isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	DebugOut(L"-------------------------------------------------------");
	level = MARIO_LEVEL_RACOON;
	e->obj->Delete();
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	if (e->nx != 0 || e->ny != 0) {
		SetHurt();
	}
}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	FireBall* fireball = dynamic_cast<FireBall*>(e->obj);
	if (fireball->isEnemyShoot) {
		fireball->isDeleted = true;
		SetHurt();
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	//if (!isOnPlatform)
	//{
	//	if (abs(ax) == MARIO_ACCEL_RUN_X)
	//	{
	//		if (nx >= 0)
	//			aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
	//		else
	//			aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
	//	}
	//	else
	//	{
	//		if (nx >= 0)
	//			aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
	//		else
	//			aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
	//	}
	//}
	//else
	//	if (isSitting)
	//	{
	//		if (nx > 0)
	//			aniId = ID_ANI_MARIO_SIT_RIGHT;
	//		else
	//			aniId = ID_ANI_MARIO_SIT_LEFT;
	//	}
	//	else
	//		if (vx == 0)
	//		{
	//			if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
	//			else aniId = ID_ANI_MARIO_IDLE_LEFT;
	//		}
	//		else if (vx > 0)
	//		{
	//			if (ax < 0)
	//				aniId = ID_ANI_MARIO_BRACE_RIGHT;
	//			else if (ax == MARIO_ACCEL_RUN_X)
	//				aniId = ID_ANI_MARIO_RUNNING_RIGHT;
	//			else if (ax == MARIO_ACCEL_WALK_X)
	//				aniId = ID_ANI_MARIO_WALKING_RIGHT;
	//		}
	//		else // vx < 0
	//		{
	//			if (ax > 0)
	//				aniId = ID_ANI_MARIO_BRACE_LEFT;
	//			else if (ax == -MARIO_ACCEL_RUN_X)
	//				aniId = ID_ANI_MARIO_RUNNING_LEFT;
	//			else if (ax == -MARIO_ACCEL_WALK_X)
	//				aniId = ID_ANI_MARIO_WALKING_LEFT;
	//		}

	if (!isOnPlatform)
	{
	}
	else {

		if (isSliding) {
			aniId = ID_ANI_MARIO_BRACE_RIGHT;

			return aniId;
		}

		if (vx == 0 && walkState != MarioWalkState::Sit) {
			aniId = ID_ANI_MARIO_IDLE_RIGHT;

			return aniId;
		}

		/*if (walkState == MarioWalkState::Sit) {
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		}*/
		switch (walkState)
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

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;


	return aniId;
}

//
// Get animation ID for Fire Mario
//
int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_FIRE_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_FIRE_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_FIRE_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_FIRE_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_FIRE_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_FIRE_MARIO_SIT_LEFT;
		}
		else if (isShootingFire) {
			if (nx > 0) {
				aniId = ID_ANI_FIRE_MARIO_FIRE_ATTACK_RIGHT;
			}
			else
				aniId = ID_ANI_FIRE_MARIO_FIRE_ATTACK_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_FIRE_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_FIRE_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_FIRE_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_FIRE_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_FIRE_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_FIRE_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_FIRE_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_FIRE_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_FIRE_MARIO_IDLE_RIGHT;
	return aniId;
}

//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOON_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_SIT_LEFT;
		}
		else if (IsAttack) {
			if (nx > 0) {
				aniId = ID_ANI_RACOON_MARIO_ATTACK_FROM_LEFT;
			}
			else
				aniId = ID_ANI_RACOON_MARIO_ATTACK_FROM_RIGHT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_RACOON_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_RACOON_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_RACOON_MARIO_IDLE_RIGHT;
	return aniId;
}

void CMario::Render()
{
	stateHandler->Render();
	RenderBoundingBox();

	//CAnimations* animations = CAnimations::GetInstance();
	//int aniId = -1;

	//if (state == MARIO_STATE_DIE)
	//	aniId = ID_ANI_MARIO_DIE;
	//else if (level == MARIO_LEVEL_BIG)
	//	aniId = GetAniIdBig();
	//else if (level == MARIO_LEVEL_SMALL)
	//	aniId = GetAniIdSmall();
	//else if (level == MARIO_LEVEL_FIRE)
	//	aniId = GetAniIdFire();
	//else if (level == MARIO_LEVEL_RACOON)
	//	aniId = GetAniIdRacoon();

	//if (direct == -1) {
	//	aniId += 1;
	//}
	//animations->Get(aniId)->Render(x, y);

	//if (tail) {
	//	tail->Render();
	//}

	//
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_SHOOTING:
		isShootingFire = true;
		break;
	case MARIO_STATE_SHOOTING_RELEASE:
		isShootingFire = false;
		state = MARIO_STATE_IDLE;
		break;
	case MARIO_RACOON_ATTACK:
		IsAttack = true;
		attack_start = GetTickCount64();
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level>=MARIO_LEVEL_BIG)
	{
		if (walkState == MarioWalkState::Sit)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			if (level == MARIO_LEVEL_RACOON) {
				left = x - MARIO_RACOON_BBOX_WIDTH / 2;
				right = left + MARIO_RACOON_BBOX_WIDTH;
			}
			else {
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
			}
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

BaseMarioState* CMario::GetStateHandler()
{
	return this->stateHandler;
}

void CMario::SitStateUpdate()
{
	LPGAME game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_DOWN)) {
		walkState = MarioWalkState::Sit;
	}
	if (game->IsKeyReleased(DIK_DOWN) && walkState == MarioWalkState::Sit) {
		walkState = MarioWalkState::Idle;
	}
}

void CMario::WalkStateUpdate(DWORD dt)
{
	LPGAME game = CGame::GetInstance();
	float vx_check = GetVX();
	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
	{
		//direct = game->IsKeyDown(DIK_RIGHT) ? 1 : -1;
		int keySign = game->IsKeyDown(DIK_LEFT) ? -1 : 1;
		//DebugOut(L"Directtt %d \n", keySign);

		if(isOnPlatform) walkState = MarioWalkState::Walk;
		ax = MARIO_WALKING_SPEED * keySign;
		float maxSpeed = MARIO_RUNNING_MAX_SPEED;

		if (game->IsKeyDown(DIK_A)) {
			if (isOnPlatform) {
				walkState = MarioWalkState::Run;
			}
			ax = MARIO_RUNNING_SPEED * keySign;
			maxSpeed = MARIO_RUNNING_MAX_SPEED;
		}
		DebugOut(L"Directtt %f \n", (float)GetVX() * keySign);
		if (GetVX() * keySign < 0) {
			isSliding = true;
			ax = (FLOAT)((game->IsKeyDown(DIK_A) ? MARIO_SKID_ACCELERATION : MARIO_SKID_ACCELERATION * 0.5) * keySign);

			if (!isOnPlatform) {
				ax = MARIO_SKID_ACCELERATION * keySign * 2;
			}
		}
		//DebugOut(L"[INFO] Current accelerate: %d \n", ax);
		vx_check += ax * dt;
		//DebugOut(L"Directtt %f \n", vx_check);
		float fly_sp = MAX_FLY_SPEED;
		if (jumpState != MarioJumpState::Idle)
			maxSpeed = (maxSpeed > fly_sp) ? fly_sp : maxSpeed;//min(maxSpeed, MAX_FLY_SPEED);

		if (abs(GetVX()) > maxSpeed) {
			int sign = GetVX() < 0 ? -1 : 1;
			if (abs(GetVX()) - maxSpeed > MARIO_ACCEL_WALK_X * dt) {
				vx_check -= MARIO_ACCEL_WALK_X * dt * sign;
			}
			else {
				vx_check = maxSpeed * sign;
			}
		}
		if (GetVX() * direct >= 0) {
			isSliding = 0;
		}
		direct = vx_check < 0 ? -1 : 1;
	}
	else {
		//else			isSliding = 0;
			//walkState = MarioWalkState::Idle;	
		if (abs(vx_check) > drag * dt) {
			int sign = vx_check < 0 ? -1 : 1;
			vx_check -= drag * dt * sign;
		}
		else {
			vx_check = 0.0f;
			if (walkState != MarioWalkState::Sit) {
				walkState = MarioWalkState::Idle;
			}
		}
	}
	//DebugOut(L"Directtt %d \n", isSliding);
	if (walkState != MarioWalkState::Sit) {
		drag = walkState == MarioWalkState::Run ? MARIO_RUN_DRAG_FORCE : MARIO_WALK_DRAG_FORCE;
	}
	drag *= isOnPlatform;

	//SetSpeed(vx_check, vy );
	vx = vx_check;
}

void CMario::JumpStateUpdate()
{
	LPGAME game = CGame::GetInstance();
}

void CMario::SetHurt()
{
	if (untouchable == 0){
		if (level > MARIO_LEVEL_SMALL){
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
			die_start = GetTickCount64();
		}
	}
	else return;
}

void CMario::ShootFire()
{
	FireBall* fireBall = new FireBall(x + ADJUST_MARIO_SHOOT_FIRE_X, y + ADJUST_MARIO_SHOOT_FIRE_Y);
	fireBall->SetState(FIRE_FROM_MARIO);
	FireList.push_back(fireBall);
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (this->level == MARIO_LEVEL_RACOON)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

