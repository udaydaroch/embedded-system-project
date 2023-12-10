/**
 * @file paddle.h
 * @author Uday Daroch, Toby Smillie
 * 
 * Description: 
 * @brief Declaration for manging the paddle in a pong game.
 * module configures movement and direction of the paddle
 * and displays the paddle on the LED Screen. 
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <stdint.h>

// Constants for the paddle module 
#define PADDLE_BEGIN 3          // Initial position of the paddle
#define PADDLE_COLUMN 4         // Column on the LED screen where the paddle is displayed
#define PADDLE_INITIAL 7        // Initial pattern for displaying the paddle
#define PADDLE_UPPER_LIMIT 5    // Upper limit for the paddle's position
#define PADDLE_LOWER_LIMIT 0    // Lower limit for the paddle's position
#define PADDLE_SHIFT_OFFSET 1   // Offset used for shifting the paddle display pattern


/**
 * struct representing the paddle 
 * consist of a integer assigned to the position of the paddle. 
*/
typedef struct {
    uint8_t pos; 
} Paddle_t;

/**
 * Updates the paddle's position based on user input (North and South navigation switch).
 * @param paddle A pointer to the Paddle_t struct representing the paddle.
*/
void paddle_display(Paddle_t*);

/**
 * Turns off the paddle's display on the LED screen.
 * @param paddle A pointer to the Paddle_t struct representing the paddle.
*/
void paddle_off(Paddle_t*);

#endif