#pragma once
#include "PlayScene.h"

#define ANI_GROUND_INTRO 1

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_DRAWMAP 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define GROUND_POSITION_X 128
#define GROUND_POSITION_Y 114//200

class IntroScene :
    public CPlayScene
{
	LPANIMATION ground;
public:
	IntroScene(int id, LPCWSTR filePath);
    virtual void Load();
    virtual void UnLoad();
    virtual void Render();
	virtual void Update(DWORD dt);

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	vector<LPGAMEOBJECT> objects;
};

