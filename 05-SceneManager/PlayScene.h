#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "QBCoin.h"
#include "Timer.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	CMario* player = NULL;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

	void LoadAssets(LPCWSTR assetFile);

	Timer* gameTime = new Timer(true, GAME_TIME_LIMIT);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }

	void SetCam(float cx, float cy);

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	Map* map = NULL;

	void PutPlayer(CMario* m)
	{
		if (dynamic_cast<CMario*>(objects[0]))
			objects[0] = m;
	}
	void SetPlayer(CMario* mario) { player = mario; }

	vector<LPGAMEOBJECT> objects;

	bool isFlyCam = false;
	int remainingTime;

	void SetStartTime(int time) { gameTime->SetTimeOut(time); }
	void BackupPlayerInfo();
	void LoadBackupPlayerInfo();
};

typedef CPlayScene* LPPLAYSCENE;

