﻿//=============================================================================
//	@file	SceneBase.h
//	@brief	シーンクラスの基底クラス
//	@autor	居本 和哉
//	@date	2019/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class Game;

//-----------------------------------------------------------------------------
//	@brief SceneBaseクラス
//-----------------------------------------------------------------------------
class SceneBase
{
public:
//===================== パブリック関数 ======================//

	SceneBase();
	virtual ~SceneBase();

	/**
	@brief	Updateの純粋仮想関数
	@return 次に実行するシーンのインスタンス
	*/
	virtual SceneBase* Update() = 0;

    /**
    @brief	ゲームの最初に実行するクラスの決定と作成
    @return 最初に実行するシーンクラス
    */
    static SceneBase* StartGame();

};

