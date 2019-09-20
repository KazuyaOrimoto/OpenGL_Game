#include "SceneBase.h"
#include "PlayScene.h"
#include "Game.h"

SceneBase::SceneBase(Game* _game)
    :game(_game)
{
}

SceneBase::~SceneBase()
{
}

SceneBase* SceneBase::StartGame(Game* _game)
{
    return new PlayScene(_game);
}
