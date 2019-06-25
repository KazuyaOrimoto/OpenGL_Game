#include "SDL.h"
#include "FPS.h"

FPS::FPS()
	: setFps(60)
	, oneFrameTickCount(1000 / setFps)
	, fpsCount(0)
	, frameStartTickTime(0)
	, fps(0)
{

}

FPS::~FPS()
{
}

/**
@brief	�t���[�����̏���
*/
void FPS::Update()
{
	deltaTime = (SDL_GetTicks() - beforetickCount) / 1000.0f;
	beforetickCount = SDL_GetTicks();
	//1�t���[���ڂ̎�����ۑ�
	if (fpsCount == 0)
	{
		frameStartTickTime = SDL_GetTicks();
	}
	//�ݒ肵���t���[�������o�߂�����
	if (fpsCount == setFps)
	{
		int nowTickTime = SDL_GetTicks();
		fps = 1000 / ((nowTickTime - frameStartTickTime) / setFps);
		fpsCount = 0;
	}
	else
	{
		fpsCount++;
	}
	Wait();
}

/**
@brief	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
*/
void FPS::Wait()
{
	int nowTickTime = SDL_GetTicks();
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), nowTickTime + oneFrameTickCount));
}
