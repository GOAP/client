#ifndef GAME_EXECUTION_HPP
#define GAME_EXECUTION_HPP

#include <string>
#include <sstream>

#include "goap/fact.hpp"
#include "goap/problem.hpp"

#include "agent.hpp"

std::vector<double> stringToDouble(std::string coords) {
    std::stringstream ss(coords);
    std::vector<double> result;
    double value;
    while(ss >> value) 
        result.push_back(value);

    return result;
}

namespace Game {
    class State {
        Agent agent;

        // TODO: Remove stub
        double times;
        std::string lastAction;
        // end stub

    public:
        void (*movementProvider)(float x, float y);
        float* (*locationProvider)();

        State() {
            this->times = 0;
            this->lastAction = "none";
        }

        // True if step is completed, false otherwise
        bool RunStep(Planner::Step step) {
            if(this->lastAction == step.name)
                this->times++;
            else {
                this->lastAction = step.name;
                this->times = 1;
            }

            std::cout << "mainloop: Action: " << step.name << ". ";

            // We only ever execute the first step of a plan.
            if(step.name == "move") {
                // Convert string coordinates into `double` coordinates.
                auto coords = stringToDouble(step.params[1]);

                this->movementProvider(coords[0], coords[1]);

                float* position = this->locationProvider();
                this->agent.SetX(position[0]);
                this->agent.SetY(position[1]);

                std::cout << "Agent at " << position[0] << ", " << position[1] << std::endl;

                float diffX = this->agent.GetX() - coords[0];
                float diffY = this->agent.GetY() - coords[1];

                if(diffX > -2 && diffX < 2 && diffY > -2 && diffY < 2)
                    return true;

            } else if(step.name == "pickup") {
                std::cout << "Picked up item." << std::endl;
                return true;
            }

            return false;
        }
    };
}

#endif
