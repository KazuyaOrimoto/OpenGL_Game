#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;

class ObstacleBox :public GameObject
{
public:
	ObstacleBox(Game* game);
	~ObstacleBox();

	int GetHardness() const { return hardness; }

	virtual void OnCollision(GameObject& argHitObject) override;

	void HitPlayer(const PlayerObject& argPlayerObject);
	void ResetObstacle();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float argDaltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	int hardness;
	GameObject* player;
};

