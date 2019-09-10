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
    @brief	�t���[�����̏���
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    virtual void UpdateGameObject(float _deltaTime) override;

    virtual void OnCollision(GameObject& _hitObject) override;

    void HitObstacle(const ObstacleBox & _hitObstacle);

    /**
    @brief	���͏���
    @param	InputState�\����
    */
    virtual void GameObjectInput(const InputState& _state)override;

private:
    MeshComponent* meshComp;
    PlayerObject* ownerObject;
    SphereCollider* sphereCollider;

};

