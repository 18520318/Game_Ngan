#include "WorldScene.h"
#include "Grass.h"
#include "Door.h"
#include "Blocker.h"
#include "Hammer.h"
#include "HelpBox.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_DRAWMAP 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define ADJUST_PADDING 10
#define HUD_HEIGHT 32

void WorldScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void WorldScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	 
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void WorldScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void WorldScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	int model = 0;
	if (tokens.size() >= 4) {
		model = atoi(tokens[3].c_str());
	}
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new WorldPlayer(x, y);
		player = (WorldPlayer*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case OBJECT_TYPE_GRASS:
	{
		obj = new Grass(x, y);
		break;
	}
	case OBJECT_TYPE_DOOR:
	{
		int scene = atoi(tokens[3].c_str());
		obj = new Door(x, y, scene);
		break;
	}
	case OBJECT_BLOCK_WORLD_MAP:
	{
		int allowLeft = atoi(tokens[3].c_str());
		int allowRight = atoi(tokens[4].c_str());
		int allowBottom = atoi(tokens[5].c_str());
		int allowTop = atoi(tokens[6].c_str());

		obj = new Blocker(x, y, allowLeft, allowRight, allowBottom, allowTop);
		break;
	}
	case OBJECT_HAMMER_WORLD_MAP:
	{
		obj = new Hammer(x, y);
		break;
	}
	case OBJECT_HELP_WORLD_MAP:
	{
		obj = new HelpBox(x, y);
		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void WorldScene::_ParseSection_TILEMAP(string line)
{
	int idTex, numOfRowMap, numofColMap, numOfRowTileSet, numOfColTileSet, totalTile;

	LPCWSTR path = ToLPCWSTR(line);
	ifstream f(path, ios::in);
	f >> idTex >> numOfRowMap >> numofColMap >> numOfRowTileSet >> numOfColTileSet >> totalTile;
	int** tileMapData = new int* [numOfRowMap];
	for (int i = 0; i < numOfRowMap; i++)
	{
		tileMapData[i] = new int[numofColMap];
		for (int j = 0; j < numofColMap; j++)
		{
			f >> tileMapData[i][j];
		}
	}
	f.close();
	map = new Map(idTex, numOfRowMap, numofColMap, numOfRowTileSet, numOfColTileSet, totalTile);
	map->GetSpriteTile();
	map->SetMapData(tileMapData);
}

void WorldScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

WorldScene::WorldScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;

	//key_handler = new CWorldKey(this);
}

void WorldScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[TILEMAP]") { section = SCENE_SECTION_DRAWMAP; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_DRAWMAP: _ParseSection_TILEMAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void WorldScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	gameTime->Update(dt);
	gameTimeRemain = GAME_TIME_LIMIT - gameTime->GetTime();

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	CGame::GetInstance()->SetCamPos(-ADJUST_PADDING, -HUD_HEIGHT - ADJUST_PADDING);

	PurgeDeletedObjects();
}

void WorldScene::Render()
{
	CGame* game = CGame::GetInstance();
	//CHUD* hud = new CHUD(game->GetCamX() + HUD_WIDTH / 2, game->GetCamY() + game->GetScreenHeight() - HUD_HEIGHT / 2);


	map->DrawMap();

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	//hud->Render(mario, gameTimeRemain);
}

void WorldScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	delete map;

	map = nullptr;
	player = nullptr;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void WorldScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), WorldScene::IsGameObjectDeleted),
		objects.end());
}

bool WorldScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
