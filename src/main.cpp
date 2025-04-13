#include "Matrix.h"
#include "Tetris.h"
#include <Arduino.h>

uint8_t potPin = A5;
uint16_t potValueRaw;
int x_pos;
uint8_t selectedShape = 6;



void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
}

void loop() {
  potValueRaw = analogRead(potPin);
  // scale analog input to correct range for selected shape
  int max_pos = led_matrix_height - 1 - (shapes[selectedShape].shapeSize - 1);
  x_pos = map(potValueRaw, 0, 1023, 0, max_pos);
  x_pos = constrain(x_pos, 0, max_pos);

  for (Point p : shapes[selectedShape].shape){
    put_pixel_portrait(p.x + x_pos, p.y, g_ontime);
  }

}

