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
	// ���e�s���ݒ�
	::Effekseer::Matrix44 mat = ::Effekseer::Matrix44().PerspectiveFovRH_OpenGL(50.0f / 180.0f * 3.14f, (float)RENDERER->GetScreenWidth() / (float)RENDERER->GetScreenHeight(), 1.0f, 13000.0f);
	g_renderer->SetProjectionMatrix(mat);

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(RENDERER->GetViewMatrix().GetEffekseerMatrix44());

	// �G�t�F�N�g�̓Ǎ�
	//g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Effect/Fire.efk");

	// �G�t�F�N�g�̍Đ�
	//g_handle = g_manager->Play(g_effect, 0, 0, 60);

	g_renderer->SetRestorationOfStatesFlag(true);
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
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// �G�t�F�N�g�̍X�V�������s��
	g_manager->Update();
}

void EffekseerManager::UpdateCameraMatrix()
{
	// �J�����s���ݒ�
	::Effekseer::Matrix44 mat = RENDERER->GetProjectionMatrix().GetEffekseerMatrix44();
	g_renderer->SetProjectionMatrix(mat);
}

void EffekseerManager::Draw()
{

	::Effekseer::Matrix44 m44 = g_renderer->GetCameraMatrix();
	Matrix4 m4 = RENDERER->GetViewMatrix();
	g_renderer->SetCameraMatrix(m4.GetEffekseerMatrix44());

	::Effekseer::Matrix44 _m44 = g_renderer->GetCameraProjectionMatrix();
	Matrix4 _m4 = RENDERER->GetProjectionMatrix();


	// �G�t�F�N�g�̕`����s���B
	g_manager->Draw();

}

int EffekseerManager::LoadEffect(std::wstring _fileName)
{
	Effekseer::Effect* effect = nullptr;
	//��x�ǂݍ��񂾃G�t�F�N�g���ǂ���
	{
		effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)(_fileName.c_str()));
	}
	Effekseer::Handle handle = g_manager->Play(effect, Effekseer::Vector3D(0.0f, 0.0f, 0.0f));
	g_manager->SetPaused(handle, false);
	return handle;
}

int EffekseerManager::PlayEffect(std::wstring _fileName, Vector3 _position)
{
	Effekseer::Effect* effect = nullptr;
	//��x�ǂݍ��񂾃G�t�F�N�g���ǂ���
	{
		effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)(_fileName.c_str()));
	}
	Effekseer::Handle handle = g_manager->Play(effect, _position.GetEffekseerVector3D());
	return handle;
}

void EffekseerManager::SetPosition(int _handle, const Vector3& _position)
{
	g_manager->SetLocation(_handle, _position.GetEffekseerVector3D());
}

void EffekseerManager::SetRotation(int _handle, const Quaternion& rotaiton)
{
	g_manager->SetRotation(_handle, Effekseer::Vector3D(rotaiton.x, rotaiton.y, rotaiton.z), rotaiton.w);
}

void EffekseerManager::SetSize(int _handle, const Vector3 _size)
{
	g_manager->SetScale(_handle, _size.x, _size.y, _size.z);
}

void EffekseerManager::SetPausedEffect(int _handle, bool _pause)
{
	g_manager->SetPaused(_handle, _pause);
	g_manager->SetShown(_handle,!_pause);
}


void EffekseerManager::SetCameraParameter(Vector3 & _position, Vector3 & _front)
{
	::Effekseer::Vector3D front = _front.GetEffekseerVector3D();
	::Effekseer::Vector3D position = _position.GetEffekseerVector3D();
	g_renderer->SetCameraParameter(front, position);
}

void EffekseerManager::StopEffect(int _handle)
{
	g_manager->StopEffect(_handle);
}

EffekseerManager::EffekseerManager()
{
	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererGL::Renderer::Create(1000);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());
}

EffekseerManager::~EffekseerManager()
{
}
