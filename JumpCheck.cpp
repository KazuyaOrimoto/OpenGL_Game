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
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void JumpCheck::UpdateGameObject(float _deltaTime)
{
	//bike�̑O��������Ɏ����̃|�W�V������ݒ肷��
	Vector3 bikePos = bike->GetPosition();
	//bike�̃|�W�V��������bike�̏�����Ɉړ�������
	Vector3 myPos = bikePos + bike->GetUp() * 200.0f;
	SetPosition(myPos);

	//��Q���ƏՓ˂��Ă��Ȃ�������
	if (!wasCollidedObstacle)
	{
		//�W�����v�\
		canJump = true;
	}
	else
	{
		//���Z�b�g
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
