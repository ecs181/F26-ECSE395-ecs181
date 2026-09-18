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

void loop() {
  // --- SECTION 1: Clokwise (5s) ---
  Serial.println("Clockwise 5s"); //ecs181 debug statement to indicate beginning rotation
  
  // TODO: Write HIGH to one pin and LOW to the other
  digitalWrite(MOTOR_B_1A, LOW); //ecs181 don't need motor A right now, it's responsible for counterclockwise
  digitalWrite(MOTOR_B_1B, HIGH); //ecs181 setting motor B to low makes the motor run clockwise
  
  delay(5000); //ecs181 delaying for 5000 ms (5 seconds)

  // --- SECTION 2: Stop (2s) ---
  Serial.println("Stop 2s");
  
  // TODO: Turn off the motor
  digitalWrite(MOTOR_B_1A, LOW); //ecs181 setting both motors to LOW to stop them
  digitalWrite(MOTOR_B_1B, LOW);

  delay(2000); //ecs181 delaying for 2000 ms (2 seconds)

  // --- SECTION 3: Counterclockwise (5s) ---
  Serial.println("Counterclockwise 5s");
  
  // TODO: Write HIGH to one pin and LOW to the other
  digitalWrite(MOTOR_B_1A, HIGH); //ecs181 motor A makes the motor run counter-clockwise
  digitalWrite(MOTOR_B_1B, LOW); //ecs181 don't need motor B for counter-clockwise motion

  delay(5000); //ecs181 delaying for 5000 ms (5 seconds)

  // --- SECTION 4: Stop (2s) ---
  Serial.println("Stop 2s");
  
  // TODO: Turn off the motor
  digitalWrite(MOTOR_B_1A, LOW);
  digitalWrite(MOTOR_B_1B, LOW);

  delay(2000);
}


// Note:
// - Please uncomment the necessary lines and fill in the blank to complete the assignment.
*/