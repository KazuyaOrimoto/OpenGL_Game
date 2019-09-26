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
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

