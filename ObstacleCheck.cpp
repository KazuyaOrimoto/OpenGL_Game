#include "ObstacleCheck.h"
#include "BikeObject.h"
#include "BoxCollider.h"

ObstacleCheck::ObstacleCheck(BikeObject* _bike)
	: GameObject()
	, bike(_bike)
	, onObstacle(false)
	, wasCollidedObstacle(false)
{
	SetPosition(bike->GetPosition());
	BoxCollider* sphereCollider = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = AABB(CHECK_AREA_MIN, CHECK_AREA_MAX);
	sphereCollider->SetObjectBox(box);
	SetScale(1.0f);
	tag = Tag::CheckArea;
	
}

ObstacleCheck::~ObstacleCheck()
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void ObstacleCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(bike->GetPosition());
	//障害物と衝突していなかったら
	if (!wasCollidedObstacle)
	{
		//障害物とぶつかっていない
		onObstacle = false;
	}
	else
	{
		//リセット
		wasCollidedObstacle = false;
	}
}

void ObstacleCheck::OnCollision(const GameObject & _hitObject)
{
	if (_hitObject.GetTag() == Tag::Obstacle)
	{
		onObstacle = true;
		wasCollidedObstacle = true;
	}
}
