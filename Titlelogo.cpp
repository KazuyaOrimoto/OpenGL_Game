//=============================================================================
//	@file	Titlelogo.cpp
//	@brief	タイトルのシーンのロゴのオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "Titlelogo.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Renderer.h"

Titlelogo::Titlelogo()
{
	SpriteComponent* sprite = new SpriteComponent(this);
	Texture* tex = RENDERER->GetTexture("Assets/Title.png");
	sprite->SetTexture(tex);
	SetPosition(Vector3(0.0,200.0f,0.0f));
	change = false;
}

Titlelogo::~Titlelogo()
{
}

void Titlelogo::UpdateGameObject(float _deltaTime)
{

}

void Titlelogo::GameObjectInput(const InputState & _state)
{
	if (!change)
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::None && _state.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == ButtonState::None
			 && !_state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) && !_state.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B))
		{
			change = true;
		}
	}
	else
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed)
		{
			SceneManager::ChangeScene(SceneName::Play);
		}
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == ButtonState::Pressed)
		{
			SceneManager::ChangeScene(SceneName::Play);
		}
		if (_state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A))
		{
			SceneManager::ChangeScene(SceneName::Play);
		}
		if (_state.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B))
		{
			SceneManager::ChangeScene(SceneName::Play);
		}
	}
}
