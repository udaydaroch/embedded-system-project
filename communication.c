/**
 * @file communcation.c
 * @author Uday Daroch, Toby Smillie
 * 
 * Description:
 * @brief provides infrared communcation 
 * This file provides the functions and logic to initalize, send, and recieve data over an infrared.
 * link between devices. It includes encoding and decoding operation to ensure proper data formatting for communication
*/

#include "communication.h"
#include "ir_uart.h"
#include "ball.h"

/**
 * Initializes the communcation module for infrared communcatoin
 * (function is called before communication operations)
*/
void communication_init(void) 
{
    ir_uart_init();
}

/**
 * Sends Ball_t and Outcome_t data over the inferared link.
 * @param ball a pointer to a Ball_t(struct) represents the ball's state.
 * @param outcome an Outcome_t(enum) value representing the outcome of the game eg LOSING,... etc.
 * 
 * The function encodes the outcome, ball->dy, and ball->y into a single byte and sends it oer the infared communication
*/
void communication_send(Ball_t* ball, Outcome_t outcome)
{
    uint8_t byteEncoded, bitsY;
    bitsY = BITSY_MAX - ball->y;
    //Encode outcome
    byteEncoded = (outcome << SHIFT_OUTCOME) + (ball->dy << SHIFT_DY) + bitsY;
    ir_uart_putc(byteEncoded);
}

/**
 * Receives Ball_t and Outcome_t data from the inferared link.
 * @param ball a pointer to a Ball_t(struct) where the receieved ball-related data will be stored
 * @param outcome an Outcome_t(enum) where the received outcome-related data will be stored
 * 
 * This function checks if the data is ready to be read over the infrared link.
 * if data is avaiable it essentially decodes its to extract the neccesary data and allocates/stores it to provided ball and outcome. 
 * the functions true if the if the data was successfully received, otherwise, it returns false. 
*/
bool communication_receive(Ball_t* ball, Outcome_t* outcome)
{

    uint8_t encodedByte;
    // checks if the data is ready to be read
    if (ir_uart_read_ready_p()){
        // gets the data 
        encodedByte = ir_uart_getc();
        // extracts the data from the provided bytes and stores it in the relavent variable
        *outcome = ((encodedByte & BITS_OUTCOME) >> SHIFT_OUTCOME);
        ball->dy = ((encodedByte & BITS_DY) >> SHIFT_DY);
        ball->y = encodedByte & BITS_Y;
        return true;
    }
    return false;
}

