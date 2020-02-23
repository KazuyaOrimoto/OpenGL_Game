#include "TitlePlayer.h"
#include "TitleCamera.h"
#include "HDRMeshComponent.h"
#include "Renderer.h"
#include "EffectComponent.h"
#include "AutoRunComponent.h"
#include "EffekseerManager.h"

TitlePlayer::TitlePlayer()
{
	meshComp = new HDRMeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/PlanePlayer.gpmesh"));
	meshComp->SetHDRColor(Vector3(0.6f, 0.6f, 0.6f));
	SetScale(3.0f);
	tag = Tag::Player;
	autoRun = new AutoRunComponent(this);
	//autoRun->SetForwardSpeed(1000);
	camera = new TitleCamera(this);
	camera->SnapToIdeal();

	effect = new EffectComponent(this);
	effect->SetPosition(position);
	effect->LoadEffect("Effect/trail.efk", position);
	effect->Play();
}


TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::UpdateGameObject(float _deltaTime)
{
	effect->SetPosition(position + (GetForward() * -100) + (GetUp() * 15));


}
