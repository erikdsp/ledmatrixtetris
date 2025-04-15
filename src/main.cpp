/**
 * @file main.cpp
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief A Tetris Game for the Arduino UNO R4 Led Matrix
 * @version 0.2
 * @date 2025-04-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "TetrisGameController.h"

TetrisGameController game(A5, 3, 4);

void setup() {
  Serial.begin(9600);
  game.init();
}

void loop() {
  game.getInput();
  game.updateGameState();
  game.draw();
}

