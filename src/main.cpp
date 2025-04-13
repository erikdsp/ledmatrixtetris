#include "Matrix.h"
#include "Tetris.h"
#include "Potentiometer.h"
#include "Button.h"
#include <Arduino.h>

Potentiometer pot(A5, 0, 7);
Button buttonLeft(3);
Button buttonRight(4);
int x_pos;
uint8_t selectedShape = 6;
TetrisActiveBlock activeTetromino(0);
TetrisGrid grid;


void setup() {
  Serial.begin(9600);
  pot.init();
  buttonLeft.init();
  buttonRight.init();
  grid.add(shapes[1], { 0, 10 } );
  grid.add(shapes[3], { 6, 10 } );
}

void loop() {
  int buttonLeftPress = buttonLeft.getState();
  int buttonRightPress = buttonRight.getState();
  pot.readValue();

  if (buttonLeftPress) {
    activeTetromino.rotate();
  }

  if (buttonRightPress) {
    selectedShape++;
    if (selectedShape > 6) selectedShape = 0;
    activeTetromino.reset(selectedShape);
  }


  int max_pos = led_matrix_height - 1 - (activeTetromino.getShapeSize() - 1);
  pot.setOutputRange(0, max_pos);
  x_pos = pot.getScaledValue();
  activeTetromino.setPosition(x_pos, 0);

  activeTetromino.draw();
  grid.draw();

}

