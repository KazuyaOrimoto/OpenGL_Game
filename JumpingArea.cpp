#include "JumpingArea.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Renderer.h"

JumpingArea::JumpingArea(Game* _game)
	:GameObject(_game)
	,boxCollider(nullptr)
{
	boxCollider = new BoxCollider(this);
	SetScale(200.0f);
	tag = Tag::JumpingObstacle;

	//オブジェクトに使うメッシュデータを設定
	//meshComp = new MeshComponent(this);
	//Mesh* mesh = RENDERER->GetMesh("Assets/Cube.gpmesh");
	//meshComp->SetMesh(mesh);

}

JumpingArea::~JumpingArea()
{
}

void JumpingArea::SetBoxCollider(AABB _box)
{
	_box.min.x -= 0.5f;
	boxCollider->SetObjectBox(_box);
}

