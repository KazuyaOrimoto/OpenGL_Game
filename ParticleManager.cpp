#include "ParticleManager.h"
#include "ParticleObject.h"
#include "Shader.h"
#include <algorithm>

ParticleManager::ParticleManager()
{
	mShader = new Shader;
	if (!mShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}
}

ParticleManager::~ParticleManager()
{
	//全パーティクルの削除
	while (!mParticles.empty())
	{
		delete mParticles.back();
		mParticles.pop_back();
	}
	delete mShader;
}

void ParticleManager::Draw()
{
	if (mParticles.size() == 0)
	{
		return;
	}
	// ブレンドモード初期状態取得
	Particle::PARTICLE_BLEND_ENUM blendType,prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = mViewMat * mProjectionMat;

	// シェーダーON
	mShader->SetActive();
	mShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// 全てのパーティクルのビルボード行列をセット
	(*itr)->SetBillboardMat(GetBillboardMatrix());

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	ChangeBlendMode(blendType);
	ChangeTexture(nowTexture);

	for (auto particle : mParticles)
	{
		//ブレンドモード変更が必要なら変更する
		blendType = particle->GetBlendType();
		if (blendType != prevType)
		{
			ChangeBlendMode(blendType);
		}
		// テクスチャ変更が必要なら変更する
		nowTexture = particle->GetTextureID();
		if (nowTexture != prevTexture)
		{
			ChangeTexture(nowTexture);
		}

		// パーティクル描画
		particle->Draw(mShader);

		// 前回描画状態として保存
		prevType = blendType;
		prevTexture = nowTexture;
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

}

void ParticleManager::SetParticle(Particle * particle)
{
	//ペンディング配列に追加
	mPendingParticles.emplace_back(particle);
}

void ParticleManager::Update(float deltaTime)
{
	//すべてのパーティクルの更新
	for (auto particle : mParticles)
	{
		particle->Update(deltaTime);
	}
	
	// ペンディング中のパーティクルをアクティブパーティクルに追加
	for (auto pending : mPendingParticles)
	{
		mParticles.emplace_back(pending);
	}
	mPendingParticles.clear();

	// アクティブパーティクルが存在しない
	if (mParticles.size() == 0)
	{
		return;
	}

	// ビュー行列・プロジェクション行列・ビルボード行列
	mViewMat       = RENDERER->GetViewMatrix();
	mProjectionMat = RENDERER->GetProjectionMatrix();
	mBillboardMat  = GetBillboardMatrix();

	// 死んでいるパーティクルを削除
	auto itr = mParticles.begin();
	while (itr != mParticles.end())
	{
		//パーティクルが死んでいるなら
		Particle *p = (*itr);
		if ( !(p->IsAlive()) )
		{
			itr = mParticles.erase(itr); // erase(itr)は要素を削除＆その次の要素を返す
		}
		else
		{
			itr++;
		}
	}

	// アクティブパーティクル存在しない
	if (mParticles.size() == 0)
	{
		return;
	}

	//ビルボード行列をパーティクルに渡す
	itr = mParticles.begin();
	(*itr)->mStaticBillboardMat = mBillboardMat; 

	// 現在のカメラ位置をパーティクルに教える
	CalcCameraPos();
	(*itr)->mStaticCameraWorldPos = CalcCameraPos();

	// パーティクルをカメラ距離で降順ソート
	std::sort(mParticles.begin(), mParticles.end(), std::greater<Particle*>());

}

// ブレンドモード変更
void ParticleManager::ChangeBlendMode(Particle::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case Particle::PARTICLE_BLEND_ENUM_ADD :
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case Particle::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case Particle ::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

// テクスチャ変更
void ParticleManager::ChangeTexture(int changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

// カメラ位置計算
Vector3 ParticleManager::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 view = RENDERER->GetViewMatrix();
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
