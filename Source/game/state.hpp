#ifndef GAME_EXECUTION_HPP
#define GAME_EXECUTION_HPP

#include <string>

#include <goap/plan.hpp>

#include "agent.hpp"

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
        bool RunStep(GOAP::Action step) {
            if(this->lastAction == step.ID) 
                this->times++;
            else {
                this->lastAction = step.ID;
                this->times = 1;
            }

            std::cout << "mainloop: Action: " << step.ID << ". ";

            // We only ever execute the first step of a plan.
            if(step.ID == "move") { 
                this->movementProvider(step.GetX(), step.GetY());

                float* position = this->locationProvider();
                this->agent.SetX(position[0]);
                this->agent.SetY(position[1]);

                std::cout << "Agent at " << position[0] << ", " << position[1] << std::endl;

                if(this->agent.GetX() == step.GetX() && this->agent.GetY() == step.GetY()) 
                    return true;

            } else if(step.ID == "pickup") {
                std::cout << "Object picked up." << std::endl;
                return true;

            }

            return false;
        }
    };
}

#endif
