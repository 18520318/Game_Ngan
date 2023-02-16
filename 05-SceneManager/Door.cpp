#include "Door.h"

Door::Door(float x, float y, int scene)
{
	this->x = x;
	this->y = y;
	this->scene = scene;
}

void Door::Render()
{
	int ani = -1;

	switch (scene) {
	case START: {
		ani = ID_ANI_DOOR_START;
		break;
	}
	case SCENE_1:
	{
		ani = ID_ANI_DOOR_SCENE_1;
		break;
	}
	case SCENE_2:
	{
		ani = ID_ANI_DOOR_SCENE_2;
		break;
	}
	case SCENE_3:
	{
		ani = ID_ANI_DOOR_SCENE_3;
		break;
	}
	case SCENE_4:
	{
		ani = ID_ANI_DOOR_SCENE_4;
		break;
	}
	case SCENE_5:
	{
		ani = ID_ANI_DOOR_SCENE_5;
		break;
	}
	case SCENE_6:
	{
		ani = ID_ANI_DOOR_SCENE_6;
		break;
	}
	case SCENE_GIFT:
	{
		ani = ID_ANI_DOOR_GIFT;
		break;
	}
	default:
		ani = ID_ANI_DOOR_SCENE_1;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void Door::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - DOOR_BBOX_WIDTH / 2;
	t = y - DOOR_BBOX_HEIGHT / 2;
	r = l + DOOR_BBOX_WIDTH;
	b = t + DOOR_BBOX_HEIGHT;
}
