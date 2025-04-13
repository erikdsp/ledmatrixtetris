#include "Matrix.h"
#include "Tetris.h"
#include "Potentiometer.h"
#include "Button.h"
#include <Arduino.h>

Potentiometer pot(A5, 0, 7);
Button buttonLeft(3);
int x_pos;
uint8_t selectedShape = 6;


void setup() {
  Serial.begin(9600);
  pot.init();
  buttonLeft.init();
}

void loop() {
  int buttonPress = buttonLeft.getState();
  pot.readValue();

  if (buttonPress) {
    selectedShape++;
    if (selectedShape > 6) selectedShape = 0;
  }

  int max_pos = led_matrix_height - 1 - (shapes[selectedShape].shapeSize - 1);
  pot.setOutputRange(0, max_pos);
  x_pos = pot.getScaledValue();

  for (Point p : shapes[selectedShape].shape){
    put_pixel_portrait(p.x + x_pos, p.y, g_ontime);
  }

}

