#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
//#include 'Agent.h'

using namespace std;

class Moodlets
{
private:
	int _moodPositionX;
	int _moodPositionY;

	sf::Sprite _drawable;
	sf::Sprite* _bg;
	sf::Sprite _icons;
	sf::View* _viewReff;
public:
	
	Moodlets(){}
	Moodlets(int MoodPositionX, int MoodPositionY, sf::Sprite bg[3], sf::Sprite icons, sf::View* viewReff)
	{
		_moodPositionX = MoodPositionX;
		_moodPositionY = MoodPositionY;

		_bg = bg;
		_icons = icons;

		_viewReff = viewReff;
	};

	~Moodlets(){};

	void WeightHigh()
	{
		_drawable = *(_bg);
	}

	void WeightMed()
	{
		_drawable = *(_bg + 1);
	}

	void WeightLow()
	{
		_drawable = *(_bg + 2); 
	}

	sf::Sprite getBG()
	{
		_drawable.setPosition(_viewReff->getCenter() - sf::Vector2f(_moodPositionX, _moodPositionY));
		
		return _drawable;
	}
	
	sf::Sprite getIcon()
	{
		_icons.setPosition(_viewReff->getCenter() - sf::Vector2f(_moodPositionX, _moodPositionY));
		return _icons;
	}
};