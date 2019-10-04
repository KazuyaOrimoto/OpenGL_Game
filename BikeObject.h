#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleBox;
class JumpCheck;

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

private:

	void Animation();

    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

	bool animation;
	int animNum;

};

