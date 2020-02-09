#include "GameClearLogo.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"


GameClearLogo::GameClearLogo()
{
	SpriteComponent* sprite = new SpriteComponent(this);
	Texture* tex = new Texture();
	tex->Load("Assets/GameClear.png");
	sprite->SetTexture(tex);
}

GameClearLogo::~GameClearLogo()
{
}

void GameClearLogo::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Held)
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == ButtonState::Held)
	{
		SceneManager::ChangeScene(SceneName::Title);
	}
}
