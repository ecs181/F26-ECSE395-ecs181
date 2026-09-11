#include <Arduino.h>

//Put your potentiometer pin assignment here
const int sensorPin = A0;

#define LED_PIN 13 //defining the LED pin to be pin 13 (as per schematic)


void setup() {
  pinMode(LED_PIN, OUTPUT); //setting LED_PIN to be output
  Serial.begin(115200);
}

void loop() {
  //This line should print out the values from the sensor by Serial.println(??);
  int analogValue = analogRead(sensorPin);
  if(analogValue > 2000){
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, HIGH); // LED On
    Serial.println("Touch");
  }
  else if(analogValue < 2000){
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, LOW); // LED Off
    Serial.println("No Touch");
  }
  else{ //debug case
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, LOW); // LED Off for safety
    Serial.println("Error");
  }
  delay(50); 
}