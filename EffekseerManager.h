#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <string>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Wingdi.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "winmm.lib")

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

#if _DEBUG
#pragma comment(lib, "VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2015/Debug/EffekseerRendererGL.lib" )
#else
#pragma comment(lib, "VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "VS2015/Release/EffekseerRendererGL.lib" )
#endif

class EffekseerManager
{
public:
    /**
    @brief  �C���X�^���X���擾����
    @return Renderer�N���X�̃C���X�^���X
    */
    static EffekseerManager* GetInstance() { return manager; }

    /**
    @brief  �C���X�^���X���쐬����
    */
    static void CreateInstance();

    /**
    @brief  �C���X�^���X���폜����
    */
    static void DeleteInstance();


private:
    EffekseerManager();
    ~EffekseerManager();

    static ::Effekseer::Manager*			g_manager;
    static ::EffekseerRenderer::Renderer*	g_renderer;
    static ::Effekseer::Effect*				g_effect;
    static ::Effekseer::Handle				g_handle;
    static ::Effekseer::Vector3D			g_position;

    static EffekseerManager* manager;
};

