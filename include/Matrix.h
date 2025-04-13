/**
 * @file Matrix.h
 * @brief 
 * 
 * This function is ported from text message scrolling
 * library by Clemens Valens, Elektor
 * Link: https://github.com/ClemensAtElektor/Arduino-UNO-R4
 * 
 */
#ifndef ARDUINO_R4_MATRIX_H
#define ARDUINO_R4_MATRIX_H
#include "LedMatrixConstants.h"

void put_pixel(uint8_t x, uint8_t y, uint32_t ontime);
void put_pixel_portrait(uint8_t x, uint8_t y, uint32_t ontime);


#endif