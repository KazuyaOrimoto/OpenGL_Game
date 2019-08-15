#pragma once

class Game;

class SceneBase
{
public:
	SceneBase(Game* game);
	virtual ~SceneBase();

	/**
	@brief	Updateの純粋仮想関数
	@param	最後のフレームを完了するのに要した時間
	@return 次に実行するシーンのインスタンス
	*/
	virtual SceneBase* Update() = 0;

    static SceneBase* StartGame(Game* game);

private:
    Game* game;
};

