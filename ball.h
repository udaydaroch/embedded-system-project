/**
 * @file ball.h
 * @author Uday Daroch, Toby Smillie
 *
 * Description: 
 * @brief Declarations for managing the ball in a pong game. 
 * This header file contains declarations for managing the ball's position, direction,
 * and interactions within a Pong-like game. It defines data structures and function
 * prototypes to facilitate the gameplay mechanics associated with the ball. 
 */

#ifndef BALL_H
#define BALL_H

#include "paddle.h"
#include <stdint.h>
#include <stdbool.h>

// All the constants used for the ball module

#define BALL_ORIGIN 0         // The origin position for the ball.
#define BALL_RECEIVE_STATE -1 // The state when the ball is received from another player.
#define WALL_UPPER_LIMIT 6    // The upper limit of the game wall.
#define WALL_LOWER_LIMIT 0    // The lower limit of the game wall.
#define BALL_X_MAX 3          // The maximum x-coordinate for the ball.
#define PADDLE_EDGE 2         // The edge position of the paddle.
#define PADDLE_SIDE 1         // The side position of the paddle.
#define BALL_UPDATE_RATE 50   // The rate at which the ball's position is updated.
#define BALL_UPDATE_INITIAL 0 // The initial value for the ball update counter.

//Enum for all possible game outcomes.
typedef enum {
    LOSER,
    WINNER,
    PLAYING
} Outcome_t;

//Enum for all possible ball movement directions
typedef enum {
    BALLUP,
    BALLHORI,
    BALLDOWN
} BallDir_t;

//struct to represent the ball
typedef struct {
    int8_t x;
    uint8_t y;
    bool dx;
    BallDir_t dy;
} Ball_t;

//Display the ball on the screen
void ball_display(Ball_t*, Paddle_t*, Outcome_t*);

//Turn off the display of the ball
void ball_off(Ball_t*);

#endif