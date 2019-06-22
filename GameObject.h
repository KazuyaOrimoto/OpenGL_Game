#pragma once
#include <vector>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;

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

	void ProcessInput(const InputState& keyState);
	virtual void GameObjectInput(const InputState& keyState);

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

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/**
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
    const Vector3& GetPosition() const { return position; }

	/**
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
    void SetPosition(const Vector3& argPos) { position = argPos; recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
    float GetScale() const { return scale; }

	/**
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��
	@param	scale
	*/
    void SetScale(float argScale) { scale = argScale;  recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
    const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
    void SetRotation(const Quaternion& argQotation) { rotation = argQotation;  recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	void SetState(State argState) { state = argState; }

	/**
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/**
	@brief�@Game�N���X�̃C���X�^���X���擾����
	@return	Game�N���X�̃|�C���^
	*/
    Game* GetGame() { return game; }

	/**
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, rotation); }

protected:
	//�Q�[���I�u�W�F�N�g�̏��
	State state;

	//Transform
	Vector3 position;
	Quaternion rotation;	
	float scale;
	Matrix4 worldTransform;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool recomputeWorldTransform;

	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;
	//�Q�[���N���X�̃C���X�^���X
	Game* game;

};

