#include <SFML/Graphics.hpp>
#include <vector>


/*
Vector containers holding all objects.
Seperate lists for interactalbe and static objects
*/
std::vector<sf::Vector2f> staticPositions;
std::vector<sf::Vector2f> interactablePositions;

sf::Vector2f a(0, 0);
sf::CircleShape circle(40);


int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");



	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}

		circle.move(a);
		App.draw(circle);
		App.display();
	}
}
