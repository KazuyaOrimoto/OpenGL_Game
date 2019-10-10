#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Renderer.h"

/**
@param	ゲームクラスのポインタ
*/
Ship::Ship()
	:GameObject()
{
	SpriteComponent* sprite = new SpriteComponent(this,100);
	sprite->SetTexture(RENDERER->GetTexture("Assets/Cube.png"));

}

Ship::~Ship()
{
}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void Ship::UpdateGameObject(float _deltaTime)
{
}
