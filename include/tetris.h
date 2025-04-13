/**
 * @file Timer.h
 * @author Erik Dahl
 * @brief  Timer class to handle timing
 * @details  This class is used to handle timing tasks
 * It has methods to reset the timer, check if it is time to update and set the duration
 * Based on Timer co-written by John Collinder
 * @version 0.1
 * @date 2025-04-13
 */

 #ifndef ARDUINO_LED_MATRIX_TETRIS_H
#define ARDUINO_LED_MATRIX_TETRIS_H

#include "Matrix.h"
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
    {{{0,1 }, {1, 1}, {2, 1}, {3, 1}}, { 1.5, 1.5 }, 4},    // I shape, 0
    {{{0,0 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 },    3},     // J shape, 1
    {{{0,2 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 },    3},     // L shape, 2
    {{{0,0 }, {1, 0}, {0, 1}, {1, 1}}, { 0.5, 0.5 }, 2},    // O shape, 3
    {{{0,1 }, {1, 1}, {1, 0}, {2, 0}}, { 1, 1 }, 3},        // S shape, 4
    {{{1,0 }, {0, 1}, {1, 1}, {2, 1}}, { 1, 1 }, 3},        // T shape, 5
    {{{0,0 }, {1, 0}, {1, 1}, {2, 1}}, { 1, 1 }, 3}         // Z shape, 6
}; 

class TetrisGrid {
    public:
    void resetGrid();
    void add(Point shape[4]);
    private:
    bool m_grid[led_matrix_height][led_matrix_width];
};

class TetrisActiveBlock {
    public:
    void rotate();
    void reset();
    void updatePosition();
    private:
    TetrisShape m_shape;
    Point m_position;
};




#endif