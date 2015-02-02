#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>


class Static : private Entity
{
private:
	/*ADD INTERACTABLE SPECIFICSS*/
public:

	Static(int id, float x, float y)
	{
		_position.x = x;
		_position.y = y;

		/*DO IF STATEMENT FOR TYPE OF INTERACTABLE*/
		//if (id == )
	}

	~Static(){}
};

