#pragma once
class FPS
{
public:
	FPS();
	~FPS();
	void Update();

private:
	void Wait();

	const Uint32 setFps;
	const Uint8 oneFrameTickCount;
	Uint8 fpsCount;
	Uint32 frameStartTickTime;
	Uint32 fps;

};

