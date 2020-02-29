//=============================================================================
//	@file	EffekseerManager.h
//	@brief	Effekseerのエフェクトを管理する
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once

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

	/**
	@brief  初期化処理
	*/
	void Initialize();

	/**
	@brief  終了処理
	*/
	void Shutdown();

	void Update();

	void UpdateCameraMatrix();

	void Draw();

	int LoadEffect(std::wstring _fileName);
	int PlayEffect(std::wstring _fileName , Vector3 _position = Vector3::Zero);

    void SetPosition(int _handle,const Vector3& _position);
    void SetRotation(int _handle,const Quaternion& rotaiton);
    void SetSize(int _handle,const Vector3 _size);

    void SetPausedEffect(int _handle,bool _pause);

	void SetCameraParameter(Vector3& _position,  Vector3& _front);

	void StopEffect(int _handle);

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

	std::map<std::wstring, Effekseer::Effect*> effects;

};

