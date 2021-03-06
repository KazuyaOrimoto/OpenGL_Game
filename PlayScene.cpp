﻿#include "PlayScene.h"
#include "GameObjectCreater.h"
#include "Game.h"
#include "Renderer.h"
#include "Math.h"

PlayScene::PlayScene()
    :SceneBase()
{
    // Setup lights
    RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
    DirectionalLight& dir = RENDERER->GetDirectionalLight();
    dir.direction = Vector3(-1.0f, 0.7f, 0.7f);
    dir.diffuseColor = Vector3(0.9f, 0.98f, 1.0f);
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

    GameObjectCreater::PlayerAndWallCreate();

}

PlayScene::~PlayScene()
{
}

SceneBase * PlayScene::Update()
{
	return this;
}
