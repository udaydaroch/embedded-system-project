/**
 * @file display_game.c
 * @author Uday Daroch, Toby Smillie
 * 
 * Description:
 * @brief controls the Led matrix display 
 * 
 * contains functions to intialize and control the led matrix display for 
 * displaying game-related information and messages. 
*/

#include "display_game.h"
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include <stdint.h>
#include <stdbool.h>

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/**
 * Initializes the Led matrix display and tingyl library
*/
void display_game_init(void) 
{   
    // configures PIO pins for LED matrix rows and columns
    for (uint8_t column = INITIAL_COLOUMN_ROW; column < LEDMAT_COLS_NUM; column++) {
        pio_config_set(cols[column], PIO_OUTPUT_HIGH);
    }
    for (uint8_t row = INITIAL_COLOUMN_ROW; row < LEDMAT_ROWS_NUM; row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }

    // Configure LED1 pin as an output.
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);

    // Initialize the tingyl library for text display.
    tinygl_init(500);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

/**
 * controls the led matrix column for display
 * 
 * @param row_pattern The LED pattern for the row.
 * @param current_column The current column being controlled.
 * @param on_off Indicates whether to turn the LEDs on or off.
 * 
*/
void display_game_column (uint8_t row_pattern, uint8_t current_column, bool on_off)
{
    // Control LED matrix column.
    if(on_off){
        for (uint8_t other_column = INITIAL_COLOUMN_ROW; other_column < LEDMAT_ROWS_NUM; other_column++) {
            if(current_column == other_column) {
                
                pio_output_low(cols[current_column]);
            } else {
                pio_output_high(cols[other_column]);
            }
        }

        for (uint8_t current_row = INITIAL_COLOUMN_ROW; current_row < LEDMAT_ROWS_NUM; current_row++) {
            if((row_pattern >> current_row) & EQUIVALNET_ROW) {
                pio_output_low(rows[current_row]);
            } else {
                pio_output_high(rows[current_row]);
            }
        }
    } else {
        for (uint8_t other_column= INITIAL_COLOUMN_ROW; other_column < LEDMAT_ROWS_NUM; other_column++) {
            if(current_column == other_column) {
                pio_output_high(cols[other_column]);
            }
        }

        for (uint8_t current_row = INITIAL_COLOUMN_ROW; current_row < LEDMAT_ROWS_NUM; current_row++) {
            if((row_pattern >> current_row) & EQUIVALNET_ROW) {
                pio_output_high(rows[current_row]);
            } 
        }
    }
}

/**
 * Controls an individual LED pixel on the matrix.
 * 
 * @param row The row of the LED pixel.
 * @param col The column of the LED pixel.
 * @param on_off Indicates whether to turn the LED on or off
*/
void display_game_pixel(uint8_t row, uint8_t col, bool on_off)
{
    // Control individual LED pixel.
    if (on_off) {
        pio_output_low (rows[row]);
        pio_output_low (cols[col]);
    } else {
        pio_output_high (rows[row]);
        pio_output_high (cols[col]);
    }
}
/**
 * sets the LED1 pin(blue light) to indiciate a win
*/
void display_game_set_win(void)
{
    pio_output_high(LED1_PIO);
}

/**
 * Displays "SERVER" or "RECIEVER" text on the LED matrix.
 * makes use of the tingyl functions to execute inputs. 
 * @param lastState whether it's the server or receiver state.
*/
void display_game_server_receiver(bool lastState)
{
    // Display appropriate text based on the state.
    if (lastState) {
        tinygl_clear();
        tinygl_text("SERVER");
    } else {
        tinygl_clear();
        tinygl_text("RECEIVER");
    }
    
}

/**
 * Updates the LED matrix display by calling the tingyl function
*/
void display_game_update(void) 
{
    tinygl_update();
}

/**
 * Clears the LED matrix display.
*/
void display_game_clear(void)
{
    tinygl_clear();
}