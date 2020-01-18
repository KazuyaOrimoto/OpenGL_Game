#include "EffekseerManager.h"
#include "Renderer.h"

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
::Effekseer::Vector3D			    EffekseerManager::g_position;

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

void EffekseerManager::InitEffekseer(char** _argv)
{
#if _WIN32
	char current_path[MAX_PATH + 1];
	GetDirectoryName(current_path, _argv[0]);
	SetCurrentDirectoryA(current_path);
#endif

	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererGL::Renderer::Create(2000);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// ���_�ʒu���m��
	g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH_OpenGL(Math::ToRadians(70.0f), (float)RENDERER->GetScreenWidth() / (float)RENDERER->GetScreenHeight(), 25.0f, 13000.0f));

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

}

void EffekseerManager::Shutdown()
{
	// �G�t�F�N�g�̒�~
	g_manager->StopEffect(g_handle);

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();
}

void EffekseerManager::Update()
{
	// �G�t�F�N�g�̈ړ��������s��
	g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// �G�t�F�N�g�̍X�V�������s��
	g_manager->Update();

}

void EffekseerManager::Draw()
{
	// �G�t�F�N�g�̕`��J�n�������s���B
	g_renderer->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	g_manager->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	g_renderer->EndRendering();
}

EffekseerManager::EffekseerManager()
{

}


EffekseerManager::~EffekseerManager()
{
}
