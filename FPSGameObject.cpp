#include "FPSGameObject.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"
#include "FPSCamera.h"
#include "MeshComponent.h"
#include "FPSCameraInput.h"

FPSGameObject::FPSGameObject(Game* game)
	:GameObject(game)
{
	mMoveComp = new MoveComponent(this);
	mCameraComp = new FPSCamera(this);
	input = new FPSCameraInput(this);

	input->SetForwardKey(SDL_SCANCODE_W);
	input->SetBackKey(SDL_SCANCODE_S);
	input->SetLeftKey(SDL_SCANCODE_A);
	input->SetRightKey(SDL_SCANCODE_D);
	input->SetMaxForwardSpeed(200.0f);
	input->SetStrafeSpeed(200.0f);
	input->SetMaxAngularSpeed(Math::Pi * 8);

	mFPSModel = new GameObject(game);
	mFPSModel->SetScale(0.75f);
	mMeshComp = new MeshComponent(mFPSModel);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));
}

void FPSGameObject::UpdateGameObject(float deltaTime)
{
	GameObject::UpdateGameObject(deltaTime);

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
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
	mFPSModel->SetRotation(q);
}


void FPSGameObject::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
