#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();

	void addFrame(sf::IntRect rect);
	void setSpriteSheet(const sf::Texture& texture);
	const sf::Texture* getSpriteSheet() const;

	std::size_t getSize() const;
	const sf::IntRect& getFrame(std::size_t num) const;

private:

	std::vector<sf::IntRect> _frames;
	const sf::Texture* _texture;
};

