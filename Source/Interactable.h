#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>

class Interactable : public Entity
{
private:
	/*ADD INTERACTABLE SPECIFICSS*/
public:

	Interactable(int id, float x, float y, sf::Sprite sprite, std::string name)
	{
		_name = name;
		_position.x = x;
		_position.y = y;

		_sprite = sprite;

		_id = id;
	}

	~Interactable(){}
};

