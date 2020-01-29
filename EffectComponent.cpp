#include "EffectComponent.h"
#include <codecvt>
#include "EffekseerManager.h"

EffectComponent::EffectComponent(GameObject* _owner)
    :Component(_owner)
    , position(Vector3::Zero)
{
}


EffectComponent::~EffectComponent()
{
}

void EffectComponent::LoadEffect(std::string _filename)
{
    std::wstring wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(_filename);
    handle = EFFECT_MANAGER->PlayEffect(wstr);

}

void EffectComponent::Stop()
{
    EFFECT_MANAGER->SetPausedEffect(handle,false);
}

void EffectComponent::Play()
{
    EFFECT_MANAGER->SetPausedEffect(handle, true);
}
