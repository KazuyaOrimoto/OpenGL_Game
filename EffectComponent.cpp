#include "EffectComponent.h"
#include <codecvt>
#include "EffekseerManager.h"

EffectComponent::EffectComponent(GameObject* _owner)
	:Component(_owner)
	, position(Vector3::Zero)
	, handle(-1)
{
}

EffectComponent::~EffectComponent()
{
	EFFECT_MANAGER->StopEffect(handle);
}

void EffectComponent::LoadEffect(std::string _filename, Vector3 _position)
{
	std::wstring wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(_filename);
	handle = EFFECT_MANAGER->PlayEffect(wstr, _position);
}

void EffectComponent::Stop()
{
	EFFECT_MANAGER->SetPausedEffect(handle, true);
}

void EffectComponent::Play()
{
	EFFECT_MANAGER->SetPausedEffect(handle, false);
}

void EffectComponent::SetPosition(const Vector3 & _pos)
{
	position = _pos;
	EFFECT_MANAGER->SetPosition(handle, position);
}

void EffectComponent::SetRotation(const Quaternion & _rot)
{
	rotation = _rot;
	EFFECT_MANAGER->SetRotation(handle,rotation);
}

void EffectComponent::SetSize(const Vector3 & _size)
{
	size = _size;
	EFFECT_MANAGER->SetSize(handle,size);
}

