# EGP-410
Template projects for base code for EGP 410 assignments.

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
  * Left click: Sets player's arrive & face location to the point clicked on
  * Enter: Spawns a random enemy on the screen, this enemy will wander untill the player is within range then will use arrive steering to follow the player.
  * D: Will delete a random enemy on the screen

# NOTES
  * Holding down enter or D will continuasly spawn or delete enemys

# Github Link
  * https://github.com/AlexTHubble/Egp-410-101-AlexanderHubble
