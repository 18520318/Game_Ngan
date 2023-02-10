#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Utils.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.07f
#define MARIO_RUNNING_SPEED		0.1f
#define MARIO_RUNNING_MAX_SPEED 0.16f
#define MARIO_WALK_MAX_SPEED 0.07f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_JUMP_MAX 0.8f

#define MARIO_GRAVITY			0.0018f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_JUMP_SPEED_MAX 0.3f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_SHOOTING	700
#define MARIO_STATE_SHOOTING_RELEASE	701

#define	MARIO_RACOON_ATTACK	800
#define	MARIO_RACOON_ATTACK_RELEASE	801

#define MARIO_POWER_FULL 7

#pragma region ANIMATION_ID



//FIRE MARIO
#define ID_ANI_FIRE_MARIO_IDLE_RIGHT 2400
#define ID_ANI_FIRE_MARIO_IDLE_LEFT 2401

#define ID_ANI_FIRE_MARIO_WALKING_RIGHT 2500
#define ID_ANI_FIRE_MARIO_WALKING_LEFT 2501

#define ID_ANI_FIRE_MARIO_RUNNING_RIGHT 2600
#define ID_ANI_FIRE_MARIO_RUNNING_LEFT 2601

#define ID_ANI_FIRE_MARIO_JUMP_WALK_RIGHT 2700
#define ID_ANI_FIRE_MARIO_JUMP_WALK_LEFT 2701

#define ID_ANI_FIRE_MARIO_JUMP_RUN_RIGHT 2800
#define ID_ANI_FIRE_MARIO_JUMP_RUN_LEFT 2801

#define ID_ANI_FIRE_MARIO_SIT_RIGHT 2900
#define ID_ANI_FIRE_MARIO_SIT_LEFT 2901

#define ID_ANI_FIRE_MARIO_BRACE_RIGHT 2100
#define ID_ANI_FIRE_MARIO_BRACE_LEFT 2101

#define ID_ANI_FIRE_MARIO_FIRE_ATTACK_RIGHT 2200
#define ID_ANI_FIRE_MARIO_FIRE_ATTACK_LEFT 2201

//RACOON MARIO
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


#define ID_ANI_RACOON_MARIO_ATTACK_FROM_LEFT 3201
#define ID_ANI_RACOON_MARIO_ATTACK_FROM_RIGHT 3200

#define ID_ANI_RACOON_MARIO_FLYING_RIGHT 3300
#define ID_ANI_RACOON_MARIO_FLYING_LEFT 3301

#define ID_ANI_RACOON_MARIO_FLOATING_RIGHT 3402
#define ID_ANI_RACOON_MARIO_FLOATING_LEFT 3403

#define ID_ANI_RACOON_WARP 3231 

#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	30
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16


#define MARIO_RACOON_BBOX_WIDTH  16


#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define ADJUST_MARIO_SHOOT_FIRE_X 5
#define ADJUST_MARIO_SHOOT_FIRE_Y 5

#define ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK 1

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_RACCON_ATTACK_TIME_OUT 500

#define POSITION_Y_OF_TAIL_MARIO 18

#define MAX_FLY_SPEED 333.0f

#define MARIO_RUN_DRAG_FORCE 0.0005f
#define MARIO_WALK_DRAG_FORCE 0.0002f

#define MARIO_SKID_ACCELERATION 0.0006f

#define PMETER_MAX 7

class BaseMarioState;

class CMario : public CGameObject
{
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	BaseMarioState* stateHandler;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;

	int coin; 
	int score;
	int live;

	BOOLEAN isGoThroughBlock = false;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithGoldBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPortalIn(LPCOLLISIONEVENT e);


public:
	CGameObject* obj = NULL;
//	CTail* tail;

	boolean isShootingFire;
	CMario(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int GetLevel() { return level; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	boolean IsAttack = false;
	boolean isRunning = false;
	boolean isWalking = false;
	boolean isRunningMax = false;
	boolean canFallSlow = false;
	BOOLEAN isSitting;
	boolean isDisable = true;

	void SetTail();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	vector<LPGAMEOBJECT> ListEffect;
	void ShootFire();
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetCurrentDirection() { return this->nx; }

	int GetCoin() { return coin; }
	void SetCoin(int _coin) { coin = _coin; }

	BaseMarioState* GetStateHandler();

	//Countdown time
	ULONGLONG attack_start = -1;
	ULONGLONG transform_start = -1;
	ULONGLONG die_start = -1;

	float powerMeter = 0;

	MarioWalkState walkState;

	MarioJumpState jumpState;

	void SitStateUpdate();
	void WalkStateUpdate(DWORD dt);
	void JumpStateUpdate();

	int direct = 1;

	void SetHurt();

	boolean isSliding = false;
	BOOLEAN isOnPlatform;

	float drag = 0;
	float _jumpStartHeight = 0;


	void SetAX(float acc_x) { this->ax = acc_x; }
	void SetAY(float acc_y) { this->ay = acc_y; }

	float GetAX() { return this->ax; }
	float GetAY() { return this->ay; }

	int GetScore() { return score; }
	void SetScore(int sc) { score += sc; }

	void SetLive(int l) { live = l; }
	int GetLive() { return live; }

	LPGAMEOBJECT hand;
};