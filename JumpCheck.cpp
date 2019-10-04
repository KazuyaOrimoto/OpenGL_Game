#include "JumpCheck.h"
#include "BikeObject.h"


JumpCheck::JumpCheck(BikeObject* _bike)
	: GameObject()
	, bike(_bike)
	, canJump(false)
{

}


JumpCheck::~JumpCheck()
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void JumpCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(bike->GetPosition());
}
