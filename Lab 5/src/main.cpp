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
int redIntervalBPM = 80;
int buzzIntervalBPM = 100;
int numDecreasingBeats = 0;
int prevHeartRate = -1;
int buzzerCounter = 0;

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
  heartRateSensor.setPulseAmplitudeGreen(0x0A); //Turn Red LED to low to indicate sensor is running
  heartRateSensor.setPulseAmplitudeRed(0); //Turn off Green LED
  //pinMode(heartRateDataPin, INPUT);
}

void loop() {

    //ecs181 getting the light reflection value 
    long pulseReaderRawVal = heartRateSensor.getIR();
    if (checkForBeat(pulseReaderRawVal) == true){
        //ecs181 calculating bpm
        long interval = millis() - lastBeat; //ecs181 get the time between heartbeats
        lastBeat = millis();
        double intervalInSeconds = interval/1000.00; //ecs181 convert to seconds
        int beatsPerMinute = 60/intervalInSeconds;
        Serial.println("");
        Serial.print(beatsPerMinute);
        Serial.print(" beats per minute | ");

        //ecs181 Now that we have bpm we can have fun with logic
        //ecs181 Notably the bpm is read on every beat, which can be inconsistent when we are tring to read the slope of bpm for our yellow light, so we will need to work around this
        if(prevHeartRate >= 0 && beatsPerMinute <= prevHeartRate){
            numDecreasingBeats++;
        }
        else{
            numDecreasingBeats = 0;
        }
        Serial.print(numDecreasingBeats);
        Serial.print(" decreasing beats in a row | ");
        prevHeartRate = beatsPerMinute;

        if(beatsPerMinute < redIntervalBPM){ //ecs181 no matter what, if our bpm is under the green interval, we are at green
            digitalWrite(greenPin, HIGH);
            digitalWrite(yellowPin, LOW);
            digitalWrite(redPin, LOW);
            Serial.print("GREEN zone");
            buzzerCounter=0;
        }
        else if(beatsPerMinute > redIntervalBPM && numDecreasingBeats < 3){ //ecs181 likewise, over red interval is always in red, and if we are in red and not decreasing, we're red
            digitalWrite(greenPin, LOW);
            digitalWrite(yellowPin, LOW);
            digitalWrite(redPin, HIGH);
            Serial.print("RED zone");
            if(beatsPerMinute > buzzIntervalBPM){
                buzzerCounter++;
                if(buzzerCounter > 20){
                    tone(buzzerPin, 500, 2000);
                    buzzerCounter=0;
                }
            }
        }
        //ecs181 the goal of the yellow zone is to let the user know that their heart rate is indeed dropping
        //ecs181 thus we take the last three readings whilst in the yellow zone and if heart rate is indeed dropping, we set light to yellow
        else if(numDecreasingBeats >= 3) { //ecs181 on a downward trend, so yellow
            digitalWrite(greenPin, LOW);
            digitalWrite(yellowPin, HIGH);
            digitalWrite(redPin, LOW);
            buzzerCounter=0; //If in the yellow zone, there is no need to have the warning buzzer activate
            Serial.print("YELLOW zone");
        }
    }
    
    


    


 
}