#include "DHT.h"

const int AirQualitySensorPin = A0;
const int GasPresencePin = 2;
const int DhtPin = 3;

int airQualityData;
int particlesFound;

DHT dht(DhtPin, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(AirQualitySensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void getPPM() {
  airQualityData = analogRead(AirQualitySensorPin);
  particlesFound = digitalRead(GasPresencePin);

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

void loop() {
  // put your main code here, to run repeatedly:
  getPPM();
  getAirInfo();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
