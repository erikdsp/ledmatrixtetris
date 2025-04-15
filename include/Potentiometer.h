#ifndef ARDUINO_POTENTIMETER_H
#define ARDUINO_POTENTIMETER_H
#include "Tetris.h"
#include <Arduino.h>

class Potentiometer {
public:
    Potentiometer(uint8_t pin, int minOutput, int maxOutput);
    void init();
    void readValue();
    void setOutputRange(int minOutput, int maxOutput);
    void setOutputRange(Range outputRange);
    int getScaledValue();
    uint16_t getRawValue();
private:
    uint8_t m_potPin;
    uint16_t m_potValueRaw;
    int m_minOutput;
    int m_maxOutput;
};


#endif