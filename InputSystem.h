#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

//�{�^���̏�Ԃ�\��
enum ButtonState
{
	None,		//������Ă��Ȃ�
	Pressed,	//�������t���[��
	Released,	//�������t���[��
	Held		//������Ă����
};

//�L�[�{�[�h�̓��͊Ǘ��N���X
class KeyboardState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̃L�[�̓��͏�Ԃ݂̂��擾����
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetKeyValue(SDL_Scancode keyCode) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	//���݂̃L�[�{�[�h�̓��͏��
	const Uint8* currState;
	//�P�t���[���O�̃L�[�{�[�h�̓��͏��
	Uint8 prevState[SDL_NUM_SCANCODES];
};

//�}�E�X�̓��͊Ǘ��N���X
class MouseState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̃}�E�X�̃|�W�V�������擾����
	@return	Position
	*/
	const Vector2& GetPosition() const { return mousePos; }

	/**
	@brief	���݂̃}�E�X�̃X�N���[���z�C�[���̏�Ԃ��擾����
	@return	�X�N���[���ʁiVector2�j
	*/
	const Vector2& GetScrollWheel() const { return scrollWheel; }

	/**
	@brief	���΃}�E�X���[�h���ǂ������擾����
	@return	true : ���΃��[�h , false , �ʏ탂�[�h
	*/
	bool IsRelative() const { return isRelative; }

	/**
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_BUTTON�萔
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(int button) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_BUTTON�萔
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetButtonState(int button) const;
private:
	//���݂̃}�E�X�̃|�W�V����
	Vector2 mousePos;
	//�X�N���[���z�C�[���̃X�N���[����
	Vector2 scrollWheel;
	// ���݂̃}�E�X�̓��͏��
	Uint32 currButtons;
	//�P�t���[���O�̃}�E�X�̓��͏��
	Uint32 prevButtons;
	// ���΃}�E�X���[�h���ǂ���
	bool isRelative;
};

// �R���g���[���[�̓��͊Ǘ��N���X
class ControllerState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

	/**
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(SDL_GameControllerButton button) const;

	/**
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	ButtonState�^�̌��݂̏��
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
