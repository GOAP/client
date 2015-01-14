#ifndef GOAP_ACTION_HPP
#define GOAP_ACTION_HPP

#include <iostream>

namespace GOAP {
    class Action {
        double coords[2];

    public:
        std::string ID;
        std::string Description;

        Action(std::string id, std::string description): ID(id), Description(description) {
            coords[0] = -1;
            coords[1] = -1; // -1 = unused
        }

        void To(double x, double y) {
            this->coords[0] = x;
            this->coords[1] = y;
        }

        void Show() {
            std::cout << this->ID;

            if(this->coords[0] != -1 && this->coords[1] != -1) {
                std::cout << ": " << this->coords[0] << "," << this->coords[1];
            }

            std::cout << std::endl;
        }

        double GetX() {
            return this->coords[0];
        }

        double GetY() {
            return this->coords[1];
        }
    };
}

#endif
