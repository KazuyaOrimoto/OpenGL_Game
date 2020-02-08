#pragma once
#include "GameObject.h"

class MoveComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;
class ObstacleObject;
class RotateComponent;
class BikeObject;
class Texture;
class EffectComponent;

class PlayerObject : public GameObject
{
public:
	PlayerObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	RotateComponent* GetRotate() const { return rotate; }
	float playerSpeed;

	/**
 @brief	入力処理
 @param	InputState構造体
 */
	virtual void GameObjectInput(const InputState& _state)override;

    bool CanMove();

private:
#ifdef _DEBUG
	virtual void ShowGameObject() override;
#endif // _DEBUG

    MoveComponent* moveComp;
    MainCamera* camera;
    AutoRunComponent* autoRun;
	RotateComponent* rotate;
	BikeObject* bike;
	Texture* texture;
	EffectComponent* effect;
};

