#include "PortalIn.h"
#include "Mario.h"
#include "PlayScene.h"

PortalIn::PortalIn(float x, float y, float w, float h, int direction, float cx, float cy, int scene)
{
	this->x = x;
	this->y = y;

	this->cx = cx;
	this->cy = cy;

	this->width = w;
	this->height = h;

	this->portal_dir = direction;

	isActive = false;
	this->sceneNo = scene;
}

void PortalIn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGame* game = CGame::GetInstance();
	//CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();

	//float sl, st, sr, sb, left, top, right, bottom;
	//mario->GetBoundingBox(sl, st, sr, sb);

	//GetBoundingBox(left, top, right, bottom);

	//if ((portal_dir == 1 && game->IsKeyDown(DIK_DOWN)) || (portal_dir == -1 && game->IsKeyDown(DIK_UP))) {
	//	if (CCollision::GetInstance()->IsOverlap(left, top, right, bottom, sl, st, sr, sb)) {
	//		isActive = true;
	//	}
	//}
	//if (isActive) {
	//	mario->isDisable = true;

	//	float mx = mario->GetX();
	//	float my = mario->GetY();

	//	my += 0.7 * portal_dir;

	//	mario->SetPosition(mx, my);
	//	mario->SetVX(0);
	//	mario->SetVY(0);

	//	mario->GetBoundingBox(sl, st, sr, sb);
	//	bool end = false;
	//	if (portal_dir > 0) {
	//		if (st >= top) {
	//			end = true;
	//		}
	//	}
	//	else {
	//		if (sb <= bottom) {
	//			end = true;
	//		}
	//	}
	//	if (end) {
	//		isActive = false;
	//		/*game->InitiateSwitchScene(sceneNo);
	//		game->SwitchScene();*/
	//		mario->isDisable = false;
	//		//mario->SetPosition(cx, cy);
	//		mario->walkState = MarioWalkState::Idle;
	//	}
	//}
}

void PortalIn::Render()
{
	RenderBoundingBox();
}

void PortalIn::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}
