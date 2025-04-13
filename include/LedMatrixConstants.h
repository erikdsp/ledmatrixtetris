/**
 * @file LedMatrixConstants.h
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief Constants for the Arduino UNO R4 LED Matrix
 * @version 0.1
 * @date 2025-04-12
 * 
 * Part of led_matrix code ported from text message scrolling
 * library by Clemens Valens, Elektor
 * Link: https://github.com/ClemensAtElektor/Arduino-UNO-R4
 * 
 */
#ifndef ARDUINO_LEDMATRIX_CONSTANTS_H
#define ARDUINO_LEDMATRIX_CONSTANTS_H

#include <Arduino.h>

// LED matrix info.
constexpr uint8_t led_matrix_pin_first = 28;
constexpr uint8_t led_matrix_pin_last = 38;
constexpr uint8_t led_matrix_pin_count = led_matrix_pin_last - led_matrix_pin_first + 1;
constexpr uint8_t led_matrix_height = 8;
constexpr uint8_t led_matrix_width = 12;

// Pixel-to-pin translation table.
// A HEX value encodes two pin numbers. The MSB is to be driven LOW,
// the LSB is to be driven HIGH.
// Example: pixel (4,2) contains the value 0x60, meaning that pin 6 must
// be driven low and pin 0 must be driven high to activate the pixel.
// The pin number is an offset to the constant led_matrix_pin_first
// Note that they all appear in pairs, so you could make the table 50%
// smaller at the cost of doing some swapping for odd or even columns.
// (0,0) is upper left corner when the board's USB connector points to the left.
constexpr uint8_t led_matrix_pins[led_matrix_height][led_matrix_width] =
{
  //  0     1     2     3     4     5     6     7     8     9    10     11
  { 0x37, 0x73, 0x47, 0x74, 0x43, 0x34, 0x87, 0x78, 0x83, 0x38, 0x84, 0x48 }, // 0
  { 0x07, 0x70, 0x03, 0x30, 0x04, 0x40, 0x08, 0x80, 0x67, 0x76, 0x63, 0x36 }, // 1
  { 0x64, 0x46, 0x68, 0x86, 0x60, 0x06, 0x57, 0x75, 0x53, 0x35, 0x54, 0x45 }, // 2
  { 0x58, 0x85, 0x50, 0x05, 0x56, 0x65, 0x17, 0x71, 0x13, 0x31, 0x14, 0x41 }, // 3
  { 0x18, 0x81, 0x10, 0x01, 0x16, 0x61, 0x15, 0x51, 0x27, 0x72, 0x23, 0x32 }, // 4
  { 0x24, 0x42, 0x28, 0x82, 0x20, 0x02, 0x26, 0x62, 0x25, 0x52, 0x21, 0x12 }, // 5
  { 0xa7, 0x7a, 0xa3, 0x3a, 0xa4, 0x4a, 0xa8, 0x8a, 0xa0, 0x0a, 0xa6, 0x6a }, // 6
  { 0xa5, 0x5a, 0xa1, 0x1a, 0xa2, 0x2a, 0x97, 0x79, 0x93, 0x39, 0x94, 0x49 }, // 7
};

constexpr uint16_t g_ontime = 521;



#endif