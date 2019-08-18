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
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float argDaltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	int hardness;
	GameObject* player;
};

