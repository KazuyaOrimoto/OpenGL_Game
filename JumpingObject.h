#pragma once
#include "ObstacleBox.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;
class JumpingArea;

class JumpingObject :
	public ObstacleBox
{
public:
	JumpingObject(Game* _game);
	~JumpingObject();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(GameObject& _hitObject) override;

	inline virtual void SetPosition(const Vector3& _pos)override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
	JumpingArea* jumpingArea;
};

