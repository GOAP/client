# AI Design Documentation

We will be using STRIPS as the Artificial Intelligence framework for the project. This involves three parts: the planner, the action structure, and the world state representation.

## World state representation

Common data format to represent states (which can be goal states, agent states, world states...). A state is essentially a set of assumptions about the world. The tricky part is going to be figuring out how to represent these assumptions in code. Assumptions about an example world:

* Temperature is 21 degC.
* Apple is at coordinates (17, 42).
* Wood is at coordinates (5, 13).

## Planner

The piece of code that calculates the most efficient plan given the following parameters:

* Goal state
* Current world state
* Agent state
* Set of actions

It returns a plan, which is in the form of a list (in which the order matters). This list contains the actions that should be executed to transform the current world state into the goal world state. In practice, the game will only execute the first step in the plan - it will recalculate the plan after executing each action. However the planner will return the full plan regardless, as it needs to compute it in its entirety anyway, so we might as well return it. We could show the full plan in the UI to give insight into the AI's state, but this is unnecessary for the completion of the primary project goals.

Effectively, this means that if we execute an action, and once that's finished we calculate a new plan from the new world state to the same goal state, the new plan will be like the old one, except that the first action in the new plan is the second one in the original plan. The specific mechanism used to implement this is discussed below.

## Action structure

STRIPS actions call for several required fields. These are:

[[ TODO(jdiez): Reread STRIPS paper to make sure this is accurate ]]

* **Pre-conditions**: a set of assumptions that must be true about the world state before this action can be executed.
* **Post-conditions**: a set of assumptions that will be added to the world state after the execution of this action is complete.
* (something else I forgot)

For the purpose of managing time, we will also implement a boolean function that given a world state returns true if the action is satisfied, false otherwise. If the action is not complete, the game will call a function that steps the world one discrete step in the direction of the completion of this action.

# Implementation

This section describes how to make the Artificial Intelligence work within the main loop of the game without blocking (that is, how to discretise steps in the completion of every action.)

The way we will schedule actions is by maintaining a game-state-wide pointer to the current action. (Note, this does not imply a global variable, it simply means a field in the internal game state (which is diferent from the world state)).

The main loop of the game will contain several bookkeeping function calls such as update sprite animation state, draw to framebuffer, swap, etc. We will not discuss them as they're outside the scope of this document.
However, in the main loop, we'll also run a small 2-state machine (unofficially dubbed *the thingymachine*) that will:

* If there **is** a scheduled action, call the boolean function that checks if the action is complete.
    * If the action is **not complete**, we call a function that will step the agent towards completing the action. (For example, if the action is `move`, the checker function will return false if the agent is not at the target position, and the step function will move it one discrete step towards the target).
    * If the action is **complete**, we unschedule the action. (i.e, set the `action` pointer to `NULL`).
* If there is **no** scheduled action, we call the planner module and schedule the first action in the plan it returns.
