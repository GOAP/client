#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

#include "goap/printable.hpp"
#include "goap/fact.hpp"
#include "goap/action.hpp"

namespace Planner {
    class Problem: public Printable {
        State state;
        std::map<std::string, Action> actions;
        Goal goal;

        bool satisfies(State state, Goal g) {
            for(auto it = g.begin(); it != g.end(); it++) {
                // Check if this fact is in the state
                for(auto its = state.begin(); its != state.end(); its++) {
                    if(its->name == it->name) {
                        assert(its->params.size() == it->params.size());

                        // If any of the arguments are different (and not floating), it doesn't satisfy the goal
                        for(int i = 0; i < its->params.size(); i++) {
                            if((its->params[i] != it->params[i]) && it->floating == false && its->floating == false)
                                return false;
                        }
                    }
                }
            }

            return true;
        }

        Action* choose_operator(Goal g) {
            // TODO: Add weighting/heuristics?
            for(auto it = this->actions.begin(); it != this->actions.end(); it++) {
                // Check if any of the postconditions in this actions are relevant to some predicate in g
                for(auto itp = it->second.postconditions.begin(); itp != it->second.postconditions.end(); itp++) {
                    for(auto itg = g.begin(); itg != g.end(); itg++) {
                        if(itp->name == itg->name)
                            return &it->second;
                    }

                }
            }

            return NULL;
        }

        std::vector<Fact> update_state(State s, Plan p, GroundState ground) {
            for(auto it = p.begin(); it != p.end(); it++) {
                // First, find an action with the same name as this fact.
                auto act_it = this->actions.find((*it).name);

                // If no action with a matching name is found, ignore this step.
                if(act_it == this->actions.end())
                    continue;

                // Otherwise, apply it to the state.
                Action act = act_it->second;
                s = act.engage(s, ground);
            }

            return s;
        }

        std::vector<GroundState> generateGroundStates() {
            // FIX FIX FIX
            return {
                {{"from", "0 0"}, {"to", "250 50"}}
            };
        }

        Plan* solve_(State s, Goal g, int depth = 0) {
            std::string padding;
            Plan* p = new Plan;

            for(int i = 0; i < depth; i++) {
                padding += "  ";
            }

            std::cout << padding << "Subproblem state: " << std::endl;
            for(auto it = s.begin(); it != s.end(); it++) {
                std::cout << padding << " - ";
                it->print();
                std::cout << std::endl;
            }

            std::cout << padding << "Subgoal: " << std::endl;
            for(auto it = g.begin(); it != g.end(); it++) {
                std::cout << padding <<" - ";
                it->print();
                std::cout << std::endl;
            }

            while(true) {
                if(satisfies(s, g)) {
                    std::cout << padding << ">> SOLUTION << state: " << std::endl;
                    for(auto it = s.begin(); it != s.end(); it++) {
                        std::cout << padding << " - ";
                        it->print();
                        std::cout << std::endl;
                    }

                    // Mission accomplished! \o/
                    return p;
                }

                // Choose the cheapest operator relevant to this subgoal
                Action* candidate = choose_operator(g);
                if(candidate == NULL)
                    return NULL;

                // Generate possible ground states
                std::vector<GroundState> grounds = this->generateGroundStates();
                auto ground = grounds.end();
                Plan* subplan = NULL;
                bool found = false;

                for(auto it = grounds.begin(); it != grounds.end(); it++) {
                    ground = it;

                    // Get a plan that solves candidate's preconditions with the current ground candidate
                    subplan = this->solve_(s, candidate->preconditions, depth + 1);
                    if(subplan == NULL)
                        continue;

                    found = true;

                    // Run all actions in the subplan and update s
                    s = update_state(s, *subplan, *ground);
                    // Run the current action and modify the state
                    s = candidate->engage(s, *ground);
                }

                if(found == false) // None of the ground states are valid: no solution
                    return NULL;

                // Add all steps in subplan to the Master Plan
                for(auto it = subplan->begin(); it != subplan->end(); it++) {
                    p->push_back(*it);
                }

                // Add the current action to the plan, matching params to ground.
                std::vector<std::string> arguments = matchGrounds(candidate->params, *ground);
                p->push_back(Step(candidate->name, arguments)); // Housekeeping
            }
        }

    public:
        Problem(std::vector<Action> _actions, State _state, Goal _goal):
            state(_state), goal(_goal) {

            for(auto it = _actions.begin(); it != _actions.end(); it++) {
                this->actions.insert(std::pair<std::string, Action>(it->name, *it)); // Thanks C++
            }
        };

        void print() {
            std::cout << "Available actions: " << std::endl;
            for(auto it = this->actions.begin(); it != this->actions.end(); it++) {
                std::cout << " - ";
                it->second.print();
            }
            std::cout << std::endl;

            std::cout << "Problem state: " << std::endl;
            for(auto it = this->state.begin(); it != this->state.end(); it++) {
                std::cout << " - ";
                it->print();
            }
            std::cout << std::endl;

            std::cout << "Goal: " << std::endl;
            for(auto it = this->goal.begin(); it != this->goal.end(); it++) {
                std::cout << " - ";
                it->print();
            }
            std::cout << std::endl;
        }

        Plan* solve() {
            return this->solve_(this->state, this->goal);
        }

    };
};