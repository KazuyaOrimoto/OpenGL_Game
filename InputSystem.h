#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

//ボタンの状態を表す
enum ButtonState
{
	None,		//押されていない
	Pressed,	//押したフレーム
	Released,	//離したフレーム
	Held		//押されている間
};

//キーボードの入力管理クラス
class KeyboardState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;

	/**
	@brief	現在のキーの入力状態のみを取得する
	@param	SDL_Scancodeのキーコード
	@return	true : 押されている , false : 押されていない
	*/
	bool GetKeyValue(SDL_Scancode _keyCode) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_Scancodeのキーコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetKeyState(SDL_Scancode _keyCode) const;
private:
	//現在のキーボードの入力状態
	const Uint8* currState;
	//１フレーム前のキーボードの入力状態
	Uint8 prevState[SDL_NUM_SCANCODES];
};

//マウスの入力管理クラス
class MouseState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;

	/**
	@brief	現在のマウスのポジションを取得する
	@return	Position
	*/
	const Vector2& GetPosition() const { return mousePos; }

	/**
	@brief	現在のマウスのスクロールホイールの状態を取得する
	@return	スクロール量（Vector2）
	*/
	const Vector2& GetScrollWheel() const { return scrollWheel; }

	/**
	@brief	相対マウスモードかどうかを取得する
	@return	true : 相対モード , false , 通常モード
	*/
	bool IsRelative() const { return isRelative; }

	/**
	@brief	現在の入力状態のみを取得する
	@param	SDL_BUTTON定数
	@return	true : 押されている , false : 押されていない
	*/
	bool GetButtonValue(int _button) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_BUTTON定数
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(int _button) const;
private:
	//マウスのポジション
	Vector2 mousePos;
	//スクロールホイールのスクロール量
	Vector2 scrollWheel;
	// 現在のマウスの入力状態
	Uint32 currButtons;
	//１フレーム前のマウスの入力状態
	Uint32 prevButtons;
	// 相対マウスモードかどうか
	bool isRelative;
};

// コントローラーの入力管理クラス
class ControllerState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;

	/**
	@brief	現在の入力状態のみを取得する
	@param	SDL_GameControllerButtonのボタンコード
	@return	true : 押されている , false : 押されていない
	*/
	bool GetButtonValue(SDL_GameControllerButton _button) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_GameControllerButtonのボタンコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(SDL_GameControllerButton _button) const;

	///**
	//@brief	左のスティックの入力値を取得する
	//@return	入力値（-1.0~1.0）
	//*/
	//const Vector2& GetLeftStick() const { return leftStick; }

	///**
	//@brief	右のスティックの入力値を取得する
	//@return	入力値（-1.0~1.0）
	//*/
	//const Vector2& GetRightStick() const { return rightStick; }

	///**
	//@brief	左のトリガーの入力値を取得する
	//@return	入力値（0.0~1.0）
	//*/
	//float GetLeftTrigger() const { return leftTrigger; }

	///**
	//@brief	右のトリガーの入力値を取得する
	//@return	入力値（0.0~1.0）
	//*/
	//float GetRightTrigger() const { return rightTrigger; }

private:
	//現在のボタンの入力状態
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	//１フレーム前のボタンの入力状態
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];
};

//各入力機器の入力状態をまとめたラッパー構造体
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize();

	/**
	@brief  終了処理
	*/
	void Shutdown();

	/**
	@brief  Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
	*/
	void PrepareForUpdate();

	/**
	@brief  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
	*/
	void Update();

	/**
	@brief  SDLイベントをInputSystemに渡す
	*/
	void ProcessEvent(union SDL_Event& _event);

	/**
	@brief  現在の入力状態を取得する
	@return （InputState）各入力情報をまとめた構造体
	*/
	const InputState& GetState() const { return state; }

	/**
	@brief  マウスのモードを設定する
	@param	true : 相対モード , false : デフォルトモード
	*/
	void SetRelativeMouseMode(bool _value);
private:
	/**
	@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
	@param	入力された値（int）
	@return	フィルタリングされた値
	*/
	float Filter1D(int _input);

	/**
	@brief  入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
	@param	入力された値のx（int）
	@param	入力された値のy（int）
	@return	フィルタリングされた値
	*/
	Vector2 Filter2D(int _inputX, int _inputY);

	//各入力機器の入力状態をまとめたラッパー構造体
	InputState state;
	//SDLでコントローラーを認識するためのクラスポインタ
	SDL_GameController* controller;
};
