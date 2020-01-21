#include "EffekseerManager.h"
#include "Renderer.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <assert.h>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Wingdi.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "winmm.lib")

#if _DEBUG
#pragma comment(lib, "VS2017/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2017/Debug/EffekseerRendererGL.lib" )
#else
#pragma comment(lib, "VS2017/Release/Effekseer.lib" )
#pragma comment(lib, "VS2017/Release/EffekseerRendererGL.lib" )
#endif

EffekseerManager*					EffekseerManager::manager = nullptr;
::Effekseer::Manager*               EffekseerManager::g_manager = nullptr;
::EffekseerRenderer::Renderer*	    EffekseerManager::g_renderer = nullptr;
::Effekseer::Effect*				EffekseerManager::g_effect = nullptr;
::Effekseer::Handle				    EffekseerManager::g_handle = -1;

#if _WIN32
static std::wstring ToWide(const char* pText)
{
	int Len = ::MultiByteToWideChar(CP_ACP, 0, pText, -1, NULL, 0);

	wchar_t* pOut = new wchar_t[Len + 1];
	::MultiByteToWideChar(CP_ACP, 0, pText, -1, pOut, Len);
	std::wstring Out(pOut);
	delete[] pOut;

	return Out;
}

void GetDirectoryName(char* dst, char* src)
{
	auto Src = std::string(src);
	int pos = 0;
	int last = 0;
	while (Src.c_str()[pos] != 0)
	{
		dst[pos] = Src.c_str()[pos];

		if (Src.c_str()[pos] == L'\\' || Src.c_str()[pos] == L'/')
		{
			last = pos;
		}

		pos++;
	}

	dst[pos] = 0;
	dst[last] = 0;
}
#endif

void EffekseerManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new EffekseerManager();
	}
}

void EffekseerManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
		manager = nullptr;
	}
}

void EffekseerManager::InitEffekseer()
{
	// 投影行列を設定
	Matrix4 mat4 = RENDERER->GetProjectionMatrix();
	::Effekseer::Matrix44 mat = RENDERER->GetProjectionMatrix().GetEffekseerMatrix44();
	g_renderer->SetProjectionMatrix(mat);

	// カメラ行列を設定
	g_renderer->SetCameraMatrix(RENDERER->GetViewMatrix().GetEffekseerMatrix44());

	// エフェクトの読込
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Assets/test.efk");

	// エフェクトの再生
	g_handle = g_manager->Play(g_effect, 0, 0, 0);
}

void EffekseerManager::Shutdown()
{
	// エフェクトの停止
	g_manager->StopEffect(g_handle);

	// 先にエフェクト管理用インスタンスを破棄
	g_manager->Destroy();

	// 次に描画用インスタンスを破棄
	g_renderer->Destroy();
}

void EffekseerManager::Update()
{
	// エフェクトの移動処理を行う
	g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// エフェクトの更新処理を行う
	g_manager->Update();
}

void EffekseerManager::UpdateCameraMatrix()
{
	// カメラ行列を設定
	::Effekseer::Matrix44 mat = RENDERER->GetProjectionMatrix().GetEffekseerMatrix44();
	g_renderer->SetProjectionMatrix(mat);
}

void EffekseerManager::Draw()
{

	// エフェクトの描画開始処理を行う。
	g_renderer->BeginRendering();

	// エフェクトの描画を行う。
	g_manager->Draw();

	// エフェクトの描画終了処理を行う。
	g_renderer->EndRendering();

}

int EffekseerManager::LoadEffect(std::string _fileName)
{
	Effekseer::Effect* effect;
	//一度読み込んだエフェクトかどうか
	effect = effects.at(_fileName);
	//読み込まれたことのないエフェクトだった場合
	if (effect == nullptr)
	{
		effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)_fileName.c_str());
		effects.insert(std::make_pair(_fileName, effect));
	}
	Effekseer::Handle handle = g_manager->Play(effect,Effekseer::Vector3D());
	g_manager->StopEffect(handle);
	auto itr = handles.find(counter);
	while (itr == handles.end())
	{
		counter++;
		itr = handles.find(counter);
	}


	return 0;
}

EffekseerManager::EffekseerManager()
{
	// 描画用インスタンスの生成
	g_renderer = ::EffekseerRendererGL::Renderer::Create(2000);

	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);

	// 描画用インスタンスから描画機能を設定
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());
}

EffekseerManager::~EffekseerManager()
{
}
