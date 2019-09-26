#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;

class ObstacleBox :public GameObject
{
public:
	ObstacleBox(Game* _game);
	~ObstacleBox();

	virtual void OnCollision(GameObject& _hitObject) override;

	void HitPlayer(const PlayerObject& _playerObject);
	virtual void ResetObstacle();
	virtual void UseObstacle();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

