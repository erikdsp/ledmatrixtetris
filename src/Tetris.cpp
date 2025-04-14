#include "Tetris.h"

TetrisActiveBlock::TetrisActiveBlock() 
{
    resetShape();
}

TetrisActiveBlock::TetrisActiveBlock(uint8_t shape) 
{
    resetShape(shape);
}

TetrisActiveBlock::TetrisActiveBlock(TetrisGrid* grid) 
  : m_grid { grid }, m_position { 3, 0 }
  {
    resetShape();
  }

void TetrisActiveBlock::resetShape(){
    resetShape(random(0, 6));
}

void TetrisActiveBlock::resetShape(uint8_t shape){
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
    if (shapeIsColliding(m_position, temporaryShape)) {
        return;
    }

    // then update the m_shape variable
    for (uint8_t i = 0 ; i < 4 ; ++i) {
        m_shape.shape[i] = temporaryShape[i];
    }
}

Range TetrisActiveBlock::getXRange() {
    int leftMostX = m_shape.shapeSize - 1;
    int rightMostX = 0;
    for (Point p : m_shape.shape) {
        if (p.x < leftMostX) leftMostX = p.x;
        if (p.x > rightMostX) rightMostX = p.x;
    }
    int min = -leftMostX;
    int max = 7 - (m_shape.shapeSize - 1) + ( m_shape.shapeSize - 1 - rightMostX );
    return { min, max };
}

void TetrisActiveBlock::setPosition(uint8_t x, uint8_t y){
    // REMOVE when setXPosition is done
    m_position.x = x;
    m_position.y = y;
}

void TetrisActiveBlock::setXPosition(int x){
    if (x > m_position.x) {
        while (x > m_position.x) {
            if (shapeIsColliding({m_position.x + 1, m_position.y })) {
                return;
            } else {
                m_position.x++;
            }
        }
    }
    if (x < m_position.x) {
        while (x < m_position.x) {
            if (shapeIsColliding({m_position.x - 1, m_position.y })) {
                return;
            } else {
                m_position.x--;
            }
        }
    }
}

bool TetrisActiveBlock::incrementYPosition(){
    if (!shapeIsColliding( { m_position.x, m_position.y + 1 } )) {
       m_position.y++;
       return true; 
    }
    else {
        return false;
    }
}

bool TetrisActiveBlock::addToGridAndResetShape() {
    m_grid->add(m_shape, m_position);
    m_grid->removeFilledLines();
    m_position.y = 0;
    resetShape();
    // if colliding Game Over
    if (shapeIsColliding(m_position)) return false;
    else return true;
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
        float x = p.x + m_position.x;
        float y = p.y + m_position.y;
        // check that values are within the grid range
        if (x >= 0 && x < 8 && y >= 0 && y < 12) {
            put_pixel_portrait(x, y, g_ontime);
        }
    }
}

// for testing
int TetrisActiveBlock::getShapeSize(){
    return m_shape.shapeSize;
}




void TetrisGrid::clearGrid(){
    for (int y = 0; y < 12; ++y) {
        m_grid[y] = 0;
    }    
}

void TetrisGrid::add(TetrisShape shape, Point position){
    for (Point p : shape.shape) {
        float x = p.x + position.x;
        float y = p.y + position.y;
        // check that values are within the grid range
        if (x >= 0 && x < 8 && y >= 0 && y < 12) {
            addCellToGrid(static_cast<uint8_t>(x), static_cast<uint8_t>(y));
        }
    }
}

void TetrisGrid::addCellToGrid(uint8_t x, uint8_t y){ 
    // Example (1 << 2) would be 00000100 in binary  
    m_grid[y] |= (1 << x); 
}

void TetrisGrid::removeCellFromGrid(uint8_t x, uint8_t y){
    // Example ~(1 << 2) would be 11111011 in binary  
    m_grid[y] &= ~(1 << x); 
}



void TetrisGrid::removeFilledLines(){
    // loop from the top
    for (int y = 0; y < 12; ++y) { 
        // If a row is filled shift the above rows down
        if (m_grid[y] == 255) { 
            shiftLinesDown(y);
        }
    }
}

void TetrisGrid::shiftLinesDown(uint8_t filledLine) {
    // Shift rows above the filled line downward
    for (int y = filledLine; y > 0; --y) {
        m_grid[y] = m_grid[y - 1]; // Move the row above to the current row
    }
    // Clear the top row
    m_grid[0] = 0;
}


bool TetrisGrid::isFilled(uint8_t x, uint8_t y) {
    if (x < 8 && y < 12) {
        return (m_grid[y] & (1 << x)) != 0;
    }
    return false;
}

void TetrisGrid::draw(){
    for (uint8_t y = 0 ; y < led_matrix_width ; ++y) {
        for (uint8_t x = 0 ; x < led_matrix_height ; ++x ) {
            if (isFilled(x, y)) {
                put_pixel_portrait(x, y, g_ontime);
            }
        }
    }
}
