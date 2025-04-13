#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin, uint16_t minOutput, uint16_t maxOutput)
  : m_potPin { pin }, m_minOutput { minOutput }, m_maxOutput { maxOutput } {}

void Potentiometer::init(){
    pinMode(m_potPin, INPUT);
}

void Potentiometer::readValue() {
    // read raw value
    m_potValueRaw = analogRead(m_potPin);
}

void Potentiometer::setOutputRange(uint16_t minOutput, uint16_t maxOutput){
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
}

uint16_t Potentiometer::getScaledValue() {
      // scale analog input to correct range for paddle control
      uint16_t scaledValue = map(m_potValueRaw, 0, 1023, m_minOutput, m_maxOutput);
      scaledValue = constrain(scaledValue, m_minOutput, m_maxOutput);
      return scaledValue;
}
