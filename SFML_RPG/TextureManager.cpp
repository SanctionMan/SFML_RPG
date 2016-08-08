#include "TextureManager.h"

TextureManager::TextureManager()
{
}

map<string, sf::Texture*> TextureManager::textures;
std::vector<string> TextureManager::order;

// Get Length of Textures Array
int TextureManager::getLength() {
	return textures.size();
}

void TextureManager::showTexturesList()
{
	std::cout << "<-- TextureManager -->" << std::endl;
	for (int i = 0; i < order.size(); i++)
	{
		std::cout << "Texture"<< i + 1 << ": " << order[i] << std::endl;
	}
	std::cout << std::endl;
}

// Get Texture by Name
sf::Texture *TextureManager::getTexture(string name)
{

	// See if we have already loaded this texture
	if (textures.find(name) != textures.end()) {
		return textures[name];
	}
	else {
		return NULL;
	}
}

// Get Texture by Index
sf::Texture *TextureManager::getTexture(int index)
{
	// Stay DRY and reuse get by name, but get string name from vector with index
	return getTexture(order.at(index));
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture *TextureManager::loadTexture(string name, string path)
{
	// Haven't loaded it yet, time to create it
	sf::Texture *texture = new sf::Texture();
	std::cout << "<-- TextureManager -->" << std::endl;
	if (texture->loadFromFile(path))
	{
		textures[name] = texture;

		// Push to vector the order in which items were loaded into map, for accessing via index.
		order.push_back(name);
		std::cout << "Created: "<< name << std::endl;
		std::cout << std::endl;
		return textures[name];
	}
	else
	{
		// Could not load the file
		std::cout << "TextureManager: could not load " << name << std::endl;
		delete texture;
		return NULL;
	}

}

TextureManager::~TextureManager()
{

	// Delete all of the textures we used
	std::cout << "<-- TextureManager -->" << std::endl;
	sf::Texture *texture;
	map<string, sf::Texture*>::iterator iter = textures.begin();
	while (iter != textures.end())
	{
		texture = iter->second;
		delete texture;
		std::cout << "Delete: " << iter->first << std::endl;
		iter++;
	}
	std::cout << std::endl;
}