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
#include "goap/fact.hpp"
#include "goap/action.hpp"
#include "goap/problem.hpp"
#include "game/state.hpp"

TmxLoader loaderObject;

/*
GLOBAL CONTAINER HOLDING ALL STATIC ENTITIES
*/
std::vector<Entity*> allTempEntities;
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
    auto printable = aiAgent.steerAi.collisionAvoidTo(&target, allTempEntities);
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
	
	//Loads The Objects to static Entities;
	loaderObject.loadFile("MapDataComplete_v2.xml");
	allTempEntities = *loaderObject.getAllEntities();
	worldState = StateMachine(allTempEntities);

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
    Planner::Action move("move",
        {"from", "to"},
        {Planner::Fact("at", {"from"}, true)},
        {Planner::Fact("!at", {"from"}, true), Planner::Fact("at", {"to"}, true)}
    );

    Planner::State initialState({
        Planner::Fact("at", {"0 0"}),
        Planner::Fact("health", {"70"}),
    });

	Planner::State pState;
	//==============================================================//
	for (int i = 0; i <= worldState.getInteractables().size() - 1; ++i)
	{
		pState.push_back(
			Planner::Fact(worldState.getInteractables()[i]->getName() + "_" + "at", { std::to_string(worldState.getInteractables()[i]->getPosition().x) + " " + std::to_string(worldState.getInteractables()[i]->getPosition().y)})
		);
	}
	//====================================================================//

    Planner::Goal goal({
        Planner::Fact("at", {"250 50"})
    });

    Planner::Problem p({ move }, initialState, goal);
    p.print();

    Planner::Plan* solution = p.solve();

    Game::State state;
    state.movementProvider = movementProvider;
    state.locationProvider = locationProvider;

    // Print plan.
    std::cout << "<<<< PLAN >>>>" << std::endl;
    std::cout << "----" << std::endl << "Solution: " << std::endl;
    for(auto it = solution->begin(); it != solution->end(); it++) {
        std::cout << " - ";
        it->print();
    }

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
        
		if(solution->size() != 0) {
            if(state.RunStep(*solution->begin())) {
                std::cout << "master: Action completed." << std::endl;
                solution->erase(solution->begin());
            }
        }

		for (int i = 0; i <= worldState.getAllEntities().size() - 1; ++i)
        {
			App.draw(worldState.getAllEntities()[i]->getSprite());
        }
        App.draw(*aiAgent.getShape());
        App.draw(*aiAgent.getDirectionShape());

        App.display();
        App.clear();
    }
}
