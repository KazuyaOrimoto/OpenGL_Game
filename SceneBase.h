#pragma once

class Game;

class SceneBase
{
public:
	SceneBase(Game* game);
	virtual ~SceneBase();

	/**
	@brief	Update�̏������z�֐�
	@param	�Ō�̃t���[������������̂ɗv��������
	@return ���Ɏ��s����V�[���̃C���X�^���X
	*/
	virtual SceneBase* Update() = 0;

    static SceneBase* StartGame(Game* game);

private:
    Game* game;
};

