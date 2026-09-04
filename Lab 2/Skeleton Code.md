```
#include <Arduino.h>
// This is required in PlatformIO but hidden in the standard Arduino IDE.

#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // TODO: Define your baud rates
  Serial.begin(115200); // Start the Serial connection
}

void loop() {
  // Making my ESP32 do an SoS Signal, so that will be the message
  Serial.println("SoS"); // Print the words to the Serial Monitor.
  
  // SOS Signal
  //First S (Three long)
  for(int i = 0; i<3; i++){
    digitalWrite(LED_PIN, HIGH); // LED On
    delay(1000); // Speed in milliseconds
    digitalWrite(LED_PIN, LOW); // LED Off
    delay(200); // Speed in milliseconds
  }
  // O (Three short)
  for(int j = 0; j<3; j++){
    digitalWrite(LED_PIN, HIGH); // LED On
    delay(500); // Speed in milliseconds
    digitalWrite(LED_PIN, LOW); // LED Off
    delay(200); // Speed in milliseconds
  }
  // Second S (Three Long)
  for(int k = 0; k<3; k++){
    digitalWrite(LED_PIN, HIGH); // LED On
    delay(1000); // Speed in milliseconds
    digitalWrite(LED_PIN, LOW); // LED Off
    delay(200); // Speed in milliseconds
  }

}
```

- Notes:
	- Please uncomment the necessary lines and fill in the blank to complete the assignment.
	- In `Serial.begin(_____);`
		- `115200` is recommended, but feel free to try it at other baud rates.
		- Baud rate is the speed of data transmission, measuring the number of signal changes per second in communication channel.