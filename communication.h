/**
 * @file communcation.h
 * @author Uday Daroch, Toby Smillie
 * 
 * Description:
 * @brief declerations of all the methods used in communation.c
 * Implementation of the communcation module for infrared data transmission
 * 
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "ball.h" // Include's the ball.h header to access the Ball_t and Outcome_t

// constants for the communcation module
#define BITSY_MAX 6       // max value for y-coordinate (used for encoding)
#define SHIFT_OUTCOME 5   // bit shift for encoding the outcome_t value
#define SHIFT_DY 3        // bit shift for encoding the ball->dy value
#define BITS_OUTCOME 0x60 // bit mask for extracting the outcome_t value
#define BITS_DY 0x18      // bit mask for extacting the ball->dy value
#define BITS_Y 0x07       // bit mask for extracting the Y-coordinate value

// Initializes the communciation module
void communication_init(void);

// Send Ball_t and Outcome_t data over infrared Communication
void communication_send(Ball_t*, Outcome_t);

// Receive Ball_t and Outcome_t data from inferared communcation
bool communication_receive(Ball_t*, Outcome_t*);

#endif