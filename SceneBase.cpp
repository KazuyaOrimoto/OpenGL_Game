#include "SceneBase.h"
#include "PlayScene.h"
#include "Game.h"

SceneBase::SceneBase(Game* argGame)
    :game(argGame)
{
}


SceneBase::~SceneBase()
{
}

SceneBase* SceneBase::StartGame(Game* game)
{
    return new PlayScene(game);
}
