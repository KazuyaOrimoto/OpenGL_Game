#pragma once

#include <functional>

enum SceneName
{
	NONE,
	Title,
	Play,
	GameOver,
	GameClear
};

class SceneBase;

class SceneManager
{
public:
    static void ChangeScene(SceneName _name);

	static void SceneUpdate();

private:
	static void StartPlayScene();
	static void StartTitleScene();
	static void StartGameOverScene();
	static void StartGameClearScene();

	static SceneName scene;
	static bool needChangeScene;
};

