#ifndef GOAP_PLAN_HPP
#define GOAP_PLAN_HPP

#include <vector>
#include <iostream>

#include "action.hpp"

namespace GOAP {
    class Plan {
        std::vector<Action> steps;

    public:
        Plan() {}

        void Add(Action action) {
            this->steps.push_back(action);
        }

        void Show() {
            int i = 1;
            for(auto it = this->steps.begin(); it != this->steps.end(); it++) {
                std::cout << "Step " << i++ << ": ";
                (*it).Show();
            }
        }

        Action operator[](int x) {
            return this->steps[x];
        }

        int Length() {
            return this->steps.size();
        }

        void Pop() {
            this->steps.erase(this->steps.begin());
        }
    };
}

#endif
