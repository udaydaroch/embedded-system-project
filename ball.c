/**
 * @file ball.c
 * @author Uday Daroch, Toby Smillie
 * 
 * Description: 
 *  @brief Implementation of the ball mechanics in the Pong game.
 * This file contains the implementation of the ball's movement, collision detection, and display
 * in the ping pong game. It defines functions to update the ball's position, display it on the screen,
 * and control its behavior when interacting with the paddle and game boundaries. This module is
 * integral to the gameplay mechanics of the Pong-like game.
*/


#include "ball.h"
#include "display_game.h"
#include "paddle.h"
#include "communication.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * Updates the position of the ball based on its direction (dy) and
 * direction flag (dx). It also handles collision detection with walls and the paddle, setting the outcome
 * accordingly. If the ball reaches the opponent's side, it sends a PLAYING signal via infrared communication.
 * 
 * @param ball A pointer to a Ball_t object representing the ball's state.
 * @param paddle A pointer to a Paddle_t object representing the paddle's state.
 * @param outcome A pointer to an Outcome_t variable representing the game's outcome (WINNER, LOSER, or PLAYING).
 * @return true if the ball is still in play, false if the game has ended.
*/
bool ball_update (Ball_t* ball, Paddle_t* paddle, Outcome_t* outcome)
{


    // checks if the ball is at the origin and should send a PLAYING signal
    if (ball->x == BALL_ORIGIN && !ball->dx) {
        
        communication_send(ball, PLAYING);
        ball->dx = true;
        ball->x = BALL_RECEIVE_STATE;

    }
    // Check if the ball is within bounds or has received data via communcation(between devices)
    if (ball->x >= BALL_ORIGIN || (communication_receive(ball, outcome))) {
        if (*outcome == WINNER) {
            return false;
        }
 
        // replicating the ball bouncing off the walls based on current position and direction
        if (ball->y == WALL_UPPER_LIMIT) {
            ball->dy = BALLDOWN;
        } else if (ball->y == WALL_LOWER_LIMIT) {
            ball->dy = BALLUP;
        }
        // update the ball's position based on its direction
        switch (ball->dy)
        {
        case BALLUP:
            ball->y++;
            break;
        case BALLHORI:
            break;
        case BALLDOWN:
            ball->y--;
            break;
        }
        //Update the ball's x-coordinate and handle collisions with the paddle 
        if (ball->dx) {
            ball->x++;
        } else {
            ball->x--;
        }

        
        // Check for collisions with the paddle and determine the outcome
        if (ball->x == BALL_X_MAX) {
            ball->dx = false;
            // Check different paddle collision scenarios
            if ((ball->y == (paddle->pos + PADDLE_EDGE) && ball->dy == BALLDOWN) || (ball->y == paddle->pos + PADDLE_SIDE && !(ball->dy == BALLDOWN)) ||(ball->y == (paddle->pos - PADDLE_SIDE) && ball->dy == BALLUP)) {
                ball->dy = BALLUP;
            } else if (ball->y == paddle->pos) {
                ball->dy = BALLHORI;
            } else if ((ball->y == (paddle->pos - PADDLE_EDGE) && ball->dy == BALLUP) || (ball->y == paddle->pos - PADDLE_SIDE && !(ball->dy == BALLUP)) || (ball->y == (paddle->pos + PADDLE_SIDE) && ball->dy == BALLDOWN)) {
                ball->dy = BALLDOWN;
            } else {
                *outcome = LOSER;
                communication_send(ball, WINNER);
            }
        }
        return true; // Ball is still in play
    }
    return false; // No data received, game over
}

/**
 * Updates the game display to reflect the current position of the ball.
 * It controls the timing of the ball updates to match the game's refresh rate.
 *
 * @param ball A pointer to a Ball_t object representing the ball's state.
 * @param paddle A pointer to a Paddle_t object representing the paddle's state.
 * @param outcome A pointer to an Outcome_t variable representing the game's outcome (WINNER, LOSER, or PLAYING).
 * 
*/
void ball_display(Ball_t* ball, Paddle_t* paddle, Outcome_t* outcome) 
{
    static uint16_t ballUpdate = BALL_UPDATE_INITIAL;
    static bool isUpdate = false;

    // update ball position with timing control
    ballUpdate++;

    if (ballUpdate >= BALL_UPDATE_RATE) {
        
        ballUpdate = BALL_UPDATE_INITIAL;
        isUpdate =  ball_update(ball, paddle, outcome);
    }
    // Display the ball on the game screen if its in play
    if(isUpdate) {
        display_game_pixel(ball->y, ball->x, true);
    }
}   


/**
 * turns off the display of the ball at its current position on the game screen.
 * 
 * @param ball A pointer to a Ball_t object representing the ball's state.
*/

void ball_off(Ball_t* ball) {
    display_game_pixel(ball->y, ball->x, false);
}
