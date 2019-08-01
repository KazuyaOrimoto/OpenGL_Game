#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;

class ObstacleObject : public GameObject
{
public:
	ObstacleObject(Game* game);
	~ObstacleObject();

	int GetHardness() { return hardness; }

	virtual void OnCollision(GameObject& argHitObject) override;

	void HitPlayer(const PlayerObject& argPlayerObject);

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	int hardness;
};

