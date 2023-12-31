#include "soil_moisture_sensor.h"

SoilMoistureSensor::SoilMoistureSensor(String sName, uint8_t uiDataPin)
{
  m_sName = sName;
  m_uiDataPin = uiDataPin;

  m_uiRelaisPin = 0;
  m_setup();
};

void SoilMoistureSensor::m_setup()
{
  m_uiTimeSinceLastRead = 0;
  m_uiInterval = 5;
  m_uiIsRunning = 0;

  m_uiThreshold = 1000;

  m_uiLastIsRunning = m_uiIsRunning;
  m_uiLastInterval = m_uiInterval;
  m_uiLastThreshold = m_uiThreshold;

  pinMode(m_uiRelaisPin, OUTPUT);
}

String *SoilMoistureSensor::m_getName() { return &m_sName; }

uint SoilMoistureSensor::m_getInterval() { return m_uiInterval; }
void SoilMoistureSensor::m_setInterval(uint uiVal)
{
  m_uiInterval = uiVal;
  if (m_uiIsRunning && uiVal != m_uiLastInterval)
    m_printStatus();
  m_uiLastInterval = m_uiInterval;
}

uint8_t SoilMoistureSensor::m_getIsRunning() { return m_uiIsRunning; }
void SoilMoistureSensor::m_setIsRunning(uint8_t uiVal)
{
  m_uiIsRunning = uiVal;
  if (uiVal != m_uiLastIsRunning)
    m_printStatus();
  m_uiLastIsRunning = m_uiIsRunning;
}

void SoilMoistureSensor::m_printStatus() {
  Serial.println("###############################################################################");
  Serial.printf( "Sensor %s is running with the following parameters: \n\tinterval: %i -> %i\n\tthreshold: %i -> X %i\n", 
  m_sName, m_uiLastInterval, m_uiInterval, m_uiLastThreshold, m_uiThreshold);  
  Serial.println("###############################################################################");  
}


uint SoilMoistureSensor::m_getThreshold() { return m_uiThreshold; }
void SoilMoistureSensor::m_setThreshold(uint uiVal)
{
  m_uiThreshold = uiVal;
  if (m_uiIsRunning && uiVal != m_uiLastThreshold)
    m_printStatus();
  m_uiLastThreshold = m_uiThreshold;
}

String SoilMoistureSensor::m_auslesen()
{
  if (m_uiIsRunning && m_uiTimeSinceLastRead > (m_uiInterval * 100))
  {
    int rawValue = analogRead(m_uiDataPin);
    if (isnan(rawValue))
    {
      Serial.println(m_sName + " Lesefehler am Sensor");
      return "";
    }

    // ist der Schwellwert erreicht, soll dass Licht angehen
    if (rawValue > m_uiThreshold)
    {
      // Serial.println("Licht an!!!");
      digitalWrite(m_uiRelaisPin, HIGH);
    }
    else if (rawValue < (m_uiThreshold - 50))
    {
      // Damit es aber nicht an dauern an und aus geht wird
      // der Wert etwas angepasst
      digitalWrite(m_uiRelaisPin, LOW);
    }

    /*float voltage = rawValue * (5.0/1023) * 1000;
    float resitance = 10000 * ( voltage / ( 5000.0 - voltage) );

    ... und hier auf die serielle Schnittstelle ausgegeben
    Serial.println(rawValue);
    Serial.print("Spannungswert:"); Serial.print(voltage); Serial.print("mV");
    Serial.print(", Widerstandswert:"); Serial.print(resitance); Serial.println("Ohm");
    Serial.println("---------------------------------------");
    */
    // Absender
    String rVal = m_sName;
    rVal.concat(',');
    // Payload
    rVal.concat(rawValue);
    m_uiTimeSinceLastRead = 0;
    return rVal;
  }

  m_uiTimeSinceLastRead += 100;
  return "";
}