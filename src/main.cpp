#include "Matrix.h"
#include "Tetris.h"
#include <Arduino.h>



void setup() {
}

void loop() {
  for (Point p : shapes[1].shape){
    float portraitX = p.y;
    float portraitY = led_matrix_height - 1 - p.x;
    put_pixel(portraitX, portraitY, g_ontime);
  }

}

