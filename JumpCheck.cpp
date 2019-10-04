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
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void JumpCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(bike->GetPosition());
}
