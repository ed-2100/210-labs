#pragma once

#include <list>
#include <string>

#include "goat.h"

// The `MenuState` enum.
//
// Describes the different states in 
// the `Application` class's internal
// state machine.
enum MenuState {
    MAIN_MENU,
    MAIN_MENU_DECISION,
    APPEND,
    REMOVE,
    DISPLAY,
    EXIT,
};

// The `Application` class.
//
// Encloses the state-machine logic into a
// unified structure for this assignment.
class Application {
private:
    std::list<Goat> listy;
    std::vector<MenuState> state;

public:
    // The `run` function.
    //
    // Runs the `Application`.
    //
    // ### Returns:
    //
    // A signed integer value, where `0` means success.
    int run();

private:
    // The `main_menu` state function.
    //
    // Displays a list of list operations to the user.
    // and sets `state` to `MAIN_MENU_DECISION`.
    void main_menu();

    // The `main_menu_decision` state function.
    //
    // Selects the state based on user input.
    void main_menu_decision();

    // The `append` state function.
    //
    // Appends a goat to the list.
    void append();

    // The `remove` state function.
    //
    // Removes a goat at a position in the list
    // based on user input.
    void remove();

    // The `display` state function.
    //
    // Displays the current contents of the goat list.
    void display();

    // A small helper to parse integer inputs.
    //
    // ### Arguments
    //
    //  - `num`: Location to store the integer.
    //  - `input`: The input string to parse.
    //
    // ### Returns
    //
    // A bool, where true means the parse was
    // successful.
    static bool parse_int(
        int& num,
        const std::string& input
    );
};
