const int AirQualitySensorPin = A0;
const int GasPresencePin = 2;

int airQualityData;
int particlesFound;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(AirQualitySensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  airQualityData = analogRead(AirQualitySensorPin);
  particlesFound = digitalRead(GasPresencePin);

  if (particlesFound) {
    Serial.print(airQualityData, DEC);
    Serial.println("PPM");  
  } else {
    Serial.println("No particles found");
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
