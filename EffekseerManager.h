#pragma once
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>
#include <vector>
#include <map>
#include <string>

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

	int LoadEffect(std::string _fileName);

private:
    EffekseerManager();
    ~EffekseerManager();

    static ::Effekseer::Manager*			g_manager;
    static ::EffekseerRenderer::Renderer*	g_renderer;
    static ::Effekseer::Effect*				g_effect;
    static ::Effekseer::Handle				g_handle;

    static EffekseerManager* manager;

	int counter = 0;

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::map<std::string, Effekseer::Effect*> effects;
	std::map<int, Effekseer::Handle> handles;

};

