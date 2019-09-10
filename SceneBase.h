#pragma once

class Game;

class SceneBase
{
public:
	SceneBase(Game* _game);
	virtual ~SceneBase();

	/**
	@brief	Updateの純粋仮想関数
	@return 次に実行するシーンのインスタンス
	*/
	virtual SceneBase* Update() = 0;

    static SceneBase* StartGame(Game* _game);

private:
    Game* game;
};

