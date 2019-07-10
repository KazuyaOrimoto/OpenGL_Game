#pragma once

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	/**
	@brief	Updateの純粋仮想関数
	@param	最後のフレームを完了するのに要した時間
	@return 次に実行するシーンのインスタンス
	*/
	virtual SceneBase* Update(float argDeltaTime) = 0;
	/**
	@brief	Drawの純粋仮想関数
	*/
	virtual void Draw() = 0;
};

