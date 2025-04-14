#include "Matrix.h"
#include "Tetris.h"
#include "Potentiometer.h"
#include "Button.h"
#include "Timer.h"
#include <Arduino.h>

Potentiometer pot(A5, 0, 7);
Button buttonLeft(3);
Button buttonRight(4);
TetrisGrid grid;
TetrisActiveBlock activeTetromino(&grid);
Timer g_tetrisTimer(1000);
Timer g_speedTimer(20000);

void setup() {
  Serial.begin(9600);
  pot.init();
  buttonLeft.init();
  buttonRight.init();
  pot.setOutputRange(activeTetromino.getXRange());
}

void loop() {
  // read values
  int buttonLeftPress = buttonLeft.getState();
  int buttonRightPress = buttonRight.getState();
  pot.readValue();

  // rotation
  if (buttonLeftPress) {
    activeTetromino.rotate();
    pot.setOutputRange(activeTetromino.getXRange());
  }

  // y movement
  if (g_tetrisTimer.timeToUpdate() || buttonRightPress) {
    bool incremented = activeTetromino.incrementYPosition();
    if (!incremented) {
      activeTetromino.addToGrid();
      pot.setOutputRange(activeTetromino.getXRange());
    }
    g_tetrisTimer.reset();
  }

  // gradually increase speed
  if (g_speedTimer.timeToUpdate()){
    uint32_t oldDuration = g_tetrisTimer.getDuration();
    if (oldDuration < 100) {
      g_tetrisTimer.setDuration(oldDuration * 0.9);
    }
    g_speedTimer.reset();
  }

  // x movement
  activeTetromino.setXPosition(pot.getScaledValue());

  // draw
  activeTetromino.draw();
  grid.draw();

}

