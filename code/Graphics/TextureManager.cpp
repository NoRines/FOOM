#include "TextureManager.h"

TextureManager& TextureManager::get()
{
	static TextureManager textureManager;
	return textureManager;
}

TextureManager::~TextureManager()
{
	for(auto itt = texMap.begin(); itt != texMap.end(); itt++)
	{
		delete itt->second;
	}
}

Bitmap* TextureManager::loadTexture(const std::string& textureName)
{
	auto textureItt = texMap.find(textureName);

	if(textureItt == texMap.end()) // No texture was found
	{
		// Load the texture
		std::string fileName = "data/" + textureName + ".bmp";

		Bitmap* texture = new Bitmap(
				std::move(Bitmap::loadFromBMPFile(fileName.c_str()))
				);

		if(texture->isValid()) // Check that the texture was loaded
		{
			texMap[textureName] = texture;
			return texMap[textureName];
		}
	}
	else
	{
		// Texture was found return texture
		return textureItt->second;
	}

	return nullptr; // The texture could not be loaded
}
