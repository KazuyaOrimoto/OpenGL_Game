#pragma once

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	/**
	@brief	Update�̏������z�֐�
	@param	�Ō�̃t���[������������̂ɗv��������
	@return ���Ɏ��s����V�[���̃C���X�^���X
	*/
	virtual SceneBase* Update(float argDeltaTime) = 0;
	/**
	@brief	Draw�̏������z�֐�
	*/
	virtual void Draw() = 0;
};

