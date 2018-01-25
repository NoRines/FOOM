#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include "FrameBuffers/Bitmap.h"

class TextureManager
{
public:
	TextureManager(const TextureManager& rhs) = delete;
	TextureManager& operator=(const TextureManager& rhs) = delete;
	TextureManager(TextureManager&& rhs) = delete;
	TextureManager& operator=(TextureManager&& rhs) = delete;

	static TextureManager& get();

	Bitmap* loadTexture(const std::string& textureName);

private:
	TextureManager() = default;
	~TextureManager();

	std::map<std::string, Bitmap*> texMap;
};

#endif
