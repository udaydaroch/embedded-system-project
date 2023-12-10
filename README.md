# Pong Game - ENCE 260

## Authors 
- Uday Daroch 
- Toby Smillie 

## Introductions
This repository contains the implemented code for a simple Pong game. The game is designed to run on embedded systems with LED matrix displays. It features control over individual LED pixels, game state management, paddle control, and a simplistic representation of a ball.

## Setup, Compilation, and Prerequisites

- Ensure you have `avr-gcc`, `avr-objcopy`, and `dfu-programmer` installed on your system.
- The embedded system should be connected to your computer.

### Building the Project

1. Clone the repository to your local machine or download the source code.
  
    git clone https://eng-git.canterbury.ac.nz/ence260-2023/group_511.git
   
2. Navigate to the project's root directory. 

    Run: cd path/to/project-directory (something like this)

3. Use the Makefile to compile the source files and build the project.

    Run: make
  
  This command compiles the source code and creates an output file named `game.out`. The process involves various steps managed by    the Makefile.

### Uploading to the Embedded System

After building the project, the next step is to upload the game onto your embedded device.

1. To upload the compiled program to your embedded system, make sure the device is connected to your computer and is ready for file transfers.

2. Click the button reset button on the microcontroller to reset it.

3. Run: make program

### Cleaning up the Build

If you want to clean up your build environment (i.e., remove all compiled files), you can use the command:

    Run: make clean

This will remove all the `.o`, `.out`, and `.hex` files from the project's directory, ensuring a clean environment for your next build.

# Please note, all these commands are to be used in the terminal from within your project's main directory !!!

## Usage
- Power on your embedded system with the game code uploaded.
- Use the Navswitch to navigate through the menu. Select between "SERVER" or "RECEIVER" game modes.
- Push the Navswitch to start the game.
- Control the paddle using the NORTH and SOUTH movements of the Navswitch.
- The game supports basic collision detection and scoring.
- A win is indicated by the LED1 (blue light) being activated.
- A lose is indicated by the ball(LED) being stuck on the losing side.

