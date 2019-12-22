#pragma once
#include "GameObject.h"

class PlayerObject;
class HDRMeshComponent;
class SphereCollider;
class ObstacleBox;
class JumpCheck;
class ObstacleCheck;
class ActionArea;
class AnimationComponent;
class PlayerAnimationController;
class MainCamera;

static Vector3 CHECK_AREA_MIN = Vector3(1500.0f, -1.0f, -1.0f);
static Vector3 CHECK_AREA_MAX = Vector3(2500.0f, 1.0f, 1.0f);

class BikeObject : public GameObject
{
public:
	BikeObject(PlayerObject* _ownerObject);
    ~BikeObject();

    /**
    @brief	フレーム毎の処理
    @param	最後のフレームを完了するのに要した時間
    */
    virtual void UpdateGameObject(float _deltaTime) override;

    virtual void OnCollision(const GameObject& _hitObject) override;

    /**
    @brief	入力処理
    @param	InputState構造体
    */
    virtual void GameObjectInput(const InputState& _state)override;

	bool CanMove();

	MainCamera* GetCamera() { return camera; }

private:
	void Animation();
	/**
	@brief	アクションを決定する
	*/
	void ActionDetermining();

	HDRMeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;
	AnimationComponent* animationComp;
	PlayerAnimationController* controller;

	JumpCheck* jumpCheck;
	ObstacleCheck* obstacleCheck;
	MainCamera* camera;

	bool animation;
	int animNum;
	bool canJumping;
	ActionArea* action;

	bool jump;
};

