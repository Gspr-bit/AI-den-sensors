#include "DHT.h"

const int AirQualitySensorPin = A0;
const int AirQualityValidPin = 2;
const int HumidityTempPin = 3;
const int SoilHumidityPin = A1;
const int SoilLectureValidPin = 4;
const int SoilSensorPowerPin = 5;
// refresh rate in ms
const int RefreshRate = 5*1000;

int airQualityData;
int particlesFound;

DHT dht(HumidityTempPin, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SoilSensorPowerPin, OUTPUT);

  pinMode(AirQualitySensorPin, INPUT);
  pinMode(SoilLectureValidPin, INPUT);
}

void getPPM() {
  airQualityData = analogRead(AirQualitySensorPin);
  particlesFound = digitalRead(AirQualityValidPin);

  if (particlesFound) {
    Serial.print(airQualityData, DEC);
    Serial.println("PPM");  
  } else {
    Serial.println("No particles found");
  }
}

void getAirInfo() {
  float airHumidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity:");
  Serial.println(airHumidity);

  Serial.print("Temperature:");
  Serial.println(temperature);
}

void getSoilInfo() {
  // turn on the sensor only when using to avoid corrosion
  digitalWrite(SoilSensorPowerPin, HIGH);
  delay(10);

  int soilMoisture = analogRead(SoilHumidityPin);
  int isValid = digitalRead(SoilLectureValidPin);

  digitalWrite(SoilSensorPowerPin, LOW);

  if (isValid) {
    Serial.print("Soil moisture:");
    Serial.println(soilMoisture);
  } else {
    Serial.println("Soil moisture error");
  }
}

void loop() {
  getPPM();
  getAirInfo();
  getSoilInfo();

  Serial.flush();
  
  delay(RefreshRate);
}
