/**
 * @file paddle.c 
 * @author Uday Daroch, Toby Smillie
 * 
 * Description: 
 * @brief Paddle management functions for the Pong game. 
 * This file contains the functions related to the paddle in the Pong game. 
 * It provides the neccesary code to control and display the paddle on the LED Screen
*/

#include "paddle.h"
#include "display_game.h"
#include "navswitch.h"

/**
 * updates the paddle's position based on user inputes (North and South navigation switch).
 * 
 * @param paddle A pointer to the Paddle_t struct representing the paddle
*/
void paddle_display(Paddle_t* paddle)
{
    navswitch_update(); // updates the navswitch
    
    /**
     * the following two if statements essentially sees if the north/ south is pushed
     * , updates the paddle's position relative to that and makes sure 
     * that the position is not exceeding the limit set for each direction. 
    */ 

    if(navswitch_push_event_p(NAVSWITCH_NORTH) && paddle->pos > PADDLE_LOWER_LIMIT) {
        paddle->pos--;
    }
    if(navswitch_push_event_p(NAVSWITCH_SOUTH) && paddle->pos < PADDLE_UPPER_LIMIT) {
        paddle->pos++;
    }

    // updates thhe specfied columns and displays the paddles on the LED screen.
    display_game_column((PADDLE_INITIAL << (paddle->pos - PADDLE_SHIFT_OFFSET)), PADDLE_COLUMN, true);
}

/**
 * Turns off the paddle's display on the LED screen.
 * 
 * @param paddle pointer to the Paddle_t struct representing the paddle. 
*/
void paddle_off(Paddle_t* paddle)
{
    display_game_column((PADDLE_INITIAL << (paddle->pos - PADDLE_SHIFT_OFFSET)), PADDLE_COLUMN, false);
}