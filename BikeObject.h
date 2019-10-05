#pragma once
#include "GameObject.h"

class PlayerObject;
class MeshComponent;
class SphereCollider;
class ObstacleBox;
class JumpCheck;

static Vector3 CHECK_AREA_MIN = Vector3(1500.0f, -1.0f, -1.0f);
static Vector3 CHECK_AREA_MAX = Vector3(2500.0f, 1.0f, 1.0f);

class BikeObject : public GameObject
{
public:
	BikeObject(PlayerObject* _ownerObject);
    ~BikeObject();

    /**
    @brief	�t���[�����̏���
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    virtual void UpdateGameObject(float _deltaTime) override;

    virtual void OnCollision(const GameObject& _hitObject) override;

    /**
    @brief	���͏���
    @param	InputState�\����
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

