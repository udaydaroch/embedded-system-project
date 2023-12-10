/**
 * @file game_state.h
 * @author Uday Daroch, Toby Smillie
 * 
 * Description: 
 * @brief Declaration for managing game state transitions.
 * This header file contains declaration for managing transitions between
 * different game states, including menu and gamplay states.It provides 
 * function prototypes for handling user inputsand state changes within the same.
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ball.h"
#include <stdbool.h>

#define SENDING_START_X 0    // Constant for sending game state.
#define RECEIVING_START_X -1 // Constant for receiving game state.

// Function prototype for the menu state. 
bool game_state_menu(Ball_t*);

#endif