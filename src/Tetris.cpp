#include "Tetris.h"

TetrisActiveBlock::TetrisActiveBlock() 
{
    reset();
}

TetrisActiveBlock::TetrisActiveBlock(uint8_t shape) 
{
    reset(shape);
}

TetrisActiveBlock::TetrisActiveBlock(TetrisGrid* grid) 
  : m_grid { grid }, m_position { 3, 0 }
  {
    reset();
  }

void TetrisActiveBlock::reset(){
    reset(random(0, 6));
}

void TetrisActiveBlock::reset(uint8_t shape){
    if (shape >= 0 && shape <= 6) {
        m_shape = shapes[shape];
    }
}

void TetrisActiveBlock::rotate(){
    Point temporaryShape[4];
    for (uint8_t i = 0 ; i < 4 ; ++i) {
        // translate to center position
        float x = m_shape.shape[i].x - m_shape.center.x;
        float y = m_shape.shape[i].y - m_shape.center.y;
        // do the rotation
        temporaryShape[i].x = -y;
        temporaryShape[i].y = x;
        // translate back to original position
        temporaryShape[i].x += m_shape.center.x;
        temporaryShape[i].y += m_shape.center.y;
    }
    // check for collisions

    // then update the m_shape variable
    for (uint8_t i = 0 ; i < 4 ; ++i) {
        m_shape.shape[i] = temporaryShape[i];
    }
}


void TetrisActiveBlock::setPosition(uint8_t x, uint8_t y){
    // REMOVE when setXPosition is done
    m_position.x = x;
    m_position.y = y;
}

void TetrisActiveBlock::setXPosition(uint8_t x){
    // TODO: move step by step, checking for collision along the way
    m_position.x = x;
}
void TetrisActiveBlock::incrementYPosition(){
    if (!shapeIsColliding( { m_position.x, m_position.y + 1 } )) {
       m_position.y++; 
    }
    else {
        // add to grid
        m_grid->add(m_shape, m_position);
        // reset y
        m_position.y = 0;
        // reset shape
        reset();
        // add collision check for GAME OVER
    }
}


bool TetrisActiveBlock::shapeIsColliding(Point position, Point shape[4]) {
    for (uint8_t i = 0 ; i < 4 ; ++i) {
        // check if any point is below bottom of grid
        if (shape[i].y + position.y >= led_matrix_width) {
            return true;
        }
        // check if any point collides with grid
        if (m_grid->isFilled(shape[i].x + position.x, shape[i].y + position.y)) {
            return true;
        }
    }
    // else return false
    return false;
}

bool TetrisActiveBlock::shapeIsColliding(Point position) {
    return shapeIsColliding(position, m_shape.shape);
}




void TetrisActiveBlock::draw(){
    for (Point p : m_shape.shape){
        put_pixel_portrait(p.x + m_position.x, p.y + m_position.y, g_ontime);
    }
}

// for testing
int TetrisActiveBlock::getShapeSize(){
    return m_shape.shapeSize;
}




void TetrisGrid::resetGrid(){

}

void TetrisGrid::add(TetrisShape shape, Point position){
    for (Point p : shape.shape) {
        float x = p.x + position.x;
        float y = p.y + position.y;
        // check that values are within the grid range
        if (x >= 0 && x <= led_matrix_height - 1 
            && y >= 0 && y <= led_matrix_width - 1) {
                m_grid[static_cast<uint8_t>(x)][static_cast<uint8_t>(y)] = true;
            }
    }
}

bool TetrisGrid::isFilled(uint8_t x, uint8_t y) {
    if (x < led_matrix_height && y < led_matrix_width) {
        return m_grid[x][y];
    }
    // add proper error handling
    return false;
}

void TetrisGrid::draw(){
    for (uint8_t y = 0 ; y < led_matrix_width ; ++y) {
        for (uint8_t x = 0 ; x < led_matrix_height ; ++x ) {
            if (m_grid[x][y]) {
                put_pixel_portrait(x, y, g_ontime);
            }
        }
    }
}
