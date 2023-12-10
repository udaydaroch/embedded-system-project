/**
 * @file display_game.h
 * @author Uday Daroch, Toby Smillie
 * 
 * Description: 
 * @brief file for controlling the LED matrix display.
 * 
 * contains functions declaration and constant definitions
 * for controlling the LED matrix display for displaying game-related information
 * and messages. 
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include "system.h"
#include <stdint.h>
#include <stdbool.h>

#define MESSAGE_RATE 20         // Rate of scrolling message
#define INITIAL_COLOUMN_ROW 0   // Initial colum and row index
#define EQUIVALNET_ROW 1        // Equivalant row for LED pattern

/**
 * Initializes the LED matrix display and tinygl library.
 */
void display_game_init(void);

/**
 * Controls the LED matrix column for display.
 */

void display_game_column(uint8_t, uint8_t, bool);
/**
 * Controls an individual LED pixel on the matrix.
 */
void display_game_pixel(uint8_t, uint8_t, bool);

/**
 * Sets the LED1 pin to indicate a win.
 */
void display_game_set_win(void);
/**
 * Displays "SERVER" or "RECEIVER" text on the LED matrix.
 */

void display_game_server_receiver(bool);

/**
 * Updates the LED matrix display.
 */
void display_game_update(void);
/**
 * Clears the LED matrix display.
 */
void display_game_clear(void);

#endif