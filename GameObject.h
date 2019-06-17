#pragma once
#include <vector>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
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

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	// Getter / Setter

    const Vector3& GetPosition() const { return position; }
    void SetPosition(const Vector3& argPos) { position = argPos; recomputeWorldTransform = true; }
    float GetScale() const { return scale; }
    void SetScale(float argScale) { scale = argScale;  recomputeWorldTransform = true; }
    const Quaternion& GetRotation() const { return rotation; }
    void SetRotation(const Quaternion& argQotation) { rotation = argQotation;  recomputeWorldTransform = true; }
	State GetState() const { return state; }
	void SetState(State argState) { state = argState; }
	const Matrix4& GetWorldTransform() const { return worldTransform; }
    Game* GetGame() { return game; }
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

