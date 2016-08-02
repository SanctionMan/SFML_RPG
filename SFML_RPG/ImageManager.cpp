#include "ImageManager.h"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	m_Images.clear();
	m_Resource_Directories.clear();
}

//ImageManager & ImageManager::operator=(const ImageManager &)
//{
//	return ImageManager &;
//}

const sf::Image & ImageManager::GetImage(const std::string & filename)
{
	// Check, whether the image already exists
	for (std::map<std::string, sf::Image>::const_iterator it = m_Images.begin();
		it != m_Images.end();
		++it)
	{
		if (filename == it->first)
		{
			std::cout << "DEBUG_MESSAGE: " << filename << " using existing image.\n";
			return it->second;
		}
	}

	// The image doesen't exists. Create it and save it.
	sf::Image image;
	
	// Search project's main directory
	if (image.loadFromFile(filename))
	{
		m_Images[filename] = image;
		std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
		return m_Images[filename];
	}

	// If the image has still not been found, search all registered directories
	for (std::vector< std::string >::iterator it = m_Resource_Directories.begin();
		it != m_Resource_Directories.end();
		++it)
	{
		if (image.loadFromFile((*it) + filename))
		{
			m_Images[filename] = image;
			std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
			return m_Images[filename];
		}

	}

	std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
	m_Images[filename] = image;
	return m_Images[filename];
}

void ImageManager::DeleteImage(const sf::Image & image)
{
	for (std::map<std::string, sf::Image>::const_iterator it = m_Images.begin();
		it != m_Images.end();
		++it)
	{
		if (&image == &it->second)
		{
			m_Images.erase(it);
			return;
		}
	}
}

void ImageManager::DeleteImage(const std::string & filename)
{
	std::map<std::string, sf::Image>::const_iterator it = m_Images.find(filename);
	if (it != m_Images.end())
		m_Images.erase(it);
}

void ImageManager::Add_Resource_Directory(const std::string & directory)
{
	// Check whether the path already exists
	for (std::vector<std::string>::const_iterator it = m_Resource_Directories.begin();
		it != m_Resource_Directories.end();
		++it)
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			return;
	}

	// insert the directory
	m_Resource_Directories.push_back(directory);
}

void ImageManager::Remove_Resource_Directory(const std::string & directory)
{
	for (std::vector<std::string>::iterator it = m_Resource_Directories.begin();
		it != m_Resource_Directories.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			it = m_Resource_Directories.erase(it);
		else
			++it;
	}
}

