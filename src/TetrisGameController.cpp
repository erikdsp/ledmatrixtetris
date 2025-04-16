#include "TetrisGameController.h"


TetrisGameController::TetrisGameController(uint8_t potPin, uint8_t buttonLeftPin, uint8_t buttonRightPin, 
    uint32_t initialUpdateSpeed, uint32_t increaseSpeedInterval) 
    : m_pot{ potPin, 0, 7 }, m_buttonLeft { buttonLeftPin }, m_buttonRight { buttonRightPin },
     m_grid {}, m_activeTetromino { &m_grid }, m_tetrisTimer { initialUpdateSpeed },
     m_speedTimer { increaseSpeedInterval } {}

void TetrisGameController::init() {
    m_pot.init();
    m_buttonLeft.init();
    m_buttonRight.init();
    m_pot.setOutputRange(m_activeTetromino.getXRange());
}

void TetrisGameController::getInput(){
    m_buttonLeftPress = m_buttonLeft.getState();
    m_buttonRightPress = m_buttonRight.getState();
    m_pot.readValue(); 
}

void TetrisGameController::updateGameState(){
    if (m_pauseGame) {
        if (m_buttonRightPress || m_buttonLeftPress) {
            this->resume();
        }
      } else {
        if (m_buttonLeftPress == LONGPRESS) {
            this->pause();
        }
  
        if (m_buttonLeftPress == SHORTPRESS) {
            this->rotate();
        }      
        
        if (m_tetrisTimer.timeToUpdate() || m_buttonRightPress == SHORTPRESS) {
            this->incrementYOrAddToGrid();  
        }
        
        if (m_speedTimer.timeToUpdate()){
            this->increaseSpeed();
        }

        m_activeTetromino.setXPosition(m_pot.getScaledValue());      
      }
}


void TetrisGameController::pause(){
    m_pauseGame = true;
    m_tetrisTimer.pause();
    m_speedTimer.pause();
}

void TetrisGameController::resume(){
    m_pauseGame = false;
    m_tetrisTimer.resume();
    m_speedTimer.resume();
}

void TetrisGameController::rotate(){
    m_activeTetromino.rotate();
    m_pot.setOutputRange(m_activeTetromino.getXRange());
}

void TetrisGameController::incrementYOrAddToGrid() {
    bool incremented = m_activeTetromino.incrementYPosition();
    if (!incremented) {
      bool playing = m_activeTetromino.addToGridAndResetShape();
      m_pot.setOutputRange(m_activeTetromino.getXRange());
      
      if (!playing) {
        this->gameOver();
      }
    }
    m_tetrisTimer.reset();
}

void TetrisGameController::gameOver(){
    m_tetrisTimer.setDuration(3000);
    m_tetrisTimer.reset();
    while (!m_tetrisTimer.timeToUpdate()) {
        m_grid.draw();
    }
    m_tetrisTimer.setDuration(1000);
    m_grid.clearGrid();
}

void TetrisGameController::increaseSpeed(){
    uint32_t oldDuration = m_tetrisTimer.getDuration();
    if (oldDuration < 100) {
      m_tetrisTimer.setDuration(oldDuration * 0.9);
    }
    m_speedTimer.reset();
}

void TetrisGameController::draw(){
    m_activeTetromino.draw();
    m_grid.draw();  
}
