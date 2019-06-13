#pragma once

#include "Property.h"
#include <cstdint>

class GameObject;

class Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	Component(GameObject* argOwner,int argUpdateOrder = 100);
	virtual ~Component();

	/**
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float argDeltaTime);

	virtual void ProcessInput(const uint8_t* keyState) {}

	virtual void OnUpdateWorldTransform() {}

	cpp_module::ReadOnlyProperty<int> readOnlyUpdateOrder;
protected:
	GameObject* owner;			//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	int updateOrder;			//�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j

};
