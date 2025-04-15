/**
 * @file Timer.h
 * @author Erik Dahl
 * @brief  Timer class to handle timing
 * @details  This class is used to handle timing tasks
 * It has methods to reset the timer, check if it is time to update and set the duration
 * Based on Timer co-written by John Collinder
 * @version 0.1
 * @date 2025-04-13
 */
#ifndef ARDUINO_TIMER_H
#define ARDUINO_TIMER_H
#include <Arduino.h>

class Timer
{

private:
    uint32_t m_timerDuration;
    uint32_t m_lastUpdate;
    bool m_paused { false };
public:

    /**
     * @brief Construct a new Timer object. Specify duration in milliseconds
     * @param timerDuration
     */
    Timer(uint32_t timerDuration = 1000)  
        : m_timerDuration(timerDuration)
    {
        reset();
    }
  
    /**
     * @brief  Reset the timer
     */
    void reset()
    {
        if (!m_paused) m_lastUpdate = millis();
        else m_lastUpdate = 0;
    }
    /**
     * @brief  Check if it is time to update
     * @return true
     * @return false
     */
    bool timeToUpdate()
    {
        if (m_paused) return false;
        else return (millis() - m_lastUpdate > m_timerDuration);
    }

    /**
     * @brief Set the Duration object
     * @param duration
     */
    void setDuration(uint32_t duration = 1000)
    {
        m_timerDuration = duration;
    }

    uint32_t getDuration(){
        return m_timerDuration;
    }

    void pause(){
        if (!m_paused) {
            m_paused = true;
            // save the current count since m_lastUpdate
            m_lastUpdate = millis() - m_lastUpdate;
        }
    }

    void resume(){
        if (m_paused){
            m_paused = false;
            // reset m_lastUpdate to current count relative to m_timerDuration
            m_lastUpdate = millis() - (m_timerDuration - m_lastUpdate);
        }
    }

};


#endif