#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 heartRateSensor;

//ecs181 Set pins for traffic light module
const int greenPin = 27;
const int yellowPin = 33;
const int redPin = 32;

//ecs181 Set pin for buzzer
const int buzzerPin = 13;

//ecs181 Set pin for heart rate monitor (serial data pin)
const int heartRateDataPin = 22;

//ecs181 set variables I will need later
long lastBeat = 0; //ecs181 will need this to calculate bpm
int redIntervalBPM = 120;
int greenIntervalBPM = 80;

void setup() {
  Serial.begin(115200); //ecs181 as heart rate monitor functions via serial data, monitoring serial input/output will be essential

  //ecs181 All traffic light pins are Output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  //ecs181 Buzzer pin is also Output
  pinMode(buzzerPin, OUTPUT);

  //ecs181 I was having a lot of trouble with setting up the heart rate sensor, so I researched online and sourced the following from https://microcontrollerslab.com/esp32-heart-rate-pulse-oximeter-max30102/
  Serial.println("Initializing...");
 
  if (!heartRateSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  heartRateSensor.setup(); //Configure sensor with default settings
  heartRateSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  heartRateSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  //pinMode(heartRateDataPin, INPUT);
}

void loop() {

    //ecs181 getting the light reflection value 
    long pulseReaderRawVal = heartRateSensor.getIR();

    //ecs181 calculating bpm
    long interval = millis() - lastBeat; //ecs181 get the time between heartbeats
    lastBeat = millis();

    int intervalInSeconds = interval/1000; //ecs181 convert to seconds
    int beatsPerMinute = 60/interval

    //ecs181 Now that we have bpm we can have fun with logic
    //ecs181 Notably the bpm is read on every beat, which can be inconsistent when we are tring to read the slope of bpm for our yellow light, so we will need to work around this

    


    


 
}