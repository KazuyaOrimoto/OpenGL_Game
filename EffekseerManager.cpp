#include "EffekseerManager.h"

EffekseerManager*                   EffekseerManager::manager = nullptr;
::Effekseer::Manager*               EffekseerManager::g_manager = nullptr;
::EffekseerRenderer::Renderer*	    EffekseerManager::g_renderer = nullptr;
::Effekseer::Effect*				EffekseerManager::g_effect = nullptr;
::Effekseer::Handle				    EffekseerManager::g_handle = -1;
::Effekseer::Vector3D			    EffekseerManager::g_position;

EffekseerManager::EffekseerManager()
{
}


EffekseerManager::~EffekseerManager()
{
}
