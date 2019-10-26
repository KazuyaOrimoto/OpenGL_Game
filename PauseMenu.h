#pragma once
#include "UIScreen.h"
class PauseMenu :
	public UIScreen
{
public:
	PauseMenu();
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

