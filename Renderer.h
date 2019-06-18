#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
    // Direction of light
    Vector3 direction;
    // Diffuse color
    Vector3 diffuseColor;
    // Specular color
    Vector3 specColor;
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
    Renderer(Game* argGame);
    ~Renderer();

    bool Initialize(float argScreenWidth, float argScreenHeight);
    void Shutdown();
    void UnloadData();

    void Draw();

	/**
	@brief  �X�v���C�g�̒ǉ�
	@param	�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  �X�v���C�g�̍폜
	@param	�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  �e�N�X�`���̎擾
	@param	�擾�������e�N�X�`���̃t�@�C����
	@return �e�N�X�`���̃|�C���^
	*/
	Texture* GetTexture(const std::string& argFileName);


    void AddMeshComp(MeshComponent* argMeshComponent);
    void RemoveMeshComp(MeshComponent* argMeshComponent);

    Mesh* GetMesh(const std::string& argFileName);

    void SetViewMatrix(const Matrix4& argView) { view = argView; }

    void SetAmbientLight(const Vector3& argAmbient) { ambientLight = argAmbient; }
    DirectionalLight& GetDirectionalLight() { return dirLight; }

    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }
private:
	/**
	@brief  �V�F�[�_�[�̓ǂݍ���
	*/
    bool LoadShaders();
	/**
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
    void CreateSpriteVerts();
    void SetLightUniforms(Shader* argShader);

    // Map of meshes loaded
    std::unordered_map<std::string, Mesh*> meshes;

    // All mesh components drawn
    std::vector<MeshComponent*> meshComponents;

	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̉ϒ��R���e�i
	std::unordered_map<std::string, Texture*>textures;

    // Game
    Game* game;

    // Sprite shader
    Shader* spriteShader;
    // Sprite vertex array
    VertexArray* spriteVerts;

    // Mesh shader
    Shader* meshShader;

    // View/projection for 3D shaders
    Matrix4 view;
    Matrix4 projection;
    // Width/height of screen
    float screenWidth;
    float screenHeight;

    // Lighting data
    Vector3 ambientLight;
    DirectionalLight dirLight;

    // Window
    SDL_Window* window;
    // OpenGL context
    SDL_GLContext context;
};