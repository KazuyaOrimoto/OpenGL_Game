#include "GameClearLogo.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Renderer.h"

GameClearLogo::GameClearLogo()
{
	SpriteComponent* sprite = new SpriteComponent(this);
	Texture* tex = RENDERER->GetTexture("Assets/GameClear.png");
	sprite->SetTexture(tex);
}

GameClearLogo::~GameClearLogo()
{
}

void GameClearLogo::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed)
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == ButtonState::Pressed)
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
	if (_state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A))
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
	if (_state.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B))
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
}
