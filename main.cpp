#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "VS2013-Test\Testsfml\Testsfml\SfVectorMath.h"


/*
Vector containers holding all objects.
Seperate lists for interactalbe and static objects
*/
std::vector<sf::Vector2f> staticPositions;
std::vector<sf::Vector2f> interactablePositions;

sf::Vector2f a(1,0);
sf::Vector2f b(1,1);


bool isTruefalse = true;

int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
	
		
		App.display();
	}
}
