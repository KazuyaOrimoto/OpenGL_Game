//=============================================================================
//	@file	PlayerModel.h
//	@brief	プレイヤーのモデル関連の処理をする
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"

class PlayerObject;
class HDRMeshComponent;
class SphereCollider;
class ObstacleBox;
class JumpCheck;
class ObstacleCheck;
class MainCamera;

static Vector3 CHECK_AREA_MIN = Vector3(1500.0f, -1.0f, -1.0f);
static Vector3 CHECK_AREA_MAX = Vector3(2500.0f, 1.0f, 1.0f);

class PlayerModel : public GameObject
{
public:
	PlayerModel(PlayerObject* _ownerObject);
    ~PlayerModel();

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

	HDRMeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

	MainCamera* camera;

	bool animation;
	int animNum;
	bool canJumping;

	bool jump;
};

