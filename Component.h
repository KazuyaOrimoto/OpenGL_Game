#pragma once

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

	/**
	@return �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	int GetUpdateOrder() const { return updateOrder; }

protected:
	GameObject* owner;			//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	int updateOrder;			//�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j

};

