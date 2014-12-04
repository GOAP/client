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

sf::Vector2f a(10,0);
sf::Vector2f b(10,0);


bool isTruefalse = true;

int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
		std::cout << angleBetweenVectors(a, b) << std::endl;

		if (isTruefalse)
		{
			b = rotateCounterClockwise(b, -90);
			isTruefalse = false;
		}

		std::cout << angleBetweenVectors(a,b) << std::endl;
		sf::RectangleShape line(a);
		sf::RectangleShape lineTwo(b);

		App.draw(line);
		App.draw(lineTwo);
		App.display();
	}
}
