#pragma once
class FPS
{
public:
	FPS();
	~FPS();
	void Update();

    int x, y;

private:
	void Wait();

	const Uint32 setFps;
	const Uint32 oneFrameTickCount;
	Uint32 fpsCount;
	Uint32 frameStartTickTime;
	Uint32 fps;

};

