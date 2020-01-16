#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"

#define RENDERER Renderer::GetInstance()

const int SAMPLE_NUM = 15;

//平行光源用の構造体
struct DirectionalLight
{
    // 光の方向
    Vector3 direction;
    // 拡散反射色
    Vector3 diffuseColor;
    // 鏡面反射色
    Vector3 specColor;
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;

//シェーダーとメッシュを紐づけるための構造体
struct ShaderToMesh
{
	std::string shaderName;
	Shader* shader;
	std::vector<MeshComponent*> meshComponentArray;
};

class Renderer
{
public:
	/**
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static Renderer* GetInstance() { return renderer; }

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
	@return true : 成功 , false : 失敗
	*/
    bool Initialize(float _screenWidth, float _screenHeight);
	/**
	@brief  終了処理
	*/
    void Shutdown();

	/**
	@brief  ロードしたデータの解放
	*/
    void UnloadData();

	/**
	@brief  描画処理
	*/
    void Draw();

	/**
	@brief  スプライトの追加
	@param	追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/**
	@brief  スプライトの削除
	@param	削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/**
	@brief  パーティクルの追加
	@param	追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/**
	@brief  スプライトの削除
	@param	削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);

	/**
	@brief  テクスチャの取得
	@param	取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& _fileName);

	/**
	@brief  メッシュコンポーネントの追加
	@param	追加するMeshComponentクラスのポインタ
	*/
    void AddMeshComponent(MeshComponent* _meshComponent);

	/**
	@brief  メッシュコンポーネントの削除
	@param	削除するMeshComponentクラスのポインタ
	*/
    void RemoveMeshComponent(MeshComponent* _meshComponent);

	/**
	@brief  メッシュの取得
	@param	取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
    Mesh* GetMesh(const std::string& _fileName);

	/**
	@brief	ビュー行列を設定する
	@param	ビュー行列
	*/
    void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/**
	@brief	環境光を設定する
	@param	Vector3（環境光を表す）
	*/
    void SetAmbientLight(const Vector3& _ambient) { ambientLight = _ambient; }

	/**
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
    DirectionalLight& GetDirectionalLight() { return dirLight; }

	/**
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
    float GetScreenWidth() const { return screenWidth; }
	
	/**
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	float GetScreenHeight() const { return screenHeight; }

	Matrix4 GetViewMatrix() const { return view; };

	void SetParticleVertex();

	Matrix4 GetProjectionMatrix() { return projection; }

	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }

	SDL_Window* GetSDLWindow() { return window; }

	SDL_GLContext GetContext() { return context; }

private:
	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	//自分のインスタンス
	static Renderer* renderer;

	/**
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
    bool LoadShaders();
	/**
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
    void CreateSpriteVerts();
	void CreateParticleVerts();
	void CreateScreenVerts();

	void DrawParticle();

	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);

	/**
	@brief  光源情報をシェーダーの変数にセットする
	@param  セットするShaderクラスのポインタ
	*/
    void SetLightUniforms(Shader* _shader, const Matrix4& view);

	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);
	Vector3 CalcCameraPos();

	//Gaussianフィルタの重み係数を算出
	void SettingWeight();

    //ファイル名でメッシュを取得するための連想配列
    std::unordered_map<std::string, Mesh*> meshes;
    //メッシュコンポーネントのポインタの可変長コンテナ
    std::vector<MeshComponent*> meshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> particles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>textures;


	//　コンポーネントに追加
	//std::vector<Particle*> particles;        // パーティクル配列

    std::vector<MeshComponent*> basicMeshComponents;

	//クラスのポインタ

    Shader* spriteShader;
    VertexArray* spriteVerts;
	Shader* particleShader;
	VertexArray* particleVertex;   // パーティクル用頂点定義
	VertexArray* screenVertex;

	std::vector<ShaderToMesh*> shaderToMeshArray;

    //ビュー行列
    Matrix4 view;
	//射影行列
    Matrix4 projection;
	//ビルボード行列
	Matrix4 mBillboardMat;
    //スクリーンの横幅
    float screenWidth;
	//スクリーンの縦幅
    float screenHeight;
    //環境光
    Vector3 ambientLight;
	//平行光源
    DirectionalLight dirLight;
    //ウィンドウ
    SDL_Window* window;
    //コンテキスト
    SDL_GLContext context;

	SDL_Renderer* sdlRenderer;

	Matrix4 scaleMat;


	//テクスチャレンダリング用
	unsigned int fbo;
	unsigned int gaussian;
	unsigned int gaussianFinal;
	class Texture* fboTexture;
	class Texture* fboBrightTexture;
	class Texture* gaussianTexture;
	class Texture* gaussianFinalTexture;
	Matrix4 fboView;
	Shader* fullShader;
	Shader* gaussianShader;

	bool CreateFBO();

	const int num = 1;

	float weight[SAMPLE_NUM];
	int gaussianRange = 15;
	int prevRange;
	int gaussianCoefficient = 1;
	int prevGaussianCoefficient;

#ifdef _DEBUG
	friend class imguiManager;
	bool isDebugView;
	bool isDrawHDRFrame = true;
	bool isNormalFrame = true;
	virtual void ShowRenderer();
#endif // _DEBUG
};