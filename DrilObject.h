#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleObject;

class DrilObject : public GameObject
{
public:
    DrilObject(Game* game, PlayerObject* ownerObject);
    ~DrilObject();

    /**
    @brief	�t���[�����̏���
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    virtual void UpdateGameObject(float argDeltaTime) override;

    virtual void OnCollision(GameObject& argHitObject) override;

    void HitObstacle(const ObstacleObject & argHitObstacle);

private:
    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

};

