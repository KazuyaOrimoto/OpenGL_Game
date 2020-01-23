#pragma once

#include <functional>

enum SceneName
{
	NONE,
	Title,
	Play,
	Result
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
	static void StartResultScene();

	static SceneName scene;
	static bool needChangeScene;
};

