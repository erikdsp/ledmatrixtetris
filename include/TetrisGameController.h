/**
 * @file Tetris.h
 * @author Erik Dahl
 * @brief  Tetris written for the Arduino UNO R4 Led Matrix
 * @version 0.1
 * @date 2025-04-13
 */
#ifndef ARDUINO_LED_MATRIX_TETRIS_GAME_CONTROLLER_H
#define ARDUINO_LED_MATRIX_TETRIS_GAME_CONTROLLER_H
#include "Tetris.h"
#include "Button.h"
#include "Potentiometer.h"
#include "Timer.h"

class TetrisGameController {
public:
    TetrisGameController(uint8_t potPin, uint8_t buttonLeftPin, uint8_t buttonRightPin, 
        uint32_t initialUpdateSpeed = 1000, uint32_t increaseSpeedInterval = 20000);
    void init();
    void getInput();
    void updateGameState();
    void draw();
private:
    void pause();
    void resume();
    void rotate();
    void incrementYOrAddToGrid();
    void gameOver();
    void increaseSpeed();
    Potentiometer m_pot; // (A5, 0, 7);
    Button m_buttonLeft; // (3);
    Button m_buttonRight; //(4);
    TetrisGrid m_grid;
    TetrisActiveBlock m_activeTetromino; //(&grid);
    Timer m_tetrisTimer; //(1000);
    Timer m_speedTimer; //(20000);
    bool m_pauseGame { false };
    int m_buttonLeftPress;
    int m_buttonRightPress;
};

#endif