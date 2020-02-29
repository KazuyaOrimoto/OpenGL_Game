//=============================================================================
//	@file	TitleCamera.h
//	@brief	タイトル用のカメラ
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "CameraComponent.h"
class TitleCamera :
	public CameraComponent
{
public:
	TitleCamera(GameObject* _owner);
	~TitleCamera();

	void Update(float _deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float _dist) { horzDist = _dist; }
	void SetVertDist(float _dist) { vertDist = _dist; }
	void SetTargetDist(float _dist) { targetDist = _dist; }
	void SetSpringConstant(float _spring) { springConstant = _spring; }

	float GetHorzDist() { return horzDist; }
	float GetVertDist() { return vertDist; }
	float GetTargetDist() { return targetDist; }
	float GetSpringConstant() { return springConstant; }
private:

	Vector3 ComputeCameraPos() const;

	Vector3 actualPos;

	Vector3 velocity;

	float horzDist;

	float vertDist;

	float targetDist;

	float springConstant;

	float radsave;

};

