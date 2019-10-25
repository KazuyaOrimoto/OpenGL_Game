#pragma once
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Math.h"

class Font
{
public:
	Font();
	~Font();

	// �t�@�C���̃��[�h�A�A�����[�h
	bool Load(const std::string& fileName);
	void Unload();

	// ��������e�N�X�`���ɕ`��
	class Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// �|�C���^�T�C�Y���t�H���g�f�[�^�̘A�z�z��
	std::unordered_map<int, TTF_Font*> fontData;
};
