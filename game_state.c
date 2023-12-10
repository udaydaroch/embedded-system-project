/**
 * @file game_state.c 
 * @author Uday Daroch, Toby Smillie
 * 
 * Description:
 * @brief Implmentation of game state management functions.
 * This file contains the implmeent of functions responsible for managing
 * different game states, including the menu state. it handles user input 
 * and state transitions wihtin the game. 
*/

#include "game_state.h"
#include "display_game.h"
#include "ball.h"
#include "navswitch.h"
#include <stdbool.h>

/**
 * handles user input to toggle between game menu options. It updates the display
 * to reflect the current menu state and returns whether the game should proceed to gameplay or
 * stay in the menu state.
 *
 * @param ball A pointer to the game ball, used to initialize its position.
 * @return True if the game should stay in the menu state, false if it should proceed to gameplay.
*/
bool game_state_menu(Ball_t* ball)
{
    // track the last menu state(sending/receiving)
    static bool lastState = true;
    // ensure intital menu display
    static bool firstTime = true;

    // update user inputs.
    navswitch_update();

    //Toggle menu state with navigation switch or for intial display and then update the display
    if(navswitch_push_event_p(NAVSWITCH_NORTH) || navswitch_push_event_p(NAVSWITCH_SOUTH) || firstTime) {
        lastState ^= true;
        display_game_server_receiver(lastState);
    }
    // start the game if navigation switch is pushed
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        display_game_clear();
        display_game_update();
        // initialise the ball-s position based on the menu state and either start sending or receiving
        if (lastState) {
            ball->x = SENDING_START_X;
        } else {
            ball->x = RECEIVING_START_X;
        }
        return false;
    }
    // mark intial display as complete and stay in the menu state ( return true)
    firstTime = false;
    display_game_update();
    return true;
}
