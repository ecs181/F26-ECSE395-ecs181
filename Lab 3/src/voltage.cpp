
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
    int voltageValue = voltage(rawPotValue); // ecs181
    Serial.println(voltageValue);
    Serial.println(rawPotValue); //ecs181 - confirming that the potentiometer value is correct for the outputted voltage
    delay(5000); //ecs181 - trying to only sample every 5 second to allow to confirm value with oscilloscope if desired
}

// function to calculate output voltage
int voltage(float analogvalue){
    int voltage;
    //analogRead(sensorPin); gives us 0-4095 values
    //use the formula (Analog value*Reference voltage) / (Sensor Resolution) to calculate the output voltage
    //max voltage (reference) is 3V
    const int refVoltage = 3; //ecs181 - I prefer to work with variables
    const int maxAnalogValue = 4095; //ecs181
    voltage = (analogvalue*refVoltage)/maxAnalogValue; //ecs181
    return voltage;
}
