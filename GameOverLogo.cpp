#include "GameOverLogo.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Renderer.h"

GameOverLogo::GameOverLogo()
{
	SpriteComponent* sprite = new SpriteComponent(this);
	Texture* tex = RENDERER->GetTexture("Assets/GameOver.png");
	sprite->SetTexture(tex);
}

GameOverLogo::~GameOverLogo()
{

}

void GameOverLogo::GameObjectInput(const InputState & _state)
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
