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
@brief	フレーム毎の処理
*/
void FPS::Update()
{
	deltaTime = (SDL_GetTicks() - beforetickCount) / 1000.0f;
	beforetickCount = SDL_GetTicks();
	//1フレーム目の時刻を保存
	if (fpsCount == 0)
	{
		frameStartTickTime = SDL_GetTicks();
	}
	//設定したフレーム数が経過したら
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
@brief	FPSが設定値より大きくならないための制御
*/
void FPS::Wait()
{
	int nowTickTime = SDL_GetTicks();
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), nowTickTime + oneFrameTickCount));
}
