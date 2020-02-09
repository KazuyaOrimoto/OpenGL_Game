#pragma once
#include "GameObject.h"
class TitlePlayer :
	public GameObject
{
public:
	TitlePlayer();
	~TitlePlayer();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

private:

	class HDRMeshComponent* meshComp;
	class TitleCamera* camera;
	class AutoRunComponent* autoRun;
	class EffectComponent* effect;

};

