#include "InputSystem.h"
#include <SDL.h>
#include <cstring>

/**
@brief	���݂̃L�[�̓��͏�Ԃ݂̂��擾����
@param	SDL_Scancode�̃L�[�R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return currState[keyCode] == 1;
}

/**
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_Scancode�̃L�[�R�[�h
@return	ButtonState�^�̌��݂̏��
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
@brief	���݂̓��͏�Ԃ݂̂��擾����
@param	SDL_BUTTON�萔
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & currButtons) == 1;
}

/**
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_BUTTON�萔
@return	ButtonState�^�̌��݂̏��
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
@brief	���݂̓��͏�Ԃ݂̂��擾����
@param	SDL_GameControllerButton�̃{�^���R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	return currButtons[button] == 1;
}

/**
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_GameControllerButton�̃{�^���R�[�h
@return	ButtonState�^�̌��݂̏��
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
@brief  ����������
@return true : ���� , false : ���s
*/
bool InputSystem::Initialize()
{
	//�L�[�{�[�h�̏���������
	//���̃L�[�{�[�h�̏�Ԃ����蓖�Ă�
	state.Keyboard.currState = SDL_GetKeyboardState(NULL);
	//�P�t���[���O�̓��͏�Ԃ�����������
	memset(state.Keyboard.prevState, 0,
		SDL_NUM_SCANCODES);

	//���݂ƂP�t���[���O�̃}�E�X�̓��͏�Ԃ�����������
	state.Mouse.currButtons = 0;
	state.Mouse.prevButtons = 0;

	//�R���g���[���[���ڑ�����Ă���Ȃ�擾����
	controller = SDL_GameControllerOpen(0);
	//�R���g���[���[���ڑ�����Ă��邩���L�^����
	state.Controller.isConnected = (controller != nullptr);
	//���݂ƂP�t���[���O�̃R���g���[���[�̓��͏�Ԃ�����������
	memset(state.Controller.currButtons, 0,
		SDL_CONTROLLER_BUTTON_MAX);
	memset(state.Controller.prevButtons, 0,
		SDL_CONTROLLER_BUTTON_MAX);

	return true;
}

/**
@brief  �I������
*/
void InputSystem::Shutdown()
{
}

/**
@brief  Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
*/
void InputSystem::PrepareForUpdate()
{
	//���݂̓��͏�Ԃ��P�t���[���O�̓��͏�ԂɃR�s�[����
	//�L�[�{�[�h
	memcpy(state.Keyboard.prevState,
		state.Keyboard.currState,
		SDL_NUM_SCANCODES);

	//�}�E�X
	state.Mouse.prevButtons = state.Mouse.currButtons;
	state.Mouse.isRelative = false;
	state.Mouse.scrollWheel = Vector2::Zero;

	//�R���g���[���[
	memcpy(state.Controller.prevButtons,
		state.Controller.currButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/**
@brief  �t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
*/
void InputSystem::Update()
{
	//�}�E�X
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

	state.Mouse.mousePos.x = static_cast<float>(x) - 1024.0f/2;
	state.Mouse.mousePos.y = 768.0f / 2 - static_cast<float>(y);

	//�R���g���[���[
	//�E�{�^��
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		state.Controller.currButtons[i] =
			SDL_GameControllerGetButton(controller,
				SDL_GameControllerButton(i));
	}

	//�E�g���K�[
	state.Controller.leftTrigger =
		Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	state.Controller.rightTrigger =
		Filter1D(SDL_GameControllerGetAxis(controller,
			SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

	//�E�X�e�B�b�N
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
@brief  SDL�C�x���g��InputSystem�ɓn��
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
@brief  �}�E�X�̃��[�h��ݒ肷��
@param	true : ���΃��[�h , false : �f�t�H���g���[�h
*/
void InputSystem::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	state.Mouse.isRelative = value;
}

/**
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
@param	���͂��ꂽ�l�iint�j
@return	�t�B���^�����O���ꂽ�l
*/
float InputSystem::Filter1D(int input)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const int deadZone = 250;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const int maxValue = 30000;

	float retVal = 0.0f;

	//���͒l�̐�Βl�����
	int absValue = input > 0 ? input : -input;
	//���͒l���f�b�h�]�[����菬�����Ȃ�
	if (absValue > deadZone)
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		//���������̒l�Ɠ����ɂ���
		retVal = input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0�̊ԂɎ��߂�
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/**
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
@param	���͂��ꂽ�l��x�iint�j
@param	���͂��ꂽ�l��y�iint�j
@return	�t�B���^�����O���ꂽ�l
*/
Vector2 InputSystem::Filter2D(int inputX, int inputY)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const float deadZone = 8000.0f;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const float maxValue = 30000.0f;

	//2�����x�N�g���ɂ���
	Vector2 dir;
	dir.x = static_cast<float>(inputX);
	dir.y = static_cast<float>(inputY);

	float length = dir.Length();

	//���͒l�̃x�N�g���̒������f�b�h�]�[����菬�����Ȃ�
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		float f = (length - deadZone) / (maxValue - deadZone);
		//0.0��1.0�̊ԂɎ��߂�
		f = Math::Clamp(f, 0.0f, 1.0f);
		//�x�N�g���𐳋K�����āA�����̒l�ɃX�P�[�����O����
		dir *= f / length;
	}

	return dir;
}