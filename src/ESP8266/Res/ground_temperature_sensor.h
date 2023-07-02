#ifndef GroundTemperatureSensor_h
#define GroundTemperatureSensor_h

#include <Arduino.h>

#include <OneWire.h>
#include <DallasTemperature.h>

class GroundTemperatureSensor {
  public:
    GroundTemperatureSensor(String sName, uint8_t uiDataPin);
    ~GroundTemperatureSensor();
    
  private:    
    String m_sName;    
    uint m_uiTimeSinceLastRead;
    uint m_uiInterval;    
    uint8_t m_uiDataPin;
    uint8_t m_uiIsRunning;        
    OneWire* m_pOneWire;
    DallasTemperature* m_pSensor;
    int m_ONE_WIRE_BUS;
    uint32_t m_uiStart;
    uint32_t m_uiStop;
    void m_setup();

    uint32_t m_run(int runs);

    uint m_uiLastIsRunning;
    uint m_uiLastInterval;    
    void m_printStatus();
  public: 
    String* m_getName();
    void m_setInterval(uint uiVal);   
    uint  m_getInterval();

    uint8_t m_getIsRunning();
    void m_setIsRunning(uint8_t uiVal);
    
    
    
    String m_auslesen();

};

#endif