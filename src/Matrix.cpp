#include "Matrix.h"

// Activate the pixel at (x,y) for ontime microseconds.
void put_pixel(uint8_t x, uint8_t y, uint32_t ontime)
{
  uint8_t pins = led_matrix_pins[y][x];
  uint8_t l = (pins>>4) + led_matrix_pin_first;
  uint8_t h = (pins&0xf) + led_matrix_pin_first;
  pinMode(l,OUTPUT);
  digitalWrite(l,LOW);
  pinMode(h,OUTPUT);
  digitalWrite(h,HIGH);
  // If ontime = 0, pixel remains active until it is deactivated
  // by another put_pixel that happens to use the same pin(s).
  if (ontime!=0)
  {
    delayMicroseconds(ontime);
    pinMode(l,INPUT);
    pinMode(h,INPUT);
  }
}