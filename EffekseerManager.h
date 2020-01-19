#pragma once
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

#define EFFECT_MANAGER EffekseerManager::GetInstance()

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

	void InitEffekseer();

	/**
	@brief  �I������
	*/
	void Shutdown();

	void Update();

	void UpdateCameraMatrix();

	void Draw();

private:
    EffekseerManager();
    ~EffekseerManager();

    static ::Effekseer::Manager*			g_manager;
    static ::EffekseerRenderer::Renderer*	g_renderer;
    static ::Effekseer::Effect*				g_effect;
    static ::Effekseer::Handle				g_handle;

    static EffekseerManager* manager;

	

};

