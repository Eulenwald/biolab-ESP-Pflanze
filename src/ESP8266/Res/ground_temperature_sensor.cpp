#include "ground_temperature_sensor.h"

GroundTemperatureSensor::GroundTemperatureSensor(String sName, uint8_t uiDataPin)
{
  m_sName = sName;
  m_uiDataPin = uiDataPin;

  
  m_setup();
};

GroundTemperatureSensor::~GroundTemperatureSensor()
{
  // Deallocate the memory that was previously reserved
  //  for this string.
  // TODO abisicher ob da
  delete m_pOneWire;
  delete m_pSensor;
}

void GroundTemperatureSensor::m_setup()
{
  m_uiTimeSinceLastRead = 0;
  m_uiInterval = 5;
  m_uiIsRunning = 0;

  m_uiLastIsRunning = m_uiIsRunning;
  m_uiLastInterval = m_uiInterval;

  m_pOneWire = new OneWire(m_uiDataPin);
  m_pSensor = new DallasTemperature(m_pOneWire);
  m_pSensor->begin();
}

String *GroundTemperatureSensor::m_getName() { return &m_sName; }

uint GroundTemperatureSensor::m_getInterval() { return m_uiInterval; }
void GroundTemperatureSensor::m_setInterval(uint uiVal)
{
  m_uiInterval = uiVal;
  if(m_uiIsRunning && uiVal != m_uiLastInterval)
    m_printStatus();
  m_uiLastInterval = m_uiInterval;
}

uint8_t GroundTemperatureSensor::m_getIsRunning() { return m_uiIsRunning; }
void GroundTemperatureSensor::m_setIsRunning(uint8_t uiVal) 
{ 
  m_uiIsRunning = uiVal; 
  if(uiVal != m_uiLastIsRunning)
    m_printStatus();
  m_uiLastIsRunning = m_uiIsRunning;
}

//Standard
void GroundTemperatureSensor::m_printStatus()
{
  Serial.println("###############################################################################");
  Serial.printf("Sensor %s is running with the following parameters: \n\tinterval: %i -- %i\n", 
  m_sName, m_uiLastInterval, m_uiInterval);
  Serial.println("###############################################################################");
}

String GroundTemperatureSensor::m_auslesen()
{
  if (m_uiIsRunning && m_uiTimeSinceLastRead > (m_uiInterval * 100))
  {
    m_pSensor->requestTemperatures();
    String rVal = m_sName;
    rVal.concat(',');
    // Payload
    rVal.concat(m_pSensor->getTempCByIndex(0));
    m_uiTimeSinceLastRead = 0;
    return rVal;
  }
  m_uiTimeSinceLastRead += 100;
  return "";
}
