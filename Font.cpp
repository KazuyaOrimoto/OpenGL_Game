#include "Font.h"
#include "Texture.h"
#include <vector>
#include "Game.h"

Font::Font()
{

}

Font::~Font()
{

}

bool Font::Load(const std::string& fileName)
{
	// �T�|�[�g����t�H���g�T�C�Y
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	// �T�C�Y���Ƃ�TTF_OpenFont���P�񂸂Ăяo��
	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		fontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::RenderText(const std::string& textKey,
	const Vector3& color /*= Color::White*/,
	int pointSize /*= 24*/)
{
	Texture* texture = nullptr;

	// �F��SDL�J���[�ɕϊ�����
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// �w��T�C�Y�̃t�H���g�f�[�^��T��
	auto iter = fontData.find(pointSize);
	if (iter != fontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = mGame->GetText(textKey);
		// SDL_Surface�ɕ`��(���u�����f�B���O����)
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// SDL_Surface����e�N�X�`���ɕϊ�����
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}
