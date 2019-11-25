#include "ParticleManager.h"
#include "ParticleObject.h"
#include "Shader.h"
#include <algorithm>

ParticleManager::ParticleManager()
{
	mShader = new Shader;
	if (!mShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}
}

ParticleManager::~ParticleManager()
{
	//�S�p�[�e�B�N���̍폜
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
	// �u�����h���[�h������Ԏ擾
	Particle::PARTICLE_BLEND_ENUM blendType,prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = mViewMat * mProjectionMat;

	// �V�F�[�_�[ON
	mShader->SetActive();
	mShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// �S�Ẵp�[�e�B�N���̃r���{�[�h�s����Z�b�g
	(*itr)->SetBillboardMat(GetBillboardMatrix());

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// ���ׂẴp�[�e�B�N����`��
	ChangeBlendMode(blendType);
	ChangeTexture(nowTexture);

	for (auto particle : mParticles)
	{
		//�u�����h���[�h�ύX���K�v�Ȃ�ύX����
		blendType = particle->GetBlendType();
		if (blendType != prevType)
		{
			ChangeBlendMode(blendType);
		}
		// �e�N�X�`���ύX���K�v�Ȃ�ύX����
		nowTexture = particle->GetTextureID();
		if (nowTexture != prevTexture)
		{
			ChangeTexture(nowTexture);
		}

		// �p�[�e�B�N���`��
		particle->Draw(mShader);

		// �O��`���ԂƂ��ĕۑ�
		prevType = blendType;
		prevTexture = nowTexture;
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

}

void ParticleManager::SetParticle(Particle * particle)
{
	//�y���f�B���O�z��ɒǉ�
	mPendingParticles.emplace_back(particle);
}

void ParticleManager::Update(float deltaTime)
{
	//���ׂẴp�[�e�B�N���̍X�V
	for (auto particle : mParticles)
	{
		particle->Update(deltaTime);
	}
	
	// �y���f�B���O���̃p�[�e�B�N�����A�N�e�B�u�p�[�e�B�N���ɒǉ�
	for (auto pending : mPendingParticles)
	{
		mParticles.emplace_back(pending);
	}
	mPendingParticles.clear();

	// �A�N�e�B�u�p�[�e�B�N�������݂��Ȃ�
	if (mParticles.size() == 0)
	{
		return;
	}

	// �r���[�s��E�v���W�F�N�V�����s��E�r���{�[�h�s��
	mViewMat       = RENDERER->GetViewMatrix();
	mProjectionMat = RENDERER->GetProjectionMatrix();
	mBillboardMat  = GetBillboardMatrix();

	// ����ł���p�[�e�B�N�����폜
	auto itr = mParticles.begin();
	while (itr != mParticles.end())
	{
		//�p�[�e�B�N��������ł���Ȃ�
		Particle *p = (*itr);
		if ( !(p->IsAlive()) )
		{
			itr = mParticles.erase(itr); // erase(itr)�͗v�f���폜�����̎��̗v�f��Ԃ�
		}
		else
		{
			itr++;
		}
	}

	// �A�N�e�B�u�p�[�e�B�N�����݂��Ȃ�
	if (mParticles.size() == 0)
	{
		return;
	}

	//�r���{�[�h�s����p�[�e�B�N���ɓn��
	itr = mParticles.begin();
	(*itr)->mStaticBillboardMat = mBillboardMat; 

	// ���݂̃J�����ʒu���p�[�e�B�N���ɋ�����
	CalcCameraPos();
	(*itr)->mStaticCameraWorldPos = CalcCameraPos();

	// �p�[�e�B�N�����J���������ō~���\�[�g
	std::sort(mParticles.begin(), mParticles.end(), std::greater<Particle*>());

}

// �u�����h���[�h�ύX
void ParticleManager::ChangeBlendMode(Particle::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case Particle::PARTICLE_BLEND_ENUM_ADD :
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case Particle::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case Particle ::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
		break;
	default:
		break;
	}
}

// �e�N�X�`���ύX
void ParticleManager::ChangeTexture(int changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

// �J�����ʒu�v�Z
Vector3 ParticleManager::CalcCameraPos()
{
	// �r���[�s���胏�[���h�ł̃J�����ʒu�Z�o
	Matrix4 view = RENDERER->GetViewMatrix();
	Matrix4 transMat = view;

	// �r���[�s��̈ړ������������
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//�ړ���������菜�������Ɠ]�u���āA��]�����̋t�ϊ������
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}
