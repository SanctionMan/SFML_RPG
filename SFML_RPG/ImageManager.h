#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
class ImageManager
{
public:
	ImageManager();
	~ImageManager();

private:
	ImageManager(const ImageManager&);
	//ImageManager& operator =(const ImageManager&);

public:
	const sf::Image& GetImage(const std::string& filename);
	void DeleteImage(const sf::Image& image);
	void DeleteImage(const std::string& filename);
	void Add_Resource_Directory(const std::string& directory);
	void Remove_Resource_Directory(const std::string& directory);

private:
	std::map<std::string, sf::Image> m_Images;
	std::vector<std::string> m_Resource_Directories;
};
