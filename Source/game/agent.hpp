#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

namespace Game {
    class Agent {
        double position[2];

    public:
        Agent() {
            this->position[0] = 0;
            this->position[1] = 0;
        }

        void SetX(double x) {
            this->position[0] = x;
        }

        void SetY(double y) {
            this->position[1] = y;
        }

        double GetX() {
            return this->position[0];
        }

        double GetY() {
            return this->position[1];
        }
    };
}

#endif
