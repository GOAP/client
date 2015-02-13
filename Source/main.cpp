#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <functional>
#include "SfVectorMath.h"
#include "StaticEntity.h"
#include "Agent.h"
#include "Steering.h"
#include "StateMachine.h"

//MAP LOADER
#include "TmxLoader.h"

// GOAP
#include "goap/action.hpp"
#include "goap/plan.hpp"
#include "game/state.hpp"

TmxLoader loaderObject;

/*
GLOBAL CONTAINER HOLDING ALL STATIC ENTITIES
*/
std::vector<Entity*> staticEntities;
/*
Creates the aiAgent with a raious of 10 and initial position of x-10, y-10.
*/
Agent aiAgent(10, 10,500, 240, 0, 0);

/*	
Initializes the world with a default state.
*/
StateMachine worldState;

void movementProvider(float x, float y) {
    sf::Vector2f target(x, y);
    auto printable = aiAgent.steerAi.collisionAvoidTo(&target, staticEntities);
	if (printable.empty())
	{
		
	}
	else
	{
		for (int i = 0; i <= printable.size() - 1; ++i)
		{
			std::cout << printable[i]->getPosition().x << " , ";
			std::cout << printable[i]->getPosition().y << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
	}
	
}

float* locationProvider() {
    float* position = new float[2];
    position[0] = aiAgent.getPositionReference()->x;
    position[1] = aiAgent.getPositionReference()->y;

    return position;
}

int main(int argc, char* argv[]) {
    sf::RenderWindow App(sf::VideoMode(800, 600), "GOAP client");
	
	
	//========================================================================================
	sf::RectangleShape a(sf::Vector2f(32 * 15, 32 * 15));
	a.setFillColor(sf::Color::White);
	//======================================================================================
	
	
	/*
    FPS LIMITER
    */
    App.setFramerateLimit(60);
	

    //Seed random number generator.
    srand(time(NULL));

    // Initialise GOAP objects.
    GOAP::Plan plan;
    GOAP::Action move("move", "Moves the agent to a position.");
    GOAP::Action pickup("pickup", "Picks up object at current position.");

    Game::State state;
    state.movementProvider = movementProvider;
    state.locationProvider = locationProvider;

    // Prepare actions.
    move.To(600, 150);

    // Add actions to plan.
    plan.Add(move);
    plan.Add(pickup);

    // Print plan.
    std::cout << "<<<< PLAN >>>>" << std::endl;
    plan.Show();
	
	//Loads The Objects to static Entities;
	loaderObject.loadFile("MapDataComplete_v2\
						  .xml");
	staticEntities = *loaderObject.getStatics();

    // Main game loop.
    std::cout << "<<<< ENTERING MAIN LOOP >>>>" << std::endl;
    while (App.isOpen()) {
        sf::Event Event;

        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }
		
		App.draw(a);

		//UPDATE STATE NEEDS TO BE CALLED EVERY FRAME
		worldState.updateState();

		//FOR TESTING PURPOSES DISPLAYING FUNCTIONALITY OF GET TIME
		float a = worldState.getCurrentTime();
        
		if(plan.Length() != 0) {
            if(state.RunStep(plan[0])) {
                std::cout << "master: Action completed." << std::endl;
                plan.Pop();
            }
        }

        /*
        while (aiAgent.getPositionReference()->x != a.x && aiAgent.getPositionReference()->y != a.y)
        {
            std::vector<StaticEntity> detectionVectorsSource = aiAgent.steerAi.collisionAvoidTo(&a, staticEntities);
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
        }*/

        /*
        Post steer while loop draw. Used in the case when the agent reaches
        the final position.
        For loop draws all static entities.
        Additional RenderWindow::draw() with the aiAgent shape as an
        argument is called to draw the agent.
        */

        for (int i = 0; i <= staticEntities.size() - 1; ++i)
        {
            App.draw(staticEntities[i]->getSprite());
        }
        App.draw(*aiAgent.getShape());
        App.draw(*aiAgent.getDirectionShape());

        App.display();
        App.clear();
    }
}
