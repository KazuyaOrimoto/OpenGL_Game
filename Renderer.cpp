﻿//=============================================================================
//	@file	Renderer.cpp
//	@brief	描画全般の管理をする
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <document.h>
#include "EffekseerManager.h"

#ifdef _DEBUG
#include "imguiManager.h"
#endif // _DEBUG

Renderer* Renderer::renderer = nullptr;

void Renderer::SetScreenMat(const Vector3& scale, const Quaternion& rotation, const Vector3& position)
{
	scaleMat = Matrix4::CreateScale(
		static_cast<float>(screenWidth),
		static_cast<float>(-screenHeight),
		1.0f);

	Matrix4 worldTransform = Matrix4::Identity;
	worldTransform *= Matrix4::CreateScale(scale);
	worldTransform *= Matrix4::CreateFromQuaternion(rotation);
	worldTransform *= Matrix4::CreateTranslation(position);

	scaleMat *= worldTransform;
}

Renderer::Renderer()
	: spriteShader(nullptr)
	, spriteVerts(nullptr)
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
@brief  インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}

/**
@brief  インスタンスを削除する
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
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// ウィンドウの作成
	window = SDL_CreateWindow("Ace", 0, 0,
		static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);

	// ウィンドウの作成に失敗した場合
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// SDLのRendererの作成
	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// SDLのRendererの作成に失敗した場合
	if (!sdlRenderer)
	{
		printf("Failed to create SDL Renderer : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	context = SDL_GL_CreateContext(window);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	//
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	scaleMat = Matrix4::CreateScale(
		static_cast<float>(screenWidth),
		static_cast<float>(-screenHeight),
		1.0f); 

	normalMat = Matrix4::CreateScale(
		static_cast<float>(screenWidth),
		static_cast<float>(-screenHeight),
		1.0f);

	SettingWeight();
	prevRange = gaussianRange;
	prevGaussianCoefficient = gaussianCoefficient;
	// カリング
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	tex = new Texture();
	tex->Load("Assets/Dummy.png");

	return true;
}

bool Renderer::LoadData()
{
	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	// Create render target for FBO
	if (!CreateFBO())
	{
		SDL_Log("Failed to create render target for FBO.");
		return false;
	}

	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateScreenVerts();

	return true;
}

/**
@brief  終了処理
*/
void Renderer::Shutdown()
{
	if (fboTexture != nullptr)
	{
		glDeleteFramebuffers(1, &fbo);
		fboTexture->Unload();
		delete fboTexture;
	}
	if (gaussianTexture != nullptr)
	{
		//glDeleteFramebuffers(1, &gaussian);
		gaussianTexture->Unload();
		delete gaussianTexture;
	}
	if (fboBrightTexture != nullptr)
	{
		//glDeleteFramebuffers(1, &gaussian);
		fboBrightTexture->Unload();
		delete fboBrightTexture;
	}
	if (gaussianFinalTexture != nullptr)
	{
		//glDeleteFramebuffers(1, &gaussian);
		gaussianFinalTexture->Unload();
		delete gaussianFinalTexture;
	}
	for (auto itr : shaderToMeshArray)
	{
		delete itr->shader;
	}

	delete spriteVerts;

	spriteShader->Unload();
	delete spriteShader;
	gaussianShader->Unload();
	delete gaussianShader;
	tex->Unload();
	delete tex;
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/**
@brief  ロードしたデータの解放
*/
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : textures)
	{
		i.second->Unload();
		delete i.second;
	}
	textures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : meshes)
	{
		i.second->Unload();
		delete i.second;
	}
	meshes.clear();
}

