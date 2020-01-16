#include "GameObjectCreater.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxObject.h"
#include "ObstacleObject.h"
#include "WallObject.h"
#include "ObstacleBox.h"
#include "Ship.h"

void GameObjectCreater::PlayerAndWallCreate()
{
	GameObject* mCameraActor = new PlayerObject();

	ObstacleBox* box;
	for (int i = 0; i < 500; i++)
	{
		box = new ObstacleBox();
	}

	for (int i = 0; i < StaticObstacle::ObstacleMaxNum; i++)
	{
		ObstacleObject* obstacle = new ObstacleObject(i);
	}

	for (int i = 0; i < 20; i++)
	{
		GameObject* wall = new WallObject(i);
	}
}