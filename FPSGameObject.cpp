#include "FPSGameObject.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"
#include "FPSCamera.h"
#include "MeshComponent.h"

FPSGameObject::FPSGameObject()
	:GameObject()
{
	//mCameraComp = new FPSCamera(this);
	moveComponent = new MoveComponent(this);
	fpsCamera = new FPSCamera(this);

	moveComponent->SetForwardKey(SDL_SCANCODE_W);
	moveComponent->SetBackKey(SDL_SCANCODE_S);
	moveComponent->SetLeftKey(SDL_SCANCODE_A);
	moveComponent->SetRightKey(SDL_SCANCODE_D);

	mFPSModel = new GameObject();
	mFPSModel->SetScale(0.75f);
	mMeshComp = new MeshComponent(mFPSModel);
	mMeshComp->SetMesh(RENDERER->GetMesh("Assets/Rifle.gpmesh"));
}

void FPSGameObject::UpdateGameObject(float _deltaTime)
{
	GameObject::UpdateGameObject(_deltaTime);

	// Update position of FPS model relative to actor position
	const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
	Vector3 modelPos = GetPosition();
	modelPos += GetForward() * modelOffset.x;
	modelPos += GetRight() * modelOffset.y;
	modelPos.z += modelOffset.z;
	mFPSModel->SetPosition(modelPos);
	// Initialize rotation to actor rotation
	Quaternion q = GetRotation();
	// Rotate by pitch from camera
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), fpsCamera->GetPitch()));
	mFPSModel->SetRotation(q);
}


void FPSGameObject::SetVisible(bool _visible)
{
	mMeshComp->SetVisible(_visible);
}
