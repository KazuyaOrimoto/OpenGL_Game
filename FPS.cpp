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

void FPS::Update()
{
	//1ÉtÉåÅ[ÉÄñ⁄ÇÃéûçèÇï€ë∂
	if (fpsCount == 0)
	{
		frameStartTickTime = SDL_GetTicks();
	}
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

void FPS::Wait()
{
	int nowTickTime = SDL_GetTicks();
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), nowTickTime + oneFrameTickCount));
}
