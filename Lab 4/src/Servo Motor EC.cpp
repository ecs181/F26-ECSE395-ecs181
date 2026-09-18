#include <ESP32Servo.h>
// Don't forget to include the library!!
// From PlatfromIO library, search for ESP32 servo and add it to the project

// Define the servo and the pin it is connected to, what is your servo pin?
Servo myServo;
const int servoPin = A0;

// Define the minimum and maximum pulse widths for the servo
const int minPulseWidth = 500; // 0.5 ms
const int maxPulseWidth = 2500; // 2.5 ms

void setup() {
  // Attach the servo to the specified pin and set its pulse width range
  myServo.attach(servoPin, minPulseWidth, maxPulseWidth);
  Serial.begin(115200);
  // Set the PWM frequency for the servo
  myServo.setPeriodHertz(50); // Standard 50Hz servo
}

void loop() {
  // The general approach will be to modulate the servo's speed via delay
  // Rotate the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    int pulseWidth;
    // the map function is a puction that maps 0 degrees to 500 pulse width, and 180 degrees to 2500 pulse width
    // map(angle, min angle, max angle, min pulse width, max pulse width)
    pulseWidth = map(angle, 0, 180, minPulseWidth, maxPulseWidth);
    myServo.writeMicroseconds(pulseWidth);

    double delayAdder = 80*abs(sin(angle * (PI/180)));
    delay(100-delayAdder);
  }

  // Rotate the servo from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    int pulseWidth;
    // the map function is a puction that maps 0 degrees to 500 pulse width, and 180 degrees to 2500 pulse width
    // map(angle, min angle, max angle, min pulse width, max pulse width)
    pulseWidth = map(angle, 0, 180, minPulseWidth, maxPulseWidth);
    myServo.writeMicroseconds(pulseWidth);
    double delayAdder = 80*abs(sin(angle * (PI/180)));
    //Serial.println(delayAdder);
    delay(100-delayAdder);
  }
}
