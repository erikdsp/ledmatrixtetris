#ifndef ARDUINO_POTENTIMETER_H
#define ARDUINO_POTENTIMETER_H
#include <Arduino.h>

class Potentiometer {
public:
    Potentiometer(uint8_t pin, uint16_t minOutput, uint16_t maxOutput);
    void init();
    void readValue();
    void setOutputRange(uint16_t minOutput, uint16_t maxOutput);
    uint16_t getScaledValue();
private:
    uint8_t m_potPin;
    uint16_t m_potValueRaw;
    uint16_t m_minOutput;
    uint16_t m_maxOutput;
};


#endif