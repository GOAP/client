#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <functional>
#include "VS2013-Test\Testsfml\Testsfml\SfVectorMath.h"
#include "VS2013-Test\Testsfml\Testsfml\StaticEntity.h"
#include "VS2013-Test\Testsfml\Testsfml\Agent.h"
#include "VS2013-Test\Testsfml\Testsfml\Steering.h"





/*
Vector containers holding all positions and all static entities.
Seperate lists for interactalbe and static objects
*/
std::vector<StaticEntity> staticEntities;




int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

	Agent aiAgent(10, 10, 10);
	sf::Vector2f a(700, 500);
		
	//Seed random number generator.
	srand(time(NULL));

	/*
	For loop populates world with static entities.
	*/
	for (int i = 0; i <= 20; ++i)
	{
		staticEntities.push_back(StaticEntity(20, rand() % 600, rand() % 800));
	}
	sf::Thread steerThread(std::bind(&steerTo, aiAgent.getPositionReference(), &a, staticEntities));
	

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
		/*
		For loop draws all static entities.
		*/
		for (int i = 0; i <= staticEntities.size() - 1; ++i)
		{
			App.draw(staticEntities[i].getShape());
		}
		App.draw(aiAgent.getShape());
		
		steerThread.launch();
			
		while (aiAgent.getPositionReference()->x != a.x && aiAgent.getPositionReference()->y != a.y)
		{
			
			for(int i = 0; i <= staticEntities.size() - 1; ++i)
			{
				App.draw(staticEntities[i].getShape());
				
			}
			App.draw(aiAgent.getShape());
			
			

			std::cout << aiAgent.getPositionReference()->x << std::endl;
			std::cout << aiAgent.getPositionReference()->y << std::endl;
			App.display();
			App.clear();
		}
		steerThread.terminate();
		
	}
}
