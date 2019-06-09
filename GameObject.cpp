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
	, position(Vector2::Zero)
	, readOnlyPosition(position)
	, scale(1.0f)
	, rotation(0.0f)
	, game(argGame)
{
}

GameObject::~GameObject()
{
}

/**
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float argDaltaTime)
{
	if (state == Active)
	{
		
	}
}

/**
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float argDaltaTime)
{
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
}

/**
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * argComponent)
{
}
