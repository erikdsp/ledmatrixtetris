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

struct FloatPoint {
    float x;
    float y;
};

struct IntPoint {
    int x;
    int y;
};

struct Range {
    int min;
    int max;
};

struct TetrisShape {
    FloatPoint shape[4];
    FloatPoint center;
    int shapeSize;
};

constexpr TetrisShape shapes[7] = { 
    { { {0, 1 }, {1, 1}, {2, 1}, {3, 1} }, { 1.5, 1.5 }, 4 },    // I shape, 0
    { { {0, 0 }, {0, 1}, {1, 1}, {2, 1} }, { 1, 1 },     3 },    // J shape, 1
    { { {0, 2 }, {0, 1}, {1, 1}, {2, 1} }, { 1, 1 },     3 },    // L shape, 2
    { { {0, 0 }, {1, 0}, {0, 1}, {1, 1} }, { 0.5, 0.5 }, 2 },    // O shape, 3
    { { {0, 1 }, {1, 1}, {1, 0}, {2, 0} }, { 1, 1 },     3 },    // S shape, 4
    { { {1, 0 }, {0, 1}, {1, 1}, {2, 1} }, { 1, 1 },     3 },    // T shape, 5
    { { {0, 0 }, {1, 0}, {1, 1}, {2, 1} }, { 1, 1 },     3 }     // Z shape, 6
}; 

class TetrisGrid {
    public:
    void clearGrid();
    void add(TetrisShape shape, IntPoint position);
    void removeFilledLines();
    void draw();
    bool isFilled(uint8_t x, uint8_t y);
    private:
    uint8_t m_grid[12];
    void addCellToGrid(uint8_t x, uint8_t y);
    void removeCellFromGrid(uint8_t x, uint8_t y);
    void shiftLinesDown(uint8_t filledLine);
};

class TetrisActiveBlock {
    public:
    TetrisActiveBlock();
    TetrisActiveBlock(uint8_t shape);
    TetrisActiveBlock(TetrisGrid* grid);
    void resetShape();
    void resetShape(uint8_t shape);
    void rotate();
    Range getXRange();
    void setPosition(uint8_t x, uint8_t y);
    void setXPosition(int x);
    bool incrementYPosition();
    bool addToGridAndResetShape();
    bool shapeIsColliding(IntPoint position, FloatPoint shape[4]);
    bool shapeIsColliding(IntPoint position);
    void draw();
    // for testing purposes
    int getShapeSize();
    private:
    TetrisShape m_shape;
    IntPoint m_position;
    TetrisGrid* m_grid;

};




#endif