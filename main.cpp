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
GLOBAL CONTAINER HOLDING ALL STATIC ENTITIES
*/
std::vector<StaticEntity> staticEntities;


int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");
	/*
	FPS LIMITER
	*/
	App.setFramerateLimit(60);

	/*
	Creates the aiAgent witha raious of 10 and initial position of x-10, y-10.
	*/
	Agent aiAgent(10, 10, 500, 240, 0, 0);

	/*
	Temporary target for the agent to try and get to.
	*/
	sf::Vector2f a(700, 10);
		
	//Seed random number generator.
	srand(time(NULL));

	/*
	For loop populates world with static entities.
	*/
	for (int i = 0; i <= 15; ++i)
	{
		staticEntities.push_back(StaticEntity(20, rand() % 600, rand() % 800));
	}

	/*
	Creates a new Thread object running the Steering::steerTo(); method.
	std::bind - C++ 11 feature. 
	"Ggenerates a forwarding call wrapper for 'steerTo'.
	Calling this wrapper is equivalent to invoking 'steerTo' with the arguments following it."
	REFERENCE: http://en.cppreference.com/w/cpp/utility/functional/bind
	
	In this case it is used to parse a multi argumented method to the Thread constructor.
	*/
	//sf::Thread steerThread(std::bind(&steerTo, aiAgent.getPositionReference(), &a, staticEntities));
	

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
		/*
		Launches the steerThread beggining the antigravity movement calculations.
		*/
		//steerThread.launch();

		
		                                                                                                                 
		/*
		While loop for testing and debugging.
		*/
		while (aiAgent.getPositionReference()->x != a.x && aiAgent.getPositionReference()->y != a.y)
		{
			std::vector<StaticEntity> detectionVectorsSource = aiAgent.steerAi.avoid(&a, staticEntities);
			if (detectionVectorsSource.size() == 0){}
			else
			{
				for (int i = 0; i <= detectionVectorsSource.size() - 1; ++i)
				{
					sf::RectangleShape detectedDot(sf::Vector2f(10, 10));
					detectedDot.setPosition(detectionVectorsSource[i].getPosition());
					detectedDot.setFillColor(sf::Color(0, 240, 0));
					App.draw(detectedDot);
				}
			}
			

			for(int i = 0; i <= staticEntities.size() - 1; ++i)
			{
				App.draw(staticEntities[i].getShape());
			}
			App.draw(*aiAgent.getShape());			
			App.draw(*aiAgent.getDirectionShape());

			App.display();
			App.clear();
		}

		/*
		Terminates the steerThread limiting the performance hit after the steering operation is finished.
		*/
		//steerThread.terminate();
		
		/*
		Post steer while loop draw. Used in the case when the agent reaches
		the final position.
		For loop draws all static entities.
		Additional RenderWindow::draw() with the aiAgent shape as an
		argument is called to draw the agent.
		*/
		for (int i = 0; i <= staticEntities.size() - 1; ++i)
		{
			App.draw(staticEntities[i].getShape());
		}
		App.draw(*aiAgent.getShape());

		App.display();
		App.clear();
	}
}
