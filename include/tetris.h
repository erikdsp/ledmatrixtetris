/**
 * @file Tetris.h
 * @author Erik Dahl
 * @brief  Tetris written for the Arduino UNO R4 Led Matrix
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
    TetrisActiveBlock();
//    TetrisActiveBlock(TetrisGrid* grid);
    void rotate();
    void reset();
    void reset(uint8_t shape);
    void setPosition(uint8_t x, uint8_t y);
    void advancePosition();
    void draw();
    // for testing purposes
    int getShapeSize();
    private:
    TetrisShape m_shape;
    Point m_position;
    TetrisGrid* m_grid;
    Point rotatePoint(Point pixel);
};




#endif