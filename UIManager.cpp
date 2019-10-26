#include "UIManager.h"
#include "Font.h"
#include "UIScreen.h"
#include <document.h>
#include <sstream>
#include <fstream>

UIManager* UIManager::uiManager = nullptr;

void UIManager::HandleKeyPress(int key)
{
	mUIStack.back()->HandleKeyPress(key);
}

void UIManager::ProcessInput(const InputState & _keyState)
{
	mUIStack.back()->ProcessInput(_keyState);
}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::CreateInstance()
{
	if (uiManager == nullptr)
	{
		uiManager = new UIManager();
	}
}

void UIManager::DeleteInstance()
{
	if (uiManager != nullptr)
	{
		delete uiManager;
		uiManager = nullptr;
	}
}

void UIManager::Update(float deltaTime)
{
	// Update UI screens
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete *iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void UIManager::LoadText(const std::string & fileName)
{
	// 既存の連想配列をクリア
	text.clear();
	// ファイルを開く
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	// ファイル全体を読み込む
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	// jsonでファイルを読み込む
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	// テキストを読み取る
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			text.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}
}

const std::string & UIManager::GetText(const std::string & key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = text.find(key);
	if (iter != text.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

Font * UIManager::GetFont(const std::string & fileName)
{
	auto iter = mFonts.find(fileName);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font();
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

void UIManager::PushUI(UIScreen * screen)
{
	mUIStack.emplace_back(screen);
}
