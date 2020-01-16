#pragma once

enum SceneName
{
	Title,
	Play,
	Result
};

class SceneBase;

class SceneManager
{
public:
    static void ChangeScene(SceneName _name);

private:
	static void StartPlayScene();
	static void StartTitleScene();

};

