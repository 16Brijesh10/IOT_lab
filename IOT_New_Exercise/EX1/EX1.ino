// Distance Measurement
#include <Wire.h>  

// Pin Definitions
#define echoPin 3  
#define trigPin 2  
#define buzzerPin 8  
#define light1Pin 11
#define light2Pin 12  
#define light3Pin 13

// Constants for distance thresholds
const int NEAR_RANGE = 10;      // Near range threshold in cm
const int MID_RANGE = 50;       // Mid range threshold in cm
const int DELAY_TIME = 1000;    // Delay between sensor readings

long duration;  
int distance;  

void setup() { 
  // Initialize pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  pinMode(buzzerPin, OUTPUT);  
  pinMode(light1Pin, OUTPUT); 
  pinMode(light2Pin, OUTPUT); 
  
  // Initialize serial communication
  Serial.begin(9600);  
  Serial.println("Annamalai University BE CSE 2023");
  Serial.println("Distance Measure Program");
}

// Function to calculate distance from the ultrasonic sensor
int getDistance() {
  // Send a pulse to the ultrasonic sensor
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  // Read the echo duration and calculate distance in cm
  duration = pulseIn(echoPin, HIGH); 
  int calculatedDistance = duration * 0.034 / 2;  
  return calculatedDistance;
}

// Function to manage the buzzer and lights based on distance
void handleAlerts(int distance) {
  if (distance <= NEAR_RANGE) {
    // Near range: Turn on light1 and buzzer at 1kHz
    Serial.println("Near Range");
    digitalWrite(light1Pin, HIGH);
    digitalWrite(light2Pin, LOW);
    digitalWrite(light3Pin, LOW);
    tone(buzzerPin, 4000);  // Buzzer at 1kHz
    delay(1000);            // Sound for 1 second
    noTone(buzzerPin);      // Turn off buzzer
  } 
  else if (distance > NEAR_RANGE && distance <= MID_RANGE) {
    // Mid-range: Turn on light2 and buzzer at 500Hz
    Serial.println("Mid Range");
    digitalWrite(light2Pin, HIGH);
    digitalWrite(light1Pin, LOW);
    digitalWrite(light3Pin, LOW);
    tone(buzzerPin, 500);   // Buzzer at 500Hz
    delay(500);             // Sound for 500 ms
    noTone(buzzerPin);      // Turn off buzzer
  } 
  else {
    // Far range: Turn off lights(1 & 2) and buzzer
    Serial.println("Far Range");
    digitalWrite(light1Pin, LOW);
    digitalWrite(light2Pin, LOW);
    digitalWrite(light3Pin, HIGH);
    noTone(buzzerPin);      // Ensure buzzer is off
    delay(500);
  }
}

void loop() { 
  // Get the current distance from the ultrasonic sensor
  distance = getDistance();  
  
  // Print distance to Serial Monitor
  Serial.print("Distance: "); 
  Serial.print(distance); 
  Serial.println(" cm");

  // Handle lights and buzzer based on distance
  handleAlerts(distance);

  // Delay between measurements to avoid excessive reading
  delay(DELAY_TIME);
}
