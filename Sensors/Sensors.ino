#include "DHT.h"

const int AirQualitySensorPin = A0;
const int AirQualityValidPin = 2;
const int HumidityTempPin = 3;
const int SoilHumidityPin = A1;
const int SoilLectureValidPin = 4;
const int SoilSensorPowerPin = 5;
// refresh rate in ms
const int RefreshRate = 5*1000;

DHT dht(HumidityTempPin, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SoilSensorPowerPin, OUTPUT);

  pinMode(AirQualitySensorPin, INPUT);
  pinMode(SoilLectureValidPin, INPUT);
}

// return -1 if data is invalid
int getPPM() {
  int particlesFound = digitalRead(AirQualityValidPin);

  if (particlesFound) {
    return analogRead(AirQualitySensorPin);
  } else {
    return -1;
  }
}

// return NaN if data is invalid
float getAirHumidity() {
  return dht.readHumidity();
}

// return NaN if data is invalid
float getTemperature() {
  return dht.readTemperature();
}

int getSoilHumidity() {
  // turn on the sensor only when using to avoid corrosion
  digitalWrite(SoilSensorPowerPin, HIGH);
  delay(10);

  int isValid = digitalRead(SoilLectureValidPin);

  digitalWrite(SoilSensorPowerPin, LOW);

  if (isValid) {
    return analogRead(SoilHumidityPin);
  } else {
    return -1;
  }
}

void loop() {
  int ppm = getPPM();
  float airHumidity = getAirHumidity();
  float temp = getTemperature();
  int soilHumidity = getSoilHumidity();

  Serial.print(ppm); 
  Serial.print(" "); 
  Serial.print(airHumidity); 
  Serial.print(" "); 
  Serial.print(temp); 
  Serial.print(" "); 
  Serial.println(soilHumidity); 

  Serial.flush();
  
  delay(RefreshRate);
}
