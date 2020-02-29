//=============================================================================
//	@file	BoxObject.h
//	@brief	ボックスのオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;

class BoxObject : public GameObject
{
public:
    BoxObject();
    ~BoxObject();

private:
    MeshComponent* meshComp;
    BoxCollider* boxCollider;

};

