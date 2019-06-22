#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

enum ButtonState
{
	None,
	Pressed,
	Released,
	Held
};

// Helper for keyboard input
class KeyboardState
{
public:
	// Friend so InputSystem can easily update it
	friend class InputSystem;
	// Get just the boolean true/false value of key
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// Get a state based on current and previous frame
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* currState;
	Uint8 prevState[SDL_NUM_SCANCODES];
};

// Helper for mouse input
class MouseState
{
public:
	friend class InputSystem;

	// For mouse position
	const Vector2& GetPosition() const { return mousePos; }
	const Vector2& GetScrollWheel() const { return scrollWheel; }
	bool IsRelative() const { return isRelative; }

	// For buttons
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	// Store current mouse position
	Vector2 mousePos;
	// Motion of scroll wheel
	Vector2 scrollWheel;
	// Store button data
	Uint32 currButtons;
	Uint32 prevButtons;
	// Are we in relative mouse mode
	bool isRelative;
};

// Helper for controller input
class ControllerState
{
public:
	friend class InputSystem;

	// For buttons
	bool GetButtonValue(SDL_GameControllerButton button) const;
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
