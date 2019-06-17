#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
    // Direction of light
    Vector3 mDirection;
    // Diffuse color
    Vector3 mDiffuseColor;
    // Specular color
    Vector3 mSpecColor;
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;

class Renderer
{
public:
    Renderer(Game* game);
    ~Renderer();

    bool Initialize(float screenWidth, float screenHeight);
    void Shutdown();
    void UnloadData();

    void Draw();

	/**
	@brief  �X�v���C�g�̒ǉ�
	@param	�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* argSprite);

	/**
	@brief  �X�v���C�g�̍폜
	@param	�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* argSprite);

	/**
	@brief  �e�N�X�`���̎擾
	@param	�擾�������e�N�X�`���̃t�@�C����
	@return �e�N�X�`���̃|�C���^
	*/
	Texture* GetTexture(const std::string& argFileName);


    void AddMeshComp(MeshComponent* mesh);
    void RemoveMeshComp(MeshComponent* mesh);

    Mesh* GetMesh(const std::string& fileName);

    void SetViewMatrix(const Matrix4& view) { mView = view; }

    void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
    DirectionalLight& GetDirectionalLight() { return mDirLight; }

    float GetScreenWidth() const { return mScreenWidth; }
    float GetScreenHeight() const { return mScreenHeight; }
private:
	/**
	@brief  �V�F�[�_�[�̓ǂݍ���
	*/
    bool LoadShaders();
	/**
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
    void CreateSpriteVerts();
    void SetLightUniforms(Shader* shader);

    // Map of meshes loaded
    std::unordered_map<std::string, Mesh*> meshes;

    // All mesh components drawn
    std::vector<MeshComponent*> meshComponents;

	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̉ϒ��R���e�i
	std::unordered_map<std::string, Texture*>textures;

    // Game
    Game* mGame;

    // Sprite shader
    Shader* mSpriteShader;
    // Sprite vertex array
    VertexArray* mSpriteVerts;

    // Mesh shader
    Shader* mMeshShader;

    // View/projection for 3D shaders
    Matrix4 mView;
    Matrix4 mProjection;
    // Width/height of screen
    float mScreenWidth;
    float mScreenHeight;

    // Lighting data
    Vector3 mAmbientLight;
    DirectionalLight mDirLight;

    // Window
    SDL_Window* mWindow;
    // OpenGL context
    SDL_GLContext mContext;
};