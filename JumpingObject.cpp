#include "JumpingObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"
#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "RotateComponent.h"
#include "Mesh.h"
#include "GameObjectManager.h"
#include "JumpingArea.h"
#include <stdlib.h>
#include "SDL.h"

JumpingObject::JumpingObject(Game* _game)
	: ObstacleBox(_game)
	, player(nullptr)
{
	//オブジェクトに使うメッシュデータを設定
	meshComp = new MeshComponent(this);

	srand((unsigned)(SDL_GetTicks() + rand()));
	int randNum = rand() % 3;
	Mesh* mesh = nullptr;
	switch (randNum)
	{
	case 0:
		mesh = RENDERER->GetMesh("Assets/Cube1.gpmesh");
		break;

	case 1:
		mesh = RENDERER->GetMesh("Assets/Cube2.gpmesh");
		break;

	case 2:
		mesh = RENDERER->GetMesh("Assets/Cube3.gpmesh");
		break;

	default:
		break;
	}
	
	meshComp->SetMesh(mesh);

	//当たり判定用のコライダーを設定
	boxCollider = new BoxCollider(this);
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);

	//スケールの設定
	SetScale(200.0f);

	//障害物管理クラスに自分を登録
	OBSTACLE_MANAGER->AddObstacle(this);

	//タグを設定
	tag = Tag::JumpingObstacle;

	//ステートを設定
	state = Paused;

	//プレイヤーのポインタを保存
	player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);

	jumpingArea = new JumpingArea(game);
	jumpingArea->SetBoxCollider(box);
}

JumpingObject::~JumpingObject()
{
	OBSTACLE_MANAGER->RemoveObstacle(this);
}

void JumpingObject::UpdateGameObject(float _deltaTime)
{
	if (player->GetPosition().x - 500.0f > position.x)
	{
		ResetObstacle();
	}
}

void JumpingObject::OnCollision(GameObject & _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{
		//障害物と当たった時の処理
		PlayerObject* obstacle = dynamic_cast<PlayerObject*>(&_hitObject);
		HitPlayer(*obstacle);
	}
}


inline void JumpingObject::SetPosition(const Vector3 & _pos)
{
	GameObject::SetPosition(_pos);
	Vector3 jumpingAreaPos = _pos + Vector3(-200.0,0.0f,0.0f);
	jumpingArea->SetPosition(jumpingAreaPos);
}

