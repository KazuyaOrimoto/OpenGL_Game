#pragma once

class Game;

class SceneBase
{
public:
	SceneBase(Game* game);
	virtual ~SceneBase();

	/**
	@brief	Updateの純粋仮想関数
	@return 次に実行するシーンのインスタンス
	*/
	virtual SceneBase* Update() = 0;

    static SceneBase* StartGame(Game* game);

private:
    Game* game;
};

