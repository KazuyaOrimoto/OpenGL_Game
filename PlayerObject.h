#pragma once
#include "GameObject.h"

class MoveComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;
class ObstacleObject;
class RotateComponent;
class BikeObject;

class PlayerObject : public GameObject
{
public:
	PlayerObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	RotateComponent* GetRotate() const { return rotate; }

    bool CanMove();

private:
    MoveComponent* moveComp;
    MainCamera* camera;
    AutoRunComponent* autoRun;
	RotateComponent* rotate;
    SphereCollider* sphereCollider;
	BikeObject* dril;
};

