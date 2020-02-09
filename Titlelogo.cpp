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
}

Titlelogo::~Titlelogo()
{
}

void Titlelogo::UpdateGameObject(float _deltaTime)
{

}

void Titlelogo::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Held)
	{
		SceneManager::ChangeScene(SceneName::Play);
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == ButtonState::Held)
	{
		SceneManager::ChangeScene(SceneName::Play);
	}
}
