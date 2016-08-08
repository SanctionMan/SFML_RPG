#pragma once

#include "SFML\Graphics.hpp"

class TextureManager
{
public:

	TextureManager();

	static int AddTexture(std::string filepath);
	static void RemoveTexture(int textureID);
	static sf::Texture& GetTexture(int textureID);

private:

	static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> m_textures;




};
