#pragma once
#include "GameObject.h"

class MoveComponent;
class MeshComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;
class ObstacleObject;
class RotateComponent;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Game* game);

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float argDaltaTime);

	/**
	@brief	描画するかどうかを設定する
	@param	true : 描画する , false : 描画しない
	*/
    void SetVisible(bool visible);

	RotateComponent* GetRotate() const { return rotate; }

	virtual void OnCollision(GameObject& argHitObject) override;

	void HitObstacle(const ObstacleObject & argHitObstacle);

private:
    MoveComponent* moveComp;
    MeshComponent* meshComp;
    SphereCollider* sphereCollider;
    MainCamera* camera;
    AutoRunComponent* autoRun;
	RotateComponent* rotate;
};

