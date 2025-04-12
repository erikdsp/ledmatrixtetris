#include "Matrix.h"
#include "Tetris.h"
#include <Arduino.h>



void setup() {
}

void loop() {
  for (Point p : shapes[1].shape){
    put_pixel(p.x, p.y, g_ontime);
  }

}

