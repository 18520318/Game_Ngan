#include "WorldScene.h"


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_DRAWMAP 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void WorldScene::_ParseSection_SPRITES(string line)
{
}

void WorldScene::_ParseSection_ANIMATIONS(string line)
{
}

void WorldScene::_ParseSection_ASSETS(string line)
{
}

void WorldScene::_ParseSection_OBJECTS(string line)
{
}

void WorldScene::_ParseSection_TILEMAP(string line)
{
}

void WorldScene::LoadAssets(LPCWSTR assetFile)
{
}

WorldScene::WorldScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;

	//key_handler = new CWorldKey(this);
}
