#include "PauseMenu.h"
#include "DialogBox.h"
#include <SDL.h>
#include "Game.h"
#include "DialogBox.h"

PauseMenu::PauseMenu()
	:UIScreen()
{
	Game::SetState(Game::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("PauseTitle");
	AddButton("ResumeButton", [this]() {
		Close();
	});
	AddButton("QuitButton", [this]() {
		new DialogBox("QuitText",
			[this]() {
			Game::SetState(Game::EQuit);
		});
	});
}

PauseMenu::~PauseMenu()
{
	SetRelativeMouseMode(true);
	Game::SetState(Game::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);

	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}
