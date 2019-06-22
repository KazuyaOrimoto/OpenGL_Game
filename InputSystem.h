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
	bool GetKeyValue(SDL_Scancode keyCode) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_Scancodeのキーコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
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
	bool GetButtonValue(int button) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_BUTTON定数
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(int button) const;
private:
	//現在のマウスのポジション
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
	bool GetButtonValue(SDL_GameControllerButton button) const;

	/**
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_GameControllerButtonのボタンコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(SDL_GameControllerButton button) const;

	const Vector2& GetLeftStick() const { return leftStick; }
	const Vector2& GetRightStick() const { return rightStick; }
	float GetLeftTrigger() const { return leftTrigger; }
	float GetRightTrigger() const { return rightTrigger; }

	bool GetIsConnected() const { return isConnected; }
private:
	// Current/previous buttons
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];
	// Left/right sticks
	Vector2 leftStick;
	Vector2 rightStick;
	// Left/right trigger
	float leftTrigger;
	float rightTrigger;
	// Is this controller connected?
	bool isConnected;
};

// Wrapper that contains current state of input
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	// Called right before SDL_PollEvents loop
	void PrepareForUpdate();
	// Called after SDL_PollEvents loop
	void Update();
	// Called to process an SDL event in input system
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return state; }

	void SetRelativeMouseMode(bool value);
private:
	float Filter1D(int input);
	Vector2 Filter2D(int inputX, int inputY);
	InputState state;
	SDL_GameController* controller;
};
