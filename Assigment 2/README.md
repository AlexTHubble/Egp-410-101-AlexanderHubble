# Assigment 2
  * Assigment 2 for EGP-410

# This repository contains three major directories:
 * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.
 * External Libs - Allegro 5.0.10 support libraries.
 * Game AI - Base source code for EGP 410 Assignments
   * pathfinding
   * state machine
   * steering

# Build instructions
  *Set steering.sln as the startup progect
  *Retarget solutions using Windows SDK Version 10.0.16299.0

# Keyboard inputs
  * A: Spawns 10 boids in random locations
  * D: Will delete a random enemy on the screen
  * S: Saves the current values to the file, generates a file if none exits
  * L: Loads the file and implements any changes to the algorathim

# FILE INSTRUCTION
  * Pressing S will generate the text file "FlockValues.txt" and will save the current values to the text file.
  * Pressing L will load the file's data values and make the adjustments to the algoritm while running
  * Simply adjusting the file then pressing L will allow the user to tweak the alogorthim.

# NOTES
  * Tends to lagg after having too many boids
  * Re saving the file will fix any errors that may of been made to the text file

# GITHUP link
  * https://github.com/AlexTHubble/EGP-410-101_Alexander-Hubble.git
