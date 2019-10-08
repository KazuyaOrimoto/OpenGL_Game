#include "CameraObject.h"
#include "Game.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "InputComponent.h"
#include "InputSystem.h"

CameraObject::CameraObject()
    :GameObject()
{
	inputComponent = new InputComponent(this);
	inputComponent->SetMaxAngularSpeed(Math::Pi);
	inputComponent->SetMaxForwardSpeed(200.0f);
	inputComponent->SetForwardKey(SDL_SCANCODE_W);
	inputComponent->SetBackKey(SDL_SCANCODE_S);
	inputComponent->SetClockwiseKey(SDL_SCANCODE_D);
	inputComponent->SetCounterClockwiseKey(SDL_SCANCODE_A);
}

void CameraObject::UpdateGameObject(float _deltaTime)
{
    GameObject::UpdateGameObject(_deltaTime);

	// このオブジェクトのポジションからビュー行列を計算
    Vector3 cameraPos = GetPosition();
    Vector3 target = GetPosition() + GetForward() * 100.0f;
    Vector3 up = Vector3::UnitZ;

    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	RENDERER->SetViewMatrix(view);
}
