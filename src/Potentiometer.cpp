#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin, int minOutput, int maxOutput)
  : m_potPin { pin }, m_minOutput { minOutput }, m_maxOutput { maxOutput } {}

void Potentiometer::init(){
    pinMode(m_potPin, INPUT);
}

void Potentiometer::readValue() {
    // read raw value
    if (millis() - m_lastPressTime > m_debounceTime) {
        m_potValueRaw = analogRead(m_potPin);
        m_lastPressTime = millis();
    }
}

void Potentiometer::setOutputRange(int minOutput, int maxOutput){
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
}

void Potentiometer::setOutputRange(Range outputRange) {
    m_minOutput = outputRange.min;
    m_maxOutput = outputRange.max;
}

int Potentiometer::getScaledValue() {
      // scale analog input to correct range for paddle control
      // constraining values above 1023 to avoid Potentiometer chattering
      // TODO: Find a more robust general solution
      int scaledValue = map(constrain(m_potValueRaw, 0, 1020), 0, 1020, m_minOutput, m_maxOutput);
      scaledValue = constrain(scaledValue, m_minOutput, m_maxOutput);
      return scaledValue;
}

uint16_t Potentiometer::getRawValue(){
    return m_potValueRaw;
}