#pragma once
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>


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

	static void InitEffekseer(char** _argv);

	/**
	@brief  終了処理
	*/
	void Shutdown();

	void Update();

	void Draw();

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

