#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin, int minOutput, int maxOutput)
  : m_potPin { pin }, m_minOutput { minOutput }, m_maxOutput { maxOutput } {}

void Potentiometer::init(){
    pinMode(m_potPin, INPUT);
}

void Potentiometer::readValue() {
    // read raw value
    m_potValueRaw = analogRead(m_potPin);
}

void Potentiometer::setOutputRange(int minOutput, int maxOutput){
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
}

int Potentiometer::getScaledValue() {
      // scale analog input to correct range for paddle control
      int scaledValue = map(m_potValueRaw, 0, 1023, m_minOutput, m_maxOutput);
      scaledValue = constrain(scaledValue, m_minOutput, m_maxOutput);
      return scaledValue;
}
