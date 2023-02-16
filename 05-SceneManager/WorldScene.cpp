#include "WorldScene.h"
#include "Grass.h"
#include "Door.h"
#include "Blocker.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_DRAWMAP 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024


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
		//obj = new CHammer(x, y);
		break;
	}
	case OBJECT_HELP_WORLD_MAP:
	{
		//obj = new CHelp(x, y);
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
}

WorldScene::WorldScene(int id, LPCWSTR filePath) :
	CPlayScene(id, filePath)
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
