#pragma once
#include "SFML\System\Clock.hpp"

#define TIME 0

class StateMachine
{
private:
	sf::Clock _timeKeeper;

	bool _isTimeOn;

	float _currentGameTime;

public:
	//Initialize world state to the following:
	/*
	Time tracking is ON
	*/
	StateMachine();

	~StateMachine();

	void stateSettings(int identifier, bool value);

	void updateState();

	float getCurrentTime();
};

StateMachine::StateMachine()
{
	_isTimeOn = true;
}

StateMachine::~StateMachine()
{

}

void StateMachine::stateSettings(int identifier, bool value)
{
	switch (identifier)
	{
	case 0:
		_isTimeOn = value;
		break;
	default:
		break;
	}
}

void StateMachine::updateState()
{
	//TIME UPDATE
	if (_timeKeeper.getElapsedTime().asSeconds() > 600.0f)
		_timeKeeper.restart();
	_currentGameTime = _timeKeeper.getElapsedTime().asSeconds();
}

float StateMachine::getCurrentTime()
{
	if (_isTimeOn)
		return _currentGameTime;
	return -1;
}