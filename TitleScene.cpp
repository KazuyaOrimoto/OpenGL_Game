#include "TitleScene.h"
#include "Game.h"


TitleScene::TitleScene(Game* _game)
    :SceneBase(_game)
{
}


TitleScene::~TitleScene()
{
}

SceneBase * TitleScene::Update()
{
    return this;
}
