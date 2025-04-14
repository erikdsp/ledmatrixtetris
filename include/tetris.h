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

struct Range {
    int min;
    int max;
};

struct TetrisShape {
    Point shape[4];
    Point center;
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
    void add(TetrisShape shape, Point position);
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
    void setXPosition(uint8_t x);
    bool incrementYPosition();
    void addToGrid();
    bool shapeIsColliding(Point position, Point shape[4]);
    bool shapeIsColliding(Point position);
    void draw();
    // for testing purposes
    int getShapeSize();
    private:
    TetrisShape m_shape;
    Point m_position;
    TetrisGrid* m_grid;

};




#endif