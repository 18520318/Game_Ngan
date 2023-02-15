#pragma once
#include "Scene.h"
#include "Game.h"

#include "GameObject.h"
#include "Map.h"

#include "Mario.h"
#include "Timer.h"
#include "WorldPlayer.h"

class WorldScene :
    public CScene
{
    CMario* mario = NULL;
    Timer* gameTime = new Timer(true, 0);
    WorldPlayer* player = NULL;

    int gameTimeRemain = 0;
    bool isTurnOnCamY = false;

    void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);

    void _ParseSection_ASSETS(string line);
    void _ParseSection_OBJECTS(string line);
    void _ParseSection_TILEMAP(string line);

    void LoadAssets(LPCWSTR assetFile);
public:
    WorldScene(int id, LPCWSTR filePath);
};

