/**
 * Project: ENCE260 - group_511 (Pong game)
 * @file game.c
 * @author Uday Daroch, Toby Smillie

 * Description:
 * @brief The main driver code for a simple Pong game. 
 * This file sets up the game environment and 
 * intializes the necessary modules
 * and consists of: 
 *  - the main game loop that responds to player inputs,
 *  - updates game state,
 *  - and renders the paddle and ball on the LED Screen.
*/

#include "system.h"
#include "pacer.h"
#include "paddle.h"
#include "display_game.h"
#include "ball.h"
#include "game_state.h"
#include "communication.h"
#include "navswitch.h"

#define PACER_RATE 500 // the rate at which the pacer module operates


int main (void)
{
    /**
     * Initializes the system, pace_unit, game, navswitich, and communcation modules.
    */
    system_init (); 
    pacer_init(PACER_RATE);
    display_game_init();
    navswitch_init();  
    communication_init(); 

    // Initializes a paddle (struct) with its beginning position which is 3 
    Paddle_t paddle = {PADDLE_BEGIN};
    // Initializes a ball(struct) with its starting position and direction. 
    Ball_t ball = {BALL_ORIGIN, BALL_ORIGIN, true, BALLDOWN};
    // Intializes the outcome(enum) the current state of the game
    Outcome_t outcome = PLAYING;

    // variables to manage the states and transitions taking place in the game.
    bool lastBall = true; 
    bool gamePlay = false;
    bool gameStart = true;

   

    while (1)
    {
        pacer_wait(); // wait for the next pacer event.


        /** if the game is at the start state
         * - display the menu
         * - wait for the player to start
        */
        if (gameStart) {
            gameStart = game_state_menu(&ball); // Display menu and check if the game starts.
            gamePlay = !gameStart; // if game start, enable the gamePlay mode.
            
        } 

        // when the game is in play, update the paddle and ball's position
        if (gamePlay){
            if (lastBall) {
                /**
                 * - turn off the ball
                 * - displays paddle in its current position
                 * - toggles the state to indicate the balls's position was updated. 
                */
                ball_off(&ball);
                paddle_display(&paddle); 
                lastBall = false;
            } else {
                paddle_off(&paddle);
                ball_display(&ball, &paddle, &outcome); 
                lastBall = true; 
            }
        }

        // checks the game's outcome by checking the assigned enum value of Outcome. 
        if (outcome != PLAYING) {
            if (outcome == WINNER){
                display_game_set_win();// Display the winning (activates the blue light)
            }
            gamePlay = false;
        }

     
    }

}