#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

#define UI_MANAGER UIManager::GetInstance()

struct InputState;

class UIManager
{
public:
	static UIManager* GetInstance() { return uiManager; }

	/**
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/**
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	void Update(float deltaTime);

	void LoadText(const std::string& fileName);
	const std::string& GetText(const std::string& key);

	class Font* GetFont(const std::string& fileName);

	// Manage UI stack
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	//UI�����邩�ǂ���
	bool UIEmpty() { return mUIStack.empty(); }

	void HandleKeyPress(int key);

	void ProcessInput(const InputState& _keyState);

private:
	UIManager();
	~UIManager();

	static UIManager* uiManager;

	std::unordered_map<std::string, class Font*> mFonts;

	std::vector<class UIScreen*> mUIStack;

	std::unordered_map<std::string, std::string> text;
};