/**
@brief  描画処理
*/
void Renderer::Draw()
{
	//ガウシアン用の値が変わっていたら
	if (gaussianRange != prevRange || gaussianCoefficient != prevGaussianCoefficient)
	{
		SettingWeight();
		prevRange = gaussianRange;
		prevGaussianCoefficient = gaussianCoefficient;
	}

	EFFECT_MANAGER->Update();

	//FBOに標準の画面を描画
	Draw3DScene(fbo, view, projection, 1.0f);

	////ガウスぼかし用の画面
	glBindFramebuffer(GL_FRAMEBUFFER, gaussian);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(screenWidth * (1.0f / 2)),
		static_cast<int>(screenHeight * (1.0f / 2))
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Disable depth testing for the global lighting pass
	glDisable(GL_DEPTH_TEST);
	gaussianShader->SetActive();
	screenVertex->SetActive();
	gaussianShader->SetMatrixUniform("uWorldTransform", normalMat);
	gaussianShader->SetFloatArrayUniform("weight", SAMPLE_NUM, weight);
	gaussianShader->SetIntUniform("uRange",15);
	gaussianShader->SetBoolUniform("horizontal", true);
	// Activate sprite verts quad
	fboBrightTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glBindFramebuffer(GL_FRAMEBUFFER, gaussianFinal);

	glViewport(0, 0,
		static_cast<int>(screenWidth * (1.0f / 2)),
		static_cast<int>(screenHeight * (1.0f / 2))
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Disable depth testing for the global lighting pass
	glDisable(GL_DEPTH_TEST);
	gaussianShader->SetActive();
	screenVertex->SetActive();
	gaussianShader->SetMatrixUniform("uWorldTransform", normalMat);
	gaussianShader->SetFloatArrayUniform("weight", SAMPLE_NUM, weight);
	gaussianShader->SetIntUniform("uRange", 15);
	gaussianShader->SetBoolUniform("horizontal",false);
	// Activate sprite verts quad
	gaussianTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	//標準フレームバッファ
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
#ifdef _DEBUG
	if (isNormalFrame)
#endif // _DEBUG
	{
		glViewport(0, 0,
			static_cast<int>(screenWidth * 1.0f),
			static_cast<int>(screenHeight * 1.0f)
		);
		spriteShader->SetActive();
		screenVertex->SetActive();
		spriteShader->SetMatrixUniform("uWorldTransform", scaleMat);
		// Activate sprite verts quad
		fboTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
#ifdef _DEBUG
	if (isDrawHDRFrame)
#endif // _DEBUG
	{
		glViewport(0, 0,
			static_cast<int>(screenWidth * 1.0),
			static_cast<int>(screenHeight * 1.0)
		);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		spriteShader->SetActive();
		screenVertex->SetActive();
		spriteShader->SetMatrixUniform("uWorldTransform", scaleMat);
		gaussianFinalTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glDisable(GL_BLEND);
	}


	// デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);


	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	spriteShader->SetActive();
	spriteVerts->SetActive();
	// すべてのスプライトの描画
	for (auto sprite : sprites)
	{
		sprite->Draw(spriteShader);
	}

	// Draw any UI screens
	//for (auto ui : UI_MANAGER->GetUIStack())
	//{
	//	ui->Draw(spriteShader);
	//}
#ifdef USE_IMGUI
	IMGUI_MANAGER->Draw();
#endif // USE_IMGUI

	SDL_GL_SwapWindow(window);

}


/**
@brief  スプライトの削除
@param	削除するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
	int myDrawOrder = _spriteComponent->GetDrawOrder();
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

	// 検索した場所のiterの場所に挿入
	sprites.insert(iter, _spriteComponent);
}

/**
@brief  スプライトの削除
@param	削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(sprites.begin(), sprites.end(), _spriteComponent);
	sprites.erase(iter);
}


/**
@brief  メッシュコンポーネントの追加
@param	追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	//同じ名前のシェーダーの配列を探す
	for (auto itr : shaderToMeshArray)
	{
		if (itr->shaderName == _meshComponent->GetMesh()->GetShaderName())
		{
			//同じ名前のシェーダーの配列にメッシュを登録する
			itr->meshComponentArray.emplace_back(_meshComponent);
			return;
		}
	}
	//同じ名前のシェーダーが見つからなかったとき
	ShaderToMesh* newShaderToMesh = new ShaderToMesh;
	newShaderToMesh->shaderName = _meshComponent->GetMesh()->GetShaderName();
	newShaderToMesh->shader = new Shader();
	if (!newShaderToMesh->shader->Load("Shaders/" + newShaderToMesh->shaderName + ".vert", "Shaders/" + newShaderToMesh->shaderName + ".frag"))
	{
		return;
	}
	newShaderToMesh->shader->SetActive();
	newShaderToMesh->shader->SetMatrixUniform("uViewProj", view * projection);
	newShaderToMesh->meshComponentArray.emplace_back(_meshComponent);
	shaderToMeshArray.emplace_back(newShaderToMesh);
	auto viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	newShaderToMesh->shader->SetMatrixUniform("uViewProj", viewProj);

}

/**
@brief  メッシュコンポーネントの削除
@param	削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	//同じ名前のシェーダーの配列を探す
	for (auto itr : shaderToMeshArray)
	{
		if (itr->shaderName == _meshComponent->GetMesh()->GetShaderName())
		{
			//同じ名前のシェーダーの配列からメッシュを削除する
			auto deleteMesh = std::find(itr->meshComponentArray.begin(), itr->meshComponentArray.end(), _meshComponent);
			itr->meshComponentArray.erase(deleteMesh);
			return;
		}
	}

}

/**
@brief  テクスチャの取得
@param	取得したいテクスチャのファイル名
@return Textureクラスのポインタ
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = textures.find(_fileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			textures.emplace(_fileName, texture);
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
@brief  メッシュの取得
@param	取得したいメッシュのファイル名
@return Meshクラスのポインタ
*/
Mesh* Renderer::GetMesh(const std::string &_fileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = meshes.find(_fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			meshes.emplace(_fileName, m);
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
@brief  シェーダーの読み込み
@return true : 成功 , false : 失敗
*/
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	spriteShader->SetActive();
	// ビュー行列の設定
	auto viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);

	gaussianShader = new Shader();
	if (!gaussianShader->Load("Shaders/Sprite.vert", "Shaders/GaussianShader.frag"))
	{
		return false;
	}
	gaussianShader->SetActive();
	// ビュー行列の設定
	gaussianShader->SetMatrixUniform("uViewProj", viewProj);

	//meshShader->SetActive();
	// ビュー行列の設定
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(50.0f),
		screenWidth, screenHeight, 1.0f, 13000.0f);
	return true;
}

/**
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
	0, 2, 1,
	2, 0, 3
	};

	spriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}


void Renderer::CreateScreenVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
	};
	screenVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4 & view, const Matrix4 & proj, float viewPortScale, bool lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(screenWidth * viewPortScale),
		static_cast<int>(screenHeight * viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// メッシュコンポーネントの描画
	//アルファブレンディングを無効にする
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	for (auto itr : shaderToMeshArray)
	{
		itr->shader->SetActive();
		itr->shader->SetMatrixUniform("uViewProj", view * projection);
		SetLightUniforms(itr->shader, view);
		for (auto meshComp : itr->meshComponentArray)
		{
			meshComp->Draw(itr->shader);
		}
	}

	//ダミー用スプライト
	spriteShader->SetActive();
	spriteVerts->SetActive();
	tex->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	EFFECT_MANAGER->BeginRendering();

	EFFECT_MANAGER->Draw();


	EFFECT_MANAGER->EndRendering();

}

/**
@brief  光源情報をシェーダーの変数にセットする
@param  セットするShaderクラスのポインタ
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", ambientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		dirLight.direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		dirLight.diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		dirLight.specColor);
}

void Renderer::ChangeTexture(int changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = view;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}

void Renderer::SettingWeight()
{
	double t = 0.0;
	double d = static_cast<double>(gaussianRange * gaussianRange) / gaussianCoefficient;
	for (auto i = 0; i < SAMPLE_NUM; i++)
	{
		double r = 1.0 + 2.0 * i;
		double w = std::exp(-0.5 * (r * r) / d);
		weight[i] = static_cast<float>(w);
		if (i > 0)
		{
			w *= 2.0;
		}
		t += w;
	}
	for (auto i = 0; i < SAMPLE_NUM; i++)
	{
		weight[i] /= static_cast<float>(t);
	}
}

bool Renderer::CreateFBO()
{
	//通常画面の描画用フレームバッファ
	int width = static_cast<int>(screenWidth);
	int height = static_cast<int>(screenHeight);

	// Generate a frame buffer for the mirror texture
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create the texture we'll use for rendering
	fboTexture = new Texture();
	fboTexture->CreateForRendering(width, height, GL_RGB);

	// Attach mirror texture as the output target for the frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fboTexture->GetTextureID(), 0);

	// Create the texture we'll use for rendering
	fboBrightTexture = new Texture();
	fboBrightTexture->CreateForRendering(width, height, GL_RGB);

	// Attach mirror texture as the output target for the frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, fboBrightTexture->GetTextureID(), 0);

	// Set the list of buffers to draw to for this frame buffer
	GLenum drawBuffers2[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glNamedFramebufferDrawBuffers(fbo, 2, drawBuffers2);

	// Add a depth buffer to this target
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	// Make sure everything worked
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// If it didn't work, delete the framebuffer,
		// unload/delete the texture and return false
		glDeleteFramebuffers(1, &fbo);
		fboTexture->Unload();
		delete fboTexture;
		fboTexture = nullptr;
		fboBrightTexture->Unload();
		delete fboBrightTexture;
		fboBrightTexture = nullptr;
		return false;
	}
	
	//ガウスぼかし用のフレームバッファ
	glGenFramebuffers(1, &gaussian);
	glBindFramebuffer(GL_FRAMEBUFFER, gaussian);

	gaussianTexture = new Texture();
	gaussianTexture->CreateForRendering(width / 2, height / 2, GL_RGB);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gaussianTexture->GetTextureID(), 0);

	// Set the list of buffers to draw to for this frame buffer
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glNamedFramebufferDrawBuffers(gaussian, 1, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// If it didn't work, delete the framebuffer,
		// unload/delete the texture and return false
		glDeleteFramebuffers(1, &gaussian);
		gaussianTexture->Unload();
		delete gaussianTexture;
		gaussianTexture = nullptr;
		return false;
	}

	//ガウスぼかし用のフレームバッファ
	glGenFramebuffers(1, &gaussianFinal);
	glBindFramebuffer(GL_FRAMEBUFFER, gaussianFinal);

	gaussianFinalTexture = new Texture();
	gaussianFinalTexture->CreateForRendering(width / 2, height / 2, GL_RGB);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gaussianFinalTexture->GetTextureID(), 0);

	// Set the list of buffers to draw to for this frame buffer
	glNamedFramebufferDrawBuffers(gaussianFinal, 1, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// If it didn't work, delete the framebuffer,
		// unload/delete the texture and return false
		glDeleteFramebuffers(1, &gaussianFinal);
		gaussianFinalTexture->Unload();
		delete gaussianFinalTexture;
		gaussianFinalTexture = nullptr;
		return false;
	}

	return true;
}

#ifdef _DEBUG
void Renderer::ShowRenderer()
{

}

#endif // _DEBUG

