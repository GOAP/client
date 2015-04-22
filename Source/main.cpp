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
#include "Moodlets.h"

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

Entity* targetEntity = NULL;

/*
   Creates the aiAgent with a raious of 10 and initial position of x-10, y-10.
   */
Agent aiAgent(10, 0, 0, 240, 0, 0);
/*	
    Initializes the world with a default state.
    */
StateMachine worldState;

Moodlets energy;
Moodlets thirst;
Moodlets hunger;
Moodlets warmth;

std::vector< sf::String > plan;

//MAKE SURE MESSAGE IS 29 CHARACTERS OR AFTER THE 29th ADD \n ESCAPE CHARACTER FOR NEW LINE.
void addMessage(string text)
{
    plan.push_back(sf::String(text));
}

void removeLatest()
{
    plan.erase(plan.begin());
    plan.shrink_to_fit();
}

void printPlan();

void movementProvider(float x, float y) {
    sf::Vector2f target(x, y);


    if (targetEntity != NULL)
        aiAgent.steerAi.collisionAvoidTo(&target, allTempEntities, targetEntity);
    else
        aiAgent.steerAi.collisionAvoidTo(&target, allTempEntities);

    /*
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
       }*/

}

float* locationProvider() {
    float* position = new float[2];
    position[0] = aiAgent.getPositionReference()->x;
    position[1] = aiAgent.getPositionReference()->y;

    return position;
}

bool isCenterMatch = true;
sf::Clock cameraClock;
sf::Vector2f cameraLookProvider(sf::Vector2f agentPos, sf::View view);
bool isBorderHit(sf::Vector2f agentPos, sf::View view);
void drop(sf::Sprite toDrop);


