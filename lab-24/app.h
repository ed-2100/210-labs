// COMSC-210 | Lab 24 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#pragma once

#include <set>
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
    std::set<Goat> trip;
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
    // Displays a list of trip operations to the user.
    // and sets `state` to `MAIN_MENU_DECISION`.
    void main_menu();

    // The `main_menu_decision` state function.
    //
    // Selects the state based on user input.
    void main_menu_decision();

    // The `append` state function.
    //
    // Appends a goat to the trip.
    void append();

    // The `remove` state function.
    //
    // Removes a goat at a position in the trip
    // based on user input.
    void remove();

    // The `display` state function.
    //
    // Displays the current contents of the trip.
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
