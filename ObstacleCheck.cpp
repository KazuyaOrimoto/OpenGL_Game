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
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void ObstacleCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(bike->GetPosition());
	//��Q���ƏՓ˂��Ă��Ȃ�������
	if (!wasCollidedObstacle)
	{
		//��Q���ƂԂ����Ă��Ȃ�
		onObstacle = false;
	}
	else
	{
		//���Z�b�g
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
