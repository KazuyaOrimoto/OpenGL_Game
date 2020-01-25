#pragma once
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>
#include <vector>
#include <map>
#include <string>
#include "Math.h"

#define EFFECT_MANAGER EffekseerManager::GetInstance()

class EffekseerManager
{
public:
    /**
    @brief  インスタンスを取得する
    @return Rendererクラスのインスタンス
    */
    static EffekseerManager* GetInstance() { return manager; }

    /**
    @brief  インスタンスを作成する
    */
    static void CreateInstance();

    /**
    @brief  インスタンスを削除する
    */
    static void DeleteInstance();

	void InitEffekseer();

	/**
	@brief  終了処理
	*/
	void Shutdown();

	void Update();

	void UpdateCameraMatrix();

	void Draw();

	int PlayEffect(std::wstring _fileName);

	void StopEffect(int _effectHandle);

	void BeginRendering() { g_renderer->BeginRendering(); }
	void EndRendering() { g_renderer->EndRendering(); }

private:
    EffekseerManager();
    ~EffekseerManager();

    static ::Effekseer::Manager*			g_manager;
    static ::EffekseerRenderer::Renderer*	g_renderer;
    static ::Effekseer::Effect*				g_effect;
    static ::Effekseer::Handle				g_handle;

    static EffekseerManager* manager;

	int counter = 0;

	//ファイル名でメッシュを取得するための連想配列
	std::map<std::wstring, Effekseer::Effect*> effects;
	std::map<int, Effekseer::Handle> handles;

};

