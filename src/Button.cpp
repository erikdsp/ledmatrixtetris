#include "Button.h"



bool Button::pressDetected(){
    return (m_currentState && !m_lastState);
}

bool Button::releaseDetected(){
    return (!m_currentState && m_lastState);
}

Button::Button(uint8_t pin, time_t longPressTime) 
    : m_pin { pin }, m_longPressTime { longPressTime }  {}

void Button::init() {
    pinMode(m_pin, INPUT);
}

ButtonState Button::getState() {
    m_currentState = digitalRead(m_pin);  

    if (pressDetected()){
        m_awaitingLongpress = true;
        m_pressTime = millis();
    }

    time_t currentTime = millis();

    if (releaseDetected() && (millis() - m_pressTime > debounceTime)) {
        m_isPressed = false;
        m_awaitingLongpress = false;

        if (currentTime - m_pressTime < m_longPressTime) {
            m_lastState = m_currentState;      
            return SHORTPRESS;
        }    
    }

    if (m_awaitingLongpress && (currentTime - m_pressTime > m_longPressTime)) {
        m_awaitingLongpress = false;
        return LONGPRESS;
    }
    
    m_lastState = m_currentState;
    return NOPRESS;
}