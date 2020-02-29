//=============================================================================
//	@file	AutoRunComponent.h
//	@brief	自動で前方へ進めるコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "Component.h"

class PlayerModel;

class AutoRunComponent :
    public Component
{
public:
    AutoRunComponent(GameObject* _owner, int _updateOrder = 10);


    void Update(float _deltaTime) override;
    void SetForwardSpeed(float _value) { forwardSpeed = _value; }
    float GetForwardSpeed() const { return forwardSpeed; }
    void SetDrilObject(PlayerModel* _playerModel) { playerModel = _playerModel; }

private:

    float forwardSpeed;
	PlayerModel* playerModel;

};

