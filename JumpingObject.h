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
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
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

