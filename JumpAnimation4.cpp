#include "JumpAnimation4.h"
#include "GameObject.h"
#include "MainCamera.h"

JumpAnimation4::JumpAnimation4(GameObject* _gameObject, MainCamera* _camera)
	:AnimationClip(_gameObject, 10)
{
}


JumpAnimation4::~JumpAnimation4()
{
}

void JumpAnimation4::Update(float deltaTime)
{
}
