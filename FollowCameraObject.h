#pragma once

#include "GameObject.h"

class MoveConponent;
class FollowComponent;
class MeshComponent;

class FollowCameraObject : public GameObject
{
public:
	FollowCameraObject(Game* game);

	void SetVisible(bool visible);

private:
	class MoveComponent* mMoveComp;
	class FollowCamera* mCameraComp;
	class MeshComponent* mMeshComp;

};

