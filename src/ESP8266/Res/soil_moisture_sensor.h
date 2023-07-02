#ifndef SoilMoistureSensor_h
#define SoilMoistureSensor_h

// Inline header Fensterkontakte

#include <Arduino.h>


class SoilMoistureSensor {
  public:
    SoilMoistureSensor(String sName, uint8_t uiDataPin);
    ~SoilMoistureSensor(){;}
  
  private:
    String m_sName;    
    uint m_uiTimeSinceLastRead;
    uint m_uiInterval;
    uint8_t m_uiDataPin;
    uint8_t m_uiIsRunning;
        
    uint m_uiThreshold;
    uint8_t m_uiRelaisPin;
    
    void m_setup();
    
    
    uint m_uiLastIsRunning;
    uint m_uiLastInterval;
    uint m_uiLastThreshold;
    void m_printStatus();

  public:
    String* m_getName();
    void m_setInterval(uint uiVal);
    uint  m_getInterval();

    uint8_t m_getIsRunning();
    void m_setIsRunning(uint8_t uiVal);

    void m_setThreshold(uint uiVal);
    uint  m_getThreshold();
    String m_auslesen();

};

#endif