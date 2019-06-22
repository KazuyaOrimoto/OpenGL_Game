#include "InputSystem.h"
#include <SDL.h>
#include <cstring>

/**
@brief	現在のキーの入力状態のみを取得する
@param	SDL_Scancodeのキーコード
@return	true : 押されている , false : 押されていない
*/
bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return currState[keyCode] == 1;
}

/**
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_Scancodeのキーコード
@return	ButtonState型の現在の状態
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (prevState[keyCode] == 0)
	{
		if (currState[keyCode] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currState[keyCode] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/**
@brief	現在の入力状態のみを取得する
@param	SDL_BUTTON定数
@return	true : 押されている , false : 押されていない
*/
bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & currButtons) == 1;
}

/**
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_BUTTON定数
@return	ButtonState型の現在の状態
*/
ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & prevButtons) == 0)
	{
		if ((mask & currButtons) == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if ((mask & currButtons) == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/**
@brief	現在の入力状態のみを取得する
@param	SDL_GameControllerButtonのボタンコード
@return	true : 押されている , false : 押されていない
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	return currButtons[button] == 1;
}

/**
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_GameControllerButtonのボタンコード
@return	ButtonState型の現在の状態
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	if (prevButtons[button] == 0)
	{
		if (currButtons[button] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currButtons[button] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/**
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool InputSystem::Initialize()
{
	// Keyboard
	// Assign current state pointer
	state.Keyboard.currState = SDL_GetKeyboardState(NULL);
	// Clear previous state memory
	memset(state.Keyboard.prevState, 0,
		SDL_NUM_SCANCODES);

	// Mouse (just set everything to 0)
	state.Mouse.currButtons = 0;
	state.Mouse.prevButtons = 0;

	// Get the connected controller, if it exists
	controller = SDL_GameControllerOpen(0);
	// Initialize controller state
	state.Controller.isConnected = (controller != nullptr);
	memset(state.Controller.currButtons, 0,
		SDL_CONTROLLER_BUTTON_MAX);
	memset(state.Controller.prevButtons, 0,
		SDL_CONTROLLER_BUTTON_MAX);

	return true;
}

/**
@brief  終了処理
*/
void InputSystem::Shutdown()
{
}

/**
@brief  Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
*/
void InputSystem::PrepareForUpdate()
{
	// Copy current state to previous
	// Keyboard
	memcpy(state.Keyboard.prevState,
		state.Keyboard.currState,
		SDL_NUM_SCANCODES);

	// Mouse
	state.Mouse.prevButtons = state.Mouse.currButtons;
	state.Mouse.isRelative = false;
	state.Mouse.scrollWheel = Vector2::Zero;

	// Controller
	memcpy(state.Controller.prevButtons,
		state.Controller.currButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/**
@brief  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
*/
void InputSystem::Update()
{
	// Mouse
	int x = 0, y = 0;
	if (state.Mouse.isRelative)
	{
		state.Mouse.currButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		state.Mouse.currButtons =
			SDL_GetMouseState(&x, &y);
	}

	state.Mouse.mousePos.x = static_cast<float>(x);
	state.Mouse.mousePos.y = static_cast<float>(y);

	// Controller
	// Buttons
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		state.Controller.currButtons[i] =
			SDL_GameControllerGetButton(controller,
				SDL_GameControllerButton(i));
	}

	// Triggers
	state.Controller.leftTrigger =
		Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	state.Controller.rightTrigger =
		Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

	// Sticks
	x = SDL_GameControllerGetAxis(controller,
		SDL_CONTROLLER_AXIS_LEFTX);
	y = -SDL_GameControllerGetAxis(controller,
		SDL_CONTROLLER_AXIS_LEFTY);
	state.Controller.leftStick = Filter2D(x, y);

	x = SDL_GameControllerGetAxis(controller,
		SDL_CONTROLLER_AXIS_RIGHTX);
	y = -SDL_GameControllerGetAxis(controller,
		SDL_CONTROLLER_AXIS_RIGHTY);
	state.Controller.rightStick = Filter2D(x, y);
}

/**
@brief  SDLイベントをInputSystemに渡す
*/
void InputSystem::ProcessEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEWHEEL:
		state.Mouse.scrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
	default:
		break;
	}
}

/**
@brief  マウスのモードを設定する
@param	true : 相対モード , false : デフォルトモード
*/
void InputSystem::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	state.Mouse.isRelative = value;
}

/**
@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
@param	入力された値（int）
@return	フィルタリングされた値
*/
float InputSystem::Filter1D(int input)
{
	// A value < dead zone is interpreted as 0%
	const int deadZone = 250;
	// A value > max value is interpreted as 100%
	const int maxValue = 30000;

	float retVal = 0.0f;

	// Take absolute value of input
	int absValue = input > 0 ? input : -input;
	// Ignore input within dead zone
	if (absValue > deadZone)
	{
		// Compute fractional value between dead zone and max value
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		// Make sure sign matches original value
		retVal = input > 0 ? retVal : -1.0f * retVal;
		// Clamp between -1.0f and 1.0f
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/**
@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
@param	入力された値のx（int）
@param	入力された値のy（int）
@return	フィルタリングされた値
*/
Vector2 InputSystem::Filter2D(int inputX, int inputY)
{
	const float deadZone = 8000.0f;
	const float maxValue = 30000.0f;

	// Make into 2D vector
	Vector2 dir;
	dir.x = static_cast<float>(inputX);
	dir.y = static_cast<float>(inputY);

	float length = dir.Length();

	// If length < deadZone, should be no input
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		// Calculate fractional value between
		// dead zone and max value circles
		float f = (length - deadZone) / (maxValue - deadZone);
		// Clamp f between 0.0f and 1.0f
		f = Math::Clamp(f, 0.0f, 1.0f);
		// Normalize the vector, and then scale it to the
		// fractional value
		dir *= f / length;
	}

	return dir;
}
