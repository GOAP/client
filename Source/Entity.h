#pragma once
#include <SFML/Graphics.hpp>


class Entity
{
protected: 
	int _id;

	sf::Vector2f _position;
	sf::Sprite _sprite;

	sf::Vector2f _publicPosition;

public: 
	/*DRAW METHOD IMPLEMENT*/

	sf::Vector2f getPosition()
	{
		_publicPosition.x = _position.x + _sprite.getLocalBounds().height / 2;
		_publicPosition.y = _position.y + _sprite.getLocalBounds().width / 2;
		
		return _publicPosition;
	}
};

