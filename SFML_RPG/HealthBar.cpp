#include "HealthBar.h"



HealthBar::HealthBar():
	_size(sf::Vector2f(35, 6)),
	_backgroundAdjustment(sf::Vector2f(0, 0)),
	_healthAdjustment(sf::Vector2f(0, 0)),
	_manaAdjustment(sf::Vector2f(0, 0)),
	_position(sf::Vector2f(0, 0)),
	_background(_size),
	_healthBar(sf::Vector2f(_size.x, _size.y / 2)),
	_manaBar(sf::Vector2f(_size.x, _size.y / 2))
{
	_healthAdjustment = sf::Vector2f(-(_size.x / 2), -(_size.y / 2));
	_manaAdjustment = sf::Vector2f(-(_size.x / 2), 0);


	_background.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));
	_background.setFillColor(sf::Color::Black);
	_background.setOutlineColor(sf::Color::Black);
	_background.setOutlineThickness(1);

	//_healthBar.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));
	_healthBar.setFillColor(sf::Color::Green);

	//_manaBar.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));
	_manaBar.setFillColor(sf::Color::Blue);
}


HealthBar::~HealthBar()
{
}

void HealthBar::update(sf::Time _deltaTime)
{
	// Update healthbar position
	_background.setPosition(_position + _backgroundAdjustment);
	_healthBar.setPosition(_position + _backgroundAdjustment + _healthAdjustment);
	_manaBar.setPosition(_position + _backgroundAdjustment + _manaAdjustment);


	// Update healthbar size
	float newSize;
	float percent = _currentHealth / _maxHealth;

	if (_currentHealth >= 0 && _currentHealth <= _maxHealth)
	{
		newSize = (_currentHealth / _maxHealth) * _size.x;
		_healthBar.setSize(sf::Vector2f(newSize, _size.y / 2));
	}
	// Update manabar size
	if (_currentMana >= 0 && _currentMana <= _maxMana)
	{
		newSize = (_currentMana / _maxMana) * _size.x;
		_manaBar.setSize(sf::Vector2f(newSize, _size.y / 2));
	}

	//Set color
	if (percent <= .30 )
		_healthBar.setFillColor(sf::Color::Red);
	else
		_healthBar.setFillColor(sf::Color::Green);
}

void HealthBar::render(sf::RenderWindow& _window)
{
	_window.draw(_background);
	_window.draw(_healthBar);
	_window.draw(_manaBar);
}

void HealthBar::setPosition(sf::Vector2f position)
{
	_position = position;
}

void HealthBar::setPosition(float x, float y)
{
	_position = sf::Vector2f(x, y);
}

void HealthBar::setCurrentHealth(float &health)
{
	_currentHealth = health;
}

void HealthBar::setCurrentMana(float &mana)
{
	_currentMana = mana;
}

void HealthBar::setMaxHealth(float &maxHealth)
{
	_maxHealth = maxHealth;
}

void HealthBar::setMaxMana(float &maxMana)
{
	_maxMana = maxMana;
}

void HealthBar::setAdjustment(sf::Vector2f adjustment)
{
	_backgroundAdjustment = adjustment;
}
