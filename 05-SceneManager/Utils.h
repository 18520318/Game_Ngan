#pragma once

#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

#include <fstream>
#include <string>
#include "AssetIDs.h"

using namespace std;

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);

enum class MarioWalkState
{
	Idle,
	Walk,
	Run,
	Sit
};

enum class MarioJumpState
{
	Idle,
	Jump,
	HighJump,
	Fly,
	Float,
	Fall
};

#define TYPE_MARIO 0
#define TYPE_OBJECT 1
#define TYPE_ENEMY 2
#define TYPE_COIN 3
#define TYPE_GOLDBRICK 4
#define TYPE_COLOR_BLOCK 5

enum EType {
	MARIO = TYPE_MARIO,
	OBJECT = TYPE_OBJECT,
	ENEMY = TYPE_ENEMY,
	COIN = TYPE_COIN,
	GOLDBRICK = TYPE_GOLDBRICK,
	COLORBLOCK = TYPE_COLOR_BLOCK,
};

#define ENEMY_STATE_IS_KOOPAS_ATTACKED 900 // koopas is kicked attack or tail attack
#define ENEMY_STATE_IS_FIRE_ATTACKED 901
#define ENEMY_STATE_IS_TAIL_ATTACKED 902