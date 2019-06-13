#pragma once
#include <vector>
#include "Math.h"
#include "Property.h"

class Game;
class Vector2;
class Component;

class GameObject
{
public:
	/**
	@brief	�Q�[���I�u�W�F�N�g�̏��
	*/
	enum State
	{
		Active,
		Paused,
		Dead
	};

	/**
	@param	�Q�[���N���X�̃|�C���^
	*/
	GameObject(Game* argGame);
	virtual ~GameObject();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float argDaltaTime);

	/**
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float argDaltaTime);

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float argDaltaTime);

	/**
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* argComponent);

	/**
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* argComponent);

	void ComputeWorldTransform();


	cpp_module::ReadOnlyProperty<Vector2> readOnlyPosition;
    cpp_module::ReadOnlyProperty<Game*> readOnlyGame;
	cpp_module::ReadOnlyProperty<Matrix4> readOnlyWorldTransform;

private:
	//�Q�[���I�u�W�F�N�g�̏��
	State state;

	//Transform
	Matrix4 worldTransform;
	Vector2 position;
	float scale;
	float rotation;	
	bool recomputeWorldTransform;

	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;
	//�Q�[���N���X�̃C���X�^���X
	Game* game;

};

