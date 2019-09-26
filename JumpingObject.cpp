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
	//�I�u�W�F�N�g�Ɏg�����b�V���f�[�^��ݒ�
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

	//�����蔻��p�̃R���C�_�[��ݒ�
	boxCollider = new BoxCollider(this);
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);

	//�X�P�[���̐ݒ�
	SetScale(200.0f);

	//��Q���Ǘ��N���X�Ɏ�����o�^
	OBSTACLE_MANAGER->AddObstacle(this);

	//�^�O��ݒ�
	tag = Tag::JumpingObstacle;

	//�X�e�[�g��ݒ�
	state = Paused;

	//�v���C���[�̃|�C���^��ۑ�
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
		//��Q���Ɠ����������̏���
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

