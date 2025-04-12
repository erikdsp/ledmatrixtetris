#ifndef ARDUINO_LED_MATRIX_TETRIS_H
#define ARDUINO_LED_MATRIX_TETRIS_H

#include <Arduino.h>

struct Point {
    float x;
    float y;
};

struct TetrisShape {
    Point shape[4];
    Point center;
    int shapeSize;
};

constexpr TetrisShape shapes[7] = { 
    {{{0,1 }, {1, 1}, {2, 1}, {3, 1}}, { 1.5, 1.5 }, 4},    // I shape
    {{{0,0 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 },    3},     // J shape
    {{{0,2 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 },    3},     // L shape
    {{{0,0 }, {1, 0}, {0, 1}, {1, 1}}, { 0.5, 0.5 }, 2},    // O shape
    {{{0,1 }, {1, 1}, {0, 1}, {0, 2}}, { 1, 1 }, 3},        // S shape
    {{{1,0 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 }, 3},        // T shape
    {{{0,0 }, {1, 0}, {1, 1}, {2, 1}}, { 1, 1 }, 3}         // Z shape
}; 




#endif