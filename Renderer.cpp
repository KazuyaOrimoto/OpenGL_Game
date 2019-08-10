#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>

Renderer* Renderer::renderer = nullptr;

Renderer::Renderer()
    : spriteShader(nullptr)
	, spriteVerts(nullptr)
    , meshShader(nullptr)
	, view(Matrix4::Identity)
	, projection(Matrix4::Identity)
	, screenWidth(0)
	, screenHeight(0)
	, ambientLight(Vector3::Zero)
{
}

Renderer::~Renderer()
{
}

/**
@brief  �C���X�^���X���쐬����
*/
void Renderer::CreateInstance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}


/**
@brief  �C���X�^���X���폜����
*/
void Renderer::DeleteInstance()
{
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

/**
@brief  ����������
@return true : ���� , false : ���s
*/
bool Renderer::Initialize(float argScreenWidth, float argScreenHeight)
{
    screenWidth = argScreenWidth;
    screenHeight = argScreenHeight;

    // OpenGL�̊e������ݒ肷��
    // �R�AOpenGL�v���t�@�C�����g��
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // OpenGL�̎g�p�o�[�W������3.3�Ɏw��
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // �_�u���o�b�t�@��L���ɂ���
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // �n�[�h�E�F�A�A�N�Z�����[�V�������g��
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//�E�B���h�E�̍쐬
    window = SDL_CreateWindow("Game Programming in C++ (Chapter 6)", 100, 100,
        static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // OpenGL�̃R���e�L�X�g���쐬
    context = SDL_GL_CreateContext(window);

    // GLEW�̏�����
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
    glGetError();

    // �V�F�[�_�[�̃��[�h
    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    //�X�v���C�g�p�̒��_�z����쐬
    CreateSpriteVerts();

    return true;
}

/**
@brief  �I������
*/
void Renderer::Shutdown()
{
    delete spriteVerts;
    spriteShader->Unload();
    delete spriteShader;
    meshShader->Unload();
    delete meshShader;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

/**
@brief  ���[�h�����f�[�^�̉��
*/
void Renderer::UnloadData()
{
    // ���ׂẴe�N�X�`���̃f�[�^�����
    for (auto i : textures)
    {
        i.second->Unload();
        delete i.second;
    }
	textures.clear();

    // ���ׂẴ��b�V���̃f�[�^�����
    for (auto i : meshes)
    {
        i.second->Unload();
        delete i.second;
    }
	meshes.clear();
}

/**
@brief  �`�揈��
*/
void Renderer::Draw()
{
    // �N���A�J���[���D�F�ɐݒ�
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // �J���[�o�b�t�@�ƃf�v�X�o�b�t�@���N���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���b�V���R���|�[�l���g�̕`��
    // �f�v�X�o�b�t�@�@��L���ɂ���
    glEnable(GL_DEPTH_TEST);
	//�A���t�@�u�����f�B���O�𖳌��ɂ���
    glDisable(GL_BLEND);
    // ��{�I�ȃ��b�V���V�F�[�_�[���A�N�e�B�u�ɂ���
    meshShader->SetActive();
    // �r���[�ˉe�s����X�V����
    meshShader->SetMatrixUniform("uViewProj", view * projection);
    // �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
    SetLightUniforms(meshShader);
	// ���ׂẴ��b�V���̕`��
    for (auto mc : meshComponents)
    {
		if (mc->GetVisible())
		{
			mc->Draw(meshShader);
		}
    }

    // �X�v���C�g�R���|�[�l���g�̕`��
    // �f�v�X�o�b�t�@�@�𖳌��ɂ���
    glDisable(GL_DEPTH_TEST);
    // �A���t�@�u�����f�B���O��L���ɂ���
    glEnable(GL_BLEND);
	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
    spriteShader->SetActive();
    spriteVerts->SetActive();
	// ���ׂẴX�v���C�g�̕`��
    for (auto sprite : sprites)
    {
        sprite->Draw(spriteShader);
    }

    // �o�b�t�@������
    SDL_GL_SwapWindow(window);
}

/**
@brief  �X�v���C�g�̍폜
@param	�폜����SpriteComponent�N���X�̃|�C���^
*/
void Renderer::AddSprite(SpriteComponent* argSpriteComponent)
{
    // ������X�v���C�g����}������ꏊ�̌���
    // (DrawOrder�����������Ԃɕ`�悷�邽��)
	int myDrawOrder = argSpriteComponent->GetDrawOrder();
    auto iter = sprites.begin();
    for (;
        iter != sprites.end();
        ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // ���������ꏊ��iter�̏ꏊ�ɑ}��
	sprites.insert(iter, argSpriteComponent);
}

/**
@brief  �X�v���C�g�̍폜
@param	�폜����SpriteComponent�N���X�̃|�C���^
*/
void Renderer::RemoveSprite(SpriteComponent* argSpriteComponent)
{
    auto iter = std::find(sprites.begin(), sprites.end(), argSpriteComponent);
	sprites.erase(iter);
}

/**
@brief  ���b�V���R���|�[�l���g�̒ǉ�
@param	�ǉ�����MeshComponent�N���X�̃|�C���^
*/
void Renderer::AddMeshComponent(MeshComponent* argMeshComponent)
{
	meshComponents.emplace_back(argMeshComponent);
}

/**
@brief  ���b�V���R���|�[�l���g�̍폜
@param	�폜����MeshComponent�N���X�̃|�C���^
*/
void Renderer::RemoveMeshComponent(MeshComponent* argMeshComponent)
{
    auto iter = std::find(meshComponents.begin(), meshComponents.end(), argMeshComponent);
    meshComponents.erase(iter);
}

/**
@brief  �e�N�X�`���̎擾
@param	�擾�������e�N�X�`���̃t�@�C����
@return Texture�N���X�̃|�C���^
*/
Texture* Renderer::GetTexture(const std::string& argFileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = textures.find(argFileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		texture = new Texture();
		if (texture->Load(argFileName))
		{
			textures.emplace(argFileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/**
@brief  ���b�V���̎擾
@param	�擾���������b�V���̃t�@�C����
@return Mesh�N���X�̃|�C���^
*/
Mesh* Renderer::GetMesh(const std::string &argFfileName)
{
    Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
    auto iter = meshes.find(argFfileName);
    if (iter != meshes.end())
    {
        m = iter->second;
    }
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
    else
    {
        m = new Mesh();
        if (m->Load(argFfileName, this))
        {
			meshes.emplace(argFfileName, m);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

/**
@brief  �V�F�[�_�[�̓ǂݍ���
@return true : ���� , false : ���s
*/
bool Renderer::LoadShaders()
{
    // �X�v���C�g�V�F�[�_�[�̍쐬
    spriteShader = new Shader();
    if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
    {
        return false;
    }

    spriteShader->SetActive();
    // �r���[�s��̐ݒ�
    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
    spriteShader->SetMatrixUniform("uViewProj", viewProj);

    // �W���̃��b�V���V�F�[�_�[�̍쐬
    meshShader = new Shader();
    if (!meshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
    {
        return false;
    }

    meshShader->SetActive();
    // �r���[�s��̐ݒ�
    view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
        screenWidth, screenHeight, 25.0f, 10000.0f);
    meshShader->SetMatrixUniform("uViewProj", view * projection);
    return true;
}

/**
@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void Renderer::CreateSpriteVerts()
{
    float vertices[] = {
        -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
        0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
        0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
        -0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    spriteVerts = new VertexArray(vertices, 4, indices, 6);
}


/**
@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param  �Z�b�g����Shader�N���X�̃|�C���^
*/
void Renderer::SetLightUniforms(Shader* shader)
{
	// �r���[�s���]�u�s��ɂ���
    Matrix4 invView = view;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    // �����̐ݒ�
    shader->SetVectorUniform("uAmbientLight", ambientLight);
    // ���s�����̐ݒ�
    shader->SetVectorUniform("uDirLight.mDirection",
        dirLight.direction);
    shader->SetVectorUniform("uDirLight.mDiffuseColor",
        dirLight.diffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor",
        dirLight.specColor);
}
