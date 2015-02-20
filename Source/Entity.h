#pragma once
#include <SFML/Graphics.hpp>


class Entity
{
	friend bool operator==(const Entity &left, const Entity &right)
	{
		return left._position.x == right._position.x && left._position.y == right._position.y;
	}
protected: 
	int _id;

	std::string _name;

	sf::Vector2f _position;
	sf::Sprite _sprite;

	sf::Vector2f _publicPosition;

public: 
	/*DRAW METHOD IMPLEMENT*/
	sf::Sprite getSprite()
	{
		_sprite.setPosition(_position);
		//_sprite.setScale(0.15, 0.15);
		return _sprite;
	}
	sf::Vector2f getPosition()
	{
		_publicPosition.x = _position.x + 15/ 2;
		_publicPosition.y = _position.y + 15 / 2;
		
		return _publicPosition;
	}
	int getId()
	{
		return _id;
	}
	std::string getName()
	{
		return _name;
	}
};

