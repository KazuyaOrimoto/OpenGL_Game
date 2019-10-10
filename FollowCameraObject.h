#pragma once

#include "GameObject.h"

class MoveConponent;
class FollowComponent;
class MeshComponent;

class FollowCameraObject : public GameObject
{
public:
	FollowCameraObject();

	void SetVisible(bool _visible);

private:
	class MoveComponent* mMoveComp;
	class FollowCamera* mCameraComp;
	class MeshComponent* mMeshComp;
	class SphereCollider* sphereCollider;
};

