#include "BoostItem.h"
#include "EffectComponent.h"

BoostItem::BoostItem()
{
	//comp = new EffectComponent(this);
	//comp->LoadEffect("Effect/Boost.efk",position);
	//comp->Play();
}

BoostItem::~BoostItem()
{
}

void BoostItem::OnCollision(const GameObject & _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{


	}
}

void BoostItem::UpdateGameObject(float _deltaTime)
{
	//comp->SetPosition(position);
}
