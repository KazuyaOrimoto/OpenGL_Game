#include "JumpCheck.h"
#include "BikeObject.h"
#include "BoxCollider.h"

JumpCheck::JumpCheck(BikeObject* _bike)
	: GameObject()
	, bike(_bike)
	, canJump(false)
	, wasCollidedObstacle(false)
{
	SetPosition(bike->GetPosition());
	BoxCollider* sphereCollider = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = AABB(CHECK_AREA_MIN, CHECK_AREA_MAX);
	sphereCollider->SetObjectBox(box);
	SetScale(1.0f);
	tag = Tag::CheckArea;
}

JumpCheck::~JumpCheck()
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void JumpCheck::UpdateGameObject(float _deltaTime)
{
	//bikeの前方少し上に自分のポジションを設定する
	Vector3 bikePos = bike->GetPosition();
	//bikeのポジションからbikeの上方向に移動させる
	Vector3 myPos = bikePos + bike->GetUp() * 200.0f;
	SetPosition(myPos);

	//障害物と衝突していなかったら
	if (!wasCollidedObstacle)
	{
		//ジャンプ可能
		canJump = true;
	}
	else
	{
		//リセット
		wasCollidedObstacle = false;
	}
}

void JumpCheck::OnCollision(const GameObject & _hitObject)
{
	if (_hitObject.GetTag() == Tag::Obstacle)
	{
		canJump = false;
		wasCollidedObstacle = true;
	}
}