int main(int argc, char* argv[]) {
    sf::RenderWindow App(sf::VideoMode(800, 600), "GOAP client");
    //create agent view and define size and centre
    sf::View agentView;
    sf::Vector2f* agentPosition = aiAgent.getPositionReference();
    agentView.setCenter(*agentPosition);
    double winWidth, winHeight;
    winWidth = 1500;
    winHeight = 750;
    agentView.setSize(winWidth, winHeight); //600, 300
    App.setView(agentView);

    //Loads The Objects to static Entities;
    sf::Sprite* terrains = loaderObject.loadFile("MapDataComplete_v2.xml");
    allTempEntities = *loaderObject.getAllEntities();
    vector< vector<int> > tiles = loaderObject.getTiles();
    worldState = StateMachine(allTempEntities);
    float aix = aiAgent.getPositionReference()->x;
    float aiy = aiAgent.getPositionReference()->y;
    energy = Moodlets(aix - 200, aiy - 200, loaderObject.getBgs(), loaderObject.getIcons()[0], &agentView);
    thirst = Moodlets(aix - 50, aiy - 200, loaderObject.getBgs(), loaderObject.getIcons()[1], &agentView);
    hunger = Moodlets(aix + 100, aiy - 200, loaderObject.getBgs(), loaderObject.getIcons()[2], &agentView);
    warmth = Moodlets(aix + 250, aiy - 200, loaderObject.getBgs(), loaderObject.getIcons()[3], &agentView);
    //========================================================================================
    sf::RectangleShape a(sf::Vector2f(32 * 100, 32 * 100));
    a.setFillColor(sf::Color::Green);
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

    Planner::Action pickup("pickup",
            {"position"},
            {Planner::Fact("at", {"position"}, true), Planner::Fact("wood_at", {"position"}, true)},
            {Planner::Fact("!wood_at", {"position"}, true), Planner::Fact("have_object", {"wood"}, false)}
            );

    Planner::State initialState({
            //Planner::Fact("health", {"70"}),
            Planner::Fact("at", { std::to_string((int) aiAgent.getPositionReference()->x) + " " + std::to_string((int) aiAgent.getPositionReference()->y) }),
            Planner::Fact("wood_at", {"1792 576"})
            });

    Planner::Goal goal({
            Planner::Fact("have_object", {"wood"})
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

    Planner::Problem p({ move, pickup }, initialState, goal);
    p.print();

    Planner::Plan* solution = p.solve();

    Game::State state;
    state.movementProvider = movementProvider;
    state.locationProvider = locationProvider;

    solution->push_back(Planner::Step("move", { "_ _", "300 300" }, false));
    solution->push_back(Planner::Step("drop", { "bed" }, false));

    // Print plan.
    std::cout << "<<<< PLAN >>>>" << std::endl;
    std::cout << "----" << std::endl << "Solution: " << std::endl;
    for(auto it = solution->begin(); it != solution->end(); it++) {
        std::string step = "- " + it->name + "(";
        for (auto itp = it->params.begin(); itp != it->params.end(); itp++) {
            step += *itp;
            if (itp != it->params.end() - 1)
                step += ", ";
        }
        step += ")";

        std::cout << step << std::endl;
        addMessage(step);
    }



    // Main game loop.
    std::cout << "<<<< ENTERING MAIN LOOP >>>>" << std::endl;
    while (App.isOpen()) {
        sf::Event Event;

        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        for (int i = 0; i < 32; ++i)
        {
            for (int j = 0; j < 32; ++j)
            {
                (terrains + tiles[i][j])->setPosition(sf::Vector2f(64 * i, 64 * j));
                App.draw(*(terrains + tiles[i][j]));
            }
        }

        //UPDATE STATE NEEDS TO BE CALLED EVERY FRAME
        worldState.updateState();

        //FOR TESTING PURPOSES DISPLAYING FUNCTIONALITY OF GET TIME
        float a = worldState.getCurrentTime();

        if(solution->size() != 0) {
            auto currentStep = *solution->begin();
            bool actionCompleted = false;

            if (currentStep.name == "move") {
                auto avoidCoords = currentStep.params[1];
                auto vectorOfDoubles = stringToDouble(avoidCoords);
                sf::Vector2f realCoords(vectorOfDoubles[0], vectorOfDoubles[1]);
                targetEntity = worldState.find(realCoords);
            }
            else if (currentStep.name == "pickup") {
                worldState.addToInventory((Interactable *) targetEntity);
            }
            else if (currentStep.name == "drop") {
                auto droppables = loaderObject.getDroppable(); 
                int idx = currentStep.params[0] == "bed" ? 1 : 0;
                auto sprite = droppables[idx];

                drop(sprite);
                actionCompleted = true;
            }
            if(state.RunStep(currentStep) || actionCompleted) {
                std::cout << "master: Action completed." << std::endl;
                solution->erase(solution->begin());
            }
        }


        for (int i = 0; i <= worldState.getAllEntities().size() - 1; ++i)
        {
            App.draw(worldState.getAllEntities()[i]->getSprite());
        }
        //define view centre
        agentView.setCenter(cameraLookProvider(*agentPosition, agentView));
        App.setView(agentView);

        App.draw(*aiAgent.getShape());
        App.draw(*aiAgent.getDirectionShape());

        /*====================================================*/

        sf::RectangleShape InterfaceBox(sf::Vector2f(650, 180));
        InterfaceBox.setPosition(agentView.getCenter().x - 275, agentView.getCenter().y + 185);
        InterfaceBox.setFillColor(sf::Color(0, 0, 255));

        InterfaceBox.setOutlineThickness(6);
        InterfaceBox.setOutlineColor(sf::Color(0, 0, 0));

        App.draw(InterfaceBox);

        // Inventory Box
        InterfaceBox.setSize(sf::Vector2f(450, 180));
        InterfaceBox.setPosition(agentView.getCenter().x - 737, agentView.getCenter().y + 185);
        InterfaceBox.setFillColor(sf::Color(0, 0, 255));

        InterfaceBox.setOutlineThickness(6);
        InterfaceBox.setOutlineColor(sf::Color(0, 0, 0));

        App.draw(InterfaceBox);

        //Message Board
        InterfaceBox.setSize(sf::Vector2f(360, 500));
        InterfaceBox.setPosition(agentView.getCenter().x + 384, agentView.getCenter().y - 135);
        InterfaceBox.setFillColor(sf::Color(50, 50, 55));

        InterfaceBox.setOutlineThickness(6);
        InterfaceBox.setOutlineColor(sf::Color(0, 0, 0));

        App.draw(InterfaceBox);

        int planSize = plan.size();
        if (plan.empty())
        {
        }
        else if (planSize < 5)
        {
            for (int i = 0; i <= planSize - 1; ++i)
            {

                sf::Text toPrint;
                toPrint.setFont(*loaderObject.getFont());
                toPrint.setString(plan[i]);
                toPrint.setCharacterSize(20);
                toPrint.setPosition(sf::Vector2f(agentView.getCenter().x + 400, agentView.getCenter().y - 100 + i*toPrint.getCharacterSize()));
                toPrint.setColor(sf::Color::Red);

                App.draw(toPrint);
            }

        }
        if (!worldState.getInventory().empty())
        {
            for (int i = 0; i <= worldState.getInventory().size() - 1; ++i)
            {

                worldState.getInventory()[i]->setPosition(sf::Vector2f(agentView.getCenter().x - 700 + 70 * i, agentView.getCenter().y + 200 + 60 * (int) ((worldState.getInventory().size() - 1) / 5)));
                App.draw(worldState.getInventory()[i]->getSprite());
            }
        }

        energy.WeightHigh();
        App.draw(energy.getBG());
        App.draw(energy.getIcon());
        thirst.WeightHigh();
        App.draw(thirst.getBG());
        App.draw(thirst.getIcon());
        hunger.WeightHigh();
        App.draw(hunger.getBG());
        App.draw(hunger.getIcon());
        warmth.WeightHigh();
        App.draw(warmth.getBG());
        App.draw(warmth.getIcon());

        App.display();
        App.clear();
    }
}


sf::Vector2f cameraLookProvider(sf::Vector2f agentPos, sf::View view)
{
    if (isBorderHit(agentPos, view) && isCenterMatch)
    {
        isCenterMatch = false;
        cameraClock.restart();
    }
    if (agentPos == view.getCenter())
        isCenterMatch = true;


    if (!isCenterMatch)
    {
        sf::Vector2f directionVector = normalize((agentPos - view.getCenter()));
        double speed = 1.16;
        sf::Int32 time = cameraClock.getElapsedTime().asMilliseconds();
        if (time > 2600)
            time = 2600;
        return view.getCenter() + scalarMult(sin(time / 2600) * speed, directionVector);
    }

}

bool isBorderHit(sf::Vector2f agentPos, sf::View view)
{
    double centerX = view.getCenter().x;
    double centerY = view.getCenter().y;

    double agentX = agentPos.x - centerX;
    double agentY = agentPos.y - centerY;
    double boxSize = 250;

    if (agentX > centerX + boxSize || agentX < centerX + boxSize ||
            +agentY > centerY + boxSize || agentY < centerY - boxSize)
        return true;
    else
    {
        return false;
    }
}

void drop(sf::Sprite toDrop)
{
    Static* temp = new Static(400, aiAgent.getPositionReference()->x, aiAgent.getPositionReference()->y, toDrop);
    worldState.addEntity(temp);
}
