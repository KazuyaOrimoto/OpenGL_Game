//=============================================================================
//	@file	AutoRunComponent.h
//	@brief	自動で前方へ進めるコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "AutoRunComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerModel.h"

AutoRunComponent::AutoRunComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, forwardSpeed(0.0f)
{
}

void AutoRunComponent::Update(float _deltaTime)
{
	if (_deltaTime > 0.02)
	{
		return;
	}
	Vector3 pos = owner->GetPosition();
	pos += owner->GetForward() * forwardSpeed * 0.016;
	owner->SetPosition(pos);
	if (playerModel != nullptr)
	{
		playerModel->SetPosition(pos);
	}
}
