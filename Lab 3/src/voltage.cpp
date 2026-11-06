
#include <Arduino.h>

// function prototype
int voltage(float analogvalue);

// Put your potentiometer pin assignment here
const int sensorPin = A0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // This is the line for printing in the serial
    int rawPotValue = analogRead(sensorPin); // ecs181
    int angleValue = voltage(rawPotValue); // ecs181
    Serial.println("");
    Serial.print("Angle Detected: ");
    Serial.print(270-angleValue); 
    Serial.print(" degrees"); 
    delay(5000); //trying to only sample every 5 second to allow to confirm value with oscilloscope if desired
}

// function to calculate output voltage
int voltage(float analogvalue){
    int voltage;
    //use the formula (Analog value*Angle Range) / (Sensor Resolution) to calculate the output voltage

    const int angleRange = 270; //ecs181 - I prefer to work with variables
    const int maxAnalogValue = 4095; //ecs181
    voltage = (analogvalue*angleRange)/maxAnalogValue; //ecs181
    return voltage;
}
