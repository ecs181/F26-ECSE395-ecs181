#include <Arduino.h>

//Put your potentiometer pin assignment here
const int sensorPin = A0;

#define LED_PIN 13 //ecs181 defining the LED pin to be pin 13 (as per schematic)


void setup() {
  pinMode(LED_PIN, OUTPUT); //ecs181 setting LED_PIN to be output
  Serial.begin(115200);
}

void loop() {
  //This line should print out the values from the sensor by Serial.println(??);
  int analogValue = analogRead(sensorPin);
  if(analogValue > 2000){ //ecs181 if the touch sensor is being touched
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, HIGH); //ecs181 LED On
    Serial.println("Touch");
  }
  else if(analogValue < 2000){//ecs181 if the touch sensor is not being touched
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, LOW); //ecs181 LED Off
    Serial.println("No Touch");
  }
  else{ //debug case
    Serial.println(analogValue); //debug statement
    digitalWrite(LED_PIN, LOW); //ecs181 LED Off for safety
    Serial.println("Error");
  }
  delay(50); 
}