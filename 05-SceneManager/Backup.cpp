#include "Backup.h"
#include "PlayScene.h"

CBackUp* CBackUp::__instance = NULL;
CBackUp* CBackUp::GetInstance()
{
	if (__instance == NULL) __instance = new CBackUp();
	return __instance;
}

void CBackUp::BackUpMario(CMario* mario)
{
	live = mario->GetLive();
	score = mario->GetScore();
	level = mario->GetLevel();
	coin = mario->GetCoin();
	gameTime = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->remainingTime;
}

void CBackUp::LoadBackUp(CMario* mario)
{
	mario->SetLive(live);
	mario->SetScore(score);
	mario->SetLevel(level);
	mario->SetCoin(coin);

	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->SetStartTime(gameTime);
}
