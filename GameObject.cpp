#include "Game.h"
#include "Math.h"
#include "Property.h"
#include "GameObject.h"
#include "Component.h"

/**
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject(Game * argGame)
	: state(Active)
	, worldTransform()
	, readOnlyWorldTransform(worldTransform)
	, position(Vector3::Zero)
	, readOnlyPosition(position)
	, scale(1.0f)
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, game(argGame)
    , readOnlyGame(game)
{
	game->AddGameObject(this);
}

GameObject::~GameObject()
{
	game->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/**
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float argDaltaTime)
{
	if (state == Active)
	{
		ComputeWorldTransform();

		UpdateComponents(argDaltaTime);
		UpdateGameObject(argDaltaTime);

		ComputeWorldTransform();

	}
}

/**
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float argDaltaTime)
{
	for (auto itr : components)
	{
		itr->Update(argDaltaTime);
	}
}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float argDaltaTime)
{
}

/**
@brief	�R���|�[�l���g��ǉ�����
@param	�ǉ�����R���|�[�l���g�̃|�C���^
*/
void GameObject::AddComponent(Component * argComponent)
{
	int order = argComponent->readOnlyUpdateOrder;
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->readOnlyUpdateOrder)
		{
			break;
		}
	}
	components.insert(itr,argComponent);
}

/**
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * argComponent)
{
	auto itr = std::find(components.begin(),components.end(),argComponent);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}

/**
@brief	Transform�̃��[���h�ϊ�
*/
void GameObject::ComputeWorldTransform()
{
	if (recomputeWorldTransform)
	{
		recomputeWorldTransform = false;
		worldTransform = Matrix4::CreateScale(scale);
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		worldTransform *= Matrix4::CreateTranslation(position);

		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}
