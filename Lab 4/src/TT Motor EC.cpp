/*
#include <Arduino.h>

// TODO: Define your pins
// Hint: Look at your wiring. Which pins did you use?
const int MOTOR_B_1A = A0;
const int MOTOR_B_1B = A1; 

void setup() {
  // TODO: Initialize Serial communication
  Serial.begin(115200); //ecs181 set Baude rate to 115200

  // TODO: Set your motor pins as OUTPUTs
  pinMode(MOTOR_B_1A, OUTPUT); //ecs181 setting pin A0 to output
  pinMode(MOTOR_B_1B, OUTPUT); //ecs181 setting pin A1 to output

  Serial.println("Pins set as Output"); //ecs181 debug statement for setting pins to output
}

// Aiming to produce a power output such that the rotational speed is an approximate sinusoid
void loop() {
    analogWrite(MOTOR_B_1A, 0); //reset power to start
    analogWrite(MOTOR_B_1B, 0);
    Serial.println("Speeding Up Clockwise");
    for(int power = 0; power <= 255; power += 5){
        double dubpower = power;
        double percentage = (dubpower/255)*100;
        Serial.print(percentage);
        Serial.println("% Power");
        analogWrite(MOTOR_B_1A, 0);
        analogWrite(MOTOR_B_1B, power);
        delay(200);
    }
    Serial.println("Full Power Clockwise");
    delay(1000);
    Serial.println("Slowing Down Clockwise");
    for(int power = 255; power >= 0; power -= 5){
        double dubpower = power;
        double percentage = (dubpower/255)*100;
        Serial.print(percentage);
        Serial.println("% Power");
        analogWrite(MOTOR_B_1A, 0);
        analogWrite(MOTOR_B_1B, power);
        delay(200);
    }
    Serial.println("At rest");
    delay(1000);
    Serial.println("Speeding up Counter Clockwise");
    for(int power = 0; power <= 255; power += 5){
        double dubpower = power;
        double percentage = (dubpower/255)*100;
        Serial.print(percentage);
        Serial.println("% Power");
        analogWrite(MOTOR_B_1A, power);
        analogWrite(MOTOR_B_1B, 0);
        delay(200);
    }
    Serial.println("Full Power Counter Clockwise");
    delay(1000);
    Serial.println("Slowing down Counter Clockwise");
    for(int power = 255; power >= 0; power -= 5){
        double dubpower = power;
        double percentage = (dubpower/255)*100;
        Serial.print(percentage);
        Serial.println("% Power");
        analogWrite(MOTOR_B_1A, power);
        analogWrite(MOTOR_B_1B, 0);
        delay(200);
    }
    Serial.println("At rest");
    delay(1000);
}


// Note:
// - Please uncomment the necessary lines and fill in the blank to complete the assignment.
*/