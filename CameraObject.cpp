#include "CameraObject.h"
#include "Game.h"
#include "SDL_scancode.h"
#include "Renderer.h"

CameraObject::CameraObject(Game * game)
    :GameObject(game)
{
}

void CameraObject::UpdateGameObject(float deltaTime)
{
    GameObject::UpdateGameObject(deltaTime);

    // Compute new camera from this actor
    Vector3 cameraPos = GetPosition();
    Vector3 target = GetPosition() + GetForward() * 100.0f;
    Vector3 up = Vector3::UnitZ;

    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(view);
}

