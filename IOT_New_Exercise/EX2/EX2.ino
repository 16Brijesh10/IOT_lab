// Soil moisture program
#include <Wire.h>

// Pin Definitions
const int moistureSensorPin = A0;
const int buzzerPin = 11;
const int lightDryPin = 13;
const int lightHumidPin = 10;
const int lightWetPin = 12;

// Moisture Thresholds
const int DRY_THRESHOLD = 1000;
const int HUMID_THRESHOLD = 600;
const int WET_THRESHOLD = 370;

int moistureLevel;

void setup() {
  // Pin Initialization
  pinMode(moistureSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightDryPin, OUTPUT);
  pinMode(lightHumidPin, OUTPUT);
  pinMode(lightWetPin, OUTPUT);

  // Serial Monitor Initialization
  Serial.begin(9600);
  Serial.println("Annamalai University BE CSE 2023");
  Serial.println("Soil Moisture Program");
}

// Function to read and calculate moisture percentage
int readMoisture() {
  int sensorValue = analogRead(moistureSensorPin);
  int moisture = 100 - ((sensorValue / 1023.0) * 100);
  Serial.print("Moisture Level: ");
  Serial.print(moisture);
  Serial.println("%");
  return sensorValue;
}

// Function to handle the dry soil condition
void handleDrySoil() {
  Serial.println("DRY SOIL");
  digitalWrite(lightDryPin, HIGH);   // Light to indicate dry soil
  digitalWrite(lightHumidPin, LOW);
  digitalWrite(lightWetPin, LOW);
  
  tone(buzzerPin, 1000);             // Buzzer at 1kHz
  delay(1000);                       // Sound for 1 second
  noTone(buzzerPin);                 // Stop sound
}

// Function to handle humid soil condition
void handleHumidSoil() {
  Serial.println("HUMID SOIL");
  digitalWrite(lightHumidPin, HIGH); // Light to indicate humid soil
  digitalWrite(lightDryPin, LOW);
  digitalWrite(lightWetPin, LOW);
}

// Function to handle wet soil condition
void handleWetSoil() {
  Serial.println("WATER SOIL");
  digitalWrite(lightWetPin, HIGH);   // Light to indicate wet soil
  digitalWrite(lightDryPin, LOW);
  digitalWrite(lightHumidPin, LOW);
}

void loop() {
  int sensorValue = readMoisture();  // Get moisture sensor value

  // Check sensor disconnection
  if (sensorValue >= DRY_THRESHOLD) {
    Serial.println("Not in soil or disconnected");
    digitalWrite(lightDryPin, LOW);
    digitalWrite(lightHumidPin, LOW);
    digitalWrite(lightWetPin, LOW);
    noTone(buzzerPin);              // Ensure buzzer is off
  }
  // Handle dry soil condition
  else if (sensorValue < DRY_THRESHOLD && sensorValue >= HUMID_THRESHOLD) {
    handleDrySoil();
  }
  // Handle humid soil condition
  else if (sensorValue < HUMID_THRESHOLD && sensorValue >= WET_THRESHOLD) {
    handleHumidSoil();
  }
  // Handle wet soil condition
  else if (sensorValue < WET_THRESHOLD) {
    handleWetSoil();
  }

  delay(1000);  // Delay before the next reading
}
