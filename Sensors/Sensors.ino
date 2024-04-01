#include "DHT.h"

const int AirQualitySensorPin = A0;
const int AirQualityValidPin = 2;
const int HumidityTempPin = 3;
const int SoilMoisturePin = A1;
const int MoistureValidPin = 4;
const int MoistureSensorPowerPin = 5;
// refresh rate in ms
const int RefreshRate = 5*1000;

int airQualityData;
int particlesFound;

DHT dht(HumidityTempPin, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MoistureSensorPowerPin, OUTPUT);

  pinMode(AirQualitySensorPin, INPUT);
  pinMode(MoistureValidPin, INPUT);

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
  digitalWrite(MoistureSensorPowerPin, HIGH);
  delay(10);

  int soilMoisture = analogRead(SoilMoisturePin);
  int isValid = digitalRead(MoistureValidPin);

  digitalWrite(MoistureSensorPowerPin, LOW);

  if (isValid) {
    Serial.print("Soil moisture:");
    Serial.println(soilMoisture);
  } else {
    Serial.println("Soil moisture error");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  getPPM();
  getAirInfo();
  getSoilInfo();
  
  delay(RefreshRate);
}
