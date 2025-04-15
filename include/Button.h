/**
 * @file Button.h
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief Adapter from Button class written for IoT project at Chas Academy
 * @version 0.2
 * @date 2025-04-13
 */
#ifndef __IOT_BUTTON_CLASS_HPP__
#define __IOT_BUTTON_CLASS_HPP__

#include <Arduino.h>

enum ButtonState
{
    NOPRESS = 0,
    SHORTPRESS,
    LONGPRESS
};

/**
 * @brief Handles button presses with functionality for short press and long press
 *
 * Button is assumed to be connected with a pull-down resistor
 * meaning Button pressed is HIGH and Button open is LOW
 */

class Button
{
private:
    uint8_t m_pin;
    uint16_t m_lastState{0};
    uint16_t m_currentState{0};
    const time_t m_longPressTime;
    const time_t debounceTime{50};
    time_t m_pressTime{0};
    bool m_isPressed{false};
    bool m_awaitingLongpress{false};
    /**
     * @brief Helper function to make functionality explicit
     *
     * @return true when press is detected
     * @return false when no press is detected
     */
    bool pressDetected();
    bool releaseDetected();

public:
    /**
     * @brief Construct a new Button object
     *
     * @param pin Number of the pin the button is connected to
     * @param longPressTime defaults to 1000 ms
     */
    Button(uint8_t pin, time_t longPressTime = 1000);
    /**
     * @brief Run in setup() to set correct pinMode
     *
     */
    void init();
    /**
     * @brief Get the current button state
     *
     * @return ButtonState Enum has the values NOPRESS, SHORTPRESS and LONGPRESS
     * on release SHORTPRESS is returned if press duration is shorter than m_longPressTime
     * if a press lasts longer than m_longPressTime LONGPRESS is immediately returned
     */
    ButtonState getState();
};

#endif