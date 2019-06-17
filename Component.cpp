#include "Component.h"
#include "GameObject.h"

/**
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
Component::Component(GameObject* argOwner, int argUpdateOrder)
	: owner(argOwner)
	, updateOrder(argUpdateOrder)
{
	owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}

/**
@param	�Ō�̃t���[������������̂ɗv��������
*/
void Component::Update(float argDeltaTime)
{
}
