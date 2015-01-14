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

// GOAP
#include "goap/action.hpp"
#include "goap/plan.hpp"
#include "game/state.hpp"

/*
GLOBAL CONTAINER HOLDING ALL STATIC ENTITIES
*/
std::vector<StaticEntity> staticEntities;
/*
Creates the aiAgent witha raious of 10 and initial position of x-10, y-10.
*/
Agent aiAgent(10, 10,500, 240, 0, 0);

void movementProvider(float x, float y) {
    sf::Vector2f target(x, y);
    aiAgent.steerAi.collisionAvoidTo(&target, staticEntities);
}

float* locationProvider() {
    float* position = new float[2];
    position[0] = aiAgent.getPositionReference()->x;
    position[1] = aiAgent.getPositionReference()->y;

    return position;
}

int main(int argc, char* argv[]) {
    sf::RenderWindow App(sf::VideoMode(800, 600), "GOAP client");
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
    move.To(700, 10);

    // Add actions to plan.
    plan.Add(move);
    plan.Add(pickup);

    // Print plan.
    std::cout << "<<<< PLAN >>>>" << std::endl;
    plan.Show();

    /*
    For loop populates world with static entities.
    */
    for (int i = 0; i <= 15; ++i)
    {
        staticEntities.push_back(StaticEntity(20, rand() % 600, rand() % 800));
    }

    // Main game loop.
    std::cout << "<<<< ENTERING MAIN LOOP >>>>" << std::endl;
    while (App.isOpen()) {
        sf::Event Event;

        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

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
            App.draw(staticEntities[i].getShape());
        }
        App.draw(*aiAgent.getShape());

        App.display();
        App.clear();
    }
}
