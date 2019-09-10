#pragma once

class Game;

class SceneBase
{
public:
	SceneBase(Game* _game);
	virtual ~SceneBase();

	/**
	@brief	Update�̏������z�֐�
	@return ���Ɏ��s����V�[���̃C���X�^���X
	*/
	virtual SceneBase* Update() = 0;

    static SceneBase* StartGame(Game* _game);

private:
    Game* game;
};

