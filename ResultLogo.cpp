#include "ResultLogo.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"


ResultLogo::ResultLogo()
{
	SpriteComponent* sprite = new SpriteComponent(this);
	Texture* tex = new Texture();
	tex->Load("Assets/Result.png");
	sprite->SetTexture(tex);
}


ResultLogo::~ResultLogo()
{
}

void ResultLogo::GameObjectInput(const InputState & _state)
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
