#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>


class Static : public Entity
{
private:
	/*ADD INTERACTABLE SPECIFICSS*/
public:

	Static(int id, float x, float y, sf::Sprite sprite)
	{
		_sprite = sprite;
		_position.x = x;
		_position.y = y;

		/*DO IF STATEMENT FOR TYPE OF INTERACTABLE*/
		//if (id == )
	}

	~Static(){}
};

