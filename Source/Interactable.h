#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>


class Interactable : public Entity
{
private:
	/*ADD INTERACTABLE SPECIFICSS*/
public:

	Interactable(int id, float x, float y)
	{
		_position.x = x;
		_position.y = y;

		/*DO IF STATEMENT FOR TYPE OF INTERACTABLE*/
		//if (id == )
	}

	~Interactable(){}
};

