#pragma once

#include "Property.h"
#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

	bool Load(const std::string& fileName);
	void Unload();

	void SetActive();

	cpp_module::ReadOnlyProperty<int> readOnlyWidth;
	cpp_module::ReadOnlyProperty<int> readOnlyHeight;

private:
	unsigned int textureID;

	int width;
	int height;
};

