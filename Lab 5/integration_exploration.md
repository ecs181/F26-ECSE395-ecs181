# Lab 5: Sensor & Actuator Integration

#### This lab is the ifnal lab with the ESP32, and it is the culmination of our work with sensors and actuators, now actually combining the two

## Methodology
1. Code is updated to ESP32 via the PlatformIO extension in VSCode
2. The sensor being used is the Heart Rate Module from the Sunfounder Kit
3. The actuators being used are the LED Traffic Light Module and Passive Buzzer Module from the Sunfounder Kit.
4. All code for integrating these sensors can be found in main.cpp in the Lab 5 folder in this Github Repository
5. Videos of the integration functioning can also be found in the Video folder of this Github Repository

## Conceptialization
My friend Jack has two types of **Supraventricular Tachycardia**, which causes him to have episodes wherein his heart beats very fast. He plays sports, so these episodes can be potentially dangerous, as he could not notice symptoms during intense activity. Additionally, he must take a break from activity during episodes, and monitor his heart rate to see if it is worsening. So, I had a couple of problems to approach:
1. Create some way to notify Jack that his heart rate is dangerously high during activity (Passive Buzzer)
2. Provide Jack some indication of the heart rate "regimes" that he is in
> Every so often my heart gets a weird electrical signal that causes it to speed up
>When an episode occurs, I have to stop what I'm doing and wait for my heart to calm down
>
>-- Jack
## Application
My tasks are as follows (loose functional specs):
- [ ] Monitor the heart rate
- [ ] Trigger the buzzer when heart rate exceeds safe limit
- [ ] Display lights as follows:
  - Green light when within safe/good limit
  - Red light when in dangerous zone and heart rate is constant/increasing
  - Yellow zone when in dangerous zone and heart rate is actively decreasing
**Circuit diagram below:**
![Circuit Diagram](./videos/Lab5CircuitDiagram.pdf)
## Application Difficulties
| Problem | Solution |
| ------- | -------- |
| Detecting a heartbeat and working with the heartbeat detection module (essentially just LEDs and a detector) is extremely difficult | Found out about heartrate.h, which has a heartbeat detection function, and also downloaded a library to work with the detection module |
| The detection is pretty inaccurate, so detecting the slope of heartrate off of two measurements is unreliable | Sample a larger range of heartbeats for detecting a negative slope |
| The module oftentimes has trouble picking up on the heartbeat | Finding a better grip to hold the module: this indicates that future extensions may require work on how the sensor is attached to the user, and also tuning of the LED brightness settings |
## Code Tips
*Relevant variables can be changed via the environment variables towards the top*
- redIntervalBPM and buzzerIntervalBPM controls the heart rate that is defined as "dangerous" for triggering the red light and the buzzer

## Time Reporting and Reflection
1. This assignment, in all, took me around 14 hours, which is part of the reason why it is late
2. I would associate a high level of difficulty with this assignment
3. The application and finagling of the heart rate monitor module consumed the most of my time, and trying various fixes often took hours of research
4. I feel very confident with the course content
5. For future years, requiring the writeup (and even the finished product) on the same day as the actual lab can be a **very** tall task, especially if students have other obligations on that day. Even having the lab on Wednesday and requiring the writeup/finished product on Friday would ease that burden immensely.

- Jack's Supraventricular Tachycardia (SVT)
- Looked into making own heart rate detection function but that shit is COMPLICATED so using built-in one from heartrate.h 
