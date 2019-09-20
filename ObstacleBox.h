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

	int GetHardness() const { return hardness; }

	virtual void OnCollision(GameObject& _hitObject) override;

	void HitPlayer(const PlayerObject& _playerObject);
	void ResetObstacle();
	void UseObstacle();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	int hardness;
	GameObject* player;
};

