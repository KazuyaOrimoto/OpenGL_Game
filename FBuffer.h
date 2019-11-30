#pragma once

#include <vector>

class FBuffer
{
public:
	FBuffer();
	~FBuffer();

	// Create/destroy the G-buffer
	bool Create(int width, int height);
	void Destroy();

	// Get the texture for a specific type of data
	class Texture* GetTexture();
	// Get the framebuffer object ID
	unsigned int GetBufferID() const { return mBufferID; }
	// Setup all the G-buffer textures for sampling
	void SetTexturesActive();
private:
	// Textures associated with G-buffer
	std::vector<class Texture*> mTextures;
	// Frame buffer object ID
	unsigned int mBufferID;
};

