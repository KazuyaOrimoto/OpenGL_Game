//=============================================================================
//	@file	SceneBase.cpp
//	@brief	シーンクラスの基底クラス
//	@autor	居本 和哉
//	@date	2019/10/3
//=============================================================================


#include "SceneBase.h"
#include "PlayScene.h"
#include "Game.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

SceneBase* SceneBase::StartGame()
{
    return new PlayScene();
}
