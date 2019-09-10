#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleBox;

class DrilObject : public GameObject
{
public:
    DrilObject(Game* _game, PlayerObject* _ownerObject);
    ~DrilObject();

    /**
    @brief	フレーム毎の処理
    @param	最後のフレームを完了するのに要した時間
    */
    virtual void UpdateGameObject(float _deltaTime) override;

    virtual void OnCollision(GameObject& _hitObject) override;

    void HitObstacle(const ObstacleBox & _hitObstacle);

    /**
    @brief	入力処理
    @param	InputState構造体
    */
    virtual void GameObjectInput(const InputState& _state)override;

private:
    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

};

