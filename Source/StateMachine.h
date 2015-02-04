#pragma once
#include <SFML/System/Clock.hpp>

#define TIME 0

#define THIRST_LOSS 0.8
#define HUNGER_LOSS 0.4
#define ENERGY_LOSS 0.23

#define ENERGY_GAIN 0.5

class StateMachine
{
private:
	//World Clock
	//600sec clock
	sf::Clock _timeKeeper;
	//1sec clock
	sf::Clock _depreciater;

	float _currentGameTime;
	
	//STATE BOOLEANS
	bool _isTimeOn;
	
	bool _isSleeping;
	
	bool _isThirsty;
	bool _isHungry;

	//FLOATS
	float _hunger;
	float _energy;
	float _thirst;

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

	void fillHunger(float ammount);
	void fillThirst(float ammount);
};

StateMachine::StateMachine()
{
	_isTimeOn = true;

	_hunger = 100;
	_energy = 100;
	_thirst = 100;
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

	if (_depreciater.getElapsedTime().asSeconds() > 1.0f)
	{
		if (!_isSleeping)
		{
			if (_energy >= ENERGY_LOSS)
				_energy -= ENERGY_LOSS;
			if (_hunger >= HUNGER_LOSS)
				_hunger -= HUNGER_LOSS;
			if (_thirst >= THIRST_LOSS)
				_thirst -= THIRST_LOSS;
		}
		else if (_isSleeping)
		{
			if (_energy >= 100)
				_energy += ENERGY_GAIN;

			if (_hunger >= HUNGER_LOSS/2)
				_hunger -= HUNGER_LOSS/2;

			if (_thirst >= THIRST_LOSS/2)
				_thirst -= THIRST_LOSS/2;
		}



		_depreciater.restart();
	}
}

float StateMachine::getCurrentTime()
{
	if (_isTimeOn)
		return _currentGameTime;
	return -1;
}

void StateMachine::fillHunger(float ammount)
{
	_hunger += ammount;
}
void StateMachine::fillThirst(float ammount)
{
	_thirst += ammount;
}
