#pragma once
#include "Utils.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

class Map
{
	static Map* __instance;
	LPTEXTURE Tex;
	int NumofRowMap, NumofColMap;
	int NumofRowTileSet, NumofColTileSet;
	int TotalTile;
	int** TileMapData;
	vector<LPSPRITE> Tiles;

public:
	Map(int TexID, int NumofRowMap, int NumofColMap, int NumofRowTileSet, int NumofColTileSet, int TotalTile);
	~Map();
	void SetMapData(int** mapData);
	void GetSpriteTile();
	void DrawMap();

	int GetMapWidth();
	int GetMapHeight();
};

