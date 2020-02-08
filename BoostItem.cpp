#include "BoostItem.h"
#include "ObstacleManager.h"
#include "EffectComponent.h"

GameObject* BoostItem::player = nullptr;

BoostItem::BoostItem()
{
	comp = new EffectComponent(this);
	comp->LoadEffect("Effect/Boost.efk",position);
	comp->Stop();
	state = Paused;
	if (player == nullptr)
	{
		player = GameObject::FindGameObject(Tag::Player);
	}
	OBSTACLE_MANAGER->AddBoostItem(this);
	tag = Tag::Boost;
}

BoostItem::~BoostItem()
{
	OBSTACLE_MANAGER->RemoveBoostItem(this);
}

void BoostItem::OnCollision(const GameObject & _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{
		ResetBoostItem();
	}
}

void BoostItem::UpdateGameObject(float _deltaTime)
{
	if (player == nullptr)
	{
		return;
	}
	if (player->GetPosition().x - 2000.0f > position.x)
	{
		ResetBoostItem();
	}
	comp->SetPosition(position);
}

void BoostItem::ResetBoostItem()
{
	comp->Stop();
	state = Paused;
}

void BoostItem::UseBoostItem()
{
	comp->Play();
	state = Active;
	GameObject::RemoveGameObject(this);
	GameObject::AddGameObject(this);
}
