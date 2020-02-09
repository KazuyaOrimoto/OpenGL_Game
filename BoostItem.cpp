#include "BoostItem.h"
#include "ObstacleManager.h"
#include "EffectComponent.h"
#include "Math.h"
#include "BoxCollider.h"

GameObject* BoostItem::player = nullptr;

BoostItem::BoostItem()
{
	comp = new EffectComponent(this);
	comp->LoadEffect("Effect/Boost.efk", position);
	comp->Stop();
	state = Paused;
	if (player == nullptr)
	{
		player = GameObject::FindGameObject(Tag::Player);
	}
	OBSTACLE_MANAGER->AddBoostItem(this);
	tag = Tag::Boost;	
	SetScale(100.0f);
	BoxCollider* b = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = { Vector3(-1.0f,-1.0f,-1.0f) , Vector3(1.0f,1.0f,1.0f) };
	b->SetObjectBox(box);
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
	Vector3 down = (GetRight() * -1) * 100;
	comp->SetPosition(position + down);
	//comp->SetPosition(position);
	Quaternion r = Quaternion(1.0f, 0.0f, 0.0f, Math::ToRadians(rot));
	comp->SetRotation(r);
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
	rotation = Quaternion::Identity;
}

void BoostItem::SetRot(float _rot)
{
	rot = _rot;
}
