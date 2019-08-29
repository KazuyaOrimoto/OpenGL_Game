#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleBox;

class DrilObject : public GameObject
{
public:
    DrilObject(Game* game, PlayerObject* ownerObject);
    ~DrilObject();

    /**
    @brief	フレーム毎の処理
    @param	最後のフレームを完了するのに要した時間
    */
    virtual void UpdateGameObject(float argDeltaTime) override;

    virtual void OnCollision(GameObject& argHitObject) override;

    void HitObstacle(const ObstacleBox & argHitObstacle);

    /**
    @brief	入力処理
    @param	InputState構造体
    */
    virtual void GameObjectInput(const InputState& keyState)override;

private:
    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

};

