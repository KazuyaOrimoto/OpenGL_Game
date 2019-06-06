#pragma once

class FPS;

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void Termination();
	void GameLoop();

private:

    void ProcessInput();
    void GenerateOutput();

	SDL_Window* window;
	SDL_Renderer* renderer;
	FPS *fps;

    bool isRunning;

};

