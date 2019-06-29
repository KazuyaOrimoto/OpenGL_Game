#pragma once
#include "Math.h"
#include <vector>

//����
struct LineSegment
{
	/**
	@param	�����̊J�n�n�_�̃|�W�V����
	@param	�����̏I���n�_�̃|�W�V����
	*/
    LineSegment(const Vector3& argStart, const Vector3& argEnd);
	
	/**
	@brief	������̓_��Ԃ�
	@param	���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����
	*/
	Vector3 PointOnSegment(float t) const;
	
	/**
	@brief	�_�Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	�C�ӂ̓_�̃|�W�V����
	@return �ŒZ����
	*/
    float MinDistanceSquared(const Vector3& argPoint)const;

	/**
	@brief	�����Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	���肷������̍\���̂P
	@param	���肷������̍\���̂Q
	@return �ŒZ����
	*/
    static float MinDistanceSquared(const LineSegment& argLine1,const LineSegment& argLine2);

	//�����̊J�n�n�_
    Vector3 start;
	//�����̏I���n�_
    Vector3 end;
};

//����
struct Plane
{
	/**
	@param	���ʂ̖@���x�N�g��
	@param	���ʂƌ��_�̕������ŒZ����
	*/
    Plane(const Vector3& argNormal, float argDistance);

	/**
	@param	���ʏ�̓_1
	@param	���ʏ�̓_2
	@param	���ʏ�̓_3
	*/
    Plane(const Vector3& argVec1, const Vector3& argVec2, const Vector3& argVec3);

	/**
	@brief	�_�ƕ��ʂ̍ŒZ������Ԃ�
	@param	�C�ӂ̓_�̃|�W�V����
	@return �������ŒZ����
	*/
    float SignedDistance(const Vector3& argPoint);

	//���ʂ̖@���x�N�g��
    Vector3 normal;
	//���ʂƌ��_�̕������ŒZ����
    float distance;
};

//��
struct Sphere
{
	/**
	@param	���̂̒��S���W
	@param	���̂̔��a
	*/
    Sphere(const Vector3& argCenter, const float argRadius);
    
	/**
	@brief	���̂ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
	bool Contains(const Vector3& argPoint)const;

	//���̂̒��S���W
    Vector3 center;
	//���̂̔��a
    float radius;
};

//�����s�o�E���f�B���O�{�b�N�X(Axis-Aligned Bounding Box)
struct AABB
{
	/**
	@param	�ŏ���x,y,z�̒l�̃|�W�V����
	@param	�ő��x,y,z�̒l�̃|�W�V����
	*/
    AABB(const Vector3& argMin,const Vector3& argMax);

	/**
	@brief	�ŏ��l�ƍő�l���e�������ƂɍX�V����
	@param	�C�ӂ̓_�̃|�W�V����
	*/
    void UpdateMinMax(const Vector3& argPoint);

	/**
	@brief	�����蔻��{�b�N�X�̉�]
	@param	��]���Ɖ�]�\���l�iQuaternion�j
	*/
    void Rotate(const Quaternion& argQuaternion);
    
	/**
	@brief	�{�b�N�X�ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
	bool Contains(const Vector3& argPoint)const;
    
	/**
	@brief	�_�ƃ{�b�N�X�̍ŒZ������Ԃ�
	@param	�C�ӂ̓_
	@return �ŒZ����
	*/
	float MinDistanceSquared(const Vector3& argPoint)const;

    Vector3 min;
    Vector3 max;
};

//�L���o�E���f�B���O�{�b�N�X�iOriented Bounding Box�j
//������
struct OBB
{
	//���S�̍��W
    Vector3 center;
	//��]�N�H�[�^�j�I��
    Quaternion rotation;
	//�{�b�N�X�̍L����i���A�����A���s���j
    Vector3 extents;
};

//�J�v�Z��
struct Capsule
{
	/**
	@param	�n�_�ƂȂ�_�̍��W
	@param	�I�_�ƂȂ�_�̍��W
	@param	�J�v�Z���̔��a
	*/
    Capsule(const Vector3& argStart,const Vector3& argEnd,float argRadius);

	/**
	@brief	�J�v�Z���̎n�_�ƏI�_�̐�����̓_��Ԃ�
	@param	���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����
	*/
    Vector3 PointOnSegment(float t)const;

	/**
	@brief	�J�v�Z���ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
    bool Contains(const Vector3& argPoint)const;

	//�J�v�Z�����\���������
    LineSegment segment;
	//�J�v�Z���̔��a
    float radius;
};

//�ʃ|���S��
struct ConvexPolygon
{
	/**
	@brief	�Q�����̃|���S���ɓ_���܂܂�Ă��邩�ǂ���
	@param	�C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�
	*/
    bool Contains(const Vector2& argPoint)const;

	//���_�̉ϒ��R���e�i
    std::vector<Vector2> vertices;
};

/**
@brief	���Ƌ��̓����蔻��
@param	���̍\���̂P
@param	���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere& argSphere1,const Sphere& argSphere2);

/**
@brief	�{�b�N�X�ƃ{�b�N�X�̓����蔻��
@param	�{�b�N�X�̍\���̂P
@param	�{�b�N�X�̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const AABB& argAABB1, const AABB& argAABB2);

/**
@brief	�J�v�Z���ƃJ�v�Z���̓����蔻��
@param	�J�v�Z���̍\���̂P
@param	�J�v�Z���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Capsule& argCapsule1, const Capsule& argCapsule2);

/**
@brief	���ƃ{�b�N�X�̓����蔻��
@param	���̍\����
@param	�{�b�N�X�̍\����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const Sphere& argSphere, const AABB& argAABB);

/**
@brief	�����Ƌ��̓����蔻��
@param	�����̍\����
@param	���̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& argLine, const Sphere& argSphere, float& outT);

/**
@brief	�����ƕ��ʂ̓����蔻��
@param	�����̍\����
@param	���ʂ̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& argLine, const Plane& argPlane, float& outT);

/**
@brief	�����ƃ{�b�N�X�̓����蔻��
@param	�����̍\����
@param	�{�b�N�X�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@param	�����̎n�_����ڐG�����ʂ̖@���x�N�g�����i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool Intersect(const LineSegment& argLine, const AABB& argAABB, float& outT,
    Vector3& outNorm);

/**
@brief	���X�C�[�v�̓����蔻��
@param	�P�t���[���O�̋��P�̍\����
@param	���݂̃t���[���̋��P�̍\����
@param	�P�t���[���O�̋��Q�̍\����
@param	���݂̃t���[���̋��Q�̍\����
@param	�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�
*/
bool SweptSphere(const Sphere& argSphere1, const Sphere& argSphere2,
    const Sphere& argSphere3, const Sphere& argSphere4, float& outT);
