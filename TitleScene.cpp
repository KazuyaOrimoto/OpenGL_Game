#include "TitleScene.h"
#include "Game.h"


TitleScene::TitleScene(Game* game)
    :SceneBase(game)
{
}


TitleScene::~TitleScene()
{
}

SceneBase * TitleScene::Update()
{
    return this;
}
