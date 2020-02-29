//=============================================================================
//	@file	SphereObject.h
//	@brief	球のオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"

class MeshComponent;
class SphereCollider;

class SphereObject : public GameObject
{
public:
	SphereObject();
	~SphereObject();

private:
	MeshComponent* meshComp;
	SphereCollider* sphereCollider;

};

